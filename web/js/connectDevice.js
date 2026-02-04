
/**
 * Validates and submits a form to connect a device with a player.
 *
 * Checks form inputs for valid MAC address format and ensures fields are not empty or too long.
 * Submits form data via a POST request to a PHP script if validation passes.
 * Redirects to the main page upon successful submission.
 *
 * @link   https://yiidaatiihee30-iot-herkansers-ac4e5948a38373b988920532de73bdfe8.dev.hihva.nl/
 * @file   This file defines the form validation and submission logic.
 * @author TheironneVelliam.
 * 
 */


function checkForm(){
    let device = document.getElementById("device_id").value;
    let player = document.getElementById("player_name").value;

     // Regex expression to check if the input is a MAC adress
    const macAddressRegex = new RegExp(/^([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})|([0-9a-fA-F]{4}.[0-9a-fA-F]{4}.[0-9a-fA-F]{4})$/);

    let isValid = true;

    if (device == "" || player == "") {
        alert("Ensure you input a value in both fields!");
        isValid = false;
    } else if (device.length > 17 || player.length > 17) {
        alert("Ensure device ID and player name are not longer than 17 characters!");
        isValid = false;
    } else if (!macAddressRegex.test(device)) {
        alert("Device ID should be a valid MAC address in the format xx:xx:xx:xx:xx:xx.");
        isValid = false;
    }
    if (isValid) {
        // Perform submission
        console.log("Form submission is valid. Proceeding...");
    } else {
        console.log("Form submission is not valid.");
    }
    return isValid;
}


function submitForm(e){
    e.preventDefault(); // prevent default handling

    var connectForm =    document.getElementById("connectForm");

    let device = document.getElementById("device_id").value;
    let player = document.getElementById("player_name").value;
    const formData = new FormData(this);
    formData.append('player_name', player);
    formData.append('device_id', device);

    if(checkForm()){
        fetch("./php/form.php", {
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
            window.location.href = 'main.html';
        })
        .catch(error => {
            console.error("There was a problem with the fetch operation:", error);
        });
    }
   
}

var connectForm = document.getElementById("connectForm");

connectForm.addEventListener("submit", submitForm);


