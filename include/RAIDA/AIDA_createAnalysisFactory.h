// -*- C++ -*-
#ifndef AIDA_createAnalysisFactory_H
#define AIDA_createAnalysisFactory_H 1
#include <AIDA/IAnalysisFactory.h>

/** Function to hook an AIDA implementation
 * @author T. Kraemer, DESY
 * @version $Id: AIDA_createAnalysisFactory.h,v 1.2 2006-12-04 17:24:06 tkraemer Exp $
 */

extern "C" {
    AIDA::IAnalysisFactory* AIDA_createAnalysisFactory(void);
}


#endif
