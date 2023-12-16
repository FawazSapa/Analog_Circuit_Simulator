//AnalogCircuit.cpp - function definitions for the analog circuit
//
// 20-May-22  M. Watler         Created.
// 27-May-22  M. Watler         Added graphical display.

/*
 *Assignment 1
 *Tanishk Singh Bisht (156476210)
 *Fawaz Faruk Sapa (161792213)
*/


#include <iomanip>//setw
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>//M_PI
#include <stdlib.h>//abs

#include "AnalogCircuit.h"
#include "Capacitor.h"
#include "Inductor.h"
#include "Resistor.h"

using namespace std;

int xpos, ypos;
int windowWidth, windowHeight;
double scalingFactor;
double cap = 0;
double ind = 0;
double res = 0;


void start() {
	cout << "BEGIN" << endl;
	AnalogCircuit circuit("RLC.dat");
	circuit.run();
	cout << "Press any key + ENTER to end..." << endl;
	char key;
	cin >> key;
	glutLeaveMainLoop();
	cout << "DONE!" << endl;
}

void AnalogCircuit::display(float xpos, float ypos, float R, float G, float B) {//draw a point on the screen
	//	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(R, G, B);//RGB
	glBegin(GL_POINTS);
	glVertex2f(xpos, ypos);
	glEnd();
	glFlush();
}

AnalogCircuit::AnalogCircuit(string filename) {//dump data to filename, initialize variables
	fout.open(filename);
	//Check if the file is open if not throw an error
	if (!fout.is_open()) {
		std::cerr << "Error opening file for writing: " << filename << std::endl;
	}

}


void AnalogCircuit::run() {
	component.push_back(new Capacitor(0.000100, 0.0, 1.0, 0.0, "C1"));//100uF, Green
	component.push_back(new Inductor(0.020, 0.0, 0.0, 1.0, "L1"));//20mH, Blue
	component.push_back(new Resistor(10, 1.0, 0.0, 0.0, "R1"));//10ohm, Red

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);  // White color for lines

	// Horizontal line
	glBegin(GL_LINES);
	glVertex2f(0, scalingFactor * windowHeight / 2);
	glVertex2f(windowWidth, scalingFactor * windowHeight / 2);
	glEnd();

	// Vertical line
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(1, windowHeight);
	glEnd();

	

	// Horizontal line markers
	glColor3f(1.0, 1.0, 1.0); 
	glBegin(GL_LINES);
	for (int i = 1; i < 10; i++) {
		float xPos = static_cast<float>(i) / 10 * windowWidth;
		glVertex2f(xPos, scalingFactor * windowHeight / 2 - 5);
		glVertex2f(xPos, scalingFactor * windowHeight / 2 + 5);
	}
	glEnd();

	// Vertical line markers
	glBegin(GL_LINES);
	for (int i = 1; i < 10; i++) {
		float yPos = static_cast<float>(i) / 10 * windowHeight;
		glVertex2f(scalingFactor, yPos);
		glVertex2f(scalingFactor+10, yPos);
	}
	glEnd();

	

	// Display each component's name and color
	int textY = 500; // Initial Y position
	int textX = windowWidth - 25; // Initial X position
	for (auto& comp : component) {
		string name = comp->GetName();
		float compRed = comp->red();
		float compGreen = comp->green();
		float compBlue = comp->blue();
		glColor3f(compRed, compGreen, compBlue);
		glRasterPos2f(textX, textY); // text position
		for (char c : name) {
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c); // Display the character
		}

		textY -= 20; // Move to the next line
	}
	

	//Run the simulation for the first 0.06 seconds (timeMax is 0.1 sec)
	//Dump data to a file as well as display on the screen
	for (double time = 0.0; time < 0.6 * timeMax; time += T) {
		double V = Vpeak * sin(2.0 * M_PI * freq * time);
		//Display the applied Voltage
		double xpos = time * windowWidth / timeMax;
		double ypos = (windowHeight * V / Vpeak) / 2.0 + scalingFactor * windowHeight / 2.0;
		AnalogCircuit::display(xpos, ypos, 1.0, 1.0, 1.0);

		// Calculate and update the current for each component
		CostFunctionV(I, V,time,xpos);
		
	}

	//Run the simulation to the end (timeMax is 0.1 sec)
	//Dump data to a file as well as display on the screen
	for (double time = 0.6 * timeMax; time < timeMax; time += T) {
		double V = 0.0;
		//Display the applied Voltage
		double xpos = time * windowWidth / timeMax;
		double ypos = (windowHeight * V / Vpeak) / 2.0 + scalingFactor * windowHeight / 2.0;
		AnalogCircuit::display(xpos, ypos, 1.0, 1.0, 1.0);
		//...
		CostFunctionV(I, V,time,xpos);
		
	}
}

void AnalogCircuit::CostFunctionV(double& current, double voltage,double time,double xpos) {
	double I1 = current;
	double J1 = 0.0;
	double J0 = 0.0;
	double alpha = 1.0;

	do {
		double sumVoltage = 0.0;
		list<Component*>::iterator it;
		for (it = component.begin(); it != component.end(); ++it) {
			double Vcomponent = (*it)->GetVoltage(I1, T);
			sumVoltage += Vcomponent;
		}
		J1 = sumVoltage - voltage;
		//Reduce alpha if J1 and J0 are of opposite signs or are equal to each other
		if ((abs(J0 - J1) != (J0 - J1)) || J0 == J1)alpha /= 2.0;

		if (abs(J1) > tolerance) {
			if (J1 < 0) {//increase the current
				I1 += alpha;
			}
			else {
				I1 -= alpha;
			}
			J0 = J1;
		}
		if (alpha < tolerance / 1000000.0) {//reset alpha
			alpha = ((double)rand() / (RAND_MAX)) + 0.5;//between 0.5 and 1.5
		}
	} while (abs(J1) > tolerance);
	
	fout << setw(12) << I1;
	list<Component*>::iterator it;
	for (it = component.begin(); it != component.end(); ++it) {
		fout << setw(12) << (*it)->GetVoltage(I1, T);
		ypos = (windowHeight * (*it)->GetVoltage(I1, T) / Vpeak) / 2.0 + scalingFactor * windowHeight / 2.0;
		//Get the RGB input from each component
		float compRed = (*it)->red();
		float compGreen = (*it)->green();
		float compBlue = (*it)->blue();
		//Display each components, Plot the graph
		display(xpos,ypos,compRed, compGreen, compBlue);

		//Check the components name name and dump the data from each component into file RLC.dat
		if ((*it)->GetName() == "C1") {
			cap = (*it)->GetVoltage(I1, T);
			dumpDataToFile(T, voltage, I1, cap, ind, res);
		}
		else if ((*it)->GetName() == "L1")
		{
			ind = (*it)->GetVoltage(I1, T);
			dumpDataToFile(T, voltage, I1, cap, ind, res);
		}
		else if ((*it)->GetName() == "R1")
		{
			res = (*it)->GetVoltage(I1, T);
			dumpDataToFile(T, voltage, I1, cap, ind, res);
		}
		//Display the state of each component in the terminal
		(*it)->Display();
		//Update the current or voltage according to the components
		(*it)->Update();
	}
	fout << endl;

	current = I1;
}
//perform cleanup
AnalogCircuit::~AnalogCircuit() {
	fout.close();
	for (auto& comp : component) {
		delete comp;
	}
	component.clear();
}
