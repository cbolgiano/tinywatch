;(function(){
  const defaultTime = 1500;

  function initialize(){
    findTinywatch();
  }

  /**
   * Find tinywatch device.
   */
  function findTinywatch(){
    showMessage('Finding tinywatch...', 'blink', 'event listening');
    evothings.ble.startScan(
      ['CCC0'],
      function(device){
        showMessage("Found tinywatch!", '', 'event received');
        evothings.ble.stopScan();
        setTimeout(function(){connectToTinywatch(device);}, defaultTime);
      },
      function(error){
        findTinywatch();
      }
    );
  }

  /**
   * Connect to tinywatch device.
   * @param {Object} device device to connect to.
   */
  function connectToTinywatch(device){
    showMessage('Connecting to tinywatch...', 'blink', 'event received');
    setTimeout(function(){
      evothings.ble.connectToDevice(device,
      function(device){
        showMessage('Connected to tinywatch.', '', 'event received');
        //TODO: Do something when connected.
      },
      function(device){
        findTinywatch();
      },
      function(error){
        findTinywatch();
      }
    );}, defaultTime);
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

  document.addEventListener('deviceready', initialize, false);
})();
