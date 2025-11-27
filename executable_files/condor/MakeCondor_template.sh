#!/bin/bash

run_filename="run_$1.sh"
sub_filename="SubmissionFileCreate_$1.sh"

cp /eos/cms/store/group/phys_heavyions/nbarnett/condor/run_template.sh ./$run_filename
cp /eos/cms/store/group/phys_heavyions/nbarnett/condor/SubmissionFileCreate_template.sh ./$sub_filename
cp $2 .
cp $3 .

filename="${2##*/}"

sed -i "s|__EXECUTABLE_FILE__|`pwd`/${filename}|g" $run_filename

today=$(date +"%m_%d_%Y")
logdir="${1}_output_${today}"
mkdir $logdir
mkdir "$logdir/out"
mkdir "$logdir/err"
mkdir "$logdir/log"
final_output_dir="$4/condor_${1}_${today}"
mkdir $final_output_dir

chmod +x $sub_filename
./$sub_filename $1 $final_output_dir $logdir $3

SubmissionFile="submit_$1.condor"
condor_submit $SubmissionFile