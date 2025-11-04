#include <iostream>
#include <cmath>


// =====================================================
// Aircraft class — models simple flight dynamics
// =====================================================

class Aircraft {
private:
    //Atributes
    double mass;
    double position;
    double speed;
    double power;
    double thrust;
    double wing_area;
    double CL; //   Lift coefficient
    double CD; //   Drag coefficient
    double rho; //  Air density
public:
    Aircraft(double mass, double position, double speed, double power, double wingarea)
    : mass(mass), position(position), speed(speed), power(power), thrust(power/speed), wing_area(wingarea), 
    CL(0.5), CD(0.03), rho(1.225) {}

    void update(double dt){
        // Forces

        double lift = 0.5 * CL * rho * speed * speed * wing_area;
        double drag = 0.5 * CD * rho * speed * speed * wing_area;
        double weight = mass * 9.81;
        
        // To simplify, the plane flies horizontally; only thrust and drag matter
        thrust = power/speed;
        double net_horizontal_force = thrust - drag;
        double net_vertical_force = lift - weight;
        double acceleration = net_horizontal_force / mass;

        // Integrate in order to calculate velocity
        speed += acceleration * dt;
        position += speed * dt;

        std::cout << "Speed: " << speed << "m/s\n";
        std::cout << "Position: " << position << "m\n";

    }
};
