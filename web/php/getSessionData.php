<?php
/**
 * This script returns session variables as a JSON response.
 * It starts the session, sets the content type to JSON, and checks
 * if the session variables 'device_id' and 'player_name' are set.
 * If set, it returns them as a JSON object; otherwise, it returns an error message.
 * 
 * Author: Theironne Velliam
 * Date: 2024-04-23
 */

session_start(); // Start the session

header('Content-Type: application/json'); // Set header so the output is treated as JSON

// Check if the session variables are set and send them back as JSON
if (isset($_SESSION['device_id']) && isset($_SESSION['player_name'])) {
    echo json_encode(['device_id' => $_SESSION['device_id'], 'player_name' => $_SESSION['player_name']]);
} else {
    echo json_encode(['error' => 'Device ID or Player Name not found in session.']);
}
?>