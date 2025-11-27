#!/bin/bash

# copying the list of files and the executable to the new condor directory
cp $2 .
cp $3 .
filename="${2##*/}"

# making a bash script to run the executble
run_filename="run_$1.sh"
if [[ "$filename" == *.py ]]; then
    cp /eos/cms/store/group/phys_heavyions/nbarnett/condor/run_py_template.sh ./$run_filename
elif [[ "$filename" == *.C ]]; then
    cp /eos/cms/store/group/phys_heavyions/nbarnett/condor/run_C_template.sh ./$run_filename
fi
sed -i "s|__EXECUTABLE_FILE__|`pwd`/${filename}|g" $run_filename

# making a directory to store the output condor information
today=$(date +"%m_%d_%Y")
logdir="${1}_output_${today}"
mkdir $logdir
mkdir "$logdir/out"
mkdir "$logdir/err"
mkdir "$logdir/log"

# making a directory to put the outputs from the condor jobs
final_output_dir="$4/condor_${1}_${today}"
mkdir $final_output_dir

# making the condor submission file
sub_filename="SubmissionFileCreate_$1.sh"
cp /eos/cms/store/group/phys_heavyions/nbarnett/condor/SubmissionFileCreate_template.sh ./$sub_filename
chmod +x $sub_filename
./$sub_filename $1 $final_output_dir $logdir $3

# submitting the condor job :)
SubmissionFile="submit_$1.condor"
condor_submit $SubmissionFile