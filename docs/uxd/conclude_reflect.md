# Conclude & Reflect


## Product Demonstration 

- To connect the device to a network you have to turn the device on and press the button down for 5 seconds. The button sits internally under face number **4**. 

![button on top face](/assets/product/components_inserted.jpeg)

- After holding the button down for 5 seconds after turning the device on a network will show up, called 'esp-captive'. Fill in the SSID and password of your internet network. and copy the device MAC address. This is the ID that is used to connect the web client to the device.
![](/assets/embedded/esp-captive.jpeg)
![](/assets/embedded/captive-page.png)
![](/assets/embedded/captive-logout.png)

- After this stage the device will store the password and SSId and wil try the use it to connect to wifi on every start up.

- Login to the page with the device ID and your name and wait until the device is connected to the MQTT broker and can respond to the web client.

- Now you can play with the device by pressing the roll button.

![type:video](/assets/product/game_example.mp4)

- The device is incased by a 3D printed casing made from TPU. This casing protects the internal components and makes the product durable and impact resistant. 
![type:video](/assets/product/3Dmodel.mp4)
![type:video](/assets/product/final_3Dmodel.mp4)
- The device can be recharged and shows a green light when charging which will turn of if the battery is 100%.
![](/assets/product/recharge.jpeg)



## Reached Requirements
> The Goal of this product is to create a interactive and immersive dice-rolling device that enhances traditional tabletop and digital gaming sessions, making it able to play with friends from a distance.
By giving the user more interaction feedback, like sound and lights, but also a web page with a nice design the iot-dice makes using dices more fun.

The main goal of this product has been reached for so far with a couple of features that could be improved. I go over all the requirements that I have drawn up and reflect on them in this section.


**REQ01**: The IoT dice shall be able to connect to a designated webpage through a secure Wi-Fi connection.

As seen before the iot-dice does connect to a Wifi network by using a captive page for the user to insert its network credentials. After the network is inserted the iot-device stores the credentials in a non-volatile storage. 
This part of the code works very well but could be improved by implementing a error handler or a input check to prevent the user from inserting a string that would fill up the non-volatile storage.

Out of the User test there also came in findings with the feedback of the captive page. the captive page would give no feedback if the network was not found or if it had a wrong password. This could be improved.
>user filled in the wrong ssid or password but did not know which one was wrong, eventually the user did copy the MAC address and logged in correctly.

<img src="../assets/embedded/captive-page.png" width="200">


**REQ02:** The IoT dice shall incorporate motion and orientation sensors to simulate realistic dice rolls.

The IoT dice does have a sensor to measure the Orientation of the device but it is not used to simulate the orientation in real-time, Thus this requirement was not met. However, the measurements of the orientation sensor is used to tell which face of the dice is thrown. 



This requirement could still be achieved because the thrown face value derives from the quaternion data that comes out of the sensor. To make this improvement quaternion data would have to be published on the MQTT broker instead of value ranging from 1 to 6. This would also mean changing a couple of functions such as the webGL dice animation.

**REQ03:** The IoT dice shall feature feedback outputs including a LED light and sound to enhance user experience.

The IoT dice does have a Blue LED and a Piezo buzzer, both these features work but great. But there is not enough stages where these features are shown. A improvement could be playing a sound or blink if the dice is turned on.  



**REQ04:** The IoT dice shall transmit data related to dice rolls, including timestamp, roll result, and ID, to a designated database hosted on a secure server.

The dice does sends its roll result and ID to a database trough the back-end from the website. This could be improved by sending more data to the database such as the battery percentage of the dice while in the session.


**REQ05:** The IoT dice is a dice that can be rolled to keep the suspense  just like a regular dice. 
This requirement has been achieved. To enhance the experience the buzzer should also make a counting down sound before the end of time to roll but I was unable to make that.

## **Device requirements**
|**Requirement ID#**|**Requirement**|**MoSCoW**|**Compliant**|
|---                |---            |---        |---         |
|EMBRQ#01|The embedded device acts as a client and sends measured sensor data to the application backend over http(s)/MQTT(tcp).|MUST|YES|
|EMBRQ#02|The embedded device also acts as a client receiver and receives status messages from the application backend over http(s) or MQTT.|MUST|YES|
|EMBRQ#03|The embedded device contains at least two types of input sensors (e.g. LDR, buttons, joystick, capacitive touch).|MUST|YES|
|EMBRQ#04|The embedded device contains at least two types of visual and/or sensory outputs (e.g. LED, LED Matrix, 7-segement display, motor, servo, actuator, LCD-screen, buzzer, etc).|MUST|YES|
|EMBRQ#05|The embedded device uses the WifiManager for configuration of SSID and password (PWD) for connecting to the network.|MUST|YES|
|EMBRQ#06|The embedded device is portable and does not require any cables while in use.|SHOULD HAVE|YES|


**EMBRQ#03**
The embedded device has two Input sensors, a button and a fuel-gauge battery sensor.
**EMBRQ#04** The Embedded device has two sensory output, an LED and a Piezo Buzzer.

Al of the embedded requirements have been achieved. However there are still a couple of features that could be improved. For example the buzzer that is used to produce sound. The sound that it creates is not loud enough in crowded places. This should have been tested more often before assembling the product.   

## Failures During Process 

### 1.
 The intended design for the product would have been a flexible printed circuit. Because the components that lay on the PCB have to face different sides of the dice I wanted to use a PCB that could flex so that all the components could be placed inside of the casing without Through holes pins or cables to connect them.
Unfortunately ordering a flex PCB would cost me way too much money with quotes that were 4 times as much as a standard PCB. So instead I redesigned my PCB design for a standard hard substrate circuit board. I took out all of the flexible parts and inserted THrough hole pins where needed to connect the components together. Eventually my design looked like this; 
![PCB design](/assets/embedded/pcb-layout-iot-dice.png)

As you can see there are a lot of through hole pins and the components are not connected. To place the components inside of the dice I had to brake the pieces of and connect them with wires. This made the time to assemble the dice longer.

Next time before designing a pcb that is intended too flex I should first look in to the cost of ordering such PCB's and do more research on the overall product cost. This would have saved me some time during the designing process. 


### 2.
I chose TPU as a filament to use and test for my product. However, it is not easy to print common failures that happen while printing with TPU are: 
- Stringing
- Oozing
- Poor Adhesion
- Under-extrusion

etc. 

I also faced These difficulties which resulted in multiple failed tries of making a casing for the product. To fix these problems, parameters in the slicer should be adjusted and optimized for TPU, which I did. I printed and adjusted the parameters until finally I had a great print. 
![](/assets/product/print_attemps.jpeg)
This took a long time an could have taken less if I used a test or calibration model, for stringing for example to adjust the settings. These models take less than a hour to print against the 15 hours of printing for every product casing that I tried to make.

![stringing calibration model](data:image/jpeg;base64,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)



