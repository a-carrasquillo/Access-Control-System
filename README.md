# Access-Control-System
<b>Description: </b>
This project simulates an entry and exit system of an urbanization that can grant access when the PIR detects a person.
This system will be simulated using a PIR sensor, an HC-SR04, a servo motor, three LEDs and a buzzer. 
For this project, the purpose of the system is to learn how to use two sensors together, which are the PIR sensor in combination with the HC-SR04. 

The <b>objectives</b> of this project are presented below.
1. The mechanical arm must be simulated with the servo motor (when it is down the red LED must be on). This must rise by placing a hand on the PIR sensor during the rise of the arm, the yellow LED must be turning on and off.
2. Simultaneously when the mechanical arm is activated, an audible alarm (buzzer to the rhythm of the yellow LED) must also be activated and when the arm is fully up, the green light must be turned on.
3. The ultrasound sensor will detect an object that interferes with the normal return of the mechanical arm to its initial position and will keep it up until the object is removed and the active audible alarm will be kept on simultaneously.
4. After a reasonable time, the mechanical arm must return to its initial position in case the HC-SR04 detects an object close enough during the descent, the arm must return to the vertical position and wait again for a reasonable time.
5. When the program starts, the red led must be set to high and the system must be with the arm down, then change the state for the normal process of entering and leaving the urbanization when the PIR is activated.

<b>Procedure:</b><br>
This project procedure can be divided into three parts. First, we have the circuit implementation. Then a state diagram to have a better understanding of the system’s behavior.  At last, we implement the code.

Part 1. Circuit Implementation.<br>
1)	Connect the Arduino 5V to the voltage area in the breadboard.
2)	Connect the Arduino ground to the ground area in the breadboard.
3)	Connect the HC-SR04 sensor to the breadboard and connect its Vcc pin and the GND pin to the 5V and the ground in the breadboard, respectively. 
4)	Then the TRIG pin of the sensor is connected to port 2. While the ECHO pin is connected to port 3. The resulting connections of the sensor are shown in Figure 1.
<br><br>![image](https://user-images.githubusercontent.com/84880545/124490906-a5ac0a80-dd80-11eb-8695-3f8495d268d3.png)<br>
Figure 1: HC-SR04 Sensor Connections.<br>

5)	Next, we connect the three LEDs in the center area of the breadboard to prevent them from interfering in the sensor readings. We connect them in the following order: red, yellow, green. The cathode of each of the LEDs is attached to the ground. While the anode of each LED is connected to their respective resistors of 330Ω. The remaining leg of the resistors were connected in the following way. The red LED resistor was connected to port 8, the yellow LED resistor was connected to port 12, while the green LED resistor was connected to port 13. In Figure 2 we can see the resulting connections for the LEDs. 
<br><br>![image](https://user-images.githubusercontent.com/84880545/124491376-3387f580-dd81-11eb-98c5-964491d80e93.png)<br>
Figure 2: LEDs Connections. <br>

6)	For the simulation, we use an unpolarized capacitor, but if you use a polarized capacitor the legs should be connected as mention below. The cathode of the capacitor is connected to port 9 of the Arduino. While the anode of the capacitor is connected to one leg of the 1kΩ resistor. The remaining leg of the 1kΩ resistor is connected to the breadboard ground.<br>
7)	The base of the transistor is connected to the node between the capacitor and the 1kΩ resistor.<br>
8)	The collector of the transistor is connected to the 5V of the breadboard.<br>
9)	The transmitter of the transistor is connected to the anode of the buzzer.<br>
10)	The cathode of the buzzer is connected to the breadboard ground. In Figure 3, we can see the resulting connection for the buzzer with the transistor and the capacitor. 
<br><br> ![image](https://user-images.githubusercontent.com/84880545/124491925-cfb1fc80-dd81-11eb-83d3-379aff83a4a8.png)<br>
Figure 3: Buzzer Connection with Transistor and Capacitor. <br>

11)	Next, connect the servo motor to port 5. Its voltage and ground were connected to the breadboard 5V and ground, respectively. The resulting connection is shown in Figure 4.
<br><br>![image](https://user-images.githubusercontent.com/84880545/124492886-063c4700-dd83-11eb-803a-1c84d7452e36.png)<br>
Figure 4: Servo Motor Connections. <br>

12)	Lastly, the PIR sensor signal pin was connected to port 4. In our simulation using tinkercad, the signal pin was the first pin from left to right. But when we were looking for the datasheet for some of its specifications we see that some models have the signal pin in the middle. For this reason, if you implement this circuit, you need to look for the datasheet corresponding to the model of your PIR sensor. The voltage, found in the middle pin, was connected to the 5V in the breadboard, while the remaining pin was connected to the breadboard ground. In Figure 5, we present the connections of the PIR sensor. At last, in Figure 6 is the finished product of our circuit.
<br><br>![image](https://user-images.githubusercontent.com/84880545/124493181-54514a80-dd83-11eb-9c8b-314584e55f10.png)<br>
Figure 5: PIR Sensor Connections. <br>
<br>![image](https://user-images.githubusercontent.com/84880545/124493454-a6926b80-dd83-11eb-8f59-886b68c9702f.png)<br>
Figure 6: Circuit Schematic. 

Part 2. State Diagram<br>
In Figure 7 we present the state diagram of what our project does and its different states throughout the execution time.
<br><br> ![image](https://user-images.githubusercontent.com/84880545/124493615-d93c6400-dd83-11eb-850f-f9e3008e9fb3.png)<br>
Figure 7: State Diagram of the project

The source code is in the repository.


This project is for educational purposes only!<br>
Copyright Disclaimer under section 107 of the Copyright Act 1976, allowance is made for “fair use” for purposes such as criticism, comment, news reporting, teaching, scholarship, education and research.<br>
Non-profit or educational use leans the balance in favor of fair use.  
