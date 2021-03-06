// -*- C++ -*-
#ifndef AIDA_IANALYSISFACTORYROOT_H
#define AIDA_IANALYSISFACTORYROOT_H 1

#include <AIDA/IAnalysisFactory.h>
#include <AIDA/ITree.h>
#include <string>

namespace AIDA {

  class IDataPointSetFactory;
  class IFitFactory;
  class IFunctionFactory;
  class IHistogramFactory;
  class IPlotterFactory;
  class ITree;
  class ITreeFactory;
  class ITupleFactory;

/**
 * The "master" factory from which other factories are obtained.
 * Typically accessed by:
 * IAnalysisFactory* af = AIDA_createAnalysisFactory();
 *
 * @author T. Kraemer, DESY
 * @version $Id: IAnalysisFactoryROOT.h,v 1.2 2006-12-04 17:24:06 tkraemer Exp $
 */

class IAnalysisFactoryROOT : public IAnalysisFactory {

public: 
    /// Destructor.
    virtual ~IAnalysisFactoryROOT() { /* nop */; }

  /**
   * Create an ITreeFactory.
   * @return The ITreeFactory.
   *
   */
   virtual ITreeFactory * createTreeFactory();

  /**
   * Create an IHistogramFactory.
   * @param tree The ITree which created histograms will be associated to.
   * @return     The IHistogramFactory.
   *
   */
   virtual IHistogramFactory * createHistogramFactory(ITree & tree) ;

  /**
   * Create an IDataPointSetFactory.
   * @param tree The ITree which created IDataPointSet will be associated to.
   * @return     The IDataPointSetFactory.
   *
   */
  virtual IDataPointSetFactory * createDataPointSetFactory(ITree & tree);

  /**
   * Create an ITupleFactory.
   * @param tree The ITree which created tuples will be associated to.
   * @return     The ITupleFactory.
   *
   */
  virtual ITupleFactory * createTupleFactory(ITree & tree);

  /**
   * Create an IFunctionFactory.
   * @param tree The ITree which created functions will be associated to.
   * @return     The IFunctionFactory.
   *
   */
  virtual IFunctionFactory * createFunctionFactory(ITree & tree) ;

    /**
     * Create an IPlotterFactory.
     * Due to the fact that the plotter factory may activate a GUI
     * tookit, the process arguments (passed to the main function)
     * could be passed to the plotter factory. Most of the GUI
     * toolkit ask for them (Motif, gtk, Qt, FLTK).
     * @param imp The AIDA implementation to use. The default uses the current implementation one.
     * @param lib The plotter to use within the choosen AIDA implementation (an AIDA implementation may have multiple plotters based on different technologies).
     */
  virtual IPlotterFactory * createPlotterFactory(int argc = 0, 
						 char * * args = 0, 
						 const std::string & imp = "",
						 const std::string & lib = "");

  /**
   * Create an IFitFactory.
   * @return     The IFitFactory.
   *
   */
  virtual IFitFactory * createFitFactory();
}; // class
} // namespace AIDA
#endif /* ifndef AIDA_IANALYSISFACTORY_H */
