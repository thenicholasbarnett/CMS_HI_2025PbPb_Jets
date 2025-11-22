#include "TROOT.h"
#include "TFile.h"
#include "TMath.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TDirectory.h"

#include "/afs/cern.ch/user/n/nbarnett/public/header_files/JetCheck_lowPUpp_binning.h"

void JetCheck_lowPUpp_lxplus(){

    TString input_file_list = "/afs/cern.ch/user/n/nbarnett/public/temp/10_28_2025/forests_lowpupp_10_30_2025.txt";
    // TString output = "JetRecoCheck_lowPUpp_v2_10_30_2025_vetomap_jetid.root";
    TString output = "JetRecoCheck_lowPUpp_v2_10_30_2025.root";

    // declaring variables //

    // event variables
    Float_t vz;

    // filter
    Int_t ppvF;

    // jet momenta
    const Int_t nm = 200;
    Int_t nref;
    Float_t rawpt[nm];
    Float_t jtpt[nm];
    Float_t jtphi[nm];
    Float_t jteta[nm];

    // PF fractions
    Float_t jtPfCHF[nm];
    Float_t jtPfNHF[nm];
    Float_t jtPfCEF[nm];
    Float_t jtPfNEF[nm];
    Float_t jtPfMUF[nm];

    // multiplicites
    Int_t jtPfCHM[nm];
    Int_t jtPfNHM[nm];
    Int_t jtPfCEM[nm];
    Int_t jtPfNEM[nm];
    Int_t jtPfMUM[nm];

    // triggers
    Int_t jet_HLT[nTrigs];
    
    // initializing inclusive event histograms //

    // event info
    TH1F *hvz_unpassed = new TH1F("hvz_unpassed", "hvz_unpassed", nvzbins, vzlims[0], vzlims[1]);
    TH1F *hvz = new TH1F("hvz", "hvz", nvzbins, vzlims[0], vzlims[1]);
    TH1I *hnref = new TH1I("hnref", "hnref", nrefbins, nreflims[0], nreflims[1]);

    // filters
    TH1I *hppvF = new TH1I("hppvF", "hppvF", ntrigbins, triglims[0], triglims[1]);

    // declaring jet histograms by eta //

    // momenta
    TH1F *hjetmom_eta[nmom][netabins];
    TH2F *hjtetaphi_eta[netabins];

    // PF fractions & multiplicities
    TH1F *hjtPfF_eta[nfrac][netabins];
    TH1F *hjtPfM_eta[nmult][netabins];

    // initializing histograms by eta //
    for(unsigned int b=0; b<netabins; b++){

        // eta bin as a string
        TString sEtaBin = Form("_AbsEta_%.0f_to_%.0f",etalo[b]*10,etahi[b]*10);

        // momenta
        for(int hj=0; hj<nmom; hj++){hjetmom_eta[hj][b] = new TH1F(smom[hj]+sEtaBin, smom[hj]+sEtaBin, nmombins[hj], nmomlo[hj], nmomhi[hj]);}
        hjtetaphi_eta[b] = new TH2F("hjtetaphi"+sEtaBin, "hjtetaphi"+sEtaBin, nhetabins, etalims[0], etalims[1], nphibins, philims[0], philims[1]);

        // PF fractions & multiplicities
        for(int hj=0; hj<nfrac; hj++){
            hjtPfF_eta[hj][b] = new TH1F(sfrac[hj]+sEtaBin, sfrac[hj]+sEtaBin, npfbins, pflims[0], pflims[1]);
            hjtPfM_eta[hj][b] = new TH1F(smult[hj]+sEtaBin, smult[hj]+sEtaBin, npfbins, pfmlims[0], pfmlims[1]);
        }
    }

    // declaring histograms by eta for triggers //

    // momenta
    TH1F *hjetmom_trig[nmom][netabins][nTrigs];
    TH2F *hjtetaphi_trig[netabins][nTrigs];

    // PF fractions & multiplicities
    TH1F *hjtPfF_trig[nfrac][netabins][nTrigs];
    TH1F *hjtPfM_trig[nmult][netabins][nTrigs];

    // initializing histograms by eta for triggers //
    for(unsigned int tr=0; tr<nTrigs; tr++){
        for(unsigned int b=0; b<netabins; b++){

        // eta bin as a string
        TString sEtaBin = Form("_AbsEta_%.0f_to_%.0f",etalo[b]*10,etahi[b]*10);

            // momemnta
            for(int hj=0; hj<nmom; hj++){hjetmom_trig[hj][b][tr] = new TH1F(smom[hj]+sEtaBin+sTrigs_short[tr], smom[hj]+sEtaBin+sTrigs_short[tr], nmombins[hj], nmomlo[hj], nmomhi[hj]);}
            hjtetaphi_trig[b][tr] = new TH2F("hjtetaphi"+sEtaBin+sTrigs_short[tr], "hjtetaphi"+sEtaBin+sTrigs_short[tr], nhetabins, etalims[0], etalims[1], nphibins, philims[0], philims[1]);

            // PF fractions & multiplicities
            for(int hj=0; hj<nfrac; hj++){
                hjtPfF_trig[hj][b][tr] = new TH1F(sfrac[hj]+sEtaBin+sTrigs_short[tr], sfrac[hj]+sEtaBin+sTrigs_short[tr], npfbins, pflims[0], pflims[1]);
                hjtPfM_trig[hj][b][tr] = new TH1F(smult[hj]+sEtaBin+sTrigs_short[tr], smult[hj]+sEtaBin+sTrigs_short[tr], npfbins, pfmlims[0], pfmlims[1]);
            }
        }
    }

    // getting jet veto map //

    // opening root file with map
    TString sfVetoMap = "/eos/cms/store/group/phys_heavyions/nbarnett/Summer23BPixPrompt23_RunD_v1.root";
    TFile *fvm = TFile::Open(sfVetoMap,"read");
   
    // getting map as 2d histogram
    TString shVetoMap = "jetvetomap_all";
    TH2D *hvetomap = (TH2D*)fvm->Get(shVetoMap);

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

        // ttree names
        const Int_t nTTrees = 4;
        TString sTTrees[nTTrees] = {"hiEvtAnalyzer/HiTree", "skimanalysis/HltTree", "ak0PFJetAnalyzer/t", "hltanalysis/HltTree"};

        // getting ttrees, printing iff the ttree isn't in the input file
        TTree *ttrees[nTTrees];
        for(int t=0; t<nTTrees; t++){
            ttrees[t] = (TTree*)fi->Get(sTTrees[t]);
            if(!ttrees[t]){cout<< "ERROR: Could not find TTree "<<sTTrees[t]<<" in file"<<endl; return;}
        }

        // event
        TString sEvtBranch = "vz";
        // printing a statement for any branches that aren't in their specified ttree
        if(!ttrees[0]->GetBranch(sEvtBranch)){cout<< "ERROR: Branch '"<<sEvtBranch<<"' not found in "<<sTTrees[0]<<endl; return;}

        // filter
        TString sFilter = "pprimaryVertexFilter";
        if(!ttrees[1]->GetBranch(sFilter)){cout<< "ERROR: Branch '"<<sFilter<<"' not found in "<<sTTrees[1]<<endl; return;}

        // jet branches
        const Int_t nJetBranch = 15;
        TString sJetBranch[nJetBranch] = {"nref", "rawpt", "jtpt", "jteta", "jtphi", "jtPfCHF", "jtPfNHF", "jtPfCEF", "jtPfNEF", "jtPfMUF", "jtPfCHM", "jtPfNHM", "jtPfCEM", "jtPfNEM", "jtPfMUM"};
        for(int b=0; b<nJetBranch; b++){if(!ttrees[2]->GetBranch(sJetBranch[b])){cout<< "ERROR: Branch '"<<sJetBranch[b]<<"' not found in "<<sTTrees[2]<<endl; return;}}

        // triggers
        for(int b=0; b<nTrigs; b++){if(!ttrees[3]->GetBranch(sTrigs[b])){cout<< "ERROR: Branch '"<<sTrigs[b]<<"' not found in "<<sTTrees[3]<<endl; return;}}

        // turning off all branches 
        for(int t=0; t<nTTrees; t++){ttrees[t]->SetBranchStatus("*",0);}

        // turning on only the branches I want
        ttrees[0]->SetBranchStatus(sEvtBranch,1);
        ttrees[1]->SetBranchStatus(sFilter,1);
        for(int b=0; b<nJetBranch; b++){ttrees[2]->SetBranchStatus(sJetBranch[b],1);}
        for(int b=0; b<nTrigs; b++){ttrees[3]->SetBranchStatus(sTrigs[b],1);}

        // assigning variables to branches //

        // event ttree
        ttrees[0]->SetBranchAddress(sEvtBranch,&vz);

        // filter ttree
        ttrees[1]->SetBranchAddress(sFilter,&ppvF);

        /// jet ttree
        // multiplicity
        ttrees[2]->SetBranchAddress(sJetBranch[0],&nref);
        // momenta
        ttrees[2]->SetBranchAddress(sJetBranch[1],rawpt);
        ttrees[2]->SetBranchAddress(sJetBranch[2],jtpt);
        ttrees[2]->SetBranchAddress(sJetBranch[3],jteta);
        ttrees[2]->SetBranchAddress(sJetBranch[4],jtphi);
        // pf fractions
        ttrees[2]->SetBranchAddress(sJetBranch[5],jtPfCHF);
        ttrees[2]->SetBranchAddress(sJetBranch[6],jtPfNHF);
        ttrees[2]->SetBranchAddress(sJetBranch[7],jtPfCEF);
        ttrees[2]->SetBranchAddress(sJetBranch[8],jtPfNEF);
        ttrees[2]->SetBranchAddress(sJetBranch[9],jtPfMUF);
        // multiplicities
        ttrees[2]->SetBranchAddress(sJetBranch[10],jtPfCHM);
        ttrees[2]->SetBranchAddress(sJetBranch[11],jtPfNHM);
        ttrees[2]->SetBranchAddress(sJetBranch[12],jtPfCEM);
        ttrees[2]->SetBranchAddress(sJetBranch[13],jtPfNEM);
        ttrees[2]->SetBranchAddress(sJetBranch[14],jtPfMUM);

        // trigger ttree
        for(int b=0; b<nTrigs; b++){ttrees[3]->SetBranchAddress(sTrigs[b],&jet_HLT[b]);}

        // for loop going over events in the trees
        for(unsigned int i=0; i<ttrees[0]->GetEntries(); i++){
            
            // getting ttree info from each event for event filters and vz
            ttrees[0]->GetEntry(i);
            ttrees[1]->GetEntry(i);

            // filling event cut histograms
            hvz_unpassed->Fill(vz);
            hppvF->Fill(ppvF);

            // checking if the event passes cuts
            // event cuts are primary vertex filter, cluster compatability filter, and |vz| < 15
            if((ppvF==0)||(TMath::Abs(vz)>15)){continue;}
            // getting jet tree info if the event cuts are passed
            ttrees[2]->GetEntry(i);
            ttrees[3]->GetEntry(i);

            // filling event histograms
            hvz->Fill(vz);
            hnref->Fill(nref);

            /// Skipping events without jets
            if((nref==0)||(jtpt[0]<=0)){continue;}

            // looping through all jets in each event
            for(unsigned int j=0; j<nref; j++){

                // // checking jet veto map 
                // Double_t vetomapval = hvetomap->GetBinContent(hvetomap->FindBin(jteta[j], jtphi[j]));
                // if(vetomapval!=0){continue;}
               
                // // jet ID requirements for leading jet
                // // https://twiki.cern.ch/twiki/bin/view/CMS/JetID13p6TeV
                // // multiplicity
                // Int_t mult = jtPfCHM[j]+jtPfNHM[j]+jtPfCEM[j]+jtPfNEM[j]+jtPfMUM[j];
                // // charged multiplicity
                // Int_t mult_ch = jtPfCHM[j]+jtPfCEM[j]+jtPfMUM[j];
                // // nuetral multiplicity
                // Int_t mult_nu = jtPfNHM[j]+jtPfNEM[j];
                // // suggested requirements by eta range
                // if((TMath::Abs(jteta[j])<=2.6)&&((jtPfNHF[j]>=0.9)||(jtPfNEF[j]>=0.9)||(mult<=1)||(jtPfMUF[j]>=0.8)||(jtPfCHF[j]<=0.01)||(mult_ch<=0)||(jtPfCEF[j]>=0.8))){continue;}
                // if(((TMath::Abs(jteta[j])>2.6)&&(TMath::Abs(jteta[j])<=2.7))&&((jtPfNHF[j]>=0.9)||(jtPfNEF[j]>=0.99)||(jtPfMUF[j]>=0.8)||(mult_ch<=0)||(jtPfCEF[j]>=0.8))){continue;}
                // if(((TMath::Abs(jteta[j])>2.7)&&(TMath::Abs(jteta[j])<=3.0))&&((jtPfNEF[j]>=0.99)||(mult_nu<=1))){continue;}
                // if(((TMath::Abs(jteta[j])>3.0)&&(TMath::Abs(jteta[j])<=5.0))&&((jtPfNHF[j]<=0.2)||(jtPfNEF[j]>=0.9)||(mult_nu<=10))){continue;}

                if(jtPfCHF[j]>0.99){continue;}
                if(jtPfMUF[j]>0.8){continue;}

                // filling histograms //

                // by eta
                for(unsigned int b=0; b<netabins; b++){
                    
                    if(TMath::Abs(jteta[j])>etahi[b]){continue;}

                    // jet momenta
                    hjetmom_eta[0][b]->Fill(rawpt[j]);
                    hjetmom_eta[1][b]->Fill(jtpt[j]);
                    hjetmom_eta[2][b]->Fill(jteta[j]);
                    hjetmom_eta[3][b]->Fill(jtphi[j]);
                    hjtetaphi_eta[b]->Fill(jteta[j], jtphi[j]);

                    // jet pf fractions
                    hjtPfF_eta[0][b]->Fill(jtPfCHF[j]);
                    hjtPfF_eta[1][b]->Fill(jtPfNHF[j]);
                    hjtPfF_eta[2][b]->Fill(jtPfCEF[j]);
                    hjtPfF_eta[3][b]->Fill(jtPfNEF[j]);
                    hjtPfF_eta[4][b]->Fill(jtPfMUF[j]);

                    // jet pf multiplicities
                    hjtPfM_eta[0][b]->Fill(jtPfCHM[j]);
                    hjtPfM_eta[1][b]->Fill(jtPfNHM[j]);
                    hjtPfM_eta[2][b]->Fill(jtPfCEM[j]);
                    hjtPfM_eta[3][b]->Fill(jtPfNEM[j]);
                    hjtPfM_eta[4][b]->Fill(jtPfMUM[j]);
                    
                    // for triggers
                    for(unsigned int tr=0; tr<nTrigs; tr++){
                        if(jet_HLT[tr]==0){continue;}

                        // jet momenta
                        hjetmom_trig[0][b][tr]->Fill(rawpt[j]);
                        hjetmom_trig[1][b][tr]->Fill(jtpt[j]);
                        hjetmom_trig[2][b][tr]->Fill(jteta[j]);
                        hjetmom_trig[3][b][tr]->Fill(jtphi[j]);
                        hjtetaphi_trig[b][tr]->Fill(jteta[j], jtphi[j]);

                        // jet pf fractions
                        hjtPfF_trig[0][b][tr]->Fill(jtPfCHF[j]);
                        hjtPfF_trig[1][b][tr]->Fill(jtPfNHF[j]);
                        hjtPfF_trig[2][b][tr]->Fill(jtPfCEF[j]);
                        hjtPfF_trig[3][b][tr]->Fill(jtPfNEF[j]);
                        hjtPfF_trig[4][b][tr]->Fill(jtPfMUF[j]);

                        // jet pf multiplicities
                        hjtPfM_trig[0][b][tr]->Fill(jtPfCHM[j]);
                        hjtPfM_trig[1][b][tr]->Fill(jtPfNHM[j]);
                        hjtPfM_trig[2][b][tr]->Fill(jtPfCEM[j]);
                        hjtPfM_trig[3][b][tr]->Fill(jtPfNEM[j]);
                        hjtPfM_trig[4][b][tr]->Fill(jtPfMUM[j]);
                    }
                }
            }
        }
        fi->Close();
    }

    // making a new file to store the new histogram
    TFile *fo = new TFile(output,"recreate");
    fo->cd();

    // writing the histogram to this new file //

    // making directories in output root file
    TDirectory *devt = fo->mkdir("event");
    TDirectory *dje = fo->mkdir("jet_eta");
    TDirectory *djt = fo->mkdir("jet_trig");

    // event info histograms
    devt->cd();
    hvz_unpassed->Write();
    hvz->Write();
    hppvF->Write();
    hnref->Write();


    // jet histograms by eta 
    dje->cd();
    for(unsigned int b=0; b<netabins; b++){

        // momenta
        for(int hj=0; hj<nmom; hj++){hjetmom_eta[hj][b]->Write();}
        hjtetaphi_eta[b]->Write();

        // fractions & multiplicities
        for(int hj=0; hj<nfrac; hj++){
            hjtPfF_eta[hj][b]->Write();
            hjtPfM_eta[hj][b]->Write();
        }
    }

    // for each trigger
    djt->cd();
    for(unsigned int b=0; b<netabins; b++){
        for(unsigned int tr=0; tr<nTrigs; tr++){
        
            // momenta
            for(int hj=0; hj<nmom; hj++){hjetmom_trig[hj][b][tr]->Write();}
            hjtetaphi_trig[b][tr]->Write();

            // fractions & multiplicities
            for(int hj=0; hj<nfrac; hj++){
                hjtPfF_trig[hj][b][tr]->Write();
                hjtPfM_trig[hj][b][tr]->Write();
            }
        }
    }
    fo->Close();
}
