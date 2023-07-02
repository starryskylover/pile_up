#include "AtlasStyle.C"
#include "AtlasLabels.C"
#include "AtlasUtils.C"


void pile_up(){
  SetAtlasStyle();

  Int_t mc_ph_type, ph_convFlag;
  UInt_t n_ph, n_jet, n_e_looseBL, n_mu, ph_isem;
  Double_t weight, ph_pt, ph_phi, ph_eta, ph_iso_et20, ph_iso_pt, ph_z_point, soft_term_pt;
  Double_t jet_lead_phi,jet_lead_pt, jet_lead_eta, metTST_pt, metTST_phi, metTSTsignif, koef;
  Double_t error_gamma_jet, error_ttgamma, error_Wgamma, error_Zll_gamma, error_egamma, error_jet_gamma, error_data_excl_bkg, error_signal_301910, error_signal_364519, error_data;
  Double_t N_gamma_jet, N_ttgamma, N_Wgamma, N_Zll_gamma, N_egamma, N_jet_gamma, N_data_excl_bkg, N_signal_301910, N_signal_364519, N_data;
  Double_t L_a = 36646.74, L_d = 44630.6, L_e = 58791.6, L_j;
  Int_t nbins=100;

  TH1D *hist_gamma_jet= new TH1D ("hist_gamma_jet", "hist_gamma_jet", nbins, -250, 250);
  TH1D *hist_ttgamma = new TH1D ("hist_ttgamma", "hist_ttgamma", nbins, -250, 250);
  TH1D *hist_Wgamma = new TH1D ("hist_Wgamma", "hist_Wgamma", nbins, -250, 250);
  TH1D *hist_Zll_gamma = new TH1D ("hist_Zll_gamma", "hist_Zll_gamma", nbins, -250, 250);
  TH1D *hist_egamma = new TH1D ("hist_egamma", "hist_egamma", nbins, -250, 250);


  const char *path1 = "/home/valerian/programs/pile_up/ShapeZj_DeltaZ.root";
  const char *path2 = "/home/valerian/programs/pile_up/pile_up_data.root";
  const char *path3 = "/home/valerian/programs/pile_up/pile_up_signal_301910.root";
  const char *path4 = "/home/valerian/programs/pile_up/pile_up_signal_364519.root";

  TFile *file1 = new TFile(path1, "READ");
  TFile *file2 = new TFile(path2, "READ");
  TFile *file3 = new TFile(path3, "READ");
  TFile *file4 = new TFile(path4, "READ");
  TH1D *hist_jet_gamma=(file1->Get<TH1D>("ph_z_point"));
  TH1D *hist_data=(file2->Get<TH1D>("hist_data"));
  TH1D *hist_signal_301910=(file3->Get<TH1D>("hist_signal"));
  TH1D *hist_signal_364519=(file4->Get<TH1D>("hist_signal"));

  const char *path = "/home/valerian/programs/R_factor_MC/private/";
  const char *nabor[] = {"gamma_jet_361045","gamma_jet_361046","gamma_jet_361047","gamma_jet_361048","gamma_jet_361049","gamma_jet_361050","gamma_jet_361051","gamma_jet_361052","gamma_jet_361053","gamma_jet_361054","gamma_jet_361055","gamma_jet_361056",
  "ttgamma_410389",
  "Wgamma_QCD_364525","Wgamma_QCD_364530", "Wgamma_QCD_364535",
  "Wgamma_EWK_361273","Wgamma_EWK_361274","Wgamma_EWK_361275",
  "Zll_gamma_364504","Zll_gamma_364509","Zll_gamma_364514",
  "egamma_308096","egamma_364170","egamma_364171","egamma_364172","egamma_364173","egamma_364174","egamma_364175","egamma_364176","egamma_364177","egamma_364178","egamma_364179","egamma_364180","egamma_364181","egamma_364182","egamma_364183",
  "egamma_410645","egamma_410644","egamma_410470","egamma_700344","egamma_700345","egamma_700346"};

  for (int l = 0; l <= 42; l++) {
  char *Nabor = new char[strlen(path) + strlen(nabor[l]) + 1];
  strcpy(Nabor, path);
  strcat(Nabor, nabor[l]);

  const char *year[] = {"/user.akurova.a.MxAOD.root","/user.akurova.d.MxAOD.root","/user.akurova.e.MxAOD.root"};
 //  int n = sizeof(year)/sizeof(year[0]);
    for (int j = 0; j <= 2; j++) {
    char *bac= new char[strlen(Nabor) + strlen(year[j]) + 1];
    strcpy(bac,Nabor);
    strcat(bac,year[j]);

    TFile *bac_MC = new TFile(bac, "READ");
    TTree *tree = (TTree*)bac_MC->Get("output_tree");
    TTree *tree_koef= (TTree*)bac_MC->Get("norm_tree");
    TTree *tree_sum_w = (TTree*)bac_MC->Get("output_tree_sw");

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

       (j == 0) ? L_j=L_a : (j == 1) ? L_j=L_d : L_j=L_e;
       Double_t norm_koef=koef*L_j/sumw;

       if (l>=0 && l<=11) hist_gamma_jet->Fill(ph_z_point, weight*norm_koef*0.733);
       if (l==12) hist_ttgamma->Fill(ph_z_point, weight*norm_koef);
       if (l>=13 && l<=18) hist_Wgamma->Fill(ph_z_point, weight*norm_koef);
       if (l>=19 && l<=21) hist_Zll_gamma->Fill(ph_z_point, weight*norm_koef);
       if (l>=22 && l<=42) hist_egamma->Fill(ph_z_point, weight*norm_koef);

        }
      }
    }

    hist_egamma -> Scale(1989/hist_egamma->Integral());
    for(int k = 1; k <= nbins; k++) hist_egamma->SetBinError(k,hist_egamma->GetBinError(k)*0.029);

    N_gamma_jet=hist_gamma_jet->IntegralAndError(1, nbins, error_gamma_jet, "");
    N_ttgamma=hist_ttgamma->IntegralAndError(1, nbins, error_ttgamma, "");
    N_Wgamma=hist_Wgamma->IntegralAndError(1, nbins, error_Wgamma, "");
    N_Zll_gamma=hist_Zll_gamma->IntegralAndError(1, nbins, error_Zll_gamma, "");
    N_egamma=hist_egamma->IntegralAndError(1, nbins, error_egamma, "");
    N_jet_gamma=hist_jet_gamma->IntegralAndError(1, nbins, error_jet_gamma, "");
    N_data=hist_data->IntegralAndError(1, nbins, error_data, "");
    N_signal_301910=hist_signal_301910->IntegralAndError(1, nbins, error_signal_301910, "");
    N_signal_364519=hist_signal_364519->IntegralAndError(1, nbins, error_signal_364519, "");

    std::cout << "N_gamma_jet= " << N_gamma_jet << " +- " << error_gamma_jet << '\n';
    std::cout << "" << '\n';

    std::cout << "N_ttgamma= " << N_ttgamma << " +- " << error_ttgamma << '\n';
    std::cout << "" << '\n';

    std::cout << "N_Wgamma= " << N_Wgamma << " +- " << error_Wgamma << '\n';
    std::cout << "" << '\n';

    std::cout << "N_Zll_gamma= " << N_Zll_gamma << " +- " << error_Zll_gamma << '\n';
    std::cout << "" << '\n';

    std::cout << "N_egamma= " << N_egamma << " +- " << error_egamma << '\n';
    std::cout << "" << '\n';

    std::cout << "N_jet_gamma= " << N_jet_gamma << " +- " << error_jet_gamma << '\n';
    std::cout << "" << '\n';

    std::cout << "N_data= " << N_data << " +- " << error_data << '\n';
    std::cout << "" << '\n';

    std::cout << "N_signal_301910= " << N_signal_301910 << " +- " << error_signal_301910 << '\n';
    std::cout << "" << '\n';

    std::cout << "N_signal_364519= " << N_signal_364519 << " +- " << error_signal_364519 << '\n';
    std::cout << "" << '\n';

    hist_data->Add(hist_gamma_jet, -1);
    hist_data->Add(hist_ttgamma, -1);
    hist_data->Add(hist_Wgamma, -1);
    hist_data->Add(hist_Zll_gamma, -1);
    hist_data->Add(hist_egamma, -1);
    hist_data->Add(hist_jet_gamma, -1);

    N_data_excl_bkg=hist_data->IntegralAndError(1, nbins, error_data_excl_bkg, "");

    std::cout << "N_data_excl_bkg= " << N_data_excl_bkg << " +- " << error_data_excl_bkg << '\n';
    std::cout << "" << '\n';

    TCanvas *c1=new TCanvas("301910","301910");
    c1->SetLogy(1);
    c1->SetCanvasSize(900,700);
    c1->cd();
    gStyle->SetErrorX(0);
    hist_data->GetXaxis()->SetTitle("#Deltaz [mm]");
    hist_data->GetYaxis()->SetTitle("Events / 5 mm");
    hist_data->GetXaxis()->SetTitleOffset(1.1);
    hist_data->GetYaxis()->SetTitleOffset(1.1);
    hist_data->SetMinimum(0.05);
    hist_data->SetMarkerStyle(8);
    hist_data->SetMarkerSize(1);
    hist_data->SetMarkerColor(kBlack);

    hist_signal_301910->SetLineStyle(1);
    hist_signal_301910->SetLineColor(kRed-7);
    hist_signal_301910->SetLineWidth(1);

    hist_data->Draw("PE");
    hist_signal_301910->Draw("HISTsame");

    TLegend *leg1 = new TLegend();
    leg1->SetBorderSize(0);
    leg1->AddEntry(hist_data,"Data");
    leg1->AddEntry(hist_signal_301910, "Z(#nu#bar{#nu})#gamma", "f");
    leg1->Draw();

    TLatex* latex1=new TLatex();
    latex1->SetTextSize(0.04);
    latex1->DrawLatex(-220,122.917,"#bf{#it{ATLAS}} Internal");
    latex1->DrawLatex(-220,208.716,"#sqrt{s}=13 TeV, 140 fb^{-1}");
    latex1->DrawLatex(-220,129.888,"SR");
    latex1->DrawLatex(-220,164,"N_{jets} #geq 0");

    TCanvas *c2=new TCanvas("364519","364519");
    c2->SetLogy(1);
    c2->SetCanvasSize(900,700);
    c2->cd();
    gStyle->SetErrorX(0);
    hist_data->GetXaxis()->SetTitle("#Deltaz [mm]");
    hist_data->GetYaxis()->SetTitle("Events / 5 mm");
    hist_data->GetXaxis()->SetTitleOffset(1.1);
    hist_data->GetYaxis()->SetTitleOffset(1.1);
    hist_data->SetMinimum(0.05);
    hist_data->SetMarkerStyle(8);
    hist_data->SetMarkerSize(1);
    hist_data->SetMarkerColor(kBlack);

    hist_signal_364519->SetLineStyle(1);
    hist_signal_364519->SetLineColor(kRed-7);
    hist_signal_364519->SetLineWidth(1);

    hist_data->Draw("PE");
    hist_signal_364519->Draw("HISTsame");

    TLegend *leg2 = new TLegend();
    leg2->SetBorderSize(0);
    leg2->AddEntry(hist_data,"Data");
    leg2->AddEntry(hist_signal_364519, "Z(#nu#bar{#nu})#gamma", "f");
    leg2->Draw();

    TLatex* latex2=new TLatex();
    latex2->SetTextSize(0.04);
    latex2->DrawLatex(-220,122.917,"#bf{#it{ATLAS}} Internal");
    latex2->DrawLatex(-220,208.716,"#sqrt{s}=13 TeV, 140 fb^{-1}");
    latex2->DrawLatex(-220,129.888,"SR");
    latex2->DrawLatex(-220,164,"N_{jets} #geq 0");

    // for(int h = 48; h <= 53; h++) {
    //   hist_data->SetBinError(h,hist_data->GetBinError(h)*0);
    //   hist_data->SetBinContent(h,hist_data->GetBinContent(h)*0);
    //
    //   hist_signal_301910->SetBinError(h,hist_data->GetBinError(h)*0);
    //   hist_signal_301910->SetBinContent(h,hist_data->GetBinContent(h)*0);
    //
    //   hist_signal_364519->SetBinError(h,hist_data->GetBinError(h)*0);
    //   hist_signal_364519->SetBinContent(h,hist_data->GetBinContent(h)*0);
    // }
    //
    //   Double_t error_data_more15_excl_bkg, error_signal_more15_301910, error_signal_more15_364519;
    //   Double_t N_data_more15_excl_bkg=hist_data->IntegralAndError(1, nbins, error_data_more15_excl_bkg, "");
    //   Double_t N_signal_more15_301910=hist_signal_301910->IntegralAndError(1, nbins, error_signal_more15_301910, "");
    //   Double_t N_signal_more15_364519=hist_signal_364519->IntegralAndError(1, nbins, error_signal_more15_364519, "");


    Double_t error_data_more15_excl_bkg1, error_data_more15_excl_bkg2, error_data_more15_excl_bkg;
    Double_t N_data_more15_excl_bkg1=(hist_data->IntegralAndError(1, 47, error_data_more15_excl_bkg1, ""));
    Double_t N_data_more15_excl_bkg2=(hist_data->IntegralAndError(54, 100, error_data_more15_excl_bkg2, ""));
    Double_t N_data_more15_excl_bkg= N_data_more15_excl_bkg1+N_data_more15_excl_bkg2;
    error_data_more15_excl_bkg=sqrt(pow(error_data_more15_excl_bkg1,2)+pow(error_data_more15_excl_bkg2,2));


    Double_t error_signal_more15_301910_1, error_signal_more15_301910_2, error_signal_more15_301910;
    Double_t N_signal_more15_301910_1=hist_signal_301910->IntegralAndError(1, 47, error_signal_more15_301910_1, "");
    Double_t N_signal_more15_301910_2=hist_signal_301910->IntegralAndError(54, 100, error_signal_more15_301910_2, "");
    Double_t N_signal_more15_301910=  N_signal_more15_301910_1+N_signal_more15_301910_2;
    error_signal_more15_301910=sqrt(pow(error_signal_more15_301910_1,2)+pow(error_signal_more15_301910_2,2));

    Double_t error_signal_more15_364519_1, error_signal_more15_364519_2, error_signal_more15_364519;
    Double_t N_signal_more15_364519_1=hist_signal_364519->IntegralAndError(1, 47, error_signal_more15_364519_1, "");
    Double_t N_signal_more15_364519_2=hist_signal_364519->IntegralAndError(54, 100, error_signal_more15_364519_2, "");
    Double_t N_signal_more15_364519=  N_signal_more15_364519_1+N_signal_more15_364519_2;
    error_signal_more15_364519=sqrt(pow(error_signal_more15_364519_1,2)+pow(error_signal_more15_364519_2,2));


    Double_t rate_PU_more15mm_301910=(N_data_more15_excl_bkg-N_signal_more15_301910)/(0.76*N_data);
    Double_t error_rate_PU_more15mm_301910=sqrt(pow(error_data_more15_excl_bkg/(N_data*0.76),2)+pow((rate_PU_more15mm_301910*error_data)/N_data,2)+pow((error_signal_more15_301910)/(0.76*N_data),2));

    Double_t rate_PU_more15mm_364519=(N_data_more15_excl_bkg-N_signal_more15_364519)/(0.76*N_data);
    Double_t error_rate_PU_more15mm_364519=sqrt(pow(error_data_more15_excl_bkg/(N_data*0.76),2)+pow((rate_PU_more15mm_364519*error_data)/N_data,2)+pow((error_signal_more15_364519)/(0.76*N_data),2));


    std::cout << "N_data_more15_excl_bkg= " << N_data_more15_excl_bkg << " +- " << error_data_more15_excl_bkg << '\n';
    std::cout << "" << '\n';

    std::cout << "N_signal_more15_301910= " << N_signal_more15_301910 << " +- " << error_signal_more15_301910 << '\n';
    std::cout << "" << '\n';

    std::cout << "N_signal_more15_364519= " << N_signal_more15_364519 << " +- " << error_signal_more15_364519 << '\n';
    std::cout << "" << '\n';

    std::cout << "rate_PU_more15mm_301910= " << rate_PU_more15mm_301910 << " +- " << error_rate_PU_more15mm_301910 << '\n';
    std::cout << "" << '\n';

    std::cout << "rate_PU_more15mm_364519= " << rate_PU_more15mm_364519 << " +- " << error_rate_PU_more15mm_364519 << '\n';
    std::cout << "" << '\n';


    Double_t error_data_more50_excl_bkg1, error_data_more50_excl_bkg2, error_data_more50_excl_bkg;
    Double_t N_data_more50_excl_bkg1=(hist_data->IntegralAndError(1, 40, error_data_more50_excl_bkg1, ""));
    Double_t N_data_more50_excl_bkg2=(hist_data->IntegralAndError(61, 100, error_data_more50_excl_bkg2, ""));
    Double_t N_data_more50_excl_bkg= N_data_more50_excl_bkg1+N_data_more50_excl_bkg2;
    error_data_more50_excl_bkg=sqrt(pow(error_data_more50_excl_bkg1,2)+pow(error_data_more50_excl_bkg2,2));


    Double_t error_signal_more50_301910_1, error_signal_more50_301910_2, error_signal_more50_301910;
    Double_t N_signal_more50_301910_1=hist_signal_301910->IntegralAndError(1, 40, error_signal_more50_301910_1, "");
    Double_t N_signal_more50_301910_2=hist_signal_301910->IntegralAndError(61, 100, error_signal_more50_301910_2, "");
    Double_t N_signal_more50_301910=  N_signal_more50_301910_1+N_signal_more50_301910_2;
    error_signal_more50_301910=sqrt(pow(error_signal_more50_301910_1,2)+pow(error_signal_more50_301910_2,2));

    Double_t error_signal_more50_364519_1, error_signal_more50_364519_2, error_signal_more50_364519;
    Double_t N_signal_more50_364519_1=hist_signal_364519->IntegralAndError(1, 40, error_signal_more50_364519_1, "");
    Double_t N_signal_more50_364519_2=hist_signal_364519->IntegralAndError(61, 100, error_signal_more50_364519_2, "");
    Double_t N_signal_more50_364519=  N_signal_more50_364519_1+N_signal_more50_364519_2;
    error_signal_more50_364519=sqrt(pow(error_signal_more50_364519_1,2)+pow(error_signal_more50_364519_2,2));


    Double_t rate_PU_more50mm_301910=(N_data_more50_excl_bkg-N_signal_more50_301910)/(0.32*N_data);
    Double_t error_rate_PU_more50mm_301910=sqrt(pow(error_data_more50_excl_bkg/(N_data*0.32),2)+pow((rate_PU_more50mm_301910*error_data)/N_data,2)+pow((error_signal_more50_301910)/(0.32*N_data),2));

    Double_t rate_PU_more50mm_364519=(N_data_more50_excl_bkg-N_signal_more50_364519)/(0.32*N_data);
    Double_t error_rate_PU_more50mm_364519=sqrt(pow(error_data_more50_excl_bkg/(N_data*0.32),2)+pow((rate_PU_more50mm_364519*error_data)/N_data,2)+pow((error_signal_more50_364519)/(0.32*N_data),2));


    std::cout << "N_data_more50_excl_bkg= " << N_data_more50_excl_bkg << " +- " << error_data_more50_excl_bkg << '\n';
    std::cout << "" << '\n';

    std::cout << "N_signal_more50_301910= " << N_signal_more50_301910 << " +- " << error_signal_more50_301910 << '\n';
    std::cout << "" << '\n';

    std::cout << "N_signal_more50_364519= " << N_signal_more50_364519 << " +- " << error_signal_more50_364519 << '\n';
    std::cout << "" << '\n';

    std::cout << "rate_PU_more50mm_301910= " << rate_PU_more50mm_301910 << " +- " << error_rate_PU_more50mm_301910 << '\n';
    std::cout << "" << '\n';

    std::cout << "rate_PU_more50mm_364519= " << rate_PU_more50mm_364519 << " +- " << error_rate_PU_more50mm_364519 << '\n';
    std::cout << "" << '\n';
}
