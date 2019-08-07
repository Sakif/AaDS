#include "Pass1.h"
#include "Pass2.h"

extern short loc_counter;
extern bool has_error;
extern vector<Inst> inst_set;
extern vector<Symbol> sym_tab;

//prints error message to LIS file
void print_err_to_lis(Error_T e, string s) {

  string msg = "***** ";
  switch (e) {
  case NO_ERR:
    ofs << "\t*****" << s << endl;
    break;
  case MISSING_OPERAND:
    ofs << "\t****** Expected operand: " << s << endl;
    break;
  case ILLEGAL_OPERAND:
    ofs << "\t****** Illegal operand: " << s << endl;
    break;
  case NUMBER_OF_OPERANDS_MISMATCH:
    ofs << "\t ***** Too many/few number of operands: " << s << endl;
    break;
  case INVALID_OPERAND:
    ofs << "\t ***** Invalid operands: " << s << endl;
    break;
  case INVALID_REGISTER:
    ofs << "\t ***** Invalid REG: " << s << endl;
    break;
  case MISSING_INSTRUCTION_DIRECTIVE:
    ofs << "\t ***** Expected INST/DIR: " << s << endl;
    break;
  case INVALID_LABEL_FORMAT:
    ofs << "\t ***** Not valid label: " << s << endl;
    break;
  case UNDEFINED_SYMBOL:
    ofs << "\t ***** Undefined operand(symbol): " << s << endl;
    break;
  case DUPLICATE_LABEL:
    ofs << "\t ***** Duplicate LBL: " << s << endl;
    break;
  case INVALID_NUMBER:
    ofs << "\t ***** Invalid Number: " << s << endl;
    break;
  case INVALID_RECORD:
    ofs << "\t ***** Invalid Record: " << s << endl;
    break;
  default:
    break;
  }
}

/* validates the operands of an instruction - if not, error message is written to the LIS file */
void validate_instruction(short int inst_id, vector<string> &toks) {
  vector<string> operands = {};
  auto ops = toks[1];   //first token is the instruction and 2nd token holds operand(s)
  stringstream ss(ops); //to split into separate operands from the token
  string tok;
  while (getline(ss, tok, ',')) { //operands are separated by comma ','
    operands.push_back(tok);
  }
  auto ex_ops = inst_set[inst_id].expected_operands;
  if (operands.size() != ex_ops.size()) { //number of operands and expected number of operands for this inst is not same
    Error_T e = NUMBER_OF_OPERANDS_MISMATCH;
    string s = "Expected: " + to_string(ex_ops.size()) + " Has: " + to_string(operands.size()) + " operands ";
    print_err_to_lis(e, s);
    has_error = true;
  } else { // validate each operand - either register, or numeric or label type and handle accordingly
    for (unsigned short int i = 0; i < operands.size(); ++i) {
      auto op = operands[i];
      if (is_register(op) != INVALID_INDEX && (ex_ops[i] == IDR || ex_ops[i] == R || ex_ops[i] == CON_R)) { //valid operand - do nothinf
        continue;
      } else if (is_numeric(op)) { //numeric operand
        //obtain value of the operand
        if (ex_ops[i] == L10 || ex_ops[i] == L13) {
          print_err_to_lis(INVALID_OPERAND, "Only labels are permitted for branch targt");
          has_error = true;
        }
        short int r;
        Error_T e = str2int(op, r);
        if (e != NO_ERR) {
          if (r > INT16_MAX || r < INT16_MIN) {
            string s = "Too large or small value..";
            print_err_to_lis(e, s);
            has_error = true;
          } else if ((r > UINT8_MAX || r < BYTE_MIN) && ex_ops[i] == BYTE) {
            string s = "BYTE value should be (0,255)";
            print_err_to_lis(INVALID_OPERAND, s);
            has_error = true;
          } else if ((r != 0 || r != 1 || r != 2 || r != 8 || r != 16 || r != 32 || r != -1) && ex_ops[i] == CON_R) {
            print_err_to_lis(INVALID_NUMBER, "CON value should be [0, 1,2, 8,16, 32 or -1]");
            has_error = true;
          } else if ((r < 0 || r > 15) && ex_ops[i] == SA) {
            print_err_to_lis(INVALID_OPERAND, "SA value should be (0,15)");
            has_error = true;
          } else if ((r < 0 || r > 7) && ex_ops[i] == TCFC) {
            print_err_to_lis(INVALID_OPERAND, "TC/FC value should be (0,7)");
            has_error = true;
          }
        } else {
          if ((ex_ops[i] == IDR || ex_ops[i] == R)) { //REG expected but number
            print_err_to_lis(INVALID_REGISTER, ">" + op + "<");
            has_error = true;
          }
        }

      } else if (is_cond(op) != INVALID_INDEX) { // cond
        if (ex_ops[i] != COND_CEC) {
          print_err_to_lis(INVALID_OPERAND, "COND operand is not valid..");
          has_error = true;
        }
      } else {                                                            //label
        if ((ex_ops[i] == IDR || ex_ops[i] == R || ex_ops[i] == CON_R)) { //REG expected but label
          print_err_to_lis(INVALID_REGISTER, ">" + op + "<");
          has_error = true;
        }

        //validate label name and check if the label is in sym_tab else store it
        else if (is_valid_label_name(op)) {

          if (is_label_in_sym_tab(op) == INVALID_INDEX) { //not in sym_tab - store
            sym_tab.insert(sym_tab.begin(), Symbol{op, "UNK", -1});
          } else {
            continue;
          }

        } else {
          print_err_to_lis(INVALID_LABEL_FORMAT, "Invalid Label nmae..");
          has_error = true;
        }
      }
    }
  }
  loc_counter += 2; //each instruction needs 2-bytes
}
/* process ALIGN directive */
void handleDirALIGN(vector<string> &ops) {
  if (ops.size() != 0) { //has operand
    print_err_to_lis(ILLEGAL_OPERAND, "directive ALIGN does not take an operand");
    has_error = true;
  } else {
    if (loc_counter % 2 != 0) {
      loc_counter++;
    } //if odd increment the address
  }
}

