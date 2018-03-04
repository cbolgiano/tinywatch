<p align="center"><img src="https://github.com/cbolgiano/tinywatch/blob/develop/assets/img/tinywatch.png" /> </p>

# tinywatch [![Build Status](https://travis-ci.org/cbolgiano/tinywatch.svg?branch=develop)](https://travis-ci.org/cbolgiano/tinywatch)
An open source smart watch that is powered by TinyCircuits TinyScreen+, TinyShield NRF8001 BLE, etc.

I wanted a project to help familarize myself with the intriguing world of tinkering and physical computing. I figured a smart watch would be a perfect project to exercise the ignorance of these topics out of me. In addition to learning about tinkering and physical computing this project will be an exercise in exploring the idea of deletability. I did not know of this ility until I watched: *[Greg Young - The art of destroying software](https://vimeo.com/108441214)*.  Watch it and hopefully you will be as interested as I was when birthing this project to explore such an interesting concept.

## Compatible Hardware

*[TinyScreen+](https://tinycircuits.com/collections/all/products/tinyscreenplus)*

*[BLE Nordic Tinyshield](https://tinycircuits.com/collections/all/products/bluetooth-low-energy-nordic-tinyshield)*

[Proto Board TinyShield](https://tinycircuits.com/collections/proto-boards/products/proto-board-tinyshield)

[Lithium Ion Polymer Battery - 3.7V 270mAh](https://tinycircuits.com/collections/accessories/products/lithium-ion-polymer-battery-3-7v-270mah)

[DC3V/0.1A 1.5V/0.05A 10x2.7mm Coin Mobile Phone Vibration Motor](https://www.amazon.com/gp/product/B00PZYMCT8/ref=ox_sc_sfl_title_4?ie=UTF8&psc=1&smid=ATVPDKIKX0DER)

## External Arduino Libraries

*[TinyCircuits-TinyScreen_Lib](https://github.com/TinyCircuits/TinyCircuits-TinyScreen_Lib)*

*[arduino-BLEPeripheral](https://github.com/sandeepmistry/arduino-BLEPeripheral)*

*[Time](https://github.com/PaulStoffregen/Time)*

## Frameworks

*[Apache Cordova](https://cordova.apache.org/)*

## Cordova Plugins

*[cordova-plugin-ble-central](https://github.com/don/cordova-plugin-ble-central)*

*[NotificationListener-cordova](https://github.com/coconauts/NotificationListener-cordova)*

## Documentation

*[Home](https://github.com/cbolgiano/tinywatch/wiki)*

*[tinywatch-sleep](https://github.com/cbolgiano/tinywatch/wiki/tinywatch-sleep)*

*[tinywatch-time](https://github.com/cbolgiano/tinywatch/wiki/tinywatch-time)*

*[tinywatch-notification](https://github.com/cbolgiano/tinywatch/wiki/tinywatch-notification)*

*[tinywatch-display](https://github.com/cbolgiano/tinywatch/wiki/tinywatch-display)*

*[tinywatch-vibrate](https://github.com/cbolgiano/tinywatch/wiki/tinywatch-vibrate)*

*[tinywatch-battery](https://github.com/cbolgiano/tinywatch/wiki/tinywatch-battery)*

## Usage

### General 
1. Clone Project.

### Android App
1. Install *[Node.js](https://nodejs.org/en/)*. It is needed for Cordova.
2. Open terminal or cmd and execute ```npm install -g cordova``` to install Cordova.
3. Follow Apache's documentation on *[Installing the Requirements](https://cordova.apache.org/docs/en/latest/guide/platforms/android/index.html#installing-the-requirements)* to setup development environment for android.
4. Go to /tinywatch/app/tinywatch.
5. Execute ```cordova run android```. This will build and deploy the tinywatch android application to an emulator or device.

### Arduino Sketch
1. Open ```tinywatch.ino``` in Arduino IDE
2. Follow the *[TinyScreen+ Setup Guide](https://tinycircuits.com/blogs/learn/158833543-tinyscreen-setup)*
2. Choose ```Sketch``` -> ```Include Library``` -> ```Add .ZIP Libraries...```
3. Open All .ZIP in ```/tinywatch/libs/```
4. Attach Tinyscreen+ and BLE Nordic Tinyshield Together
5. Connect Tinyscreen+ and BLE Nordic Tinyshield to Computer
6. To Compile Choose ```Verify``` in Arduino IDE
7. To Upload Choose ```Upload``` in Arduino IDE

### Platformio (Not Working)
1. Install ```python2.7```
2. Install ```pip```
3. Install ```platformio```
4. Change directories to where the ```platformio.ini``` is located
5. To build and upload execute ```platformio run --target upload```

## License

This project is [licensed](LICENSE) under the [MIT Licence](http://en.wikipedia.org/wiki/MIT_License).
