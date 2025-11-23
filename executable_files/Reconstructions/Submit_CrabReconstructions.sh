#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <run number> <number of RawPrime datasets to reconstruct>"
    echo "Example: $0 399912 10"
    exit 1
fi

run_number="$1"
declare -i NumPDs="$2"

for ((i=0; i<NumPDs; i++)); do
    crab_cfg="Crab_RECO_PbPb_run${run_number}_RawPrime${i}.py"
    crab submit "$crab_cfg"
done



