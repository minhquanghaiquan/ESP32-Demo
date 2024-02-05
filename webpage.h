#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <Arduino.h>

const char webpage[] PROGMEM = R"=====(
  <!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>WiFi Configuration</title>
  <style>
    body {
      font-family: Arial, sans-serif;
      text-align: center;
      margin: 20px;
    }
    input {
      padding: 10px;
      margin: 5px;
    }
    button {
      padding: 10px;
      margin-top: 10px;
    }
  </style>
  <script src="https://cdn.jsdelivr.net/npm/axios/dist/axios.min.js"></script>
</head>
<body>
  <h2>WiFi Configuration</h2>
  <form id="wifiForm">
    <label for="ssid">WiFi SSID:</label>
    <input type="text" id="ssid" name="ssid" required>
    <br>
    <label for="password">WiFi Password:</label>
    <input type="password" id="password" name="password" required>
    <br>
    <button type="button" onclick="submitForm()">Submit</button>
  </form>
  <script>
    function submitForm() {
      var ssid = document.getElementById('ssid').value;
      var password = document.getElementById('password').value;
      console.log('Data sent:', { ssid: ssid, password: password });
      // Use Axios to send a POST request to /submit endpoint
      axios.post('/submit', { ssid: ssid, password: password })
        .then(function (response) {
          console.log('Response:', response.data);
          alert("WiFi configuration submitted successfully!");
        })
        .catch(function (error) {
          console.error('Error:', error);
        });
    }
  </script>
</body>
</html>
)=====";

#endif