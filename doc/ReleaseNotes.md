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
