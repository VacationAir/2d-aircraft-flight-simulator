// =====================================================
// Main class — 2d aircraft flight simulator
// Author: VacationAir 
// Latest revision: 6/11/2025 
// =====================================================

#include <iostream>
#include "aircraft.cpp"
#include <fstream>


void create_flight_data_table(double t, double position, double altitude, double speed, double acceleration, double vs, double angle) {
    static bool header_written = false;
    std::ofstream file("flight_data.csv", std::ios::app); 

    if (!header_written) {
        file << "time,position,altitude,speed,acceleration,vertical_speed,angle\n";
        header_written = true;
    }

    file << t << "," << position << "," << altitude << "," << speed << "," << acceleration << "," << vs << "," << angle << "\n";
}

int main(){
    Aircraft cessna152(600,0.75, 0, 46.3, 610, 4.1,  82000, 14.9); // Parameters for a cesssna 152 at 90 Knots (46.3 m/s) at 2000ft (610m) with a 4.1º angle
    double dt = 0.01; // seconds
    std::ofstream("flight_data.csv").close();
    for(double i = 0; i < 60; i+= dt){ // 1 Minute -> 60 seconds
        cessna152.update(dt);
        create_flight_data_table(i,cessna152.getPosition(), cessna152.getAltitude(), cessna152.getSpeed(), cessna152.getAcceleration(), cessna152.getVs(), cessna152.getAngleThetaDegree());
        std::cout << "Time: " << i << " seconds\n";
        
    }
    system("python3 plot_results.py");
    return 0;
}
