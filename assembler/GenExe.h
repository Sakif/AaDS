#pragma once
#ifndef _GENEXE_H
#define _GENEXE_H

#include "Globals.h"
// extern short loc_counter;
// extern bool has_error;
// extern vector<Inst> inst_set;
extern vector<Symbol> sym_tab;

enum SRec_Type {
  S0,
  S1,
  S9
};

struct SRec {
  SRec_Type _type;
  char _typeStr[2];
  char _count[2];
  char _addr[4];
  string _data; //should be max 28 byte
  char _checksum[2];
};

void getChecksum0(const string &s, string &cs);
void getChecksum1(const string &s, string &cs);

#endif //_GENEXE_H