#include "TROOT.h"
#include "TFile.h"
#include "TMath.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TDirectory.h"
#include <vector>
#include <iostream>

// #include "/afs/cern.ch/user/n/nbarnett/public/header_files/JetSelection_PbPb.h"
#include "/afs/cern.ch/user/n/nbarnett/public/header_files/JSON_handler.h"
#include "/afs/cern.ch/user/n/nbarnett/public/header_files/Jet_PbPb_DATA_binning.h"
#include "/afs/cern.ch/user/n/nbarnett/public/header_files/2025PbPb_JetTriggers.h"

void JetTurnOn_PbPb_DATA_lxplus(TString input_filelist, TString output_root, TString output_txt){

    // for applying JSON and Jet Selections from headers
    JSON_handler dcs;
    // JetSelect js;

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

    // triggers
    Int_t jet_HLT[nhlTrigs];
    Int_t jet_L1[nl1Trigs];

    // HLT Jet Objects
    vector<Float_t>* HLT_JetObj_pt[nhlTrigs];
    vector<Float_t>* HLT_JetObj_eta[nhlTrigs];
    vector<Float_t>* HLT_JetObj_phi[nhlTrigs];
    for(int t=0; t<nhlTrigs; t++){
        HLT_JetObj_pt[t] = new vector<Float_t>();
        HLT_JetObj_eta[t] = new vector<Float_t>();
        HLT_JetObj_phi[t] = new vector<Float_t>();
    }
    
    // initializing inclusive event histograms //

    // event info
    TH1F *hvz_unpassed = new TH1F("hvz_unpassed", "", nvzbins, vzlims[0], vzlims[1]);
    TH1F *hvz = new TH1F("hvz", "", nvzbins, vzlims[0], vzlims[1]);
    TH1I *hhiBin = new TH1I("hhiBin", "", nhibins, hibinlims[0], hibinlims[1]);
    TH1I *hnref = new TH1I("hnref", "", nrefbins, nreflims[0], nreflims[1]);
    TH1I *hrun = new TH1I("hrun", "", nrunbins, hrunlims[0], hrunlims[1]);

    // declaring histograms //

    /// by eta
    // jet pt
    TH1F *h_ljtpt_eta[netabins];
    TH1F *hl1_ljtpt_eta[netabins][nl1Trigs];
    TH1F *hhlt_ljtpt_eta[2][netabins][nhlTrigs];
    TH1F *hl1hlt_ljtpt_eta[2][netabins][nhlTrigs];

    /// by hibin
    TH1F *h_ljtpt_hibin[netabins][nhiBin];
    TH1F *hl1_ljtpt_hibin[netabins][nl1Trigs][nhiBin];
    TH1F *hhlt_ljtpt_hibin[2][netabins][nhlTrigs][nhiBin];
    TH1F *hl1hlt_ljtpt_hibin[2][netabins][nhlTrigs][nhiBin];

    // initializing histograms //

    TString hname = "hjtpt";
    
    // by eta
    for(unsigned int b=0; b<netabins; b++){

        hname = "hjtpt"+htitles_byeta[b];
        h_ljtpt_eta[b] = new TH1F(hname, hname, nptbins, ptlims[0], ptlims[1]);
        
        for(int t=0; t<nhlTrigs; t++){

            hname = "hjtpt"+htitles_byeta[b]+sHLTrigs_short[t];
            hhlt_ljtpt_eta[0][b][t] = new TH1F(hname, hname, nptbins, ptlims[0], ptlims[1]);

            hname = "hjtpt_dR"+htitles_byeta[b]+sHLTrigs_short[t];
            hhlt_ljtpt_eta[1][b][t] = new TH1F(hname, hname, nptbins, ptlims[0], ptlims[1]);

            hname = "hjtpt"+htitles_byeta[b]+"_l1t"+sHLTrigs_short[t];
            hl1hlt_ljtpt_eta[0][b][t] = new TH1F(hname, hname, nptbins, ptlims[0], ptlims[1]);

            hname = "hjtpt_dR"+htitles_byeta[b]+"_l1t"+sHLTrigs_short[t];
            hl1hlt_ljtpt_eta[1][b][t] = new TH1F(hname, hname, nptbins, ptlims[0], ptlims[1]);

            if(t>=nl1Trigs){continue;}

            hname = "hjtpt"+htitles_byeta[b]+sL1Trigs_short[t];
            hl1_ljtpt_eta[b][t] = new TH1F(hname, hname, nptbins, ptlims[0], ptlims[1]);
        }

        // by hiBin
        for(unsigned int hb=0; hb<nhiBin; hb++){
            
            hname = "hjtpt"+htitles_byeta[b]+htitles_byhibin[hb];
            h_ljtpt_hibin[b][hb] = new TH1F(hname, hname, nptbins, ptlims[0], ptlims[1]);
            
            for(int t=0; t<nhlTrigs; t++){

                hname = "hjtpt"+htitles_byeta[b]+sHLTrigs_short[t]+htitles_byhibin[hb];
                hhlt_ljtpt_hibin[0][b][t][hb] = new TH1F(hname, hname, nptbins, ptlims[0], ptlims[1]);

                hname = "hjtpt_dR"+htitles_byeta[b]+sHLTrigs_short[t]+htitles_byhibin[hb];
                hhlt_ljtpt_hibin[1][b][t][hb] = new TH1F(hname, hname, nptbins, ptlims[0], ptlims[1]);

                hname = "hjtpt"+htitles_byeta[b]+"_l1t"+sHLTrigs_short[t]+htitles_byhibin[hb];
                hl1hlt_ljtpt_hibin[0][b][t][hb] = new TH1F(hname, hname, nptbins, ptlims[0], ptlims[1]);

                hname = "hjtpt_dR"+htitles_byeta[b]+"_l1t"+sHLTrigs_short[t]+htitles_byhibin[hb];
                hl1hlt_ljtpt_hibin[1][b][t][hb] = new TH1F(hname, hname, nptbins, ptlims[0], ptlims[1]);

                if(t>=nl1Trigs){continue;}

                hname  = "hjtpt"+htitles_byeta[b]+sL1Trigs_short[t]+htitles_byhibin[hb];
                hl1_ljtpt_hibin[b][t][hb] = new TH1F(hname, hname, nptbins, ptlims[0], ptlims[1]);
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
    ifstream myfile(input_filelist);
    string filename;

    // making output text file
    std::ofstream outputFile(output_txt);

    // keeping track of how many files have been processed
    int filenumber = 0;

    // looping over root files from list
    while(getline(myfile, filename)){

        filenumber+=1;

        // reading and staging input file
        TString input = filename;
        TFile *fi = TFile::Open(input,"read");
        if(!fi){cout<< "ERROR: Could not open file "<<input<<endl; return;}
        fi->cd();

        // showing the file being processed in the terminal
        cout<<"processing file "<< filenumber <<": "<<input<<endl;

        // getting ttrees, printing iff the ttree isn't in the input file
        TTree *ttrees[nTTrees];
        for(int t=0; t<nTTrees; t++){
            ttrees[t] = (TTree*)fi->Get(sTTrees[t]);
            if(!ttrees[t]){cout<< "ERROR: Could not find TTree "<<sTTrees[t]<<" in file"<<endl; return;}
        }

        // trigger tree
        TTree *Trig_ttree = (TTree*)fi->Get(sTrigTree);
        if(!Trig_ttree){cout<< "ERROR: Could not find TTree "<<sTrigTree<<" in file"<<endl; return;}

        // HLT Object tree
        TTree *TrigObj_ttrees[nhlTrigs];
        for(int t=0; t<nhlTrigs; t++){
            TrigObj_ttrees[t] = (TTree*)fi->Get(sHLTObjTrees[t]);
            if(!TrigObj_ttrees[t]){cout<< "ERROR: Could not find TTree "<<sHLTObjTrees[t]<<" in file"<<endl; return;}
        }

        // printing a statement for any branches that aren't in their specified ttree
        for(int b=0; b<nEvtBranch; b++){if(!ttrees[0]->GetBranch(sEvtBranch[b])){cout<< "ERROR: Branch '"<<sEvtBranch[b]<<"' not found in "<<sTTrees[0]<<endl; return;}}
        for(int b=0; b<nFilters; b++){if(!ttrees[1]->GetBranch(sFilters[b])){cout<< "ERROR: Branch '"<<sFilters[b]<<"' not found in "<<sTTrees[1]<<endl; return;}}
        for(int b=0; b<nJetBranch; b++){if(!ttrees[2]->GetBranch(sJetBranch[b])){cout<< "ERROR: Branch '"<<sJetBranch[b]<<"' not found in "<<sTTrees[2]<<endl; return;}}
        for(int b=0; b<nhlTrigs; b++){if(!Trig_ttree->GetBranch(sHLTrigs[b])){cout<< "ERROR: Branch '"<<sHLTrigs[b]<<"' not found in "<<sTrigTree<<endl; return;}}
        for(int b=0; b<nl1Trigs; b++){if(!Trig_ttree->GetBranch(sL1Trigs[b])){cout<< "ERROR: Branch '"<<sL1Trigs[b]<<"' not found in "<<sTrigTree<<endl; return;}}

        // turning off all branches 
        for(int t=0; t<nTTrees; t++){ttrees[t]->SetBranchStatus("*",0);}
        Trig_ttree->SetBranchStatus("*",0);
        for(int t=0; t<nhlTrigs; t++){TrigObj_ttrees[t]->SetBranchStatus("*",0);}

        // turning on only the branches I want
        for(int b=0; b<nEvtBranch; b++){ttrees[0]->SetBranchStatus(sEvtBranch[b],1);}
        for(int b=0; b<nFilters; b++){ttrees[1]->SetBranchStatus(sFilters[b],1);}
        for(int b=0; b<nJetBranch; b++){ttrees[2]->SetBranchStatus(sJetBranch[b],1);}
        for(int b=0; b<nhlTrigs; b++){Trig_ttree->SetBranchStatus(sHLTrigs[b],1);}
        for(int b=0; b<nl1Trigs; b++){Trig_ttree->SetBranchStatus(sL1Trigs[b],1);}
        for(int t=0; t<nhlTrigs; t++){for(int b=0; b<nHLTObjBranch; b++){TrigObj_ttrees[t]->SetBranchStatus(sHLTObjBranch[b],1);}}

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

        // trigger ttree
        for(int b=0; b<nhlTrigs; b++){Trig_ttree->SetBranchAddress(sHLTrigs[b],&jet_HLT[b]);}
        for(int b=0; b<nl1Trigs; b++){Trig_ttree->SetBranchAddress(sL1Trigs[b],&jet_L1[b]);}

        // HLT object ttree
        for(int t=0; t<nhlTrigs; t++){TrigObj_ttrees[t]->SetBranchAddress(sHLTObjBranch[0],&HLT_JetObj_pt[t]);}
        for(int t=0; t<nhlTrigs; t++){TrigObj_ttrees[t]->SetBranchAddress(sHLTObjBranch[1],&HLT_JetObj_eta[t]);}
        for(int t=0; t<nhlTrigs; t++){TrigObj_ttrees[t]->SetBranchAddress(sHLTObjBranch[2],&HLT_JetObj_phi[t]);}

        // for loop going over events in the trees 
        for(unsigned int i=0; i<ttrees[0]->GetEntries(); i++){
            
            // getting ttree info from each event for event filters and vz
            ttrees[0]->GetEntry(i);
            ttrees[1]->GetEntry(i);

            // filling event cut histograms
            hvz_unpassed->Fill(vz);

            // checking if the event passes cuts
            // event cuts are primary vertex filter, cluster compatability filter, and |vz| < 15
            if((ppvF==0)||(pclustF==0)||(pphfF==0)||(TMath::Abs(vz)>15)){continue;}
            // getting jet tree info if the event cuts are passed
            ttrees[2]->GetEntry(i);
            Trig_ttree->GetEntry(i);
            for(int t=0; t<nhlTrigs; t++){TrigObj_ttrees[t]->GetEntry(i);}

            // applying JSON with header file
            if(!dcs.isGood(run, lumi)){continue;}

            // filling most event histograms
            hvz->Fill(vz);
            hhiBin->Fill(hiBin);

            /// Skipping events without jets
            if((nref==0)||(jtpt[0]<=0)){continue;}

            // terminal will yell at me if the leading jet index isn't zero (it never yells at me)
            Int_t lj = 0;
            for(Int_t j = 0; j<nref; j++){if(jtpt[j]>jtpt[lj]){lj=j;}}
            if(lj!=0){cout<<"leading jet index is "<<lj<<endl;}

            // only looking at events that fire the minbias l1 trigger
            if(jet_L1[0]==0){continue;}

            // jet pt cut applied to leading jet
            if(jtpt[0]<ptcut){continue;}

            // checking jet veto map 
            Double_t vetomapval = hvetomap->GetBinContent(hvetomap->FindBin(jteta[0], jtphi[0]));
            if(vetomapval!=0){continue;}

            //// AGREED UPON JET ID REQUIREMENTS ////
            if((jtPfCHF[0]>=0.99)||(jtPfCEF[0]>=0.8)||(jtPfMUF[0]>=0.8)){continue;}

            // matching HLT object to offline jet
            int iHltMatch[nhlTrigs] = {0};
            for(int t=0; t<nhlTrigs; t++){
                if(jet_HLT[t]==0){continue;}
                for(int tj=0; tj<HLT_JetObj_pt[t]->size(); tj++){
                    double deta = TMath::Abs(HLT_JetObj_eta[t]->at(tj)-jteta[0]);
                    double dphi = TMath::ACos(TMath::Cos(HLT_JetObj_phi[t]->at(tj)-jtphi[0]));
                    if(TMath::Sqrt(deta*deta + dphi*dphi)<0.3){iHltMatch[t]=1;}
                    if(HLT_JetObj_pt[t]->at(tj)<HLT_Thresh[t]){iHltMatch[t]=0;}
                }
            }
            // for(int t=0; t<nhlTrigs; t++){if((iHltMatch[t]==0)&&(jet_HLT[t]==1)){cout<<"no dR match but "<<sHLTrigs[t]<<" fires"<<endl;}}

            // filling last event histogram
            hnref->Fill(nref);

            for(unsigned int b=0; b<netabins; b++){
                if((TMath::Abs(jteta[0])<etalo[b])||(TMath::Abs(jteta[0])>etahi[b])){continue;}

                h_ljtpt_eta[b]->Fill(jtpt[0]);

                int flag_l1 = 0;
                int flag_lthlt = 0;
                
                for(int t=0; t<nhlTrigs; t++){

                    // writing out to text file when we have drops
                    if((iHltMatch[t]!=0)&&(jet_HLT[t]==0)&&(jtpt[0]>(HLT_Thresh[t]+40.0))){
                        cout<<"entry "<<i<<endl;
                        cout<<"leading jet pt is "<<jtpt[lj]<<endl;
                        cout<<", but "+sHLTrigs[t]+" didn't fire :("<<endl;
                        outputFile<<"\n"<< filename<<"\n";
                        outputFile<<"run is "<<run<<", lumi is "<<lumi<<", event is "<<event<<", entry is "<<i<<"\n";
                        outputFile<<"hiBin is "<<hiBin<<", leading jet pt is "<<jtpt[0]<<"\n";
                        outputFile<<"CHF:NHF:CEF:NEF:MUF are "<<jtPfCHF[0]<<":"<<jtPfNHF[0]<<":"<<jtPfCEF[0]<<":"<<jtPfNEF[0]<<":"<<jtPfMUF[0]<<"\n";
                        outputFile<<sHLTrigs[t]+" didn't fire\n";
                    }

                    if(jet_HLT[t]==1){
                        hhlt_ljtpt_eta[0][b][t]->Fill(jtpt[0]);
                        if(iHltMatch[t]==1){hhlt_ljtpt_eta[1][b][t]->Fill(jtpt[0]);}
                        if(jet_L1[L1SeedHLT[t]]==1){
                            hl1hlt_ljtpt_eta[0][b][t]->Fill(jtpt[0]);
                            flag_lthlt=1;
                            if(iHltMatch[t]==1){hl1hlt_ljtpt_eta[1][b][t]->Fill(jtpt[0]);}
                        }
                    }
                    if((t>=nl1Trigs)){continue;}
                    if(jet_L1[t]==1){
                        hl1_ljtpt_eta[b][t]->Fill(jtpt[0]);
                        flag_l1=1;
                    }
                }

                for(unsigned int hb=0; hb<nhiBin; hb++){   
                    if((hiBin<hiBinlo[hb])||(hiBin>hiBinhi[hb])){continue;}

                    h_ljtpt_hibin[b][hb]->Fill(jtpt[0]);
                    
                    for(int t=0; t<nhlTrigs; t++){
                        if(jet_HLT[t]==1){
                            hhlt_ljtpt_hibin[0][b][t][hb]->Fill(jtpt[0]);
                            if(iHltMatch[t]==1){hhlt_ljtpt_hibin[1][b][t][hb]->Fill(jtpt[0]);}
                            if(jet_L1[L1SeedHLT[t]]==1){
                                hl1hlt_ljtpt_hibin[0][b][t][hb]->Fill(jtpt[0]);
                                flag_lthlt=1;
                                if(iHltMatch[t]==1){hl1hlt_ljtpt_hibin[1][b][t][hb]->Fill(jtpt[0]);}
                            }
                        }
                        if((t>=nl1Trigs)){continue;}
                        if(jet_L1[t]==1){
                            hl1_ljtpt_hibin[b][t][hb]->Fill(jtpt[0]);
                            flag_l1=1;
                        }
                    }
                }
                if((flag_l1==0)&&(flag_lthlt==1)){cout<<"l1 check didn't pass, but l1 and hlt check passed in run:lumi:event "<<run<<":"<<lumi<<":"<<event<<endl;}
            }
        }
        fi->Close();
    }

    // making a new file to store the new histogram
    TFile *fo = new TFile(output_root,"recreate");
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
    hnref->Write();
    hrun->Write();

    // jet histograms by eta 
    for(unsigned int b=0; b<netabins; b++){
        dji->cd(); 
        h_ljtpt_eta[b]->Write();
        for(int t=0; t<nhlTrigs; t++){
            hhlt_ljtpt_eta[0][b][t]->Write();
            hl1hlt_ljtpt_eta[0][b][t]->Write();
            hhlt_ljtpt_eta[1][b][t]->Write();
            hl1hlt_ljtpt_eta[1][b][t]->Write();
            if((t>=nl1Trigs)){continue;}
            hl1_ljtpt_eta[b][t]->Write();
        }
        // for each hibin
        djh->cd();
        for(int hb=0; hb<nhiBin; hb++){
            h_ljtpt_hibin[b][hb]->Write();
            for(int t=0; t<nhlTrigs; t++){
                hhlt_ljtpt_hibin[0][b][t][hb]->Write();
                hl1hlt_ljtpt_hibin[0][b][t][hb]->Write();
                hhlt_ljtpt_hibin[1][b][t][hb]->Write();
                hl1hlt_ljtpt_hibin[1][b][t][hb]->Write();
                if((t>=nl1Trigs)){continue;}
                hl1_ljtpt_hibin[b][t][hb]->Write();
            }
        }
    }
    fo->Close();
    outputFile.close();
}
