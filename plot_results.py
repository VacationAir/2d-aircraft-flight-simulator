#
# File:                 plot_results.py
# Author:               VacationAir
# Latest revition:      6/11/2025
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
    theta = data["angle"]
    
    fig, ax = plt.subplots(figsize=(8, 6))
    
    ax.plot(time, theta, color="blue", linewidth=2)
    
    ax.set_xlabel("Time in seconds")
    ax.set_ylabel("Angle (º)")
    ax.set_title("Airplane - Angle Theta in Time")
    
    ax.grid(True)
    plt.tight_layout()
    plt.savefig("grafico.png", dpi=300, bbox_inches='tight')
    plt.savefig("./plots/time_and_angle.png", dpi=300, bbox_inches='tight')
    plt.show()

def plot_speed_in_time():
    time = data["time"]
    speed = data["speed"]
    
    fig, ax = plt.subplots(figsize=(8, 6))
    
    ax.plot(time, speed, color="blue", linewidth=2)
    
    ax.set_xlabel("Time in seconds")
    ax.set_ylabel("Speed (m/s)")
    ax.set_title("Airplane - Speed in Time")
    
    ax.grid(True)
    plt.tight_layout()
    plt.savefig("grafico.png", dpi=300, bbox_inches='tight')
    plt.savefig("./plots/time_and_speed.png", dpi=300, bbox_inches='tight')
    plt.show()

def plot_vs_in_time():
    time = data["time"]
    vs = data["vertical_speed"]
    
    fig, ax = plt.subplots(figsize=(8, 6))
    
    ax.plot(time, vs, color="blue", linewidth=2)
    
    ax.set_xlabel("Time in seconds")
    ax.set_ylabel("Vertical speed (in m/s)")
    ax.set_title("Airplane - Vertical Speed in Time")
    
    ax.grid(True)
    plt.tight_layout()
    plt.savefig("grafico.png", dpi=300, bbox_inches='tight')
    plt.savefig("./plots/time_and_vs.png", dpi=300, bbox_inches='tight')
    plt.show()

def plot_vs_feet_in_time():
    time = data["time"]
    vs_in_meters = data["vertical_speed"]
    vs_in_feet = []
    for vs in vs_in_meters:
        vs_in_feet.append(vs*196.85)

    fig, ax = plt.subplots(figsize=(8, 6))
    
    ax.plot(time, vs_in_feet, color="blue", linewidth=2)
    
    ax.set_xlabel("Time in seconds")
    ax.set_ylabel("Vertical speed (in m/s)")
    ax.set_title("Airplane - Vertical Speed in Time")
    
    ax.grid(True)
    plt.tight_layout()
    plt.savefig("grafico.png", dpi=300, bbox_inches='tight')
    plt.savefig("./plots/time_and_vs.png", dpi=300, bbox_inches='tight')
    plt.show()

def plot_acceleration_in_time():
    time = data["time"]
    acceleration = data["acceleration"]

    fig, ax = plt.subplots(figsize=(8, 6))
    
    ax.plot(time, acceleration, color="blue", linewidth=2)
    
    ax.set_xlabel("Time in seconds")
    ax.set_ylabel("Acceleration (in m/s²)")
    ax.set_title("Airplane - Acceleration in Time")
    
    ax.grid(True)
    plt.tight_layout()
    plt.savefig("grafico.png", dpi=300, bbox_inches='tight')
    plt.savefig("./plots/time_and_acceleration.png", dpi=300, bbox_inches='tight')
    plt.show()

def plot_all_together():
    time = data["time"]
    
    fig, axes = plt.subplots(5, 1, figsize=(10, 12), sharex=True)
    
    # 1. Altitude
    axes[0].plot(time, data["altitude"], color="dodgerblue")
    axes[0].set_ylabel("Altitude (m)")
    axes[0].grid(True)
    
    # 2. Speed
    axes[1].plot(time, data["speed"], color="orange")
    axes[1].set_ylabel("Speed (m/s)")
    axes[1].grid(True)
    
    # 3. Angle (theta)
    axes[2].plot(time, data["angle"], color="green")
    axes[2].set_ylabel("Theta (°)")
    axes[2].grid(True)
    
    # 4. Vertical speed
    axes[3].plot(time, data["vertical_speed"] * 196.85, color="purple")
    axes[3].set_ylabel("V/S (ft/min)")
    axes[3].grid(True)
    
    # 5. Acceleration
    axes[4].plot(time, data["acceleration"], color="red")
    axes[4].set_ylabel("Accel (m/s²)")
    axes[4].set_xlabel("Time (s)")
    axes[4].grid(True)
    
    fig.suptitle("Flight Parameters vs Time", fontsize=14)
    plt.tight_layout(rect=[0, 0, 1, 0.97])
    plt.savefig("./plots/all_parameters_time.png", dpi=300, bbox_inches='tight')
    plt.show()


def main():
    plot_position_and_altitude()
    plot_time_and_altitude()
    plot_time_and_position()
    plot_time_and_angle()
    plot_speed_in_time()
    plot_vs_feet_in_time()
    plot_acceleration_in_time()
    plot_all_together()

if __name__ == "__main__":
    main()