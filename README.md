# 🛩️ 2D Aircraft Flight Simulator

A physically based two-dimensional aircraft flight simulator written in **C++**, designed to model the fundamental dynamics of flight with computational efficiency and educational clarity.  
This project simulates the motion of an aircraft under realistic aerodynamic forces, allowing analysis of speed, altitude, attitude, and other flight parameters over time.

---

## 📘 Overview

This simulator numerically integrates Newton's equations of motion for a light aircraft (such as a Cessna 152) within a two-dimensional space.  
The model incorporates **lift**, **drag**, **thrust**, and **weight** as primary forces, using aerodynamic principles to predict how the aircraft evolves under different flight attitudes.

The simulation is paired with a **Python visualization module** (`plot_results.py`) that produces time-resolved plots of altitude, speed, and other metrics directly from flight data logged during runtime.

---

## ⚙️ Physics Model

The simulation assumes a non-rotating Earth and a constant air density.  
The main aerodynamic forces are defined as:

\[
L = \frac{1}{2} \rho V^2 S C_L
\]

\[
D = \frac{1}{2} \rho V^2 S C_D
\]

where:

| Symbol | Quantity | Units |
|:-------:|-----------|--------|
| \( L \) | Lift | N |
| \( D \) | Drag | N |
| \( \rho \) | Air density | kg/m³ |
| \( V \) | Airspeed | m/s |
| \( S \) | Wing area | m² |
| \( C_L \) | Lift coefficient | — |
| \( C_D \) | Drag coefficient | — |

The **thrust** is modeled as:

\[
T = \frac{P}{V}
\]

where \( P \) is the available engine power.  
In future developments, \( T \) can be refined using a propeller efficiency factor or a function of propeller performance curves.

The forces are projected into the **horizontal (x)** and **vertical (y)** components as:

\[
F_x = T \cos(\theta) - D \cos(\theta) - L \sin(\theta)
\]
\[
F_y = T \sin(\theta) - D \sin(\theta) + L \cos(\theta) - W
\]

The aircraft's position and velocity are updated at each time step using Euler integration.

---

