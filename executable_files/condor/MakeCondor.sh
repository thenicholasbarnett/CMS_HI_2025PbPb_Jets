# name of condor job
jobname=""

# exectuable script.C with path
executable=""

# list of input files
filelist=""

# output directory
output_dir=""


today=$(date +"%m_%d_%Y")
mkdir "condor_${jobname}_${today}"
cd "condor_${jobname}_${today}"
cp /eos/cms/store/group/phys_heavyions/nbarnett/condor/MakeCondor_template.sh ./MakeCondor_${jobname}.sh
chmod +x MakeCondor_${jobname}.sh
./"MakeCondor_${jobname}.sh" $jobname $executable $filelist $output_dir