/* process BSS directive */
void handleDirBSS(vector<string> &ops) {
  short int r;
  if (ops.size() != 1) { //no operand or more than one operand
    print_err_to_lis(NUMBER_OF_OPERANDS_MISMATCH, "BSS must have one and only one operand");
    has_error = true;
  } else {
    if (is_numeric(ops[0])) {
      Error_T e = str2int(ops[0], r);
      if (e == NO_ERR) {
        loc_counter += r;
      } else {
        print_err_to_lis(e, "BSS operand should be a valid number");
        has_error = true;
      }

    } else {
      auto r2 = is_label_in_sym_tab(ops[0]);
      if (r2 == INVALID_INDEX) { // not in symbol table - check name, store label in sym_tab and emit error
        if (is_valid_label_name(ops[0])) {
          sym_tab.insert(sym_tab.begin(), Symbol{ops[0], "UNK", -1});
        } else {
          print_err_to_lis(INVALID_LABEL_FORMAT, "");
          has_error = true;
        }

      } else {
        loc_counter += sym_tab[r2].value;
      }
    }
  }
}

/* process BSS directive */
void handleDirBYTE(vector<string> &ops) {
  short int r;
  if (ops.size() != 1) { //no operand or more than one operand
    print_err_to_lis(NUMBER_OF_OPERANDS_MISMATCH, "BYTE must have one and only one operand");
    has_error = true;
  } else {
    if (is_numeric(ops[0])) {
      Error_T e = str2int(ops[0], r);
      if (e == NO_ERR && (r < BYTE_MIN || r > INT8_MAX)) {
        print_err_to_lis(INVALID_OPERAND, "BYTE must be 8-bit size (0,255)");
        has_error = true;
      } else if (e != NO_ERR) { //str2err could not convert
        print_err_to_lis(e, " Invalid operand for BYTE directive ");
        has_error = true;
      } else { //no error and valid BYTE size
      }
    } else { //operand is not a number - consider a label
      auto r2 = is_label_in_sym_tab(ops[0]);
      if (r2 == INVALID_INDEX) { // not in symbol table - check name, store label in sym_tab and emit error
        if (is_valid_label_name(ops[0])) {
          sym_tab.insert(sym_tab.begin(), Symbol{ops[0], "UNK", -1});
        } else {
          print_err_to_lis(INVALID_LABEL_FORMAT, "");
          has_error = true;
        }
      } else if ((sym_tab[r2].value < BYTE_MIN || sym_tab[r2].value > INT8_MAX)) { //label in sym_tab
        print_err_to_lis(INVALID_OPERAND, "BYTE must be 8-bit size (0,255)");
        has_error = true;
      }
    }
  }
}

/* process END directive */
void handleDirEND(vector<string> &ops) {
  short int r;
  if (ops.size() == 1) {
    Error_T e = str2int(ops[0], r);
    if (e != NO_ERR) { //not a valid number - may be label name
      auto r1 = is_label_in_sym_tab(ops[0]);
      if (r1 == INVALID_INDEX) { // not in symbol table - check name, store label in sym_tab and emit error
        if (is_valid_label_name(ops[0])) {
          sym_tab.insert(sym_tab.begin(), Symbol{ops[0], "UNK", -1});
        } else {
          print_err_to_lis(INVALID_LABEL_FORMAT, "");
          has_error = true;
        }
      }
    }
  }
}

