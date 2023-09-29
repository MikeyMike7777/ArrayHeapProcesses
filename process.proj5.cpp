/**
* file: process-proj5.h
* author: Michael Mathews
* course: CSI 3334
* assignment: project 5
* due date: April 8, 2022
* version: 11.7
 
 This file defines the Process class and its functions
*/

#include "process-proj5.h"

/* Process default constructor
*  parameters:
*      none
*  return value: none
*
* This function creates the base Process and sets the id
*/
Process::Process(int theId){
    this->id = theId;
    this->submissionTime = 0;
    this->deadline = 0;
    this->requiredTime = 0;
    this->information = "";
}

/* run
*  parameters:
*      currentSystemTime - gives the current time in the program
*  return value: currentSystemTime gives the time in the system after running
*  a program, or doesn't change it if a Process has been skipped
*
* This function runs or skips a Process based on it's deadline
*/
int Process::run(int currentSystemTime) const{
    //skip if process cant finish in time, run if can finish
    if(currentSystemTime+this->requiredTime > this->deadline){
        cout << "skipping process id " << this->id << " at "
             << currentSystemTime << endl;
    }
    else{
        cout << "running process id " << this->id << " at "
             << currentSystemTime << endl;
        cout << this->information << endl;
        currentSystemTime += this->requiredTime;
    }
    return currentSystemTime;
}

/* canComplete
*  parameters:
*      currentSystemTime - gives the current time in the program
*  return value: comp - holds true if a process can finish before a deadline
*
* This function lets the programmer know if a process can be completed in time
*/
bool Process::canComplete(int currentSystemTime) const{
    bool comp = false;
    if(currentSystemTime+this->requiredTime < this->deadline){
        comp = true;
    }
    return comp;
}

/* getId
*  parameters:
*      none
*  return value: id which holds the processs's location in order of insertion
*
* This function gives a Process's id
*/
int Process::getId() const{
    return this->id;
}

/* getSubmissionTime
*  parameters:
*      none
*  return value: submissionTime which holds a process's time of submission
*
* This function gives a Process's submissionTime
*/
int Process::getSubmissionTime() const{
    return this->submissionTime;
}

/* operator<
*  parameters:
*      p - Process to compare to implicit Process
*  return value: lessThan - true if the first Process is less than the second
*
* This function defines the < operator for the Process class
*/
bool Process::operator<(Process const &p) const{
    bool lessThan = false;
    if(this->deadline < p.deadline){
        lessThan = true;
    }
    else if(this->deadline == p.deadline){
        if(this->requiredTime < p.requiredTime){
            lessThan = true;
        }
        else if(this->requiredTime == p.requiredTime){
            if(this->id < p.id){
                lessThan = true;
            }
        }
    }
    return lessThan;
}

/* operator>>
*  parameters:
*      p - Process to read in
       is - input stream to read in through
*  return value: is - input stream full of values read in
*
* This function defines the >> operator for the Process class to help read in
* Processes
*/
istream &operator>>(istream &is, Process &p){
    const int SPACE = 1;
    is >> p.submissionTime >> p.deadline >> p.requiredTime;
    cin.ignore(SPACE);
    getline(cin, p.information);
    return is;
}
