#ifndef _GLOBALS_H
#define _GLOBALS_H


#include "stdio.h"
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
#include<algorithm>
#include<cctype>
#include<map>
#include<iomanip>
#include<stdlib.h>

#define INVALID_INDEX -1
#define BYTE_MIN 0
#define BYTE_INCREASE 1
#define WORD_INCREASE 2


using namespace std;


enum Operand_T{ //operands tyoe
    IDR, //pre/post increment decrement register - denoted as 'p' in instruction file
    R, //register (no, pre/post +/-) - 'r'
    OFFSET, //offset value - signed number with range [-64,63] - 'o'
    L13, //label with 13-bit offset - 'a'
    L10, //label with 10-bit offset - 'l'
    BYTE, //byte value - 'b'
    CON_R, //register or fixed/constant value [0,1,2,8,16,32,-1] - 'v'  
    SA, //vector value [0-15], 's'
    COND_CEC, //cec value - 'c'
    TCFC //TC/FC type [0-7] - 't'
};

enum Error_T{
    NO_ERR = 0, //no error :-)
    MISSING_OPERAND, //missing operand, eg. instruction/directive without required operand  
    ILLEGAL_OPERAND, //unwanted operand, eg, operand after ALIGN
    NUMBER_OF_OPERANDS_MISMATCH, //too many ortoo few operands compared to expected
    INVALID_OPERAND, //operand present but invalid. eg, byte value is not in byte range
    INVALID_REGISTER, //expected register operand but got something else, possibly undefined
    MISSING_INSTRUCTION_DIRECTIVE, //token following a LBL must be either an INST or a DIR 
    INVALID_LABEL_FORMAT, //label format is not valid
    UNDEFINED_SYMBOL, //Symbol(label or register) is not defined  - might be capyured at the end of first pass/ in 2nd pass??
    DUPLICATE_LABEL, //duplicate label in symbol table
    INVALID_NUMBER, //the string is not a valid number - compare with INVALID_OPERAND???
    INVALID_RECORD //too many tokens
};
struct Symbol{
    string name; //name of the symbol
    string type; //SymbolType type; //label (LBL), register (REG) or unknown (UNK)
    int value; //value - decimal  
};

struct Inst{ //instruction
    string mnemonic; //mnemonic of the instruction
    string opcode; //most significant binary bits of this mnemonic -stored as string to join rest of the bits to create full opcode 
    vector<Operand_T>  expected_operands; //rule for the expected operands for this instruction
    //Inst(string m, string o, vector<Operand_T> e):mnemonic(m), opcode(o),expected_operands(e){}
};

//global vars
extern short int loc_counter;
extern bool has_error;
extern vector<Inst> inst_set; //instruction set - global scope
extern ofstream ofs;
const vector<string> directives = {"ALIGN", "BSS", "BYTE", "END", "EQU", "ORG", "WORD"};
enum directiveIndexes { dirALIGN,
                        dirBSS,
                        dirBYTE,
                        dirEND,
                        dirEQU,
                        dirORG,
                        dirWORD };
const vector<string> cecs = {"EQ", "NE", "CS", "HS", "CC", "LO", "MI", "PL", "VS", "VC", "HI", "LS", "GE", "LT", "GT", "LE", "AL"};
const vector<unsigned short int> cec_values = {0, 1, 2, 2, 3, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
extern vector<Symbol> sym_tab;

//functions
bool is_numeric(string s);
Error_T str2int(string s, short int& value);
short int is_register(string s);
void get_tokens(string & l, vector<string>& toks);
short int check_if_instruction(string s);
short int check_if_directive(string s);
bool is_valid_label_name(string lbl);
short int is_label_in_sym_tab(string lbl);
short int is_cond(string s);

void init_globals(string src_fname, string inst_fname = "instructions.txt");



#endif //_GLOBALS_H