/* process EQU directive */
void handleDirEQU(vector<string> &ops, string &p_tok) {
  short int r;
  if (p_tok.empty()) { //preceding token must be label but not present
    print_err_to_lis(UNDEFINED_SYMBOL, "EQU directive must be preceded by a LBL");
    has_error = true;

  }

  else if (ops.size() != 1) {
    print_err_to_lis(MISSING_OPERAND, "EQU must have an operand");
    has_error = true;
  } else if (ops.size() == 1) { // looks fine - operand could be a value or a register
    auto r1 = is_label_in_sym_tab(p_tok);

    auto rr = is_register(ops[0]);
    if (rr == INVALID_INDEX && !is_numeric(ops[0])) { //operand is neither a register nor a value - error
      print_err_to_lis(INVALID_OPERAND, "Operand of EQU must be a value or a REG");
      has_error = true;
    } else if (rr != INVALID_INDEX && !sym_tab[r1].type.compare("UNK")) { //label is a REG with the corresponding REG value
      cout << sym_tab[r1].type << "\tvalue " << sym_tab[r1].value << endl;
      sym_tab[r1].type = "REG";
      sym_tab[r1].value = sym_tab[rr].value;
    } else { //operand is numeric

      Error_T e = str2int(ops[0], r);
      if (e != NO_ERR) { //has error in the value
        print_err_to_lis(e, "Operand of EQU is not valid");
        has_error = true;
      } else {

        if (!sym_tab[r1].type.compare("UNK")) {
          sym_tab[r1].type = "LBL";
          sym_tab[r1].value = r;
        }
      }
    }
  }
}

/* process ORG directive */
void handleDirORG(vector<string> &ops) {
  short int r;
  if (ops.size() != 1) {
    print_err_to_lis(INVALID_OPERAND, "ORG should have an operand");
    has_error = true;
  } else {
    if (is_numeric(ops[0])) {
      Error_T e = str2int(ops[0], r);
      if (e == NO_ERR) {
        loc_counter = r;
      } else {
        print_err_to_lis(INVALID_NUMBER, "ORG operand should be a valid number");
        has_error = true;
      }
    } else {
      print_err_to_lis(INVALID_OPERAND, "ORG operand should be a valid number");
      has_error = true;
    }
  }
}

/* process WORD directive */
void handleDirWORD(vector<string> &ops) {
  short int r;
  if (ops.size() != 1) { //no operand or more than one operand
    print_err_to_lis(NUMBER_OF_OPERANDS_MISMATCH, "WORD must have an operand");
    has_error = true;
  } else {

    if (is_numeric(ops[0])) {
      Error_T e = str2int(ops[0], r);
      if (e == NO_ERR && (r < BYTE_MIN || r > UINT16_MAX)) {
        print_err_to_lis(INVALID_OPERAND, "WORD must be 16-bit size (0,65535)");
        has_error = true;
      } else if (e != NO_ERR) { //str2err could not convert
        print_err_to_lis(e, " Invalid operand for WORD directive ");
        has_error = true;
      } else { //no error and valid BYTE size
      }
    } else { //operand is not a number - consider a label
      auto r2 = is_label_in_sym_tab(ops[0]);
      if (r2 == INVALID_INDEX) { // not in symbol table - check name, store label in sym_tab and emit error
        if (is_valid_label_name(ops[0])) {
          sym_tab.insert(sym_tab.begin(), Symbol{ops[0], "UNK", -1});
        } else {
          print_err_to_lis(INVALID_LABEL_FORMAT, "");
          has_error = true;
        }
      } else if ((sym_tab[r2].value < BYTE_MIN || sym_tab[r2].value > UINT16_MAX)) { //label in sym_tab
        print_err_to_lis(INVALID_OPERAND, "WORD must be 8-bit size (0,255)");
        has_error = true;
      }
    }
  }
}

/* process the directive based on the index in directives */
void process_directive(short int d_id, vector<string> &rec, string p_tok) {
  /************ */
  vector<string> operands = {};
  if (rec.size() == 2) { //has operand
    auto ops = rec[1];
    /* split different operands - separated by comma */
    stringstream ss(ops); //
    string tok;
    while (getline(ss, tok, ',')) {
      operands.push_back(tok);
    }
  }
  directiveIndexes di = static_cast<directiveIndexes>(d_id);

  switch (di) {
  case dirALIGN:
    handleDirALIGN(operands);
    break;
  case dirBSS:
    handleDirBSS(operands);
    break;
  case dirBYTE:
    handleDirBYTE(operands);
    loc_counter += BYTE_INCREASE;
    break;
  case dirEND:
    handleDirEND(operands);
    break;
  case dirEQU:
    handleDirEQU(operands, p_tok);
    break;
  case dirORG:
    handleDirORG(operands);
    break;
  case dirWORD: //6: //WORD
    handleDirWORD(operands);
    loc_counter += WORD_INCREASE;
    break;
  default:
    break;
  }
  return;
}

