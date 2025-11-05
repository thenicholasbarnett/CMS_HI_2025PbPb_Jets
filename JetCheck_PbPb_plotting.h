#include "JetCheck_PbPb_MC_binning.h"

/// file paths
// non-overlay
TString path_mom = "/plots/individual/momenta/";
TString path_ep = "/plots/individual/eta_phi/";
TString path_frac = "/plots/individual/fractions/";
TString path_mult = "/plots/individual/multiplicity/";
// overlay
TString path_ovr_mom = "/plots/overlays/momenta/";
TString path_ovr_frac = "/plots/overlays/fractions/";
TString path_ovr_mult = "/plots/overlays/multiplicity/";

void normalizeh(TH1F *h){
    double a = h->Integral();
    h->Scale(1.0/a);
}

void save_h1f_1(TH1F *h, TString xtitle, TString ytitle, TString hname, TString path){

    // canvas
    TCanvas *c = new TCanvas();
    c->SetTitle("");
    c->SetName(hname);
    c->cd();
    if((xtitle=="p_{T}^{raw}")||(xtitle=="p_{T}^{jet}")){c->SetLogy();}
    c->SetRealAspectRatio();

    // cout<<"made canvas"<<endl;

    if(!h){std::cerr << "Error: null histogram pointer passed to save_h1f_1" << std::endl; return;}

    // clone of hist
    TH1F *h_c = (TH1F*)h->Clone("new name");

    // cout<<"cloned input histogram"<<endl;

    // markers
    h_c->Draw("e1p");
    // h_c->SetMarkerStyle(1);
    h_c->SetMarkerStyle(8);
    h_c->SetMarkerColor(kBlack);
    h_c->SetLineColor(kBlack);

    // titles
    h_c->SetTitle("");
    h_c->SetName(hname);
    h_c->GetYaxis()->SetTitle(ytitle);
    h_c->GetYaxis()->CenterTitle(true);
    h_c->GetXaxis()->SetTitle(xtitle);
    h_c->GetXaxis()->CenterTitle(true);

    // cout<<"edited cloned histogram"<<endl;

    // legend
    TLegend *l = new TLegend(0.7,0.7,0.9,0.9);
    l->SetBorderSize(0);
    l->SetFillStyle(0);
    l->AddEntry(h_c,hname,"pl");
    l->AddEntry((TObject*)0, "akCs4PF", "");
    l->Draw("same");

    // cout<<"made legend"<<endl;

    // // y axis limits
    // h_c->SetMinimum(0.8);
    // h_c->SetMaximum(1.2);

    // saving
    c->SaveAs(path+hname+".png");
}

void save_h1i_1(TH1I *h, TString xtitle, TString ytitle, TString hname, TString path){

    // canvas
    TCanvas *c = new TCanvas();
    c->SetTitle("");
    c->SetName(hname);
    c->cd();
    // c->SetLogy();
    c->SetRealAspectRatio();

    // clone of hist
    TH1I *h_c = (TH1I*)h->Clone(hname);

    // markers
    h_c->Draw("e1p");
    // h_c->SetMarkerStyle(1);
    h_c->SetMarkerStyle(8);
    h_c->SetMarkerColor(kBlack);
    h_c->SetLineColor(kBlack);

    // titles
    h_c->SetTitle("");
    h_c->SetName(hname);
    h_c->GetYaxis()->SetTitle(ytitle);
    h_c->GetYaxis()->CenterTitle(true);
    h_c->GetXaxis()->SetTitle(xtitle);
    h_c->GetXaxis()->CenterTitle(true);

    // legend
    TLegend *l = new TLegend(0.7,0.7,0.9,0.9);
    l->SetBorderSize(0);
    l->SetFillStyle(0);
    l->AddEntry(h_c,hname,"pl");
    l->AddEntry((TObject*)0, "akCs4PF", "");
    l->Draw("same");

    // // y axis limits
    // h_c->SetMinimum(0.8);
    // h_c->SetMaximum(1.2);

    // saving
    c->SaveAs(path+hname+".png");

    // deleting
    delete c;
    delete h_c;
    delete l;
}

void save_2d_byhibin(TH2F *h[netabins][nhiBin], int etaindex, int hibinindex, TString xtitle, TString ytitle, TString htitle, TString hname, TString path){

    // canvas
    TCanvas *c = new TCanvas();
    c->SetTitle("");
    c->SetName(hname);
    c->cd();
    // c->SetLogy();
    c->SetRealAspectRatio();

    // clone of hist
    TH2F *h_c = (TH2F*)h[etaindex][hibinindex]->Clone(hname);

    // markers
    h_c->Draw("COLZ");
    // h_c->SetMarkerStyle(1);
    h_c->SetMarkerStyle(8);
    h_c->SetMarkerColor(kBlack);
    h_c->SetLineColor(kBlack);

    // titles
    h_c->SetTitle(htitle);
    h_c->SetName(hname);
    h_c->GetYaxis()->SetTitle(ytitle);
    h_c->GetYaxis()->CenterTitle(true);
    h_c->GetXaxis()->SetTitle(xtitle);
    h_c->GetXaxis()->CenterTitle(true);

    // // legend
    // TLegend *l = new TLegend(0.7,0.7,0.9,0.9);
    // l->SetBorderSize(0);
    // l->SetFillStyle(0);
    // l->AddEntry(h_c,hname,"pl");
    // l->AddEntry((TObject*)0, "akCs4PF", "");
    // l->Draw("same");

    // // y axis limits
    // h_c->SetMinimum(0.8);
    // h_c->SetMaximum(1.2);

    // saving
    c->SaveAs(path+hname+".png");

    // deleting
    delete c;
    delete h_c;
    // delete l;
}

