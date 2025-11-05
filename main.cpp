#include <iostream>
#include "aircraft.cpp"

int main(){
    Aircraft cessna152(600, 0, 46.3, 610, 0,  82000, 14.9); // Parameters for a cesssna 152 at 90 Knots (46.3 m/s) at 2000ft (610m) with a 4.1º angle
    double dt = 0.01; // seconds
    for(double i = 0; i < 60; i+= dt){ // 1 Minute -> 60 seconds
        cessna152.update(dt);
        std::cout << "Time: " << i << " seconds\n";
    }
    return 0;
}
