#include "Globals.h"

short loc_counter;
bool has_error;
vector<Inst> inst_set;
vector<Symbol> sym_tab;
ofstream ofs;

/* check if the string has format of Numeric type operand */
bool is_numeric(string s) {
  if (((s.front() == '#') || (s.front() == '$')) || ((s.front() == '\'') && (s.back() == '\''))) {
    return true;
  } else {
    return false;
  }
}

/* converts numeric type strings to corresponding integer value, error is captured and returns flase then */
Error_T str2int(string s, short int &value) {
  Error_T err = NO_ERR;
  if (s.front() == '#') { //integer value
    s.erase(0, 1);        //remove leading '#'
    value = stoi(s);
  } else if (s.front() == '$') { //hex value
    s.erase(0, 1);               //remove leading '$'
    value = stoi(s, nullptr, 16);
  } else if (s.front() == '\'' && s.back() == '\'') { //char - could be escaped or alpha-numeric
    unsigned int result = 0;
    s.erase(0, 1);                                      //remove leading "'"
    s.pop_back();                                       // remove trailing "'"
    for (unsigned short int i = 0; i < s.size(); i++) { //each char in string
      result <<= 8;
      result += s[i];
    }
    value = result & 0xffff;
  } else {
    err = INVALID_NUMBER;
  }
  return err;
}

/* check if the string is defined as register in symbol table */
short int is_register(string s) {
  short int flag = INVALID_INDEX;
  s.erase(remove(s.begin(), s.end(), '+'), s.end()); //erase any pre/post Increment (+)
  s.erase(remove(s.begin(), s.end(), '-'), s.end()); //erase any pre/post Decrement (-)
  for (unsigned short int i = 0; i < sym_tab.size(); ++i) {
    if (!sym_tab[i].name.compare(s) && (!sym_tab[i].type.compare("REG"))) { // found a register
      flag = i;
      break;
    }
  }
  return flag;
}

/* remove everything after comment char ';' and split the remaining into different tokens separated by space ' '  */
void get_tokens(string &l, vector<string> &toks) {
  string stripped = l.substr(0, l.find(";")); //strip off comments
  if (stripped.empty()) {
    return;
  } //comment line, nothing to tokenize
  else {
    replace(stripped.begin(), stripped.end(), '\t', ' '); //replace tab witha space, if there is any
    stringstream ss(stripped);
    string token;
    while (getline(ss, token, ' ')) {
      token.erase(remove_if(token.begin(), token.end(), [](char &c) { return isspace<char>(c, locale::classic()); }), token.end()); //remove any unwated space
      if (!token.empty()) {
        toks.push_back(token);
      }
    }
    return;
  }
}

/* returns the index of an instruction, if present in the instruction set, otherwise returns INVALID_INDEX (-1) */
short int check_if_instruction(string s) {
  short int flag = INVALID_INDEX;
  for (unsigned short int i = 0; i < inst_set.size(); ++i) {
    string mnem = inst_set[i].mnemonic;
    bool b = (mnem.size() == s.size()) && (equal(mnem.begin(), mnem.end(), s.begin(), [](char &c1, char &c2) { return toupper(c1) == toupper(c2); }));
    if (b) {
      flag = i;
      break;
    }
  }

  return flag;
}

/* returns the index of the directive, if present in the directives */
short int check_if_directive(string s) {
  short int flag = INVALID_INDEX;
  for (unsigned short int i = 0; i < directives.size(); ++i) {
    string d = directives[i];
    bool b = (d.size() == s.size()) && (equal(d.begin(), d.end(), s.begin(), [](char &c1, char &c2) { return toupper(c1) == toupper(c2); }));
    if (b) {
      flag = i;
      break;
    }
  }
  return flag;
}

/* impose rules for label name */
bool is_valid_label_name(string lbl) {
  bool flag = true;
  // -- first letter must be alphabetic
  if (!(isalpha(lbl.front()) || lbl.front() == '_') || !(std::find_if(lbl.begin(), lbl.end(), [](char c) { return !(std::isalnum(c) || (c == '_')); }) == lbl.end()) || lbl.size() > 32) {
    flag = false;
  }

  return flag;
}

