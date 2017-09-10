var defaultTime = 1500;
var tenMinutes = 600000;
var thirtySeconds = 30000;
var fiveSeconds = 5000;

var tinywatch = {
  uuid: 'CCC0',
  characteristics: {
    time: {
      uuid: 'CCC1'
    },
    notification: {
      uuid: 'CCC2'
    }
  },
  id: null
};

/**
 * Show message.
 * @param {String} text Text to show.
 * @param {String} containerClassName CSS classes for message container.
 * @param {String} className CSS classes for message.
 */
function showMessage(text, containerClassName, className){
  if(containerClassName !== null || containerClassName !== undefined){
    document.querySelector('#messageContainer').className = containerClassName;
  }
  if(className){
    document.querySelector('#message').className = className;
  }
  document.querySelector('#message').innerHTML = text;
}

/**
 * Number to 4 byte ArrayBuffer.
 * @param {Number} num Number to convert to 4 byte ArrayBuffer.
 * @return ArrayBuffer
 */
function toUint32ArrayBuffer (num) {
  var ab = new ArrayBuffer(4); // an Int32 takes 4 bytes
  var view = new DataView(ab);
  view.setUint32(0, num, false); // byteOffset = 0; litteEndian = false
      
  return ab;
}

var app = {
  initialize: function(){
    this.bindEvents();
  },
  bindEvents: function(){
    document.addEventListener('deviceready', app.onDeviceReady, false);
  },
  onDeviceReady: function() {
    app.scan();
    notificationListener.listen(app.onNotification, app.onNotificationFailure);
  },
  onNotification: function(notification) {
    /*showMessage('Sending Notification...', 'blink', 'event listening');

      function success(){
      showMessage('Notification Sent!', '', 'event received');
      setTimeout(function() {
	 
      }, fiveSeconds);
    }*/

    ble.write(tinywatch.id, tinywatch.uuid, tinywatch.characteristics.notification.uuid,new ArrayBuffer(), null, null);
  },
  /*onNotificationFailure: function(reason) {
    showMessage('Notification error!: ' + reason, '', 'event failed');
  },*/
  scan: function() {
    showMessage('Finding tinywatch...', 'blink', 'event listening');

    var foundTinywatch = false;

    function onScan(peripheral) {
      showMessage('Found tinywatch!', 'blink', 'event listening');
  
      foundTinywatch = true;

      ble.connect(peripheral.id, app.onConnect, app.onDisconnect);
    }

    function scanFailure(reason) {
      app.scan();
    }
    
    ble.scan([tinywatch.uuid], 5, onScan, scanFailure);

     setTimeout(function() {
       if (!foundTinywatch) {
         app.scan();
       } else {
         showMessage('Connected to tinywatch.', '', 'event received');
       }
     }, fiveSeconds);
  },
  onConnect: function(peripheral) {
    tinywatch.id = peripheral.id;
    showMessage('Connected to tinywatch.', '', 'event received');
    app.writeTime();
  },
  onDisconnect: function(reason) {
    app.scan();
  },
  writeTime: function(){
    function success(){
      setTimeout(function() {
        app.writeTime();
      }, tenMinutes);
    }

    function failure(reason){
      setTimeout(function() {
        app.writeTime();
      }, thirtySeconds);
    }

    //Get local date to send to tinywatch.
    navigator.globalization.dateToString(new Date(), function(date){
      var timezoneOffset = new Date(date.value).getTimezoneOffset() * 60000;
      var now = (Date.now() - timezoneOffset) / 1000;
      var dataToSend = toUint32ArrayBuffer(now);
      ble.write(tinywatch.id, tinywatch.uuid, tinywatch.characteristics.time.uuid, dataToSend, this.success, this.failure);
    }, function(){      
      setTimeout(function() {
        app.writeTime();
      }, tenMinutes);
    });
  }
};

app.initialize();
