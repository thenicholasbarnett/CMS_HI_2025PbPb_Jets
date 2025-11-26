#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TDirectory.h"
#include "TAxis.h"

#include "header_files/JetCheck_PbPb_plotting.h"

void JetCheck_Plotting_PbPb(TString input_num, TString input_denom){

    // getting rid of legends in hists in root file
    gStyle->SetOptStat(0);

    // reading input files
    TFile *fi0 = TFile::Open(input_num,"read");
    cout<<"opened "<<input_num<<endl;
    TFile *fi1 = TFile::Open(input_denom,"read");
    cout<<"opened "<<input_denom<<endl;

    // flags for saving files //
    int flag_mom = 0;
    int flag_pf_frac = 0;
    int flag_momr = 0;
    int flag_pf_fracr = 0;

    int flag_ep = 1;
    int flag_mom_ovr = 1;
    int flag_pf_frac_ovr = 1;
    int flag_epr = 1;
    int flag_momr_ovr = 1;
    int flag_pf_fracr_ovr = 1;

    // int flag_ep = 0;
    // int flag_pf_fracr_ovr = 0;
    // int flag_momr_ovr = 0;
    // int flag_epr = 0;
    // int flag_mom_ovr = 0;
    // int flag_pf_frac_ovr = 0;


    // declaring histograms //

    /// by eta
    // momenta
    TH1F *hjetmom_eta[2][nmom][nptcuts][netabins];
    TH2F *hjtetaphi_eta[2][nptcuts][netabins];
    // PF fractions
    TH1F *hjtPfF_eta[2][nfrac][nptcuts][netabins];
    /// by hibin
    TH1F *hjetmom_hibin[2][nmom][nptcuts][netabins][nhiBin];
    TH2F *hjtetaphi_hibin[2][nptcuts][netabins][nhiBin];
    TH1F *hjtPfF_hibin[2][nfrac][nptcuts][netabins][nhiBin];

    // strings of directory paths in input root file to histograms
    TString path_evt = "event/";
    TString path_inc = "jet_inclusive/";
    TString path_hibin = "jet_hibin/";

    // getting histograms //
    TString hname;

    // by pt cut
    for(unsigned int p=0; p<nptcuts; p++){
        // by eta
        for(unsigned int b=0; b<netabins; b++){
            // momenta
            for(int hj=0; hj<nmom; hj++){
                hname = path_inc+smom[hj]+htitles_byptcut[p]+htitles_byeta[b];
                hjetmom_eta[0][hj][p][b] = (TH1F*) fi0->Get(hname);
                hjetmom_eta[1][hj][p][b] = (TH1F*) fi1->Get(hname);
                if(!hjetmom_eta[0][hj][p][b]){cerr<<"ERROR: Could not find histogram '"<< hname<<"' in files"<<endl;}
            }
            hname = path_inc+ep+htitles_byptcut[p]+htitles_byeta[b];
            hjtetaphi_eta[0][p][b] = (TH2F*) fi0->Get(hname);
            hjtetaphi_eta[1][p][b] = (TH2F*) fi1->Get(hname);
            if(!hjtetaphi_eta[0][p][b]){cerr<<"ERROR: Could not find histogram '"<< hname<<"' in files"<<endl;}
            // PF fractions
            for(int hj=0; hj<nfrac; hj++){
                hname = path_inc+sfrac[hj]+htitles_byptcut[p]+htitles_byeta[b];
                hjtPfF_eta[0][hj][p][b] = (TH1F*) fi0->Get(hname);
                hjtPfF_eta[1][hj][p][b] = (TH1F*) fi1->Get(hname);
                if(!hjtPfF_eta[0][hj][p][b]){cerr<<"ERROR: Could not find histogram '"<< hname<<"' in files"<<endl;}
            }
            // by hiBin
            for(unsigned int hb=0; hb<nhiBin; hb++){
                for(int hj=0; hj<nmom; hj++){
                    hname = path_hibin+smom[hj]+htitles_byptcut[p]+htitles_byeta[b]+htitles_byhibin[hb];
                    hjetmom_hibin[0][hj][p][b][hb] = (TH1F*) fi0->Get(hname);
                    hjetmom_hibin[1][hj][p][b][hb] = (TH1F*) fi1->Get(hname);
                    if(!hjetmom_hibin[0][hj][p][b][hb]){cerr<<"ERROR: Could not find histogram '"<< hname<<"' in files"<<endl;}
                }
                hname = path_hibin+ep+htitles_byptcut[p]+htitles_byeta[b]+htitles_byhibin[hb];
                hjtetaphi_hibin[0][p][b][hb] = (TH2F*) fi0->Get(hname);
                hjtetaphi_hibin[1][p][b][hb] = (TH2F*) fi1->Get(hname);
                if(!hjtetaphi_hibin[0][p][b][hb]){cerr<<"ERROR: Could not find histogram '"<< hname<<"' in files"<<endl;}
                for(int hj=0; hj<nfrac; hj++){
                    hname = path_hibin+sfrac[hj]+htitles_byptcut[p]+htitles_byeta[b]+htitles_byhibin[hb];
                    hjtPfF_hibin[0][hj][p][b][hb] = (TH1F*) fi0->Get(hname);
                    hjtPfF_hibin[1][hj][p][b][hb] = (TH1F*) fi1->Get(hname);
                    if(!hjtPfF_hibin[0][hj][p][b][hb]){cerr<<"ERROR: Could not find histogram '"<< hname<<"' in files"<<endl;}
                }
            }
        }
    }
    cout<<"got histograms"<<endl;

    // normalizing jet histograms //
    double a;

    // for hists from both files
    for(int i=0; i<2; i++){
        // by pt cut
        for(unsigned int p=0; p<nptcuts; p++){
            // by eta
            for(unsigned int b=0; b<netabins; b++){
                // momenta 
                for(int hj=0; hj<nmom; hj++){
                    a = hjetmom_eta[i][hj][p][b]->Integral();
                    hjetmom_eta[i][hj][p][b]->Scale(1.0/a);
                }
                // eta phi map
                a = hjtetaphi_eta[i][p][b]->Integral();
                hjtetaphi_eta[i][p][b]->Scale(1.0/a);
                // fractions and multiplicities
                for(int hj=0; hj<nfrac; hj++){
                    a = hjtPfF_eta[i][hj][p][b]->Integral();
                    hjtPfF_eta[i][hj][p][b]->Scale(1.0/a);
                }
                // by hiBin
                for(unsigned int hb=0; hb<nhiBin; hb++){
                    for(int hj=0; hj<nmom; hj++){
                        a = hjetmom_hibin[i][hj][p][b][hb]->Integral();
                        hjetmom_hibin[i][hj][p][b][hb]->Scale(1.0/a);
                    }
                    a = hjtetaphi_hibin[i][p][b][hb]->Integral();
                    hjtetaphi_hibin[i][p][b][hb]->Scale(1.0/a);
                    for(int hj=0; hj<nfrac; hj++){
                        Double_t a = hjtPfF_hibin[i][hj][p][b][hb]->Integral();
                        hjtPfF_hibin[i][hj][p][b][hb]->Scale(1.0/a);
                    }
                }
            }
        }
    }
    cout<<"histograms normalized"<<endl;

    // saving non-overlay histograms //

    for(unsigned int p=0; p<nptcuts; p++){
        for(unsigned int b=0; b<netabins; b++){
            for(unsigned int i=0; i<2; i++){
                // momenta 
                for(int hj=0; hj<nmom; hj++){if(flag_mom==1){save_h1f_1(hjetmom_eta[i][hj][p][b], htitles_mom_xaxis[hj], "", htitles_mom_name[hj]+htitles_byptcut[p]+htitles_byeta[b], path_mom);}}
                if(flag_ep==1){save_2df(hjtetaphi_eta[0][p][b], htitles_mom_xaxis[2], htitles_mom_xaxis[3], "Inclusive", "jet_eta_phi"+htitles_byptcut[p]+htitles_byeta[b], path_ep);}
                // PF fractions
                for(int hj=0; hj<nfrac; hj++){if(flag_pf_frac==1){save_h1f_1(hjtPfF_eta[i][hj][p][b], htitles_frac_xaxis[hj], "", htitles_frac_name[hj]+htitles_byptcut[p]+htitles_byeta[b], path_frac);}}
                // by hiBin
                for(unsigned int hb=0; hb<nhiBin; hb++){
                    for(int hj=0; hj<nmom; hj++){if(flag_mom==1){save_h1f_1(hjetmom_hibin[i][hj][p][b][hb], htitles_mom_xaxis[hj], "", htitles_mom_name[hj]+htitles_byptcut[p]+htitles_byeta[b]+htitles_byhibin[hb], path_mom);}}
                    if(flag_ep==1){save_2df(hjtetaphi_hibin[0][p][b][hb], htitles_mom_xaxis[2], htitles_mom_xaxis[3], shiBins[hb], "jet_eta_phi"+htitles_byptcut[p]+htitles_byeta[b]+htitles_byhibin[hb], path_ep);}
                    for(int hj=0; hj<nfrac; hj++){if(flag_pf_frac==1){save_h1f_1(hjtPfF_hibin[i][hj][p][b][hb], htitles_frac_xaxis[hj], "", htitles_frac_name[hj]+htitles_byptcut[p]+htitles_byeta[b]+htitles_byhibin[hb], path_frac);}}
                }
                // saving overlay histograms //
                for(int hj=0; hj<nmom; hj++){if(flag_mom_ovr==1){save_mom_overlay(hjetmom_hibin, p, b, hj, htitles_mom_xaxis[hj], "", htitles_mom_name[hj]+htitles_byptcut[p]+htitles_byeta[b]+"_overlay", path_ovr_mom);}}
                for(int hj=0; hj<nfrac; hj++){if(flag_pf_frac_ovr==1){save_pf_overlay(hjtPfF_hibin, p, b, hj, htitles_frac_xaxis[hj], "", htitles_frac_name[hj]+htitles_byptcut[p]+htitles_byeta[b]+"_overlay", path_ovr_frac);}}
            }
        }
    }

    // making ratio histograms //

    // declaring ratio hists

    // by eta
    TH1F *hjetmom_eta_ratio[nmom][nptcuts][netabins];
    TH2F *hjtetaphi_eta_ratio[nptcuts][netabins];
    TH1F *hjtPfF_eta_ratio[nfrac][nptcuts][netabins];

    // by hibin
    TH1F *hjetmom_hibin_ratio[nmom][nptcuts][netabins][nhiBin];
    TH2F *hjtetaphi_hibin_ratio[nptcuts][netabins][nhiBin];
    TH1F *hjtPfF_hibin_ratio[nfrac][nptcuts][netabins][nhiBin];

    // making ratios with divide function
    
    for(unsigned int p=0; p<nptcuts; p++){
        for(unsigned int b=0; b<netabins; b++){
            for(int hj=0; hj<nmom; hj++){
                hjetmom_eta_ratio[hj][p][b] = (TH1F*)hjetmom_eta[0][hj][p][b]->Clone();
                hjetmom_eta_ratio[hj][p][b]->Divide(hjetmom_eta[0][hj][p][b],hjetmom_eta[1][hj][p][b],1,1,"");
            }
            hjtetaphi_eta_ratio[p][b] = (TH2F*)hjtetaphi_eta[0][p][b]->Clone();
            hjtetaphi_eta_ratio[p][b]->Divide(hjtetaphi_eta[0][p][b],hjtetaphi_eta[1][p][b],1,1,"");
            for(int hj=0; hj<nfrac; hj++){
                hjtPfF_eta_ratio[hj][p][b] = (TH1F*)hjtPfF_eta[0][hj][p][b]->Clone();
                hjtPfF_eta_ratio[hj][p][b]->Divide(hjtPfF_eta[0][hj][p][b],hjtPfF_eta[1][hj][p][b],1,1,"");
            }
            for(unsigned int hb=0; hb<nhiBin; hb++){
                for(int hj=0; hj<nmom; hj++){
                    hjetmom_hibin_ratio[hj][p][b][hb] = (TH1F*)hjetmom_hibin[0][hj][p][b][hb]->Clone();
                    hjetmom_hibin_ratio[hj][p][b][hb]->Divide(hjetmom_hibin[0][hj][p][b][hb],hjetmom_hibin[1][hj][p][b][hb],1,1,"");
                }
                hjtetaphi_hibin_ratio[p][b][hb] = (TH2F*)hjtetaphi_hibin[0][p][b][hb]->Clone();
                hjtetaphi_hibin_ratio[p][b][hb]->Divide(hjtetaphi_hibin[0][p][b][hb],hjtetaphi_hibin[1][p][b][hb],1,1,"");
                for(int hj=0; hj<nfrac; hj++){
                    hjtPfF_hibin_ratio[hj][p][b][hb] = (TH1F*)hjtPfF_hibin[0][hj][p][b][hb]->Clone();
                    hjtPfF_hibin_ratio[hj][p][b][hb]->Divide(hjtPfF_hibin[0][hj][p][b][hb],hjtPfF_hibin[1][hj][p][b][hb],1,1,"");
                }
            }
        }
    }

    // saving ratio histograms //

    for(unsigned int p=0; p<nptcuts; p++){
        for(unsigned int b=0; b<netabins; b++){
            for(int hj=0; hj<nmom; hj++){if(flag_momr==1){save_h1f_1(hjetmom_eta_ratio[hj][p][b], htitles_mom_xaxis[hj], "", htitles_mom_name[hj]+htitles_byptcut[p]+htitles_byeta[b], pathr_mom);}}
            if(flag_ep==1){save_2df(hjtetaphi_eta_ratio[p][b], htitles_mom_xaxis[2], htitles_mom_xaxis[3], "Inclusive", "jet_eta_phi"+htitles_byptcut[p]+htitles_byeta[b], pathr_ep);}
            for(int hj=0; hj<nfrac; hj++){if(flag_pf_fracr==1){save_h1f_1(hjtPfF_eta_ratio[hj][p][b], htitles_frac_xaxis[hj], "", htitles_frac_name[hj]+htitles_byptcut[p]+htitles_byeta[b], pathr_frac);}}
            for(unsigned int hb=0; hb<nhiBin; hb++){
                for(int hj=0; hj<nmom; hj++){if(flag_momr==1){save_h1f_1(hjetmom_hibin_ratio[hj][p][b][hb], htitles_mom_xaxis[hj], "", htitles_mom_name[hj]+htitles_byptcut[p]+htitles_byeta[b]+htitles_byhibin[hb], pathr_mom);}}
                if(flag_ep==1){save_2df(hjtetaphi_hibin_ratio[p][b][hb], htitles_mom_xaxis[2], htitles_mom_xaxis[3], shiBins[hb], "jet_eta_phi"+htitles_byptcut[p]+htitles_byeta[b]+htitles_byhibin[hb], pathr_ep);}
                for(int hj=0; hj<nfrac; hj++){if(flag_pf_fracr==1){save_h1f_1(hjtPfF_hibin_ratio[hj][p][b][hb], htitles_frac_xaxis[hj], "", htitles_frac_name[hj]+htitles_byptcut[p]+htitles_byeta[b]+htitles_byhibin[hb], pathr_frac);}}
            }
            for(int hj=0; hj<nmom; hj++){if(flag_momr_ovr==1){save_momr_overlay(hjetmom_hibin_ratio, p, b, hj, htitles_mom_xaxis[hj], "", htitles_mom_name[hj]+htitles_byptcut[p]+htitles_byeta[b]+"_overlay", pathr_ovr_mom);}}
            for(int hj=0; hj<nfrac; hj++){if(flag_pf_fracr_ovr==1){save_pfr_overlay(hjtPfF_hibin_ratio, p, b, hj, htitles_frac_xaxis[hj], "", htitles_frac_name[hj]+htitles_byptcut[p]+htitles_byeta[b]+"_overlay", pathr_ovr_frac);}}
        }
    }
    fi0->Close();
    fi1->Close();
}

        