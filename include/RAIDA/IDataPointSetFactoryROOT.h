// -*- C++ -*-
#ifndef AIDA_IDATAPOINTSETFACTORYROOT_H
#define AIDA_IDATAPOINTSETFACTORYROOT_H 1
#include <AIDA/IDataPointSetFactory.h>

#include <string>
#include <vector>

namespace AIDA {

  class ICloud1D;
  class ICloud2D;
  class ICloud3D;
  class IDataPointSet;
  class IHistogram1D;
  class IHistogram2D;
  class IHistogram3D;
  class IProfile1D;
  class IProfile2D;
  class ITree;

/**
 * Basic user-level interface for creating a factory
 * of IDataPointSet.
 * 
 * @author T. Kraemer, DESY
 * @version $Id: IDataPointSetFactoryROOT.h,v 1.2 2006-12-04 17:24:06 tkraemer Exp $
 */

class IDataPointSetFactoryROOT : public IDataPointSetFactory {

public: 
    /// Destructor.
    virtual ~IDataPointSetFactoryROOT() { /* nop */; }

  IDataPointSetFactoryROOT(ITree & tree);
  IDataPointSetFactoryROOT();

    /**
     * Create an empty IDataPointSet.
     * @param path        The path of the IDataPointSet. The path can either be a relative or full path.
     *                    ("/folder1/folder2/dataName" and "../folder/dataName" are valid paths).
     *                    All the directories in the path must exist. The characther `/` cannot be used
     *                    in names; it is only used to delimit directories within paths.
     * @param title       The title of the IDataPointSet.
     * @param dimOfPoints The dimension of the IDataPoints that can be stored in the set.
     * @return            The newly created IDataPointSet.
     *
     */
  ///virtual IDataPointSet * create(const std::string & path, const std::string & title, int dimOfPoints) ;

    /**
     * Create an empty IDataPointSet.
     * @param pathAndTitle The path of the IDataPointSet. The path can either be a relative or full path.
     *                     The last part of the path is used as the title.
     *                     ("/folder1/folder2/dataTitle" and "../folder/dataTitle" are valid paths).
     *                     All the directories in the path must exist. The characther `/` cannot be used
     *                     in names; it is only used to delimit directories within paths.
     * @param dimOfPoints  The dimension of the IDataPoints that can be stored in the set.
     * @return             The newly created IDataPointSet.
     *
     */
  ///virtual IDataPointSet * create(const std::string & pathAndTitle, int dimOfPoints) ;

    /**
     * Create a two dimensional IDataPointSet providing the data along y (the x value is 
     * the index of the y value in the array).
     * @param path  The path of the IDataPointSet. The path can either be a relative or full path.
     *              ("/folder1/folder2/dataTitle" and "../folder/dataTitle" are valid paths).
     *              All the directories in the path must exist. The characther `/` cannot be used
     *              in names; it is only used to delimit directories within paths.
     * @param title The title of the IDataPointSet.
     * @param y     The array of the y values
     * @param ey    The array with the symmetric errors on y
     * @return      The created IDataPointSet.
     *
     */
  ///virtual IDataPointSet * createY(const std::string & path, const std::string & title, const std::vector<double>  & y, const std::vector<double>  & ey) ;

    /**
     * Create a two dimensional IDataPointSet providing the data along y (the x value is 
     * the index of the y value in the array).
     * @param path  The path of the IDataPointSet. The path can either be a relative or full path.
     *              ("/folder1/folder2/dataTitle" and "../folder/dataTitle" are valid paths).
     *              All the directories in the path must exist. The characther `/` cannot be used
     *              in names; it is only used to delimit directories within paths.
     * @param title The title of the IDataPointSet.
     * @param y     The array of the y values
     * @param eyp   The array with the plus errors on y
     * @param eym   The array with the minus errors on y
     * @return      The created IDataPointSet.
     *
     */
  ///virtual IDataPointSet * createY(const std::string & path, const std::string & title, const std::vector<double>  & y, const std::vector<double>  & eyp, const std::vector<double>  & eym) ;

