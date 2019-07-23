#pragma once
#ifndef _PASS1_H
#define _PASS1_H

#include "Globals.h"
extern short loc_counter;
extern bool has_error;
extern vector<Inst> inst_set;
extern vector<Symbol> sym_tab;


void print_err_to_lis(Error_T e, string s);
void validate_instruction(short int inst_id, vector<string> &toks);
void process_directive(short int d_id, vector<string> & rec, string p_tok ="");
void validate_tokens(vector<string> &toks);
bool Pass1(string src_fname);

#endif //_PASS1_H