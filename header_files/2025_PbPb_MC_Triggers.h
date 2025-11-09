// // high level triggers
// const Int_t nHLTrigs = 5;
// TString sHLTrigs[nHLTrigs] = {"HLT_HIPuAK4CaloJet40Eta5p1_MinBiasHF1AND_v8", "HLT_HIPuAK4CaloJet60Eta5p1_MinBiasHF1AND_v8", "HLT_HIPuAK4CaloJet80Eta5p1_v16", "HLT_HIPuAK4CaloJet100Eta5p1_v16", "HLT_HIPuAK4CaloJet120Eta5p1_v16"};

// // level 1 triggers
// const int nL1Trigs = 5;
// TString sL1Trigs[nL1Trigs]= {"L1_MinimumBiasHF1_AND_BptxAND","L1_MinimumBiasHF1_AND_BptxAND","L1_SingleJet60_BptxAND","L1_SingleJet60_BptxAND","L1_SingleJet80_BptxAND"};

// number of triggers
const Int_t nhlTrigs = 3;
const Int_t nl1Trigs = 2;
// high level triggers
TString sHLTrigs[nhlTrigs] = {"HLT_HIPuAK4CaloJet80Eta5p1_v16", "HLT_HIPuAK4CaloJet100Eta5p1_v16", "HLT_HIPuAK4CaloJet120Eta5p1_v16"};
TString sHLTrigs_short[nhlTrigs] = {"_HLT_Jet80", "_HLT_Jet100", "_HLT_Jet120"};
// level 1 seeds for hlts above
TString sL1Trigs[nl1Trigs]= {"L1_SingleJet60_BptxAND", "L1_SingleJet80_BptxAND"};
TString sL1Trigs_short[nl1Trigs]= {"_L1_Jet60", "_L1_Jet80"};