    /**
     * Create a two dimensional IDataPointSet providing the data along y (the x value is 
     * the index of the y value in the array).
     * @param pathAndTitle The path of the IDataPointSet. The path can either be a relative or full path.
     *                     The last part of the path is used as the title.
     *                     ("/folder1/folder2/dataTitle" and "../folder/dataTitle" are valid paths).
     *                     All the directories in the path must exist. The characther `/` cannot be used
     *                     in names; it is only used to delimit directories within paths.
     * @param y            The array of the y values
     * @param ey           The array with the symmetric errors on y
     * @return             The created IDataPointSet.
     *
     */
  ///virtual IDataPointSet * createY(const std::string & pathAndTitle, const std::vector<double>  & y, const std::vector<double>  & ey) ;

    /**
     * Create a two dimensional IDataPointSet providing the data along y (the x value is 
     * the index of the y value in the array).
     * @param pathAndTitle The path of the IDataPointSet. The path can either be a relative or full path.
     *                     The last part of the path is used as the title.
     *                     ("/folder1/folder2/dataTitle" and "../folder/dataTitle" are valid paths).
     *                     All the directories in the path must exist. The characther `/` cannot be used
     *                     in names; it is only used to delimit directories within paths.
     * @param y            The array of the y values
     * @param eyp          The array with the plus errors on y
     * @param eym          The array with the minus errors on y
     * @return             The created IDataPointSet.
     *
     */
  ///virtual IDataPointSet * createY(const std::string & pathAndTitle, const std::vector<double>  & y, const std::vector<double>  & eyp, const std::vector<double>  & eym) ;

    /**
     * Create a two dimensional IDataPointSet providing the data along x (the y value is 
     * the index of the x value in the array).
     * @param path  The path of the IDataPointSet. The path can either be a relative or full path.
     *              ("/folder1/folder2/dataTitle" and "../folder/dataTitle" are valid paths).
     *              All the directories in the path must exist. The characther `/` cannot be used
     *              in names; it is only used to delimit directories within paths.
     * @param title The title of the IDataPointSet.
     * @param x     The array of the x values
     * @param ex    The array with the symmetric errors on x
     * @return      The created IDataPointSet.
     *
     */
  ///virtual IDataPointSet * createX(const std::string & path, const std::string & title, const std::vector<double>  & x, const std::vector<double>  & ex) ;

    /**
     * Create a two dimensional IDataPointSet providing the data along x (the y value is 
     * the index of the x value in the array).
     * @param path  The path of the IDataPointSet. The path can either be a relative or full path.
     *              ("/folder1/folder2/dataTitle" and "../folder/dataTitle" are valid paths).
     *              All the directories in the path must exist. The characther `/` cannot be used
     *              in names; it is only used to delimit directories within paths.
     * @param title The title of the IDataPointSet.
     * @param x     The array of the x values
     * @param exp   The array with the plus errors on x
     * @param exm   The array with the minus errors on x
     * @return      The created IDataPointSet.
     *
     */
  ///virtual IDataPointSet * createX(const std::string & path, const std::string & title, const std::vector<double>  & x, const std::vector<double>  & exp, const std::vector<double>  & exm) ;

    /**
     * Create a two dimensional IDataPointSet providing the data along x (the y value is 
     * the index of the x value in the array).
     * @param pathAndTitle The path of the IDataPointSet. The path can either be a relative or full path.
     *                     The last part of the path is used as the title.
     *                     ("/folder1/folder2/dataTitle" and "../folder/dataTitle" are valid paths).
     *                     All the directories in the path must exist. The characther `/` cannot be used
     *                     in names; it is only used to delimit directories within paths.
     * @param x            The array of the x values
     * @param ex           The array with the symmetric errors on x
     * @return             The created IDataPointSet.
     *
     */
  ///virtual IDataPointSet * createX(const std::string & pathAndTitle, const std::vector<double>  & x, const std::vector<double>  & ex) ;

