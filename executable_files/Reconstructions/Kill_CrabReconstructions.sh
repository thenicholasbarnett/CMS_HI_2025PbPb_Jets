#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <run number> <number of RawPrime crab jobs to kill>"
    echo "Example: $0 399912 20"
    exit 1
fi

run_number="$1"
declare -i NumPDs="$2"
today=$(date +"%m_%d_%Y")

for ((i=0; i<NumPDs; i++)); do
    request_name="crab_RECO_PbPb_${today}_run${run_number}_v0_RP${i}"
    crab kill -d crab_projects/"$crab_cfg"
done



