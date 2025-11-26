#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TDirectory.h"
#include "TAxis.h"

#include "header_files/JetCheck_PbPb_plotting.h"

void JetCheck_PlottingIndividual_PbPb(TString input, int run_num){

    // getting rid of legends in hists in root file
    gStyle->SetOptStat(0);

    // reading input files
    TFile *fi = TFile::Open(input,"read");
    cout<<"opened "<<input<<endl;

    // flags for saving files //
    int flag_mom = 0;
    int flag_pf_frac = 0;

    int flag_ep = 1;
    int flag_mom_ovr = 1;
    int flag_pf_frac_ovr = 1;

    // int flag_ep = 0;
    // int flag_pf_fracr_ovr = 0;
    // int flag_momr_ovr = 0;

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
                hjetmom_eta[hj][p][b] = (TH1F*) fi->Get(hname);
                if(!hjetmom_eta[hj][p][b]){cerr<<"ERROR: Could not find histogram '"<< hname<<"' in file"<<endl;}
            }
            hname = path_inc+ep+htitles_byptcut[p]+htitles_byeta[b];
            hjtetaphi_eta[p][b] = (TH2F*) fi->Get(hname);
            if(!hjtetaphi_eta[p][b]){cerr<<"ERROR: Could not find histogram '"<< hname<<"' in file"<<endl;}
            // PF fractions
            for(int hj=0; hj<nfrac; hj++){
                hname = path_inc+sfrac[hj]+htitles_byptcut[p]+htitles_byeta[b];
                hjtPfF_eta[hj][p][b] = (TH1F*) fi->Get(hname);
                if(!hjtPfF_eta[hj][p][b]){cerr<<"ERROR: Could not find histogram '"<< hname<<"' in file"<<endl;}
            }
            // by hiBin
            for(unsigned int hb=0; hb<nhiBin; hb++){
                for(int hj=0; hj<nmom; hj++){
                    hname = path_hibin+smom[hj]+htitles_byptcut[p]+htitles_byeta[b]+htitles_byhibin[hb];
                    hjetmom_hibin[hj][p][b][hb] = (TH1F*) fi->Get(hname);
                    if(!hjetmom_hibin[hj][p][b][hb]){cerr<<"ERROR: Could not find histogram '"<< hname<<"' in file"<<endl;}
                }
                hname = path_hibin+ep+htitles_byptcut[p]+htitles_byeta[b]+htitles_byhibin[hb];
                hjtetaphi_hibin[p][b][hb] = (TH2F*) fi->Get(hname);
                if(!hjtetaphi_hibin[p][b][hb]){cerr<<"ERROR: Could not find histogram '"<< hname<<"' in file"<<endl;}
                for(int hj=0; hj<nfrac; hj++){
                    hname = path_hibin+sfrac[hj]+htitles_byptcut[p]+htitles_byeta[b]+htitles_byhibin[hb];
                    hjtPfF_hibin[hj][p][b][hb] = (TH1F*) fi->Get(hname);
                    if(!hjtPfF_hibin[hj][p][b][hb]){cerr<<"ERROR: Could not find histogram '"<< hname<<"' in file"<<endl;}
                }
            }
        }
    }
    cout<<"got histograms"<<endl;

    // normalizing jet histograms //

    // by pt cut
    for(unsigned int p=0; p<nptcuts; p++){
        // by eta
        for(unsigned int b=0; b<netabins; b++){
            // momenta 
            for(int hj=0; hj<nmom; hj++){normalize(hjetmom_eta[hj][p][b]);}
            // eta phi map
            normalize(hjtetaphi_eta[p][b]);
            // fractions and multiplicities
            for(int hj=0; hj<nfrac; hj++){normalize(hjtPfF_eta[hj][p][b]);}
            // by hiBin
            for(unsigned int hb=0; hb<nhiBin; hb++){
                for(int hj=0; hj<nmom; hj++){normalize(hjetmom_hibin[hj][p][b][hb]);}
                normalize(hjtetaphi_hibin[p][b][hb]);
                for(int hj=0; hj<nfrac; hj++){normalize(hjtPfF_hibin[hj][p][b][hb]);}
            }
        }
    }
    cout<<"histograms normalized"<<endl;

    // saving individual histograms //

    for(unsigned int p=0; p<nptcuts; p++){
        for(unsigned int b=0; b<netabins; b++){
            if(b==1){continue;}
            // momenta 
            for(int hj=0; hj<nmom; hj++){if(flag_mom==1){save_h1f_1(hjetmom_eta[hj][p][b], htitles_mom_xaxis[hj], "", htitles_mom_name[hj]+htitles_byptcut[p]+htitles_byeta[b], run_num, path_mom);}}
            if(flag_ep==1){save_2df(hjtetaphi_eta[p][b], p, htitles_mom_xaxis[2], htitles_mom_xaxis[3], "Inclusive", "jet_eta_phi"+htitles_byptcut[p]+htitles_byeta[b], run_num, path_ep);}
            // PF fractions
            for(int hj=0; hj<nfrac; hj++){if(flag_pf_frac==1){save_h1f_1(hjtPfF_eta[hj][p][b], htitles_frac_xaxis[hj], "", htitles_frac_name[hj]+htitles_byptcut[p]+htitles_byeta[b], run_num, path_frac);}}
            // by hiBin
            for(unsigned int hb=0; hb<nhiBin; hb++){
                for(int hj=0; hj<nmom; hj++){if(flag_mom==1){save_h1f_1(hjetmom_hibin[hj][p][b][hb], htitles_mom_xaxis[hj], "", htitles_mom_name[hj]+htitles_byptcut[p]+htitles_byeta[b]+htitles_byhibin[hb], run_num, path_mom);}}
                if(flag_ep==1){save_2df(hjtetaphi_hibin[p][b][hb], p, htitles_mom_xaxis[2], htitles_mom_xaxis[3], shiBins[hb], "jet_eta_phi"+htitles_byptcut[p]+htitles_byeta[b]+htitles_byhibin[hb], run_num, path_ep);}
                for(int hj=0; hj<nfrac; hj++){if(flag_pf_frac==1){save_h1f_1(hjtPfF_hibin[hj][p][b][hb], htitles_frac_xaxis[hj], "", htitles_frac_name[hj]+htitles_byptcut[p]+htitles_byeta[b]+htitles_byhibin[hb], run_num, path_frac);}}
            }
            // saving overlay histograms //
            for(int hj=0; hj<nmom; hj++){if(flag_mom_ovr==1){save_mom_overlay(hjetmom_hibin, p, b, hj, htitles_mom_xaxis[hj], "", htitles_mom_name[hj]+htitles_byptcut[p]+htitles_byeta[b]+"_overlay", run_num, path_mom);}}
            for(int hj=0; hj<nfrac; hj++){if(flag_pf_frac_ovr==1){save_pf_overlay(hjtPfF_hibin, p, b, hj, htitles_frac_xaxis[hj], "", htitles_frac_name[hj]+htitles_byptcut[p]+htitles_byeta[b]+"_overlay", run_num, path_frac);}}
        
        }
    }
    fi->Close();
}

        