    /**
     * Create a two dimensional IDataPointSet providing the data along x (the y value is 
     * the index of the x value in the array).
     * @param pathAndTitle The path of the IDataPointSet. The path can either be a relative or full path.
     *                     The last part of the path is used as the title.
     *                     ("/folder1/folder2/dataTitle" and "../folder/dataTitle" are valid paths).
     *                     All the directories in the path must exist. The characther `/` cannot be used
     *                     in names; it is only used to delimit directories within paths.
     * @param x            The array of the x values
     * @param exp          The array with the plus errors on x
     * @param exm          The array with the minus errors on x
     * @return             The created IDataPointSet.
     *
     */
  ///virtual IDataPointSet * createX(const std::string & pathAndTitle, const std::vector<double>  & x, const std::vector<double>  & exp, const std::vector<double>  & exm) ;

    /**
     * Create a two dimensional IDataPointSet providing the data.
     * @param path  The path of the IDataPointSet. The path can either be a relative or full path.
     *              ("/folder1/folder2/dataTitle" and "../folder/dataTitle" are valid paths).
     *              All the directories in the path must exist. The characther `/` cannot be used
     *              in names; it is only used to delimit directories within paths.
     * @param title The title of the IDataPointSet.
     * @param x     The array of the x values
     * @param y     The array of the y values
     * @param exp   The array with the plus errors on x
     * @param eyp   The array with the plus errors on y
     * @param exm   The array with the minus errors on x
     * @param eym   The array with the minus errors on y
     * @return      The created IDataPointSet.
     *
     */
  ///virtual IDataPointSet * createXY(const std::string & path, const std::string & title, const std::vector<double>  & x, const std::vector<double>  & y, const std::vector<double>  & exp, const std::vector<double>  & eyp, const std::vector<double>  & exm, const std::vector<double>  & eym) ;

    /**
     * Create a two dimensional IDataPointSet providing the data.
     * @param path  The path of the IDataPointSet. The path can either be a relative or full path.
     *              ("/folder1/folder2/dataTitle" and "../folder/dataTitle" are valid paths).
     *              All the directories in the path must exist. The characther `/` cannot be used
     *              in names; it is only used to delimit directories within paths.
     * @param title The title of the IDataPointSet.
     * @param x     The array of the x values
     * @param y     The array of the y values
     * @param ex    The array with the symmetric errors on x
     * @param ey    The array with the symmetric errors on y
     * @return      The created IDataPointSet.
     *
     */
  ///virtual IDataPointSet * createXY(const std::string & path, const std::string & title, const std::vector<double>  & x, const std::vector<double>  & y, const std::vector<double>  & ex, const std::vector<double>  & ey) ;

    /**
     * Create a two dimensional IDataPointSet providing the data.
     * @param pathAndTitle The path of the IDataPointSet. The path can either be a relative or full path.
     *                     The last part of the path is used as the title.
     *                     ("/folder1/folder2/dataTitle" and "../folder/dataTitle" are valid paths).
     *                     All the directories in the path must exist. The characther `/` cannot be used
     *                     in names; it is only used to delimit directories within paths.
     * @param x            The array of the x values
     * @param y            The array of the y values
     * @param exp          The array with the plus errors on x
     * @param eyp          The array with the plus errors on y
     * @param exm          The array with the minus errors on x
     * @param eym          The array with the minus errors on y
     * @return             The created IDataPointSet.
     *
     */
  ///virtual IDataPointSet * createXY(const std::string & pathAndTitle, const std::vector<double>  & x, const std::vector<double>  & y, const std::vector<double>  & exp, const std::vector<double>  & eyp, const std::vector<double>  & exm, const std::vector<double>  & eym) ;

