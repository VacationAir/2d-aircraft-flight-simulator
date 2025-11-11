// =====================================================
// Main — 2D Aircraft Flight Simulator
// Author: VacationAir 
// Latest revision: 11/11/2025 
// =====================================================

#include <iostream>
#include <fstream>
#include "aircraft.cpp"

void runOpenGLSimulation(int argc, char** argv);

// Helper function: write flight data to CSV
void logFlightData(double t, double position, double altitude, double speed, double acceleration, double vs, double angle) {
    static bool header_written = false;
    std::ofstream file("flight_data.csv", std::ios::app);

    if (!header_written) {
        file << "time,position,altitude,speed,acceleration,vertical_speed,angle\n";
        header_written = true;
    }

    file << t << "," 
         << position << "," 
         << altitude << "," 
         << speed << "," 
         << acceleration << "," 
         << vs << "," 
         << angle << "\n";
}

int main(int argc, char** argv) {
    // Clear previous flight data
    std::ofstream("flight_data.csv").close();

    // Create aircraft object (Cessna 152 parameters)
    Aircraft cessna152(600, 0.75, 0, 46.3, 610, 4.1, 82000, 14.9);

    // Numerical integration: simulate 1 minute at dt = 0.01 s
    const double dt = 0.01;
    const double simulation_time = 60.0;

    std::cout << "=== Running Numerical Simulation ===" << std::endl;

    for (double t = 0; t < simulation_time; t += dt) {
        cessna152.update(dt);
        logFlightData(
            t,
            cessna152.getPosition(),
            cessna152.getAltitude(),
            cessna152.getSpeed(),
            cessna152.getAcceleration(),
            cessna152.getVs(),
            cessna152.getAngleThetaDegree()
        );

        // Optional console output
        if (static_cast<int>(t * 100) % 100 == 0) { // print every 1 second
            std::cout << "Time: " << t << " s, Altitude: " 
                      << cessna152.getAltitude() << " m, Speed: " 
                      << cessna152.getSpeed() << " m/s" << std::endl;
        }
    }

    // Ask user if they want to plot the results
    std::string input_plot;
    std::cout << "\nPlot results? (Y/N): ";
    std::cin >> input_plot;
    if (input_plot == "Y" || input_plot == "y") {
        system("python3 plot_results.py");
    }

    // Ask user if they want to run the OpenGL simulation
    std::string input_sim;
    std::cout << "Run OpenGL simulation? (Y/N): ";
    std::cin >> input_sim;
    if (input_sim == "Y" || input_sim == "y") {
        std::cout << "Launching OpenGL animation..." << std::endl;
        runOpenGLSimulation(argc, argv);
    }

    std::cout << "Simulation complete." << std::endl;
    return 0;
}
