#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TDirectory.h"
#include "TAxis.h"

#include "../header_files/JetCheck_lowPUpp_plotting.h"
// #include "../header_files/JetCheck_lowPUpp_binning.h"

void JetRecoCheck_Plotting_lowPUpp_v0(){

    // getting rid of legends in hists in root file
    gStyle->SetOptStat(0);

    // reading input file
    TString input = "../root_files/10_30_2025_lowPUpp/JetRecoCheck_lowPUpp_v2_10_30_2025.root";
    // TString input = "../root_files/10_30_2025_lowPUpp/JetRecoCheck_lowPUpp_v2_10_30_2025_jetid_vetomap.root";
    TFile *fi = TFile::Open(input,"read");
    cout<<"opened "<<input<<endl;

    // flags for saving files //

    // event
    int flag_evt = 0;
    // momenta
    int flag_mom = 0;
    int flag_etaphi = 0;
    // fractions and multiplicities
    int flag_pf = 0;
    // overlays
    int flag_mom_ovr = 1;
    int flag_pf_ovr = 0;

    // getting event info histograms 
    TH1F *hvz_unpassed = (TH1F*) fi->Get("event/hvz_unpassed");
    TH1F *hvz = (TH1F*) fi->Get("event/hvz");
    TH1I *hnref = (TH1I*) fi->Get("event/hnref");
    TH1I *hppvF = (TH1I*) fi->Get("event/hppvF");

    // declaring jet histograms by eta bin //

    // momenta
    TH1F *hjetmom_eta[nmom][netabins];
    TH2F *hjtetaphi_eta[netabins];

    // PF fractions & multiplicities
    TH1F *hjtPfF_eta[nfrac][netabins];
    TH1F *hjtPfM_eta[nmult][netabins];

    // declaring jet histograms by eta for triggers //

    // momenta
    TH1F *hjetmom_trig[nmom][netabins][nTrigs];
    TH2F *hjtetaphi_trig[netabins][nTrigs];

    // PF fractions & multiplicities
    TH1F *hjtPfF_trig[nfrac][netabins][nTrigs];
    TH1F *hjtPfM_trig[nmult][netabins][nTrigs];

    // getting jet histograms by eta //
    for(unsigned int b=0; b<netabins; b++){

        // eta bin as a string
        TString sEtaBin = Form("_AbsEta_%.0f_to_%.0f",etalo[b]*10,etahi[b]*10);

        // momenta
        for(int hj=0; hj<nmom; hj++){
            TString htitle0 = "jet_eta/"+smom[hj]+sEtaBin;
            hjetmom_eta[hj][b] = (TH1F*) fi->Get(htitle0);
            if(!hjetmom_eta[hj][b]){cerr<<"ERROR: Could not find histogram '"<< htitle0<<"' in file"<<endl;}
        }
        TString htitle1 = "jet_eta/hjtetaphi"+sEtaBin;
        hjtetaphi_eta[b] = (TH2F*) fi->Get(htitle1);
        if(!hjtetaphi_eta[b]){cerr<<"ERROR: Could not find histogram '"<< htitle1<<"' in file"<<endl;}

        // PF fractions & multiplicities
        for(int hj=0; hj<nfrac; hj++){

            TString htitle2 = "jet_eta/"+sfrac[hj]+sEtaBin;
            hjtPfF_eta[hj][b] = (TH1F*) fi->Get(htitle2);
            if(!hjtPfF_eta[hj][b]){cerr<<"ERROR: Could not find histogram '"<< htitle2<<"' in file"<<endl;}

            TString htitle3 = "jet_eta/"+smult[hj]+sEtaBin;
            hjtPfM_eta[hj][b] = (TH1F*) fi->Get(htitle3);
            if(!hjtPfM_eta[hj][b]){cerr<<"ERROR: Could not find histogram '"<< htitle3<<"' in file"<<endl;}
        }

        // for triggers
        for(unsigned int tr=0; tr<nTrigs; tr++){

            // momenta
            for(int hj=0; hj<nmom; hj++){
                TString htitle4 = "jet_trig/"+smom[hj]+sEtaBin+sTrigs_short[tr];
                hjetmom_trig[hj][b][tr] = (TH1F*) fi->Get(htitle4);
                if(!hjetmom_trig[hj][b][tr]){cerr<<"ERROR: Could not find histogram '"<< htitle4<<"' in file"<<endl;}
            }
            TString htitle5 = "jet_trig/hjtetaphi"+sEtaBin+sTrigs_short[tr];
            hjtetaphi_trig[b][tr] = (TH2F*) fi->Get(htitle5);
                if(!hjtetaphi_trig[b][tr]){cerr<<"ERROR: Could not find histogram '"<< htitle5<<"' in file"<<endl;}

            // PF fractions & multiplicities
            for(int hj=0; hj<nfrac; hj++){

                TString htitle6 = "jet_trig/"+sfrac[hj]+sEtaBin+sTrigs_short[tr];
                hjtPfF_trig[hj][b][tr] = (TH1F*) fi->Get(htitle6);
                if(!hjtPfF_trig[hj][b][tr]){cerr<<"ERROR: Could not find histogram '"<< htitle6<<"' in file"<<endl;}

                TString htitle7 = "jet_trig/"+smult[hj]+sEtaBin+sTrigs_short[tr];
                hjtPfM_trig[hj][b][tr] = (TH1F*) fi->Get(htitle7);
                if(!hjtPfM_trig[hj][b][tr]){cerr<<"ERROR: Could not find histogram '"<< htitle7<<"' in file"<<endl;}
            }
        }
    }

    cout<<"got jet histograms by eta and trig"<<endl;

    // normalizing all 1D jet histograms //

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

        // for triggers
        for(unsigned int tr=0; tr<nTrigs; tr++){

            // momenta 
            for(int hj=0; hj<nmom; hj++){
                Double_t a2 = hjetmom_trig[hj][b][tr]->Integral();
                hjetmom_trig[hj][b][tr]->Scale(1.0/a2);
            }

            // fractions and multiplicities
            for(int hj=0; hj<nfrac; hj++){
                Double_t a3 = hjtPfF_trig[hj][b][tr]->Integral();
                Double_t b3 = hjtPfM_trig[hj][b][tr]->Integral();
                hjtPfF_trig[hj][b][tr]->Scale(1.0/a3);
                hjtPfM_trig[hj][b][tr]->Scale(1.0/b3);
            }
        }
    }
        
    cout<<"histograms have been normalized"<<endl;
    
    // declaring strings //

    // histogram names
    TString htitles_mom_name[nmom] = {"raw_jet_pt", "jet_pt", "jet_eta", "jet_phi"};
    TString htitles_frac_name[nfrac] = {"Charged Hadron Fraction", "Neutral Hadron Fraction", "Charged Electromagnetic Fraction", "Neutral Electromagnetic Fraction", "Muon Fraction"};
    TString htitles_mult_name[nmult] = {"Charged Hadron Multiplicity", "Neutral Hadron Multiplicity", "Charged Electromagnetic Multiplicity", "Neutral Electromagnetic Multiplicity", "Muon Multiplicity"};
    
    // x axis titles
    TString htitles_mom_xaxis[nmom] = {"p_{T}^{raw}", "p_{T}^{jet}", "#eta^{jet}", "#phi^{jet}"};
    TString htitles_frac_xaxis[nfrac] = {"CHF", "NHF", "CEF", "NEF", "MUF"};
    TString htitles_mult_xaxis[nmult] = {"CHM", "NHM", "CEM", "NEM", "MUM"};

    // file paths
    TString path_evt = "../plots/event/";
    TString path_mom = "../plots/momenta/";
    TString path_frac = "../plots/fractions/";
    TString path_mult = "../plots/multiplicity/";
    TString path_over = "../plots/overlays/";;
    
    // saving event histograms //
    if(flag_evt==1){
        save_h1f_1(hvz_unpassed, "v_{z}^{all events}", "", "hvz_unpassed", path_evt);
        save_h1f_1(hvz, "v_{z}^{passed events}", "", "hvz", path_evt);
        save_h1i_1(hnref, "nref", "", "nref", path_evt);
        save_h1i_1(hppvF, "primary_vertex_filter", "", "primary_vertex_filter", path_evt);
        cout<<"saved event histograms"<<endl;
    }
    

    // saving jet histograms //
    for(unsigned int b=0; b<netabins; b++){
        TString sEtaBin = Form("_AbsEta_%.0f_to_%.0f",etalo[b]*10,etahi[b]*10);

        // momenta 
        for(int hj=0; hj<nmom; hj++){
            if(flag_mom==0){continue;}
            save_h1f_1(hjetmom_eta[hj][b], htitles_mom_xaxis[hj], "", htitles_mom_name[hj]+sEtaBin, path_mom);
        }
        if(flag_etaphi==1){save_2d_bytrig1(hjtetaphi_eta, b, htitles_mom_xaxis[2], htitles_mom_xaxis[3], "Not Triggered Jets", "jet_eta_phi"+sEtaBin, path_mom);}

        // PF fractions & multiplicities
        for(int hj=0; hj<nfrac; hj++){
            if(flag_pf==0){continue;}
            save_h1f_1(hjtPfF_eta[hj][b], htitles_frac_xaxis[hj], "", htitles_frac_name[hj]+sEtaBin, path_frac);
            save_h1f_1(hjtPfM_eta[hj][b], htitles_mult_xaxis[hj], "", htitles_mult_name[hj]+sEtaBin, path_mult);
        }

        // for triggers
        for(unsigned int tr=0; tr<nTrigs; tr++){

            // momenta
            for(int hj=0; hj<nmom; hj++){
                if(flag_mom==0){continue;}
                save_h1f_1(hjetmom_trig[hj][b][tr], htitles_mom_xaxis[hj], "", htitles_mom_name[hj]+sEtaBin+sTrigs_short[tr], path_mom);
            }
            if(flag_etaphi==1){save_2d_bytrig2(hjtetaphi_trig, b, tr, htitles_mom_xaxis[2], htitles_mom_xaxis[3], sTrigs[tr], "jet_eta_phi"+sEtaBin+sTrigs_short[tr], path_mom);}

            // PF fractions & multiplicities
            for(int hj=0; hj<nfrac; hj++){
                if(flag_pf==0){continue;}
                save_h1f_1(hjtPfF_trig[hj][b][tr], htitles_frac_xaxis[hj], "", htitles_frac_name[hj]+sEtaBin+sTrigs_short[tr], path_frac);
                save_h1f_1(hjtPfM_trig[hj][b][tr], htitles_mult_xaxis[hj], "", htitles_mult_name[hj]+sEtaBin+sTrigs_short[tr], path_mult);
            }
        }
    }

    // saving overlay plots for triggers of jet histograms//
    for(unsigned int b=0; b<netabins; b++){
        TString sEtaBin = Form("_AbsEta_%.0f_to_%.0f",etalo[b]*10,etahi[b]*10);
        TString st = "trig_";

        // momenta
        for(int hj=0; hj<nmom; hj++){
            if(flag_mom_ovr==0){continue;}
            save_mom_overlay(hjetmom_trig, b, hj, htitles_mom_xaxis[hj], "", st+htitles_mom_name[hj]+sEtaBin, path_over);
        }

        // PF fractions & multiplicities
        for(int hj=0; hj<nfrac; hj++){
            if(flag_pf_ovr==0){continue;}
            save_pf_overlay(hjtPfF_trig, b, hj, htitles_frac_xaxis[hj], "", st+htitles_frac_name[hj]+sEtaBin, path_over);
            save_pf_overlay(hjtPfM_trig, b, hj, htitles_mult_xaxis[hj], "", st+htitles_mult_name[hj]+sEtaBin, path_over);
        }
    }
    fi->Close();
}

        