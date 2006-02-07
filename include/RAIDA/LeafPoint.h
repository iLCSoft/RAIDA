#ifndef AIDA_LEAFPOINT_H
#define AIDA_LEAFPOINT_H 1

#include <string>
#include <TROOT.h>

using namespace std;

namespace AIDA {

class LeafPoint {

public:

  LeafPoint();

  LeafPoint(string type);

  LeafPoint(string type,string name);

  LeafPoint(const LeafPoint & rhs);

  void* getValue() const; 

  double getDouble() const ;

  float getFloat() const ; 

  int getInt() const ;

  short getShort() const ; 

  long getLong() const ;

  char getChar() const ;

  bool getBool() const ; 

  std::string getString() const ;

  char getType() const ;

  string getTypeLong() const ;

  string getName() const ;

  string getROOTNameType() const ;

  void clear();

  bool set(const float v); 

  bool set(const double v); 

  bool set(const int v); 

  bool set(const short v); 

  bool set(const long v); 

  bool set(const char v); 

  bool set(const bool v); 

  bool set(const string v); 

  //private:

  char _leafType;

  string _leafName;

  Float_t _f;

  Double_t _d;

  Int_t _i;

  Short_t _s; // Signed Short integer 

  // Long64_t _l;

  Int_t _l; // Long is treated as int because there is no normal long in ROOT

  Char_t _c; 

  Bool_t _b;

  string _st;

}; // end class
} // namespace AIDA
#endif /* ifndef AIDA_LEAFPOINT_H */
