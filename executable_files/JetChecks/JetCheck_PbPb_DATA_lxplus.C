#include "TROOT.h"
#include "TFile.h"
#include "TMath.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TDirectory.h"

#include "/afs/cern.ch/user/n/nbarnett/public/header_files/JetSelection_PbPb.h"
#include "/afs/cern.ch/user/n/nbarnett/public/header_files/JSON_handler.h"
#include "/afs/cern.ch/user/n/nbarnett/public/header_files/JSON_handler.h"
#include "/afs/cern.ch/user/n/nbarnett/public/header_files/Jet_PbPb_DATA_binning.h"

void JetCheck_PbPb_DATA_lxplus(TString input_filelist, TString output){

    // for applying JSON and Jet Selections from headers
    JSON_handler dcs;
    JetSelect js;

    // declaring variables //

    // event variables
    Float_t vz;
    Int_t hiBin;
    UInt_t run;
    ULong64_t event;
    UInt_t lumi;

    // filter
    Int_t ppvF;
    Int_t pclustF;
    Int_t pphfF;

    // jet momenta
    const Int_t nm = 100;
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
    
    // initializing inclusive event histograms //

    // event info
    TH1F *hvz_unpassed = new TH1F("hvz_unpassed", "", nvzbins, vzlims[0], vzlims[1]);
    TH1F *hvz = new TH1F("hvz", "", nvzbins, vzlims[0], vzlims[1]);
    TH1I *hhiBin = new TH1I("hhiBin", "", nhibins, hibinlims[0], hibinlims[1]);
    TH1I *hnref = new TH1I("hnref", "", nrefbins, nreflims[0], nreflims[1]);
    TH1I *hrun = new TH1I("hrun", "", nrunbins, hrunlims[0], hrunlims[1]);

    // declaring histograms //

    /// by eta
    // momenta
    TH1F *hjetmom_eta[nmom][nptcuts][netabins];
    TH2F *hjtetaphi_eta[nptcuts][netabins];
    // PF fractions
    TH1F *hjtPfF_eta[nfrac][nptcuts][netabins];
    /// by hibin
    TH1F *hjetmom_hibin[nmom][nptcuts][netabins][nhiBin];
    TH2F *hjtetaphi_hibin[nptcuts][netabins][nhiBin];
    TH1F *hjtPfF_hibin[nfrac][nptcuts][netabins][nhiBin];

    // initializing histograms //
    TString hname;

    // by pt cut
    for(unsigned int p=0; p<nptcuts; p++){
        // by eta
        for(unsigned int b=0; b<netabins; b++){
            // momenta
            for(int hj=0; hj<nmom; hj++){
                hname = smom[hj]+htitles_byptcut[p]+htitles_byeta[b];
                hjetmom_eta[hj][p][b] = new TH1F(hname, hname, nmombins[hj], nmomlo[hj], nmomhi[hj]);
            }
            // eta phi map
            hname = ep+htitles_byptcut[p]+htitles_byeta[b];
            hjtetaphi_eta[p][b] = new TH2F(hname, hname, nhetabins, etalims[0], etalims[1], nphibins, philims[0], philims[1]);
            // PF fractions & multiplicities
            for(int hj=0; hj<nfrac; hj++){
                hname = sfrac[hj]+htitles_byptcut[p]+htitles_byeta[b];
                hjtPfF_eta[hj][p][b] = new TH1F(hname, hname, npfbins, pflims[0], pflims[1]);
            }
            // by hiBin
            for(unsigned int hb=0; hb<nhiBin; hb++){
                for(int hj=0; hj<nmom; hj++){
                    hname = smom[hj]+htitles_byptcut[p]+htitles_byeta[b]+htitles_byhibin[hb];
                    hjetmom_hibin[hj][p][b][hb] = new TH1F(hname, hname, nmombins[hj], nmomlo[hj], nmomhi[hj]);
                }
                hname = ep+htitles_byptcut[p]+htitles_byeta[b]+htitles_byhibin[hb];
                hjtetaphi_hibin[p][b][hb] = new TH2F(hname, hname, nhetabins, etalims[0], etalims[1], nphibins, philims[0], philims[1]);
                for(int hj=0; hj<nfrac; hj++){
                    hname = sfrac[hj]+htitles_byptcut[p]+htitles_byeta[b]+htitles_byhibin[hb];
                    hjtPfF_hibin[hj][p][b][hb] = new TH1F(hname, hname, npfbins, pflims[0], pflims[1]);
                }
            }
        }
    }

    // getting list of root files to process
    ifstream myfile(input_filelist);
    string filename;

    // keeping track of how many files have been processed
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

        // getting ttrees, printing iff the ttree isn't in the input file
        TTree *ttrees[nTTrees];
        for(int t=0; t<nTTrees; t++){
            ttrees[t] = (TTree*)fi->Get(sTTrees[t]);
            if(!ttrees[t]){cout<< "ERROR: Could not find TTree "<<sTTrees[t]<<" in file"<<endl; return;}
        }

        // printing a statement for any branches that aren't in their specified ttree
        for(int b=0; b<nEvtBranch; b++){if(!ttrees[0]->GetBranch(sEvtBranch[b])){cout<< "ERROR: Branch '"<<sEvtBranch[b]<<"' not found in "<<sTTrees[0]<<endl; return;}}
        for(int b=0; b<nFilters; b++){if(!ttrees[1]->GetBranch(sFilters[b])){cout<< "ERROR: Branch '"<<sFilters[b]<<"' not found in "<<sTTrees[1]<<endl; return;}}
        for(int b=0; b<nJetBranch; b++){if(!ttrees[2]->GetBranch(sJetBranch[b])){cout<< "ERROR: Branch '"<<sJetBranch[b]<<"' not found in "<<sTTrees[2]<<endl; return;}}

        // turning off all branches 
        for(int t=0; t<nTTrees; t++){ttrees[t]->SetBranchStatus("*",0);}

        // turning on only the branches I want
        for(int b=0; b<nEvtBranch; b++){ttrees[0]->SetBranchStatus(sEvtBranch[b],1);}
        for(int b=0; b<nFilters; b++){ttrees[1]->SetBranchStatus(sFilters[b],1);}
        for(int b=0; b<nJetBranch; b++){ttrees[2]->SetBranchStatus(sJetBranch[b],1);}

        // assigning variables to branches //

        // event ttree
        ttrees[0]->SetBranchAddress(sEvtBranch[0],&vz);
        ttrees[0]->SetBranchAddress(sEvtBranch[1],&hiBin);
        ttrees[0]->SetBranchAddress(sEvtBranch[2],&run);
        ttrees[0]->SetBranchAddress(sEvtBranch[3],&event);
        ttrees[0]->SetBranchAddress(sEvtBranch[4],&lumi);

        // filter ttree
        ttrees[1]->SetBranchAddress(sFilters[0],&pclustF);
        ttrees[1]->SetBranchAddress(sFilters[1],&ppvF);
        ttrees[1]->SetBranchAddress(sFilters[2],&pphfF);

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

        // for loop going over events in the trees
        for(unsigned int i=0; i<ttrees[0]->GetEntries(); i++){
            
            // getting ttree info from each event for event filters and vz
            ttrees[0]->GetEntry(i);
            ttrees[1]->GetEntry(i);

            // filling event cut histograms
            hvz_unpassed->Fill(vz);

            // applying JSON //
            if(!dcs.isGood(run, lumi)){continue;}

            // checking if the event passes cuts
            // event cuts are primary vertex filter, cluster compatability filter, and |vz| < 15
            if((ppvF==0)||(pclustF==0)||(pphfF==0)||(TMath::Abs(vz)>15)){continue;}
            // getting jet tree info if the event cuts are passed
            ttrees[2]->GetEntry(i);

            // filling event histograms
            hvz->Fill(vz);
            hhiBin->Fill(hiBin);
            hrun->Fill(run);
            hnref->Fill(nref);

            /// Skipping events without jets
            if((nref==0)||(jtpt[0]<=0)){continue;}

            // looping through all jets in each event
            for(unsigned int j=0; j<nref; j++){
                
                // using header file for jet identification
                if(!js.JetSelection(jteta[j], jtphi[j], jtPfCEF[j], jtPfNEF[j],jtPfMUF[j])){continue;}
                
                // filling histograms //

                for(unsigned int p=0; p<nptcuts; p++){
                    if(jtpt[j]<ptcuts[p]){continue;}

                    for(unsigned int b=0; b<netabins; b++){
                        if((TMath::Abs(jteta[j])<etalo[b])||(TMath::Abs(jteta[j])>etahi[b])){continue;}

                        // jet momenta
                        hjetmom_eta[0][p][b]->Fill(rawpt[j]);
                        hjetmom_eta[1][p][b]->Fill(jtpt[j]);
                        hjetmom_eta[2][p][b]->Fill(jteta[j]);
                        hjetmom_eta[3][p][b]->Fill(jtphi[j]);
                        hjtetaphi_eta[p][b]->Fill(jteta[j], jtphi[j]);

                        // jet pf fractions
                        hjtPfF_eta[0][p][b]->Fill(jtPfCHF[j]);
                        hjtPfF_eta[1][p][b]->Fill(jtPfNHF[j]);
                        hjtPfF_eta[2][p][b]->Fill(jtPfCEF[j]);
                        hjtPfF_eta[3][p][b]->Fill(jtPfNEF[j]);
                        hjtPfF_eta[4][p][b]->Fill(jtPfMUF[j]);

                        // by hibin
                        for(int hb=0; hb<nhiBin; hb++){
                            if((hiBin<hiBinlo[hb])||(hiBin>hiBinhi[hb])){continue;}
                            
                            // leading jet momenta

                            // jet momenta
                            hjetmom_hibin[0][p][b][hb]->Fill(rawpt[j]);
                            hjetmom_hibin[1][p][b][hb]->Fill(jtpt[j]);
                            hjetmom_hibin[2][p][b][hb]->Fill(jteta[j]);
                            hjetmom_hibin[3][p][b][hb]->Fill(jtphi[j]);
                            hjtetaphi_hibin[p][b][hb]->Fill(jteta[j], jtphi[j]);

                            // jet pf fractions
                            hjtPfF_hibin[0][p][b][hb]->Fill(jtPfCHF[j]);
                            hjtPfF_hibin[1][p][b][hb]->Fill(jtPfNHF[j]);
                            hjtPfF_hibin[2][p][b][hb]->Fill(jtPfCEF[j]);
                            hjtPfF_hibin[3][p][b][hb]->Fill(jtPfNEF[j]);
                            hjtPfF_hibin[4][p][b][hb]->Fill(jtPfMUF[j]);
                        }
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
    TDirectory *dji = fo->mkdir("jet_inclusive");
    TDirectory *djh = fo->mkdir("jet_hibin");

    // event info histograms
    devt->cd();
    hvz_unpassed->Write();
    hvz->Write();
    hhiBin->Write();
    hrun->Write();
    hnref->Write();

    // jet histograms
    for(unsigned int p=0; p<nptcuts; p++){
        for(unsigned int b=0; b<netabins; b++){
            dji->cd(); 
            // momenta
            for(int hj=0; hj<nmom; hj++){hjetmom_eta[hj][p][b]->Write();}
            hjtetaphi_eta[p][b]->Write();
            // fractions
            for(int hj=0; hj<nfrac; hj++){hjtPfF_eta[hj][p][b]->Write();}
            // for each hibin
            djh->cd();
            for(int hb=0; hb<nhiBin; hb++){
                for(int hj=0; hj<nmom; hj++){hjetmom_hibin[hj][p][b][hb]->Write();}
                hjtetaphi_hibin[p][b][hb]->Write();
                for(int hj=0; hj<nfrac; hj++){hjtPfF_hibin[hj][p][b][hb]->Write();}
            }
        }
    }
    fo->Close();
}