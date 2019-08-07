#ifdef WINDOWS
#include <windows.h>
#else
#include <dirent.h>
#include <limits.h>
#include <unistd.h>
#endif
#include "Pass2.h"
#include <stdlib.h>

extern short loc_counter;
extern bool has_error;
extern vector<Inst> inst_set;
extern vector<Symbol> sym_tab;
ofstream of_xme;
string s1str, s9str;

InstType getInstType(vector<Operand_T> ops) {
  if (ops.size() == 1 && ops[0] == L10) {
    return Branch10;
  } else if (ops.size() == 1 && ops[0] == L13) {
    return Branch13;
  } else if (ops.size() == 1 && (ops[0] == R || ops[0] == SA)) {
    return OneAddr;
  } else if (ops.size() == 2 && ops[0] == CON_R && ops[1] == R) {
    return Arith;
  } else if (ops.size() == 2 && ops[0] == R && ops[1] == R) {
    return RegExchange;
  } else if (ops.size() == 2 && ops[0] == IDR && ops[1] == R) {
    return MemAccessLD;
  } else if (ops.size() == 2 && ops[0] == R && ops[1] == IDR) {
    return MemAccessST;
  } else if (ops.size() == 2 && ops[0] == BYTE && ops[1] == R) {
    return RegInit;
  } else if (ops.size() == 3 && ops[0] == COND_CEC && ops[1] == TCFC && ops[2] == TCFC) {
    return Cex;
  } else if (ops.size() == 3 && ops[0] == R && ops[1] == OFFSET && ops[2] == R) {
    return MemAccessRelLD;
  } else {
    return MemAccessRelST;
  }
}

/* generate opcode for Br13 instruction BL */
void handleBranch13(short int inst_id, vector<string> &ops, unsigned short &opcode) {
  // find label index from sym_tab
  auto lbl_index = is_label_in_sym_tab(ops[0]);
  short int offset = sym_tab[lbl_index].value - loc_counter - 2;
  auto opc = stoi(inst_set[inst_id].opcode, nullptr, 2);
  Br13Overlay instCode;
  instCode.inst._offset = offset >> 1;
  instCode.inst._opCode = opc;
  opcode = instCode.sh;
}

/* generate opcode for Br10 instruction branching other than BL */
void handleBranch10(short int inst_id, vector<string> &ops, unsigned short &opcode) {
  // find label index from sym_tab
  auto lbl_index = is_label_in_sym_tab(ops[0]);
  short int offset = sym_tab[lbl_index].value - loc_counter - 2;
  auto opc = stoi(inst_set[inst_id].opcode, nullptr, 2);
  Br10Overlay instCode;
  instCode.inst._offset = offset >> 1;
  instCode.inst._opCode = opc;
  opcode = instCode.sh;
}

/* generate opcode for Arithmatic (REG/CON, REG) instruction */
void handleArith(short int inst_id, vector<string> &ops, unsigned short &opcode) {
  // find label index from sym_tab
  bool is_const = false;
  short int lbl_index;
  auto src_index = is_register(ops[0]);
  auto dst_index = is_register(ops[1]);
  short int v;
  if (src_index == INVALID_INDEX) {
    // src is not a REG but CONST
    is_const = true;
    // find the value of the CONST then
    if (is_numeric(ops[0])) {
      str2int(ops[0], v);
    } else {
      lbl_index = is_label_in_sym_tab(ops[0]);
      v = sym_tab[lbl_index].value;
    }
  }
  bool is_byte = false;
  // check last 2 chars to check whether ".B" is present in instruction
  string last2chars = inst_set[inst_id].mnemonic.substr(inst_set[inst_id].mnemonic.size() - 2);
  if (last2chars.compare(".B") == 0) {
    // instruction ends with .B
    is_byte = true;
  }
  auto opc = stoi(inst_set[inst_id].opcode, nullptr, 2);
  ArithOverlay instCode;
  // populate
  instCode.inst._dst = sym_tab[dst_index].value;
  if (is_const) {
    short int src_value = 0;
    if (v == 0) {
      src_value = 0;
    } else if (v == 1) {
      src_value = 1;
    } else if (v == 2) {
      src_value = 2;
    } else if (v == 4) {
      src_value = 3;
    } else if (v == 8) {
      src_value = 4;
    } else if (v == 16) {
      src_value = 5;
    } else if (v == 32) {
      src_value = 6;
    } else if (v == -1) {
      src_value = 7;
    }

    instCode.inst._src = src_value;
    instCode.inst._regCon = SET_BIT;
  } else {
    instCode.inst._src = sym_tab[src_index].value;
    instCode.inst._regCon = CLEAR_BIT;
  }

  if (is_byte) {
    instCode.inst._wordByte = SET_BIT;
  } else {
    instCode.inst._wordByte = CLEAR_BIT;
  }

  instCode.inst._opCode = opc;

  opcode = instCode.sh;
}

