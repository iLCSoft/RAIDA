// -*- C++ -*-
#ifndef AIDA_IMANAGEDOBJECTROOT_H
#define AIDA_IMANAGEDOBJECTROOT_H 1


#include <AIDA/IManagedObject>
#include <string>

namespace AIDA {

/**
 * An object which can be stored in a tree.
 * @see ITree
 *
 * @author The AIDA team (http://aida.freehep.org/)
 *
 */
 
class IManagedObjectROOT : virtual public IManagedObject {

public: 
    /// Destructor.
    virtual ~IManagedObject() { /* nop */; }

    /**
     * Get the name of an IManagedObject.
     * Names can only be changed using the ITree.mv().
     * @return The name of the IManagedObject.
     *
     */ 
    virtual std::string name() const;

    /**
     *  A simple introspection method.
     * It offers to implementations the possibility 
     * to avoid the usage of the dynamic_cast. It appears
     * that this C++ feature is not yet reliable (May 2003)
     * in complex environments that intensivly use the dynamic loading.
     *  The signature of this method follows the qt_cast method found
     * in Qt (see the Q_OBJECT macro).
     *  Example of usage is :
     *      AIDA::IManagedObject* object = tree->find("myData");
     *      if(object) {
     *        AIDA::IHistogram* histo = object->cast("AIDA::IHistogram");
     *        if(histo) {
     *          // the object is an histo.
     *        }
     *      }
     * @param className The name of the class to cast on.
     * @return The right pointer. Return 0 if className is not in the 
     * inheritance tree.
     */ 
    virtual void * cast(const std::string & className) const;
}; // class
} // namespace AIDA
#endif /* ifndef AIDA_IMANAGEDOBJECTROOT_H */
