#
# File:                 plot_results.py
# Author:               VacationAir
# Latest revition:      5/11/2025
#

import os
import pandas as pd
import matplotlib.pyplot as plt

os.makedirs("plots", exist_ok=True)
data = pd.read_csv("flight_data.csv")

# Function to create a graph based on position and time 

def plot_position_and_altitude():
    position = data["position"]
    altitude = data["altitude"]
    
    fig, ax = plt.subplots(figsize=(8, 6))
    
    ax.plot(position, altitude, color="blue", linewidth=2)
    
    ax.set_xlabel("Position (m)")
    ax.set_ylabel("Altitude (m)")
    ax.set_title("Airplane - Position vs Altitude")
    
    ax.grid(True)
    plt.tight_layout()
    plt.savefig("./plots/position_and_altitude.png", dpi=300, bbox_inches='tight')
    plt.show()

def plot_time_and_altitude():
    time = data["time"]
    altitude = data["altitude"]
    
    fig, ax = plt.subplots(figsize=(8, 6))
    
    ax.plot(time, altitude, color="blue", linewidth=2)
    
    ax.set_xlabel("Time in seconds")
    ax.set_ylabel("Altitude (m)")
    ax.set_title("Airplane - Altitude in Time")
    
    ax.grid(True)
    plt.tight_layout()
    plt.savefig("grafico.png", dpi=300, bbox_inches='tight')
    plt.savefig("./plots/time_and_altitude.png", dpi=300, bbox_inches='tight')
    plt.show()

def plot_time_and_position():
    time = data["time"]
    position = data["position"]
    
    fig, ax = plt.subplots(figsize=(8, 6))
    
    ax.plot(time, position, color="blue", linewidth=2)
    
    ax.set_xlabel("Time in seconds")
    ax.set_ylabel("Position (m)")
    ax.set_title("Airplane - Position in Time")
    
    ax.grid(True)
    plt.tight_layout()
    plt.savefig("grafico.png", dpi=300, bbox_inches='tight')
    plt.savefig("./plots/time_and_position.png", dpi=300, bbox_inches='tight')
    plt.show()

def plot_time_and_angle():
    time = data["time"]
    angle = data["angle"]
    
    fig, ax = plt.subplots(figsize=(8, 6))
    
    ax.plot(time, angle, color="blue", linewidth=2)
    
    ax.set_xlabel("Time in seconds")
    ax.set_ylabel("Angle (º)")
    ax.set_title("Airplane - Angle Theta in Time")
    
    ax.grid(True)
    plt.tight_layout()
    plt.savefig("grafico.png", dpi=300, bbox_inches='tight')
    plt.savefig("./plots/time_and_angle.png", dpi=300, bbox_inches='tight')
    plt.show()

def main():
    plot_position_and_altitude()
    plot_time_and_altitude()
    plot_time_and_position()
    plot_time_and_angle()

if __name__ == "__main__":
    main()