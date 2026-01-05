# ESP32 "Musashi" IoT LED Matrix Studio

**A professional, web-controlled 8×8 LED Matrix driven by an ESP32 and 74HC595 shift registers.**

This repository contains the advanced firmware for the **Musashi Studio** project. Unlike basic blink examples, this project implements a **non-blocking rendering engine**, a **responsive AJAX web dashboard**, and a massive library of procedural animations and bitmaps. 

The system allows you to control animations, scrolling text, and geometric patterns wirelessly from any smartphone or computer **without reloading the webpage**.

---

## 1. Project Features

This project goes beyond simple multiplexing to demonstrate professional IoT concepts:

* **IoT Web Dashboard:** Control the matrix wirelessly via a mobile-friendly web interface.
* **AJAX Communication:** Instant button response using the JavaScript `fetch` API. The page never reloads, providing an "App-like" feel.
* **Non-Blocking Engine:** Animations use `millis()` timers instead of `delay()`. This ensures the Wi-Fi connection remains stable and responsive even during complex rendering.
* **Orientation Correction (Mode 8):** Advanced software mapping that mathematically corrects matrix rotation or wiring inversions on the fly.
* **50+ Shape Library:** A built-in database of icons, Islamic geometric art, weather symbols, and retro game sprites.
* **Procedural Animations:** Real-time calculated effects including **Rolling Gears**, **Radar Scans**, and **Pacman** gameplay.
* **mDNS Support:** Access the dashboard via `http://musashi.local` instead of hunting for IP addresses.

---

## 2. Platform and Tools

* **IDE:** Visual Studio Code with **PlatformIO** extension.
* **Framework:** Arduino for ESP32.
* **Hardware:** ESP32-WROVER (or standard ESP32 Dev Module).
* **Language:** C++ (Embedded).

---

## 3. Hardware Architecture

The project uses two 74HC595 shift registers to expand the ESP32's GPIO capability. We drive 16 pins (8 rows + 8 columns) using only **3 data lines** from the ESP32.

### Component List
* **Controller:** ESP32 Development Board
* **Drivers:** 2× 74HC595 Shift Registers (Daisy-chained)
* **Display:** 8×8 LED Dot Matrix (Common Anode)
* **Passive:** 8× 220Ω Resistors (Current limiting for rows)
* **Power:** 5V via USB (Logic level 3.3V)

### Components Overview
Below is the full collection of parts used in the project:
![Component Image](image/component.jpg)

### Matrix Theory & Pinout
The LED matrix is a grid of 64 LEDs. To control them, we use **Multiplexing**: scanning one column at a time so fast that the human eye sees a complete image.

![Component Knowledge](image/component_knowledge.jpg)
![Component Knowledge 1](image/component_knowledge1.jpg)

These images explain:
* Structure of the LED matrix.
* Pin numbering.
* Difference between Common Anode and Common Cathode.
* Internal LED arrangement.

---

## 4. Circuit & Wiring

The ESP32 communicates with the first 74HC595 (Rows), which passes data to the second 74HC595 (Columns).

### Circuit Schematic
This schematic shows the electrical connections between the ESP32, the shift registers, and the matrix.
![Circuit Schematic](image/circuit.jpg)

### Hardware Wiring Layout
A step-by-step breadboard wiring guide. This corresponds directly to the schematic above.
![Hardware Wiring](image/hardware_connection.jpg)

### Pin Mapping (Code Configuration)

| ESP32 Pin | 74HC595 Pin | Function | Description |
| :--- | :--- | :--- | :--- |
| **GPIO 15** | Pin 14 (DS) | **Data** | Serial data input |
| **GPIO 4** | Pin 11 (SH_CP) | **Clock** | Shift register clock |
| **GPIO 2** | Pin 12 (ST_CP) | **Latch** | Storage register clock |
| **3.3V / 5V** | Pin 16 (VCC) | **Power** | IC Power Supply |
| **GND** | Pin 8 (GND) | **Ground** | Common Ground |

*Note: The Output Enable (OE) is grounded (always on) and Master Reset (MR) is tied High to VCC.*

---

## 5. Software Architecture

The software is designed in layers to simulate a multi-threaded environment on a single core.

### 1. The Rendering Engine (`render()`)
This function runs thousands of times per second. It reads from a `frameBuffer` array and pushes data to the shift registers. It includes the **"Mode 8"** transformation algorithm, which mathematically flips and rotates bits to match the physical orientation of the matrix, ensuring images are always upright.

### 2. The Animation State Machine (`updateAnimations()`)
Unlike beginner code that uses `delay(100)`, which freezes the processor, this engine uses `millis()`.
* It checks: *"Has 100ms passed since the last frame?"*
* If **Yes**: It draws the next frame of the Gear or Pacman animation.
* If **No**: It immediately yields control back to the Wi-Fi handler.
This allows the dashboard buttons to work instantly, even while an animation is playing.

