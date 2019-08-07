#include "cpu.h"

void dev_mem_access(unsigned short mar, unsigned short &mbr, ACTION rw, SIZE wb) {
  //TODO
}

/* Emulates the bus and the memory access
    - mar:  memory address
    - mbr: ref to data to read/write
    - rw: READ|WRITE
    - wb: WORD|BYTE
 */
void bus(unsigned short mar, unsigned short &mbr, ACTION rw, SIZE wb) {
  if (rw == READ) {
    mbr = (wb == WORD) ? memory.word_mem[mar >> 1] : memory.byte_mem[mar];
  } else { //rw == WRITE
    if (wb == WORD) {
      memory.word_mem[mar >> 1] = mbr;
    } else { //BYTE
      memory.byte_mem[mar] = (unsigned char)(mbr & 0xFF);
    }
    // zero latency for system memomory - not increment required for defult case(sys mem)
  }
  if (mar < DEVMEM) { //this part is not implemented - a dummy function is placed instead TODO: if time permits
    dev_mem_access(mar, mbr, rw, wb);
  }

  if (mar < VECTORBASE) {
    sysclk += 3;
  }
}

/*  runs fetch-decode-execute-check cycle
    The emulator contains all required vars to carryout the tasks 
 */
void go(Emulator &emulator) {
  debug(emulator);
  emulator.cpu.isRunning = true;
  emulator.cpu.exitRequired = false;
  for (;;) {
    fetch();
    decode_and_execute(); //(emulator);
    //execute(emulator);
    check(emulator); //
    if (emulator.cpu.exitRequired) {
      break;
    }
  }

  return;
}

/* Get (fetch) data from memory 
   - Obtain data from PC and updated accordingly, 
   - NOTE: 'bus' is used
*/
void fetch() {
  MAR = PC;
#ifdef DEBUG
  printf("\nFetching from location 0x%x", MAR);
#endif //DEBUG
  //read from PC and store in IR - use bus
  bus(MAR, MBR, READ, WORD);
  IR = MBR;
  //increment PC
  PC += INSTSIZE;
  SET_BIT(PC, 0, 0); //PC should be even!

  return;
}

/* Deassembly opcode and operand from Instruction in the IR
    - no input or output 
 */
void decode_and_execute() { //(Emulator & emulator){
  decode_execute();
}
void execute(Emulator &emulator);
void check(Emulator &emulator); //other than regular cpu task,like, interrupt handle, check for exit etc