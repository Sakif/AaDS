
#include "Globals.h"
#include "Pass1.h"
#include "Pass2.h"
//#include "GenExe.h"

int main(int argc, char *argv[]) {

  init_globals(argv[1]);
  if (Pass1(argv[1])) {
    //cout<<"Pass1 done"<<endl;
    if (Pass2(argv[1])) {
      cout << "Assembly completed successfully..." << endl;
    } else {
      cout << "Pass2 failed...program terminates..." << endl;
      system("pause");
      exit(0);
    }
  } else {
    cout << "Pass1 failed...program terminates..." << endl;
    system("pause");
    exit(0);
  }

  // string fname = "19 04 28 - Users Guide Example.xme";
  // cout<<"string len: "<<fname.size();

  // if(fname.size()>28){
  //     string str28 = fname.substr(0,28);
  //     cout<<"string 28: "<< str28;
  // }

  // string test_str = "0D0000A2ex01.txt";
  // string check;

  // getChecksum0(test_str, check);
  // cout<<test_str<<"\t"<<check<<endl;

  // test_str = "1F000019 04 28 - Users Guide Examp";
  // getChecksum0(test_str, check);
  // cout<<test_str<<"\t"<<check<<endl;

  // test_str = "0500800000";
  // getChecksum1(test_str, check);
  // cout<<test_str<<"\t"<<check<<endl;

  // test_str = "05FF000100";
  // getChecksum1(test_str, check);
  // cout<<test_str<<"\t"<<check<<endl;

  // test_str = "150100006C017000500A500240AA45FD271154FF3F";
  // getChecksum1(test_str, check);
  // cout<<test_str<<"\t"<<check<<endl;
}
