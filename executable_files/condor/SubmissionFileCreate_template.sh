#!/bin/sh                                                                                                                                                                                    

SubmissionFile=submit_$1.condor

echo "Universe   = vanilla" > $SubmissionFile
echo "Executable = `pwd`/run_$1.sh" >> $SubmissionFile
echo "+JobFlavour = longlunch" >> $SubmissionFile
echo "Transfer_Input_Files = run_$1.sh" >> $SubmissionFile
echo "should_transfer_files = YES" >> $SubmissionFile
echo "WhenToTransferOutput = ON_EXIT">> $SubmissionFile
#echo "request_cpus = 4" >> $SubmissionFile
echo >> $SubmissionFile

Count=0
Input=$MyInputFiles

while IFS= read -r line; do

   echo "Arguments = $line $2/output_${1}_${Count}.root" >> $SubmissionFile

   echo "Output    = $3/out/job_$Count.out" >> $SubmissionFile
   echo "Error     = $3/err/job_$Count.err" >> $SubmissionFile
   echo "Log       = $3/log/job_$Count.log" >> $SubmissionFile

   echo 'Queue' >> $SubmissionFile

   Count=$((Count+1))

done < $4
