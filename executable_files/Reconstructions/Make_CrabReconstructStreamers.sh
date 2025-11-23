#!/bin/bash

if [ "$#" -ne 3 ]; then
    echo "Usage: $0 <name of an output storage directory> <run number> <number of RawPrime datasets to reconstruct>"
    echo "Example: $0 /store/group/phys_heavyions/nbarnett/RECO 399912 10"
    exit 1
fi

output_dir="$1"
run_number="$2"
declare -i NumPDs="$3"

run_first3=${run_number:0:3}
run_last3=${run_number:3:3}
today=$(date +"%m_%d_%Y")

crab_dir="Crab_RECO_run${run_number}_RawPrime0to${NumPDs}_${today}"
mkdir "$crab_dir"
cd "$crab_dir"
cp /eos/cms/store/group/phys_heavyions/nbarnett/RECO2025/Crab_RECO_PbPb_run_RawPrime_template.py .
cp /eos/cms/store/group/phys_heavyions/nbarnett/RECO2025/recoPbPbrawPr2mini_RAW2DIGI_L1Reco_RECO_PAT_T4.py .

for ((i=0; i<NumPDs; i++)); do
    path="/eos/cms/store/t0streamer/Data/PhysicsHIPhysicsRawPrime${i}/000/${run_first3}/${run_last3}"
    txt_list="filelist_dat_run${run_number}_RP${i}.txt"
    ls "$path"/* > "$txt_list"
    sed -i "s|/eos/cms||" "$txt_list"
    crab_cfg="Crab_RECO_PbPb_run${run_number}_RawPrime${i}.py"
    cp Crab_RECO_PbPb_run_RawPrime_template.py "$crab_cfg"
    sed -i "s|__INPUT_FILE_LIST__|${txt_list}|g" "$crab_cfg"
    sed -i "s|__OUTPUT_DIR__|${output_dir}|g" "$crab_cfg"
    request_name="RECO_PbPb_${today}_run${run_number}_v0_RP${i}"
    sed -i "s|__REQUEST_NAME__|${request_name}|g" "${crab_cfg}"
done

rm Crab_RECO_PbPb_run_RawPrime_template.py
cp /eos/cms/store/group/phys_heavyions/nbarnett/RECO2025/Submit_CrabReconstructions.sh .

cd ..
