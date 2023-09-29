/**
* file: driver-proj5.cpp
* author: Michael Mathews
* course: CSI 3334
* assignment: project 5
* due date: April 8, 2022
* version: 11.7
 
 This file uses the arrayHeap and Process classes to perform functions
*/

#include <iostream>
#include "arrayheap-student-proj5.h"
#include "process-proj5.h"

/* main
*  parameters:
*      argc -- the number of arguments from the command line
*      argv -- the command line argument values
*  return value: 0 (indicating a successful run)
*
* This project uses reads in processes and completes them based on which one's need to be done first.
* Implements ArrayHeap class and Process class.
*/

int main(int argc, const char * argv[]) {
    int currTime = 0, prevTime, numProcesses, numSkip = 0;
    ArrayHeap<Process> pq;
    
    cin >> numProcesses;
    
    //while reading in (also increments id)
    for(int i = 0; i < numProcesses; i++){
        //set id and read in
        Process curr(i);
        cin >> curr;
        //check submission time - reached
        if(curr.getSubmissionTime() <= currTime){
            //place on heap
            pq.insert(curr);
        }
        //check submission time - not reached
        else{
            //hold in local variable, check heap for processes
            if(pq.getNumItems() > 0){
                //keep running until submission time reached
                while(pq.getNumItems() > 0 and curr.getSubmissionTime() > currTime){
                    //if can process can finish before deadline, run/skip it
                    prevTime = currTime;
                    currTime = pq.getMinItem().run(currTime);
                    //if skipped, count it
                    if(currTime == prevTime){
                        currTime++;
                        numSkip++;
                    }
                    pq.removeMinItem();
                    
                    //if new heap is empty and less than curr submission time
                    if(pq.getNumItems() == 0 and
                       currTime < curr.getSubmissionTime()){
                        currTime = curr.getSubmissionTime();
                    }
                }
                //add to heap
                pq.insert(curr);
            }
            else{
                currTime = curr.getSubmissionTime();
                pq.insert(curr);
            }
        }
    }
    
    //if done reading in
    while(pq.getNumItems() > 0){
        //get highest priority item and run/skip it then remove from heap
        prevTime = currTime;
        currTime = pq.getMinItem().run(currTime);
        //if skipped, count it
        if(currTime == prevTime){
            currTime++;
            numSkip++;
        }
        pq.removeMinItem();
    }
    
    //summary
    cout << "final clock is                 " << currTime << endl;
    cout << "number of processes run is     " << numProcesses-numSkip << endl;
    cout << "number of processes skipped is " << numSkip << endl;
    
    return 0;
}
