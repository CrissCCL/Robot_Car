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


Where:


For implementation efficiency, the incremental (recursive) form of the PID controller is used:


With coefficients:



Where:




## Control PI digital:

\[
u(n) = u(n-1) + K_0 e(n) + K_1 e(n-1)
\]

\[
Giro_{PWM}(n) = Giro_{PWM}(n-1) + K_0 e(n) + K_1 e(n-1)
\]

### Parámetros:

\[
K_0 = K_p + \frac{K_p}{2T_i} T_s
\]

\[
K_1 = -K_p + \frac{K_p}{2T_i} T_s
\]

---

## Control PID digital:

\[
u(n) = u(n-1) + K_0 e(n) + K_1 e(n-1) + K_2 e(n-2)
\]

\[
Giro_{PWM}(n) = Giro_{PWM}(n-1) + K_0 e(n) + K_1 e(n-1) + K_2 e(n-2)
\]

### Parámetros:

\[
K_0 = K_p + \frac{K_p}{2T_i} T_s + \frac{K_p T_d}{T_s}
\]

\[
K_1 = -K_p + \frac{K_p}{2T_i} T_s - 2 \frac{K_p T_d}{T_s}
\]

\[
K_2 = \frac{K_p T_d}{T_s}
\]

---

### Función de transferencia:

\[
G_{CD}(z) = \frac{K_0 + K_1 z^{-1} + K_2 z^{-2}}{1 - z^{-1}}
\]

### Ecuación en diferencias:

\[
u(n) = u(n-1) + K_0 e(n) + K_1 e(n-1) + K_2 e(n-2)
\]



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
