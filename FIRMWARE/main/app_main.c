#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_err.h"
#include "audio_element.h"
#include "audio_pipeline.h"
#include "audio_event_iface.h"
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include "i2s_stream.h"
#include "fatfs_stream.h"
#include "mp3_decoder.h"
#include "esp_peripherals.h"
#include "periph_sdcard.h"
#include "board.h"

static const char *TAG = "MP3_PLAYER";

#define MOUNT_POINT "/sdcard"


#define BUTTON_NEXT        GPIO_NUM_32
#define BUTTON_PREV        GPIO_NUM_33
#define BUTTON_PLAY_PAUSE  GPIO_NUM_25
#define BUTTON_VOL_UP      GPIO_NUM_26
#define BUTTON_VOL_DOWN    GPIO_NUM_27
#define BUTTON_BL_CONTROL  GPIO_NUM_14

#define MAX_FILES 64
static char file_list[MAX_FILES][256];
static int total_files = 0;
static int current_index = 0;
static bool is_playing = true;
static audio_pipeline_handle_t pipeline = NULL;
static audio_element_handle_t i2s_stream_writer = NULL;

void play_file(const char *filepath)
{
    ESP_LOGI(TAG, "Playing file: %s", filepath);

    if (pipeline) {
        audio_pipeline_terminate(pipeline);
        audio_pipeline_deinit(pipeline);
        pipeline = NULL;
    }

    audio_element_handle_t fatfs_stream_reader, mp3_decoder;

    audio_pipeline_cfg_t pipeline_cfg = DEFAULT_AUDIO_PIPELINE_CONFIG();
    pipeline = audio_pipeline_init(&pipeline_cfg);
    mem_assert(pipeline);

    fatfs_stream_cfg_t fatfs_cfg = FATFS_STREAM_CFG_DEFAULT();
    fatfs_cfg.type = AUDIO_STREAM_READER;
    fatfs_stream_reader = fatfs_stream_init(&fatfs_cfg);

    mp3_decoder_cfg_t mp3_cfg = DEFAULT_MP3_DECODER_CONFIG();
    mp3_decoder = mp3_decoder_init(&mp3_cfg);

    i2s_stream_cfg_t i2s_cfg = I2S_STREAM_CFG_DEFAULT();
    i2s_cfg.type = AUDIO_STREAM_WRITER;
    i2s_stream_writer = i2s_stream_init(&i2s_cfg);

    audio_pipeline_register(pipeline, fatfs_stream_reader, "file");
    audio_pipeline_register(pipeline, mp3_decoder, "mp3");
    audio_pipeline_register(pipeline, i2s_stream_writer, "i2s");

    audio_pipeline_link(pipeline, (const char *[]) {"file", "mp3", "i2s"}, 3);

    audio_element_set_uri(fatfs_stream_reader, filepath);

    audio_pipeline_run(pipeline);
    is_playing = true;
}

void configure_buttons()
{
    gpio_config_t io_conf = {
        .intr_type = GPIO_INTR_DISABLE,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pin_bit_mask = (1ULL << BUTTON_NEXT) | (1ULL << BUTTON_PREV) |
                        (1ULL << BUTTON_PLAY_PAUSE) | (1ULL << BUTTON_VOL_UP) |
                        (1ULL << BUTTON_VOL_DOWN) | (1ULL << BUTTON_BL_CONTROL)
    };
    gpio_config(&io_conf);
}

void button_poll_task(void *arg)
{
    bool last_next = true, last_prev = true, last_play = true;
    bool last_vol_up = true, last_vol_down = true;

    while (1) {
        bool curr_next = gpio_get_level(BUTTON_NEXT);
        bool curr_prev = gpio_get_level(BUTTON_PREV);
        bool curr_play = gpio_get_level(BUTTON_PLAY_PAUSE);
        bool curr_vol_up = gpio_get_level(BUTTON_VOL_UP);
        bool curr_vol_down = gpio_get_level(BUTTON_VOL_DOWN);

        if (!curr_next && last_next) {
            current_index = (current_index + 1) % total_files;
            play_file(file_list[current_index]);
        }
        if (!curr_prev && last_prev) {
            current_index = (current_index - 1 + total_files) % total_files;
            play_file(file_list[current_index]);
        }
        if (!curr_play && last_play) {
            if (is_playing) {
                audio_pipeline_pause(pipeline);
                is_playing = false;
            } else {
                audio_pipeline_resume(pipeline);
                is_playing = true;
            }
        }
        if (!curr_vol_up && last_vol_up) {
            audio_element_info_t info = {};
            audio_element_getinfo(i2s_stream_writer, &info);
            info.volume += 10;
            if (info.volume > 100) info.volume = 100;
            audio_element_setinfo(i2s_stream_writer, &info);
        }
        if (!curr_vol_down && last_vol_down) {
            audio_element_info_t info = {};
            audio_element_getinfo(i2s_stream_writer, &info);
            info.volume -= 10;
            if (info.volume < 0) info.volume = 0;
            audio_element_setinfo(i2s_stream_writer, &info);
        }

        last_next = curr_next;
        last_prev = curr_prev;
        last_play = curr_play;
        last_vol_up = curr_vol_up;
        last_vol_down = curr_vol_down;

        vTaskDelay(pdMS_TO_TICKS(150));
    }
}

void app_main(void)
{
    esp_log_level_set("AUDIO_ELEMENT", ESP_LOG_WARN);

    ESP_LOGI(TAG, "Initializing peripherals...");
    esp_periph_config_t periph_cfg = DEFAULT_ESP_PERIPH_SET_CONFIG();
    esp_periph_set_handle_t set = esp_periph_set_init(&periph_cfg);

    audio_board_sdcard_init(set, ESP_SD_MODE_SPI);
    configure_buttons();

    ESP_LOGI(TAG, "Opening directory %s", MOUNT_POINT);
    DIR *dir = opendir(MOUNT_POINT);
    if (!dir) {
        ESP_LOGE(TAG, "Failed to open dir: %s", MOUNT_POINT);
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL && total_files < MAX_FILES) {
        if (entry->d_type == DT_REG && strstr(entry->d_name, ".mp3")) {
            snprintf(file_list[total_files], sizeof(file_list[0]), "%s/%s", MOUNT_POINT, entry->d_name);
            total_files++;
        }
    }
    closedir(dir);

    if (total_files == 0) {
        ESP_LOGW(TAG, "No MP3 files found");
        return;
    }

    current_index = 0;
    play_file(file_list[current_index]);

    xTaskCreate(button_poll_task, "button_poll", 4096, NULL, 5, NULL);

    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }