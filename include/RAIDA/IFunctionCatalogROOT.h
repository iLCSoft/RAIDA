// -*- C++ -*-
#ifndef AIDA_IFUNCTIONCATALOGROOT_H
#define AIDA_IFUNCTIONCATALOGROOT_H 1

#include <string>
#include <vector>
#include <AIDA/IFunctionCatalog.h>

namespace AIDA {

class IFunction;

/** @interface 
 *
 * Function catalog.
 *
 * @author T. Kraemer, DESY
 * @version $Id: IFunctionCatalogROOT.h,v 1.1 2007-01-02 16:20:45 tkraemer Exp $
 */
 
class IFunctionCatalogROOT : public IFunctionCatalog {

public: 
  /// Destructor.
  virtual ~IFunctionCatalogROOT() { /* nop */; }

  IFunctionCatalogROOT() { /* nop */; }

  /**
   * Remember persistently definition (code!) of a function under a name.
   * Scripted function created by the user may be automatically available
   * in the subsequent analysis sessions. This is also a way to create
   * new names for combinations of exisiting model functions ("G+G+E+P5").
   * Last but not least, system may be easily extended with model functions
   * developed in the programming language directly.
   * Predefined functions: "G","E","Pn".
   */
  virtual bool add(std::string nameId, IFunction * f) ;

  virtual bool add(std::string nameId, const std::string & codelet) ;

  /*
   * Get a list of all available functions.
   */
  virtual std::vector<std::string>  list() ;

  /*
   * Remove function from the catalog.
   */
  virtual void remove(const std::string & nameId) ;

  /*
   * Write contents of the catalog to disk.
   * We have to agree on the format here, or define and XML 
   * entry for IFunctionCatalog!
   */
  virtual bool storeAll(const std::string & nameOnDisk) ;

  /* 
   * Load contents of the catalog from disk
   * We have to agree on the format here, or define and XML 
   * entry for IFunctionCatalog!
   */
  virtual bool loadAll(const std::string & nameOnDisk) ;
}; // class
} // namespace AIDA
#endif /* ifndef AIDA_IFUNCTIONCATALOGROOT_H */
