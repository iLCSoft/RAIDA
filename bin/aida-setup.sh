#!/bin/sh
# -*- sh-indentation: 3 -*-
#
###############################################################################
#
# This script makes sure that $PATH includes the path to aida-config
# 
# This script requires RAIDA_HOME to be set properly  
# 
# F.Gaede, T.Kraemer, DESY
#
###############################################################################

# test whether RAIDA_HOME is unknown 
if [ -z "${RAIDA_HOME}" ]
then
    echo "$(basename "$0"): error: RAIDA_HOME is not set" 1>&2 ; exit 1
fi

export PATH=$RAIDA_HOME/bin:$PATH

exit 0 
