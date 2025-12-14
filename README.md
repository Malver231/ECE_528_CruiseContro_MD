
ECE 528 CRUISE CONTROL 

 INTRODUCTION
This project focuses on designing and implementing a mobile robot capable of maintaining a safe following distance, reacting “intelligently” to obstacles, and accepting manual commands through Bluetooth. The system integrates ultrasonic sensing, PI-based cruise control, and a real-time obstacle avoidance state machine onto the MSP432P401R microcontroller.
Ultrasonic distance data is continuously acquired using hardware capture and filtering, enabling smooth speed regulation. When obstacles are detected, the robot transitions into an avoidance mode that evaluates its surroundings using live sensor data and selects an alternate heading. Additionally, manual commands issued over Bluetooth override autonomous behavior and provide direct control for testing and demonstration.
The combination of continuous sensing, control theory, and event-driven state management makes this system a practical demonstration of embedded robotics principles and autonomous vehicle behavior.

FUNCTIONAL BLOCK

<img width="567" height="531" alt="image" src="https://github.com/user-attachments/assets/91c722a1-f81e-4228-8a41-aab9f25c4b2a" />

STATE MACHINE BLOCK

<img width="711" height="484" alt="image" src="https://github.com/user-attachments/assets/f09796d0-e114-4135-af72-96a415e6ff45" />


<img width="594" height="344" alt="image" src="https://github.com/user-attachments/assets/749a7a8b-44c6-416c-8f8d-ee115714c94d" />

BACKGROUND AND METHODOLOGY

Autonomous mobile robots rely on three foundational principles: sensing, control, and decision-making. This project implements all three using the MSP432 microcontroller, an ultrasonic distance sensor, classical PI control, and a finite state machine.

Ultrasonic Distance Measurement.

The HC-SR04 ultrasonic sensor determines distance using the time-of-flight principle that was originally intended to be used with this project. A short 10 µs trigger pulse initiates a 40 kHz ultrasonic burst. The sensor raises its echo pin for a duration proportional to the round-trip travel time of the sonic pulse. Using hardware capture mode on Timer_A2 in continuous mode, and interrupt enable trigger by both eges, and using Interrupt Service Routine (see figure 2), the MSP432 timestamps the rising and falling edges of the echo signal. The measured pulse width is converted to distance using  the formula:
   distance" "(mm)=(Δt" " (us)⋅10)/58

PI Control for Cruise Mode.

Proportional-Integral (PI) control is used to maintain a safe following distance. The proportional term reacts to instantaneous error:

e(t)=d_measured-d_target

while the integral term eliminates accumulated steady-state error. The combined output adjusts the PWM duty cycle of the motors:
u(t)=K_p e(t)+K_i∫e(t)dt
This maintains smooth, stable motion while reacting to dynamic changes in distance.

Finite State Machine for Behavior Control.

Robot behavior is organized into a high-level state machine with four modes: 
IDLE     CRUISE     AVOID     MANUAL.

 The CRUISE state uses PI control to maintain distance. When the robot detects that it is too close to an obstacle, it transitions into the AVOID state. A non-blocking state machine evaluates left and right directions using live ultrasonic readings until a clear path is found. Bluetooth commands allow manual override by transitioning into the MANUAL state, where direct motor commands are executed.
This combination of sensing, closed-loop control, and state-based decision-making forms the foundation of the robot’s autonomous behavior.

COMPONENTS USED

<img width="1237" height="370" alt="image" src="https://github.com/user-attachments/assets/7c7d28b6-9b3d-42eb-9747-78e73175c648" />

PINS USED

<img width="1322" height="681" alt="image" src="https://github.com/user-attachments/assets/72d8298d-2bf0-46e6-a0a4-e3d87bf34e5e" />

