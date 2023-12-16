/*
 *Assignment 1
 *Tanishk Singh Bisht (156476210)
 *Fawaz Faruk Sapa (161792213)
*/

#ifndef _CAPACITOR_H_
#define _CAPACITOR_H_

#include "Component.h"

class Capacitor : public Component {
private:
    double capacitance;
    double voltage[2]; // Array to store voltage at two time steps
public:
    // Constructor for Capacitor
    Capacitor(double _capacitance, float _Red, float _Green, float _Blue, const std::string& _name)
        : capacitance(_capacitance){
        Red = _Red;
        Blue = _Blue;
        Green = _Green;
        name = _name;
        voltage[0] = 0.0;
        voltage[1] = 0.0;
    }
    // Get the name of the capacitor
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
    // Update function to advance the voltage to the next time step
    virtual void Update() override {
        voltage[0] = voltage[1];
    }
    // Calculate and update the voltage of the capacitor based on current and timestep
    virtual double GetVoltage(double _current, double timestep) override {
        voltage[1] = voltage[0] + (_current * timestep) / capacitance;
        return voltage[1];
    }
    // Display the state of the capacitor
    virtual void Display() override {
        std::cout << "Capacitor " << name << ": Voltage = " << voltage[1] << " V" << std::endl;
    }
};

#endif // _CAPACITOR_H_
