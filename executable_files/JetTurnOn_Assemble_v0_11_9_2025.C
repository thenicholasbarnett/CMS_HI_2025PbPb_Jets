#include "TROOT.h"
#include "TMath.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TDirectory.h"
#include "TGraph.h"
#include "TGraphAsymmErrors.h"

#include "JetTurnOn_plotting_11_9_2025.h"

void JetTurnOn_Assemble_v0_11_9_2025(){
    
    // getting rid of legends in hists in root file
    gStyle->SetOptStat(0);

    // opening the input file
    TString input="JetTurnOn_2025PbPbMC_11_9_2025_withDM.root";
    TFile *fi = TFile::Open(input,"read");
    fi->cd();

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

    // declaring ratio graphs and hists //

    TGraphAsymmErrors* hr_ljtpt_eta[netabins][nhlTrigs];
    TGraphAsymmErrors* hr_ljtpt_hibin[netabins][nhlTrigs][nhiBin];
    TH2F* hr_ep_eta[netabins][nhlTrigs];
    TH2F* hr_ep_hibin[netabins][nhlTrigs][nhiBin];

    // strings of directory paths in turnon file //

    TString ji = "jet_inclusive/";
    TString jh = "jet_hibin/";

    // retrieving histograms //
    
    // by eta
    for(unsigned int b=0; b<netabins; b++){

        // eta bin as a string
        TString sEtaBin = Form("_AbsEta_%.0f_to_%.0f",etalo[b]*10,etahi[b]*10);

        TString htitle0 = ji+"hjtpt"+sEtaBin;
        h_ljtpt_eta[b] = (TH1F*) fi->Get(htitle0);

        TString htitle1 = ji+"hetaphi"+sEtaBin;
        h_ep_eta[b] = (TH2F*) fi->Get(htitle1);
        
        for(int t=0; t<nhlTrigs; t++){

            TString htitle4 = ji+"hjtpt"+sEtaBin+sHLTrigs_short[t];
            hhlt_ljtpt_eta[b][t] = (TH1F*) fi->Get(htitle4);

            TString htitle5 = ji+"hetaphi"+sEtaBin+sHLTrigs_short[t];
            hhlt_ep_eta[b][t] = (TH2F*) fi->Get(htitle5);

            TString htitle6 = ji+"hjtpt"+sEtaBin+"_l1t"+sHLTrigs_short[t];
            hl1hlt_ljtpt_eta[b][t] = (TH1F*) fi->Get(htitle6);

            TString htitle7 = ji+"hetaphi"+sEtaBin+"_l1t"+sHLTrigs_short[t];
            hl1hlt_ep_eta[b][t] = (TH2F*) fi->Get(htitle7);
            hr_ep_eta[b][t] = (TH2F*)hl1hlt_ep_eta[b][t]->Clone("ratio_"+htitle7);

            if((t==nl1Trigs)||(t>nl1Trigs)){continue;}

            TString htitle2 = ji+"hjtpt"+sEtaBin+sL1Trigs_short[t];
            hl1_ljtpt_eta[b][t] = (TH1F*) fi->Get(htitle2);

            TString htitle3 = ji+"hetaphi"+sEtaBin+sL1Trigs_short[t];
            hl1_ep_eta[b][t] = (TH2F*) fi->Get(htitle3);
        }

        // by hiBin
        for(unsigned int hb=0; hb<nhiBin; hb++){

            // hibin as a string
            TString shiBin = Form("_hibin_%d_to_%d",hiBinlo[hb],hiBinhi[hb]);
            
            TString htitle8 = jh+"hjtpt"+sEtaBin+shiBin;
            h_ljtpt_hibin[b][hb] = (TH1F*) fi->Get(htitle8);

            TString htitle9 = jh+"hetaphi"+sEtaBin+shiBin;
            h_ep_hibin[b][hb] = (TH2F*) fi->Get(htitle9);
            
            for(int t=0; t<nhlTrigs; t++){

                TString htitle12 = jh+"hjtpt"+sEtaBin+sHLTrigs_short[t]+shiBin;
                hhlt_ljtpt_hibin[b][t][hb] = (TH1F*) fi->Get(htitle12);

                TString htitle13 = jh+"hetaphi"+sEtaBin+sHLTrigs_short[t]+shiBin;
                hhlt_ep_hibin[b][t][hb] = (TH2F*) fi->Get(htitle13);

                TString htitle14 = jh+"hjtpt"+sEtaBin+"_l1t"+sHLTrigs_short[t]+shiBin;
                hl1hlt_ljtpt_hibin[b][t][hb] = (TH1F*) fi->Get(htitle14);

                TString htitle15 = jh+"hetaphi"+sEtaBin+"_l1t"+sHLTrigs_short[t]+shiBin;
                hl1hlt_ep_hibin[b][t][hb] = (TH2F*) fi->Get(htitle15);
                hr_ep_hibin[b][t][hb] = (TH2F*)hl1hlt_ep_hibin[b][t][hb]->Clone("ratio_"+htitle15);

                if((t==nl1Trigs)||(t>nl1Trigs)){continue;}

                TString htitle10 = jh+"hjtpt"+sEtaBin+sL1Trigs_short[t]+shiBin;
                hl1_ljtpt_hibin[b][t][hb] = (TH1F*) fi->Get(htitle10);

                TString htitle11 = jh+"hetaphi"+sEtaBin+sL1Trigs_short[t]+shiBin;
                hl1_ep_hibin[b][t][hb] = (TH2F*) fi->Get(htitle11);
            }
        }
    }
    cout<<"finished getting histograms"<<endl;

    // for(unsigned int b=0; b<netabins; b++){
    //     for(int t=0; t<nhlTrigs; t++){
    //         // normalizeh1(hl1hlt_ljtpt_eta[b][t]);
    //         normalizeh2(hl1hlt_ep_eta[b][t]);
    //         if((t==nl1Trigs)||(t>nl1Trigs)){continue;}
    //         // normalizeh1(hl1_ljtpt_eta[b][t]);
    //         normalizeh2(hl1_ep_eta[b][t]);
    //     }
    //     for(unsigned int hb=0; hb<nhiBin; hb++){
    //         for(int t=0; t<nhlTrigs; t++){
    //             // normalizeh1(hl1hlt_ljtpt_hibin[b][t][hb]);
    //             normalizeh2(hl1hlt_ep_hibin[b][t][hb]);
    //             if((t==nl1Trigs)||(t>nl1Trigs)){continue;}
    //             // normalizeh1(hl1_ljtpt_hibin[b][t][hb]);
    //             normalizeh2(hl1_ep_hibin[b][t][hb]);
    //         }
    //     }
    // }
    // cout<<"histograms normalized"<<endl;
    
    /// Making output file
    TString output="JetTurnOn_Assembled_fdamasDijetMC_11_9_2025.root";
    TFile *fo = new TFile(output,"recreate");
    fo->cd();

    // generating ratios
    for(unsigned int b=0; b<netabins; b++){

        // leading jet pt
        hr_ljtpt_eta[b][0] = new TGraphAsymmErrors(hl1hlt_ljtpt_eta[b][0],hl1_ljtpt_eta[b][0],"cl=0.683 b(1,1) mode");
        hr_ljtpt_eta[b][1] = new TGraphAsymmErrors(hl1hlt_ljtpt_eta[b][1],hl1_ljtpt_eta[b][0],"cl=0.683 b(1,1) mode");
        hr_ljtpt_eta[b][2] = new TGraphAsymmErrors(hl1hlt_ljtpt_eta[b][2],hl1_ljtpt_eta[b][1],"cl=0.683 b(1,1) mode");
        
        // eta phi maps
        hr_ep_eta[b][0]->Divide(hl1hlt_ep_eta[b][0], hl1_ep_eta[b][0], 1, 1, "B");
        hr_ep_eta[b][1]->Divide(hl1hlt_ep_eta[b][1], hl1_ep_eta[b][0], 1, 1, "B");
        hr_ep_eta[b][2]->Divide(hl1hlt_ep_eta[b][2], hl1_ep_eta[b][1], 1, 1, "B");

        for(unsigned int hb=0; hb<nhiBin; hb++){
            hr_ljtpt_hibin[b][0][hb] = new TGraphAsymmErrors(hl1hlt_ljtpt_hibin[b][0][hb],hl1_ljtpt_hibin[b][0][hb],"cl=0.683 b(1,1) mode");
            hr_ljtpt_hibin[b][1][hb] = new TGraphAsymmErrors(hl1hlt_ljtpt_hibin[b][1][hb],hl1_ljtpt_hibin[b][0][hb],"cl=0.683 b(1,1) mode");
            hr_ljtpt_hibin[b][2][hb] = new TGraphAsymmErrors(hl1hlt_ljtpt_hibin[b][2][hb],hl1_ljtpt_hibin[b][1][hb],"cl=0.683 b(1,1) mode");
            hr_ep_hibin[b][0][hb]->Divide(hl1hlt_ep_hibin[b][0][hb], hl1_ep_hibin[b][0][hb], 1, 1, "B");
            hr_ep_hibin[b][1][hb]->Divide(hl1hlt_ep_hibin[b][1][hb], hl1_ep_hibin[b][0][hb], 1, 1, "B");
            hr_ep_hibin[b][2][hb]->Divide(hl1hlt_ep_hibin[b][2][hb], hl1_ep_hibin[b][1][hb], 1, 1, "B");
        }
    }
    cout<<"finished generating ratios"<<endl;

    // making directories for efficiencies
    TDirectory *djin = fo->mkdir("inputs");
    TDirectory *dji = fo->mkdir("jet_inclusive");
    TDirectory *djh = fo->mkdir("jet_hibin");

    for(int t=0; t<nhlTrigs; t++){
        for(unsigned int b=0; b<netabins; b++){
            djin->cd(); 
            hl1hlt_ljtpt_eta[b][t]->Write();
            if(t<nl1Trigs){hl1_ljtpt_eta[b][t]->Write();}
            dji->cd(); 
            hr_ljtpt_eta[b][t]->Write();
            hr_ep_eta[b][t]->Write();
            for(unsigned int hb=0; hb<nhiBin; hb++){
                djin->cd(); 
                hl1hlt_ljtpt_hibin[b][t][hb]->Write();
                if(t<nl1Trigs){hl1_ljtpt_hibin[b][t][hb]->Write();}
                djh->cd();
                hr_ljtpt_hibin[b][t][hb]->Write();
                hr_ep_hibin[b][t][hb]->Write();
            }
        }
    }
    cout<<"ratios written to output file"<<endl;

    // save_h2f(TH2F *h[netabins][nhlTrigs], int etaindex, int trig_index, TString xtitle, TString ytitle, TString hname, TString htitle)
    // save_h2f_hibin(TH2F *h[netabins][nhlTrigs][nhiBin], int etaindex, int trig_index, int hibin_index, TString xtitle, TString ytitle, TString hname, TString htitle)
    // save_gr_alltrig(TGraphAsymmErrors *h[netabins][nhlTrigs], int etaindex, TString xtitle, TString ytitle, TString hname, TString htitle)
    // save_gr_alltrig_hibin(TGraphAsymmErrors *h[netabins][nhlTrigs][nhiBin], int etaindex, int hibin_index, TString xtitle, TString ytitle, TString hname, TString htitle)

    for(unsigned int b=0; b<netabins; b++){
        save_gr_alltrig(hr_ljtpt_eta, b, "p_{T,leading jet}", "hlt & l1 fire/ l1 fire", "RelHLT_TurnOn_inclusive", "");
        for(int t=0; t<nhlTrigs; t++){save_h2f(hr_ep_eta, b, t, "#eta^{leading jet}", "#phi^{leading jet}", "eta_phi"+sHLTrigs_short[t], sHLTrigs[t]);}
        for(unsigned int hb=0; hb<nhiBin; hb++){
            save_gr_alltrig_hibin(hr_ljtpt_hibin, b, hb, "p_{T,leading jet}", "hlt & l1 fire/ l1 fire", "RelHLT_TurnOn"+shiBins[hb], "");
            for(int t=0; t<nhlTrigs; t++){save_h2f_hibin(hr_ep_hibin, b, t, hb, "#eta^{leading jet}", "#phi^{leading jet}", "eta_phi"+sHLTrigs_short[t]+shiBins[hb], sHLTrigs[t]+shiBins[hb]);}
        }
    }
    cout<<"ratios saved as png files"<<endl;
}