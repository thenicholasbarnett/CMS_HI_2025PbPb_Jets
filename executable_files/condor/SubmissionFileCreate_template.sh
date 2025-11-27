#!/bin/sh                                                                                                                                                                                    

SubmissionFile=submit_$1.condor

echo "Universe   = vanilla" > $SubmissionFile
echo "Executable = `pwd`/run_$1.sh" >> $SubmissionFile
echo "+JobFlavour = longlunch" >> $SubmissionFile
echo "Transfer_Input_Files = run_$1.sh" >> $SubmissionFile
echo "should_transfer_files = YES" >> $SubmissionFile
echo "WhenToTransferOutput = ON_EXIT">> $SubmissionFile
echo >> $SubmissionFile

Count=0
Input=$MyInputFiles

while IFS= read -r line; do

   echo "Arguments = $line $2/output_JetTurnOn_$Count.root" >> $SubmissionFile

   echo "Output    = $3/out/out_$Count.txt" >> $SubmissionFile
   echo "Error     = $3/err/err_$Count.txt" >> $SubmissionFile
   echo "Log       = $3/log/log_$Count.txt" >> $SubmissionFile

   echo 'Queue' >> $SubmissionFile

   Count=$((Count+1))

done < $4
