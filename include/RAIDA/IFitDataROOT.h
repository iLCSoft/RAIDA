// -*- C++ -*-
#ifndef AIDA_IFITDATAROOT_H
#define AIDA_IFITDATAROOT_H 1

#include <AIDA/IFitData.h>
#include <string>
#include <vector>

namespace AIDA {

class ICloud1D;
class ICloud2D;
class ICloud3D;
class IDataPointSet;
class IEvaluator;
class IHistogram1D;
class IHistogram2D;
class IHistogram3D;
class IProfile1D;
class IProfile2D;
class IRangeSet;
class ITuple;

/** Dummy implementation of the Abstract representation of the fit data. 
 * @author T. Kraemer, DESY
 * @version $Id: IFitDataROOT.h,v 1.1 2007-01-03 13:35:25 tkraemer Exp $
 */

class IFitDataROOT : public IFitData {

public: 
  /// Destructor.
  virtual ~IFitDataROOT() { /* nop */; }

  IFitDataROOT() { /* nop */; }

  /**
   * One dimensional connections.
   */

  /**
   * Create a one dimensional connection to an IHistogram1D.
   * @param h       The 1D histogram to which to connect to.
   * @return false If something is wrong.
   */
  virtual bool create1DConnection(const IHistogram1D & h) ;

  /**
   * Create a one dimensional connection to an ICloud1D.
   * @param c       The 1D cloud to which to connect to.
   * @return false If something is wrong.
   */
  virtual bool create1DConnection(const ICloud1D & c) ;

  /**
   * Create a one dimensional connection to an IProfile1D.
   * @param p       The 1D profile to which to connect to.
   * @return false If something is wrong.
   */
  virtual bool create1DConnection(const IProfile1D & p) ;

  /**
   * Create a one dimensional connection to an IDataPointSet.
   * @param dp       The dataPointSet to which to connect to.
   * @param xIndex   The index of the coordinate to which the variable is connected.
   * @param valIndex The index of the coordinate used as "height".
   * @return false If something is wrong.
   */
  virtual bool create1DConnection(const IDataPointSet & dp, 
				  int xIndex, int valIndex) ;

  /**
   * Two dimensional connections.
   */

  /**
   * Create a two dimensional connection to an IHistogram2D.
   * @param h        The 2D histogram to which to connect to.
   * @return false If something is wrong.
   */
  virtual bool create2DConnection(const IHistogram2D & h) ;

  /**
   * Create a two dimensional connection to an IHistogram2D.
   * @param h        The 2D histogram to which to connect to.
   * @param xIndex   The index of the axis to which the x variable is connected.
   * @param yIndex   The index of the axis to which the y variable is connected.
   * @return false If something is wrong.
   */
  virtual bool create2DConnection(const IHistogram2D & h, 
				  int xIndex, int yIndex) ;

  /**
   * Create a two dimensional connection to an ICloud2D.
   * @param c        The 2D cloud to which to connect to.
   * @return false If something is wrong.
   */
  virtual bool create2DConnection(const ICloud2D & c) ;

  /**
   * Create a two dimensional connection to an ICloud2D.
   * @param c        The 2D cloud to which to connect to.
   * @param xIndex   The index of the axis to which the x variable is connected.
   * @param yIndex   The index of the axis to which the y variable is connected.
   * @return false If something is wrong.
   */
  virtual bool create2DConnection(const ICloud2D & c, 
				  int xIndex, int yIndex) ;

  /**
   * Create a two dimensional connection to an IProfile2D.
   * @param p       The 2D profile to which to connect to.
   * @return false If something is wrong.
   */
  virtual bool create2DConnection(const IProfile2D & p) ;

  /**
   * Create a two dimensional connection to an IProfile2D.
   * @param p        The 2D profile to which to connect to.
   * @param xIndex   The index of the axis to which the x variable is connected.
   * @param yIndex   The index of the axis to which the y variable is connected.
   * @return false If something is wrong.
   */
  virtual bool create2DConnection(const IProfile2D & p, 
				  int xIndex, int yIndex) ;