/* generate opcode for Register Exchange (REG, REG) instruction SWAP - note: MOV constants as well, so, it is handled using 2-op inst (Arith) */
void handleRegExchange(short int inst_id, vector<string> &ops, unsigned short &opcode) {
  // find REG index from sym_tab

  auto src_index = is_register(ops[0]);
  auto dst_index = is_register(ops[1]);

  auto opc = stoi(inst_set[inst_id].opcode, nullptr, 2);
  RegExchangeOverlay instCode;
  // populate
  instCode.inst._dst = sym_tab[dst_index].value;
  instCode.inst._src = sym_tab[src_index].value;
  instCode.inst._wordByte = CLEAR_BIT; // this bit and the next are ignored but set to 0 for completeness
  instCode.inst._regCon = CLEAR_BIT;
  instCode.inst._opCode = opc;

  opcode = instCode.sh;
}

/* generate opcode for OneAddr (REG) instruction  SRA, RRC SWPB SXT */
void handleOneAddr(short int inst_id, vector<string> &ops, unsigned short &opcode) {
  // find label index from sym_tab
  auto dst_index = is_register(ops[0]);
  bool is_byte = false;
  // check last 2 chars to check whether ".B" is present in instruction
  string last2chars = inst_set[inst_id].mnemonic.substr(inst_set[inst_id].mnemonic.size() - 2);
  if (last2chars.compare(".B") == 0) {
    // instruction ends with .B
    is_byte = true;
  }
  auto opc = stoi(inst_set[inst_id].opcode, nullptr, 2);
  OneAddrOverlay instCode;
  // populate
  instCode.inst._dst = sym_tab[dst_index].value;
  instCode.inst._zeros = CLEAR_BIT;
  if (is_byte) {
    instCode.inst._wordByte = SET_BIT;
  } else {
    instCode.inst._wordByte = CLEAR_BIT;
  }
  instCode.inst._zero = CLEAR_BIT;
  instCode.inst._opCode = opc;

  opcode = instCode.sh;
}

/* generate opcode for Direct Memory Loading  (LD) instruction */
void handleMemAccessLD(short int inst_id, vector<string> &ops, unsigned short &opcode) {
  PrePostIncrDecr addr_modifier = None;
  if (ops[0].front() == '+') { // pre-increment
    addr_modifier = PreIncrement;
  } else if (ops[0].front() == '-') {
    addr_modifier = PreDecrement;
  } else if (ops[0].back() == '+') {
    addr_modifier = PostIncrement;
  } else if (ops[0].back() == '-') {
    addr_modifier = PostDecrement;
  }

  auto src_index = is_register(ops[0]);
  auto dst_index = is_register(ops[1]);
  bool is_byte = false;
  // check last 2 chars to check whether ".B" is present in instruction
  string last2chars = inst_set[inst_id].mnemonic.substr(inst_set[inst_id].mnemonic.size() - 2);
  if (last2chars.compare(".B") == 0) {
    // instruction ends with .B
    is_byte = true;
  }
  auto opc = stoi(inst_set[inst_id].opcode, nullptr, 2);
  MemAccessOverlay instCode;
  // populate
  instCode.inst._dst = sym_tab[dst_index].value;
  instCode.inst._src = sym_tab[src_index].value;
  switch (addr_modifier) {
  case PreIncrement:
    instCode.inst._prpo = SET_BIT;
    instCode.inst._dec = CLEAR_BIT;
    instCode.inst._inc = SET_BIT;
    break;
  case PreDecrement:
    instCode.inst._prpo = SET_BIT;
    instCode.inst._dec = SET_BIT;
    instCode.inst._inc = CLEAR_BIT;
    break;
  case PostIncrement:
    instCode.inst._prpo = CLEAR_BIT;
    instCode.inst._dec = CLEAR_BIT;
    instCode.inst._inc = SET_BIT;
    break;
  case PostDecrement:
    instCode.inst._prpo = CLEAR_BIT;
    instCode.inst._dec = SET_BIT;
    instCode.inst._inc = CLEAR_BIT;
    break;
  default: // no pre/post increment/decrement
    instCode.inst._prpo = CLEAR_BIT;
    instCode.inst._dec = CLEAR_BIT;
    instCode.inst._inc = CLEAR_BIT;
    break;
  }

  if (is_byte)
    instCode.inst._wordByte = SET_BIT;
  else
    instCode.inst._wordByte = CLEAR_BIT;
  instCode.inst._opCode = opc;
  opcode = instCode.sh;
}

