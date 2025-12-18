# 🚀 Assisted-Trajectory Robot Car

## 📖 Overview
This model robot car was developed and built to implement an assisted-trajectory (Drive by Wire) system. The system is controlled using a Teensy 4.0 microcontroller to enhance computational speed and stability.  

A gyroscope MPU6050 measures angular rate, while an H-bridge L298N drives the motors. The robot is operated via a Flysky FS-6X remote using a PPM/PWM modulated signal.


## 🧩 Hardware Notes — Pin Availability

The currently implemented PCB used in this robot car **does not expose Teensy 4.0 pins 12 and 13**, as the original board was designed for a specific application and limited I/O requirements.

As part of an ongoing hardware update, a **new pin expansion and routing strategy** is being developed.  
This updated PCB revision exposes **all relevant Teensy 4.0 pins**, including pins **12 and 13**, enabling greater flexibility and reuse across multiple projects.

This improvement aligns with the goal of creating **modular and reusable hardware blocks** that can be shared across multiple projects.

> 🔗 **NOTE:**  
> The updated pin expansion hardware is referenced in the **Related Repositories** section at the end of this document.


## 📂 Contents
- `/Hardware` → schematic, PCB, Gerbers.
- `/control_car` → C code for Teensy in the Arduino environment.

## 🌐 YouTube
📺 [My Playlist](https://youtube.com/playlist?list=PLy6JmHc8bVqIY5rbHkpyFbhlm4xQOCF1T&si=1QBgLZTLAjbxRnrU)


## ⚙️ System Description — Auto Robot (Assisted-Trajectory)
- **Controller:** Teensy 4.0 (high-speed MCU for improved stability and processing)  
- **Sensors:** Gyroscope (angular velocity) and supporting encoders/IMU as available  
- **Actuators:** Dual DC motors with H-bridge driver  
- **Control Strategy:** PI-assisted trajectory control (drive-by-wire)  
- **Sampling period:** **0.004 seconds (250 Hz)**  
- **Data transmission:** UART link to a **Raspberry Pi 4B** for logging and postprocessing  
- **Data logging:** Raspberry Pi saves incoming telemetry to `.csv` files for analysis  
- **Visualization:**  Offline monitoring and plotting via Matlab



## 🔄 Control Loop

<p align="center">
<img src="https://github.com/user-attachments/assets/6554999b-4045-4824-b776-99e6d4a64039" alt="Diagrama sistema" width="500">
</p>

### Controlled Variables
- **Yaw** → Angular velocity control (rotation rate)

## 📐 Digital PID Control

The PID controllers implemented in this project are **incremental (velocity form)** and use **trapezoidal integration** for the integral term.  
This ensures:
- Accurate discrete-time implementation suitable for microcontrollers.
- Consistency between simulation and embedded hardware behavior.
- Avoidance of integral windup when combined with actuator saturation or anti-windup mechanisms.

The UAV uses a discrete PI controller implemented on a Teensy microcontroller.  
The control law in the digital domain is expressed as:

$$
u(n) = u(n-1) + K_0 e(n) + K_1 e(n-1)
$$

Digital PI controller implemented for Yaw rate measured in Gyroscope,

$$
Gyro_{PWM}(n) = Gyro_{PWM}(n-1) + K_0 e(n) + K_1 e(n-1)
$$




### Parameters:
The parameters are adjusted for the angular rate,

$$
K_0 = K_p + \frac{K_p}{2T_i} T_s
$$

$$
K_1 = -K_p + \frac{K_p}{2T_i} T_s
$$

### Control Signal:

$$
motor_1=PWR_{PWM}+Gyro_{PWM}
$$
$$
motor_2=PWR_{PWM}-Gyro_{PWM}
$$

## :triangular_ruler: Connection Diagram

<p align="center">
<img src="https://github.com/user-attachments/assets/3c3a294c-4754-4421-848b-a7afd0249743" alt="Esquema de conexiones" width="500">
</p>

## 🧪 PI Control Test and ARX Model Comparison  

A test was performed using a **PI controller** applied to the assisted trajectory system of the robot car.  
The experimental results were compared against a **linear ARX model** identified from system data.  

### 🔹 General ARX Model Equation  

The ARX (Auto-Regressive with eXogenous input) model is defined as:  

$$
y(k) + a_1 y(k-1) + a_2 y(k-2) + \dots + a_{n_a} y(k-n_a) =
b_1 u(k-1) + b_2 u(k-2) + \dots + b_{n_b} u(k-n_b) + e(k)
$$  

Where:  
- $$y(k)$$: system output at sample $$k$$ 
- $$u(k)$$: input signal at sample $$k$$  
- $$( a_i, b_j)$$: ARX parameters  
- $$( n_a, n_b)$$: model orders  
- $$e(k) $$: disturbance/noise  

### 🔹 Results Overview  
- ✅ The PI controller improved **trajectory tracking** and reduced steady-state error.  
- 📉 The ARX model provided a good approximation of the system dynamics, with slight deviations due to unmodeled nonlinearities.  
- ⚖️ The comparison validates the feasibility of using simple parametric models (ARX) for **controller design and evaluation**.  

### 🔹 Experimental Plots  

<p align="center">
<img src="https://github.com/user-attachments/assets/df96d89c-fe9f-4e2f-a7c6-7a3ea11e48c8" alt="ARX vs Experimental Comparison" width="500">
</p>

## 🖼️ Render 3D PCB

<p align="center">
<img src="https://github.com/user-attachments/assets/4ba71673-e3fc-413e-8d6d-a915e6dcacb8" alt="PCB Render" width="500">
</p>

## ⚡ Physical Prototype

<table>
  <tr>
    <td align="center">
      <img src="https://github.com/user-attachments/assets/531a438f-fe71-4ad5-b7c5-ba94d4f77213" alt="Foto del prototipo" width="450"><br>
      <sub>Assembly device</sub>
    </td>
    <td align="center">
      <img src="https://github.com/user-attachments/assets/287534e9-c59d-42de-ac4f-8b715e09e8dd" alt="Foto del prototipo" width="450"><br>
      <sub>Complete setup</sub>
    </td>
  </tr>
</table>

## 🔗 Related Repositories

For additional tutorials and examples related to digital control simulations, visit:

- [Digital Control — Anti-Windup (Positional PI)](https://github.com/CrissCCL/Digital_ControlAntiWindup)
- [Digital Control Simulation — First Order System + Saturation](https://github.com/CrissCCL/Digital_ControlSim)
- [Digital Control Simulation — ARX Model + Saturation](https://github.com/CrissCCL/Digital_ControlSimARX)

An updated Teensy 4.0 pin expansion shield is available and can be reused across different projects:
- [Teensy 4.0 Pin Expansion Shield](https://github.com/CrissCCL/Teensy_SHIELD)



## 📜 License
MIT License  
