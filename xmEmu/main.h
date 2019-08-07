#ifndef _MAIN_H_
#define _MAIN_H_

#include<iostream>
#include "cpu.h"
#include "debugger.h"
#include "Globals.h"
// #include "devices.h"
// #include "memory.h"

#define NUMDEVS 8 

struct Emulator{
    Debugger debugger;
    CPU cpu; //emulates a specific cpu (that specify, registers, associated instructions, memory model etc)
    //Device device[NUMDEVS]; //to be implemented, if time permits :-(( 
};


#endif //_MAIN_H_