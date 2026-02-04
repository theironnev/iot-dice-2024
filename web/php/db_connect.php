<?php
/**
 * This script provides functions to open and close a database connection using MySQLi.
 * The OpenCon function establishes a connection to the specified database,
 * and the CloseCon function closes the given database connection.
 * 
 * Author: Theironne Velliam
 * Date: 2024-04-23
 */

/**
 * OpenCon function
 * 
 * Establishes a connection to the MySQL database using the provided
 * server, user, password, and database name. If the connection fails,
 * it terminates the script and displays an error message.
 * 
 * @return mysqli The database connection object
 */
function OpenCon()
{
// Basic connection settings
$dbServer = 'localhost';
$dbUser = 'root';
$dbPassword = '7YKyE8R2AhKzswfN';
$dbName = 'iot-dice';
$conn = new mysqli($dbServer, $dbUser, $dbPassword,$dbName) or die("Connect failed: %s\n". $conn -> error);
return $conn;
}
/**
 * CloseCon function
 * 
 * Closes the given database connection.
 * 
 * @param mysqli $conn The database connection object to close
 */
function CloseCon($conn)
{
$conn -> close();
}
