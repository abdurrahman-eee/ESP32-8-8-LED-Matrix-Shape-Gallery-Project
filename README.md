# ESP32 8×8 LED Matrix Shape Gallery Project

This repository contains a complete project for driving a single 8×8 LED matrix using an ESP32 and two 74HC595 shift registers. The program displays multiple clear pixel-based shapes in a continuous slideshow. The project is implemented and built using PlatformIO in Visual Studio Code.

The goal of the project is to learn:

* how an LED matrix works
* how to multiplex rows and columns
* how to use 74HC595 shift registers
* how to generate custom shapes and symbols on an 8×8 matrix

---

## 1. Project Summary

The LED matrix contains 64 LEDs arranged as 8 rows by 8 columns.
To reduce the number of pins required, the LEDs are internally grouped and controlled using common anode or common cathode wiring. In this project, a common anode matrix is used.

The ESP32 sends data to the LED matrix column by column. Due to human visual persistence, even though only one column is actually lit at a time, the pattern appears as a complete image.

Two 74HC595 shift registers are used so that only a few ESP32 GPIO pins are required.

---

## 2. Platform and Tools

* Visual Studio Code
* PlatformIO extension
* ESP32 board support in PlatformIO
* C/C++ programming language

This project is written for PlatformIO, but the source code can be adapted to the Arduino IDE if necessary.

---

## 3. Components Used

The images for component explanation are already uploaded in the repository in the `image` folder. The filenames below match your repository.

### Component list image

File:
`image/component.jpg`
![Component Image](image/component.jpg)


This image shows the full collection of parts used in the project.

### Detailed component knowledge image

Files:
`image/component_knowledge.jpg`
`image/component_knowledge1.jpg`

These images explain:

* structure of LED matrix
* pin numbering
* difference between common anode and common cathode
* internal LED arrangement

### Breadboard and GPIO board

* ESP32-WROVER development board
* ESP32 GPIO extension board
* Full-size breadboard

### IC and passive components

* 74HC595 shift register IC x2
* 8×8 LED dot matrix display x1
* 220 Ω resistors x8
* Male-to-male jumper wires

---

## 4. How the LED Matrix Works

The matrix can be common anode or common cathode.

In this project:

* rows share common positive terminals
* columns are controlled as negative returns

To display an image:

1. select a column
2. enable appropriate rows as binary pattern
3. add a short delay
4. move to next column
5. repeat continuously

Persistence of vision makes it appear static.

The image `component_knowledge.jpg` contains graphical explanation and bit patterns for displaying a smile symbol.

---

## 5. Circuit and Wiring

### Circuit schematic

File:
`image/circuit.jpg`

This schematic shows electrical connection between:

* ESP32
* two 74HC595 ICs
* LED matrix rows and columns
* resistors for current limiting

74HC595 connections:

* one IC drives rows
* one IC drives columns
* latch, clock, and data are shared

Power supply:

* 3.3 V logic used
* optionally 5 V matrix supply for higher brightness

### Hardware wiring layout

File:
`image/hardware_connection.jpg`

This breadboard wiring diagram shows actual jumper wire routing.
It corresponds directly to the schematic and can be followed step by step when assembling the hardware.

---

## 6. Pin Connections (ESP32 to 74HC595)

The default pin mapping in the code:

* GPIO 15 → DS (Data)
* GPIO 4 → SH_CP (Clock)
* GPIO 2 → ST_CP (Latch)
* GND → GND
* 3.3 V → VCC

If your ESP32 layout is different, edit the pin constants in code.

---

## 7. Software Operation

The code:

* initializes GPIO pins
* performs full LED self-test
* refreshes the matrix using multiplexing
* cycles through many stored shapes
* each shape is displayed for a defined time

Shapes belong to groups such as:

* emoji faces
* geometric shapes
* retro game patterns
* simple Islamic art style shapes
* mathematical patterns

You can add your own by defining 8-byte arrays.

---

## 8. Building and Uploading the Code (PlatformIO)

Steps to compile using PlatformIO:

1. Open Visual Studio Code
2. Install PlatformIO extension
3. Create a new ESP32 project
4. Select board such as `esp32dev`
5. Replace `src/main.cpp` with the project source file
6. Connect ESP32 by USB
7. Click “Upload”

PlatformIO will compile and flash automatically.

---

## 9. Adding Images in GitHub README

Store images in folder:

```
image/
```

To show images in README:

```
![Component List](image/component.jpg)

![Component Knowledge](image/component_knowledge.jpg)

![Circuit Diagram](image/circuit.jpg)

![Hardware Connection](image/hardware_connection.jpg)
```

You already uploaded:

* circuit.jpg
* component.jpg
* component_knowledge.jpg
* component_knowledge1.jpg
* hardware_connection.jpg

They can be placed wherever you want in the README.

---

## 10. Troubleshooting

Nothing lights up:

* check 3.3 V and GND
* check common ground between ESP32 and matrix
* verify latch, clock, and data lines

Random blinking:

* wiring error in 74HC595 connections

Shape mirrored or upside down:

* rotate matrix physically
* reverse row or column orientation in software

Low brightness:

* use lower resistor value like 220 Ω
* supply matrix with 5 V if supported

---

## 11. Future Improvements

Possible extensions:

* Wi-Fi remote control
* phone or browser dashboard
* Bluetooth operation
* scrolling text
* interactive buttons
* multiple cascaded matrices

---

## 12. Conclusion

This project demonstrates how to:

* control LED matrices
* use shift registers for IO expansion
* implement multiplex display refresh
* design binary graphics manually

It is a practical starting point for more advanced LED signage and display systems.

---
