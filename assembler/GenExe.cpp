#include "GenExe.h"

void getChecksum0(const string &s, string &cs) {
  int result = 0;
  string hex_nums = s.substr(0, 6); //first 2
  // string addr = s.substr(2,4); //next 4 chars address
  string data = s.substr(6);
  short int r;
  for (unsigned short int i = 0; i < hex_nums.size(); i += 2) {
    string v = hex_nums.substr(i, 2);
    r = stoi(v, nullptr, 16);
    result += r;
  }

  for (unsigned short int i = 0; i < data.size(); i++) { //each char in string
    r = data[i];
    result += r;
    // if(isdigit(data[i])){
    //     result += (data[i] - '0');
    // }
    // else{ result += data[i];}
  }
  //get ones complement
  //result += r;
  stringstream ss;
  ss << std::uppercase << std::setw(2) << std::hex << ~result; //ones complement
  string t = ss.str();
  cs = (t.length() > 2) ? t.substr(t.length() - 2, 2) : t;
}

void getChecksum1(const string &s, string &cs) {
  int result = 0;
  short int r;
  for (unsigned short int i = 0; i < s.size(); i += 2) {
    string v = s.substr(i, 2);
    r = stoi(v, nullptr, 16);
    result += r;
  }

  stringstream ss;
  ss << std::uppercase << std::setw(2) << std::hex << ~result; //ones complement
  string t = ss.str();
  cs = (t.length() > 2) ? t.substr(t.length() - 2, 2) : t;
}