/* generate opcode for Direct Memory Store  (ST) instruction */
void handleMemAccessST(short int inst_id, vector<string> &ops, unsigned short &opcode) {
  PrePostIncrDecr addr_modifier = None;
  if (ops[1].front() == '+') { // pre-increment
    addr_modifier = PreIncrement;
  } else if (ops[1].front() == '-') {
    addr_modifier = PreDecrement;
  } else if (ops[1].back() == '+') {
    addr_modifier = PostIncrement;
  } else if (ops[1].back() == '-') {
    addr_modifier = PostDecrement;
  }

  auto src_index = is_register(ops[0]);
  auto dst_index = is_register(ops[1]);
  bool is_byte = false;
  // check last 2 chars to check whether ".B" is present in instruction
  string last2chars = inst_set[inst_id].mnemonic.substr(inst_set[inst_id].mnemonic.size() - 2);
  if (last2chars.compare(".B") == 0) {
    // instruction ends with .B
    is_byte = true;
  }
  auto opc = stoi(inst_set[inst_id].opcode, nullptr, 2);
  MemAccessOverlay instCode;
  // populate
  instCode.inst._dst = sym_tab[dst_index].value;
  instCode.inst._src = sym_tab[src_index].value;
  switch (addr_modifier) {
  case PreIncrement:
    instCode.inst._prpo = SET_BIT;
    instCode.inst._dec = CLEAR_BIT;
    instCode.inst._inc = SET_BIT;
    break;
  case PreDecrement:
    instCode.inst._prpo = SET_BIT;
    instCode.inst._dec = SET_BIT;
    instCode.inst._inc = CLEAR_BIT;
    break;
  case PostIncrement:
    instCode.inst._prpo = CLEAR_BIT;
    instCode.inst._dec = CLEAR_BIT;
    instCode.inst._inc = SET_BIT;
    break;
  case PostDecrement:
    instCode.inst._prpo = CLEAR_BIT;
    instCode.inst._dec = SET_BIT;
    instCode.inst._inc = CLEAR_BIT;
    break;
  default: // no pre/post increment/decrement
    instCode.inst._prpo = CLEAR_BIT;
    instCode.inst._dec = CLEAR_BIT;
    instCode.inst._inc = CLEAR_BIT;
    break;
  }

  if (is_byte)
    instCode.inst._wordByte = SET_BIT;
  else
    instCode.inst._wordByte = CLEAR_BIT;

  instCode.inst._opCode = opc;
  opcode = instCode.sh;
}