void save_2d_byeta(TH2F *h[netabins], int etaindex, TString xtitle, TString ytitle, TString htitle, TString hname, TString path){

    // canvas
    TCanvas *c = new TCanvas();
    c->SetTitle("");
    c->SetName(hname);
    c->cd();
    // c->SetLogy();
    c->SetRealAspectRatio();

    // clone of hist
    TH2F *h_c = (TH2F*)h[etaindex]->Clone(hname);

    // markers
    h_c->Draw("COLZ");
    // h_c->SetMarkerStyle(1);
    h_c->SetMarkerStyle(8);
    h_c->SetMarkerColor(kBlack);
    h_c->SetLineColor(kBlack);

    // titles
    h_c->SetTitle(htitle);
    h_c->SetName(hname);
    h_c->GetYaxis()->SetTitle(ytitle);
    h_c->GetYaxis()->CenterTitle(true);
    h_c->GetXaxis()->SetTitle(xtitle);
    h_c->GetXaxis()->CenterTitle(true);

    // // legend
    // TLegend *l = new TLegend(0.7,0.7,0.9,0.9);
    // l->SetBorderSize(0);
    // l->SetFillStyle(0);
    // l->AddEntry(h_c,hname,"pl");
    // l->AddEntry((TObject*)0, "akCs4PF", "");
    // l->Draw("same");

    // // y axis limits
    // h_c->SetMinimum(0.8);
    // h_c->SetMaximum(1.2);

    // saving
    c->SaveAs(path+hname+".png");

    // deleting
    delete c;
    delete h_c;
    // delete l;
}

void save_mom_overlay(TH1F *h[nmom][netabins][nhiBin], int etaindex, int momindex, TString xtitle, TString ytitle, TString hname, TString path){

    if(momindex < 0 || momindex >= nmom || etaindex < 0 || etaindex >= netabins){cerr << "ERROR: out-of-bounds indices in " << hname << endl;return;}
    for(int i=0; i<nhiBin;i++){
        if(!h[momindex][etaindex][i]){
            cerr<<"ERROR: null histogram for hibin "<<shiBins[i]<<" in '"<< hname<<"'"<<endl;
            return;
        }
    }

    // canvas
    TCanvas *c = new TCanvas();
    c->SetTitle("");
    c->SetName(hname);
    c->cd();
    if((xtitle=="p_{T}^{raw}")||(xtitle=="p_{T}^{jet}")){c->SetLogy();}
    if((xtitle=="p_{T}^{raw}")||(xtitle=="p_{T}^{jet}")){c->SetLogx();}
    c->SetRealAspectRatio();

    // clones of hists
    TH1F *h1_c = (TH1F*)h[momindex][etaindex][0]->Clone();
    TH1F *h_c[nTrigs-1];
    for(unsigned int i=1; i<nTrigs; i++){
        h_c[i-1] = (TH1F*)h[momindex][etaindex][i]->Clone();
    }

    // // setting y axis limits
    if(xtitle=="#eta^{jet}"){h1_c->SetMaximum(0.1);}
    // if(xtitle=="#eta^{jet}"){h1_c->SetMinimum(0.07);}
    if(xtitle=="#phi^{jet}"){h1_c->SetMaximum(0.02);}
    if(xtitle=="#phi^{jet}"){h1_c->SetMinimum(0.01);}
    if((xtitle=="p_{T}^{raw}")||(xtitle=="p_{T}^{jet}")){h1_c->GetXaxis()->SetRangeUser(10,1000);}

    // parent histogram (h[0])
    h1_c->Draw("e1p");
    h1_c->SetMarkerStyle(1);
    h1_c->SetMarkerColor(kBlack);
    h1_c->SetLineColor(kBlack);
    h1_c->SetTitle("");
    h1_c->SetName(hname);
    h1_c->GetYaxis()->SetTitle(ytitle);
    h1_c->GetYaxis()->CenterTitle(true);
    h1_c->GetXaxis()->SetTitle(xtitle);
    h1_c->GetXaxis()->CenterTitle(true);

    // other four histograms
    for(unsigned int i=0; i<nTrigs-1; i++){
        if(i==0){
            h_c[i]->SetMarkerColor(kBlue);
            h_c[i]->SetLineColor(kBlue);
        }
        if(i==1){
            h_c[i]->SetMarkerColor(kRed);
            h_c[i]->SetLineColor(kRed);
        }
        if(i==2){
            h_c[i]->SetMarkerColor(kGreen+1);
            h_c[i]->SetLineColor(kGreen+1);
        }
        if(i==3){
            h_c[i]->SetMarkerColor(kMagenta);
            h_c[i]->SetLineColor(kMagenta);
        }
        h_c[i]->SetMarkerStyle(1);
        h_c[i]->Draw("same");
    }

    c->SetLeftMargin(0.18);  
    c->SetBottomMargin(0.15);
    h1_c->GetYaxis()->SetTitleOffset(2);
    h1_c->GetXaxis()->SetTitleOffset(1.3);

    // legend
    // TLegend *l = new TLegend(0.5,0.6,0.9,0.9);
    TLegend *l = new TLegend(0.2,0.175,0.7,0.45);
    l->SetBorderSize(0);
    l->SetFillStyle(0);
    l->AddEntry((TObject*)0, "akCs4PF", "");
    l->AddEntry((TObject*)0, htitles_byeta[etaindex]+", p_{T} > 20 GeV", "");
    l->AddEntry(h1_c,shiBins[0],"pl");
    for(unsigned int i=1; i<nhiBin; i++){
        l->AddEntry(h_c[i-1],shiBins[i],"pl");
    }

    l->Draw("same");

    // saving
    c->SaveAs(path+hname+".png");

    // deleting
    delete c;
    delete h1_c;
    delete l;
}

