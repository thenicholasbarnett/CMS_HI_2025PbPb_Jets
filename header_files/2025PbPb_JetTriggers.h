// trigger tree
TString sTrigTree = "akPu4CaloJetAnalyzer/caloJetTree";

// high level triggers
const Int_t nHLTrigs = 5;
TString sHLTrigs[nHLTrigs] = {"HLT_HIPuAK4CaloJet40Eta5p1_MinBiasHF1AND_v8", "HLT_HIPuAK4CaloJet60Eta5p1_MinBiasHF1AND_v8", "HLT_HIPuAK4CaloJet80Eta5p1_v16", "HLT_HIPuAK4CaloJet100Eta5p1_v16", "HLT_HIPuAK4CaloJet120Eta5p1_v16"};

// level 1 triggers
const int nL1Trigs = 5;
TString sL1Trigs[nL1Trigs]= {"L1_MinimumBiasHF1_AND_BptxAND","L1_MinimumBiasHF1_AND_BptxAND","L1_SingleJet60_BptxAND","L1_SingleJet60_BptxAND","L1_SingleJet80_BptxAND"};
