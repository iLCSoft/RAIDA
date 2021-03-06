// -*- C++ -*-
#ifndef AIDA_PATHNAME_H
#define AIDA_PATHNAME_H 1

#include <iostream>
#include <string>
#include <vector>

/**
 * This class provides functionality to separate the path and filename 
 * information from each other.
 * @author T. Kraemer, DESY
 * @version $Id: PathName.h,v 1.3 2006-12-04 17:24:06 tkraemer Exp $
 */

using namespace std;

namespace AIDA {
class PathName {
public:
  PathName();
  PathName(const string rawName);
  void setPathName(string rawName);
  void changePath(string rawPath);

  string getName() const;
  string getName(int number) const;
  string getPath()const;
  string getPathTo(int number)const;
  string getPathName()const;
  string getPathNameTemp()const;
  string getNameTemp()const;
  int getNumberOfNames()const;
  bool onlyName()const;
  bool isEmpty()const;
protected:
  void clean();
private:
  string _rawPathName;
  vector<string> _names;
  bool _isEmpty;
  bool _isRelative;
};
} // namespace AIDA
#endif /* ifndef AIDA_PATHNAME_H */
