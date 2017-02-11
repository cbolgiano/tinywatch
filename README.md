<p align="center"><img src="https://github.com/cbolgiano/tinywatch/blob/develop/img/tinywatch.png" /> </p>

# tinywatch [![Build Status](https://travis-ci.org/cbolgiano/tinywatch.svg?branch=develop)](https://travis-ci.org/cbolgiano/tinywatch)
A project to create an open source watch that is powered by TinyCircuits TinyScreen+, TinyShield NRF8001 BLE, td2play, etc.

## Compatible Hardware

*[TinyScreen+](https://tinycircuits.com/collections/all/products/tinyscreenplus)*

*[BLE Nordic Tinyshield](https://tinycircuits.com/collections/all/products/bluetooth-low-energy-nordic-tinyshield)*

## External Libraries

*[td2play](https://github.com/zet23t/td2play)*

*[arduino-BLEPeripheral](https://github.com/sandeepmistry/arduino-BLEPeripheral)*

*[Time](https://github.com/PaulStoffregen/Time)*

## Frameworks

*[Apache Cordova](https://cordova.apache.org/)*

## Plugins

*[cordova-plugin-ble-central](https://github.com/don/cordova-plugin-ble-central)*

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
2. Choose ```Sketch``` -> ```Include Library``` -> ```Add .ZIP Libraries...```
3. Open All .ZIP in ```/tinywatch/libs/```
4. Attach Tinyscreen+ and BLE Nordic Tinyshield Together
5. Connect Tinyscreen+ and BLE Nordic Tinyshield to Computer
6. To Compile Choose ```Verify``` in Arduino IDE
7. To Upload Choose ```Upload``` in Arduino IDE

## License

This project is [licensed](LICENSE) under the [MIT Licence](http://en.wikipedia.org/wiki/MIT_License).
