#include <RAIDA/IAnnotationROOT.h>
#include <string>
#include <RAIDA/NotYetImplementedException.h>

using namespace AIDA ;

bool IAnnotationROOT::addItem(const std::string & key, 
			      const std::string & value, 
			      bool sticky) 
{
  throw(NotYetImplementedException("addItem()","IAnnotation"));
  return true;
}

bool IAnnotationROOT::removeItem(const std::string & key) 
{
  throw(NotYetImplementedException("removeItem()","IAnnotation"));
  return true;
}

std::string IAnnotationROOT::value(const std::string & key) const 
{
  throw(NotYetImplementedException("value()","IAnnotation"));
  return std::string("");
}

void IAnnotationROOT::setValue(const std::string & key, 
			       const std::string & value) 
{
  throw(NotYetImplementedException("setValue()","IAnnotation"));
}

void IAnnotationROOT::setSticky(const std::string & key, bool sticky) 
{
  throw(NotYetImplementedException("setSticky()","IAnnotation"));
}

int IAnnotationROOT::size() const 
{
  throw(NotYetImplementedException("size()","IAnnotation"));
  return 0;
}

std::string IAnnotationROOT::key(int index) const 
{
  throw(NotYetImplementedException("key()","IAnnotation"));
  return std::string("");
}

std::string IAnnotationROOT::value(int index) const 
{
  throw(NotYetImplementedException("value()","IAnnotation"));
  return std::string("");
}

void IAnnotationROOT::reset() 
{
  throw(NotYetImplementedException("reset()","IAnnotation"));
}
