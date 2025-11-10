#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"

// void nref_max_finder_data(TString input_file_list = "/afs/cern.ch/user/n/nbarnett/public/txt_files/forest_locations_2025/forests_RawPrime_Replay.txt", TString output = "/eos/cms/store/group/phys_heavyions/nbarnett/temp/11_10_2025/nref_RawPrime_Replay_11_10_2025.root"){
void nref_max_finder_data(TString input_file_list, TString output){

    // declaring variables //

    // number of jets
    Int_t nref;

    // max number of jets
    Int_t nrefmax = 0;

    // any value larger than the expected max number of jets
    const int nrefmax_guess = 500;
    
    // declaring nref binning
    const int nrefbins = nrefmax_guess;
    const int nreflims[2] = {0, nrefmax_guess};

    // initializing jet multiplicity histogram
    TH1I *hnref = new TH1I("hnref", "hnref", nrefbins, nreflims[0], nreflims[1]);

    // getting list of root files to process
    ifstream myfile(input_file_list);
    string filename;

    // keeping track of which file I'm processing
    int filenumber = 0;

    // looping over root files from list
    while(getline(myfile, filename)){

        filenumber+=1;

        // reading and staging input file
        TString input = filename;
        TFile *fi = TFile::Open(input,"read");
        fi->cd();

        // showing the file being processed in the terminal
        cout<<"processing file "<< filenumber <<": "<<input<<endl;

        // getting the TTrees from the input file //

        // ttree name
        TString sTTree = "akCs4PFJetAnalyzer/t";

        // getting ttrees, printing iff the ttree isn't in the input file
        TTree *ttree = (TTree*)fi->Get(sTTree);
        if(!ttree){cout<< "ERROR: Could not find TTree "<<sTTree<<" in file "<<endl; return;}

        // declaring the names of branches to get from the TTree
        TString sBranch = "nref";
        if(!ttree->GetBranch(sBranch)){cout<< "ERROR: Branch '"<<sBranch<<"' not found in "<<sTTree<<endl; return;}

        // turning off all branches
        ttree->SetBranchStatus("*",0);

        // turning on only the branch I want
        ttree->SetBranchStatus(sBranch,1);

        // assigning variable to branch
        ttree->SetBranchAddress(sBranch,&nref);

        // for loop going over events in the trees
        for(unsigned int i=0; i<ttree->GetEntries(); i++){
            
            // getting ttree info for each event
            ttree->GetEntry(i);

            // filling nref histogram
            hnref->Fill(nref);

            // changing the value of max nref iff nref is bigger for this event than the current max nref
            if(nref>nrefmax){nrefmax=nref;}
        }
        fi->Close();
    }

    cout<<"maximum number of jets is "<<nrefmax <<endl;

    /// Making output files
    TFile *fo = new TFile(output,"recreate");
    fo->cd();

    // writing the histograms to this new file
    hnref->Write();

    fo->Close();
}