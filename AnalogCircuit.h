//AnalogCircuit.h - header file for the analog circuit
//
// 21-May-22  M. Watler         Created.
// 27-May-22  M. Watler         Added graphical display.

/*
 *Assignment 1
 *Tanishk Singh Bisht (156476210)
 *Fawaz Faruk Sapa (161792213)
*/


#ifndef _ANALOGCIRCUIT_H_
#define _ANALOGCIRCUIT_H_

#include <fstream>
#include <list>
#include <Windows.h>    
#include <gl/GL.h>    
#include <gl/GLU.h>    
#include <gl/glut.h>
#include <gl/freeglut.h>
#include<iomanip>
#include "Component.h"

extern int windowWidth, windowHeight;
extern double scalingFactor;

void start();

class AnalogCircuit {
	const double T = 0.000001;//timestep of 1uS
	const double timeMax = 0.1;
	const double tolerance = 0.0001;//
	const double freq = 50;//50Hz
	const double Vpeak = 10.0;//10V
	const int xoffset = 50;
	double I;
	std::list<Component*> component;//polymorphism with the STL
	std::ofstream fout;
	//Function to dump the specific data into a file
	void dumpDataToFile(double time, double voltage, double current, double V_cap,double V_ind,double V_res) {
		if (fout.is_open()) {
			fout << std::fixed << std::setprecision(7);
			fout << std::setw(12) << "Time" << std::setw(12) << "Applied Voltage" << std::setw(12) << "Current"
				<< std::setw(12) << "V_cap" << std::setw(12) << "V_ind" << std::setw(12) << "V_res" << std::endl;
			fout << std::setw(12) << time << std::setw(12) << voltage << std::setw(12) << current
				<< std::setw(12) << V_cap << std::setw(12) << V_ind << std::setw(12) << V_res << std::endl;
		}
	}
public:
	AnalogCircuit(std::string filename);//dump output data to a file
	static void display(float xpos,float ypos, float R, float G, float B);//display output data on the screen
	void run();
	void CostFunctionV(double& current, double V,double time,double xpos);
	~AnalogCircuit();
};

#endif// _ANALOGCIRCUIT_H_