/*function to validate tokens in a record for pass 1*/
void validate_tokens(vector<string> &toks) {

  if (toks.size() > 3) { //too many tokens in a record
    print_err_to_lis(INVALID_RECORD, "too many tokens ");
    has_error = true;
    return;
  }

  //consider 1st token as instruction
  short int id = check_if_instruction(toks[0]);

  if (id != INVALID_INDEX) { //an instruction - next token must present and operand(s)

    validate_instruction(id, toks);
  } else { //either directive or label
    id = check_if_directive(toks[0]);

    if (id != INVALID_INDEX) { // a directive found - there may or may not have operand(s)
      if (id == 4) {           //EQU should not be here
        print_err_to_lis(UNDEFINED_SYMBOL, "EQU should be preceded by LBL");
        has_error = true;
      } else {
        process_directive(id, toks);
      }

    } else { // this token is a label - following token must be INST/DIR, if any

      if (is_valid_label_name(toks[0])) { //valid name - go ahead
        id = is_label_in_sym_tab(toks[0]);
        if (id == INVALID_INDEX) { //no label in sym_tab with this name - so insert
          sym_tab.insert(sym_tab.begin(), Symbol{toks[0], "LBL", loc_counter});
        } else if (!sym_tab[id].type.compare("UNK")) { //UNK label found - change type and value
          sym_tab[id].type = "LBL";
          sym_tab[id].value = loc_counter;
        } else { //duplicate label
          print_err_to_lis(DUPLICATE_LABEL, "");
          has_error = true;
        }
      } else { //invalid label name
        print_err_to_lis(INVALID_LABEL_FORMAT, "Invalid Label nmae..");
        has_error = true;
      }
      if (toks.size() > 1) { //more tokens are there and has to be INST/DIR
        string prev_tok = toks[0];
        toks.erase(toks.begin()); //erase first token
        id = check_if_instruction(toks[0]);
        if (id != INVALID_INDEX) { //an instruction - next token must present and operand(s)
          validate_instruction(id, toks);
        } else { //either directive or label
          id = check_if_directive(toks[0]);
          if (id != INVALID_INDEX) { // a directive found - there may or may not have operand(s)
            process_directive(id, toks, prev_tok);
          } else { // this tok is a label - again! -Error
            print_err_to_lis(MISSING_INSTRUCTION_DIRECTIVE, "Expected INST/DIR after a LBL");
            has_error = true;
          }
        }

        /****** */
      }
    }
  }
}

/* conducts pass1 */
bool Pass1(string src_fname) {
  // read the src file line by line and process it
  ifstream ifs;
  ifs.open(src_fname);
  string line;          //to hold the content of a line
  short int n_line = 0; //corresponding line number in the src file
  if (ifs.is_open()) {
    //bool no_err = true;
    //read each line of src file and process it
    while (getline(ifs, line)) {
      n_line++;
      ofs << "\t" << n_line << "\t" << line << endl;
      if (line.empty()) {
        continue;
      } else {
        //get tokens from the line
        vector<string> tokens = {};
        get_tokens(line, tokens);
        if (tokens.size() > 0) {
          validate_tokens(tokens);
        } else {
          continue;
        }
      }
    }

    ifs.close();

  } else {
    cout << "Could not open source file: " << src_fname << endl;
    return false;
  }

  for (unsigned short int i = 0; i < sym_tab.size(); ++i) {
    if (!sym_tab[i].type.compare("UNK")) { // found an 'UNK' entry
      has_error = true;
      break;
    }
  }

  if (has_error) {
    //print sym_tab
    cout << "Has Error...printing to LIS" << endl;
    ofs << "First pass error....assembly terminated...." << endl;

    ofs << "\n ****  Symbol Table ***" << std::endl;
    ofs << "Name\t\tType\tValue\tDecimal" << std::endl;

    for (auto s : sym_tab) {
      stringstream ss;
      ss << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << s.value;
      string hex_v;
      if (s.value == -1) {
        hex_v = "FFFF";
      } else {
        string t = ss.str();
        hex_v = (t.length() > 4) ? t.substr(t.length() - 4, 4) : t;
      }
      ofs << s.name << "\t\t" << s.type << "\t" << hex_v << "\t" << s.value << endl;
    }
    ofs.close();
    return false;
  } else {
    cout << "No Error in Pass1...starting Pass 2" << endl;
    // ofs<<"First pass error....assembly terminated...."<<endl;
    //ofs.close();

    if (Pass2(src_fname)) {
      return true;
    } else {
      cout << " Problem in Pass2..." << endl;
      return false;
    }
  }
}
