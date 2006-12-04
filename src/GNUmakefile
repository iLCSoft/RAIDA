###########################################################
#
# Example GNUmakefile to build an Application with Marlin
#
# @author Frank Gaede
# @version $Id: GNUmakefile,v 1.2 2006-12-04 17:24:06 tkraemer Exp $
#
###########################################################

# requires path to MARLIN and Marlin v00-09 or higher
# can be called from top level makefile


#----------------------------------------------------------------------------
#                user variables 
#----------------------------------------------------------------------------


# name of the program/library
PROGNAME = RAIDA



#----  additional user include/libraries
#-- optionally can be specified in the to level GNUmakefile of $MARLIN

ifndef USERINCLUDES
 NOMARLIN = 1

 USERINCLUDES = 
 USERINCLUDES += `root-config --cflags`
endif

ifndef USERLIBS
 USERLIBS =
 USERLIBS += `root-config --libs`
 USERLIBS += `root-config --glibs`
endif


#----------------------------------------------------------------------------
#        do not modify anything below in order to use top level makefile
#----------------------------------------------------------------------------

# the base directory of your application
# this is where you  would normaly have the lib, bin and source directories
BASEDIR = ..
INSTALL = $(BASEDIR)/lib
BINDIR = $(BASEDIR)/bin



ifdef RAIDADEBUG
 CPPFLAGS = -g -Wall -ansi
else
 CPPFLAGS = -O3 -Wall -ansi
endif


# check for private compiler definition
ifdef MY_CXX
  CXX = $(MY_CXX)
else
  CXX = g++
endif

AR = ar

#--------------------------------------------------------------------------------------
LIBS +=   -Wl,-whole-archive  -L $(INSTALL)  -l$(PROGNAME) -Wl,-no-whole-archive
#--------------------------------------------------------------------------------------

ifdef RAIDA_DEBUG_VERBOSE
 INCLUDE += -D USE_RAIDA_DEBUG_VERBOSE 
endif

INCLUDE +=  -I $(BASEDIR)/include
INCLUDE += $(USERINCLUDES)
CPPFLAGS += $(INCLUDE)

ifndef NOMARLIN
 CPPFLAGS += `. $(MARLIN)/bin/marlin_includes.sh`
endif

LIBS += $(USERLIBS)

ifndef NOMARLIN
 LIBS += `. $(MARLIN)/bin/marlin_libs.sh`
endif

bin:  lib $(BINDIR)/$(PROGNAME)

$(BINDIR)/$(PROGNAME): $(INSTALL)/lib$(PROGNAME).a
	mkdir -p $(BINDIR)
	$(CXX) -o $(BINDIR)/$(PROGNAME) $(CPPFLAGS) $(BASEDIR)/mainroot.cc $(LIBS) 

objects = $(patsubst %.cc,%.o, $(wildcard *.cc)  )

$(INSTALL)/lib$(PROGNAME).a: $(objects)
	mkdir -p $(INSTALL)
	$(AR) cr $(INSTALL)/lib$(PROGNAME).a  $?

lib: $(INSTALL)/lib$(PROGNAME).a


clean:
	rm -f *.o $(INSTALL)/lib$(PROGNAME).a $(BINDIR)/$(PROGNAME)

doc:
	cd $(BASEDIR)/doc ; doxygen ;