/* generate opcode for Cex  (CEX) instruction */
void handleCex(short int inst_id, vector<string> &ops, unsigned short &opcode) {
  // operand format: COND, TC, FC
  auto cond_index = is_cond(ops[0]); // index of the COND in `cecs`
  // find tc value
  short int tc;
  if (is_numeric(ops[1])) { // tc is a value (not label)
    str2int(ops[1], tc);
  } else { // tc value is suuplied as label - find the label value in sym_tab
    auto lbl_index = is_label_in_sym_tab(ops[1]);
    tc = sym_tab[lbl_index].value;
  }
  // find fc value
  short int fc;
  if (is_numeric(ops[2])) { // tc is a value (not label)
    str2int(ops[2], fc);
  } else { // tc value is suuplied as label - find the label value in sym_tab
    auto lbl_index = is_label_in_sym_tab(ops[2]);
    fc = sym_tab[lbl_index].value;
  }

  auto opc = stoi(inst_set[inst_id].opcode, nullptr, 2);
  CexOverlay instCode;
  // populate
  instCode.inst._fc = fc;
  instCode.inst._tc = tc;
  instCode.inst._condCec = cec_values[cond_index];
  instCode.inst._opCode = opc;

  opcode = instCode.sh;
}

/* generate opcode for Register Initialization  (MOVL, MOVLZ, etc) instruction */
void handleRegInit(short int inst_id, vector<string> &ops, unsigned short &opcode) {
  // find the BYTE value
  short int b;
  if (is_numeric(ops[0])) { // tc is a value (not label)
    str2int(ops[0], b);
  } else { // tc value is suuplied as label - find the label value in sym_tab
    auto lbl_index = is_label_in_sym_tab(ops[0]);
    b = sym_tab[lbl_index].value;
  }
  // find REG index
  auto reg_index = is_register(ops[1]);
  auto opc = stoi(inst_set[inst_id].opcode, nullptr, 2);
  RegisterInitOverlay instCode;
  // populate
  instCode.inst._Byte = b;
  instCode.inst._dst = sym_tab[reg_index].value;
  instCode.inst._opCode = opc;

  opcode = instCode.sh;
}

/* generate opcode for Relative Memory Loading (LDR) instruction */
void handleMemAccessRelLD(short int inst_id, vector<string> &ops, unsigned short &opcode) {
  auto src_index = is_register(ops[0]);
  auto dst_index = is_register(ops[2]);
  // get offset value
  short int offset;
  if (is_numeric(ops[1])) {
    str2int(ops[1], offset);
  } else { // should not reach here, but in case
    auto lbl_index = is_label_in_sym_tab(ops[1]);
    offset = sym_tab[lbl_index].value;
  }
  bool is_byte = false;
  // check last 2 chars to check whether ".B" is present in instruction
  string last2chars = inst_set[inst_id].mnemonic.substr(inst_set[inst_id].mnemonic.size() - 2);
  if (last2chars.compare(".B") == 0) {
    // instruction ends with .B
    is_byte = true;
  }
  auto opc = stoi(inst_set[inst_id].opcode, nullptr, 2);
  MemAccessRelativeOverlay instCode;
  // populate
  instCode.inst._dst = sym_tab[dst_index].value;
  instCode.inst._offset = offset;
  instCode.inst._src = sym_tab[src_index].value;

  if (is_byte)
    instCode.inst._wordByte = SET_BIT;
  else
    instCode.inst._wordByte = CLEAR_BIT;

  instCode.inst._opCode = opc;
  opcode = instCode.sh;
}

/* generate opcode for Relative Memory Store (STR) instruction */
void handleMemAccessRelST(short int inst_id, vector<string> &ops, unsigned short &opcode) {
  auto src_index = is_register(ops[0]);
  auto dst_index = is_register(ops[1]);
  // get offset value
  short int offset;
  if (is_numeric(ops[2])) {
    str2int(ops[2], offset);
  } else { // should not reach here, but in case
    auto lbl_index = is_label_in_sym_tab(ops[2]);
    offset = sym_tab[lbl_index].value;
  }
  bool is_byte = false;
  // check last 2 chars to check whether ".B" is present in instruction
  string last2chars = inst_set[inst_id].mnemonic.substr(inst_set[inst_id].mnemonic.size() - 2);
  if (last2chars.compare(".B") == 0) {
    // instruction ends with .B
    is_byte = true;
  }
  auto opc = stoi(inst_set[inst_id].opcode, nullptr, 2);
  MemAccessRelativeOverlay instCode;
  //populate
  instCode.inst._dst = sym_tab[dst_index].value;
  instCode.inst._offset = offset;
  instCode.inst._src = sym_tab[src_index].value;

  if (is_byte) {
    instCode.inst._wordByte = SET_BIT;
  } else {
    instCode.inst._wordByte = CLEAR_BIT;
  }

  instCode.inst._opCode = opc;

  opcode = instCode.sh;
}

