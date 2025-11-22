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

// triggers of interest
const Int_t nTrigs = 4;
TString sTrigs[nTrigs] = {"HLT_PFJet40_L1Jet24_v1", "HLT_PFJet80_L1SingleJet60_v1", "HLT_PFJet110_v16", "HLT_PFJet140_v35"};
TString sTrigs_short[nTrigs] = {"_HLT_jet40", "_HLT_jet80", "_HLT_jet110", "_HLT_jet140"};

// declaring binning //

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
const int npfbins = 100;
const float pflims[2] = {0.0, 1.0};

// pf multiplicities
const int npfmbins = 50;
const int pfmlims[2] = {0, 50};

// |eta|
const int netabins = 3;
const float etalo[netabins] = {0, 0, 0};
const float etahi[netabins] = {1.6, 2.4, 5};

// momenta
const int nmombins[nmom] = {nptbins, nptbins, nhetabins, nphibins};
const float nmomlo[nmom] = {ptlims[0], ptlims[0], etalims[0], philims[0]};
const float nmomhi[nmom] = {ptlims[1], ptlims[1], etalims[1], philims[1]};

// declaring legend boundaries //
const float legxmin = 0.1;
const float legxmax = 0.9;
const float legymin = 0.72;
const float legymax = 0.9;

