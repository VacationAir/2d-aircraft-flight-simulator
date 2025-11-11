// =====================================================
// Aircraft class — 2d aircraft flight simulator
// Author: VacationAir 
// Latest revision: 11/11/2025 
// =====================================================



#include <iostream>
#include <cmath>


class Aircraft {
private:
    // Physical attributes
    double mass;           // Aircraft mass (kg)
    double position;       // Horizontal position (m)
    double speed;          // Total speed (m/s)
    double acceleration;   // Total acceleration (m/s²)
    double vs;             // Vertical speed (m/s)
    double altitude;       // Altitude (m)
    double theta;          // Pitch angle (degrees)
    double theta_rad;      // Pitch angle (radians)
    double vx;             // Horizontal velocity (m/s)
    double vy;             // Vertical velocity (m/s)
    double power;          // Engine power (W)
    double thrust;         // Thrust force (N)
    double wing_area;      // Wing area (m²)
    double CL;             // Lift coefficient
    double CD;             // Drag coefficient
    double rho;            // Air density (kg/m³)
    double eep;            // Estimated engine performance factor
public:
    Aircraft(double mass, double eep, double position, double speed, double altitude,double theta, double power, double wingarea)
    :   mass(mass),
        eep(eep),
        position(position), 
        speed(speed), 
        acceleration(0),
        vs(0),
        altitude(altitude), 
        theta(theta),
        theta_rad(theta*M_PI/180),
        vx(speed*cos(theta_rad)), 
        vy(speed*sin(theta_rad)), 
        power(power), 
        thrust(power/speed), 
        wing_area(wingarea), 
        CL(0.24), 
        CD(0.03), 
        rho(1.225) {}    

    void update(double dt){
        speed = sqrt(vx*vx + vy*vy);
        vs = vy;
        theta_rad = atan2(vy, vx);
        theta = theta_rad*180/M_PI;
        thrust = eep * power/ std::max(speed, 1.0); 
        // Forces
        double lift = 0.5 * CL * rho * speed * speed * wing_area;
        double drag = 0.5 * CD * rho * speed * speed * wing_area;
        double weight = mass * 9.81;
        double Fx = thrust * cos(theta_rad) - drag * cos(theta_rad) - lift * sin(theta_rad);
        double Fy = thrust * sin(theta_rad) - drag * sin(theta_rad) + lift * cos(theta_rad) - weight;

        // Acceleration components 
        double ax = Fx / mass;
        double ay = Fy / mass;
        acceleration = sqrt(ax*ax + ay*ay);

        // Integrate in order to calculate velocity.
        vx += ax * dt;
        vy += ay *dt;
        position += vx * dt;
        altitude += vy * dt;
        std::cout << "Speed: " << speed << "m/s\n";
        std::cout << "Position: " << position << "m\n";
        std::cout << "Altitude: " << altitude << "m\n";
        std::cout << "Angle theta: " << theta << " in degrees\n";

    }
    // ======================
    // Get and Set functions
    // ======================
    
    double getAltitude(){
        return altitude;
    }
    double getSpeed(){
        return speed;
    }
    double getPosition(){
        return position;
    }
    double getAngleThetaDegree(){
        return theta;
    }
    double getVs(){
        return vs;
    }
    double getAcceleration(){
        return acceleration;
    }
};

