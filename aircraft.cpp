// =====================================================
// Aircraft class — models simple flight dynamics
// Author: VacationAir 
// Latest revision: 5/11/2025 
// =====================================================



#include <iostream>
#include <cmath>


class Aircraft {
private:
    //Atributes
    double mass;
    double position;
    double speed;
    double altitude; // In meters, not feet
    double theta; // Degrees
    double theta_rad;
    double vx;
    double vy;
    double power;
    double thrust;
    double wing_area;
    double CL; //   Lift coefficient
    double CD; //   Drag coefficient
    double rho; //  Air density
public:
    Aircraft(double mass, double position, double speed, double altitude,double theta, double power, double wingarea)
    :   mass(mass),
        position(position), 
        speed(speed), 
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
        theta_rad = atan2(vy, vx);
        theta = theta_rad*180/M_PI;
        thrust = power/speed; 
        // Forces
        double lift = 0.5 * CL * rho * speed * speed * wing_area;
        double drag = 0.5 * CD * rho * speed * speed * wing_area;
        double weight = mass * 9.81;
        double Fx = thrust * cos(theta_rad) - drag * cos(theta_rad) - lift * sin(theta_rad);
        double Fy = thrust * sin(theta_rad) - drag * sin(theta_rad) + lift * cos(theta_rad) - weight;

        // Acceleration components 
        double ax = Fx / mass;
        double ay = Fy / mass;

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
};

