#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TDirectory.h"
#include "TAxis.h"

#include "JetCheck_PbPb_plotting.h"

void JetRecoCheck_Plotting_PbPb_v0_11_11_2025(){

    // getting rid of legends in hists in root file
    gStyle->SetOptStat(0);

    // reading input file
    TString input0 = "11_12_2025/root_files/RawPrime_Replay_JetChecks_ptcut40.root";
    TString input1 = "11_12_2025/root_files/RawPrime_OG_JetChecks_ptcut40.root";
    TFile *fi0 = TFile::Open(input0,"read");
    cout<<"opened "<<input0<<endl;
    TFile *fi1 = TFile::Open(input1,"read");
    cout<<"opened "<<input1<<endl;

    // flags for saving files //
    int flag_mom = 0;
    int flag_pf_frac = 0;
    int flag_pf_mult = 0;
    int flag_pf_mult_ovr = 0;
    int flag_momr = 0;
    int flag_pf_fracr = 0;
    int flag_pf_multr = 0;
    int flag_pf_multr_ovr = 0;

    int flag_ep = 1;
    // int flag_mom_ovr = 1;
    // int flag_pf_frac_ovr = 1;
    // int flag_epr = 1;
    // int flag_momr_ovr = 1;
    // int flag_pf_fracr_ovr = 1;

    // int flag_ep = 0;
    int flag_pf_fracr_ovr = 0;
    int flag_momr_ovr = 0;
    int flag_epr = 0;
    int flag_mom_ovr = 0;
    int flag_pf_frac_ovr = 0;


    // declaring histograms //

    /// by eta
    // momenta
    TH1F *hjetmom_eta[2][nmom][netabins];
    TH2F *hjtetaphi_eta[2][netabins];
    // PF fractions & multiplicities
    TH1F *hjtPfF_eta[2][nfrac][netabins];
    TH1F *hjtPfM_eta[2][nmult][netabins];

    /// by hibin
    TH1F *hjetmom_hibin[2][nmom][netabins][nhiBin];
    TH2F *hjtetaphi_hibin[2][netabins][nhiBin];
    TH1F *hjtPfF_hibin[2][nfrac][netabins][nhiBin];
    TH1F *hjtPfM_hibin[2][nmult][netabins][nhiBin];

    // strings of directory paths in input root file to histograms
    TString path_evt = "event/";
    TString path_inc = "jet_inclusive/";
    TString path_hibin = "jet_hibin/";

    // getting histograms //

    // by eta
    for(unsigned int b=0; b<netabins; b++){

        // momenta
        for(int hj=0; hj<nmom; hj++){
            TString htitle0 = path_inc+smom[hj]+htitles_byeta[b];
            hjetmom_eta[0][hj][b] = (TH1F*) fi0->Get(htitle0);
            hjetmom_eta[1][hj][b] = (TH1F*) fi1->Get(htitle0);
            if(!hjetmom_eta[0][hj][b]){cerr<<"ERROR: Could not find histogram '"<< htitle0<<"' in files"<<endl;}
        }

        TString htitle1 = path_inc+"hjtetaphi"+htitles_byeta[b];
        hjtetaphi_eta[0][b] = (TH2F*) fi0->Get(htitle1);
        hjtetaphi_eta[1][b] = (TH2F*) fi1->Get(htitle1);
        if(!hjtetaphi_eta[0][b]){cerr<<"ERROR: Could not find histogram '"<< htitle1<<"' in files"<<endl;}

        // PF fractions & multiplicities
        for(int hj=0; hj<nfrac; hj++){

            TString htitle2 = path_inc+sfrac[hj]+htitles_byeta[b];
            hjtPfF_eta[0][hj][b] = (TH1F*) fi0->Get(htitle2);
            hjtPfF_eta[1][hj][b] = (TH1F*) fi1->Get(htitle2);
            if(!hjtPfF_eta[0][hj][b]){cerr<<"ERROR: Could not find histogram '"<< htitle2<<"' in files"<<endl;}

            TString htitle3 = path_inc+smult[hj]+htitles_byeta[b];
            hjtPfM_eta[0][hj][b] = (TH1F*) fi0->Get(htitle3);
            hjtPfM_eta[1][hj][b] = (TH1F*) fi1->Get(htitle3);
            if(!hjtPfM_eta[0][hj][b]){cerr<<"ERROR: Could not find histogram '"<< htitle3<<"' in files"<<endl;}
        }

        // by hiBin
        for(unsigned int hb=0; hb<nhiBin; hb++){
        
            for(int hj=0; hj<nmom; hj++){
                TString htitle4 = path_hibin+smom[hj]+htitles_byeta[b]+htitles_byhibin[hb];
                hjetmom_hibin[0][hj][b][hb] = (TH1F*) fi0->Get(htitle4);
                hjetmom_hibin[1][hj][b][hb] = (TH1F*) fi1->Get(htitle4);
                if(!hjetmom_hibin[0][hj][b][hb]){cerr<<"ERROR: Could not find histogram '"<< htitle4<<"' in files"<<endl;}
            }

            TString htitle5 = path_hibin+"hjtetaphi"+htitles_byeta[b]+htitles_byhibin[hb];
            hjtetaphi_hibin[0][b][hb] = (TH2F*) fi0->Get(htitle5);
            hjtetaphi_hibin[1][b][hb] = (TH2F*) fi1->Get(htitle5);
            if(!hjtetaphi_hibin[0][b][hb]){cerr<<"ERROR: Could not find histogram '"<< htitle5<<"' in files"<<endl;}

            for(int hj=0; hj<nfrac; hj++){

                TString htitle6 = path_hibin+sfrac[hj]+htitles_byeta[b]+htitles_byhibin[hb];
                hjtPfF_hibin[0][hj][b][hb] = (TH1F*) fi0->Get(htitle6);
                hjtPfF_hibin[1][hj][b][hb] = (TH1F*) fi1->Get(htitle6);
                if(!hjtPfF_hibin[0][hj][b][hb]){cerr<<"ERROR: Could not find histogram '"<< htitle6<<"' in files"<<endl;}

                TString htitle7 = path_hibin+smult[hj]+htitles_byeta[b]+htitles_byhibin[hb];
                hjtPfM_hibin[0][hj][b][hb] = (TH1F*) fi0->Get(htitle7);
                hjtPfM_hibin[1][hj][b][hb] = (TH1F*) fi1->Get(htitle7);
                if(!hjtPfM_hibin[0][hj][b][hb]){cerr<<"ERROR: Could not find histogram '"<< htitle7<<"' in files"<<endl;}
            }
        }
    }

    cout<<"got histograms"<<endl;

    // normalizing jet histograms //

    // for hists from both files
    for(int i=0; i<2; i++){
        // by eta
        for(unsigned int b=0; b<netabins; b++){

            // momenta 
            for(int hj=0; hj<nmom; hj++){
                Double_t a0 = hjetmom_eta[i][hj][b]->Integral();
                hjetmom_eta[i][hj][b]->Scale(1.0/a0);
            }

            // eta phi map
            Double_t a1 = hjtetaphi_eta[i][b]->Integral();
            hjtetaphi_eta[i][b]->Scale(1.0/a1);

            // fractions and multiplicities
            for(int hj=0; hj<nfrac; hj++){
                Double_t a2 = hjtPfF_eta[i][hj][b]->Integral();
                hjtPfF_eta[i][hj][b]->Scale(1.0/a2);

                Double_t a3 = hjtPfM_eta[i][hj][b]->Integral();
                hjtPfM_eta[i][hj][b]->Scale(1.0/a3);
            }

            // by hiBin
            for(unsigned int hb=0; hb<nhiBin; hb++){

                for(int hj=0; hj<nmom; hj++){
                    Double_t a4 = hjetmom_hibin[i][hj][b][hb]->Integral();
                    hjetmom_hibin[i][hj][b][hb]->Scale(1.0/a4);
                }
                Double_t a5 = hjtetaphi_hibin[i][b][hb]->Integral();
                hjtetaphi_hibin[i][b][hb]->Scale(1.0/a5);

                for(int hj=0; hj<nfrac; hj++){
                    Double_t a6 = hjtPfF_hibin[i][hj][b][hb]->Integral();
                    hjtPfF_hibin[i][hj][b][hb]->Scale(1.0/a6);

                    Double_t a7 = hjtPfM_hibin[i][hj][b][hb]->Integral();
                    hjtPfM_hibin[i][hj][b][hb]->Scale(1.0/a7);
                }
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
            if(flag_mom==1){save_h1f_1(hjetmom_eta[0][hj][b], htitles_mom_xaxis[hj], "", htitles_mom_name[hj]+sEtaBin, path_mom);}
        }
        if(flag_ep==1){save_2d_byeta(hjtetaphi_eta, b, htitles_mom_xaxis[2], htitles_mom_xaxis[3], "Inclusive", "jet_eta_phi"+sEtaBin, path_ep);}

        // PF fractions & multiplicities
        for(int hj=0; hj<nfrac; hj++){
            if(flag_pf_frac==1){save_h1f_1(hjtPfF_eta[0][hj][b], htitles_frac_xaxis[hj], "", htitles_frac_name[hj]+sEtaBin, path_frac);}
            if(flag_pf_mult==1){save_h1f_1(hjtPfM_eta[0][hj][b], htitles_mult_xaxis[hj], "", htitles_mult_name[hj]+sEtaBin, path_mult);}
        }

        // by hiBin
        for(unsigned int hb=0; hb<nhiBin; hb++){
            TString shiBin = Form("_hibin_%d_to_%d",hiBinlo[hb],hiBinhi[hb]);
            
            for(int hj=0; hj<nmom; hj++){
                if(flag_mom==1){save_h1f_1(hjetmom_hibin[0][hj][b][hb], htitles_mom_xaxis[hj], "", htitles_mom_name[hj]+sEtaBin+shiBin, path_mom);}
            }
            if(flag_ep==1){save_2d_byhibin(hjtetaphi_hibin, b, hb, htitles_mom_xaxis[2], htitles_mom_xaxis[3], shiBins[hb], "jet_eta_phi"+sEtaBin+shiBin, path_ep);}

            for(int hj=0; hj<nfrac; hj++){
                if(flag_pf_frac==1){save_h1f_1(hjtPfF_hibin[0][hj][b][hb], htitles_frac_xaxis[hj], "", htitles_frac_name[hj]+sEtaBin+shiBin, path_frac);}
                if(flag_pf_mult==1){save_h1f_1(hjtPfM_hibin[0][hj][b][hb], htitles_mult_xaxis[hj], "", htitles_mult_name[hj]+sEtaBin+shiBin, path_mult);}
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

    // making ratio histograms //

    // declaring ratio hists

    // by eta
    TH1F *hjetmom_eta_ratio[nmom][netabins];
    TH2F *hjtetaphi_eta_ratio[netabins];
    TH1F *hjtPfF_eta_ratio[nfrac][netabins];
    TH1F *hjtPfM_eta_ratio[nmult][netabins];

    // by hibin
    TH1F *hjetmom_hibin_ratio[nmom][netabins][nhiBin];
    TH2F *hjtetaphi_hibin_ratio[netabins][nhiBin];
    TH1F *hjtPfF_hibin_ratio[nfrac][netabins][nhiBin];
    TH1F *hjtPfM_hibin_ratio[nmult][netabins][nhiBin];

    // making ratios with divide function
    
    for(unsigned int b=0; b<netabins; b++){
        for(int hj=0; hj<nmom; hj++){
            hjetmom_eta_ratio[hj][b] = (TH1F*)hjetmom_eta[0][hj][b]->Clone();
            hjetmom_eta_ratio[hj][b]->Divide(hjetmom_eta[0][hj][b],hjetmom_eta[1][hj][b],1,1,"");
        }
        hjtetaphi_eta_ratio[b] = (TH2F*)hjtetaphi_eta[0][b]->Clone();
        hjtetaphi_eta_ratio[b]->Divide(hjtetaphi_eta[0][b],hjtetaphi_eta[1][b],1,1,"");
        for(int hj=0; hj<nfrac; hj++){
            hjtPfF_eta_ratio[hj][b] = (TH1F*)hjtPfF_eta[0][hj][b]->Clone();
            hjtPfF_eta_ratio[hj][b]->Divide(hjtPfF_eta[0][hj][b],hjtPfF_eta[1][hj][b],1,1,"");
            hjtPfM_eta_ratio[hj][b] = (TH1F*)hjtPfM_eta[0][hj][b]->Clone();
            hjtPfM_eta_ratio[hj][b]->Divide(hjtPfM_eta[0][hj][b],hjtPfM_eta[1][hj][b],1,1,"");
        }
        for(unsigned int hb=0; hb<nhiBin; hb++){
            for(int hj=0; hj<nmom; hj++){
                hjetmom_hibin_ratio[hj][b][hb] = (TH1F*)hjetmom_hibin[0][hj][b][hb]->Clone();
                hjetmom_hibin_ratio[hj][b][hb]->Divide(hjetmom_hibin[0][hj][b][hb],hjetmom_hibin[1][hj][b][hb],1,1,"");
            }
            hjtetaphi_hibin_ratio[b][hb] = (TH2F*)hjtetaphi_hibin[0][b][hb]->Clone();
            hjtetaphi_hibin_ratio[b][hb]->Divide(hjtetaphi_hibin[0][b][hb],hjtetaphi_hibin[1][b][hb],1,1,"");
            for(int hj=0; hj<nfrac; hj++){
                hjtPfF_hibin_ratio[hj][b][hb] = (TH1F*)hjtPfF_hibin[0][hj][b][hb]->Clone();
                hjtPfF_hibin_ratio[hj][b][hb]->Divide(hjtPfF_hibin[0][hj][b][hb],hjtPfF_hibin[1][hj][b][hb],1,1,"");
                hjtPfM_hibin_ratio[hj][b][hb] = (TH1F*)hjtPfM_hibin[0][hj][b][hb]->Clone();
                hjtPfM_hibin_ratio[hj][b][hb]->Divide(hjtPfM_hibin[0][hj][b][hb],hjtPfM_hibin[1][hj][b][hb],1,1,"");
            }
        }
    }

    // saving ratio histograms //
    
    for(unsigned int b=0; b<netabins; b++){
        TString sEtaBin = Form("_AbsEta_%.0f_to_%.0f",etalo[b]*10,etahi[b]*10);
        for(int hj=0; hj<nmom; hj++){
            if(flag_momr==1){save_h1f_1(hjetmom_eta_ratio[hj][b], htitles_mom_xaxis[hj], "", htitles_mom_name[hj]+sEtaBin, pathr_mom);}
        }
        if(flag_ep==1){save_2dr_byeta(hjtetaphi_eta_ratio, b, htitles_mom_xaxis[2], htitles_mom_xaxis[3], "Inclusive", "jet_eta_phi"+sEtaBin, pathr_ep);}
        for(int hj=0; hj<nfrac; hj++){
            if(flag_pf_fracr==1){save_h1f_1(hjtPfF_eta_ratio[hj][b], htitles_frac_xaxis[hj], "", htitles_frac_name[hj]+sEtaBin, pathr_frac);}
            if(flag_pf_multr==1){save_h1f_1(hjtPfM_eta_ratio[hj][b], htitles_mult_xaxis[hj], "", htitles_mult_name[hj]+sEtaBin, pathr_mult);}
        }
        for(unsigned int hb=0; hb<nhiBin; hb++){
            TString shiBin = Form("_hibin_%d_to_%d",hiBinlo[hb],hiBinhi[hb]);
            for(int hj=0; hj<nmom; hj++){
                if(flag_momr==1){save_h1f_1(hjetmom_hibin_ratio[hj][b][hb], htitles_mom_xaxis[hj], "", htitles_mom_name[hj]+sEtaBin+shiBin, pathr_mom);}
            }
            if(flag_ep==1){save_2dr_byhibin(hjtetaphi_hibin_ratio, b, hb, htitles_mom_xaxis[2], htitles_mom_xaxis[3], shiBins[hb], "jet_eta_phi"+sEtaBin+shiBin, pathr_ep);}
            for(int hj=0; hj<nfrac; hj++){
                if(flag_pf_fracr==1){save_h1f_1(hjtPfF_hibin_ratio[hj][b][hb], htitles_frac_xaxis[hj], "", htitles_frac_name[hj]+sEtaBin+shiBin, pathr_frac);}
                if(flag_pf_multr==1){save_h1f_1(hjtPfM_hibin_ratio[hj][b][hb], htitles_mult_xaxis[hj], "", htitles_mult_name[hj]+sEtaBin+shiBin, pathr_mult);}
            }
        }
        for(int hj=0; hj<nmom; hj++){
            if(flag_momr_ovr==1){save_momr_overlay(hjetmom_hibin_ratio, b, hj, htitles_mom_xaxis[hj], "", htitles_mom_name[hj]+sEtaBin+"_overlay", pathr_ovr_mom);}
        }
        for(int hj=0; hj<nfrac; hj++){
            if(flag_pf_fracr_ovr==1){save_pfr_overlay(hjtPfF_hibin_ratio, b, hj, htitles_frac_xaxis[hj], "", htitles_frac_name[hj]+sEtaBin+"_overlay", pathr_ovr_frac);}
            if(flag_pf_multr_ovr==1){save_pfr_overlay(hjtPfM_hibin_ratio, b, hj, htitles_mult_xaxis[hj], "", htitles_mult_name[hj]+sEtaBin+"_overlay", pathr_ovr_mult);}
        }
    }
    fi0->Close();
    fi1->Close();
}

        