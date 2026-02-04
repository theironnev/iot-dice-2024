# Intro
 
In the previous version of IoT Cubice project I made some documentation. This page is a resume to describe the background of this project.
# starting proces version 1
The assignment for this blueprint was to create an IoT device that communicates with a web server. Additionally, the device must utilize sensors/actuators and a database to store the rolled dice.

Before I begin creating a physical prototype, I will first conduct research, which is the blueprint phase. During this phase, I research my chosen project, such as the target audience, competition analysis, and blueprint learnings. Additionally, I formulate a research question to further delve into one of the aspects of my prototype for improvement. The profile I have chosen is hardware interface. My goal is to apply an improvement to my prototype in the hardware aspect after the blueprint phase.

The findings I have discovered during the blueprint phase are documented in my Academic Poster.

![CUBICE Poster](assets/poster-iot.jpg)


# Embedded

## Component Research

First, I began by searching for possible ways to create a dice device that utilizes sensors to transmit the thrown face to a web server. For this purpose, I first examined the usable sensors I received in the UNO RS3 starter Kit. The reason for this is to keep the costs of the prototype as low as possible.

In the Kit, there were two sensors that seemed like possible candidates:

- Ball switch (tilt sensor)
- Photoresistor ([click here for example](https://en.wikipedia.org/wiki/Photoresistor))

<img src="https://www.tinytronics.nl/shop/image/cache/data/product-546/hxd2801-1200x1200h.jpg" alt="Ball Switch" width="200">


The ball switch is a mechanical sensor that gives a HIGH when it's upright and LOW when it's rotated more than 90 degrees compared to the horizon. This is because there is an aluminum ball in the sensor that reduces the output resistance when it touches the underside.

So, one such sensor can only detect whether it's upright or not. Hence, for a dice, I would need 6 of them to detect all 6 faces. In my Kit, I only have 2 of these sensors. To obtain more of these sensors, I searched around for fellow students who didn't mind lending sensors from their kit.

Disadvantages of Ball switch sensor:

- Can only give output for upright or not
- Mechanical ball inside can get stuck at a degree


The other sensor from my Kit that I tested is the Photo-resistor. This is a resistor that changes resistance when exposed to more or less light on the sensor. The way I wanted to apply these sensors is by placing them in the 6 faces of the dice. The face of the dice pointing upwards would then be determined by the output of the reflecting face lying on the ground. This face doesn't absorb daylight, so it would give a different output than the rest of the faces.

Of course, there is one drawback to this method of detection, and that is the influence of external factors being too influential. This would mean that in an overly bright room, the dice wouldn't work properly.

In addition to the sensors I received in my kit, I also researched other methods to determine the thrown face.
Sensors such as:
- Touch sensor ([link to example](https://www.digikey.nl/nl/products/detail/dfrobot/SEN0296/10136557?utm_adgroup=&utm_source=google&utm_medium=cpc&utm_campaign=PMax%20Shopping_Product_Medium%20Volume%20Products&utm_term=&productid=10136557))
- Distance sensor
- Gyroscoop ([link to example](https://randomnerdtutorials.com/arduino-mpu-6050-accelerometer-gyroscope/))

From these 3 other methods, further research excluded all but the gyroscope as a better option than the ball switches.

A gyroscope measures the rotation of an object. This can be used to determine how the dice has rotated. A usable sensor for this project could be the [MPU-6050](https://www.tinytronics.nl/shop/index.php?route=product/search&search=mpu%206050) . This is a 3.3/5v module that is well supported for Arduino projects.

The only downside is that this product is not included in my kit, which also increases production costs. Therefore, at the start of building my prototype, I chose to go for the ball switch sensor.

<img src="https://www.tinytronics.nl/shop/image/cache/data/product-100/MPU-6050%202-1200x1200w.jpg" alt="mpu" width="200">

#### Battery shield
To make the Cubice portable I want It to be powered wireless. This meant that I had to add a battery to my device. This can be tricky for multiple reasons like:

- **Power Consumption:** IoT devices often have varying power requirements depending on their operation mode (e.g., active vs. sleep). Optimizing power consumption to prolong battery life while ensuring device functionality is crucial.

- **Battery Lifetime:** Selecting the right battery type and capacity is essential to ensure the desired lifespan of the IoT device between battery replacements or recharges.

- **Voltage Regulation:** Maintaining stable voltage levels throughout the battery discharge cycle is crucial for the proper operation of the IoT device. Voltage regulation circuits may be required to ensure consistent performance.

- **Form Factor:** IoT devices often have compact form factors, requiring small and lightweight battery solutions that fit within the device's constraints without sacrificing performance.

- **Charging Circuitry:** Implementing reliable charging circuitry for rechargeable batteries is essential. Overcharging or improper charging can lead to reduced battery life, safety hazards, or even damage to the device.

An example is that a light weight and rechargeable lithium battery would be the best option for this project but they are fragile and a risk on catching on fire if not treated right. Like throwing it as a dice. An other reason is that the WEMOS D1 mini need a stable voltage supply of 3.3 volts. A lithium battery has a nominal voltage of 3.7 so there has to be a voltage regulation in between.
Luckily by doing a little research I found a WEMOS battery shield that handles this problem. documentation of this product can be found over [here!](https://www.wemos.cc/en/latest/d1_mini_shield/battery.html)

For the risk of damaging the battery I should consider project requirements so that the dice does not have to be a throwable device. Or maybe add some protection. 

<img src="./assets/battery_shield.jpg" alt="wemos battery shield" width="200">



## Cubice LIbrary

I made a Cubice class too oversee all the functions that I use for the dice project and to make it reusable.


```c++
#ifndef MyCubice_h
#define MyCubice_h
#include "Arduino.h" 

#define SIDE_SENS_6  D0
#define SIDE_SENS_5  D5
#define SIDE_SENS_4  D7
#define SIDE_SENS_3  D8
#define SIDE_SENS_2  D3
#define SIDE_SENS_1  D4  // can not use D4 when Uploading code

class MyCubice{
	public: 
		MyCubice();
		void rolled();

		// if param is 5 every side gets shuffled but side 6
		// if param is 6 every side gets shuffled 
 		// the lower the param the les sides that get shuffled
		void shuffleDices(int shuffled_sides);
		void calc_thrownDice();
	
		int getDice();
		int get_secondDice();
		int get_thirdDice();
		int*get_diceArray();
		int*get_second_diceArray();
		int*get_third_diceArray();
		void rstRolled();

		int gen_diceNR();
		int gen_2_diceNR ();
		int gen_3_diceNR ();
	private:
  
	int _thrownDice;
    int _thrown_secondDice;
    int _thrown_thirdDice;
    int _dice [6]= {1,2,3,4,5,6};
    int _second_dice [6]= {1,2,3,4,5,6};
    int _third_dice [6]= {1,2,3,4,5,6};
};

	
#endif
```

## Device Conection to Web 

### With http get request
I made two functions to interact with the webserver. One is to send data sndData() and the other to get data getData().
when the sendData() is called the Cubice will send the value of face that stand-up, straight to webserver trough a php post request.
when getData() is called it returns the input state that the webserver regulates. 
There are 5 inputs on the webserver so getData() returns a String from 0 to 5. 
```c++
void sndData(){
    HTTPClient http; 
    String url1,url2,url3,linkGet;
    url1 = "/insert_db.php/?D1="+String(Cubice.gen_diceNR())+"&D2=null&D3=null";
    url2 = "/insert_db.php/?D1="+String(Cubice.gen_diceNR())+"&D2="+String(Cubice.gen_diceNR())+"&D3=null";
    url3 = "/insert_db.php/?D1="+String(Cubice.gen_diceNR())+"&D2="+String(Cubice.gen_diceNR())+"&D3="+String(Cubice.gen_diceNR());// add de dices here 
    if(*amountDice == 1){linkGet = host + url1;}
    if(*amountDice == 2){linkGet = host + url2;}
    if(*amountDice == 3){linkGet = host + url3;}

    Serial.println(linkGet);
    
    
    http.begin(client, linkGet);
    int httpCode = http.GET();
    String payload = http.getString(); 
     
    Serial.println("http code response: ");
    Serial.print(httpCode);
    Serial.println(payload);
    Serial.println("----------------Closing Send Data----------------");
    http.end(); //--> Close connection
    }
    
    String getData(){
    HTTPClient httpClient; //> declared httpClient object
    String getPage, getURL, getData;
    
    // url string to get data from site
     getPage = "/GetState.php";
     getURL = host + getPage; // the URL where i get my data from
     getData = "ID=0";

    Serial.println(getURL);
    httpClient.begin(client, getURL);
    httpClient.addHeader("Content-Type", "application/x-www-form-urlencoded"); 
    int httpCodeGet = httpClient.POST(getData);
    String payloadGet = httpClient.getString();
    Serial.print("Response Code : "); //--> If Response Code = 200 means Successful connection, if -1 means connection failed. For more information see here : https://en.wikipedia.org/wiki/List_of_HTTP_status_codes
    Serial.println(httpCodeGet); //--> Print HTTP return code
    
    Serial.println("payload: "+payloadGet);
    Serial.println("----------------Closing Get Data----------------");
    httpClient.end(); //--> Close connection
    return payloadGet;
  
  }
```

In the setup() function i setup my wifi and the pins for the ball switch sensors.
In the loop() function i handle the input values.
```c++
void loop() {
    String input= getData();
    delay(2000);
    Serial.print(input);
    if(input == "1"){
         digitalWrite(ON_Board_LED, HIGH); //--> Turn off Led
        if(*pmsgState== 0){
           sndData();
          *pmsgState = 1;
        }else{
          Serial.print("data snd to db");
          }
    }
    else if(input == "2"){
        if(*pmsgState== 0){
          *amountDice = 1;
        }else{
          Serial.print("sndData sened 1 dice now");
          }
    }
    else if(input == "3"){
              if(*pmsgState== 0){
          *amountDice = 2;
        }else{
          Serial.print("sndData sened 2 dice now");
          }
    }
    else if(input == "4"){
      if(*pmsgState== 0){
          *amountDice = 3;
        }else{
          Serial.print("sndData sened 3 dice now");
          }
    }
    else if(input == "5"){
      if(*pmsgState== 0){
          Cubice.shuffleDices(6);
        }else{
          Serial.print("dices shuffled");
          }
    }
    
    else{
      digitalWrite(ON_Board_LED, LOW); //--> Turn onn Led
        if(*pmsgState== 0){
          Serial.print("wacht op input!");
        }else{
          Serial.print("window closed!!");
          *pmsgState = 0;
        }
      }

  delay(500); //--> GET Data at every 5 seconds
  }
```
### Update with MQTT
On further research I gained more knowledge on deferent messaging protocols. One of the messaging protocols that I found is MQTT. MQTT is designed for efficient communication between devices, including those connected over wireless networks. It operates at the application layer of the OSI (Open Systems Interconnection) model, providing a lightweight and publish/subscribe messaging transport suitable for IoT (Internet of Things) and M2M (Machine-to-Machine) communication scenarios. 

A couple of advantageous on  why I want to use MQTT for this project: 

- **Asynchronous Communication:** MQTT allows for asynchronous communication, meaning the client (IoT device) doesn't need to wait for a response from the server (webpage) after sending a message. This can be crucial for IoT applications where real-time or near real-time data transmission is required.

- **Reduced Overhead:** MQTT typically has lower overhead compared to traditional HTTP requests. With MQTT, the overhead of headers and connection setup is minimized, making it more efficient for small, frequent data transmissions common in IoT scenarios.

- **Pub/Sub Architecture:** MQTT operates on a publish/subscribe messaging pattern. This allows for a one-to-many communication model where multiple clients (subscribers) can receive messages from a single publisher (IoT device) without the need for individual connections. This scalability is beneficial for IoT deployments with multiple devices and consumers.

- **Reliability:** MQTT supports Quality of Service (QoS) levels, allowing for different levels of reliability in message delivery. This ensures that messages are delivered reliably, even in challenging network conditions or when devices are intermittently connected.

- **Low Bandwidth and Power Consumption:** MQTT's lightweight protocol and efficient message transmission make it suitable for IoT devices with limited bandwidth and power resources. This can prolong the battery life of battery-operated devices and reduce data costs in cellular IoT deployments.

- **Security:** MQTT supports authentication and encryption mechanisms to secure communications between clients and brokers. Additionally, MQTT brokers can be configured to restrict access based on client credentials, enhancing the security of IoT deployments.

I don't think I can apply all of these advantageous of using MQTT in my project but it is a good standpoint on why I should choose for MQTT.

#### Updated code

```c++
// Check for Message received on define topic for MQTT Broker
void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
// handles the incoming messages on topic webapp, if msg is "R" it means throw button is clicked on webapp,
// if msg is "s" then the shuffle button is clicked

  switch ((char)payload[0]) {
  case 'R':
    //web app button is preese, give back dice faces
    Cubice.rolled();
 
    // send the rolled faces in a char array, 3 rolled dices means "..." chars
    
    msgValue =100* Cubice.getDice()+ 10*Cubice.get_secondDice()+ Cubice.get_thirdDice();
    char buffer [8];
     itoa(msgValue,buffer, 10);
    //snprintf (msg, MSG_BUFFER_SIZE,"");
    client.publish("dice/dice", buffer);
    Serial.println(buffer);
    break;
  case 'S':
    //shuffle faces of dice 1, 2 and 3
    Cubice.shuffleDices(6);
    break;
    
    //not yet used
   case 'N':
    //reset dices values on same faces
    Cubice.rstShuffled();
    break;
  default:
    // if nothing else matches, do the default
    // default is optional
    break;
  }
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(),mqtt_un ,mqtt_pw)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("dice/webapp", "hello world");
      // ... and resubscribe
      client.subscribe("dice/webapp");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

```
### MQTT Broker
The broker that I'm using is a Mosquitto MQTT installed broker that is running on a Raspberry Pi 4.
![Raspberry Pi4](./assets/rp4.jpeg)


## Wiring Diagram
The hardware wiring is shown below in a schematic image. The green switch sensors in this schematic drawing are the ball switch sensors. To test them, they are all oriented differently on the breadboard.

![wirediagram](./assets/wireDiagram.png)
## BOM
# Web Application
# Architecture 
# Assets

