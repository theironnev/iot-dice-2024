/**
 * Handles front-end functionality for a web application interacting with a back-end server and an IoT MQTT client.
 *
 * Fetches session data, sets up MQTT client, and manages UI updates for device connectivity and status.
 * Includes event listeners for page load and button click to fetch and display session data.
 * Regularly checks device connectivity and requests battery status.
 *
 * @link https://yiidaatiihee30-iot-herkansers-ac4e5948a38373b988920532de73bdfe8.dev.hihva.nl/
 * @file This file defines the main front-end logic.
 * @author TheironneVelliam.
 * 
 */

import { anim} from './renderThree.js'
import {setupMqttClient,publishAreYouThere,publishRoll,publishBattery,batteryPercentage} from './iot-mqtt.js'

let session_id;
let session_player;




document.addEventListener("DOMContentLoaded", function() {
  fetch('./php/getSessionData.php')
  .then(response => response.json())
  .then(data => {
    if (data.device_id) {
      console.log("Device ID from session:", data.device_id);
      console.log("user from session:", data.player_name);
      session_id = data.device_id;
      session_player = data.player_name;
      setupMqttClient(String(session_id));
      anim();
      
    } else {
      console.error("Error:", data.error);
    }
  })
  .catch(error => console.error('Fetch error:', error));
});




document.addEventListener('DOMContentLoaded', function () {
  const button = document.getElementById('spin');
  button.addEventListener('click', function () {
    //insert last throw before publishing next one
    fetchLastInsertedRow();
    publishRoll(session_id, 'Rolling Loud!')
  });
});

function fetchLastInsertedRow() {
    fetch('./php/roll.php')
    .then(response => response.json())
    .then(data => {
        console.log(data.lastInsertedRow.player_name);
        // Here, data contains the last inserted row from the PHP file
        displayLastInsertedRow(data.lastInsertedRow);
    })
    .catch(error => {
        // Handle any errors that occur during the fetch request
        console.error('Error:', error);
    });
}

function displayLastInsertedRow(rowData) {
    const data = JSON.parse(rowData);
    const playerName = data.player_name;
    const rolledNumber = data.rolled_number;
    const throwTime = data.throw_time;

    document.getElementById('player').innerHTML= 'player: '+`${playerName}`;
    document.getElementById('rolled').innerHTML= 'rolled: '+`${rolledNumber}`;
    document.getElementById('time').innerHTML= 'time: '+`${throwTime}`;
    const container = document.getElementById('dataContainer');
    const playerNameElement = document.createElement('p');
    playerNameElement.textContent = `Player Name: ${playerName}`;
    const rolledNumberElement = document.createElement('p');
    rolledNumberElement.textContent = `Rolled Number: ${rolledNumber}`;
    const throwTimeElement = document.createElement('p').innerHTML;
    // throwTimeElement.textContent = `Throw Time: ${throwTime}`;

    container.appendChild(playerNameElement);
    container.appendChild(rolledNumberElement);
    container.appendChild(throwTimeElement);
}
let messageReceived = false;
let count = 0;

document.addEventListener('worldMessageReceived', function(event) {
    console.log('Received in main.js:', event.detail.message);
    messageReceived = true;
  });
  
function areYouThereInterval() { //This funtion looks if the device is still connected and asks the battery level
if (messageReceived) {
    console.log('Message was received, resetting counter.');
    messageReceived = false;
    count = 0;

} else {
    count++;
    console.log(`No message received yet. Attempt ${count}`);
}if (count >= 2) {
    endRotation();
    clearInterval(intervalId);
    console.log('Interval cleared');
}else{
    publishAreYouThere(session_id, 'hallo');
    publishBattery(session_id, 'here i ask the battery status')
    document.getElementById('batteryStatus').innerHTML= 'Battery: '+`${batteryPercentage}`+'%';
}
}
  

const intervalId = setInterval( areYouThereInterval, 5000);

