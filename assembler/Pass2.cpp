#include "Pass2.h"

extern short loc_counter;
extern bool has_error;
extern vector<Inst> inst_set;
extern vector<Symbol> sym_tab;

//prints error message to LIS file
void print_err_to_lis2(Error_T e, string s){

    string msg = "***** ";
    switch(e){
        case NO_ERR:
            ofs<<"\t*****"<< s<<endl;
            break;
        case MISSING_OPERAND:
            ofs<<"\t****** Expected operand: " << s<<endl;
            break;
        case ILLEGAL_OPERAND:
            ofs<<"\t****** Illegal operand: " <<s<<endl;
            break;
        case  NUMBER_OF_OPERANDS_MISMATCH:
            ofs<<"\t ***** Too many/few number of operands: "<<s<<endl;
            break;
        case INVALID_OPERAND:
            ofs<<"\t ***** Invalid operands: "<<s<<endl;
            break;
        case INVALID_REGISTER:
            ofs<<"\t ***** Invalid REG: "<<s<<endl;
            break;
        case MISSING_INSTRUCTION_DIRECTIVE:
            ofs<<"\t ***** Expected INST/DIR: "<<s<<endl;
            break; 
        case INVALID_LABEL_FORMAT:
            ofs<<"\t ***** Not valid label: "<<s<<endl;
            break; 
        case UNDEFINED_SYMBOL:
            ofs<<"\t ***** Undefined operand(symbol): "<<s<<endl;
            break; 
        case DUPLICATE_LABEL:
            ofs<<"\t ***** Duplicate LBL: "<<s<<endl;
            break;
        case INVALID_NUMBER:
            ofs<<"\t ***** Invalid Number: "<<s<<endl;
            break;
        case INVALID_RECORD:
            ofs<<"\t ***** Invalid Record: "<<s<<endl;
            break;
        default:
            break;

    }

}

InstType getInstType(vector<Operand_T> ops){
    if(ops.size() == 1 && ops[0] == L10){
        return Branch10;
    }
    else if(ops.size() == 1 && ops[0] == L13){
        return Branch13;
    }
    else if (ops.size() == 1 && (ops[0] == R || ops[0] == SA)){
        return OneAddr;
    }
    else if(ops.size() == 2 && ops[0] == CON_R && ops[1] == R){
        return Arith;
    }
    else if(ops.size() == 2 && ops[0] == R && ops[1] == R){
        return RegExchange;
    }
    else if(ops.size() == 2 && ops[0] == IDR && ops[1] == R){
        return MemAccessLD;
    }
    else if(ops.size() == 2 && ops[0] == R && ops[1] == IDR){
        return MemAccessST;
    }
    else if(ops.size() == 2 && ops[0] == BYTE && ops[1] == R){
        return RegInit;
    }
    else if(ops.size() == 3 && ops[0] == COND_CEC && ops[1] == TCFC && ops[2] == TCFC){
        return Cex;
    }
    else if(ops.size() == 3 && ops[0] == R && ops[1] == OFFSET && ops[2] == R){
        return MemAccessRelLD;
    }
    else { return MemAccessRelST;}
}
/* generate opcode for Br13 instruction BL*/
void handleBranch13(short int inst_id, vector<string>& ops, unsigned short& opcode){
    //find label index from sym_tab
    auto lbl_index = is_label_in_sym_tab(ops[0]);
    short int offset = sym_tab[lbl_index].value - loc_counter -2;
    auto opcode = stoi(inst_set[inst_id].opcode, nullptr,2);
    Br13Overlay instCode;
    instCode.inst._offset = offset >> 1;
    instCode.inst._opCode = opcode;

    opcode = instCode.sh;
    // //print hex value
    // stringstream ss;
    // ss<<std::uppercase<<std::setfill('0')<<std::setw(4)<<std::hex<<instCode.sh;
    // string t = ss.str();
    // string hex_v = (t.length()> 4)? t.substr(t.length()-4,4):t;
    // ofs<<"\t"<<loc_counter<<"\t"<<hex_v<<"\t"<<orig_line<<endl;
}

/* generate opcode for Br13 instruction BL*/
void handleBranch10(short int inst_id, vector<string>& ops, unsigned short& opcode){
    //find label index from sym_tab
    auto lbl_index = is_label_in_sym_tab(ops[0]);
    short int offset = sym_tab[lbl_index].value - loc_counter -2;
    auto opcode = stoi(inst_set[inst_id].opcode, nullptr,2);
    Br13Overlay instCode;
    instCode.inst._offset = offset >> 1;
    instCode.inst._opCode = opcode;

    opcode = instCode.sh;
    
}