/* validates the operands of an instruction - if not, error message is written to the LIS file */
void proc_instruction(short int inst_id, vector<string> &toks, string &line, short int &n) {
  vector<string> operands = {};
  auto ops = toks[1];   //first token is the instruction and 2nd token holds operand(s)
  stringstream ss(ops); //to split into separate operands from the token
  string tok;
  while (getline(ss, tok, ',')) { //operands are separated by comma ','
    operands.push_back(tok);
  }
  auto ex_ops = inst_set[inst_id].expected_operands;
  //assume - error checked in pass1
  InstType it = getInstType(ex_ops);
  unsigned short opcode;
  switch (it) {
  case Branch13:
    handleBranch13(inst_id, operands, opcode);
  case Branch10:
    handleBranch10(inst_id, operands, opcode);
    break;
  case Arith:
    handleArith(inst_id, operands, opcode);
    break;
  case RegExchange:
    handleRegExchange(inst_id, operands, opcode);
    break;
  case OneAddr:
    handleOneAddr(inst_id, operands, opcode);
    break;
  case MemAccessLD:
    handleMemAccessLD(inst_id, operands, opcode);
    break;
  case MemAccessST:
    handleMemAccessST(inst_id, operands, opcode);
    break;
  case Cex:
    handleCex(inst_id, operands, opcode);
    break;
  case RegInit:
    handleRegInit(inst_id, operands, opcode);
    break;
  case MemAccessRelLD:
    handleMemAccessRelLD(inst_id, operands, opcode);
    break;
  case MemAccessRelST:
    handleMemAccessRelST(inst_id, operands, opcode);
    break;
  default:
    break;
  }

  // print to file
  stringstream ss_loc, ss_opcode;
  ss_loc << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << loc_counter;
  ss_opcode << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << opcode;
  string t = ss_loc.str();
  string hex_loc = (t.length() > 4) ? t.substr(t.length() - 4, 4) : t;
  t = ss_opcode.str();
  string hex_opcode = (t.length() > 4) ? t.substr(t.length() - 4, 4) : t;

  ofs << n << "\t" << hex_loc << "\t" << hex_opcode << "\t" << line << endl;
  s1str = s1str + hex_loc + hex_opcode;

  loc_counter += INSTRUCTION_LEN; //each instruction needs 2-bytes
}

/* generates opcode for BSS */
void handleBSS(vector<string> &ops, string &line, short int &n) {
  short int r;
  if (is_numeric(ops[0])) { // BSS operand is numeric
    str2int(ops[0], r);
  } else { // the value is in sym_tab
    auto lbl_index = is_label_in_sym_tab(ops[0]);
    r = sym_tab[lbl_index].value;
  }
  // print to file
  stringstream ss_loc, ss_opcode;
  ss_loc << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << loc_counter;
  ss_opcode << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << BSS_OPCODE;
  string t = ss_loc.str();
  string hex_loc = (t.length() > 4) ? t.substr(t.length() - 4, 4) : t;
  t = ss_opcode.str();
  string hex_opcode = (t.length() > 4) ? t.substr(t.length() - 4, 4) : t;

  ofs << n << "\t" << hex_loc << "\t" << hex_opcode << "\t" << line << endl;
  s1str = s1str + hex_loc + hex_opcode;
  loc_counter += r;
}