  /**
   * Create a two dimensional connection to an IDataPointSet.
   * @param dp       The dataPointSet to which to connect to.
   * @param xIndex   The index of the coordinate to which the x variable is connected.
   * @param yIndex   The index of the coordinate to which the y variable is connected.
   * @param valIndex The index of the coordinate used as "height".
   * @return false If something is wrong.
   */
  virtual bool create2DConnection(const IDataPointSet & dp, 
				  int xIndex, int yIndex, int valIndex) ;

  /**
   * Three dimensional connections.
   */

  /**
   * Create a three dimensional connection to an IHistogram3D.
   * @param h        The 3D histogram to which to connect to.
   * @return false If something is wrong.
   */
  virtual bool create3DConnection(const IHistogram3D & h) ;

  /**
   * Create a three dimensional connection to an IHistogram3D.
   * @param h        The 3D histogram to which to connect to.
   * @param xIndex   The index of the axis to which the x variable is connected.
   * @param yIndex   The index of the axis to which the y variable is connected.
   * @param zIndex   The index of the axis to which the z variable is connected.
   * @return false If something is wrong.
   */
  virtual bool create3DConnection(const IHistogram3D & h, 
				  int xIndex, int yIndex, int zIndex) ;

  /**
   * Create a three dimensional connection to an ICloud3D.
   * @param c        The 3D cloud to which to connect to.
   * @return false If something is wrong.
   */
  virtual bool create3DConnection(const ICloud3D & c) ;

  /**
   * Create a three dimensional connection to an ICloud3D.
   * @param c        The 3D cloud to which to connect to.
   * @param xIndex   The index of the axis to which the x variable is connected.
   * @param yIndex   The index of the axis to which the y variable is connected.
   * @param zIndex   The index of the axis to which the z variable is connected.
   * @return false If something is wrong.
   */
  virtual bool create3DConnection(const ICloud3D & c, 
				  int xIndex, int yIndex, int zIndex) ;

  /**
   * Create a three dimensional connection to an IDataPointSet.
   * @param dp       The dataPointSet to which to connect to.
   * @param xIndex   The index of the coordinate to which the x variable is connected.
   * @param yIndex   The index of the coordinate to which the y variable is connected.
   * @param zIndex   The index of the coordinate to which the z variable is connected.
   * @param valIndex The index of the coordinate used as "height".
   * @return false If something is wrong.
   */
  virtual bool create3DConnection(const IDataPointSet & dp, 
				  int xIndex, int yIndex, int zIndex, 
				  int valIndex) ;

  /**
   * General connections.
   */

  /**
   * Tuples are for UNBINNED fits, so no value column required.
   */

  /** 
   * Create a connection to an ITuple.
   * @param t        The ITuple.
   * @param colNames The names of the columns to which to connect.
   * @return false If something is wrong.
   */
  virtual bool createConnection(const ITuple & t, 
				std::vector<std::string>  colNames) ;

  /** 
   * Create a connection to an ITuple.
   * @param t     The ITuple.
   * @param evals The list of the IEvaluator used to calculate the variable's value.
   * @return false If something is wrong.
   */
  virtual bool createConnection(const ITuple & t, 
				std::vector<IEvaluator *>  & evals) ;

  /**
   * Create a connection to an IDataPointSet.
   * @param dp       The dataPointSet to which to connect to.
   * @param indeces  The indeces of the coordinates to which the variables are connected.
   * @param valIndex The index of the coordinate used as "height".
   * @return false If something is wrong.
   */
  virtual bool createConnection(const IDataPointSet & dp, 
				std::vector<int>  indeces, int valIndex) ;

  /**
   * Remove all Ranges and connections; after this is like newly create.
   */
  virtual void reset() ;

  /**
   * The dimension of this IFitData, i.e. the number of connections.
   * @return The dimension of the IFitData.
   */
  virtual int dimension() const ;

  /// Return a string describing the data. This should be considered as a
  /// hint to the user where to find the original data objects and how
  /// to connect the data pipes. PENDING: probably this can be part of
  /// XML streaming.
  virtual std::string dataDescription() const ;

  /**
   * Get Range of the corresponding connection by index. 
   * The index represent the order in which
   * connections are coming out of the IFitData.
   * @param  The index of the connection.
   * @return      The Range
   */
  virtual IRangeSet & range(int index) const ;
}; // class
} // namespace AIDA
#endif /* ifndef AIDA_IFITDATAROOT_H */
