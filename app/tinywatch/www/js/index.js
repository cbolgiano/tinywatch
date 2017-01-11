;(function(){
  const defaultTime = 1500;
  let tinywatch = null;

  function initialize(){
    if(tinywatch){
      showMessage('Connected to tinywatch.', '', 'event received');
      sendTime();
    } else{
      findTinywatch();
    }
  }

  function reinitialize(){
    tinywatch = null;
    initialize();
  }

  function onClose(){
    evothings.ble.stopScan();
    if(tinywatch){
      evothings.ble.close(tinywatch);
    }
    navigator.app.exitApp();
  }

  /**
   * Find tinywatch device.
   */
  function findTinywatch(){
    if(!tinywatch){
      showMessage('Finding tinywatch...', 'blink', 'event listening');
      evothings.ble.startScan(
      ['CCC0'],
        function(device){
          showMessage("Found tinywatch!", '', 'event received');
          evothings.ble.stopScan();
          setTimeout(function(){connectToTinywatch(device);}, defaultTime);
        },
        function(error){
          reinitialize();
        }
      );
    }
  }

  /**
   * Connect to tinywatch device.
   * @param {Object} device device to connect to.
   */
  function connectToTinywatch(device){
    setTimeout(showMessage('Connecting to tinywatch...', 'blink', 'event received'), defaultTime);
      evothings.ble.connectToDevice(device,
      function(device){
        showMessage('Connected to tinywatch.', '', 'event received');
        tinywatch = device;
      },
      function(device){
        reinitialize();
      },
      function(error){
        reinitialize();
      }
    );
  }

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

  function sendTime(){
    if(tinywatch){
      var service = evothings.ble.getService(tinywatch, "CCC0");
      var characteristic = evothings.ble.getCharacteristic(service, "CCC2");
      evothings.ble.writeCharacterisitic(
        tinywatch
      , characteristic
      , (new Date()).getTime()
      , null
      , null);
    }
  }

  document.addEventListener('deviceready', initialize, false);
  document.addEventListener('backButton', onClose, false);
})();
