
/**
 * Manages MQTT client setup, message handling, and communication for IoT devices.
 *
 * Establishes MQTT connection, subscribes to topics, and handles incoming messages.
 * Includes functions to publish messages to specific topics and handle responses.
 *
 * @link   https://yiidaatiihee30-iot-herkansers-ac4e5948a38373b988920532de73bdfe8.dev.hihva.nl/
 * @file   This file defines the MQTT client setup and message handling logic.
 * @author TheironneVelliam.
 * 
 */
import { anim,rotateToFace, startRotation} from './renderThree.js'

export let batteryPercentage ='';


const brokerUrl = 'ws://localhost:9001';
const client = mqtt.connect(brokerUrl, {
  username: 'iot-web',
  password: '7YKyE8R2AhKzswfN',
  keepalive: 60,
  reconnectPeriod: 5000,
  clean: true,
});


// Function to handle MQTT setup and message handling
export function setupMqttClient(session_id) {
  const brokerUrl = 'ws://localhost:9001';
  const client = mqtt.connect(brokerUrl, {
    username: 'iot-web',
    password: '7YKyE8R2AhKzswfN',
    keepalive: 60,  // Keepalive period in seconds
    reconnectPeriod: 5000, // Reconnect period in milliseconds
    clean: true, // Set to false if you need to persist subscriptions and messages
    });
  

  // Define topics based on session_id
  const topics = {
    world: `cubice/${session_id}/web/world`,
    rolled: `cubice/${session_id}/web/rolled`,
    battery: `cubice/${session_id}/web/battery`
  };

  client.on('connect', function () {
    console.log('Connected to broker');

    // Subscribe to all topics
    client.subscribe([topics.rolled, topics.world, topics.battery], function (err) {
      if (!err) {
        console.log(`Subscribed to topics: ${Object.values(topics).join(", ")}`);
      } else {
        console.error('Subscription error:', err);
        client.end();
      }
    });
  });

  client.on('message', function (topic, message) {
    if (topic === topics.world) {
      handleWorldMessage(message.toString());
    } else if (topic === topics.rolled) {
      handleRolledMessage(message.toString());
    } else if (topic === topics.battery) {
      handleBatteryMessage(message.toString());
    }
  });

  client.on('error', function (err) {
    console.error('Connection error:', err);
    client.end();
  });

  client.on('close', function () {
    console.log('Connection closed');
  });
}

// Function to handle messages for each topic
function handleRolledMessage(message) {
  console.log('Rolled message received:', message);
  rotateToFace(message);
  const date = Date.UTC();
  const formData = new FormData(this);
formData.append('rolled_number', message);
formData.append('date_time', date);
  // send message immediately to db
    fetch("./php/roll.php", {
        method: "POST",
        body: formData,
    })
    .then(response => {
        if (!response.ok) {
            throw new Error("Network response was not ok");
        }
        return response.text();
    })
    .then(data => {
        
        console.log(data); // Response from PHP script
    })
    .catch(error => {
        console.error("There was a problem with the fetch operation:", error);
    });
}

function handleWorldMessage(message) {
  console.log('World message received:', message);
 // Create a custom event with the message as detail
 const event = new CustomEvent('worldMessageReceived', { detail: { message } });
 document.dispatchEvent(event);
  
}

export function handleBatteryMessage(message) {
  console.log('Battery message received:', message);
  batteryPercentage = String(message);
  
}

// Functions to publish messages on specific topics
export function publishRoll(session_id, message) {
  publishMessage(`cubice/${session_id}/dice/roll`, message);
  startRotation();
}

export function publishAreYouThere(session_id, message) {
  publishMessage(`cubice/${session_id}/dice/areyouthere`, message);
  
}

export function publishBattery(session_id, message) {
  publishMessage(`cubice/${session_id}/dice/battery`, message);
}

// General publish function
// General publish function using shared client
function publishMessage(topic, message) {
    if (client.connected) {
      client.publish(topic, message, () => {
        console.log(`Message published to ${topic}`);
      });
    } else {
      console.log('Client is not connected. Message not sent.');
    }
  }

