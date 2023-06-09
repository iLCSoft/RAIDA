// -*- C++ -*-
#ifndef AIDA_ITREEROOT_H
#define AIDA_ITREEROOT_H 1


#include <AIDA/ITree.h>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <TFile.h>
namespace AIDA {

  ///class IManagedObject;

/**
 * User level interface to a Tree.
 *
 * All paths follow unix convention .., ., /, 
 * backslash is the escape character.
 * Relative paths are allowed.
 *
 * NOTE: - this tree keeps a current position(pwd) within the tree.
 * This may be implemented on a per-thread basis.
 *
 * @author T. Kraemer, DESY
 * @version $Id: ITreeROOT.h,v 1.5 2008-01-30 17:42:20 killenberg Exp $
 */

class ITreeROOT : public ITree {

public: 
    /// Destructor.
  virtual ~ITreeROOT(); // { /* nop */; }

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
  ITreeROOT(const std::string & storeName,
	    const std::string & storeType = "",
	    bool readOnly = false,
	    bool createNew = false,
	    const std::string &options = "");

    ITreeROOT();

  /**
   * Get the name of the store.
   * @return The store's name.
   *
   */
  virtual std::string storeName() const;

  /**
   * Get the IManagedObject at a given path in the ITree. The path can 
   * either be
   * absolute or relative to the current working directory.
   * @param path The path.
   * @return     The corresponding IManagedObject.
   *
   */
  virtual IManagedObject * find(const std::string & path) { throw std::runtime_error("Not implemented"); }

  /**
   * Get a mounted ITree at a given path in the current ITree. The path can either be
   * absolute or relative to the current working directory.
   * @param path The path.
   * @return     The corresponding ITree.
   *
   */
  virtual ITree * findTree(const std::string & path) { throw std::runtime_error("Not implemented"); }

  /**
   * Change to a given directory.
   * @param path The absolute or relative path of the directory we are changing to.
   * @return false If the path does not exist.
   *
   */
  virtual bool cd(const std::string & path) ;

  /**
   * Get the path of the current working directory.
   * @return The path of the current working directory.
   *
   */
  virtual std::string pwd() const;

  /** 
   * List, into a given output stream, all the IManagedObjects, including directories
   * (but not "." and ".."), in a given path. Directories end with "/". The list can be recursive.
   * @param path      The path where the list has to be performed (by default the current directory ".").
   * @param recursive If <code>true</code> the list is extended recursively
   *                  in all the directories under path (the default is <code>false</code>.
   * @param os        The output stream into which the list is dumped (by default the standard output).
   * @return false If the path does not exist.
   *
   */
  virtual bool ls(const std::string & path = ".", 
		  bool recursive = false, 
		  std::ostream & os = std::cout) const;

  /**
   * Get the list of names of the IManagedObjects under a given path, including directories
   * (but not "." and ".."). Directories end with "/".
   * The returned names are appended to the given path unless the latter is ".".
   * @param path      The path where the list has to be performed (by default the current directory ".").
   * @param recursive If <code>true</code> the list is extended recursively
   *                  in all the directories under path (the default is <code>false</code>.
   *
   */
  virtual std::vector<std::string>  listObjectNames(const std::string & path = ".", bool recursive = false) const { throw std::runtime_error("Not implemented"); }

  /**
   * Get the list of types of the IManagedObjects under a given path.
   * The types are the leaf class of the Interface, e.g. "IHistogram1D", "ITuple", etc.
   * Directories are marked with "dir".
   * The order of the types is the same as the order for the listObjectNames() method
   * to achieve a one-to-one correspondance between object names and types.
   * @param path      The path where the list has to be performed (by default the current directory ".").
   * @param recursive If <code>true</code> the list is extended recursively
   *                  in all the directories under path (the default is <code>false</code>.
   *
   */
  virtual std::vector<std::string>  listObjectTypes(const std::string & path = ".", bool recursive = false) const { throw std::runtime_error("Not implemented"); }

  /**
   * Create a new directory. Given a path only the last directory
   * in it is created if all the intermediate subdirectories already exist.
   * @param path The absolute or relative path of the new directory.
   * @return false If a subdirectory within the path does
   *             not exist or it is not a directory. Also if the directory already exists.
   *
   */   
  virtual bool mkdir(const std::string & path);