/* generates opcode for BYTE directive */
void handleBYTE(vector<string> &ops, string &line, short int &n) {
  short int r;
  if (is_numeric(ops[0])) {
    str2int(ops[0], r);
  } else { // operand is not a number - consider a label
    auto r2 = is_label_in_sym_tab(ops[0]);
    r = sym_tab[r2].value;
  }

  //print to file
  stringstream ss_loc, ss_opcode;
  ss_loc << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << loc_counter;
  ss_opcode << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << r;
  string t = ss_loc.str();
  string hex_loc = (t.length() > 4) ? t.substr(t.length() - 4, 4) : t;
  t = ss_opcode.str();
  string hex_opcode = (t.length() > 4) ? t.substr(t.length() - 4, 4) : t;

  ofs << n << "\t" << hex_loc << "\t" << hex_opcode << "\t" << line << endl;
  s1str = s1str + hex_loc + hex_opcode;
  loc_counter += BYTE_INCREASE;
}

/* generates opcode for BYTE directive */
void handleWORD(vector<string> &ops, string &line, short int &n) {
  short int r;
  if (is_numeric(ops[0])) {
    str2int(ops[0], r);
  } else { // operand is not a number - consider a label
    auto r2 = is_label_in_sym_tab(ops[0]);
    r = sym_tab[r2].value;
  }

  // print to file
  stringstream ss_loc, ss_opcode;
  ss_loc << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << loc_counter;
  ss_opcode << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << r;
  string t = ss_loc.str();
  string hex_loc = (t.length() > 4) ? t.substr(t.length() - 4, 4) : t;
  t = ss_opcode.str();
  string hex_opcode = (t.length() > 4) ? t.substr(t.length() - 4, 4) : t;

  ofs << n << "\t" << hex_loc << "\t" << hex_opcode << "\t" << line << endl;
  s1str = s1str + hex_loc + hex_opcode;
  loc_counter += WORD_INCREASE;
}
/* process the directive based on the index in directives */
void proc_directive(short int d_id, vector<string> &rec, string &line, short int &n, string p_tok) {
  vector<string> operands = {};
  if (rec.size() == 2) { // has operand
    auto ops = rec[1];
    /* split different operands - separated by comma */
    stringstream ss(ops); //
    string tok;
    while (getline(ss, tok, ',')) {
      operands.push_back(tok);
    }
  }
  directiveIndexes di = static_cast<directiveIndexes>(d_id);
  short int r;
  switch (di) {
  case dirALIGN:
    if (loc_counter % 2 != 0) {
      loc_counter++;
    } /* if odd increment the address do nothing, print to ofs */
    ofs << n << "\t\t\t" << line << endl;
    break;
  case dirBSS:
    handleBSS(operands, line, n);
    break;
  case dirBYTE: //2: //BYTE
    handleBYTE(operands, line, n);
    break;
  case dirEND:
    // extract the start address, if provided
    if (operands.size() == 1) {
      short int r;
      if (is_numeric(operands[0])) {
        str2int(operands[0], r);
      } else { // operand is not a number - consider a label
        auto r2 = is_label_in_sym_tab(operands[0]);
        r = sym_tab[r2].value;
      }
      // print to file
      stringstream ss_opcode;
      ss_opcode << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << r;
      string t = ss_opcode.str();
      string hex_opcode = (t.length() > 4) ? t.substr(t.length() - 4, 4) : t;
      s9str = s9str + hex_opcode;
    }
    ofs << n << "\t\t\t" << line << endl;
    break;
  case dirEQU:
    /* do nothing - everything is taken care of at Pass 1 */
    ofs << n << "\t\t\t" << line << endl;
    break;
  case dirORG:
    // no opcode - just loc_counter  is assigned new value
    ofs << n << "\t\t\t" << line << endl;
    str2int(operands[0], r);
    loc_counter = r;
    break;
  case dirWORD: // 6: //WORD
    handleWORD(operands, line, n);
    break;
  default:
    break;
  }
  return;
}

