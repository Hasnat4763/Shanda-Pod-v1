# Shanda Pod

It is an MP3 player which can also play audio via bluetooth A2DP source and a PCM5102A module

I made this project because I wanted to experiment with mp3 players and I need an mp3 player with bluetooth outputs



# PCB

This is the Schematic

![image](https://github.com/user-attachments/assets/cf8cf1f3-c7ba-49cb-905d-fadb41d9e061)

This is the PCB

<img width="470" height="645" alt="image" src="https://github.com/user-attachments/assets/3620366e-a8a8-40f0-a261-e14fbf11dbe9" />


PCB 3D View

<img width="595" height="567" alt="image" src="https://github.com/user-attachments/assets/a2bb433f-2579-4d33-966e-b1c03e4d77fc" />


<img width="610" height="717" alt="image" src="https://github.com/user-attachments/assets/3f319d5f-0245-49e9-b67a-8d00bf88b0c3" />


# CAD

I designed it in Fusion360 which was pretty hard as it crashed idk why
This is all the parts fitted together

<img width="868" height="642" alt="image" src="https://github.com/user-attachments/assets/f35d87f6-e101-42c3-a9c3-510c25d019a7" />


<img width="633" height="594" alt="image" src="https://github.com/user-attachments/assets/e5572c78-542b-4a17-8968-3e1fb05e89f8" />


<img width="498" height="548" alt="image" src="https://github.com/user-attachments/assets/6541612a-bd79-411b-b075-8530d8cf3736" />


This is a cover which will sit on top of the battery

![image](https://github.com/user-attachments/assets/d2665aa3-3a77-4949-9ecc-f9aa24d3bc90)


# Schematic

I have some parts outside of my PCB

![image](https://github.com/user-attachments/assets/d00d3899-5d28-4b81-9fc1-e293170bbf6d)

# BOM

| Name                                                                  | Qty | Final Price - USD(BDT) | Link                                                                                                                |
| --------------------------------------------------------------------- | --- | ----------------------- | ------------------------------------------------------------------------------------------------------------------- |
| ESP-32-WROVER-E                                                       | 1   | US $7.39                | [here](https://www.aliexpress.com/item/1005008347478258.html?spm=a2g0o.cart.0.0.35b638daQUHsS4&mp=1)                                                             |
| NASAYI 10pcs/lot DM3AT-SF-PEJM5                                       | 10  | US $8.63                | [here](https://www.aliexpress.com/item/1005009250329013.html?spm=a2g0o.cart.0.0.35b638daQUHsS4&mp=1&pdp_ext_f=%7B%22cart2PdpParams%22%3A%7B%22pdpBusinessMode%22%3A%22retail%22%7D%7D)                                  |
| CH340C sop-16 Chipset                                                 | 5   | US $1.44                | [here](https://www.aliexpress.com/item/1005004970840775.html?spm=a2g0o.cart.0.0.35b638daQUHsS4&mp=1)                                           |
| 6092 bq25185 USB / DC / Solar Charger with 3.3V Buck Board            | 1   | US $13.66               | [here](https://www.aliexpress.com/item/1005008651296534.html?spm=a2g0o.cart.0.0.35b638daQUHsS4&mp=1)                                                                |
| 100NF 0.1UF 50V C0805 Capacitor                                       | 100 | US $0.73                | [here](https://www.aliexpress.com/item/1115774532.html?spm=a2g0o.cart.0.0.35b638daQUHsS4&mp=1)                                                                                   |
|  SSD1306                                                              | 1   | US $1.42                | [here](https://www.aliexpress.com/item/1005003780343300.html?spm=a2g0o.cart.0.0.35b638daQUHsS4&mp=1)                                                                                   |
| PCM5102A DAC                                                          | 1   | US $4.05                | [here](https://www.aliexpress.com/item/1005006104368969.html?spm=a2g0o.cart.0.0.35b638daQUHsS4&mp=1)                                                                                   |
| Insert M1.6 Brass Heat Threaded Insert Nut and Stainless Steel Screw  |set  | US $15.02               | [here](https://www.aliexpress.com/item/1005004837433548.html?spm=a2g0o.cart.0.0.35b638daQUHsS4&mp=1)                                                                                   |
| MHP30 Mini Hot Plate                                                  | 1   | US $13.52               | [here](https://www.aliexpress.com/item/1005005887052045.html?spm=a2g0o.cart.0.0.72f938daHYVVmK&mp=1)          |
| 18650 Lithium-ion                                                     | 2   | 348 BDT                 | [here](https://www.daraz.com.bd//products/i337388376-s1645620986.html?spm=a2o42.cart.0.0.5b8f282903B5mN&urlFlag=true&tradePath=%2CcartPriceDrop%2Ccart)                                           |
| PCB                                                                   | 5   | US $26.68               | [here](https://hc-cdn.hel1.your-objectstorage.com/s/v3/ba1be02d5d65575ba7409b266db8009ed1d59e8f_image.png)                                          |
| Stencil                                                               | 1   | US $$8.90               | [here](https://hc-cdn.hel1.your-objectstorage.com/s/v3/ba1be02d5d65575ba7409b266db8009ed1d59e8f_image.png)                                         |                                                                                 |
| Soldering Paste                                                       | 1   | US $5.66                | [here](https://www.aliexpress.com/item/1005006866665560.html?spm=a2g0o.productlist.main.1.6cdaixN5ixN5lS&algo_pvid=d2d48ad6-fe2d-4fcb-97f4-56ea489d9285&pdp_ext_f=%7B%22order%22%3A%223526%22%2C%22eval%22%3A%221%22%7D&utparam-url=scene%3Asearch%7Cquery_from%3A)                                         |        
| Top Case                                                              | 1   | Printing Legion         | 
| Bottom Case                                                           | 1   | Printing Legion         |
| Battery Cover                                                         | 1   | Printing Legion         |

# Total Cost: ~ 120$ USD

