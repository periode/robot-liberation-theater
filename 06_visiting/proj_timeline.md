# Performing robo :: Detailed plan for your actor
## Areas of greatest risk or uncertainty
1.	Can we implement directionality of the robot?
2.	Computer vision – we have identified that we can track blobs on the computer using the openFrameworks software, and need to verify in the real world.
3.	Reliance on camera
4.	Robot sensing “steps” (using CV entirely), needs override in case detection doesn’t occur

##	Mechanical
1.	3D print ramps as landmarks (maintain stability) -hardcorde
2.	Rubber traction wheels
3.	Breadboard/ PCB board
4.	Acrylic body
5.	universal hub mounts (Polulu) for optical encoders

##	Electronics
1.	Bluetooth controller (robot + openFrameworks)
2.	Accelerometer
3.	Gyroscope
4.	IR LED lights to be detected by IR camera
5.	Adafruit motor controller with max 1.2 A 
6.	Arduino Uno

##	Software
1.	Open frameworks (Open CV, and communication)
2.	Hardcode locations in the program
3.	send signal to computer and computer generates word

##	Power
1.	+12V power supply for motor
2.	5 V supply for Arduino Uno

##	Schedule 

### Thursday Nov 23
* Control from MATLAB (link:https://www.mathworks.com/help/control/examples/control-of-an-inverted-pendulum-on-a-cart.html?prodcode=RC&language=en)
* Assemble the parts of the circuit (2 H-bridges| motor shield), accelerometer, gyroscope, 2x DC motors_
* Laser cut chassis (make wider?)
* Write and test code in Arduino/Matlab:
  o	Find out if Matlab code can be saved to Arduino for balancing
  o	Implement motion along x-, y-directions by modifying model
Power- check whether 6V battery enough for both DC motors

### Tuesday Nov 28
* The environment
Write and test code in Arduino:
decide on word generation (i.e. when robot passes over ramp)
decide on sound generation (speaker/PA system)
Design aesthetics of robot

* Implementation
Test that all devices are communicating with each other properly
Buttons on Bluetooth controller to send messages to the robot

* The environment
Write and test code in Arduino:
decide on word generation (i.e. when robot passes over ramp)

### Thursday Dec 5

* Test power duration, control of robot moving
* Ensure smooth running
* Decide where IR lights will be positioned in design
* Test with playtesting stage, and finalise robot-environment interactions
    
###	References
1.	http://www.brokking.net/yabr_main.html)
2. "Two-wheeled self-balancing robot" paper
