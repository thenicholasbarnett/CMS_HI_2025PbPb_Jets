#!/bin/sh --login
#BSUB -q 1nh
cmsenv
cmsRun '__EXECUTABLE_FILE__("'$1'", "'$2'")'