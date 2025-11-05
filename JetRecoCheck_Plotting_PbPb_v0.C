#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TDirectory.h"
#include "TAxis.h"

#include "../../header_files/plotting_PbPb/JetCheck_PbPb_plotting.h"

void JetRecoCheck_Plotting_PbPb_v0_11_4_2025(){

    // getting rid of legends in hists in root file
    gStyle->SetOptStat(0);

    // reading input file
    // TString input = "../../root_files/11_4_2025/JetRecoCheck_2024PbPbMC_v0_11_4_2025.root";
    // TString input = "../../root_files/11_4_2025/JetRecoCheck_2024PbPbMC_v0_11_4_2025_id.root";
    // TString input = "../../root_files/11_4_2025/JetRecoCheck_2025PbPbMC_v0_11_4_2025_prepatch.root";
    // TString input = "../../root_files/11_4_2025/JetRecoCheck_2025PbPbMC_v0_11_4_2025_prepatch_id.root";
    TString input = "../../root_files/11_4_2025/JetRecoCheck_2025PbPbMC_v1_11_4_2025_postpatch.root";
    // TString input = "../../root_files/11_4_2025/JetRecoCheck_2025PbPbMC_v1_11_4_2025_postpatch_id.root";
    TFile *fi = TFile::Open(input,"read");
    cout<<"opened "<<input<<endl;

    // flags for saving files //

    // momenta
    int flag_mom = 0;
    int flag_ep = 1;
    // fractions 
    int flag_pf_frac = 0;
    //multiplicities
    int flag_pf_mult = 0;
    // overlays
    int flag_mom_ovr = 1;
    int flag_pf_frac_ovr = 1;
    int flag_pf_mult_ovr = 0;

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

    // strings of directory paths in input root file to histograms
    TString path_evt = "event/";
    TString path_eta = "jet_eta/";
    TString path_hibin = "jet_hibin/";
    TString path_trig = "jet_trig/";

    // getting histograms //

    // by eta
    for(unsigned int b=0; b<netabins; b++){

        // eta bin as a string
        TString sEtaBin = Form("_AbsEta_%.0f_to_%.0f",etalo[b]*10,etahi[b]*10);

        // momenta
        for(int hj=0; hj<nmom; hj++){
            TString htitle0 = path_eta+smom[hj]+sEtaBin;
            hjetmom_eta[hj][b] = (TH1F*) fi->Get(htitle0);
            if(!hjetmom_eta[hj][b]){cerr<<"ERROR: Could not find histogram '"<< htitle0<<"' in file"<<endl;}
        }

        TString htitle1 = path_eta+"hjtetaphi"+sEtaBin;
        hjtetaphi_eta[b] = (TH2F*) fi->Get(htitle1);
        if(!hjtetaphi_eta[b]){cerr<<"ERROR: Could not find histogram '"<< htitle1<<"' in file"<<endl;}

        // PF fractions & multiplicities
        for(int hj=0; hj<nfrac; hj++){

            TString htitle2 = path_eta+sfrac[hj]+sEtaBin;
            hjtPfF_eta[hj][b] = (TH1F*) fi->Get(htitle2);
            if(!hjtPfF_eta[hj][b]){cerr<<"ERROR: Could not find histogram '"<< htitle2<<"' in file"<<endl;}

            TString htitle3 = path_eta+smult[hj]+sEtaBin;
            hjtPfM_eta[hj][b] = (TH1F*) fi->Get(htitle3);
            if(!hjtPfM_eta[hj][b]){cerr<<"ERROR: Could not find histogram '"<< htitle3<<"' in file"<<endl;}
        }

        // by hiBin
        for(unsigned int hb=0; hb<nhiBin; hb++){

        // hibin bin as a string
        TString shiBin = Form("_hibin_%d_to_%d",hiBinlo[hb],hiBinhi[hb]);
        
            for(int hj=0; hj<nmom; hj++){
                TString htitle4 = path_hibin+smom[hj]+sEtaBin+shiBin;
                hjetmom_hibin[hj][b][hb] = (TH1F*) fi->Get(htitle4);
                if(!hjetmom_hibin[hj][b][hb]){cerr<<"ERROR: Could not find histogram '"<< htitle4<<"' in file"<<endl;}
            }

            TString htitle5 = path_hibin+"hjtetaphi"+sEtaBin+shiBin;
            hjtetaphi_hibin[b][hb] = (TH2F*) fi->Get(htitle5);
            if(!hjtetaphi_hibin[b][hb]){cerr<<"ERROR: Could not find histogram '"<< htitle5<<"' in file"<<endl;}

            for(int hj=0; hj<nfrac; hj++){

                TString htitle6 = path_hibin+sfrac[hj]+sEtaBin+shiBin;
                hjtPfF_hibin[hj][b][hb] = (TH1F*) fi->Get(htitle6);
                if(!hjtPfF_hibin[hj][b][hb]){cerr<<"ERROR: Could not find histogram '"<< htitle6<<"' in file"<<endl;}

                TString htitle7 = path_hibin+smult[hj]+sEtaBin+shiBin;
                hjtPfM_hibin[hj][b][hb] = (TH1F*) fi->Get(htitle7);
                if(!hjtPfM_hibin[hj][b][hb]){cerr<<"ERROR: Could not find histogram '"<< htitle7<<"' in file"<<endl;}
            }
        }
    }

    cout<<"got histograms"<<endl;

    // normalizing 1D jet histograms //

    // by eta
    for(unsigned int b=0; b<netabins; b++){

        // momenta 
        for(int hj=0; hj<nmom; hj++){
            Double_t a0 = hjetmom_eta[hj][b]->Integral();
            hjetmom_eta[hj][b]->Scale(1.0/a0);
        }

        // fractions and multiplicities
        for(int hj=0; hj<nfrac; hj++){
            Double_t a1 = hjtPfF_eta[hj][b]->Integral();
            Double_t b1 = hjtPfM_eta[hj][b]->Integral();
            hjtPfF_eta[hj][b]->Scale(1.0/a1);
            hjtPfM_eta[hj][b]->Scale(1.0/b1);
        }

        // by hiBin
        for(unsigned int hb=0; hb<nhiBin; hb++){

            for(int hj=0; hj<nmom; hj++){
                Double_t a2 = hjetmom_hibin[hj][b][hb]->Integral();
                hjetmom_hibin[hj][b][hb]->Scale(1.0/a2);
            }

            for(int hj=0; hj<nfrac; hj++){
                Double_t a3 = hjtPfF_hibin[hj][b][hb]->Integral();
                Double_t b3 = hjtPfM_hibin[hj][b][hb]->Integral();
                hjtPfF_hibin[hj][b][hb]->Scale(1.0/a3);
                hjtPfM_hibin[hj][b][hb]->Scale(1.0/b3);
            }
        }
    }
        
    cout<<"histograms normalized"<<endl;
    
    // declaring strings //

    // histogram names
    TString htitles_mom_name[nmom] = {"raw_jet_pt", "jet_pt", "jet_eta", "jet_phi"};
    TString htitles_frac_name[nfrac] = {"Charged_Hadron_Fraction", "Neutral_Hadron_Fraction", "Charged_Electromagnetic_Fraction", "Neutral_Electromagnetic_Fraction", "Muon_Fraction"};
    TString htitles_mult_name[nmult] = {"Charged_Hadron_Multiplicity", "Neutral_Hadron_Multiplicity", "Charged_Electromagnetic_Multiplicity", "Neutral_Electromagnetic_Multiplicity", "Muon_Multiplicity"};
    
    // x axis titles
    TString htitles_mom_xaxis[nmom] = {"p_{T}^{raw}", "p_{T}^{jet}", "#eta^{jet}", "#phi^{jet}"};
    TString htitles_frac_xaxis[nfrac] = {"CHF", "NHF", "CEF", "NEF", "MUF"};
    TString htitles_mult_xaxis[nmult] = {"CHM", "NHM", "CEM", "NEM", "MUM"};

    // saving non-overlay histograms //

    // by eta
    for(unsigned int b=0; b<netabins; b++){
        TString sEtaBin = Form("_AbsEta_%.0f_to_%.0f",etalo[b]*10,etahi[b]*10);

        // momenta 
        for(int hj=0; hj<nmom; hj++){
            if(flag_mom==1){save_h1f_1(hjetmom_eta[hj][b], htitles_mom_xaxis[hj], "", htitles_mom_name[hj]+sEtaBin, path_mom);}
        }
        if(flag_ep==1){save_2d_byeta(hjtetaphi_eta, b, htitles_mom_xaxis[2], htitles_mom_xaxis[3], "Inclusive", "jet_eta_phi"+sEtaBin, path_ep);}

        // PF fractions & multiplicities
        for(int hj=0; hj<nfrac; hj++){
            if(flag_pf_frac==1){save_h1f_1(hjtPfF_eta[hj][b], htitles_frac_xaxis[hj], "", htitles_frac_name[hj]+sEtaBin, path_frac);}
            if(flag_pf_mult==1){save_h1f_1(hjtPfM_eta[hj][b], htitles_mult_xaxis[hj], "", htitles_mult_name[hj]+sEtaBin, path_mult);}
        }

        // by hiBin
        for(unsigned int hb=0; hb<nhiBin; hb++){
            TString shiBin = Form("_hibin_%d_to_%d",hiBinlo[hb],hiBinhi[hb]);
            
            for(int hj=0; hj<nmom; hj++){
                if(flag_mom==1){save_h1f_1(hjetmom_hibin[hj][b][hb], htitles_mom_xaxis[hj], "", htitles_mom_name[hj]+sEtaBin+shiBin, path_mom);}
            }
            if(flag_ep==1){save_2d_byhibin(hjtetaphi_hibin, b, hb, htitles_mom_xaxis[2], htitles_mom_xaxis[3], shiBin, "jet_eta_phi"+sEtaBin+shiBin, path_ep);}

            for(int hj=0; hj<nfrac; hj++){
                if(flag_pf_frac==1){save_h1f_1(hjtPfF_hibin[hj][b][hb], htitles_frac_xaxis[hj], "", htitles_frac_name[hj]+sEtaBin+shiBin, path_frac);}
                if(flag_pf_mult==1){save_h1f_1(hjtPfM_hibin[hj][b][hb], htitles_mult_xaxis[hj], "", htitles_mult_name[hj]+sEtaBin+shiBin, path_mult);}
            }
        }

        // saving overlay histograms //

        for(int hj=0; hj<nmom; hj++){
            if(flag_mom_ovr==1){save_mom_overlay(hjetmom_hibin, b, hj, htitles_mom_xaxis[hj], "", htitles_mom_name[hj]+sEtaBin+"_overlay", path_ovr_mom);}
        }
        for(int hj=0; hj<nfrac; hj++){
            if(flag_pf_frac_ovr==1){save_pf_overlay(hjtPfF_hibin, b, hj, htitles_frac_xaxis[hj], "", htitles_frac_name[hj]+sEtaBin+"_overlay", path_ovr_frac);}
            if(flag_pf_mult_ovr==1){save_pf_overlay(hjtPfM_hibin, b, hj, htitles_mult_xaxis[hj], "", htitles_mult_name[hj]+sEtaBin+"_overlay", path_ovr_mult);}
        }
    }
    fi->Close();
}

        