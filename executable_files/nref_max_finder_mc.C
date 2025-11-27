#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"

void nref_max_finder_mc(TString input_filelist, TString output){

    // declaring variables //

    // event weight
    Float_t w;

    // number of jets
    Int_t nref;

    // max number of jets
    Int_t nrefmax = 0;

    // expected max number of jets
    const int nrefmax_guess = 200;
    
    // declaring nref binning
    const int nrefbins = nrefmax_guess;
    const int nreflims[2] = {0, nrefmax_guess};

    // initializing jet multiplicity histogram
    TH1I *hnref = new TH1I("hnref", "hnref", nrefbins, nreflims[0], nreflims[1]);
    TH1I *hnref_noweight = new TH1I("hnref_noweight", "hnref_noweight", nrefbins, nreflims[0], nreflims[1]);

    // getting list of root files to process
    ifstream myfile(input_filelist);
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

        // ttree names
        const Int_t nTTrees = 2;
        TString sTTrees[nTTrees] = {"hiEvtAnalyzer/HiTree", "ak4PFJetAnalyzer/t"};

        // getting ttrees, printing iff the ttree isn't in the input file
        TTree *ttrees[nTTrees];
        for(int t=0; t<nTTrees; t++){
            ttrees[t] = (TTree*)fi->Get(sTTrees[t]);
            if(!ttrees[t]){cout<< "ERROR: Could not find TTree "<<sTTrees[t]<<" in file "<<endl; return;}
        }

        // declaring the names of branches to get from the TTrees //

        // event
        TString sEvtBranch = "weight";
        // printing a statement for any branches that aren't in their specified ttree
        if(!ttrees[0]->GetBranch(sEvtBranch)){cout<< "ERROR: Branch '"<<sEvtBranch<<"' not found in "<<ttrees[0]<<endl; return;}

        // jets
        TString sJetBranch = "nref";
        if(!ttrees[1]->GetBranch(sJetBranch)){cout<< "ERROR: Branch '"<<sJetBranch<<"' not found in "<<ttrees[1]<<endl; return;}

        // turning off all branches 
        for(int t=0; t<nTTrees; t++){ttrees[t]->SetBranchStatus("*",0);}

        // turning on only the branches I want
        ttrees[0]->SetBranchStatus(sEvtBranch,1);
        ttrees[1]->SetBranchStatus(sJetBranch,1);

        // assigning variables to branches
        ttrees[0]->SetBranchAddress(sEvtBranch,&w);
        ttrees[1]->SetBranchAddress(sJetBranch,&nref);

        // for loop going over events in the trees
        for(unsigned int i=0; i<ttrees[0]->GetEntries(); i++){
            
            // getting ttree info for each event
            for(int t=0; t<nTTrees; t++){ttrees[t]->GetEntry(i);}

            // filling nref histogram
            hnref->Fill(nref, w);
            hnref_noweight->Fill(nref);

            // changing the value of max nref iff nref is bigger for this event than the current max nref
            if(nref>nrefmax){nrefmax=nref;}
        }
        fi->Close();
    }
    cout<<"end of file processing"<<endl;

    cout<<"maximum number of jets was "<<nrefmax <<endl;

    /// Making output files
    TFile *fo = new TFile(output,"recreate");
    fo->cd();

    // writing the histograms to this new file
    hnref->Write();
    hnref_noweight->Write();

    fo->Close();
}