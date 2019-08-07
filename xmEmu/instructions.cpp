#include "instructions.h"

void reg_const_ops() {
}

void ldr_str_ops() {
  PswOverlay psw;
  psw.sh = PSW;
  LDRSTROverlay ldrstr;
  ldrstr.inst = IR;
  unsigned short EA;
#ifdef DEBUG
  printf("\nExecuting LDRSTR type instruction");
  printf("\nDST %d SRC %d OFF %d", ldrstr.dst, ldrstr.src, ldrstr.off);
#endif
  TMP = ldrstr.bits.off;   //store offset bits to TMP Reg
  if (CHECK_BIT(TMP, 6)) { //sign extension bit- Sec 6.1.2 XM2 ISA
    TMP |= 0xFFE0;
  }
  if (ldrstr.bits.type == 1) {               //LDR
    EA = reg_file[0][ldrstr.bits.src] + TMP; //effective address
    MAR = EA;
    MBR = reg_file[0][ldrstr.bits.dst];
    if (ldrstr.bits.wb == 0) { //WORD
      bus(MAR, MBR, READ, WORD);
    } else { //BYTE
      bus(MAR, MBR, READ, BYTE);
    }

  }

  else if (ldrstr.bits.type == 0) {          //STR
    EA = reg_file[0][ldrstr.bits.dst] + TMP; //effective address
    MAR = EA;
    MBR = reg_file[0][ldrstr.bits.src];
    if (ldrstr.bits.wb == 0) { //WORD
      bus(MAR, MBR, WRITE, WORD);
    } else { //BYTE
      bus(MAR, MBR, WRITE, BYTE);
    }
  }

  return;
}
/* Decode instruction and call execute  */
void decode_execute() {
  //check B15:B14
  switch (OPMASK(IR)) {
  case 0: //Branching
    branch_ops();
    break;
  case 1:              //REG-CON ops, REG ops, LDST, and special cases
    if (OPBIT13(IR)) { // MOV instructions
      mov_ops();
    } else if (OPBIT12(IR)) { // LD, ST, SVC, and CEX
      ld_st_special();
    } else { // all REG ops
      reg_const_ops();
    }
    break;
  case 2: //LDR access
  case 3: //STR access
    ldr_str_ops();
    break;
  }
}