    /**
     * Create a two dimensional IDataPointSet providing the data.
     * @param pathAndTitle The path of the IDataPointSet. The path can either be a relative or full path.
     *                     The last part of the path is used as the title.
     *                     ("/folder1/folder2/dataTitle" and "../folder/dataTitle" are valid paths).
     *                     All the directories in the path must exist. The characther `/` cannot be used
     *                     in names; it is only used to delimit directories within paths.
     * @param x            The array of the x values
     * @param y            The array of the y values
     * @param ex           The array with the symmetric errors on x
     * @param ey           The array with the symmetric errors on y
     * @return             The created IDataPointSet.
     *
     */
  ///virtual IDataPointSet * createXY(const std::string & pathAndTitle, const std::vector<double>  & x, const std::vector<double>  & y, const std::vector<double>  & ex, const std::vector<double>  & ey) ;

    /**
     * Create a three dimensional IDataPointSet providing the data.
     * @param path  The path of the IDataPointSet. The path can either be a relative or full path.
     *              ("/folder1/folder2/dataTitle" and "../folder/dataTitle" are valid paths).
     *              All the directories in the path must exist. The characther `/` cannot be used
     *              in names; it is only used to delimit directories within paths.
     * @param title The title of the IDataPointSet.
     * @param x     The array of the x values
     * @param y     The array of the y values
     * @param z     The array of the z values
     * @param exp   The array with the plus errors on x
     * @param eyp   The array with the plus errors on y
     * @param ezp   The array with the plus errors on z
     * @param exm   The array with the minus errors on x
     * @param eym   The array with the minus errors on y
     * @param ezm   The array with the minus errors on z
     * @return      The created IDataPointSet.
     *
     */
  ///virtual IDataPointSet * createXYZ(const std::string & path, const std::string & title, const std::vector<double>  & x, const std::vector<double>  & y, const std::vector<double>  & z, const std::vector<double>  & exp, const std::vector<double>  & eyp, const std::vector<double>  & ezp, const std::vector<double>  & exm, const std::vector<double>  & eym, const std::vector<double>  & ezm) ;

    /**
     * Create a three dimensional IDataPointSet providing the data.
     * @param path  The path of the IDataPointSet. The path can either be a relative or full path.
     *              ("/folder1/folder2/dataTitle" and "../folder/dataTitle" are valid paths).
     *              All the directories in the path must exist. The characther `/` cannot be used
     *              in names; it is only used to delimit directories within paths.
     * @param title The title of the IDataPointSet.
     * @param x     The array of the x values
     * @param y     The array of the y values
     * @param z     The array of the z values
     * @param ex    The array with the symmetric errors on x
     * @param ey    The array with the symmetric errors on y
     * @param ez    The array with the symmetric errors on z
     * @return      The created IDataPointSet.
     *
     */
  ///virtual IDataPointSet * createXYZ(const std::string & path, const std::string & title, const std::vector<double>  & x, const std::vector<double>  & y, const std::vector<double>  & z, const std::vector<double>  & ex, const std::vector<double>  & ey, const std::vector<double>  & ez) ;

    /**
     * Create a two dimensional IDataPointSet providing the data.
     * @param pathAndTitle The path of the IDataPointSet. The path can either be a relative or full path.
     *                     The last part of the path is used as the title.
     *                     ("/folder1/folder2/dataTitle" and "../folder/dataTitle" are valid paths).
     *                     All the directories in the path must exist. The characther `/` cannot be used
     *                     in names; it is only used to delimit directories within paths.
     * @param x            The array of the x values
     * @param y            The array of the y values
     * @param z            The array of the z values
     * @param exp          The array with the plus errors on x
     * @param eyp          The array with the plus errors on y
     * @param ezp          The array with the plus errors on z
     * @param exm          The array with the minus errors on x
     * @param eym          The array with the minus errors on y
     * @param ezm          The array with the minus errors on z
     * @return             The created IDataPointSet.
     *
     */
  ///virtual IDataPointSet * createXYZ(const std::string & pathAndTitle, const std::vector<double>  & x, const std::vector<double>  & y, const std::vector<double>  & z, const std::vector<double>  & exp, const std::vector<double>  & eyp, const std::vector<double>  & ezp, const std::vector<double>  & exm, const std::vector<double>  & eym, const std::vector<double>  & ezm) ;

