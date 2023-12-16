/*
 *Assignment 1
 *Tanishk Singh Bisht (156476210)
 *Fawaz Faruk Sapa (161792213)
*/

#ifndef _INDUCTOR_H_
#define _INDUCTOR_H_

#include "Component.h"

class Inductor : public Component {
private:
    double inductance;
    double current[2]; // Array to store current for two time steps
public:
    // Constructor for Inductor
    Inductor(double _inductance, float _Red, float _Green, float _Blue, const std::string& _name)
        : inductance(_inductance){
        Red = _Red;
        Blue = _Blue;
        Green = _Green;
        name = _name;
        current[0] = 0.0;
        current[1] = 0.0;
    }
    // Get the name of the inductor
    virtual std::string GetName() const override {
        return name;
    }
    // Get the red color component for visualization
    virtual float red() override {
        return Red;
    }
    // Get the green color component for visualization
    virtual float green() override {
        return Green;
    }
    // Get the blue color component for visualization
    virtual float blue() override {
        return Blue;
    }
    // Update function for the inductor to store the current from the current time step
    virtual void Update() override {
        current[0] = current[1];
    }
    // Calculate and return the voltage across the inductor based on current and time step
    virtual double GetVoltage(double _current, double timestep) override {
        current[1] = _current; // Store the current value for the current time step
        return inductance * (current[1] - current[0]) / timestep;
    }
    // Display the state of the inductor, showing the current for the current time step
    virtual void Display() override {
        std::cout << "Inductor " << name << ": Current = " << current[1] << " A" << std::endl;
    }
};

#endif // _INDUCTOR_H_
