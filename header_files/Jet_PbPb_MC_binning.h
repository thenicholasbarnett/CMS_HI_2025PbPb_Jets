
// maximum pt of jets to include
const Float_t ptcut = 20.0;

// strings of ttrees and branches of interest //

// ttree names
const Int_t nTTrees = 4;
TString sTTrees[nTTrees] = {"hiEvtAnalyzer/HiTree", "skimanalysis/HltTree", "akCs4PFJetAnalyzer/t", "hltanalysis/HltTree"};

// event
const Int_t nEvtBranch = 3;
TString sEvtBranch[nEvtBranch] = {"weight", "vz", "hiBin"};

// filters
const Int_t nFilters = 2;
TString sFilters[nFilters] = {"pclusterCompatibilityFilter", "pprimaryVertexFilter"};

// jet branches
const Int_t nJetBranch = 15;
TString sJetBranch[nJetBranch] = {"nref", "rawpt", "jtpt", "jteta", "jtphi", "jtPfCHF", "jtPfNHF", "jtPfCEF", "jtPfNEF", "jtPfMUF", "jtPfCHM", "jtPfNHM", "jtPfCEM", "jtPfNEM", "jtPfMUM"};

// declaring strings for naming //

// momenta
const Int_t nmom = 4;
TString smom[nmom] = {"hrawpt","hjtpt","hjteta","hjtphi"};

// fractions
const Int_t nfrac = 5;
TString sfrac[nfrac] = {"hjtPfCHF","hjtPfNHF","hjtPfCEF","hjtPfNEF","hjtPfMUF"};

// multiplicities
const Int_t nmult = 5;
TString smult[nmult] = {"hjtPfCHM","hjtPfNHM","hjtPfCEM","hjtPfNEM","hjtPfMUM"};

// declaring histogram binning //

// vz
const int nvzbins = 40;
const float vzlims[2] = {-20.0, 20.0}; 

// pT
const int nptbins = 100;
const float ptlims[2] = {0.0, 1000.0}; 

//eta
const int nhetabins = 50;
const float etalims[2] = {-5.1, 5.1};

//phi
const int nphibins = 64;
const float philims[2] = {-3.2, 3.2};

// nref
const int nrefbins = 30;
const int nreflims[2] = {0, 30}; 

// trigger decisions
const int ntrigbins = 2;
const int triglims[2] = {0,2};

// pf fractions
const int npfbins = 10;
const float pflims[2] = {0.0, 1.0};

// pf multiplicities
const int npfmbins = 50;
const int pfmlims[2] = {0, 50};

// hiBin
const int nhibins = 200;
const int hibinlims[2] = {0, 200};

// centrality binning
const int nhiBin = 5;
const int nhiBin1 = 6;
int hiBins[nhiBin1] = {0, 20, 60, 100, 160, 200};
int hiBinlo[nhiBin] = {0, 20, 60, 100, 160};
int hiBinhi[nhiBin] = {20, 60, 100, 160, 200};
TString shiBins[nhiBin] = {"0 < hiBin < 20", "20 < hiBin < 60", "60 < hiBin < 100", "100 < hiBin < 160", "160 < hiBin < 200"};
TString htitles_byhibin[nhiBin] = {"_hiBin_0_to_20", "_hiBin_20_to_60", "_hiBin_60_to_100", "_hiBin_100_to_160", "_hiBin_160_to_200"};

// |eta|
const int netabins = 3;
const float etalo[netabins] = {0.0, 0.0, 0.0};
const float etahi[netabins] = {1.6, 2.4, 5.0};
TString htitles_byeta[netabins] = {"|#eta| < 1.6", "|#eta| < 2.4", "|#eta| < 5"};

// momenta
const int nmombins[nmom] = {nptbins, nptbins, nhetabins, nphibins};
const float nmomlo[nmom] = {ptlims[0], ptlims[0], etalims[0], philims[0]};
const float nmomhi[nmom] = {ptlims[1], ptlims[1], etalims[1], philims[1]};