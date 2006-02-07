// -*- C++ -*-
#ifndef AIDA_NAMING_H
#define AIDA_NAMING_H 1

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace AIDA {
class Naming {

public:

  static string binEntry(const string & name) ;

  static string binContents(const string & name) ;

  static string binMeanX(const string & name) ;

  static string binMeanY(const string & name) ;

  static string binMeanZ(const string & name) ;

  static string titleBinEntry(const string & name) ;

  static string titleBinContents(const string & name) ;

  static string titleBinMeanX(const string & name) ;

  static string titleBinMeanY(const string & name) ;

  static string titleBinMeanZ(const string & name) ;

protected:

  static string mergeNames(const string & n1,const string & n2) ;

};
} // namespace AIDA
#endif /* ifndef AIDA_PATHNAME_H */
