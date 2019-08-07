#pragma once
#ifndef _PASS2_H
#define _PASS2_H
// #ifdef __cpp_lib_filesystem
// #include<filesystem>
// #else
// #include<experimental/filesystem>
// namespace std{
//     namespace filesystem = experimental::filesystem;
// }
// #endif

#include "Globals.h"

#define SET_BIT 1
#define CLEAR_BIT 0
#define INSTRUCTION_LEN 2
#define BSS_OPCODE 0
#define MAX_BYTE_SREC_DATA 28 //maximum number of byte in srec data field
#define ADDR_BYTES_SREC 2     //number of byte in address fieled
#define CHKSUM_BYTE_SREC 1    //number of byte in checksumS fieled

extern short loc_counter;
extern bool has_error;
extern vector<Inst> inst_set;
extern vector<Symbol> sym_tab;

/*********** Instruction Set Structs for Pass 2  **************/

enum PrePostIncrDecr {
  None,
  PreIncrement,
  PreDecrement,
  PostIncrement,
  PostDecrement
};

enum InstType {
  MemAccessLD,
  MemAccessST,
  MemAccessRelLD,
  MemAccessRelST,
  RegInit,
  Branch13,
  Branch10,
  Cex,
  Arith,
  RegExchange,
  OneAddr
};

/* Register direct and register direct with pre or post auto-increment or auto-decrement Inst - Section 6.1.1 (LD and ST) */
/* used when expected operands of type - (IDR,R) or (R,IDR) */
struct MemAccessInstruction {
  unsigned _dst : 3;      //dest register
  unsigned _src : 3;      //src register
  unsigned _wordByte : 1; //word or byte flag
  unsigned _inc : 1;      //increment flag
  unsigned _dec : 1;      //decrement flag
  unsigned _prpo : 1;     //pre/post flag
  unsigned _opCode : 6;   //opcode for ld or st instruction
};

union MemAccessOverlay {
  unsigned short sh;
  MemAccessInstruction inst;
};

/* Register Relative memory access Inst - Section 6.1.2 (LDR and STR) */
/* used when expected operands of type - (R,OFFSET,R) or (R,R,OFFSET) */
struct MemAccessRelativeInstruction {
  unsigned _dst : 3;      //dest register
  unsigned _src : 3;      //src register
  unsigned _wordByte : 1; //word or byte flag
  short int _offset : 7;  //offset value
  unsigned _opCode : 2;   //opcode for ldr or str instruction
};

union MemAccessRelativeOverlay {
  unsigned short sh;
  MemAccessRelativeInstruction inst;
};

/* Register Initialization Instruction - Section 6.2 */
/* used when expected operands of type - (BYTE,R)  */
struct RegisterInitInstruction {
  unsigned _dst : 3;    //dest register
  unsigned _Byte : 8;   //8-bit value
  unsigned _opCode : 5; //opcode for the instruction
};

union RegisterInitOverlay {
  unsigned short sh;
  RegisterInitInstruction inst;
};

/* Branching with 13-bit offset Inst - Section 6.3 (BL) */
/* used when expected operands of type - L13 */
struct Br13Instruction {
  short int _offset : 13; //offset value
  short int _opCode : 3;  //opcode for BL instruction
};

union Br13Overlay {
  unsigned short sh;
  Br13Instruction inst;
};

/* Branching with 10-bit offset Inst - Section 6.3 (Branching other than BL) */
/* used when expected operands of type - L10 */
struct Br10Instruction {
  short int _offset : 10; //offset value
  short int _opCode : 6;  //opcode for branching instruction except BL
};

union Br10Overlay {
  unsigned short sh;
  Br10Instruction inst;
};
/* Conditional Execution Inst - Section 6.4 (CEX) */
/* expected operands (COND_CEC,TCFC,TCFC) */
struct CexInstruction {
  unsigned _fc : 3;
  unsigned _tc : 3;
  unsigned _condCec : 4;
  unsigned _opCode : 6;
};

union CexOverlay {
  unsigned short sh;
  CexInstruction inst;
};

/* 2-operand (REG-REG or CON-REG) Inst - Section 6.5 and Reg Exchange MOV(.B or .W) */
/* expected operands (CON_R,R) */
struct ArithInstruction {
  unsigned _dst : 3;
  unsigned _src : 3;
  unsigned _wordByte : 1;
  unsigned _regCon : 1;
  unsigned _opCode : 8;
};

union ArithOverlay {
  unsigned short sh;
  ArithInstruction inst;
};

/* Register exchange (REG-REG) Inst - Section 6.6 SWAP, except MOV(.B or .W) */
/* expected operands (R,R) */
struct RegExchangeInstruction {
  unsigned _dst : 3;
  unsigned _src : 3;
  unsigned _wordByte : 1;
  unsigned _regCon : 1;
  unsigned _opCode : 8;
};

union RegExchangeOverlay {
  unsigned short sh;
  RegExchangeInstruction inst;
};

/* Single register Inst - Section 6.7 */
/* expected operands (R) */
struct OneAddrInstruction {
  unsigned _dst : 3;
  unsigned _zeros : 3;
  unsigned _wordByte : 1;
  unsigned _zero : 1;
  unsigned _opCode : 8;
};

union OneAddrOverlay {
  unsigned short sh;
  OneAddrInstruction inst;
};

/*<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>> */
enum SRec_Type {
  S0,
  S1,
  S9
};

struct SRec {
  SRec_Type _type;
  string _count;    //char _count[2];
  string _addr;     //char _addr[4];
  string _data;     //should be max 28 byte
  string _checksum; //char _checksum[2];
};

//string s1str, s9str;

//std::filesystem::path getexepath();
void proc_instruction(short int inst_id, vector<string> &toks);
void proc_directive(short int d_id, vector<string> &rec, string p_tok = "");
void proc_tokens(vector<string> &toks);
bool Pass2(string src_fname);

#endif //_PASS2_H
