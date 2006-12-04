#include <iostream>
#include <string>

/** This header file provides a mechanism, which makes the name of a
 * a CVS tag available for a c++ program. This can be used to print the 
 * current version of a software package to the screen.
 *
 * The function getName() returns a string containing the CVS tag name.  
 * This only works, if a tagged version of the sources is "checked out" with the 
 * "-r" option. To check out version "v00-01" of the project "nnTrainer" type: 
 *
 * cvs co -r v00-01 nnTrainer
 *
 * If a not tagged version is checked out, getName() returns an empty string. 
 * This also is the case if the latest version is the 
 * tagged version, but the check out is done without the "-r" option.
 * 
 * The getName() function reads out the value of the "Name" keyword. 
 * To make this work properly add this file with 
 *
 * cvs add -kkv Revision.h
 * cvs ci Revision.h
 *
 * to your CVS repository. If you check in this file together with other files
 * to create a new CVS repository, the keyword modus has to be set after 
 * the check in using 
 *
 * cvs admin -kkv Revision.h 
 *
 * (usually "-kkv" should be the standard mode. In this case you can omit
 * this command.) 
 *
 * To tag a version of the project "nnTrain" type:
 *
 * cd nnTrain 
 * cvs tag v00-01 . 
 *
 * To remove a tag type:
 * 
 * cd nnTrain
 * cvs tag -d v00-01 . 
 * @author T. Kraemer, DESY
 * @version $Id: Revision.h,v 1.2 2006-12-04 17:36:39 tkraemer Exp $
 */

namespace Revision {

std::string getName() 
{
  std::string CVSTagName("$Name: not supported by cvs2svn $"); 

  if (CVSTagName.size() == 0) return "";

  std::string testName;
  testName  = "$";
  testName += "Name:  ";
  testName += "$";
  if (CVSTagName == testName) return "";

  if (CVSTagName.find("$Name:") < CVSTagName.length())
    {
      CVSTagName.erase(CVSTagName.find("$Name:"),6);
    }
  while (CVSTagName.size() > 0 && CVSTagName[0] == ' ')
    {
      CVSTagName.erase(0,1);
    }
  if (CVSTagName.find("$") < CVSTagName.length())
    {
      CVSTagName.erase(CVSTagName.find("$"),1);
    }
  while (CVSTagName.size() > 0 && CVSTagName[CVSTagName.size()-1] == ' ')
    {
      CVSTagName.erase(CVSTagName.size()-1,1);
    }

  return CVSTagName;
}

}


