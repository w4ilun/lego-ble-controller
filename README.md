##4-channel Bluetooth LE controller for Lego Power Functions

First attempt at making a Lego BLE contoller.

* PCB Design and Fabrication - EasyEDA
* Firmware - Arduino
* Remote Control App - Web Bluetooth APIs

###Top Layer
![Top Layer](/hardware/gerber_top.png)

###Bottom Layer
![Bottom Layer](/hardware/gerber_bottom.png)

###Components
* 1 x Arduino Pro Micro module
* 1 x HM-10 Bluetooth LE module
* 2 x TB6612FNG Motor Controller IC - U2 & U3
* 2 x Tantalum Capacitor 10uF 25V
* 4 x Ceramic Capacitor 0.1uF 25V
* 5 x JST-XH 4 Pin Connectors Male/Female pairs
* 5 x Lego Power Functions Extension Wire

###Remote Control App
* Uses the Web Bluetooth API in Chrome to connect and control the board
* To use, first enable Web Bluetooth in your Chrome browser (e.g. chrome://flags )
* Go to https://w4ilun.github.io/lego-ble-controller and click connect
* Feel free to customize the UI with additional controls and adding the remaining channels

##Control Protocol
* The acceptable range for each channel are integers between -255 and 255
* (-) negative values will reverse the motor/servo direction
* Encoding Scheme: **m1val**#**m2val**#**m3val**#**m4val** E.g. 100#255#-128#30
