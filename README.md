# Smart Home Automation System (AVR)

This project is a **Smart Home Automation System** developed using **AVR ATmega32** microcontroller. The system includes features like:

- Admin/User login system with password protection
- Secure EEPROM-based credential storage
- Access control using LCD and 4x4 Keypad
- LED control (Green, Red, Blue, Yellow)
- AC (fan) control using temperature sensor and PWM
- Servo motor control for door automation
- Alarm and buzzer system for incorrect login attempts

## 🔐 Features:

### 👤 Admin:
- Sign-in only once and save credentials to EEPROM
- Login authentication (3 trials)
- Controls:
  - AC based on temperature sensor (LM35)
  - Door control using servo motor
  - LED control (ON/OFF/Dimming)
  - Add/Delete users (up to 3)

### 👥 Users:
- Login authentication (3 trials)
- Control:
  - LEDs (ON/OFF/Dimming)
  - AC based on temperature

## 🧠 Components Used:
- ATmega32 Microcontroller
- LCD 16x2
- 4x4 Keypad
- EEPROM (Internal)
- LEDs (GRN, RED, BLU, YEL)
- Servo Motor
- Buzzer
- LM35 Temperature Sensor
- PWM (OC0 and OC1A)

## 🛠️ Technologies:
- AVR C
- PlatformIO (Recommended)
- Low-Level Driver Abstraction (DIO, LCD, ADC, PWM, EEPROM, etc.)

## 📸 Screens:
- Login Interface on LCD
- Temperature Display
- LED Control Menu
- Add/Delete User Menu

## ⚠️ Security:
- Admin and users have separate login
- System locks after 3 wrong trials
- Buzzer and red LED alert system

## 📦 Getting Started:

1. Clone the repository:
```bash
git clone https://github.com/YOUR_USERNAME/Smart-Home-Automation-AVR.git
