#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <bitset>

//control enumerations
enum SIZE { WORD = 0,
            BYTE };
enum ACTION { READ = 0,
              WRITE };

#define INSTSIZE 2
//#define SET_BIT(var, pos, val) ((var) |= (val << pos)) //set bit at 'pos' in 'var' to 'val' [0|1]

/*Memory */
#define BYTEMAXMEM (1 << 16) /* 2^16 bytes */
#define WORDMAXMEM (1 << 15) /* 2^15 words */
#define VECTORBASE 0xFFC0    /*base address for vectors */
#define DEVMEM 0x0010

union mem_ex {
  unsigned char byte_mem[BYTEMAXMEM];
  unsigned short word_mem[WORDMAXMEM];
};

extern union mem_ex memory;
/* Registers */
#define REGCNT 8 //number of registers - in cols
#define ROWS 2   //number of rows, first row (0-index)for different registers, 2nd row for corresponding constants

extern unsigned reg_file[ROWS][REGCNT]; //available to programmer

//define alias names for REGs
#define LR reg_file[0][4]  //Link Register
#define SP reg_file[0][5]  //Stack Pointer
#define PSW reg_file[0][6] //Program Status Word
#define PC reg_file[0][7]  //Program Counter

/* PSW related */
extern unsigned carry[2][2][2];
extern unsigned overflow[2][2][2];

// not accessible by programmer
extern unsigned short MAR;
extern unsigned short MBR;
extern unsigned short IR;
extern unsigned short TMP;

extern short int sysclk; //system clock counter

// check if bit "pos" is set in "var"
#define CHECK_BIT(var, pos) (((var) & (1 << pos)) >> pos)
// set bit "pos" in "var". "val" = [0|1]
#define SET_BIT(var, pos, val) ((var) |= (val << pos))

// sign extension masks
#define SEXT_BL 0xE000 // 1110.0000.0000.0000 -> sign extend from bit 13
#define SEXT_BR 0xF800 // 1111.1000.0000.0000 -> sign extend from bit 10

// byte isolator
#define LO_BYTE 0x00FF
#define HI_BYTE 0xFF00
// /* set bit at 'pos' in 'var' to 'val' [0|1] */
// inline void SET_BIT(unsigned int &var, unsigned short pos, unsigned short val){
//     (var |= (val << pos));
// }

// /* check if the bit 'pos' is set in a 'var' */
// typedef std::bitset<sizeof(int)> IntBits;
// inline bool CHECK_BIT(unsigned int var, unsigned short pos){ return IntBits(var).test(pos);}

#endif //_GLOBALS_H_