    /**
     * Create a two dimensional IDataPointSet providing the data.
     * @param pathAndTitle The path of the IDataPointSet. The path can either be a relative or full path.
     *                     The last part of the path is used as the title.
     *                     ("/folder1/folder2/dataTitle" and "../folder/dataTitle" are valid paths).
     *                     All the directories in the path must exist. The characther `/` cannot be used
     *                     in names; it is only used to delimit directories within paths.
     * @param x            The array of the x values
     * @param y            The array of the y values
     * @param z            The array of the z values
     * @param exp          The array with the symmetric errors on x
     * @param eyp          The array with the symmetric errors on y
     * @param ezp          The array with the symmetric errors on z
     * @return             The created IDataPointSet.
     *
     */
  ///virtual IDataPointSet * createXYZ(const std::string & pathAndTitle, const std::vector<double>  & x, const std::vector<double>  & y, const std::vector<double>  & z, const std::vector<double>  & ex, const std::vector<double>  & ey, const std::vector<double>  & ez) ;

    /**
     * Make a copy of a given IDataPointSet.
     * @param path         The path of the IDataPointSet. The path can either be a relative or full path.
     *                     ("/folder1/folder2/dataName" and "../folder/dataName" are valid paths).
     *                     All the directories in the path must exist. The characther `/` cannot be used
     *                     in names; it is only used to delimit directories within paths.
     * @param dataPointSet The IDataPointSet to be copied.
     * @return             The copy of the given IDataPointSet.
     *
     */
  ///virtual IDataPointSet * createCopy(const std::string & path, const IDataPointSet & dataPointSet) ;

    /**
     * Destroy a given IDataPointSet.
     * @param dataPointSet  The IDataPointSet to be destroyed.
     * @return false If dataPointSet cannot be destroyed.
     *
     */
  ///virtual bool destroy(IDataPointSet * dataPointSet) ;

    /**
     * Create an IDataPointSet from an IHistogram1D.
     * @param path    The path of the IDataPointSet. The path can either be a relative or full path.
     *                ("/folder1/folder2/dataName" and "../folder/dataName" are valid paths).
     *                All the directories in the path must exist. The characther `/` cannot be used
     *                in names; it is only used to delimit directories within paths.
     * @param hist    The IHistogram1D from which the data is taken.
     * @param options Options, currently not specified
     * @return        The newly created IDataPointSet.
     *
     */
  ///virtual IDataPointSet * create(const std::string & path, const IHistogram1D & hist, const std::string & options = "") ;

    /**
     * Create an IDataPointSet from an IHistogram2D.
     * @param path    The path of the IDataPointSet. The path can either be a relative or full path.
     *                ("/folder1/folder2/dataName" and "../folder/dataName" are valid paths).
     *                All the directories in the path must exist. The characther `/` cannot be used
     *                in names; it is only used to delimit directories within paths.
     * @param hist    The IHistogram2D from which the data is taken.
     * @param options Options, currently not specified
     * @return        The newly created IDataPointSet.
     *
     */
  ///virtual IDataPointSet * create(const std::string & path, const IHistogram2D & hist, const std::string & options = "") ;