/* generate opcode for Br13 instruction BL*/
void handleArith(short int inst_id, vector<string>& ops, unsigned short& opcode){
    //find label index from sym_tab
    auto src_index = is_label_in_sym_tab(ops[0]);
    auto dst_index = is_label_in_sym_tab(ops[1]);
    short int offset = sym_tab[lbl_index].value - loc_counter -2;
    auto opcode = stoi(inst_set[inst_id].opcode, nullptr,2);
    ArithOverlay instCode;
    instCode.inst._offset = offset >> 1;
    instCode.inst._opCode = opcode;

    opcode = instCode.sh;
    
}


/* validates the operands of an instruction - if not, error message is written to the LIS file */
void proc_instruction(short int inst_id, vector<string> &toks, string & line){
    vector<string> operands = {};
    auto ops = toks[1]; //first token is the instruction and 2nd token holds operand(s)
    stringstream ss(ops); //to split into separate operands from the token
    string tok;
    while(getline(ss, tok, ',')){ //operands are separated by comma ','
        operands.push_back(tok);
    }
    auto ex_ops = inst_set[inst_id].expected_operands;
    //assume - error checked in pass1
    InstType it = getInstType(ex_ops);
    unsigned short opcode;
    switch(it){
        case Branch13:
            handleBranch13(inst_id, operands, opcode);          
        case Branch10:
            handleBranch10(inst_id, operands, opcode);
            break;
        case Arith:
            handleArith(inst_id, operands, opcode);
            break;
        case RegExchange:
            break;
        case OneAddr:
            break;
        case MemAccessLD:
            break;
        case MemAccessST:
            break;
        case Cex:
            break;
        case RegInit:
            break;
        case MemAccessRelLD:
            break;
        case MemAccessRelST:
            break;
        default:
            break;
    }
        
    
    loc_counter +=2; //each instruction needs 2-bytes  
}
/* process the directive based on the index in directives */
void proc_directive(short int d_id, vector<string> & rec, string p_tok ){
    /************ */
    vector<string> operands = {};
    if(rec.size() == 2){ //has operand
        auto ops = rec[1];
         /* split different operands - separated by comma */
        stringstream ss(ops); //
        string tok;
        while(getline(ss, tok, ',')){
             operands.push_back(tok);
        }
    }
    directiveIndexes di = static_cast<directiveIndexes>(d_id);
    short int r;
    short int r1;
    switch(di){ //d_id){
        case dirALIGN: //0: //ALIGN
            if(operands.size() != 0){ //has operand
                print_err_to_lis(ILLEGAL_OPERAND, "directive ALIGN does not take an operand");
                has_error = true;
            }
            else{
                if(loc_counter%2 != 0){loc_counter++;} //if odd increment the address
            }
            break;
        case dirBSS: //1: //BSS
            if(operands.size() != 1){ //no operand or more than one operand
                print_err_to_lis(NUMBER_OF_OPERANDS_MISMATCH, "BSS must have one and only one operand");
                has_error = true;
            }
            else{
                if(is_numeric(operands[0])){
                    Error_T e = str2int(operands[0],r);
                    if(e == NO_ERR){
                        loc_counter += r;
                    }
                    else{
                        print_err_to_lis(e, "BSS operand should be a valid number");
                        has_error = true;
                    }
                    
                }
                else{
                    auto r2 = is_label_in_sym_tab(operands[0]);
                    if(r2 == INVALID_INDEX){ // not in symbol table - check name, store label in sym_tab and emit error
                        if(is_valid_label_name(operands[0])){
                            sym_tab.insert(sym_tab.begin(), Symbol{operands[0],"UNK",-1});
                        }
                        else{
                            print_err_to_lis(INVALID_LABEL_FORMAT, "");
                            has_error = true;
                        }
                        
                    }
                    else{
                        loc_counter += sym_tab[r2].value;
                    }
                   
                }
            }
            break;
        case dirBYTE: //2: //BYTE
            if(operands.size() != 1){ //no operand or more than one operand
                print_err_to_lis(NUMBER_OF_OPERANDS_MISMATCH, "BYTE must have one and only one operand");
                has_error = true;
            }
            else{
                if(is_numeric(operands[0])){
                    Error_T e = str2int(operands[0],r);
                    if(e == NO_ERR && ( r < BYTE_MIN || r > INT8_MAX)){
                        print_err_to_lis(INVALID_OPERAND, "BYTE must be 8-bit size (0,255)");
                        has_error= true;
                    }
                    else if (e != NO_ERR){ //str2err could not convert 
                        print_err_to_lis(e, " Invalid operand for BYTE directive ");
                        has_error = true;
                    }
                    else{ //no error and valid BYTE size
                        
                    }
                }
                else{ //operand is not a number - consider a label
                    auto r2 = is_label_in_sym_tab(operands[0]);
                    if(r2 == INVALID_INDEX){ // not in symbol table - check name, store label in sym_tab and emit error
                        if(is_valid_label_name(operands[0])){
                            sym_tab.insert(sym_tab.begin(), Symbol{operands[0],"UNK",-1});
                        }
                        else{
                            print_err_to_lis(INVALID_LABEL_FORMAT, "");
                            has_error = true;
                        }
                    }
                    else if(( sym_tab[r2].value < BYTE_MIN || sym_tab[r2].value > INT8_MAX)){ //label in sym_tab
                         print_err_to_lis(INVALID_OPERAND, "BYTE must be 8-bit size (0,255)");
                        has_error= true;
                    }
                }
                
            }
            loc_counter += BYTE_INCREASE;
            break;
        case dirEND: //3: //END
            if(operands.size()==1){
                Error_T e = str2int(operands[0],r);
                if(e != NO_ERR){ //not a valid number - may be label name 
                    auto r1 = is_label_in_sym_tab(operands[0]);
                    if(r1 == INVALID_INDEX){ // not in symbol table - check name, store label in sym_tab and emit error
                        if(is_valid_label_name(operands[0])){
                            sym_tab.insert(sym_tab.begin(), Symbol{operands[0],"UNK",-1});
                        }
                        else{
                            print_err_to_lis(INVALID_LABEL_FORMAT, "");
                            has_error = true;
                        }
                        
                    }
                    
                }
            }
            
            break;
        case dirEQU: //4: //EQU
            
            if(p_tok.empty()){ //preceding token must be label but not present
                print_err_to_lis(UNDEFINED_SYMBOL,"EQU directive must be preceded by a LBL");
                has_error = true;
                
            }
            
            else if(operands.size()!=1){ 
                print_err_to_lis(MISSING_OPERAND, "EQU must have an operand");
                has_error = true;
            }
            else if (operands.size()==1){ // looks fine - operand could be a value or a register
                r1 =  is_label_in_sym_tab(p_tok);
                
                auto rr = is_register(operands[0]);
                if(rr == INVALID_INDEX && !is_numeric(operands[0])){ //operand is neither a register nor a value - error
                    print_err_to_lis(INVALID_OPERAND, "Operand of EQU must be a value or a REG");
                    has_error = true;
                }
                else if(rr != INVALID_INDEX && !sym_tab[r1].type.compare("UNK")){ //label is a REG with the corresponding REG value
                    cout<< sym_tab[r1].type<<"\tvalue "<< sym_tab[r1].value<<endl;
                    sym_tab[r1].type = "REG";
                    sym_tab[r1].value = sym_tab[rr].value;
                }
                else{ //operand is numeric
                   
                    Error_T e = str2int(operands[0],r);
                    if(e != NO_ERR){ //has error in the value
                        print_err_to_lis(e, "Operand of EQU is not valid");
                        has_error = true; 
                    }
                    else{
                        
                        if(!sym_tab[r1].type.compare("UNK")){
                            sym_tab[r1].type = "LBL";
                            sym_tab[r1].value = r;
                        }
                        
                    }
                }
            }
     
            break;
        case dirORG: // 5: //ORG
            if(operands.size()!=1){ 
                print_err_to_lis(INVALID_OPERAND, "ORG should have an operand");
                has_error = true;
            }
            else{
                if(is_numeric(operands[0])){
                    Error_T e = str2int(operands[0], r);
                    if(e == NO_ERR){
                        loc_counter = r;
                    }
                    else{
                       print_err_to_lis(INVALID_NUMBER, "ORG operand should be a valid number");
                       has_error = true; 
                    }
                }
                else{
                    print_err_to_lis(INVALID_OPERAND, "ORG operand should be a valid number");
                    has_error = true; 
                }
               
            }
            break;
        case dirWORD: //6: //WORD
            if(operands.size() != 1){ //no operand or more than one operand
                print_err_to_lis(NUMBER_OF_OPERANDS_MISMATCH, "WORD must have an operand");
                has_error = true;
            }
            else{

                if(is_numeric(operands[0])){
                    Error_T e = str2int(operands[0],r);
                    if(e == NO_ERR && ( r < BYTE_MIN || r > UINT16_MAX)){
                        print_err_to_lis(INVALID_OPERAND, "WORD must be 16-bit size (0,65535)");
                        has_error= true;
                    }
                    else if (e != NO_ERR){ //str2err could not convert 
                        print_err_to_lis(e, " Invalid operand for WORD directive ");
                        has_error = true;
                    }
                    else{ //no error and valid BYTE size
                        
                    }
                }
                else{ //operand is not a number - consider a label
                    auto r2 = is_label_in_sym_tab(operands[0]);
                    if(r2 == INVALID_INDEX){ // not in symbol table - check name, store label in sym_tab and emit error
                        if(is_valid_label_name(operands[0])){
                            sym_tab.insert(sym_tab.begin(), Symbol{operands[0],"UNK",-1});
                        }
                        else{
                            print_err_to_lis(INVALID_LABEL_FORMAT, "");
                            has_error = true;
                        }
                    }
                    else if(( sym_tab[r2].value < BYTE_MIN || sym_tab[r2].value > UINT16_MAX)){ //label in sym_tab
                        print_err_to_lis(INVALID_OPERAND, "WORD must be 8-bit size (0,255)");
                        has_error= true;
                    }
                }
               
            }
            loc_counter += WORD_INCREASE;
           
            break;
        default:
             
            break;
        

    }
    return;
    /****************** */
}

   


