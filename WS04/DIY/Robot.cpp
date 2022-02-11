/* ------------------------------------------------------
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
Date    Sun Feb 13 2022

Workshop 4 part 2
Module: Robot
Desc:   Module for Robot object which displays the details of the robots in the designated areas
Filename: Robot.cpp
-----------------------------------------------------------*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

#include "Robot.h"

namespace sdds {

	void Robot::setSafeEmpty() {
		m_name = nullptr;
		m_location = nullptr;
		m_weight = 0;
		m_width = 0;
		m_height = 0;
		m_speed = 0;
		m_isDeployed = false;
	}

	void Robot::deallocMemory() {
		delete [] m_name;
		m_name = nullptr;
		delete [] m_location;
		m_location = nullptr;
	}

	bool Robot::validateRobotInfo(const char* name, const char* location, double weight, double width, double height, double speed) const {
		bool result = false;

		// checks if all robot info information pass validation
		if (weight > 0 && weight < MAX_DOUBLE_EXCLUSIVE &&
			width > 0 && width < MAX_DOUBLE_EXCLUSIVE &&
			height > 0 && height < MAX_DOUBLE_EXCLUSIVE &&
			speed > 0 && speed < MAX_DOUBLE_EXCLUSIVE &&
			validateCString(name, 1, MAX_NAME_LEN) &&
			validateCString(location, 1, MAX_LOCATION_LEN)
			) {
			result = true;	// everything passed validation
		}

		return result;
	}

	Robot::Robot() {
		setSafeEmpty();		// set member variables to safe empty state
	}

	Robot::Robot(const char* name, const char* location, double weight, double width, double height, double speed, bool isDeployed) {
		setSafeEmpty();		// set member variables to safe empty state
		set(name, location, weight,  width, height, speed, isDeployed);	// validate arguments and set values to data members, set to safe empty state if validation fails
	}

	Robot::~Robot() {
		deallocMemory();
	}

	bool Robot::isValid() const {
		// check if member variables pass validation
		return validateRobotInfo(m_name, m_location, m_weight, m_width, m_height, m_speed);
	}

	char* Robot::getName() const {
		return m_name;
	}

	char* Robot::getLocation() const {
		return m_location;
	}

	bool Robot::isDeployed() const {
		return m_isDeployed;
	}

	double Robot::getSpeed() const {
		return m_speed;
	}

	bool Robot::setLocation(const char* location) {
		bool result = false;

		if (validateCString(location, 1, MAX_LOCATION_LEN)) {	// only proceed to set the location if it passes validation
			delete [] m_location;	// dealloc memory of prev location value if any
			m_location = nullptr;

			m_location = new (nothrow) char[strlen(location)+1];	// allocate dynamic memory for location based on length of argument string

			if (m_location != nullptr) {

				strcpy(m_location, location);				// copy argument value to address of newly allocated memory

				result = true;
			}
		}

		return result;
	}

	void Robot::setDeployed(bool isDeployed) {
		m_isDeployed = isDeployed;	// no need to validate boolean value since it can only be true or false
	}

	Robot& Robot::set(const char* name, const char* location, double weight, double width, double height, double speed, bool isDeployed) {
		deallocMemory();	// deallocate memory if any

							// check if arguments are valid
		if (validateRobotInfo(name, location, weight, width, height, speed)) {

			// set member variables to arguments

			m_name = new char[strlen(name)+1];			// allocate dynamic memory for name based on length of argument string
			m_location = new char[strlen(location)+1];	// allocate dynamic memory for location based on length of argument string

			strcpy(m_name, name);					// copy argument value to address of newly allocated memory
			strcpy(m_location, location);			// copy argument value to address of newly allocated memory

			m_weight = weight;
			m_width = width;
			m_height = height;
			m_speed = speed;
			m_isDeployed = isDeployed;

		} else {	// argument(s) are not valid
			setSafeEmpty();		// set member variables to safe empty state
		}

		return *this;
	}

	bool Robot::display() const {
		bool result = false;

		if (isValid() == true) {

			streamsize oldPrecision = cout.precision();	// save precision

			cout.setf(ios::left);	// set left align
			cout << "| ";

			cout.width(10);
			cout << m_name;			// print name

			cout << " | ";

			cout.width(15);
			cout << m_location;		// print location

			cout << " | ";

			cout.unsetf(ios::left);	// unset left align
			cout.setf(ios::fixed);	// set fixed format
			cout.precision(1);		// change precision to one decimal place

			cout.width(6);
			cout << m_weight;		// print weight

			cout << " | ";

			cout.width(6);
			cout << m_width;		// print width

			cout << " | ";

			cout.width(6);
			cout << m_height;		// print height

			cout << " | ";

			cout.width(6);
			cout << m_speed;		// print speed

			cout << " | ";

			cout.unsetf(ios::fixed);		// unset fixed format
			cout.precision(oldPrecision);	// change precision back
			cout.setf(ios::left);			// set left align

			cout.width(8);
			cout << (m_isDeployed ? "YES" : "NO");	// print yes if deployed, no if not deployed

			cout.unsetf(ios::left);			// unset left align

			cout << " |" << endl;

			result = true;
		}

		return result;
	}

	bool validateCString(const char* stringPtr, int min, int max) {
		bool result = false;
		int stringLen = 0;

		// checks if all robot info information pass validation
		if (stringPtr != nullptr) {
			// get length of string cstring
			stringLen = strlen(stringPtr);

			// check if cstring length meets requirements
			if (stringLen >= min && stringLen <= max) {
				result = true;
			}
		}

		return result;
	}

	void printReportHeader() {
		cout << "                        ------ Robot Control Room -----" << endl;
		cout << "                    ---------------------------------------" << endl;
		cout << "| Robot ID   | Location        | Weight |  Width | Height |  Speed | Deployed |" << endl;
		cout << "|------------+-----------------+--------+--------+--------+--------+----------|" << endl;
	}



	void printReportSummary(const Robot robot[], int num_robots, int numDeployed, int fastest) {
		cout << "|=============================================================================|" << endl;
		cout << "| SUMMARY:                                                                    |" << endl;
		
		cout << "| ";

		cout.setf(ios::left);	// set left align

		cout.width(75);
		cout << to_string(numDeployed) + "  robots are deployed.";	// by converting the int to string we can ensure the formatting is
																	// corect no matter how many digits the integer is

		cout.unsetf(ios::left);	// unset left align

		cout << " |" << endl;

		cout << "| The fastest robot is:                                                       |" << endl;
		cout << "| Robot ID   | Location        | Weight |  Width | Height |  Speed | Deployed |" << endl;
		cout << "|------------+-----------------+--------+--------+--------+--------+----------|" << endl;
		robot[fastest].display();
		cout << "|=============================================================================|" << endl;
	}

	int conrtolRooomReport(const Robot robot[], int num_robots) {
		int index = -1;
		bool invalidBotFound = false;
		int fastestIndex = -1;	// store index of fastest robot so far
		int fastestSpeed = 0;	// store fastest speed so far
		int speed = 0;
		int numDeployedBots = 0;

		printReportHeader();

		// generate report
		for (int i = 0; i < num_robots && !invalidBotFound; i++) {

			if (robot[i].display()) { // display printed successfully, robot was valid

									  // check if robot is deployed
				if (robot[i].isDeployed()) {
					numDeployedBots++;		// increment counter of deployed bots
				}

				// check if robot speed beats the current speed record
				speed = robot[i].getSpeed();
				if (speed > fastestSpeed) {
					fastestSpeed = speed;	// update current record
					fastestIndex = i;		// update record holder
				} 

			} else { // display returned false, robot was invalid
				invalidBotFound = true;		// quit the loop when invalid robot found
				index = i;	// set return value to index
			}


		}

		// generate summary only if no invalids were found
		if (!invalidBotFound) {
			printReportSummary(robot, num_robots, numDeployedBots, fastestIndex);
		}

		return index;
	}
}