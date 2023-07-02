#include "AtlasStyle.C"
#include "AtlasLabels.C"
#include "AtlasUtils.C"

void pile_up_signal(){

  SetAtlasStyle();

  Int_t mc_ph_type, ph_convFlag;
  UInt_t n_ph, n_jet, n_e_looseBL, n_mu, ph_isem;
  Double_t weight, ph_pt, ph_phi, ph_eta, ph_iso_et20, ph_iso_pt, ph_z_point, soft_term_pt;
  Double_t jet_lead_phi,jet_lead_pt, jet_lead_eta, metTST_pt, metTST_phi, metTSTsignif, koef;
  Double_t error_sig_less10, error_sig_more15, error_sig_more50;
  Double_t N_sig_less10, N_sig_more15, N_sig_more50;
  Double_t L_a = 36646.74, L_d = 44630.6, L_e = 58791.6, L_j;
  Int_t nbins=100;

  TH1D *hist_signal= new TH1D ("hist_signal", "hist_signal", nbins, -250, 250);

    // const char *path = "/home/valerian/programs/R_factor_MC/private/Znunu_301910";
    const char *path = "/home/valerian/programs/R_factor_MC/private/nabor_364519";
    const char *year[] = {"/user.akurova.a.MxAOD.root","/user.akurova.d.MxAOD.root","/user.akurova.e.MxAOD.root"};

      for (int j = 0; j <= 2; j++) {
      char *sig= new char[strlen(path) + strlen(year[j]) + 1];
      strcpy(sig,path);
      strcat(sig,year[j]);

      TFile *sig_MC = new TFile(sig, "READ");
      TTree *tree = (TTree*)sig_MC->Get("output_tree");
      TTree *tree_koef= (TTree*)sig_MC->Get("norm_tree");
      TTree *tree_sum_w = (TTree*)sig_MC->Get("output_tree_sw");

      Double_t sumw = 0;
      Double_t sum_of_weights_bk_xAOD;

      tree_sum_w->SetBranchAddress("sum_of_weights_bk_xAOD",&sum_of_weights_bk_xAOD);

      int entry = (int)tree_sum_w->GetEntries();
      for (int k=0; k<entry; k++)
      {
        tree_sum_w->GetEntry(k);
        sumw += sum_of_weights_bk_xAOD;
      }

      tree->SetBranchAddress("n_ph", &n_ph);
      tree->SetBranchAddress("n_jet", &n_jet);
      tree->SetBranchAddress("n_e_looseBL", &n_e_looseBL);
      tree->SetBranchAddress("n_mu", &n_mu);
      tree->SetBranchAddress("weight", &weight);
      tree->SetBranchAddress("ph_pt",&ph_pt);
      tree->SetBranchAddress("ph_phi",&ph_phi);
      tree->SetBranchAddress("ph_eta",&ph_eta);
      tree->SetBranchAddress("ph_iso_et20",&ph_iso_et20);
      tree->SetBranchAddress("ph_iso_pt", &ph_iso_pt);
      tree->SetBranchAddress("ph_isem", &ph_isem);
      tree->SetBranchAddress("ph_z_point", &ph_z_point);
      tree->SetBranchAddress("jet_lead_phi",&jet_lead_phi);
      tree->SetBranchAddress("jet_lead_pt",&jet_lead_pt);
      tree->SetBranchAddress("jet_lead_eta",&jet_lead_eta);
      tree->SetBranchAddress("metTST_pt", &metTST_pt);
      tree->SetBranchAddress("metTST_phi",&metTST_phi);
      tree->SetBranchAddress("metTSTsignif", &metTSTsignif);
      tree->SetBranchAddress("mc_ph_type", &mc_ph_type);
      tree->SetBranchAddress("ph_convFlag", &ph_convFlag);
      tree->SetBranchAddress("soft_term_pt", &soft_term_pt);


      tree_koef->SetBranchAddress("koef", &koef);
      int Num_koef = (int)tree_koef->GetEntries();
       for (int g=0; g<Num_koef; g++){
          tree_koef->GetEntry(g);
       }

    int Num_tree = (int)tree->GetEntries();

    for (int i=0; i<Num_tree; i++){
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
      if (n_ph !=1 || n_e_looseBL !=0 || n_mu !=0) continue;
      if (fabs(ph_z_point) >= 250) continue;
      if (metTST_pt <=130) continue;
      if (metTSTsignif <= 11) continue;
      if (dphi_1 <= 0.7) continue;
      if (n_jet >= 1 && dphi_2 <= 0.4) continue;
      if (ph_isem != 0) continue;
      if (ph_iso_et20/ph_pt >= 0.065) continue;
      if (ph_iso_pt/ph_pt >= 0.05) continue;
      if (ph_convFlag==0 || ph_convFlag==2 || ph_convFlag==4) continue;
      if (soft_term_pt >= 16) continue;

      (j == 0) ? L_j=L_a : (j == 1) ? L_j=L_d : L_j=L_e;
      Double_t norm_koef=koef*L_j/sumw;

      hist_signal->Fill(ph_z_point, weight*norm_koef);
      }
   }

    // TFile *file = new TFile ("pile_up_signal_301910.root","RECREATE");
    // hist_signal->Write();
    // file->Close();

    TFile *file = new TFile ("pile_up_signal_364519.root","RECREATE");
    hist_signal->Write();
    file->Close();
}
