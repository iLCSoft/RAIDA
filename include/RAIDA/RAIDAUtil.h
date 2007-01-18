// -*- C++ -*-
#ifndef AIDA_RAIDAUtil_H
#define AIDA_RAIDAUtil_H 1

#include <iostream>
#include <vector>
#include <string>

/**
 * Class holding utility functions for RAIDA.  
 * @author T. Kraemer, DESY
 * @version $Id: RAIDAUtil.h,v 1.4 2007-01-18 11:04:09 tkraemer Exp $
 */


namespace AIDA {
namespace RAIDAUtil {
  /// converts binindex from AIDA to ROOT conventions
  int binIndexAIDA2ROOT(int index, int nBins);

  /// converts binindex from AIDA to ROOT conventions
  int binIndexROOT2AIDA(int index, int nBins);

  /// Checks if a std::vector<double> is ordered according to the 
  /// magnitude of the values:
  /// x[i] < x[i+1] for all i \in {0,1,2,3...}  or
  /// x[i] > x[i+1] for all i \in {0,1,2,3...}  
  bool isOrdered(std::vector<double> x);

  /** Remove wide spaces " " at the left side of a string.
   * @param s string with any contents 
   * @return string where the wide spaces are removed at the appropriated end
   *         between words, the wide spaces stay untouched.
   */
  std::string removeWidespaceLeft(std::string s);

  /** Remove wide spaces " " at the right side of a string.
   */
  std::string removeWidespaceRight(std::string s);

  /** Remove wide spaces " " at both sides of a string.
   */
  std::string removeWidespaceLeftRight(std::string s);

  /** Split a string into parts separated by a specified separator.
   * wide spaces are removed at the beginning and at the end of the 
   * results. 
   * @param s String to be separated.
   * @param sep separator character.
   * @return a vector of strings containing the different parts.
   */ 
  std::vector<std::string> splitIntoWords(std::string s,char sep);

} // namespace RAIDAUtil
} // namespace AIDA
#endif /* ifndef AIDA_RAIDAUtil_H */
