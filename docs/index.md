![poster](./assets/frontpage_dice.jpg)


# Intro
This project is a remake of an previous IoT-project that I have build in 2022. In that time I was not able to complete the whole project in time, thats why I had to resit this project. In this page I will explain what the goal is of my IoT-device and from where I started. The first IoT-project "Cubice" that I made was pretty much done but I did not document my progress.

In the meantime I gained more knowledge and expertism in the field of Iot & embedded systems as a HBO-ICT TI student. The new things that I have learned made me able to reflect on my previous IoT-project and see some aspect of the project that I want to improve. To improve as a IoT specialist and apply the things that I have learned.

The changes like design, requirements, choice of electrical components, architecture and research on new findings will further be explained in this logbook. But first the goal of this project.

# Cubice
To start it out the assignment for the IoT minor is to create a small IoT-device that that is innovative and connects to a webserver, database & api. A couple of blueprints where handed out to give a example. I choose to create a wireless multi-dice that can be used with a web application. This makes playing with a dice much more fun because there are more possibilities. 

In addition, the Cubice is larger than a normal die, which means there is a different way of rolling. What makes rolling a dice fun is the game of chance and of course hoping for a high number. The Cubice makes using a dice even more exciting.

# Link Tree
The documentation of this whole project is divided in pages. To have easy access this following link tree can help that describes each page link.
- **Documentation on previous project**
- **Documentation on project requirements**
- **Embedded device**
- **Web page**


# User Manual 
## Instructions 
1. first thing that you have to do is connect the dice device to wifi. You do this by connecting the wemos mcu to a computer that has arduino installed. in the source code you then have to change the SSID and password.

2. test if the wifi is set by running the code. if the wifi is set unplug the dice device from th ecomputer and connect the power supply. The dice will automaticaly connect back with the wifi when its on power.

3. no to roll the dice go to the webpage http://localhost/ 

4. to test if the webpage is connected to the database roll the dice once. if the dice is turned on and you clicked on roll dice you should see th enumber of dice that is trown.
if this dont work and you get the error
open the webapplication
2. when on the web p