/* function to validate tokens in a record for pass 1 */
void proc_tokens(vector<string> &toks, string &line, short int &n) {
  //consider 1st token as instruction
  short int id = check_if_instruction(toks[0]);

  if (id != INVALID_INDEX) { // an instruction - next token must present and operand(s)
    proc_instruction(id, toks, line, n);
  } else { // either directive or label
    id = check_if_directive(toks[0]);
    if (id != INVALID_INDEX) { // a directive found - there may or may not have operand(s)
      proc_directive(id, toks, line, n, "");
    } else {                 // this token is a label - following token must be INST/DIR, if any
      if (toks.size() > 1) { // more tokens are there and has to be INST/DIR
        string prev_tok = toks[0];
        toks.erase(toks.begin()); // erase first token
        id = check_if_instruction(toks[0]);
        if (id != INVALID_INDEX) { // an instruction - next token must present and operand(s)
          proc_instruction(id, toks, line, n);
        } else { // either directive or label
          id = check_if_directive(toks[0]);
          if (id != INVALID_INDEX) { // a directive found - there may or may not have operand(s)
            proc_directive(id, toks, line, n, prev_tok);
          }
        }
      }
    }
  }
}

/* populate checksum for a s-rec (assuming, count, addr and data is present) */
void populateChecksum(SRec &srec) {
  int result = 0;
  short int r;
  // process len field (1 byte) of srec
  r = stoi(srec._count, nullptr, 16);
  result += r;
  // precess addr field (2 bytes) of srec
  for (unsigned short int i = 0; i < srec._addr.size(); i += 2) {
    string v = srec._addr.substr(i, 2);
    r = stoi(v, nullptr, 16);
    result += r;
  }
  // things are different for S0 and S1 then
  if (srec._type == S0) {
    for (unsigned short int i = 0; i < srec._data.size(); i++) { // each char in string
      r = srec._data[i];
      result += r;
    }
  } else if (srec._type == S1) {
    for (unsigned short int i = 0; i < srec._data.size(); i += 2) {
      string v = srec._data.substr(i, 2);
      r = stoi(v, nullptr, 16);
      result += r;
    }
  }
  // get ones complement of the sum
  stringstream ss;
  ss << std::uppercase << std::setw(2) << std::hex << ~result; // ones complement
  string t = ss.str();
  srec._checksum = (t.length() > 2) ? t.substr(t.length() - 2, 2) : t;
}

void populateS0(string f, SRec &srec) {
  srec._type = S0;
  srec._addr = "0000";
  unsigned short int len = f.size();
  string data0 = f;
  if (len > 28) { // file name is more than 28 bytes
    len = 28;
    data0 = f.substr(0, 28);
  }
  srec._data = data0;

  len += ADDR_BYTES_SREC + CHKSUM_BYTE_SREC;
  // get the hex string for calculated len
  stringstream ss;
  ss << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << len;
  string t = ss.str();
  srec._count = (t.length() > 2) ? t.substr(t.length() - 2, 2) : t;
}

void get_addr_opcode(const vector<string> &tokens, string addr, string rev_opcode) {}

/* generate S1 screcs from the s1str string */
void generateS1Recs(vector<string> &s1recs) {
  vector<string> all_address = {};
  vector<string> all_opcodes = {};
  for (unsigned short int i = 0; i < s1str.size(); i += 8) { // 4 chars for address and 4 chars for opcode
    string a = s1str.substr(i, 4);
    all_address.push_back(a);
    string o = s1str.substr(i + 4, 4);
    all_opcodes.push_back(o);
  }

  unsigned short int index = 0;
  SRec crec = {};
  crec._type = S1;
  crec._addr = all_address[index];
  string data = "";
  int curr_addr, next_addr;

  while (index < all_address.size()) {
    curr_addr = stoi(all_address[index], nullptr, 16);
    if (index < all_address.size() - 1) {
      next_addr = stoi(all_address[index + 1], nullptr, 16);
    } else
      next_addr = INVALID_INDEX;

    data = data + all_opcodes[index].substr(2, 2) + all_opcodes[index].substr(0, 2);

    if (abs(next_addr - curr_addr) > 2 || next_addr == INVALID_NUMBER) { // need to populate s1 rec and if req, create new s1
      crec._data = data;
      unsigned short int len = data.size() / 2 + ADDR_BYTES_SREC + CHKSUM_BYTE_SREC;
      stringstream ss;
      ss << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << len;
      string t = ss.str();
      crec._count = (t.length() > 2) ? t.substr(t.length() - 2, 2) : t;
      populateChecksum(crec);
      // insert to vector
      string s1RecStr = "S1" + crec._count + crec._addr + crec._data + crec._checksum;
      s1recs.push_back(s1RecStr);
      if (next_addr == INVALID_INDEX) { // no more S1 rec to produce
        break;
      } else {     // we processed the current record
        crec = {}; // init
        crec._type = S1;
        index++;
        crec._addr = all_address[index];
        data = ""; // clear prev conten
      }
    } else {
      index += 1;
    }
  }
}

