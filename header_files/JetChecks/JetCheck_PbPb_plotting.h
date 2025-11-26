
#include "Jet_PbPb_DATA_binning.h"

/// file paths
// non-overlay
TString path_mom = "plots/individual/momenta/";
TString path_ep = "plots/individual/eta_phi/";
TString path_frac = "plots/individual/fractions/";
// overlay
TString path_ovr_mom = "plots/overlays/momenta/";
TString path_ovr_frac = "plots/overlays/fractions/";
// ratios
TString pathr_mom = "plots/ratio/individual/momenta/";
TString pathr_ep = "plots/ratio/individual/eta_phi/";
TString pathr_frac = "plots/ratio/individual/fractions/";
TString pathr_ovr_mom = "plots/ratio/overlays/momenta/";
TString pathr_ovr_frac = "plots/ratio/overlays/fractions/";
    
// declaring strings //

// histogram names
TString htitles_mom_name[nmom] = {"raw_jet_pt", "jet_pt", "jet_eta", "jet_phi"};
TString htitles_frac_name[nfrac] = {"Charged_Hadron_Fraction", "Neutral_Hadron_Fraction", "Charged_Electromagnetic_Fraction", "Neutral_Electromagnetic_Fraction", "Muon_Fraction"};

// x axis titles
TString htitles_mom_xaxis[nmom] = {"p_{T}^{raw}", "p_{T}^{jet}", "#eta^{jet}", "#phi^{jet}"};
TString htitles_frac_xaxis[nfrac] = {"CHF", "NHF", "CEF", "NEF", "MUF"};

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

void save_2df(TH2F* h, TString xtitle, TString ytitle, TString htitle, TString hname, TString path){

    // canvas
    TCanvas *c = new TCanvas();
    c->SetTitle("");
    c->SetName(hname);
    c->cd();
    // c->SetLogy();
    c->SetRealAspectRatio();

    // clone of hist
    TH2F *h_c = (TH2F*)h->Clone(hname);

    // markers
    h_c->GetZaxis()->SetRangeUser(0.0, 0.001);
    h_c->Draw("colz");
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

    // saving
    c->SaveAs(path+hname+".png");

    // deleting
    delete c;
    delete h_c;
    // delete l;
}

