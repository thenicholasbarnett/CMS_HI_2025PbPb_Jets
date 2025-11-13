#include "TROOT.h"
#include "TFile.h"
#include "TMath.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TDirectory.h"

#include "/afs/cern.ch/user/n/nbarnett/public/header_files/Jet_PbPb_DATA_binning.h"

// void JetCheck_PbPb_DATA_lxplus_v0_11_10_2025(TString input_file_list="/afs/cern.ch/user/n/nbarnett/public/txt_files/forest_locations_2025/forests_RawPrime_Replay.txt", TString output="/eos/cms/store/group/phys_heavyions/nbarnett/temp/11_12_2025/RawPrime_Replay_JetChecks_ptcut20.root"){
void JetCheck_PbPb_DATA_lxplus_v0_11_10_2025_OG(TString input_file_list="/afs/cern.ch/user/n/nbarnett/public/txt_files/forest_locations_2025/forests_RawPrime_OG.txt", TString output="/eos/cms/store/group/phys_heavyions/nbarnett/temp/11_12_2025/RawPrime_OG_JetChecks_ptcut20.root"){

    // declaring variables //

    // event variables
    Float_t vz;
    Int_t hiBin;
    UInt_t run;

    // filter
    Int_t ppvF;
    Int_t pclustF;

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

    // multiplicites
    Int_t jtPfCHM[nm];
    Int_t jtPfNHM[nm];
    Int_t jtPfCEM[nm];
    Int_t jtPfNEM[nm];
    Int_t jtPfMUM[nm];
    
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
    // momenta
    TH1F *hjetmom_eta[nmom][netabins];
    TH2F *hjtetaphi_eta[netabins];
    // PF fractions & multiplicities
    TH1F *hjtPfF_eta[nfrac][netabins];
    TH1F *hjtPfM_eta[nmult][netabins];

    /// by hibin
    TH1F *hjetmom_hibin[nmom][netabins][nhiBin];
    TH2F *hjtetaphi_hibin[netabins][nhiBin];
    TH1F *hjtPfF_hibin[nfrac][netabins][nhiBin];
    TH1F *hjtPfM_hibin[nmult][netabins][nhiBin];

    // initializing histograms //
    
    // by eta
    for(unsigned int b=0; b<netabins; b++){

        // momenta
        for(int hj=0; hj<nmom; hj++){
            TString htitle0 = smom[hj]+htitles_byeta[b];
            hjetmom_eta[hj][b] = new TH1F(htitle0, htitle0, nmombins[hj], nmomlo[hj], nmomhi[hj]);
        }
        
        // eta phi map
        TString htitle1 = "hjtetaphi"+htitles_byeta[b];
        hjtetaphi_eta[b] = new TH2F(htitle1, htitle1, nhetabins, etalims[0], etalims[1], nphibins, philims[0], philims[1]);

        // PF fractions & multiplicities
        for(int hj=0; hj<nfrac; hj++){
            TString htitle2 = sfrac[hj]+htitles_byeta[b];
            hjtPfF_eta[hj][b] = new TH1F(htitle2, htitle2, npfbins, pflims[0], pflims[1]);

            TString htitle3 = smult[hj]+htitles_byeta[b];
            hjtPfM_eta[hj][b] = new TH1F(htitle3, htitle3, npfmbins, pfmlims[0], pfmlims[1]);
        }

        // by hiBin
        for(unsigned int hb=0; hb<nhiBin; hb++){
        
            for(int hj=0; hj<nmom; hj++){
                TString htitle4 = smom[hj]+htitles_byeta[b]+htitles_byhibin[hb];
                hjetmom_hibin[hj][b][hb] = new TH1F(htitle4, htitle4, nmombins[hj], nmomlo[hj], nmomhi[hj]);
            }

            TString htitle5 = "hjtetaphi"+htitles_byeta[b]+htitles_byhibin[hb];
            hjtetaphi_hibin[b][hb] = new TH2F(htitle5, htitle5, nhetabins, etalims[0], etalims[1], nphibins, philims[0], philims[1]);

            for(int hj=0; hj<nfrac; hj++){

                TString htitle6 = sfrac[hj]+htitles_byeta[b]+htitles_byhibin[hb];
                hjtPfF_hibin[hj][b][hb] = new TH1F(htitle6, htitle6, npfbins, pflims[0], pflims[1]);

                TString htitle7 = smult[hj]+htitles_byeta[b]+htitles_byhibin[hb];
                hjtPfM_hibin[hj][b][hb] = new TH1F(htitle7, htitle7, npfmbins, pfmlims[0], pfmlims[1]);
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

        // for loop going over events in the trees
        for(unsigned int i=0; i<ttrees[0]->GetEntries(); i++){
            
            // getting ttree info from each event for event filters and vz
            ttrees[0]->GetEntry(i);
            ttrees[1]->GetEntry(i);

            // filling event cut histograms
            hvz_unpassed_unweighted->Fill(vz);
            hvz_unpassed->Fill(vz);
            hppvF->Fill(ppvF);
            hpclustF->Fill(pclustF);

            // checking if the event passes cuts
            // event cuts are primary vertex filter, cluster compatability filter, and |vz| < 15
            if((ppvF==0)||(pclustF==0)||(TMath::Abs(vz)>15)){continue;}
            // getting jet tree info if the event cuts are passed
            ttrees[2]->GetEntry(i);

            // filling event histograms
            hvz->Fill(vz);
            hnref->Fill(nref);
            hhiBin->Fill(hiBin);

            /// Skipping events without jets
            if((nref==0)||(jtpt[0]<=0)){continue;}

            if(run!=388621){continue;}

            // looping through all jets in each event
            for(unsigned int j=0; j<nref; j++){

                // jet pt cut
                if(jtpt[j]<ptcut){continue;}

                // checking jet veto map 
                Double_t vetomapval = hvetomap->GetBinContent(hvetomap->FindBin(jteta[j], jtphi[j]));
                if(vetomapval!=0){continue;}
               
                // jet ID requirements for leading jet
                // https://twiki.cern.ch/twiki/bin/view/CMS/JetID13p6TeV
                // multiplicity
                Int_t mult = jtPfCHM[j]+jtPfNHM[j]+jtPfCEM[j]+jtPfNEM[j]+jtPfMUM[j];
                // charged multiplicity
                Int_t mult_ch = jtPfCHM[j]+jtPfCEM[j]+jtPfMUM[j];
                // nuetral multiplicity
                Int_t mult_nu = jtPfNHM[j]+jtPfNEM[j];
                // suggested requirements by eta range
                if((TMath::Abs(jteta[j])<=2.6)&&((jtPfNHF[j]>=0.9)||(jtPfNEF[j]>=0.9)||(mult<=1)||(jtPfMUF[j]>=0.8)||(jtPfCHF[j]<=0.01)||(mult_ch<=0)||(jtPfCEF[j]>=0.8))){continue;}
                if(((TMath::Abs(jteta[j])>2.6)&&(TMath::Abs(jteta[j])<=2.7))&&((jtPfNHF[j]>=0.9)||(jtPfNEF[j]>=0.99)||(jtPfMUF[j]>=0.8)||(mult_ch<=0)||(jtPfCEF[j]>=0.8))){continue;}
                if(((TMath::Abs(jteta[j])>2.7)&&(TMath::Abs(jteta[j])<=3.0))&&((jtPfNEF[j]>=0.99)||(mult_nu<=1))){continue;}
                if(((TMath::Abs(jteta[j])>3.0)&&(TMath::Abs(jteta[j])<=5.0))&&((jtPfNHF[j]<=0.2)||(jtPfNEF[j]>=0.9)||(mult_nu<=10))){continue;}

                // if((jtPfCHF[j]>0.99)||(jtPfMUF[j]>0.8)){continue;}

                // filling histograms //

                // by eta
                for(unsigned int b=0; b<netabins; b++){
                    if((TMath::Abs(jteta[j])<etalo[b])||(TMath::Abs(jteta[j])>etahi[b])){continue;}

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

                    // by hibin
                    for(int hb=0; hb<nhiBin; hb++){
                        if((hiBin<hiBinlo[hb])||(hiBin>hiBinhi[hb])){continue;}

                        // jet momenta
                        hjetmom_hibin[0][b][hb]->Fill(rawpt[j]);
                        hjetmom_hibin[1][b][hb]->Fill(jtpt[j]);
                        hjetmom_hibin[2][b][hb]->Fill(jteta[j]);
                        hjetmom_hibin[3][b][hb]->Fill(jtphi[j]);
                        hjtetaphi_hibin[b][hb]->Fill(jteta[j], jtphi[j]);

                        // jet pf fractions
                        hjtPfF_hibin[0][b][hb]->Fill(jtPfCHF[j]);
                        hjtPfF_hibin[1][b][hb]->Fill(jtPfNHF[j]);
                        hjtPfF_hibin[2][b][hb]->Fill(jtPfCEF[j]);
                        hjtPfF_hibin[3][b][hb]->Fill(jtPfNEF[j]);
                        hjtPfF_hibin[4][b][hb]->Fill(jtPfMUF[j]);

                        // jet pf multiplicities
                        hjtPfM_hibin[0][b][hb]->Fill(jtPfCHM[j]);
                        hjtPfM_hibin[1][b][hb]->Fill(jtPfNHM[j]);
                        hjtPfM_hibin[2][b][hb]->Fill(jtPfCEM[j]);
                        hjtPfM_hibin[3][b][hb]->Fill(jtPfNEM[j]);
                        hjtPfM_hibin[4][b][hb]->Fill(jtPfMUM[j]);
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
    hppvF->Write();
    hnref->Write();


    // jet histograms by eta 
    for(unsigned int b=0; b<netabins; b++){
        dji->cd(); 

        // momenta
        for(int hj=0; hj<nmom; hj++){hjetmom_eta[hj][b]->Write();}
        hjtetaphi_eta[b]->Write();

        // fractions & multiplicities
        for(int hj=0; hj<nfrac; hj++){
            hjtPfF_eta[hj][b]->Write();
            hjtPfM_eta[hj][b]->Write();
        }

        // for each hibin
        djh->cd();
        for(int hb=0; hb<nhiBin; hb++){
    
            // momenta
            for(int hj=0; hj<nmom; hj++){hjetmom_hibin[hj][b][hb]->Write();}
            hjtetaphi_hibin[b][hb]->Write();

            // fractions & multiplicities
            for(int hj=0; hj<nfrac; hj++){
                hjtPfF_hibin[hj][b][hb]->Write();
                hjtPfM_hibin[hj][b][hb]->Write();
            }
        }
    }
    fo->Close();
}