<?php
/**
 * This script handles the insertion of dice roll data into the database.
 * It includes functions to insert a roll, check for existing devices, 
 * retrieve the last inserted row, and orchestrate the process based on form submissions.
 * The result is output as a JSON response.
 * 
 * Author: Theironne Velliam
 * Date: 2024-03-20
 */

// Start the session 
session_start();
include "db_connect.php";


$device_id =$_SESSION['device_id'];
$player_name = $_SESSION['player_name'];

/**
 * insertRoll function
 * 
 * Inserts a rolled number into the dice_rolls table along with the player name and device ID.
 * 
 * @param int $rolled_number The rolled number to insert
 * @param string $device_id The device ID
 * @param string $player_name The player name
 * @param mysqli $conn The database connection object
 */
function insertRoll($rolled_number,$device_id,$player_name, $conn) {
    $query = "INSERT INTO `dice_rolls`( `player_name`, `rolled_number`,`device_id`) VALUES ('$player_name','$rolled_number','$device_id')";
    
    $result = mysqli_query($conn, $query);
    if (!$result) {
        // Handle error
        echo "Error: " . mysqli_error($conn);
    }
}



/**
 * isDeviceExists function
 * 
 * Checks if the given device ID already exists in the device_session table.
 * 
 * @param string $device_id The device ID to check
 * @param mysqli $conn The database connection object
 * @return bool True if the device ID exists, false otherwise
 */

function isDeviceExists($device_id, $conn) {
    $query = "SELECT * FROM `device_session` WHERE device_id = '$device_id'";
    $result = mysqli_query($conn, $query);
    return mysqli_num_rows($result) > 0;
}

/**
 * getLastInsertedRow function
 * 
 * Retrieves the last inserted row from the dice_rolls table.
 * 
 * @param mysqli $conn The database connection object
 * @return array The last inserted row as an associative array
 */
function getLastInsertedRow($conn) {
    $query = "SELECT * FROM `dice_rolls` ORDER BY id DESC LIMIT 1";
    $result = mysqli_query($conn, $query);
    return mysqli_fetch_assoc($result);
}

/**
 * handleInsertion function
 * 
 * Main function to handle the insertion of dice roll data.
 * It checks if the device exists, inserts the roll, and retrieves the last inserted row.
 * 
 * @param int $rolled_number The rolled number to insert
 * @param string $device_id The device ID
 * @param string $player_name The player name
 * @param mysqli $conn The database connection object
 * @return array The last inserted row as an associative array
 */
function handleInsertion($rolled_number,$device_id,$player_name, $conn) {

    if (isDeviceExists($device_id, $conn)) {
        // Insert device_id into devices table
        insertRoll($rolled_number,$device_id,$player_name, $conn);
        return getLastInsertedRow($conn);

    }

}



// Handle form submission
if ($_SERVER["REQUEST_METHOD"] === "POST") {
    
    // Get form data
    $rolled_number = $_POST["rolled_number"];


    $conn = OpenCon(); //Open db connection

    $lastInsertedRow = handleInsertion($rolled_number,$device_id,$player_name, $conn);

    // Output the last inserted row as JSON
    echo json_encode($lastInsertedRow);
    echo json_encode(['lastInsertedRow' => $lastInsertedRow]);

    CloseCon($conn); //Close db connection

}


