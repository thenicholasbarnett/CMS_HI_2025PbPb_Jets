#!/bin/sh --login
#BSUB -q 1nh
root '__EXECUTABLE_FILE__("'$1'", "'$2'")'