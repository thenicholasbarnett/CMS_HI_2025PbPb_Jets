#include "TROOT.h"
#include "TFile.h"
#include "TMath.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TDirectory.h"

#include "/afs/cern.ch/user/n/nbarnett/public/header_files/Jet_PbPb_MC_binning.h"
#include "/afs/cern.ch/user/n/nbarnett/public/header_files/2025_PbPb_MC_Triggers.h"

void JetTurnOn_PbPb_MC_lxplus_v0_11_9_2025(TString input_file_list="/afs/cern.ch/user/n/nbarnett/public/txt_files/forest_locations_2025/forests_2025PbPb_DijetMC_fdamas_cmssw15_1_0_patch1.txt",TString output="/eos/cms/store/group/phys_heavyions/nbarnett/temp/11_9_2025/JetTurnOn_2025PbPbMC_11_9_2025_withDM.root"){

    // declaring variables //

    // event variables
    Float_t w;
    Float_t vz;
    Int_t hiBin;

    // filter
    Int_t ppvF;
    Int_t pclustF;

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
    Int_t jet_HLT[nhlTrigs];
    Int_t jet_L1[nl1Trigs];
    
    // initializing inclusive event histograms //

    // event info
    TH1F *hvz_unpassed = new TH1F("hvz_unpassed", "", nvzbins, vzlims[0], vzlims[1]);
    TH1F *hvz_unpassed_unweighted = new TH1F("hvz_unpassed_unweighted", "", nvzbins, vzlims[0], vzlims[1]);
    TH1F *hvz = new TH1F("hvz", "", nvzbins, vzlims[0], vzlims[1]);
    TH1I *hhiBin = new TH1I("hhiBin", "", nhibins, hibinlims[0], hibinlims[1]);
    TH1I *hnref = new TH1I("hnref", "", nrefbins, nreflims[0], nreflims[1]);

    // filters
    TH1I *hppvF = new TH1I("hppvF", "", ntrigbins, triglims[0], triglims[1]);
    TH1I *hpclustF = new TH1I("hpclustF", "", ntrigbins, triglims[0], triglims[1]);

    // declaring histograms //

    /// by eta
    // jet pt
    TH1F *h_ljtpt_eta[netabins];
    TH1F *hl1_ljtpt_eta[netabins][nl1Trigs];
    TH1F *hhlt_ljtpt_eta[netabins][nhlTrigs];
    TH1F *hl1hlt_ljtpt_eta[netabins][nhlTrigs];
    // eta phi maps
    TH2F *h_ep_eta[netabins];
    TH2F *hl1_ep_eta[netabins][nl1Trigs];
    TH2F *hhlt_ep_eta[netabins][nhlTrigs];
    TH2F *hl1hlt_ep_eta[netabins][nhlTrigs];

    /// by hibin
    TH1F *h_ljtpt_hibin[netabins][nhiBin];
    TH1F *hl1_ljtpt_hibin[netabins][nl1Trigs][nhiBin];
    TH1F *hhlt_ljtpt_hibin[netabins][nhlTrigs][nhiBin];
    TH1F *hl1hlt_ljtpt_hibin[netabins][nhlTrigs][nhiBin];
    TH2F *h_ep_hibin[netabins][nhiBin];
    TH2F *hl1_ep_hibin[netabins][nl1Trigs][nhiBin];
    TH2F *hhlt_ep_hibin[netabins][nhlTrigs][nhiBin];
    TH2F *hl1hlt_ep_hibin[netabins][nhlTrigs][nhiBin];

    // initializing histograms //
    
    // by eta
    for(unsigned int b=0; b<netabins; b++){

        // eta bin as a string
        TString sEtaBin = Form("_AbsEta_%.0f_to_%.0f",etalo[b]*10,etahi[b]*10);

        TString htitle0 = "hjtpt"+sEtaBin;
        h_ljtpt_eta[b] = new TH1F(htitle0, htitle0, nptbins, ptlims[0], ptlims[1]);

        TString htitle1 = "hetaphi"+sEtaBin;
        h_ep_eta[b] = new TH2F(htitle1, htitle1, nhetabins, etalims[0], etalims[1], nphibins, philims[0], philims[1]);
        
        for(int t=0; t<nhlTrigs; t++){

            TString htitle4 = "hjtpt"+sEtaBin+sHLTrigs_short[t];
            hhlt_ljtpt_eta[b][t] = new TH1F(htitle4, htitle4, nptbins, ptlims[0], ptlims[1]);

            TString htitle5 = "hetaphi"+sEtaBin+sHLTrigs_short[t];
            hhlt_ep_eta[b][t] = new TH2F(htitle5, htitle5, nhetabins, etalims[0], etalims[1], nphibins, philims[0], philims[1]);

            TString htitle6 = "hjtpt"+sEtaBin+"_l1t"+sHLTrigs_short[t];
            hl1hlt_ljtpt_eta[b][t] = new TH1F(htitle6, htitle6, nptbins, ptlims[0], ptlims[1]);

            TString htitle7 = "hetaphi"+sEtaBin+"_l1t"+sHLTrigs_short[t];
            hl1hlt_ep_eta[b][t] = new TH2F(htitle7, htitle7, nhetabins, etalims[0], etalims[1], nphibins, philims[0], philims[1]);

            if((t==nl1Trigs)||(t>nl1Trigs)){continue;}

            TString htitle2 = "hjtpt"+sEtaBin+sL1Trigs_short[t];
            hl1_ljtpt_eta[b][t] = new TH1F(htitle2, htitle2, nptbins, ptlims[0], ptlims[1]);

            TString htitle3 = "hetaphi"+sEtaBin+sL1Trigs_short[t];
            hl1_ep_eta[b][t] = new TH2F(htitle3, htitle3, nhetabins, etalims[0], etalims[1], nphibins, philims[0], philims[1]);
        }

        // by hiBin
        for(unsigned int hb=0; hb<nhiBin; hb++){

            // hibin as a string
            TString shiBin = Form("_hibin_%d_to_%d",hiBinlo[hb],hiBinhi[hb]);
            
            TString htitle8 = "hjtpt"+sEtaBin+shiBin;
            h_ljtpt_hibin[b][hb] = new TH1F(htitle8, htitle8, nptbins, ptlims[0], ptlims[1]);

            TString htitle9 = "hetaphi"+sEtaBin+shiBin;
            h_ep_hibin[b][hb] = new TH2F(htitle9, htitle9, nhetabins, etalims[0], etalims[1], nphibins, philims[0], philims[1]);
            
            for(int t=0; t<nhlTrigs; t++){

                TString htitle12 = "hjtpt"+sEtaBin+sHLTrigs_short[t]+shiBin;
                hhlt_ljtpt_hibin[b][t][hb] = new TH1F(htitle12, htitle12, nptbins, ptlims[0], ptlims[1]);

                TString htitle13 = "hetaphi"+sEtaBin+sHLTrigs_short[t]+shiBin;
                hhlt_ep_hibin[b][t][hb] = new TH2F(htitle13, htitle13, nhetabins, etalims[0], etalims[1], nphibins, philims[0], philims[1]);

                TString htitle14 = "hjtpt"+sEtaBin+"_l1t"+sHLTrigs_short[t]+shiBin;
                hl1hlt_ljtpt_hibin[b][t][hb] = new TH1F(htitle14, htitle14, nptbins, ptlims[0], ptlims[1]);

                TString htitle15 = "hetaphi"+sEtaBin+"_l1t"+sHLTrigs_short[t]+shiBin;
                hl1hlt_ep_hibin[b][t][hb] = new TH2F(htitle15, htitle15, nhetabins, etalims[0], etalims[1], nphibins, philims[0], philims[1]);

                if((t==nl1Trigs)||(t>nl1Trigs)){continue;}

                TString htitle10 = "hjtpt"+sEtaBin+sL1Trigs_short[t]+shiBin;
                hl1_ljtpt_hibin[b][t][hb] = new TH1F(htitle10, htitle10, nptbins, ptlims[0], ptlims[1]);

                TString htitle11 = "hetaphi"+sEtaBin+sL1Trigs_short[t]+shiBin;
                hl1_ep_hibin[b][t][hb] = new TH2F(htitle11, htitle11, nhetabins, etalims[0], etalims[1], nphibins, philims[0], philims[1]);
            }
        }
    }

    // getting jet veto map //

    // opening root file with map
    TString sfVetoMap = "/eos/cms/store/group/phys_heavyions/nbarnett/Winter25Prompt25_RunCDE.root";
    TFile *fvm = TFile::Open(sfVetoMap,"read");
   
    // getting map as 2d histogram
    TString shVetoMap = "jetvetomap_all";
    TH2D *hvetomap = (TH2D*)fvm->Get(shVetoMap);

    // getting list of root files to process
    ifstream myfile(input_file_list);
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
        for(int b=0; b<nhlTrigs; b++){if(!ttrees[3]->GetBranch(sHLTrigs[b])){cout<< "ERROR: Branch '"<<sHLTrigs[b]<<"' not found in "<<sTTrees[3]<<endl; return;}}
        for(int b=0; b<nl1Trigs; b++){if(!ttrees[3]->GetBranch(sL1Trigs[b])){cout<< "ERROR: Branch '"<<sL1Trigs[b]<<"' not found in "<<sTTrees[3]<<endl; return;}}

        // turning off all branches 
        for(int t=0; t<nTTrees; t++){ttrees[t]->SetBranchStatus("*",0);}

        // turning on only the branches I want
        for(int b=0; b<nEvtBranch; b++){ttrees[0]->SetBranchStatus(sEvtBranch[b],1);}
        for(int b=0; b<nFilters; b++){ttrees[1]->SetBranchStatus(sFilters[b],1);}
        for(int b=0; b<nJetBranch; b++){ttrees[2]->SetBranchStatus(sJetBranch[b],1);}
        for(int b=0; b<nhlTrigs; b++){ttrees[3]->SetBranchStatus(sHLTrigs[b],1);}
        for(int b=0; b<nl1Trigs; b++){ttrees[3]->SetBranchStatus(sL1Trigs[b],1);}

        // assigning variables to branches //

        // event ttree
        ttrees[0]->SetBranchAddress(sEvtBranch[0],&w);
        ttrees[0]->SetBranchAddress(sEvtBranch[1],&vz);
        ttrees[0]->SetBranchAddress(sEvtBranch[2],&hiBin);

        // filter ttree
        ttrees[1]->SetBranchAddress(sFilters[0],&pclustF);
        ttrees[1]->SetBranchAddress(sFilters[1],&ppvF);

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
        for(int b=0; b<nhlTrigs; b++){ttrees[3]->SetBranchAddress(sHLTrigs[b],&jet_HLT[b]);}
        for(int b=0; b<nl1Trigs; b++){ttrees[3]->SetBranchAddress(sL1Trigs[b],&jet_L1[b]);}

        // for loop going over events in the trees 
        for(unsigned int i=0; i<ttrees[0]->GetEntries(); i++){
            
            // getting ttree info from each event for event filters and vz
            ttrees[0]->GetEntry(i);
            ttrees[1]->GetEntry(i);

            // filling event cut histograms
            hvz_unpassed_unweighted->Fill(vz);
            hvz_unpassed->Fill(vz, w);
            hppvF->Fill(ppvF, w);
            hpclustF->Fill(pclustF, w);

            // checking if the event passes cuts
            // event cuts are primary vertex filter, cluster compatability filter, and |vz| < 15
            if((ppvF==0)||(pclustF==0)||(TMath::Abs(vz)>15)){continue;}
            // getting jet tree info if the event cuts are passed
            ttrees[2]->GetEntry(i);
            ttrees[3]->GetEntry(i);

            // filling event histograms
            hvz->Fill(vz, w);
            hnref->Fill(nref, w);
            hhiBin->Fill(hiBin, w);

            /// Skipping events without jets
            if((nref==0)||(jtpt[0]<=0)){continue;}

            for(unsigned int b=0; b<netabins; b++){
                if((TMath::Abs(jteta[0])<etalo[b])||(TMath::Abs(jteta[0])>etahi[b])){continue;}

                h_ljtpt_eta[b]->Fill(jtpt[0], w);
                h_ep_eta[b]->Fill(jteta[0], jtphi[0], w);

                int flag_l1 = 0;
                int flag_lthlt = 0;
                
                for(int t=0; t<nhlTrigs; t++){
                    if(jet_HLT[t]==1){
                        hhlt_ljtpt_eta[b][t]->Fill(jtpt[0], w);
                        hhlt_ep_eta[b][t]->Fill(jteta[0], jtphi[0], w);
                        if(((t==0)||(t==1))&&(jet_L1[0]==1)){
                            hl1hlt_ljtpt_eta[b][t]->Fill(jtpt[0], w);
                            hl1hlt_ep_eta[b][t]->Fill(jteta[0], jtphi[0], w);
                            flag_lthlt=1;
                        }
                        if((t==2)&&(jet_L1[1]==1)){
                            hl1hlt_ljtpt_eta[b][t]->Fill(jtpt[0], w);
                            hl1hlt_ep_eta[b][t]->Fill(jteta[0], jtphi[0], w);
                            flag_lthlt=1;
                        }
                    }
                    if((t==nl1Trigs)||(t>nl1Trigs)){continue;}
                    if(jet_L1[t]==1){
                        hl1_ljtpt_eta[b][t]->Fill(jtpt[0], w);
                        hl1_ep_eta[b][t]->Fill(jteta[0], jtphi[0], w);
                        flag_l1=1;
                    }
                    if((flag_l1==0)&&(flag_lthlt==1)){cout<<"l1 check didn't pass, but l1 and hlt check passed"<<endl;}
                }

                for(unsigned int hb=0; hb<nhiBin; hb++){   
                    if((hiBin<hiBinlo[hb])||(hiBin>hiBinhi[hb])){continue;}

                    h_ljtpt_hibin[b][hb]->Fill(jtpt[0], w);
                    h_ep_hibin[b][hb]->Fill(jteta[0], jtphi[0], w);
                    
                    for(int t=0; t<nhlTrigs; t++){
                        if(jet_HLT[t]==1){
                            hhlt_ljtpt_hibin[b][t][hb]->Fill(jtpt[0], w);
                            hhlt_ep_hibin[b][t][hb]->Fill(jteta[0], jtphi[0], w);
                            if(((t==0)||(t==1))&&(jet_L1[0]==1)){
                                hl1hlt_ljtpt_hibin[b][t][hb]->Fill(jtpt[0], w);
                                hl1hlt_ep_hibin[b][t][hb]->Fill(jteta[0], jtphi[0], w);
                                flag_lthlt=1;
                            }
                            if((t==2)&&(jet_L1[1]==1)){
                                hl1hlt_ljtpt_hibin[b][t][hb]->Fill(jtpt[0], w);
                                hl1hlt_ep_hibin[b][t][hb]->Fill(jteta[0], jtphi[0], w);
                                flag_lthlt=1;
                            }
                        }
                        if((t==nl1Trigs)||(t>nl1Trigs)){continue;}
                        if(jet_L1[t]==1){
                            hl1_ljtpt_hibin[b][t][hb]->Fill(jtpt[0], w);
                            hl1_ep_hibin[b][t][hb]->Fill(jteta[0], jtphi[0], w);
                            flag_l1=1;
                        }
                        if((flag_l1==0)&&(flag_lthlt==1)){cout<<"l1 check didn't pass, but l1 and hlt check passed"<<endl;}
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
    hvz_unpassed_unweighted->Write();
    hvz_unpassed->Write();
    hvz->Write();
    hppvF->Write();
    hpclustF->Write();
    hnref->Write();

    // jet histograms by eta 
    for(unsigned int b=0; b<netabins; b++){
        dji->cd(); 

        h_ljtpt_eta[b]->Write();
        h_ep_eta[b]->Write();
        
        for(int t=0; t<nhlTrigs; t++){
            hhlt_ljtpt_eta[b][t]->Write();
            hhlt_ep_eta[b][t]->Write();
            hl1hlt_ljtpt_eta[b][t]->Write();
            hl1hlt_ep_eta[b][t]->Write();
            if((t==nl1Trigs)||(t>nl1Trigs)){continue;}
            hl1_ljtpt_eta[b][t]->Write();
            hl1_ep_eta[b][t]->Write();
        }

        // for each hibin
        djh->cd();
        for(int hb=0; hb<nhiBin; hb++){

            h_ljtpt_hibin[b][hb]->Write();
            h_ep_hibin[b][hb]->Write();
            
            for(int t=0; t<nhlTrigs; t++){
                hhlt_ljtpt_hibin[b][t][hb]->Write();
                hhlt_ep_hibin[b][t][hb]->Write();
                hl1hlt_ljtpt_hibin[b][t][hb]->Write();
                hl1hlt_ep_hibin[b][t][hb]->Write();
                if((t==nl1Trigs)||(t>nl1Trigs)){continue;}
                hl1_ljtpt_hibin[b][t][hb]->Write();
                hl1_ep_hibin[b][t][hb]->Write();
            }
        }
    }
    fo->Close();
}