/*return the index of the symbol in sym_tab other than registers - LBL and UNK */
short int is_label_in_sym_tab(string lbl) {
  short int flag = INVALID_INDEX;
  for (unsigned short int i = 0; i < sym_tab.size(); ++i) {
    if (!sym_tab[i].name.compare(lbl) && ((!sym_tab[i].type.compare("LBL")) || (!sym_tab[i].type.compare("UNK")))) { // found an entry
      flag = i;
      break;
    }
  }
  return flag;
}

/* check if the string is CEC */
short int is_cond(string s) {
  short int flag = INVALID_INDEX;
  for (unsigned short int i = 0; i < cecs.size(); ++i) {
    string d = cecs[i];
    bool b = (d.size() == s.size()) && (equal(d.begin(), d.end(), s.begin(), [](char &c1, char &c2) { return toupper(c1) == toupper(c2); }));
    if (b) {
      flag = i;
      break;
    }
  }
  return flag;
}

void init_globals(string src_fname, string inst_fname /* = "instructions.txt"*/) {
  /* create operand map to populate expected operands for each instructions  */
  map<string, Operand_T> inst_map;     //maps operand string from input file to Operand_T
  map<string, Operand_T>::iterator it; //iterator for the map
  inst_map["p"] = IDR;                 //pre/post inc/dec Reg
  inst_map["r"] = R;                   //Reg
  inst_map["o"] = OFFSET;              //offset
  inst_map["a"] = L13;                 //label for 13-bit offset BL
  inst_map["l"] = L10;                 //label for 10-bit offset - other branching inst
  inst_map["b"] = BYTE;                //byte
  inst_map["v"] = CON_R;               //CON or Reg
  inst_map["s"] = SA;                  //SA vector
  inst_map["c"] = COND_CEC;            //val from cec
  inst_map["t"] = TCFC;                //TC or FC vallue

  inst_set = {};
  ifstream ifs;
  ifs.open(inst_fname);       //open the instruction file
  if (ifs.is_open()) {        //could open the file
    string l;                 //line
    while (getline(ifs, l)) { //read each line in l
      if (l.empty()) {
        continue;
      }
      stringstream ss(l);
      vector<string> tokens;
      string token;
      while (getline(ss, token, ' ')) {
        tokens.push_back(token);
      }
      if (tokens.size() != 3) {
        cout << "Invalid entry in instruction file: " << l << endl;
        break;
      }
      //third token contains operands - decipher it
      auto s = tokens[2];
      vector<Operand_T> v_ops_t;
      if (s.size() < 2) {
        v_ops_t.push_back(inst_map.find(s)->second);
      } else {
        stringstream ss2(s);
        vector<string> v_ops;
        string tok;
        while (getline(ss2, tok, ',')) {
          v_ops.push_back(tok);
        }
        for (auto o : v_ops) {
          v_ops_t.push_back(inst_map.find(o)->second);
        }
      }
      Inst an_inst;
      an_inst.mnemonic = tokens[0];
      an_inst.opcode = tokens[1];
      an_inst.expected_operands = v_ops_t;
      inst_set.push_back(an_inst);
    }

  } else {
    cout << "\nCould not open instruction file " << inst_fname << endl;
  }
  ifs.close(); //end reading instruction file
  /******************* done with instruction set*/
  loc_counter = 0;
  has_error = false;
  //directives = {"ALIGN","BSS","BYTE","END","EQU","ORG","WORD"};
  //cecs = {"EQ","NE","CS","HS","CC","LO","MI","PL","VS","VC","HI","LS","GE","LT","GT","LE","AL"};
  //initialize symbol table and populate with the default registers
  sym_tab = {};
  for (short int i = 0; i < TOTAL_REGISTER; ++i) {
    sym_tab.insert(sym_tab.begin(), Symbol{"R" + to_string(i), "REG", i});
  }

  //create the LIS output file to write the result
  string of_name = src_fname.substr(0, src_fname.find_last_of('.')) + ".lis"; //lis file name
  ofs.open(of_name);
  ofs << " .ASM file: " << src_fname << endl;
  ofs << "\n\n\n"; //put 3 blank lines
}
