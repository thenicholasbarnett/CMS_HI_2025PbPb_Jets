#include "Jet_PbPb_DATA_binning.h"
#include "2025PbPb_JetTriggers.h"
// #include "2024PbPb_JetTriggers.h"

// run number
TString sRunNumber = "Run 399593 RawPrime0";
TString sGT = "151X_dataRun3_Prompt_v1";

// legend boundaries
const float legxmin = 0.1;
const float legxmax = 0.9;
const float legymin = 0.68;
const float legymax = 0.9;

// y axis limit for efficiencies
const float eff_lim = 1.4;

// minimum and maximum x axis (pt) values for jet turn ons
float ptmin = 20.0;
float ptmax = 300.0;

void save_gr_alltrig(TGraphAsymmErrors *h[2][netabins][nhlTrigs], int drmatch, int etaindex, TString xtitle, TString ytitle, TString hname, TString htitle){
    
    // canvas
    TCanvas *c = new TCanvas();
    c->SetTitle("");
    c->SetName(hname);
    c->cd();
    // c->SetLogx();
    c->SetRealAspectRatio();

    // graph clones
    TGraphAsymmErrors *h_c[nhlTrigs];
    for(int t=0; t<nhlTrigs; t++){h_c[t] = (TGraphAsymmErrors*)h[drmatch][etaindex][t]->Clone(hname);}
    h_c[0]->Draw("ap");

    // tline
    TLine *line1 = new TLine(ptmin,1,ptmax,1);
    line1->SetLineWidth(1);
    line1->SetLineColor(kBlack);
    line1->SetLineStyle(2);
    line1->Draw("same");

    // markers
    for(int t=0; t<nhlTrigs; t++){
        if(t==0){
            h_c[t]->SetMarkerColor(kBlack);
            h_c[t]->SetLineColor(kBlack);
        }
        if(t==1){
            h_c[t]->SetMarkerColor(kBlue);
            h_c[t]->SetLineColor(kBlue);
        }
        if(t==2){
            h_c[t]->SetMarkerColor(kRed);
            h_c[t]->SetLineColor(kRed);
        }
        if(t==3){
            h_c[t]->SetMarkerColor(kGreen);
            h_c[t]->SetLineColor(kGreen);
        }
        if(t==4){
            h_c[t]->SetMarkerColor(kMagenta);
            h_c[t]->SetLineColor(kMagenta);
        }
        h_c[t]->SetMarkerStyle(1);
        h_c[t]->Draw("p");
    }

    // titles
    h_c[0]->SetTitle(htitle);
    h_c[0]->SetName(hname);
    h_c[0]->GetYaxis()->SetTitle(ytitle);
    h_c[0]->GetXaxis()->SetTitle(xtitle);
    h_c[0]->GetYaxis()->CenterTitle(true);
    h_c[0]->GetXaxis()->CenterTitle(true);

    // y axis limits
    h_c[0]->SetMinimum(0.0);
    h_c[0]->SetMaximum(eff_lim);
    h_c[0]->GetXaxis()->SetRangeUser(ptmin,ptmax);

    // legend
    TLegend *l = new TLegend(legxmin,legymin,legxmax,legymax);
    l->SetBorderSize(0);
    l->SetFillStyle(0);
    for(int t=0; t<nhlTrigs; t++){
        l->AddEntry(h_c[t],sHLTrigs[t],"l");    
    }
    l->AddEntry((TObject*)0, sRunNumber, "");
    l->AddEntry((TObject*)0, sGT, "");
    l->AddEntry((TObject*)0, "akCs4PF", "");
    l->AddEntry((TObject*)0, sEtaBins[etaindex], "");
    if(drmatch==1){l->AddEntry((TObject*)0, "#Delta R < 0.3", "");}
    l->Draw("same");

    // saving
    if(drmatch==0){c->SaveAs("plots/"+hname+".png");}
    if(drmatch==1){c->SaveAs("plots/dR_matched/"+hname+"_dR_matched"+".png");}

    // deleting
    delete c;
    delete l;
}

void save_gr_alltrig_hibin(TGraphAsymmErrors *h[2][netabins][nhlTrigs][nhiBin], int drmatch, int etaindex, int hibin_index, TString xtitle, TString ytitle, TString hname, TString htitle){
    
    // canvas
    TCanvas *c = new TCanvas();
    c->SetTitle("");
    c->SetName(hname);
    c->cd();
    // c->SetLogx();
    c->SetRealAspectRatio();

    // graph clones
    TGraphAsymmErrors *h_c[nhlTrigs];
    for(int t=0; t<nhlTrigs; t++){h_c[t] = (TGraphAsymmErrors*)h[drmatch][etaindex][t][hibin_index]->Clone(hname);}
    h_c[0]->Draw("ap");

    // tline
    TLine *line1 = new TLine(ptmin,1,ptmax,1);
    line1->SetLineWidth(1);
    line1->SetLineColor(kBlack);
    line1->SetLineStyle(2);
    line1->Draw("same");

    // markers
    for(int t=0; t<nhlTrigs; t++){
        if(t==0){
            h_c[t]->SetMarkerColor(kBlack);
            h_c[t]->SetLineColor(kBlack);
        }
        if(t==1){
            h_c[t]->SetMarkerColor(kBlue);
            h_c[t]->SetLineColor(kBlue);
        }
        if(t==2){
            h_c[t]->SetMarkerColor(kRed);
            h_c[t]->SetLineColor(kRed);
        }
        if(t==3){
            h_c[t]->SetMarkerColor(kGreen);
            h_c[t]->SetLineColor(kGreen);
        }
        if(t==4){
            h_c[t]->SetMarkerColor(kMagenta);
            h_c[t]->SetLineColor(kMagenta);
        }
        h_c[t]->SetMarkerStyle(1);
        h_c[t]->Draw("p");
    }

    // titles
    h_c[0]->SetTitle(htitle);
    h_c[0]->SetName(hname);
    h_c[0]->GetYaxis()->SetTitle(ytitle);
    h_c[0]->GetXaxis()->SetTitle(xtitle);
    h_c[0]->GetYaxis()->CenterTitle(true);
    h_c[0]->GetXaxis()->CenterTitle(true);

    // y axis limits
    h_c[0]->SetMinimum(0.0);
    h_c[0]->SetMaximum(eff_lim);
    h_c[0]->GetXaxis()->SetRangeUser(ptmin,ptmax);

    // legend
    TLegend *l = new TLegend(legxmin,legymin,legxmax,legymax);
    l->SetBorderSize(0);
    l->SetFillStyle(0);
    for(int t=0; t<nhlTrigs; t++){
        l->AddEntry(h_c[t],sHLTrigs[t],"l");    
    }
    l->AddEntry((TObject*)0, sRunNumber, "");
    l->AddEntry((TObject*)0, sGT, "");
    l->AddEntry((TObject*)0, shiBins[hibin_index], "");
    l->AddEntry((TObject*)0, "akCs4PF", "");
    l->AddEntry((TObject*)0, sEtaBins[etaindex], "");
    if(drmatch==1){l->AddEntry((TObject*)0, "#Delta R < 0.3", "");}
    l->Draw("same");

    // saving
    if(drmatch==0){c->SaveAs("plots/"+hname+".png");}
    if(drmatch==1){c->SaveAs("plots/dR_matched/"+hname+"_dR_matched"+".png");}

    // deleting
    delete c;
    delete l;
}