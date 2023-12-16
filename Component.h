//Component.h - abstract base class for electronic components

//
// 19-May-22  M. Watler         Created.
// 27-May-22  M. Watler         Added graphical display.

/*
 *Assignment 1
 *Tanishk Singh Bisht (156476210)
 *Fawaz Faruk Sapa (161792213)
*/

#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include <iostream>

class Component {
protected:
	float Red;
	float Green;
	float Blue;
	std::string name;
public:
	virtual std::string GetName() const = 0;
	virtual void Update() = 0;
	virtual double GetVoltage(double _current, double timestep) = 0;
	virtual void Display() = 0;
	//Getter Functions for the RGB state of each component
	virtual float red()=0;
	virtual float green()=0;
	virtual float blue()=0;

};

#endif// _COMPONENT_H_
