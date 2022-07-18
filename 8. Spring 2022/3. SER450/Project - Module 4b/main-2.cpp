/*************************************************************************
* main.cpp
*
* This file contains the main method used to run Project 4b.
* Much of the code has been adapted from my Project 4a submission.
*
* Author: Jacob Hreshchyshyn
*
**************************************************************************/
#include "Cpu.h"
#include "DataMemory.h"
#include "InstructionMemory.h"
#include "RegisterFile.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <sstream>
using namespace std;

// Below is the main method used to run the program and to assist in benchmarking.
int main(int argc, char *argv[])
{
    cout << "-------------- WELCOME TO THE PIPELINED SIMULATOR! ---------------\n";
    cout << "------------- Jacob Hreshchyshyn SER450 - Project 4b -------------\n\n";
    // The following code up to the file.close() instruction is responsible for
    // reading the filename parameter, using it to open the input text file, 
    // and parsing that file with the relevant hexcodes and bits indicating
    // what type of memory is being saved.
    Cpu cpu;
    ifstream file;
    int clocks = 100;
    if (argv[2]) {
        clocks = stoi(argv[2]);
    }
    file.open(argv[1]);
    if(!file.is_open())
    {
        return 1;
    }
    while(file) 
    {
        string instruction;
        string firstHex;
        string memBit;
        string secondHex;
        getline(file, instruction, '\n');
        //cout << instruction << endl;
        if(instruction != "")
        {
            firstHex = instruction.substr(0, 8);
            memBit = instruction.at(9);
            secondHex = instruction.substr(11, 19);
            unsigned int fHex;
            unsigned int sHex;
            // Assistance with hex conversions comes from this site:
            // https://stackoverflow.com/questions/4801146/c-hex-string-to-unsigned-int
            istringstream converter1(firstHex);
            istringstream converter2(secondHex);
            converter1 >> hex >> fHex;
            converter2 >> hex >> sHex;
            //cout << fHex << endl;
            //cout << sHex << endl;
            if(memBit == "0") 
            {
                cpu.setDmem(fHex, sHex);
            }
            else 
            {
                cpu.setImem(fHex, sHex);
            }
        }
    }
    file.close();
    int count = 0;
    // Running through 100 cycles
    for (int i = 0; i < clocks; i++)
    {
        cpu.dump();
        cout << "Clock Cycle: " << i << endl;
        cpu.update();
        count++;
    }
    cout << "Clock Cycle: " << count << endl;
    cpu.dump();
    return 0;
}