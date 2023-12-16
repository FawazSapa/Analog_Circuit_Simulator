/*
 *Assignment 1
 *Tanishk Singh Bisht (156476210)
 *Fawaz Faruk Sapa (161792213)
*/

#ifndef _RESISTOR_H_
#define _RESISTOR_H_

#include "Component.h"

class Resistor : public Component {
private:
    double resistance;
    double current; // Current passing through the resistor
public:
    // Constructor for Resistor
    Resistor(double _resistance, float _Red, float _Green, float _Blue, const std::string& _name)
        : resistance(_resistance), current(0.0) {
        Red = _Red;
        Blue = _Blue;
        Green = _Green;
        name = _name;
    }
    // Get the name of the resistor
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
    // Update function for the resistor (not used in this case)
    virtual void Update() override {
    }
    // Calculate and return the voltage across the resistor based on current and resistance
    virtual double GetVoltage(double _current, double timestep) override {
        current = _current;
        return current * resistance;
    }
    // Display the state of the resistor, showing the current passing through it
    virtual void Display() override {
        std::cout << "Resistor " << name << ": Current = " << current << " A" << std::endl;
    }
};

#endif // _RESISTOR_H_