### 3. The Async Web Server
The ESP32 hosts a website stored in its flash memory.
* **Frontend:** HTML/CSS/JavaScript with a grid layout.
* **Backend:** Listens for HTTP requests like `/set?id=101`.
* **Communication:** Uses AJAX (Asynchronous JavaScript and XML) to send commands silently in the background.

---

## 6. Installation & Setup

1.  **Clone the Repository:**
    ```bash
    git clone [https://github.com/abdurrahman-eee/ESP32-IoT-LED-Matrix-Studio.git)
    ```
2.  **Open in PlatformIO:**
    Open the project folder in Visual Studio Code.
3.  **Configure Wi-Fi:**
    Open `src/main.cpp` and edit the credentials:
    ```cpp
    const char* ssid = "iPhone";      // Your Network Name
    const char* password = "aassddff"; // Your Password
    ```
4.  **Upload:**
    Connect ESP32 via USB and click the **PlatformIO: Upload** button.
5.  **Monitor:**
    Open the Serial Monitor (115200 baud) to verify the connection and see the IP address.

---

## 7. How to Use the Dashboard

1.  **Connect:** Ensure your phone or laptop is on the same Wi-Fi network (or Hotspot) as the ESP32.
2.  **Access:**
    * **Easy Method:** Open browser and type `http://musashi.local`
    * **Direct Method:** Type the IP address shown in Serial Monitor (e.g., `http://172.20.10.3`).
3.  **Control:**
    * **Animations:** Click buttons like "GEAR ROLL" or "PACMAN" to start live procedural animations.
    * **Typing:** Click "MUSASHI" to see the name typed out letter-by-letter.
    * **Shapes:** Select from 50+ icons (Islamic Star, Checkmark, Weather, etc.).
    * **Stop:** Click the red "STOP" button to clear the matrix.


**Demo:**
![Hardware Wiring](image/Demo1.jpg)
![Hardware Wiring](image/Demo2.jpg)
---

## 8. Customization Guide

### Adding New Shapes
The project includes a massive library, but you can add your own custom designs.
1.  Use a [Binary-to-Hex Converter](https://xantorohara.github.io/led-matrix-editor/) to draw your 8x8 shape.
2.  Copy the hex code array.
3.  Open `src/main.cpp` and locate the `SHAPES` array.
4.  Paste your new shape at the end:
    ```cpp
    // Example: A filled box
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, 
    ```
5.  Update the Dashboard HTML in `handleRoot()` to add a button for your new ID number.

### Changing Scrolling Text
To change the text in the typing animations (like "MUSASHI" or "RAHMAN"), modify the `updateAnimations()` function inside `src/main.cpp`:


// Logic for Mode 103 (Musashi Typing)
int seq[] = {12, 20, 18, 0, 18, 7, 8}; // Indices for M, U, S, A, S, H, I
// Change these numbers to match the letters in the ALPHABET array you want to spell.

---


###  **9. Troubleshooting**
1. Dashboard doesn't load:

Check Network: Ensure you are connected to the 2.4GHz Wi-Fi band (ESP32 does not support 5GHz).

Hotspot: If using an iPhone Hotspot, turn on "Maximize Compatibility".

IP Address: If http://musashi.local fails, check the Serial Monitor and use the IP address directly (e.g., http://192.168.1.15).

2. Matrix is mirrored or upside down:

This project uses a software function applyMode8() to map the bits to the physical LEDs.

If your matrix looks wrong, you do not need to rewire it. Simply adjust the bit-shifting logic inside the applyMode8 function to rotate the image 90, 180, or 270 degrees.

3. Flickering or Ghosting:

Slight flickering during heavy Wi-Fi activity is normal as the single-core ESP32 handles network traffic.

If flickering is severe, check your breadboard jumper wires—loose connections on the latch (ST_CP) or clock (SH_CP) pins are the most common cause.
---

## 10. Future Roadmap
Cloud Control: Integrate MQTT (Message Queuing Telemetry Transport) to control the matrix from outside the local network via the Internet.

NTP Clock: Fetch real-time data from NTP servers to display a digital clock.

Audio Visualization: Add an analog microphone module (MAX4466) to make the matrix react to music beats.

RGB Upgrade: Port the logic to support WS2812B (NeoPixel) matrices for full-color animations.
---

## 11. Conclusion
This project demonstrates how to bridge low-level hardware control (Shift Registers, Multiplexing) with high-level software concepts (AJAX, Non-blocking I/O, REST APIs). It serves as a robust foundation for any advanced IoT display system.

Project Lead: Abdur Rahman Repository: ESP32-IoT-LED-Matrix-Studio License: MIT License
