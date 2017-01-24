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

var defaultTime = 1500;

var tinywatch = {
  uuid: 'CCC0',
  characteristics: {
    time: {
      uuid: 'CCC2'
    }
  },
  id: null
};

var app = {
  initialize: function(){
    this.bindEvents();
  },
  bindEvents: function(){
    document.addEventListener('deviceready', this.onDeviceReady, false);
  },
  onDeviceReady: function() {
    app.scan();
  },
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
       }
     }, 5000);
  },
  onConnect: function(peripheral) {
    tinywatch.id = peripheral.id;
    showMessage('Connected to tinywatch.', '', 'event received');
    app.writeTime(peripheral);
  },
  onDisconnect: function(reason) {
    app.scan();
  },
  writeTime: function(p){
    function success(){
      showMessage('Successfully wrote time.', '', 'event received');
    }

    function failure(reason){
      showMessage('Failed to write time.', '', 'event received');
    }
    var date = new Date();
    var hours = "H:" + date.getHours();
    var minutes = "m:" + date.getMinutes();
    var seconds = "S:" + date.getSeconds();
    var timeString = "T:" + hours + minutes + seconds;
          
    var data = new Uint8Array(timeString.length);
    for(var i = 0; i < timeString.length; i++){
      data[i] = timeString.charCodeAt(i);
    }
    ble.writeWithoutResponse(tinywatch.id, tinywatch.uuid, tinywatch.characteristics.time.uuid, data.buffer, success, failure);
  }
};

app.initialize();
