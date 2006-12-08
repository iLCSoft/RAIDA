// -*- C++ -*-
#ifndef AIDA_IANNOTATIONROOT_H
#define AIDA_IANNOTATIONROOT_H 1

#include <string>
#include <AIDA/IAnnotation.h>

namespace AIDA {

/**
 * The annotation holds arbitrary information represented with (key,value) pairs
 * of strings. A sticky bit is associated to every item to protect it (or not)
 * from a reset operation.
 * 
 * @author T. Kraemer, DESY
 * @version $Id: IAnnotationROOT.h,v 1.1 2006-12-08 10:58:59 tkraemer Exp $
 */

class IAnnotationROOT : public IAnnotation {

public: 
    /// Destructor.
  virtual ~IAnnotationROOT() { /* nop */; }

  IAnnotationROOT() { /* nop */; }

  /**
   * The list of the commonly accepted keys :
   * "Title" for the title.
   *
   */
    
  /**
   * Add a key/value pair with a given sticky flag.
   * If key alredy exists, override its value ?
   * @param key    The key to be added.
   * @param value  The key's value.
   * @param sticky The key's sticky flag. If <code>true</code> the item will
   *               not be removed when the method reset or removeItem are invoked.
   *               The default value for the sticky flag is <code>false</code>.
   * @return false If the key already exists.
   *
   */
  virtual bool addItem(const std::string & key, 
		       const std::string & value, 
		       bool sticky = false) ;

  /**
   * Remove the item indicated by a given key.
   * @param key The key to be removed. If the key is flagged as "sticky" it
   *            will not be removed.
   * @return false If the key is sticky.
   *
   */
  virtual bool removeItem(const std::string & key) ;

  /**
   * Retrieve the value for a given key.
   * @param key The key.
   * @return    The corresponding value.
   *
   */
  virtual std::string value(const std::string & key) const ;

  /**
   * Set the value for a given key.  
   * @param key   The key whose vale is to be changed.
   * @param value The new value.
   *
   */
  virtual void setValue(const std::string & key, 
			const std::string & value) ;

  /**
   * Set the sticky flag for a given key.
   * @param key    The key whose stick flag is to be set.
   * @param sticky The new sticky flag.
   *
   */
  virtual void setSticky(const std::string & key, bool sticky) ;

  /**
   * Get the size of the IAnnotation, i.e. the number of keys contained in it.
   * @return The size of the IAnnotation.
   *
   */
  virtual int size() const ;

  /**
   * Get the key at a given position within the IAnnotation.
   * @param index The key's position within the IAnnotation.
   * @return      The corresponding key.
   *
   */
  virtual std::string key(int index) const ;

  /**
   * Get the value at a given position within the IAnnotation.
   * @param index The value's position within the IAnnotation.
   * @return      The corresponding value.
   *
   */
  virtual std::string value(int index) const ;

  /**
   * Remove all the non-sticky items.
   *
   */
  virtual void reset() ;
}; // class
} // namespace AIDA
#endif /* ifndef AIDA_IANNOTATIONROOT_H */
