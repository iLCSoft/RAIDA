// -*- C++ -*-
#ifndef AIDA_ITREEFACTORYROOT_H
#define AIDA_ITREEFACTORYROOT_H 1

#include <AIDA/ITreeFactory.h>
#include <AIDA/ITree.h>

#include <string>



namespace AIDA {

class ITree;

/**
 * The creator of trees.
 *
 * @author The AIDA team (http://aida.freehep.org/)
 */
 
class ITreeFactoryROOT : public ITreeFactory {

public: 
    /// Destructor.
    virtual ~ITreeFactoryROOT() { /* nop */; }

    /**
     * Creates a new tree that is not associated with a store.
     */
  virtual ITree * create();

    /**
     * Creates a new tree and associates it with a store.
     * The store is assumed to be read/write.
     * The store will be created if it does not exist.
     * @param storeName The name of the store, if empty (""), the tree is created
     *                  in memory and therefore will not be associated with a file.
     * @param storeType Implementation specific string, may control store type
     * @param readOnly If true the store is opened readonly, an exception if it does not exist
     * @param createNew If false the file must exist, if true the file will be created
     * @param options Other options, currently are not specified
     *
     */
  virtual ITree * create(const std::string & storeName, 
                         const std::string & storeType = "", 
                         bool readOnly = false, 
                         bool createNew = false, 
                         const std::string & options = "");

}; // class
} // namespace AIDA
#endif /* ifndef AIDA_ITREEFACTORYROOT_H */
