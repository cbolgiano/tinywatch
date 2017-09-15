cordova.define('cordova/plugin_list', function(require, exports, module) {
module.exports = [
    {
        "id": "cordova-plugin-ble-central.ble",
        "file": "plugins/cordova-plugin-ble-central/www/ble.js",
        "pluginId": "cordova-plugin-ble-central",
        "clobbers": [
            "ble"
        ]
    },
    {
        "id": "cordova-plugin-globalization.GlobalizationError",
        "file": "plugins/cordova-plugin-globalization/www/GlobalizationError.js",
        "pluginId": "cordova-plugin-globalization",
        "clobbers": [
            "window.GlobalizationError"
        ]
    },
    {
        "id": "cordova-plugin-globalization.globalization",
        "file": "plugins/cordova-plugin-globalization/www/globalization.js",
        "pluginId": "cordova-plugin-globalization",
        "clobbers": [
            "navigator.globalization"
        ]
    },
    {
        "id": "net.coconauts.notification-listener.NotificationListener",
        "file": "plugins/net.coconauts.notification-listener/www/notification-listener.js",
        "pluginId": "net.coconauts.notification-listener",
        "clobbers": [
            "notificationListener"
        ]
    }
];
module.exports.metadata = 
// TOP OF METADATA
{
    "cordova-plugin-compat": "1.1.0",
    "cordova-plugin-ble-central": "1.1.4",
    "cordova-plugin-globalization": "1.0.5",
    "net.coconauts.notification-listener": "0.0.1"
};
// BOTTOM OF METADATA
});