    /**
     * Create an IDataPointSet from an IHistogram3D.
     * @param path    The path of the IDataPointSet. The path can either be a relative or full path.
     *                ("/folder1/folder2/dataName" and "../folder/dataName" are valid paths).
     *                All the directories in the path must exist. The characther `/` cannot be used
     *                in names; it is only used to delimit directories within paths.
     * @param hist    The IHistogram3D from which the data is taken.
     * @param options Options, currently not specified
     * @return        The newly created IDataPointSet.
     *
     */
  ///virtual IDataPointSet * create(const std::string & path, const IHistogram3D & hist, const std::string & options = "") ;

    /**
     * Create an IDataPointSet from an ICloud1D.
     * @param path    The path of the IDataPointSet. The path can either be a relative or full path.
     *                ("/folder1/folder2/dataName" and "../folder/dataName" are valid paths).
     *                All the directories in the path must exist. The characther `/` cannot be used
     *                in names; it is only used to delimit directories within paths.
     * @param cloud   The ICloud1D from which the data is taken.
     * @param options Options, currently not specified
     * @return        The newly created IDataPointSet.
     *
     */
  ///virtual IDataPointSet * create(const std::string & path, const ICloud1D & cloud, const std::string & options = "") ;

    /**
     * Create an IDataPointSet from an ICloud2D.
     * @param path    The path of the IDataPointSet. The path can either be a relative or full path.
     *                ("/folder1/folder2/dataName" and "../folder/dataName" are valid paths).
     *                All the directories in the path must exist. The characther `/` cannot be used
     *                in names; it is only used to delimit directories within paths.
     * @param cloud   The ICloud2D from which the data is taken.
     * @param options Options, currently not specified
     * @return        The newly created IDataPointSet.
     *
     */
  ///virtual IDataPointSet * create(const std::string & path, const ICloud2D & cloud, const std::string & options = "") ;

    /**
     * Create an IDataPointSet from an ICloud3D.
     * @param path    The path of the IDataPointSet. The path can either be a relative or full path.
     *                ("/folder1/folder2/dataName" and "../folder/dataName" are valid paths).
     *                All the directories in the path must exist. The characther `/` cannot be used
     *                in names; it is only used to delimit directories within paths.
     * @param cloud   The ICloud3D from which the data is taken.
     * @param options Options, currently not specified
     * @return        The newly created IDataPointSet.
     *
     */
  ///virtual IDataPointSet * create(const std::string & path, const ICloud3D & cloud, const std::string & options = "") ;

    /**
     * Create an IDataPointSet from an IProfile1D.
     * @param path    The path of the IDataPointSet. The path can either be a relative or full path.
     *                ("/folder1/folder2/dataName" and "../folder/dataName" are valid paths).
     *                All the directories in the path must exist. The characther `/` cannot be used
     *                in names; it is only used to delimit directories within paths.
     * @param profile The IProfile1D from which the data is taken.
     * @param options Options, currently not specified
     * @return        The newly created IDataPointSet.
     *
     */
  ///virtual IDataPointSet * create(const std::string & path, const IProfile1D & profile, const std::string & options = "") ;

    /**
     * Create an IDataPointSet from an IProfile2D.
     * @param path    The path of the IDataPointSet. The path can either be a relative or full path.
     *                ("/folder1/folder2/dataName" and "../folder/dataName" are valid paths).
     *                All the directories in the path must exist. The characther `/` cannot be used
     *                in names; it is only used to delimit directories within paths.
     * @param profile The IProfile2D from which the data is taken.
     * @param options Options, currently not specified
     * @return        The newly created IDataPointSet.
     *
     */
  ///virtual IDataPointSet * create(const std::string & path, const IProfile2D & profile, const std::string & options = "") ;

    /**
     * Add two IDataSetPoint, point by point and measurement by measurement.
     * @param path          The path of resulting the IDataPointSet. The path can either be a relative or full path.
     *                      ("/folder1/folder2/dataName" and "../folder/dataName" are valid paths).
     *                      All the directories in the path must exist. The characther `/` cannot be used
     *                      in names; it is only used to delimit directories within paths.
     * @param dataPointSet1 The first member of the addition.
     * @param dataPointSet2 The second member of the addition.
     *                      if a directory in the path does not exist, or the path is illegal.
     *
     */
  ///virtual IDataPointSet * add(const std::string & path, const IDataPointSet & dataPointSet1, const IDataPointSet & dataPointSet2) ;

