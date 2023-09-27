# Micromouse Project 🤖

![Micromouse Robot](media/Dina.jpg)

Welcome to the Micromouse project repository! This project showcases a small autonomous robot designed for maze navigation. Explore this project if you're interested in robotics and autonomous systems.

## Table of Contents
- [Hardware Components](#hardware-components)
- [Software](#Software 🧾)
  - [Controlling the Robot](#controlling-the-robot)
  - [Algorithms](#algorithms)
- [Team](#team)
- [Installation](#installation)
- [Contributing](#contributing)
- [Contact](#contact)

## Hardware Components 🛠️

The Micromouse project utilizes the following hardware components:

### PCB (Printed Circuit Board) 🧩
![PCB](media/pcb_image.jpg)

The central control hub that connects and manages all other components.

You can find all details and schematic [Here](https://oshwlab.com/om4rr/micromouse).

### Ultrasonic Sensor 🦇
![Ultrasonic Sensor](media/ultrasonic_image.jpg)

Measures distances and detects obstacles for navigation.

### IR Sensor (Infrared Sensor) 🕵️
![IR Sensor](media/ir_sensor_image.jpg)

Detects lines and walls for precise navigation in mazes.

### Optical Encoder 🔍
![Optical Encoder](media/encoder_image.jpg)

Tracks wheel movements for accurate control.

### Wheels 🚗
![Wheels and Chassis](media/wheels_image.jpg)

The wheels of the robot.

### 3D Design 🖨️

We have designed a custom 3D chassis for the robot using Fusion 360. Here's a photo of our 3D design:

![3D Design](media/3D_Design_image.jpg)

For More Photos click [Here](Design/images)

### Bluetooth Module 📶
![Bluetooth Module](media/bluetooth_image.jpg)

Allows remote debugging and control for monitoring the robot.

### Motors 🔄
![Motors](media/motors_image.jpg)

Drive the wheels for movement.

### Freewheel (Caster Wheel) 🎡
![Freewheel](media/freewheel_image.jpg)

Provides stability and maneuverability during turns.

### Gyroscope (MPU6050) 🧭
![Gyroscope](media/gyroscope_image.jpg)

Measures angles and helps maintain orientation for accurate navigation.

## Software 🧾

### Controlling the Robot 🎮

#### Angle Control with PD System 📐

We've implemented a PD (Proportional-Derivative) control system for angle control using the Gyroscope (MPU6050) as the feedback element. The primary goal of this system is to keep the robot moving in a straight line and execute precise 90-degree turns when needed.

- **Proportional (P):** The proportional part of the controller ensures that the desired angle remains static, allowing the robot to move in a straight line.

   Functionality: When P is adjusted, it affects how quickly the robot corrects deviations from a straight path.

- **Derivative (D):** The derivative part helps fine-tune the turning process.

   Functionality: Tuning D affects how the robot responds to deviations in the angle, contributing to stable and precise turns.

For graphs and visualizations of the tuning process, please click [Graphs](Testing/PID_CALC/Graphs) to access the response graphs.

#### Sensor Reading 📡

To navigate the maze effectively, the robot continuously reads sensors located in every cell. Here's how the sensors work:

- **Ultrasonic Sensors:** These sensors detect obstacles, specifically walls, by measuring distances. This information helps the robot avoid collisions and navigate around maze walls.

- **IR Sensors (Infrared Sensors):** While the robot is designed to move in a straight line, minor alignment issues can occur. The IR sensors play a crucial role in detecting deviations from a straight path. If an IR sensor reads a signal, it indicates that the robot is getting too close to a wall.

   Functionality: In response to IR sensor readings, we make minor adjustments to the desired angle, typically by 5 degrees, to correct the alignment and maintain a straight path.

By combining precise angle control and sensor readings, our robot can successfully navigate the maze with accuracy and efficiency.

### Algorithms 🧠

The general idea for the algorithm is that it discovers the whole maze using the flood-fill algorithm and collects the data needed to configure the shortest path using BFS.
The code is provided with comments to explain in detail this approach [Algorithm](Optimised_Algorithm/floodfill/floodfill.cpp).

#### Maze Simulation 🌀

You can watch a maze simulation in action below:

[![Maze Simulation](media/maze_simulation.gif)](https://github.com/hamed2634/MicroMouse-Robot/assets/52867472/5dad4e3b-37f2-4e1f-a091-5508377ebc72)

## Team 👥

Meet the team members who contributed to this project:

- **[Hamed](https://github.com/Hamed2634):** Responsible for controlling the robot.

- **[3bkareem](https://github.com/3bkareem):** Responsible for algorithm development.

- **[om4rrr](https://github.com/om4rrr):** Responsible for PCB design and assembling hardware.

- **[Kareem](https://github.com/UwUKareem):** Responsible for 3D design.

## Installation 📥

1. You can download the latest version of the Micromouse project as a ZIP file by clicking [here](link_to_zip_file.zip).

## Contributing 🤝

While this project primarily serves as a showcase, we welcome suggestions and improvements. Feel free to create issues or send pull requests.

## Contact 📧

For inquiries or to get in touch, you can reach us at [hamed.mohamed26324@gmail.com]. Enjoy exploring the Micromouse project! 🤖🚀
