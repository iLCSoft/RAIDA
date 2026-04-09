# v01-12

* 2026-01-20 Juan Miguel Carceller ([PR#10](https://github.com/ilcsoft/raida/pull/10))
  - Create a symbolic link to make `find_package(AIDA)` work

* 2026-01-19 Thomas Madlener ([PR#9](https://github.com/ilcsoft/raida/pull/9))
  - Update to the latest Key4hep CI workflow

* 2026-01-19 Juan Miguel Carceller ([PR#8](https://github.com/ilcsoft/raida/pull/8))
  - Check for the Config.cmake and LibDeps.cmake in lib/cmake first in case it is installed there instead of the usual root of the installation folder.

# v01-11

# v01-10

* 2023-04-18 tmadlener ([PR#5](https://github.com/iLCSoft/RAIDA/pull/5))
  - Migrate CI to github actions and remove travis-CI based configuration.

* 2023-04-18 jmcarcell ([PR#4](https://github.com/iLCSoft/RAIDA/pull/4))
  - Link only against the ROOT libraries that are necessary to avoid downstream linker problems.

# v01-09

* 2018-01-12 Frank Gaede ([PR#3](https://github.com/iLCSoft/RAIDA/pull/3))
  - silence warnings: effc++, unused, vla 
  - fix virtual inheritance in IFunctionROOT

# v01-08

# v01-07

F. Gaede
   - made compatible with c++11
   - removed -ansi -pedantic -Wno-long-long

# v01-06-02

    - added BEFORE to INCLUDE_DIRECTORIES

# v01-06-01

    - added AIDAConfig.cmake configuration files to be able to
        call FIND_PACKAGE( AIDA ) without and additional FindAIDA.cmake module

# v01-06

    - fixed building documentation
    - added RAIDAConfigVersion.cmake to check RAIDA version


# v01-05

      - fixed issue with duplicate histograms (M.Killenberg)
      - removed old GNUmakefiles

# v01-04-03

    - made cmake 2.6 compatible
    - added 32 bit compatibility build option
    - added RAIDA_LIBRARY_DIRS

# v01-04-02

    - added compatibility issue for being able to switch between RAIDA/JAIDA
        in LCFIVertex

# v01-04-01

           J.Engels, DESY 
           added aida-config and aida-setup.sh INSTALL rule in CMakeLists.txt

# v01-04

          M.Killenberg, Bonn
         - Added Doxyfile 
         - Introduced memory management of histograms in IHistorgamFactoryROOT
         - Removed memory leaks in IHistgram1D, 2D and 3D
         - IHistorgamFactoryROOT::destroy(IBaseHistogram * hist) implemented

# v01-03

    - cmake now default build tool - see README
    - bug fix: proper path for ntuple: "/N-Tuples"
       
# v01-02

     - added cmake support
