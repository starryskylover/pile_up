#include "AtlasStyle.C"
#include "AtlasLabels.C"
#include "AtlasUtils.C"

void pile_up_data(){

SetAtlasStyle();

  Int_t ph_convFlag;
  UInt_t n_ph, n_jet, n_e_looseBL, n_mu, ph_isem;
  Double_t ph_pt, ph_phi, ph_eta, ph_iso_et40, ph_iso_et20, ph_iso_pt, ph_z_point, soft_term_pt;
  Double_t jet_lead_phi,jet_lead_pt, jet_lead_eta, jet_sublead_phi, metTST_pt, metTST_phi, metTSTsignif;
  Double_t error_data;
  Double_t N_data;
  Int_t nbins=100;

  TH1D *hist_data = new TH1D ("hist_data", "hist_data", nbins, -250, 250);

  const char *path = "/home/valerian/programs/R_factor_MC/private/data_PU/data-15-18-reproc-21-02-23-checked_met120.root";

    TFile *data = new TFile(path, "READ");
    TTree *tree = (TTree*)data->Get("output_tree");

    tree->SetBranchAddress("n_ph", &n_ph);
    tree->SetBranchAddress("n_jet", &n_jet);
    tree->SetBranchAddress("n_e_looseBL", &n_e_looseBL);
    tree->SetBranchAddress("n_mu", &n_mu);
    tree->SetBranchAddress("ph_pt",&ph_pt);
    tree->SetBranchAddress("ph_phi",&ph_phi);
    tree->SetBranchAddress("ph_eta",&ph_eta);
    tree->SetBranchAddress("ph_iso_et20", &ph_iso_et20);
    tree->SetBranchAddress("ph_iso_pt", &ph_iso_pt);
    tree->SetBranchAddress("ph_isem", &ph_isem);
    tree->SetBranchAddress("ph_z_point", &ph_z_point);
    tree->SetBranchAddress("jet_lead_phi",&jet_lead_phi);
    tree->SetBranchAddress("jet_lead_pt",&jet_lead_pt);
    tree->SetBranchAddress("jet_lead_eta",&jet_lead_eta);
    tree->SetBranchAddress("metTST_pt", &metTST_pt);
    tree->SetBranchAddress("metTST_phi",&metTST_phi);
    tree->SetBranchAddress("metTSTsignif", &metTSTsignif);
    tree->SetBranchAddress("ph_convFlag", &ph_convFlag);
    tree->SetBranchAddress("soft_term_pt", &soft_term_pt);

    int entry = (int)tree->GetEntries();

    for (int i=0; i<entry; i++){
    tree->GetEntry(i);

    TLorentzVector *v1 = new TLorentzVector();
    TLorentzVector *v2 = new TLorentzVector();
    TLorentzVector *v3 = new TLorentzVector();
    v1->SetPtEtaPhiM(metTST_pt, 0, metTST_phi, 0);
    v2->SetPtEtaPhiM(jet_lead_pt, jet_lead_eta, jet_lead_phi, 0);
    v3->SetPtEtaPhiM(ph_pt, ph_eta, ph_phi, 0);
    Double_t dphi_1=abs((*v1).DeltaPhi(*v3));
    Double_t dphi_2=abs((*v1).DeltaPhi(*v2));

    if (ph_pt <= 150) continue;
    if (n_ph !=1 || n_e_looseBL !=0 || n_mu!=0) continue;
    if (fabs(ph_z_point) > 250) continue;
    if (metTST_pt <=130) continue;
    if (metTSTsignif <= 11) continue;
    if (dphi_1 <= 0.7) continue;
    if (n_jet >= 1 && dphi_2 <= 0.4) continue;
    if (ph_iso_et20/ph_pt >= 0.065) continue;
    if (ph_iso_pt/ph_pt >= 0.05) continue;
    if (ph_convFlag==0 || ph_convFlag==2 || ph_convFlag==4) continue;
    if (ph_isem != 0) continue;
    if (soft_term_pt >= 16) continue;

    hist_data->Fill(ph_z_point, 1.0);
  }

  TFile *file = new TFile ("pile_up_data.root","RECREATE");
  hist_data->Write();
  file->Close();

}