    /**
     * Subtract two IDataSetPoint, point by point and measurement by measurement.
     * @param path          The path of the resulting IDataPointSet. The path can either be a relative or full path.
     *                      ("/folder1/folder2/dataName" and "../folder/dataName" are valid paths).
     *                      All the directories in the path must exist. The characther `/` cannot be used
     *                      in names; it is only used to delimit directories within paths.
     * @param dataPointSet1 The first member of the subtraction.
     * @param dataPointSet2 The second member of the subtraction.
     * @param strategy      The strategy of how to perform the subtraction. The default corresponds to
     *                      uncorrelated Gaussian error propagation.
     *                      if a directory in the path does not exist, or the path is illegal.
     *
     */
  ///virtual IDataPointSet * subtract(const std::string & path, const IDataPointSet & dataPointSet1, const IDataPointSet & dataPointSet2) ;

    /**
     * Multiply two IDataSetPoint, point by point and measurement by measurement.
     * @param path          The path of the resulting IDataPointSet. The path can either be a relative or full path.
     *                      ("/folder1/folder2/dataName" and "../folder/dataName" are valid paths).
     *                      All the directories in the path must exist. The characther `/` cannot be used
     *                      in names; it is only used to delimit directories within paths.
     * @param dataPointSet1 The first member of the multiplication.
     * @param dataPointSet2 The second member of the multiplication.
     * @param strategy      The strategy of how to perform the multiplication. The default corresponds to
     *                      uncorrelated Gaussian error propagation.
     *                      if a directory in the path does not exist, or the path is illegal.
     *
     */
  ///virtual IDataPointSet * multiply(const std::string & path, const IDataPointSet & dataPointSet1, const IDataPointSet & dataPointSet2) ;

    /**
     * Divide two IDataSetPoint, point by point and measurement by measurement.
     * @param path          The path of resulting the IDataPointSet. The path can either be a relative or full path.
     *                      ("/folder1/folder2/dataName" and "../folder/dataName" are valid paths).
     *                      All the directories in the path must exist. The characther `/` cannot be used
     *                      in names; it is only used to delimit directories within paths.
     * @param dataPointSet1 The first member of the division.
     * @param dataPointSet2 The second member of the division.
     * @param strategy      The strategy of how to perform the division. The default corresponds to
     *                      uncorrelated Gaussian error propagation.
     *                      if a directory in the path does not exist, or the path is illegal.
     *
     */
  ///virtual IDataPointSet * divide(const std::string & path, const IDataPointSet & dataPointSet1, const IDataPointSet & dataPointSet2) ;

    /**
     * Calculate weighted means of two IDataSetPoint, point by point and measurement by measurement.
     * @param path          The path of the resulting IDataPointSet. The path can either be a relative or full path.
     *                      ("/folder1/folder2/dataName" and "../folder/dataName" are valid paths).
     *                      All the directories in the path must exist. The characther `/` cannot be used
     *                      in names; it is only used to delimit directories within paths.
     * @param dataPointSet1 The first IDataPointSet.
     * @param dataPointSet2 The second IDataPointSet.
     * @param strategy      The strategy of how to calculate the weighted means. The default corresponds to
     *                      uncorrelated Gaussian error propagation.
     *                      if a directory in the path does not exist, or the path is illegal.
     *
     */
  ///virtual IDataPointSet * weightedMean(const std::string & path, const IDataPointSet & dataPointSet1, const IDataPointSet & dataPointSet2) ;
}; // class
} // namespace AIDA
#endif /* ifndef AIDA_IDATAPOINTSETFACTORYROOT_H */