  /**
   * Create a directory recursively. Given a path the last directory
   * and all the intermediate non-existing subdirectories are created.
   * @param path The absolute or relative path of the new directory.
   * @return false If an intermediate subdirectory
   *             is not a directory, or if the directory already exists.
   *
   */
  virtual bool mkdirs(const std::string & path) { throw std::runtime_error("Not implemented"); }

  /**
   * Remove a directory and all the contents underneeth.
   * @param path The absolute or relative path of the directory to be removed.
   * @return false If path does not exist or if it is not
   *             a directory.
   *
   */
  virtual bool rmdir(const std::string & path) { throw std::runtime_error("Not implemented"); }

  /**
   * Remove an IManagedObject by specifying its path.
   * If the path points to a mount point, the mount point should first commit, then 
   * close and delete the tree object.
   * @param path The absolute or relative path of the IManagedObject to be removed.
   * @return false If path does not exist.
   *
   */
  virtual bool rm(const std::string & path) { throw std::runtime_error("Not implemented"); }

  /**
   * Get the full path of an IManagedObject.
   * @param object The IManagedObject whose path is to be returned.
   * @return       The object's absolute path.
   *               In C++ if the object does not exist, an empty string is returned.
   *
   */
  virtual std::string findPath(const IManagedObject & object) const { throw std::runtime_error("Not implemented"); }

  /**
   * Move an IManagedObject or a directory from one directory to another.
   * @param oldPath The path of the IManagedObject or direcoty to be moved.
   * @param newPath The path of the diretory in which the object has to be moved to.
   * @return false If either path does not exist.
   *
   */
  virtual bool mv(const std::string & oldPath, const std::string & newPath) { throw std::runtime_error("Not implemented"); }

  /**
   * Commit any open transaction to the underlying store(s).
   * It flushes objects into the disk for non-memory-mapped stores.
   * @return false If the underlying store cannot be written out.
   *
   */
  virtual bool commit();

  /**
   * Set the strategy of what should happen if two objects have the same path.
   * Default is overwrite.
   * @param overwrite <code>true</code> to enable overwriting.
   *
   */
  virtual void setOverwrite(bool overwrite = true) { throw std::runtime_error("Not implemented"); }

  /**
   * Copy an object from a path to another.
   * @param oldPath   The path of the object to be copied.
   * @param newPath   The path where the object is to be copied.
   * @param recursive <code>true</code> if a recursive copy has to be performed.
   * @return false If either path does not exist.
   *
   */
  virtual bool cp(const std::string & oldPath, const std::string & newPath, bool recursive = false) { throw std::runtime_error("Not implemented"); }

  /**
   * Create a symbolic link to an object in the ITree.
   * @param path  The absolute or relative path of the object to be linked.
   * @param alias The absolute or relative name of the link.
   * @return false If path or any
   *              subidrectory within path does not exist.
   *
   */
  virtual bool symlink(const std::string & path, const std::string & alias) { throw std::runtime_error("Not implemented"); }

  /**
   * Mounts a tree within another (target) tree. A tree can only be mounted once.
   * Example:
   * <pre>
   *     target.mount("/home/tonyj",tree,"/");
   * </pre>
   * @param path     The path in the target tree
   * @param tree     The tree to mount within the target tree
   * @param treePath The mount point within the tree to be mounted.
   * @return false If something does not exist.
   *
   */
  virtual bool mount(const std::string & path, ITree & tree, const std::string & treePath)  { throw std::runtime_error("Not implemented"); }

  /**
   * Unmount a subtree at a given path (mount point).
   * Whenever a tree is destroyed it first unmounts all dependent trees.
   * @param path The path of the subtree to be unmounted.
   * @return false If path does not exist.
   *
   */
  virtual bool unmount(const std::string & path) { throw std::runtime_error("Not implemented"); }

  /**
   * Closes the underlying store.
   * Changes will be saved only if commit() has been called before.
   * The call is propagated to the dependent mounted trees.
   * @return false If there are problems writing out
   *         the underlying store.
   *
   */
  virtual bool close() ;

  /**
   *  See IManagedObject for a description.
   * @param className The name of the class to cast on.
   * @return The right pointer. Return 0 if failure.
   */ 
  virtual void * cast(const std::string & className) const { throw std::runtime_error("Not implemented"); }

private:

  TFile *_ROOTFile;
  std::string _storeName;

}; // class
} // namespace AIDA
#endif /* ifndef AIDA_ITREEROOT_H */