void print_to_xme(string src_fname) {
  string ofxme_name = src_fname.substr(0, src_fname.find_last_of('.')) + ".xme"; // xme file name
  of_xme.open(ofxme_name);
  // Write the S0 record
  SRec srec0 = {};              // create s0 rec
  populateS0(src_fname, srec0); // populate byte count,addr, and data
  populateChecksum(srec0);      // calculate checksum based on count, addr and data
  of_xme << "S0" << srec0._count << srec0._addr << srec0._data << srec0._checksum << endl;
  // process s1str to create s1 srec(s)
  // of_xme<<"S1"<<s1str<<endl;
  vector<string> s1recs;
  generateS1Recs(s1recs);

  for (unsigned short int i = 0; i < s1recs.size(); ++i)
    of_xme << s1recs[i] << endl;
  // generate S9 srecand print
  SRec srec9 = {}; // create an s9 rec
  srec9._type = S9;
  if (s9str.empty()) {
    srec9._addr = "0000";
  } else {
    srec9._addr = s9str;
  }
  // populate len/count
  unsigned short int len = ADDR_BYTES_SREC + CHKSUM_BYTE_SREC; // data field is ignored in S9 srec
  stringstream ss;
  ss << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << len;
  string t = ss.str();
  srec9._count = (t.length() > 2) ? t.substr(t.length() - 2, 2) : t;
  populateChecksum(srec9);
  of_xme << "S9" << srec9._count << srec9._addr << srec9._checksum << endl;

  of_xme.close();
}

/* conducts pass1 */
bool Pass2(string src_fname) {
  s1str = "";
  s9str = "";
  ofs.close();
  string of_name = src_fname.substr(0, src_fname.find_last_of('.')) + ".lis"; // lis file name
  ofs.open(of_name);

  // read the src file line by line and process it
  ifstream ifs;
  ifs.open(src_fname);
  string line;          // to hold the content of a line
  short int n_line = 0; // corresponding line number in the src file
  if (ifs.is_open()) {
    while (getline(ifs, line)) {
      n_line++;
      if (line.empty()) {
        ofs << "\t" << n_line << "\t" << line << endl;
        continue;
      } else {
        // get tokens from the line
        vector<string> tokens = {};
        get_tokens(line, tokens);
        if (tokens.size() > 0) {
          proc_tokens(tokens, line, n_line);
        } else {
          ofs << "\t" << n_line << "\t" << line << endl;
          continue;
        }
      }
    }
    ifs.close();

    ofs << "\nSuccessful Completion of Assembly" << endl;
    ofs << "\n ****  Symbol Table ***" << std::endl;
    ofs << "Name\t\t\tType\tValue\tDecimal" << std::endl;

    for (auto s : sym_tab) {
      stringstream ss;
      ss << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << s.value;
      string t = ss.str();
      string hex_v = (t.length() > 4) ? t.substr(t.length() - 4, 4) : t;
      ofs.width(20);
      ofs << std::left << s.name;
      ofs.width(8);
      ofs << std::left << s.type;
      ofs.width(8);
      ofs << std::left << hex_v;
      ofs << s.value << endl;
    }

    /* char* cwd = _getcwd(0,0); */
    char *cwd = getcwd(0, 0);
    string working_directory(cwd);
    string fname = working_directory + "\\" + src_fname.substr(0, src_fname.find_last_of('.')) + ".xme"; // lis file name

    ofs << "\n .XME file:  " << fname << endl;
    ofs.close();
    /* print to xme file */
    //open of_xme to write xmmakina executable

    print_to_xme(src_fname); // print to xme file
    return true;
  } else {
    std::cout << "Could not open source file: " << src_fname << endl;
    return false;
  }
}
