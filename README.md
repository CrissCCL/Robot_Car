# 🚀 Assisted-Trajectory Robot Car

## 📖 Overview
This model robot car was developed and built to implement an assisted-trajectory (Drive by Wire) system. The system is controlled using a Teensy microcontroller to enhance computational speed and stability.  

A gyroscope measures angular velocity, while an H-bridge drives the motors. The robot is operated via a Flysky FS-6X remote using a PPM/PWM modulated signal.

## 📂 Contents
- `/Hardware` → schematic, PCB, Gerbers.
- `/control_car` → C code for Teensy in the Arduino environment.
- `/docs` → photos.

## 🌐 YouTube
📺 [My Playlist](https://youtube.com/playlist?list=PLy6JmHc8bVqIY5rbHkpyFbhlm4xQOCF1T&si=1QBgLZTLAjbxRnrU)

## 🔄 Control Loop
<p align="center">
<img src="docs/diagrama auto.png" alt="Diagrama sistema" width="500">
</p>

### Controlled Variables
- **Yaw** → Angular velocity control (rotation rate)

## 📐 Digital PID Control

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
The parameters are adjusted for each of the angular rate,
$$
K_0 = K_p + \frac{K_p}{2T_i} T_s
$$

$$
K_1 = -K_p + \frac{K_p}{2T_i} T_s
$$



## :triangular_ruler: Connection Diagram
<p align="center">
<img src="docs/conexiones.png" alt="Esquema de conexiones" width="500">
</p>

## 🖼️ Render 3D PCB
<p align="center">
<img src="docs/shield teensy_v2.jpg" alt="PCB Render" width="500">
</p>
---

## ⚡ Physical Prototype
<p align="center">
<img src="docs/auto4.jpg" alt="Foto del prototipo" width="400">
</p>
<p align="center">
<img src="docs/auto7.jpg" alt="Foto del prototipo" width="400">
</p>

## 📜 License
MIT License  