void save_mom_overlay(TH1F *h[2][nmom][nptcuts][netabins][nhiBin], int ptindex, int etaindex, int momindex, TString xtitle, TString ytitle, TString hname, TString path){

    // canvas
    TCanvas *c = new TCanvas();
    c->SetTitle("");
    c->SetName(hname);
    c->cd();
    if((xtitle=="p_{T}^{raw}")||(xtitle=="p_{T}^{jet}")){c->SetLogy();}
    if((xtitle=="p_{T}^{raw}")||(xtitle=="p_{T}^{jet}")){c->SetLogx();}
    c->SetRealAspectRatio();

    // clones of hists
    TH1F *h1_c = (TH1F*)h[0][momindex][ptindex][etaindex][0]->Clone();
    TH1F *h_c[nhiBin-1];
    for(unsigned int i=1; i<nhiBin; i++){
        h_c[i-1] = (TH1F*)h[0][momindex][ptindex][etaindex][i]->Clone();
    }

    // // setting y axis limits
    if(xtitle=="#eta^{jet}"){h1_c->SetMaximum(0.1);}
    if(xtitle=="#eta^{jet}"){h1_c->SetMinimum(0.0);}
    if(xtitle=="#phi^{jet}"){h1_c->SetMaximum(0.05);}
    if(xtitle=="#phi^{jet}"){h1_c->SetMinimum(0.0);}
    if((xtitle=="p_{T}^{raw}")||(xtitle=="p_{T}^{jet}")){h1_c->GetXaxis()->SetRangeUser(ptcuts[ptindex],1000);}

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
    for(unsigned int i=0; i<nhiBin-1; i++){
        if(i==3){continue;}
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

    float x0 = 0.5;
    float x1 = 0.9;
    float y0 = 0.6;
    float y1 = 0.9;
    if(xtitle=="#eta^{jet}"){
        x0 = 0.2;
        x1 = 0.7;
        y0 = 0.175;
        y1 = 0.45;
    }
    // legend
    TLegend *l = new TLegend(x0,y0,x1,y1);
    // TLegend *l = new TLegend(0.2,0.175,0.7,0.45);
    l->SetBorderSize(0);
    l->SetFillStyle(0);
    l->AddEntry((TObject*)0, "akCs4PF", "");
    l->AddEntry((TObject*)0, sptcuts[ptindex], "");
    l->AddEntry((TObject*)0, sEtaBins[etaindex], "");
    l->AddEntry(h1_c,shiBins[0],"pl");
    for(unsigned int i=1; i<nhiBin; i++){
        if(i==(nhiBin-1)){continue;}
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

void save_momr_overlay(TH1F *h[nmom][nptcuts][netabins][nhiBin], int ptindex, int etaindex, int momindex, TString xtitle, TString ytitle, TString hname, TString path){

    // canvas
    TCanvas *c = new TCanvas();
    c->SetTitle("");
    c->SetName(hname);
    c->cd();
    if((xtitle=="p_{T}^{raw}")||(xtitle=="p_{T}^{jet}")){c->SetLogx();}
    c->SetRealAspectRatio();

    // clones of hists
    TH1F *h1_c = (TH1F*)h[momindex][ptindex][etaindex][0]->Clone();
    TH1F *h_c[nhiBin-1];
    for(unsigned int i=1; i<nhiBin; i++){
        h_c[i-1] = (TH1F*)h[momindex][ptindex][etaindex][i]->Clone();
    }

    // // setting y axis limits
    if(xtitle=="#eta^{jet}"){h1_c->SetMaximum(1.2);}
    if(xtitle=="#eta^{jet}"){h1_c->SetMinimum(0.8);}
    if(xtitle=="#phi^{jet}"){h1_c->SetMaximum(1.5);}
    if(xtitle=="#phi^{jet}"){h1_c->SetMinimum(0.5);}
    if((xtitle=="p_{T}^{raw}")||(xtitle=="p_{T}^{jet}")){h1_c->SetMaximum(5);}
    if((xtitle=="p_{T}^{raw}")||(xtitle=="p_{T}^{jet}")){h1_c->SetMinimum(0);}
    if((xtitle=="p_{T}^{raw}")||(xtitle=="p_{T}^{jet}")){h1_c->GetXaxis()->SetRangeUser(ptcuts[ptindex],1000);}

    // tline
    int binxmax = h1_c->FindLastBinAbove(h1_c->GetBinLowEdge(1));
    float linexmax = h1_c->GetBinLowEdge(binxmax)+h1_c->GetBinWidth(binxmax);
    float linexmin = h1_c->GetBinLowEdge(1);
    if((xtitle=="p_{T}^{raw}")||(xtitle=="p_{T}^{jet}")){linexmin=ptlims[0];linexmax=ptlims[1];}
    if(xtitle=="#eta^{jet}"){linexmin=etalims[0];linexmax=etalims[1];}
    if(xtitle=="#phi^{jet}"){linexmin=philims[0];linexmax=philims[1];}
    TLine *line1 = new TLine(linexmin,1,linexmax,1);
    line1->SetLineWidth(1);
    line1->SetLineColor(kBlack);
    line1->SetLineStyle(2);

    // parent histogram (h[0])
    h1_c->Draw("e1p");
    line1->Draw("same");
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
    for(unsigned int i=0; i<nhiBin-1; i++){
        if(i==3){continue;}
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
    // TLegend *l = new TLegend(0.2,0.175,0.7,0.45);
    TLegend *l = new TLegend(0.2,0.65,0.7,0.85);
    l->SetBorderSize(0);
    l->SetFillStyle(0);
    l->AddEntry((TObject*)0, "akCs4PF", "");
    l->AddEntry((TObject*)0, sptcuts[ptindex], "");
    l->AddEntry((TObject*)0, sEtaBins[etaindex], "");
    l->AddEntry(h1_c,shiBins[0],"pl");
    for(unsigned int i=1; i<nhiBin; i++){
        if(i==(nhiBin-1)){continue;}
        l->AddEntry(h_c[i-1],shiBins[i],"pl");
    }

    l->Draw("same");

    // saving
    c->SaveAs(path+hname+".png");

    // deleting
    delete c;
    delete h1_c;
    delete l;
    delete line1;
}

void save_pf_overlay(TH1F *h[2][nfrac][nptcuts][netabins][nhiBin], int ptindex, int etaindex, int pfindex, TString xtitle, TString ytitle, TString hname, TString path){

    // canvas
    TCanvas *c = new TCanvas();
    c->SetTitle("");
    c->SetName(hname);
    c->cd();
    c->SetRealAspectRatio();

    // clones of hists
    TH1F *h1_c = (TH1F*)h[0][pfindex][ptindex][etaindex][0]->Clone();
    TH1F *h_c[nhiBin-1];
    for(unsigned int i=1; i<nhiBin; i++){
        h_c[i-1] = (TH1F*)h[0][pfindex][ptindex][etaindex][i]->Clone();
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
    if((xtitle=="MUF")||(xtitle=="CEF")||(xtitle=="NHF")){c->SetLogy();}

    // other four histograms
    for(unsigned int i=0; i<nhiBin-1; i++){
        if(i==3){continue;}
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

    // legend
    float x0 = 0.5;
    float x1 = 0.9;
    float y0 = 0.6;
    float y1 = 0.9;
    if(xtitle=="CHF"){x0=0.2;x1=0.5;}
    TLegend *l = new TLegend(x0,y0,x1,y1);
    l->SetBorderSize(0);
    l->SetFillStyle(0);
    l->AddEntry((TObject*)0, "akCs4PF", "");
    l->AddEntry((TObject*)0, sptcuts[ptindex], "");
    l->AddEntry((TObject*)0, sEtaBins[etaindex], "");
    l->AddEntry(h1_c,shiBins[0],"pl");
    for(unsigned int i=1; i<nhiBin; i++){
        if(i==(nhiBin-1)){continue;}
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

void save_pfr_overlay(TH1F *h[nfrac][nptcuts][netabins][nhiBin], int ptindex, int etaindex, int pfindex, TString xtitle, TString ytitle, TString hname, TString path){

    // canvas
    TCanvas *c = new TCanvas();
    c->SetTitle("");
    c->SetName(hname);
    c->cd();
    c->SetRealAspectRatio();

    // clones of hists
    TH1F *h1_c = (TH1F*)h[pfindex][ptindex][etaindex][0]->Clone();
    TH1F *h_c[nhiBin-1];
    for(unsigned int i=1; i<nhiBin; i++){
        h_c[i-1] = (TH1F*)h[pfindex][ptindex][etaindex][i]->Clone();
    }

    // // setting y axis limits
    // h1_c->SetMaximum(0.05);

    // tline
    int binxmax = h1_c->FindLastBinAbove(h1_c->GetBinLowEdge(1));
    float linexmax = h1_c->GetBinLowEdge(binxmax)+h1_c->GetBinWidth(binxmax);
    float linexmin = h1_c->GetBinLowEdge(1);
    if((xtitle=="CHF")||(xtitle=="CEF")||(xtitle=="NHF")||(xtitle=="NEF")||(xtitle=="MUF")){linexmin=0;linexmax=1;}
    TLine *line1 = new TLine(linexmin,1,linexmax,1);
    line1->SetLineWidth(1);
    line1->SetLineColor(kBlack);
    line1->SetLineStyle(2);

    // parent histogram (h[0])
    h1_c->Draw("e1p");
    line1->Draw("same");
    if((xtitle=="NHF")||(xtitle=="NEF")||(xtitle=="CHF")){h1_c->GetYaxis()->SetRangeUser(0.8,1.2);}
    // if((xtitle=="MUF")||(xtitle=="CEF")){h1_c->GetYaxis()->SetRangeUser(0.0,2.0);}
    if(xtitle=="MUF"){h1_c->GetYaxis()->SetRangeUser(0.0,2.0);}
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
    for(unsigned int i=0; i<nhiBin-1; i++){
        if(i==3){continue;}
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

    // legend
    float x0 = 0.5;
    float x1 = 0.9;
    float y0 = 0.6;
    float y1 = 0.9;
    if((xtitle=="NHF")||(xtitle=="NEF")){x0=0.2;x1=0.5;y0=0.2;y1=0.5;}
    TLegend *l = new TLegend(x0,y0,x1,y1);
    l->SetBorderSize(0);
    l->SetFillStyle(0);
    l->AddEntry((TObject*)0, "akCs4PF", "");
    l->AddEntry((TObject*)0, sptcuts[ptindex], "");
    l->AddEntry((TObject*)0, sEtaBins[etaindex], "");
    l->AddEntry(h1_c,shiBins[0],"pl");
    for(unsigned int i=1; i<nhiBin; i++){
        if(i==(nhiBin-1)){continue;}
        l->AddEntry(h_c[i-1],shiBins[i],"pl");
    }

    l->Draw("same");

    // saving
    c->SaveAs(path+hname+".png");

    // deleting
    delete c;
    delete h1_c;
    delete l;
    delete line1;
}
