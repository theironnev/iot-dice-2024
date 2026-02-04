<?php
/**
 * This script handles the insertion of device sessions and participants into the database.
 * It includes functions to insert a device ID into the device_session table, 
 * insert a participant into the session_participants table, and check for existing device IDs.
 * The main function orchestrates the process and redirects to the main page upon successful insertion.
 * 
 * Author: Theironne Velliam
 * Date: 2024-04-23
 */

session_start();
include "db_connect.php";


// Function to insert device_id into devices table if not already present
function insertDevice($device_id, $conn) {
    $query = "INSERT INTO `device_session`(`device_id`) VALUES ('$device_id')";
    $result = mysqli_query($conn, $query);
    if (!$result) {
        // Handle error
        echo "Error: " . mysqli_error($conn);
    }
}

// Function to insert device_id into participants table
function insertParticipant($device_id, $player_name, $conn) {
    $query = "INSERT INTO session_participants (player_name, device_id) VALUES ('$player_name', '$device_id')";
    $result = mysqli_query($conn, $query);
    if (!$result) {
        // Handle error
        echo "Error: " . mysqli_error($conn);
    }

    return $result; // Return true if insertion was successful, false otherwise
}

// Function to check if device_id already exists in devices table
function isDeviceExists($device_id, $conn) {
    $query = "SELECT * FROM `device_session` WHERE device_id = '$device_id'";
    $result = mysqli_query($conn, $query);
    return mysqli_num_rows($result) > 0;
}

// Main function to handle insertion
function handleInsertion($device_id,$player_name, $conn) {
    if (!isDeviceExists($device_id, $conn)) {
        // Insert device_id into devices table
        insertDevice($device_id, $conn);
    }
    
    // Insert device_id into participants table
    $participantInserted = insertParticipant($device_id, $player_name, $conn);

    // Redirect to play.html if both device exists and participant inserted successfully
    if (isDeviceExists($device_id, $conn) && $participantInserted) {
        header("Location: ../main.html");
        exit; // Ensure script stops executing after redirection
    }
}



// Handle form submission 
if ($_SERVER["REQUEST_METHOD"] === "POST"){
    
    // Get form data
    $player_name = $_POST["player_name"];
    $device_id = $_POST["device_id"];

    // Set the device_id as a session variable
    $_SESSION['player_name'] = $player_name;
    $_SESSION['device_id'] = $device_id;

    $conn = OpenCon(); //Open db connection

    handleInsertion($device_id,$player_name, $conn);//Sends device session to database

    CloseCon($conn); //Close db connection

}

