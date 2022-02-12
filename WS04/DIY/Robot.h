/* ------------------------------------------------------
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
Date    Sat Feb 12 2022

Workshop 4 part 2
Module: Robot
Desc:   Module for Robot object which displays the details of the robots in the designated areas
Filename: Robot.h
-----------------------------------------------------------*/

#ifndef SDDS_ROBOT_H
#define SDDS_ROBOT_H 

namespace sdds {

    const int MAX_NAME_LEN = 10;
    const int MAX_LOCATION_LEN = 15;
    const double MAX_DOUBLE_EXCLUSIVE = 9999.95;

    class Robot {
        char* m_name;
        char* m_location;
        double m_weight;
        double m_width;
        double m_height;
        double m_speed;
        bool m_isDeployed;

        // initialize all member variables to safe empty state
        void setSafeEmpty();

        // deallocate memory for name, location, 
        void deallocMemory();

        // checks a set of robot info to see if it passes validation
        bool validateRobotInfo(const char* name, const char* location, double weight, double width, double height, double speed) const;

    public:

        // initialize member variables
        Robot();

        // Dynamically store name, location,  arguments in corresponding member variables
        // Store year, code, weight arguments in corresponding member variables if provided and pass validation
        // If any argument provided does not pass validation the object will be set to safe empty state
        Robot(const char* name, const char* location, double weight, double width, double height, double speed, bool isDeployed);

        // deallocate the dynamically allocated memory in name, location
        ~Robot();

        // checks whether this object has valid values
        bool isValid() const;

        // returns robot name
        char* getName() const;

        // returns robot location
        char* getLocation() const;

        // returns true if robot is deployed, false if not
        bool isDeployed() const;

        // returns robot speed
        double getSpeed() const;

        // set robot location
        // returns true if set successfully, false otherwise
        bool setLocation(const char* location);

        // set robot deployment status
        void setDeployed(bool isDeployed);

        // set robot info
        // first deallocate all the allocated memory and then sets the attributes to the corresponding arguments exactly like the 6 argument constructor
        // Returns the reference of the current object
        Robot& set(const char* name, const char* location, double weight, double width, double height, double speed, bool isDeployed);

        // if the object is valid prints the values of all the member variables
        // returns true if printing successful, false otherwise
        bool display() const;
    };

    // Returns true if pointer is not null and points to address of cstring within length requirements
    bool validateCString(const char* stringPtr, int min, int max);
    
    // Prints header for control room report
    void printReportHeader();

    // Prints summary for control room report
    void printReportSummary(const Robot robot[], int num_robots, int numDeployed, int fastest);

    // This function receives an array of robots and prints a report of their information and a summary that prints the total number of
    // deployed robots and the information of the fastest robot in the array
    // If during the printout of the array an invalid robot is detected, printing stops and the index of the invalid robot in the array is returned
    // If no Invalid robot is detected, the summary is printed and the value -1 is returned
    int conrtolRooomReport(const Robot robot[], int num_robots);
}

#endif // ! SDDS_ROBOT_H