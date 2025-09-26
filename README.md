# 🚀 Assisted-Trajectory Robot Car

## 📖 Overview
This model robot car was developed and built to implement an assisted-trajectory (Drive by Wire) system. The system is controlled using a Teensy microcontroller to enhance computational speed and stability.  

A gyroscope measures angular velocity, while an H-bridge drives the motors. The robot is operated via a Flysky FS-6X remote using a PPM/PWM modulated signal.

## 📂 Contents
- `/Hardware` → schematic, PCB, Gerbers.
- `/control_car` → C code for Teensy in the Arduino environment.
- `/docs` → photos.

## 📐 Digital PID Control

The UAV uses a discrete PID controller implemented on a Teensy microcontroller.  
The control law in the digital domain is expressed as:

$\[
u[k] = K_p \cdot e[k] \;+\; K_i \cdot \sum_{i=0}^{k} e[i] \cdot T_s \;+\; K_d \cdot \frac{e[k] - e[k-1]}{T_s}
\]$

Where:
- \( u[k] \) → Control signal at step \(k\)  
- \( e[k] \) → Error signal at step \(k\) (\( e[k] = r[k] - y[k] \))  
- \( K_p \) → Proportional gain  
- \( K_i \) → Integral gain  
- \( K_d \) → Derivative gain  
- \( T_s \) → Sampling time  

For implementation efficiency, the incremental (recursive) form of the PID controller is used:

\[
u[k] = u[k-1] + a_0 \cdot e[k] + a_1 \cdot e[k-1] + a_2 \cdot e[k-2]
\]

With coefficients:

\[
a_0 = K_p \left(1 + \frac{T_s}{2 T_i} + \frac{T_d}{T_s}\right), \quad
a_1 = -K_p \left(1 - \frac{T_s}{2 T_i} + \frac{2 T_d}{T_s}\right), \quad
a_2 = K_p \cdot \frac{T_d}{T_s}
\]

Where:
- \( T_i \) → Integral time constant  
- \( T_d \) → Derivative time constant  





## 🌐 YouTube
📺 [My Playlist](https://youtube.com/playlist?list=PLy6JmHc8bVqIY5rbHkpyFbhlm4xQOCF1T&si=1QBgLZTLAjbxRnrU)

## 🔄 Control Loop
<p align="center">
<img src="docs/diagrama auto.png" alt="Diagrama sistema" width="500">
</p>

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
