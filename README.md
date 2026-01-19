# **ESP32 Smart Motor Control System**

**Created by:** Wasel Ahmed  

![IMG_2351](https://github.com/user-attachments/assets/c241dada-177b-4c4f-9d9b-5bb9d360c776)

---

## **Project Overview**

This project is my **first project using the ESP32**. It is a **smart motor control system** that allows precise control of a DC motor using an **L293D motor driver**. The system can move the motor **forward, reverse, stop**, and simulate **task sequences with speed variations**, failures, and recovery mechanisms.  

The project demonstrates how microcontrollers can **interact with actuators**, manage tasks, and track **system statistics**.

---

## **Hardware Components**

- **ESP32 Dev Board**  
- **L293D Motor Driver**  
- **DC Motor**  
- **Power supply for motor**  
- **Connecting wires**  
- **Breadboard (optional)**  

**Pin Configuration:**

- **ENA (Motor Enable): GPIO 25**  
- **IN1 (Motor Direction 1): GPIO 27**  
- **IN2 (Motor Direction 2): GPIO 14**

---

## **Functions Implemented**

- **motorForward(speedPercent)** – Moves motor forward at a specified speed (0–100%)  
- **motorReverse(speedPercent)** – Moves motor in reverse at a specified speed  
- **motorSoftStop()** – Gradually reduces motor speed to 0  
- **motorHardStop()** – Instantly stops the motor  
- **runBasicTask()** – Executes a full task sequence including speed variations and simulated failures  
- **printStatistics()** – Displays total tasks, successes, failures, recoveries, and system uptime  
- **printHelp()** – Displays available commands  

---

## **Failures Encountered**

During testing:  

- **Motor ran continuously without command** – Fixed by adjusting PWM control and pin logic  
- **Random task failures** – Simulated in code to test recovery sequences  
- **Learning curve with ESP32 PWM control** – Solved using `analogWrite` for simplicity  

---

## **Future Improvements**

- **Add Wi-Fi connectivity** to report data remotely  
- **Integrate Google Sheets** for automated logging  
- **Add sensors** for real-world feedback like current or position  
- **Implement mobile app interface** for control  

---

## **Project Highlights**

- First project using **ESP32**  
- Implemented **motor control and safety mechanisms**  
- **Task automation and statistics tracking**  
- **Recovery mechanisms for simulated failures**  
- **Serial interface commands** for easy manual control  

---

## **What I Learned**

- How to **interface an ESP32 with L293D** for DC motor control  
- Practical use of **PWM** for speed control  
- Designing **task sequences** with phases and conditional logic  
- Tracking **statistics** and **system uptime** in microcontrollers  
- Handling **failures and recovery** in embedded systems  

---

## **Usage Instructions**

1. Connect the **ESP32** and **L293D** as per the pin configuration.  
2. Upload the code using **Arduino IDE**.  
3. Open **Serial Monitor** at 115200 baud.  
4. Use the following commands:  
   - `r` – Run main actuator task  
   - `f` – Forward (50%, 2s)  
   - `b` – Reverse (50%, 2s)  
   - `s` – Emergency stop  
   - `d` – Display statistics  
   - `c` – Clear statistics  
   - `h` – Show help  

---

## **Repository Structure**

- `main.ino` – Arduino code for motor control and task sequences  
- `README.md` – Project description and instructions  

---

## **Acknowledgments**

- Inspiration from online ESP32 tutorials for **motor control**  
- Learning resources from Arduino and L293D datasheets  
- Guidance and clarifications from **ChatGPT**, for code structure, and troubleshooting assistance  