/*function to validate tokens in a record for pass 1*/
void proc_tokens(vector<string> &toks, string &line){

    //consider 1st token as instruction
    short int id = check_if_instruction(toks[0]);
    
    if(id != INVALID_INDEX){ //an instruction - next token must present and operand(s)  
        
        proc_instruction(id,toks, line);
    }
    else{//either directive or label
        id = check_if_directive(toks[0]);
        
        if(id != INVALID_INDEX){ // a directive found - there may or may not have operand(s)
            proc_directive(id, toks, line);
        }
        else{ // this token is a label - following token must be INST/DIR, if any
         
          if(toks.size()>1){ //more tokens are there and has to be INST/DIR
            string prev_tok = toks[0];
            toks.erase(toks.begin()); //erase first token
            id = check_if_instruction(toks[0]);
            if(id != INVALID_INDEX){ //an instruction - next token must present and operand(s)  
                proc_instruction(id,toks, line);
            }
            else{//either directive or label
                id = check_if_directive(toks[0]);
                if(id != INVALID_INDEX){ // a directive found - there may or may not have operand(s)
                    proc_directive(id, toks, prev_tok, line);
                }
            }    
        }
             
        }

    }

}


/* conducts pass1 */
bool Pass2(string src_fname){
    // read the src file line by line and process it
    ifstream ifs;
    ifs.open(src_fname);
    string line; //to hold the content of a line
    short int n_line = 0; //corresponding line number in the src file
    if(ifs.is_open()){
        while(getline(ifs, line)){
            n_line++;
            
            if(line.empty()){ 
                ofs<<"\t"<<n_line<<"\t"<<line<<endl;
                continue;
            }
            else{
                //get tokens from the line 
                vector<string> tokens = {};
                get_tokens(line, tokens); 
                if(tokens.size() > 0){
                  proc_tokens(tokens, line);
                }
                else{
                    ofs<<"\t"<<n_line<<"\t"<<line<<endl; 
                    continue;
                }
                
            }
           
        }

        ifs.close();
       
    }
    else
    {
        cout<<"Could not open source file: "<<src_fname<<endl;
        return false;
    }

        
    cout<<"...printing to LIS"<<endl;
    ofs<<"Successfully completed Aseembly"<<endl;

    ofs<<"\n ****  Symbol Table ***"<<std::endl;
    ofs<<"Name\t\tType\tValue\tDecimal"<<std::endl;
    
    for(auto s : sym_tab){
        stringstream ss;
        ss<<std::uppercase<<std::setfill('0')<<std::setw(4)<<std::hex<<s.value;
        string hex_v;
        if(s.value == -1){ hex_v = "FFFF"; } else {hex_v = ss.str();}
        ofs<<s.name<<"\t\t"<<s.type<<"\t"<<hex_v<<"\t"<<s.value<<endl;
    }
    ofs.close();
    return true;
      
}
    