#ifndef _CPU_H_
#define _CPU_H_
#include "Globals.h"
#include "debugger.h"
#include "instructions.h"
#include "main.h"
#include "stdio.h"

struct CPU {
  bool isRunning;    //cpu status, either running or sleeping
  bool exitRequired; // check is exit is rquired - cntrl+break or other
};

//functions for cpu-cycle
void go(Emulator &emulator);
void fetch();              //fetch(Emulator & emulator);
void decode_and_execute(); //decode(Emulator & emulator);
void execute(Emulator &emulator);
void check(Emulator &emulator); //other than regular cpu task,like, interrupt handle, check for exit etc

void bus(unsigned short mar, unsigned short &mbr, ACTION rw, SIZE wb); //emulating bus behavior

#endif //_CPU_H_