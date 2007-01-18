// -*- C++ -*-
#include <RAIDA/RAIDAUtil.h>
#include <AIDA/IAxis.h>
#include <iostream>
#include <vector>
#include <string>

using namespace AIDA ;

int RAIDAUtil::binIndexAIDA2ROOT(int index, int nBins)
{
  // Bin numbering transformation from AIDA to ROOT conventions
  int indexROOT = 0;
  if (index <= IAxis::UNDERFLOW_BIN)
    indexROOT = 0;
  else if (index >= nBins )
    indexROOT = nBins+1;
  else if (index == IAxis::OVERFLOW_BIN)
    indexROOT = nBins+1; 
  else
    indexROOT = index + 1;

  return indexROOT;
}

int RAIDAUtil::binIndexROOT2AIDA(int index, int nBins)
{
  // Bin numbering transformation from ROOT to AIDA conventions
  int indexAIDA = 0;
  if (index <= 0)
    indexAIDA = IAxis::UNDERFLOW_BIN;
  else if (index >= nBins+1)
    indexAIDA = IAxis::OVERFLOW_BIN;
  else 
    indexAIDA = index - 1;

  return indexAIDA;
}

bool RAIDAUtil::isOrdered(std::vector<double> x)
{
  if (x[0]<x[x.size()-1])
    {
      for (int i=0 ; i<=(int)x.size()-2 ; i++)
        {
          if (x[i]>=x[i+1])
            {
              return false;
            }
        }
    }
  else if (x[0]>x[x.size()-1])
    {
      for (int i=0 ; i<=(int)x.size()-2 ; i++)
        {
          if (x[i]<=x[i+1])
            {
              return false;
            }
        }
    }
  else
    {
      return false;
    }
  return true;
}

std::string RAIDAUtil::removeWidespaceLeft(std::string s)
{
  while (s.length() > 0)
    {
      if (s[0]==' ') s.erase(0,1);
      else break;
    }
  return s;
}

std::string RAIDAUtil::removeWidespaceRight(std::string s)
{
  while (s.length() > 0)
    {
      if (s[s.length()-1] == ' ') s.erase(s.length()-1,1);
      else break;
    }
  return s;
}

std::string RAIDAUtil::removeWidespaceLeftRight(std::string s)
{
  return removeWidespaceLeft( removeWidespaceRight(s) );
}

std::vector<std::string> RAIDAUtil::splitIntoWords(std::string s,char sep)
{
  s = removeWidespaceLeftRight(s);
  std::vector<std::string> words;

  while (s.length() > 0)
    {
      std::string word;
      std::string::size_type pos = s.find(sep);
      if (pos==std::string::npos) pos=s.length();
      word = s.substr(0,pos);
      s.erase(0,pos+1);
      words.push_back(removeWidespaceRight(word));
      s = removeWidespaceLeft(s);
    }

  return words;
}

