#include "TROOT.h"
#include "TMath.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TDirectory.h"
#include "TGraph.h"
#include "TGraphAsymmErrors.h"

#include "header_files/JetTurnOn_plotting.h"

void JetTurnOn_Assemble(TString input, TString output){
    
    // getting rid of legends in hists in root file
    gStyle->SetOptStat(0);

    // opening the input file
    TFile *fi = TFile::Open(input,"read");
    fi->cd();

    // declaring input histograms //

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

    // declaring ratio graphs //

    TGraphAsymmErrors* hr_ljtpt_eta[2][netabins][nhlTrigs];
    TGraphAsymmErrors* hr_ljtpt_hibin[2][netabins][nhlTrigs][nhiBin];
    TGraphAsymmErrors* hr_HLT_ljtpt_eta[2][netabins][nhlTrigs];
    TGraphAsymmErrors* hr_HLT_ljtpt_hibin[2][netabins][nhlTrigs][nhiBin];

    // strings of directory paths in turnon file //

    TString ji = "jet_inclusive/hjtpt";
    TString jh = "jet_hibin/hjtpt";

    // retrieving histograms //
    
    // by eta
    for(unsigned int b=0; b<netabins; b++){
        TString hname = ji+htitles_byeta[b];
        h_ljtpt_eta[b] = (TH1F*) fi->Get(hname);

        for(int t=0; t<nhlTrigs; t++){
            hname = ji+htitles_byeta[b]+sHLTrigs_short[t];
            hhlt_ljtpt_eta[0][b][t] = (TH1F*) fi->Get(hname);

            hname = ji+htitles_byeta[b]+"_l1t"+sHLTrigs_short[t];
            hl1hlt_ljtpt_eta[0][b][t] = (TH1F*) fi->Get(hname);

            hname = ji+"_dR"+htitles_byeta[b]+sHLTrigs_short[t];
            hhlt_ljtpt_eta[1][b][t] = (TH1F*) fi->Get(hname);

            hname = ji+"_dR"+htitles_byeta[b]+"_l1t"+sHLTrigs_short[t];
            hl1hlt_ljtpt_eta[1][b][t] = (TH1F*) fi->Get(hname);

            if(t>=nl1Trigs){continue;}
            hname = ji+htitles_byeta[b]+sL1Trigs_short[t];
            hl1_ljtpt_eta[b][t] = (TH1F*) fi->Get(hname);
        }
        // by hiBin
        for(unsigned int hb=0; hb<nhiBin; hb++){
            hname = jh+htitles_byeta[b]+htitles_byhibin[hb];
            h_ljtpt_hibin[b][hb] = (TH1F*) fi->Get(hname);

            for(int t=0; t<nhlTrigs; t++){
                hname = jh+htitles_byeta[b]+sHLTrigs_short[t]+htitles_byhibin[hb];
                hhlt_ljtpt_hibin[0][b][t][hb] = (TH1F*) fi->Get(hname);

                hname = jh+htitles_byeta[b]+"_l1t"+sHLTrigs_short[t]+htitles_byhibin[hb];
                hl1hlt_ljtpt_hibin[0][b][t][hb] = (TH1F*) fi->Get(hname);

                hname = jh+"_dR"+htitles_byeta[b]+sHLTrigs_short[t]+htitles_byhibin[hb];
                hhlt_ljtpt_hibin[1][b][t][hb] = (TH1F*) fi->Get(hname);

                hname = jh+"_dR"+htitles_byeta[b]+"_l1t"+sHLTrigs_short[t]+htitles_byhibin[hb];
                hl1hlt_ljtpt_hibin[1][b][t][hb] = (TH1F*) fi->Get(hname);

                if(t>=nl1Trigs){continue;}
                hname = jh+htitles_byeta[b]+sL1Trigs_short[t]+htitles_byhibin[hb];
                hl1_ljtpt_hibin[b][t][hb] = (TH1F*) fi->Get(hname);
            }
        }
    }
    cout<<"finished getting histograms"<<endl;
    
    /// Making output file
    TFile *fo = new TFile(output,"recreate");
    fo->cd();

    // generating ratios
    for(int t=0; t<nhlTrigs; t++){
        for(int b=0; b<netabins; b++){
            for(int r=0; r<2; r++){
                // full HLT efficiency
                hr_HLT_ljtpt_eta[r][b][t] = new TGraphAsymmErrors(hhlt_ljtpt_eta[r][b][t],h_ljtpt_eta[b],"cl=0.683 b(1,1) mode");
                // relative HLT efficiency
                hr_ljtpt_eta[r][b][t] = new TGraphAsymmErrors(hl1hlt_ljtpt_eta[r][b][t],hl1_ljtpt_eta[b][L1SeedHLT[t]],"cl=0.683 b(1,1) mode");

                for(unsigned int hb=0; hb<nhiBin; hb++){
                    // full HLT efficiency
                    hr_HLT_ljtpt_hibin[r][b][t][hb] = new TGraphAsymmErrors(hhlt_ljtpt_hibin[r][b][t][hb],h_ljtpt_hibin[b][hb],"cl=0.683 b(1,1) mode");     
                    // reltive HLT efficiencies
                    hr_ljtpt_hibin[r][b][t][hb] = new TGraphAsymmErrors(hl1hlt_ljtpt_hibin[r][b][t][hb],hl1_ljtpt_hibin[b][L1SeedHLT[t]][hb],"cl=0.683 b(1,1) mode");
                }
            }
        }
    }
    cout<<"finished generating ratios"<<endl;

    // making directories for efficiencies
    TDirectory *d_in = fo->mkdir("inputs");
    TDirectory *d_out = fo->mkdir("outputs");

    for(int t=0; t<nhlTrigs; t++){
        for(unsigned int b=0; b<netabins; b++){
            for(int i=0; i<2; i++){
                d_in->cd(); 
                hl1hlt_ljtpt_eta[i][b][t]->Write();
                if((t<nl1Trigs)&&(i==0)){hl1_ljtpt_eta[b][t]->Write();}

                d_out->cd(); 
                hr_HLT_ljtpt_eta[i][b][t]->Write();
                hr_ljtpt_eta[i][b][t]->Write();
                
                for(unsigned int hb=0; hb<nhiBin; hb++){
                    d_in->cd(); 
                    hl1hlt_ljtpt_hibin[i][b][t][hb]->Write();
                    if((t<nl1Trigs)&&(i==0)){hl1_ljtpt_hibin[b][t][hb]->Write();}

                    d_out->cd();
                    hr_HLT_ljtpt_hibin[i][b][t][hb]->Write();
                    hr_ljtpt_hibin[i][b][t][hb]->Write();
                }
            }
        }
    }
    cout<<"ratios written to output file"<<endl;

    for(unsigned int b=0; b<netabins; b++){
        for(int i=0; i<2; i++){
            save_gr_alltrig(hr_ljtpt_eta, i, b, "p_{T,leading jet}", "HLT & L1 & MB / L1 & MB", "RelHLT_TurnOn_inclusive"+htitles_byeta[b], "");
            save_gr_alltrig(hr_HLT_ljtpt_eta, i, b, "p_{T,leading jet}", "HLT & MB/ MB", "HLT_TurnOn_inclusive"+htitles_byeta[b], "");
            for(unsigned int hb=0; hb<nhiBin; hb++){
                save_gr_alltrig_hibin(hr_ljtpt_hibin, i, b, hb, "p_{T,leading jet}", "HLT & L1 & MB/ L1 & MB", "RelHLT_TurnOn"+htitles_byhibin[hb]+htitles_byeta[b], "");
                save_gr_alltrig_hibin(hr_HLT_ljtpt_hibin, i, b, hb, "p_{T,leading jet}", "HLT & MB/ MB", "HLT_TurnOn"+htitles_byhibin[hb]+htitles_byeta[b], "");
            }
        }
    }
    cout<<"ratios saved as png files"<<endl;
}
