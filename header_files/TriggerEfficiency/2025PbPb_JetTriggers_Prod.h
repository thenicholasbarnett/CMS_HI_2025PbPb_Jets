// trigger tree
TString sTrigTree = "hltanalysis/HltTree";

// high level triggers
const Int_t nhlTrigs = 5;
TString sHLTrigs[nhlTrigs] = {"HLT_HIPuAK4CaloJet40Eta5p1_MinBiasHF1AND_ZDC1nOR_v7","HLT_HIPuAK4CaloJet60Eta5p1_MinBiasHF1AND_ZDC1nOR_v7","HLT_HIPuAK4CaloJet60Eta5p1_MinBiasHF1AND_v8","HLT_HIPuAK4CaloJet80Eta5p1_v16","HLT_HIPuAK4CaloJet100Eta5p1_v16","HLT_HIPuAK4CaloJet120Eta5p1_v16"};
TString sHLTrigs_short[nhlTrigs] = {"_HLT_Jet40", "_HLT_Jet60", "_HLT_Jet80", "_HLT_Jet100", "_HLT_Jet120"};
float HLT_Thresh[nhlTrigs] = {40.0, 60.0, 80.0, 100.0, 120.0};
const int L1SeedHLT[nhlTrigs] = {0,0,1,1,2};

// level 1 trigger seeds for HLT
const int nl1Trigs = 3;
TString sL1Trigs[nl1Trigs]= {"L1_MinimumBiasZDC1n_Th1_OR_MinimumBiasHF1_AND_BptxAND","L1_SingleJet60_BptxAND","L1_SingleJet80_BptxAND"};
TString sL1Trigs_short[nl1Trigs] = {"_L1_MinBias", "_L1_Jet60", "_L1_Jet80"};

// HLT Object trees
TString sHLTObjDir = "hltobject/";
TString sHLTObjTrees[nhlTrigs] = {sHLTObjDir+sHLTrigs[0], sHLTObjDir+sHLTrigs[1], sHLTObjDir+sHLTrigs[2], sHLTObjDir+sHLTrigs[3], sHLTObjDir+sHLTrigs[4]};

// hlt object branches
const Int_t nHLTObjBranch = 3;
TString sHLTObjBranch[nHLTObjBranch] = {"pt", "eta", "phi"};