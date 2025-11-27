#!/bin/sh --login
#BSUB -q 1nh
source /cvmfs/cms.cern.ch/cmsset_default.sh
cd /afs/cern.ch/user/n/nbarnett/public/CondorWorkArea/CMSSW_15_1_0_patch3/src
eval `scramv1 runtime -sh`
exec > /dev/null 2>&1
cmsRun __EXECUTABLE_FILE__ $1 $2