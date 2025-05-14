setInterval(function() {
  fetch('http://192.168.0.7/status') // replace with your ESP32s home wifi IP address, its different for each wifi thing
    .then(response => response.text())
    .then(data => {
      if (data === '1') {
        chrome.tabs.create({ url: 'http://google.com/' });
      } else if (data === '2') {
        chrome.tabs.create({ url: 'https://chatgpt.com' });
      }
    })
    .catch(error => console.log('Error:', error));
}, 500);
