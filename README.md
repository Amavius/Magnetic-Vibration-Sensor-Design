# Coil–Magnet Vibration Sensor (Measurement Systems Project)

This repository contains my Measurement Systems course final project:  
a **coil–magnet vibration sensor** with Arduino data acquisition and **FFT-based frequency analysis**.

## Features
- Custom-designed coil–magnet vibration sensor
- Arduino-based data acquisition system
- Real-time signal processing
- FFT analysis of vibration response
- Documentation and report

## Recent improvements
- Higher-throughput serial streaming (115200 baud) for faster data offload from the Arduino acquisition sketch.
- Deterministic timer-driven sampling with race-free buffering, enabling continuous capture cycles without manual resets.
- Cleaner interrupt handling and code structure for easier maintenance and extension.

## Repository Structure
- `Code` → Arduino and MATLAB source codes 
- `Report` → Full project report (PDF)  
