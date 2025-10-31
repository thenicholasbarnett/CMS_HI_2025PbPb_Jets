
#include "JetCheck_lowPUpp_binning.h"

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

void save_2d_bytrig1(TH2F *h[3], int etaindex, TString xtitle, TString ytitle, TString htitle, TString hname, TString path){

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

void save_2d_bytrig2(TH2F *h[3][4], int etaindex, int trigindex, TString xtitle, TString ytitle, TString htitle, TString hname, TString path){

    // canvas
    TCanvas *c = new TCanvas();
    c->SetTitle("");
    c->SetName(hname);
    c->cd();
    // c->SetLogy();
    c->SetRealAspectRatio();

    // clone of hist
    TH2F *h_c = (TH2F*)h[etaindex][trigindex]->Clone(hname);

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

void save_mom_overlay(TH1F *h[nmom][netabins][nTrigs], int etaindex, int momindex, TString xtitle, TString ytitle, TString hname, TString path){
// void save_mom_overlay(TH1F *(*h)[netabins][nTrigs], int etaindex, int momindex, TString xtitle, TString ytitle, TString hname, TString path){

    if(momindex < 0 || momindex >= nmom || etaindex < 0 || etaindex >= netabins){cerr << "ERROR: out-of-bounds indices in " << hname << endl;return;}
    for(int i=0; i<4;i++){
        if(!h[momindex][etaindex][i]){
            cerr<<"ERROR: null histogram for trigger"<<sTrigs[i]<<" in '"<< hname<<"'"<<endl;
            return;
        }
    }

    // canvas
    TCanvas *c = new TCanvas();
    c->SetTitle("");
    c->SetName(hname);
    c->cd();
    if((xtitle=="p_{T}^{raw}")||(xtitle=="p_{T}^{jet}")){c->SetLogy();}
    // if((xtitle=="p_{T}^{raw}")||(xtitle=="p_{T}^{jet}")){c->SetLogx();}
    c->SetRealAspectRatio();

    // clones of hists
    TH1F *h1_c = (TH1F*)h[momindex][etaindex][0]->Clone();
    TH1F *h_c[3];
    for(unsigned int i=1; i<4; i++){
        h_c[i-1] = (TH1F*)h[momindex][etaindex][i]->Clone();
    }

    // // setting y axis limits
    // h1_c->SetMaximum(0.05);
    // if(xtitle=="#eta^{jet}"){h1_c->SetMaximum(0.07);}
    // if(xtitle=="#phi^{jet}"){h1_c->SetMaximum(0.04);}
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
        h_c[i]->SetMarkerStyle(1);
        h_c[i]->Draw("same");
    }
    
    TString htitles_byeta[3] = {"|#eta| < 1.6", "|#eta| < 2.4", "|#eta| < 5"};

    // legend
    TLegend *l = new TLegend(0.5,0.6,0.9,0.9);
    l->SetBorderSize(0);
    l->SetFillStyle(0);
    l->AddEntry(h1_c,sTrigs[0],"pl");
    for(unsigned int i=1; i<nTrigs; i++){
        l->AddEntry(h_c[i-1],sTrigs[i],"pl");
    }
    l->AddEntry((TObject*)0, "ak4PF", "");
    l->AddEntry((TObject*)0, htitles_byeta[etaindex], "");

    l->Draw("same");

    // saving
    c->SaveAs(path+hname+".png");

    // deleting
    delete c;
    delete h1_c;
    delete l;
}

void save_pf_overlay(TH1F *h[nmult][netabins][nTrigs], int etaindex, int pfindex, TString xtitle, TString ytitle, TString hname, TString path){
// void save_pf_overlay(TH1F *(*h)[netabins][nTrigs], int etaindex, int pfindex, TString xtitle, TString ytitle, TString hname, TString path){

    if(pfindex < 0 || pfindex >= nmult || etaindex < 0 || etaindex >= netabins){cerr << "ERROR: out-of-bounds indices in " << hname << endl;return;}
    for(int i=0; i<4;i++){
        if(!h[pfindex][etaindex][i]){
            cerr<<"ERROR: null histogram for trigger"<<sTrigs[i]<<" in '"<< hname<<"'"<<endl;
            return;
        }
    }

    // canvas
    TCanvas *c = new TCanvas();
    c->SetTitle("");
    c->SetName(hname);
    c->cd();
    if((xtitle=="p_{T}^{raw}")||(xtitle=="p_{T}^{jet}")){c->SetLogy();}
    // if((xtitle=="p_{T}^{raw}")||(xtitle=="p_{T}^{jet}")){c->SetLogx();}
    c->SetRealAspectRatio();

    // clones of hists
    TH1F *h1_c = (TH1F*)h[pfindex][etaindex][0]->Clone();
    TH1F *h_c[3];
    for(unsigned int i=1; i<4; i++){
        h_c[i-1] = (TH1F*)h[pfindex][etaindex][i]->Clone();
    }

    // // setting y axis limits
    // h1_c->SetMaximum(0.05);
    // if(xtitle=="#eta^{jet}"){h1_c->SetMaximum(0.07);}
    // if(xtitle=="#phi^{jet}"){h1_c->SetMaximum(0.04);}
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
        h_c[i]->SetMarkerStyle(1);
        h_c[i]->Draw("same");
    }
    
    TString htitles_byeta[3] = {"|#eta| < 1.6", "|#eta| < 2.4", "|#eta| < 5"};

    // legend
    TLegend *l = new TLegend(0.5,0.6,0.9,0.9);
    l->SetBorderSize(0);
    l->SetFillStyle(0);
    l->AddEntry(h1_c,sTrigs[0],"pl");
    for(unsigned int i=1; i<nTrigs; i++){
        l->AddEntry(h_c[i-1],sTrigs[i],"pl");
    }
    l->AddEntry((TObject*)0, "ak4PF", "");
    l->AddEntry((TObject*)0, htitles_byeta[etaindex], "");

    l->Draw("same");

    // saving
    c->SaveAs(path+hname+".png");

    // deleting
    delete c;
    delete h1_c;
    delete l;
}
