#include "Jet_PbPb_MC_binning.h"
#include "2025_PbPb_MC_Triggers.h"

const float legxmin = 0.1;
const float legxmax = 0.9;
const float legymin = 0.72;
const float legymax = 0.9;

const float eff_lim = 1.3;

float ptmin = 20.0;
float ptmax = 500.0;

void normalizeh1(TH1F *h){
    double a = h->Integral();
    h->Scale(1.0/a);
}

void normalizeh2(TH2F *h){
    double a = h->Integral();
    h->Scale(1.0/a);
}

void save_h2f(TH2F *h[netabins][nhlTrigs], int etaindex, int trig_index, TString xtitle, TString ytitle, TString hname, TString htitle){
    
    // canvas
    TCanvas *c = new TCanvas();
    c->SetTitle("");
    c->SetName(hname);
    c->cd();
    c->SetRealAspectRatio();

    // clone of hist
    TH2F *h_c = (TH2F*)h[etaindex][trig_index]->Clone(hname);
    h_c->Draw("COLZ");
    h_c->GetZaxis()->SetRangeUser(0.0, eff_lim);

    // titles
    h_c->SetTitle(htitle);
    h_c->SetName(hname);
    h_c->GetYaxis()->SetTitle(ytitle);
    h_c->GetXaxis()->SetTitle(xtitle);
    h_c->GetYaxis()->CenterTitle(true);
    h_c->GetXaxis()->CenterTitle(true);

    // saving
    c->SaveAs("../plots/"+hname+".png");

    // deleting
    delete c;
    delete h_c;
}

void save_h2f_hibin(TH2F *h[netabins][nhlTrigs][nhiBin], int etaindex, int trig_index, int hibin_index, TString xtitle, TString ytitle, TString hname, TString htitle){
    
    // canvas
    TCanvas *c = new TCanvas();
    c->SetTitle("");
    c->SetName(hname);
    c->cd();
    c->SetRealAspectRatio();

    // clone of hist
    TH2F *h_c = (TH2F*)h[etaindex][trig_index][hibin_index]->Clone(hname);
    h_c->Draw("COLZ");
    h_c->GetZaxis()->SetRangeUser(0.0, eff_lim);

    // titles
    h_c->SetTitle(htitle);
    h_c->SetName(hname);
    h_c->GetYaxis()->SetTitle(ytitle);
    h_c->GetXaxis()->SetTitle(xtitle);
    h_c->GetYaxis()->CenterTitle(true);
    h_c->GetXaxis()->CenterTitle(true);

    // saving
    c->SaveAs("../plots/"+hname+".png");

    // deleting
    delete c;
    delete h_c;
}

void save_gr_alltrig(TGraphAsymmErrors *h[netabins][nhlTrigs], int etaindex, TString xtitle, TString ytitle, TString hname, TString htitle){
    
    // canvas
    TCanvas *c = new TCanvas();
    c->SetTitle("");
    c->SetName(hname);
    c->cd();
    c->SetLogx();
    c->SetRealAspectRatio();

    // graph clones
    TGraphAsymmErrors *h_c[nhlTrigs];
    for(int t=0; t<nhlTrigs; t++){h_c[t] = (TGraphAsymmErrors*)h[etaindex][t]->Clone(hname);}
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
    l->AddEntry((TObject*)0, "akCs4PF", "");
    l->Draw("same");

    // saving
    c->SaveAs("../plots/"+hname+".png");

    // deleting
    delete c;
    delete l;
}

void save_gr_alltrig_hibin(TGraphAsymmErrors *h[netabins][nhlTrigs][nhiBin], int etaindex, int hibin_index, TString xtitle, TString ytitle, TString hname, TString htitle){
    
    // canvas
    TCanvas *c = new TCanvas();
    c->SetTitle("");
    c->SetName(hname);
    c->cd();
    c->SetLogx();
    c->SetRealAspectRatio();

    // graph clones
    TGraphAsymmErrors *h_c[nhlTrigs];
    for(int t=0; t<nhlTrigs; t++){h_c[t] = (TGraphAsymmErrors*)h[etaindex][t][hibin_index]->Clone(hname);}
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
    TString shiBin = Form("%d < hiBin < %d",hiBinlo[hibin_index],hiBinhi[hibin_index]);
    l->AddEntry((TObject*)0, shiBin, "");
    l->AddEntry((TObject*)0, "akCs4PF", "");
    l->Draw("same");

    // saving
    c->SaveAs("../plots/"+hname+".png");

    // deleting
    delete c;
    delete l;
}