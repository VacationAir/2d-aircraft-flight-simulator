#include <iostream>
#include "aircraft.cpp"

int main(){
    Aircraft cessna152(600, 0, 46.3, 82000, 14.9); // Parameters for a cesssna 152 at 90 Knots (46.3 m/s)
    double dt = 0.001; // seconds
    for(double i = 0; i < 60; i+= dt){ // 1 Minute -> 60 seconds
        cessna152.update(dt);
    }
    return 0;
}