void save_pf_overlay(TH1F *h[nmult][netabins][nhiBin], int etaindex, int pfindex, TString xtitle, TString ytitle, TString hname, TString path){

    if(pfindex < 0 || pfindex >= nmult || etaindex < 0 || etaindex >= netabins){cerr << "ERROR: out-of-bounds indices in " << hname << endl;return;}
    for(int i=0; i<nhiBin;i++){
        if(!h[pfindex][etaindex][i]){
            cerr<<"ERROR: null histogram for trigger"<<shiBins[i]<<" in '"<< hname<<"'"<<endl;
            return;
        }
    }

    // canvas
    TCanvas *c = new TCanvas();
    c->SetTitle("");
    c->SetName(hname);
    c->cd();
    c->SetRealAspectRatio();

    // clones of hists
    TH1F *h1_c = (TH1F*)h[pfindex][etaindex][0]->Clone();
    TH1F *h_c[nTrigs-1];
    for(unsigned int i=1; i<nTrigs; i++){
        h_c[i-1] = (TH1F*)h[pfindex][etaindex][i]->Clone();
    }

    // // setting y axis limits
    // h1_c->SetMaximum(0.05);

    // parent histogram (h[0])
    h1_c->Draw("e1p");
    h1_c->SetMarkerStyle(1);
    h1_c->SetMarkerColor(kBlack);
    h1_c->SetLineColor(kBlack);
    h1_c->SetTitle("");
    h1_c->SetName(hname);
    h1_c->GetYaxis()->SetTitle(ytitle);
    h1_c->GetYaxis()->CenterTitle(true);
    h1_c->GetXaxis()->SetTitle(xtitle);
    h1_c->GetXaxis()->CenterTitle(true);

    // other four histograms
    for(unsigned int i=0; i<nTrigs-1; i++){
        if(i==0){
            h_c[i]->SetMarkerColor(kBlue);
            h_c[i]->SetLineColor(kBlue);
        }
        if(i==1){
            h_c[i]->SetMarkerColor(kRed);
            h_c[i]->SetLineColor(kRed);
        }
        if(i==2){
            h_c[i]->SetMarkerColor(kGreen+1);
            h_c[i]->SetLineColor(kGreen+1);
        }
        if(i==3){
            h_c[i]->SetMarkerColor(kMagenta);
            h_c[i]->SetLineColor(kMagenta);
        }
        h_c[i]->SetMarkerStyle(1);
        h_c[i]->Draw("same");
    }

    c->SetLeftMargin(0.18);  
    c->SetBottomMargin(0.15);
    h1_c->GetYaxis()->SetTitleOffset(1.8);
    h1_c->GetXaxis()->SetTitleOffset(1.3);
    
    TString htitles_byeta[3] = {"|#eta| < 1.6", "|#eta| < 2.4", "|#eta| < 5"};

    // legend
    TLegend *l = new TLegend(0.5,0.6,0.9,0.9);
    l->SetBorderSize(0);
    l->SetFillStyle(0);
    l->AddEntry((TObject*)0, "akCs4PF", "");
    l->AddEntry((TObject*)0, htitles_byeta[etaindex]+", p_{T} > 20 GeV", "");
    l->AddEntry(h1_c,shiBins[0],"pl");
    for(unsigned int i=1; i<nhiBin; i++){
        l->AddEntry(h_c[i-1],shiBins[i],"pl");
    }

    l->Draw("same");

    // saving
    c->SaveAs(path+hname+".png");

    // deleting
    delete c;
    delete h1_c;
    delete l;
}
