#include <iostream>
#include <string>
#include <vector>

void Overlay() {

          Double_t sigma_inel=80000000000;
          Double_t mu[]={25.1,37.8,36.1};
          Int_t company;
          std::cout << "Enter company-> 0-MC16   1-MC16d   2-MC16e" << '\n';
          cin >> company;

          std::vector<std::string> NameGamma = {"045_", "046_", "047_", "048_", "049_", "050_", "051_", "052_", "053_", "054_", "055_", "056_"};
          std::vector<std::string> NameZ = {"222_a.root", "223_a.root","011_a.root", "012_a.root", "013_a.root", "014_a.root", "015_a.root", "016_a.root", "017_a.root", "020_a.root", "021_a.root", "022_a.root", "023_a.root", "024_a.root", "025_a.root", "026_a.root",
          "029_a.root", "030_a.root", "031_a.root", "032_a.root", "033_a.root", "034_a.root", "035_a.root"};

          std::vector<std::string> OutputFileGamma = {
          "GammaJets_361045_a.root", "GammaJets_361046_a.root", "GammaJets_361047_a.root", "GammaJets_361048_a.root", "GammaJets_361049_a.root",
          "GammaJets_361050_a.root", "GammaJets_361051_a.root", "GammaJets_361052_a.root", "GammaJets_361053_a.root", "GammaJets_361054_a.root",
          "GammaJets_361055_a.root", "GammaJets_361056_a.root"};
          std::vector<std::string> OutputFileZ = {
          "Zjets_364222_a.root", "Zjets_364223_a.root","Zjets_366011_a.root", "Zjets_366012_a.root", "Zjets_366013_a.root",
          "Zjets_366014_a.root", "Zjets_366015_a.root", "Zjets_366016_a.root", "Zjets_366017_a.root", "Zjets_366020_a.root",
          "Zjets_366021_a.root", "Zjets_366022_a.root", "Zjets_366023_a.root", "Zjets_366024_a.root","Zjets_366025_a.root",
          "Zjets_366026_a.root", "Zjets_366029_a.root", "Zjets_366030_a.root", "Zjets_366031_a.root", "Zjets_366032_a.root",
          "Zjets_366033_a.root", "Zjets_366034_a.root", "Zjets_366035_a.root"};

          vector<pair<Double_t, Double_t>> VectorSumAndErrorTotal(OutputFileGamma.size());

          for (int itGamma = 0; itGamma < OutputFileGamma.size(); ++itGamma) {

              cout << "OutputFileGamma: " << OutputFileGamma[itGamma] << ", NameGamma: " << NameGamma[itGamma] << endl;

              Double_t SumForEveryGamma=0;
              Double_t ErrorForEveryGamma=0;


              TFile* file_gamma_jets = new TFile (OutputFileGamma[itGamma].c_str(), "READ");
              TTree* tree_gamma_jets = (TTree*)file_gamma_jets->Get("gamma_tree");

              vector<shared_ptr<TTreeReader>> readers_gamma_jets;
              readers_gamma_jets.push_back(make_shared<TTreeReader>(tree_gamma_jets));

              Int_t entries_gamma_jets = readers_gamma_jets[0] -> GetEntries();
              std::cout << "entries_gamma_jets = " << entries_gamma_jets <<'\n';

              TTreeReaderValue<Double_t> weight_gamma(*readers_gamma_jets[0], "weight_gamma");
              TTreeReaderValue<Double_t> ph_pt_gamma(*readers_gamma_jets[0], "ph_pt_gamma");
              TTreeReaderValue<Double_t> ph_phi_gamma(*readers_gamma_jets[0], "ph_phi_gamma");
              TTreeReaderValue<Double_t> ph_eta_gamma(*readers_gamma_jets[0], "ph_eta_gamma");
              TTreeReaderValue<Double_t> jet_lead_phi_gamma(*readers_gamma_jets[0], "jet_lead_phi_gamma");
              TTreeReaderValue<Double_t> jet_lead_pt_gamma(*readers_gamma_jets[0], "jet_lead_pt_gamma");
              TTreeReaderValue<Double_t> jet_lead_eta_gamma(*readers_gamma_jets[0], "jet_lead_eta_gamma");
              TTreeReaderValue<Double_t> metTST_pt_gamma(*readers_gamma_jets[0], "metTST_pt_gamma");
              TTreeReaderValue<Double_t> metTST_phi_gamma(*readers_gamma_jets[0], "metTST_phi_gamma");
              TTreeReaderValue<UInt_t> n_jet_gamma(*readers_gamma_jets[0], "n_jet_gamma");
              TTreeReaderValue<Double_t> koef_gamma(*readers_gamma_jets[0], "koef_gamma");
              TTreeReaderValue<Double_t> cross_section_gamma(*readers_gamma_jets[0], "cross_section_gamma");
              TTreeReaderValue<Double_t> luminosity(*readers_gamma_jets[0], "luminosity");
              TTreeReaderValue<Double_t> sumw_gamma(*readers_gamma_jets[0], "sumw_gamma");

              std::vector<pair<Double_t, Double_t>> VectorSumAndErrorForEveryGamma(OutputFileZ.size());


                       for (int itZ = 0; itZ < OutputFileZ.size(); ++itZ) {


                            Double_t sumForItGammaItZ=0;
                            Double_t meanWeightGumma=0;
                            Double_t meanWeightZ=0;
                            Double_t Quad_w_gamma=0;
                            Double_t Quad_w_z=0;


                            Double_t weight_znunu,weight_gamma_jets, ph_pt, ph_phi, ph_eta, jet_lead_phi,jet_lead_pt, jet_lead_eta, metTST_pt, metTST_phi;
                            Int_t n_jet;
                            Double_t koef_gamma_jets, koef_znunu, lumin, sumw_znunu, sumw_gamma_jets, cross_section_gamma_jets, cross_section_znunu;

                            TFile* file_combined = new TFile ((NameGamma[itGamma]+NameZ[itZ]).c_str(), "RECREATE");
                            TTree *combined_tree = new TTree ("combined_tree", "combined_tree");

                            combined_tree->Branch("ph_pt",&ph_pt,"ph_pt/D");
                            combined_tree->Branch("ph_eta",&ph_eta,"ph_eta/D");
                            combined_tree->Branch("ph_phi",&ph_phi,"ph_phi/D");
                            combined_tree->Branch("jet_lead_pt",&jet_lead_pt,"jet_lead_pt/D");
                            combined_tree->Branch("jet_lead_eta",&jet_lead_eta,"jet_lead_eta/D");
                            combined_tree->Branch("jet_lead_phi",&jet_lead_phi,"jet_lead_phi/D");
                            combined_tree->Branch("n_jet",&n_jet,"n_jet/i");
                            combined_tree->Branch("metTST_pt",&metTST_pt,"metTST_pt/D");
                            combined_tree->Branch("metTST_phi",&metTST_phi,"metTST_phi/D");
                            combined_tree->Branch("weight_znunu",&weight_znunu,"weight_znunu/D");
                            combined_tree->Branch("weight_gamma_jets",&weight_gamma_jets,"weight_gamma_jets/D");
                            combined_tree->Branch("koef_znunu",&koef_znunu,"koef_znunu/D");
                            combined_tree->Branch("koef_gamma_jets",&koef_gamma_jets,"koef_gamma_jets/D");
                            combined_tree->Branch("cross_section_znunu",&cross_section_znunu,"cross_section_znunu/D");
                            combined_tree->Branch("cross_section_gamma_jets",&cross_section_gamma_jets,"cross_section_gamma_jets/D");
                            combined_tree->Branch("lumin",&lumin,"lumin/D");
                            combined_tree->Branch("sumw_znunu",&sumw_znunu,"sumw_znunu/D");
                            combined_tree->Branch("sumw_gamma_jets",&sumw_gamma_jets,"sumw_gamma_jets/D");


                            TFile* file_znunu = new TFile (OutputFileZ[itZ].c_str(), "READ");
                            TTree* tree_znunu = (TTree*)file_znunu->Get("Z_nunu_tree");
                            vector<shared_ptr<TTreeReader>> readers_znunu;
                            readers_znunu.push_back(make_shared<TTreeReader>(tree_znunu));

                            TTreeReaderValue<Double_t> weight_Znunu(*readers_znunu[0], "weight_Znunu");
                            TTreeReaderValue<Double_t> ph_pt_Znunu(*readers_znunu[0], "ph_pt_Znunu");
                            TTreeReaderValue<Double_t> ph_phi_Znunu(*readers_znunu[0], "ph_phi_Znunu");
                            TTreeReaderValue<Double_t> ph_eta_Znunu(*readers_znunu[0], "ph_eta_Znunu");
                            TTreeReaderValue<Double_t> jet_lead_phi_Znunu(*readers_znunu[0], "jet_lead_phi_Znunu");
                            TTreeReaderValue<Double_t> jet_lead_pt_Znunu(*readers_znunu[0], "jet_lead_pt_Znunu");
                            TTreeReaderValue<Double_t> jet_lead_eta_Znunu(*readers_znunu[0], "jet_lead_eta_Znunu");
                            TTreeReaderValue<Double_t> metTST_pt_Znunu(*readers_znunu[0], "metTST_pt_Znunu");
                            TTreeReaderValue<Double_t> metTST_phi_Znunu(*readers_znunu[0], "metTST_phi_Znunu");
                            TTreeReaderValue<UInt_t> n_jet_Znunu(*readers_znunu[0], "n_jet_Znunu");
                            TTreeReaderValue<Double_t> koef_Znunu(*readers_znunu[0], "koef_Znunu");
                            TTreeReaderValue<Double_t> cross_section_z(*readers_znunu[0], "cross_section_z");
                            TTreeReaderValue<Double_t> sumw_Znunu(*readers_znunu[0], "sumw_Znunu");

                            Int_t entries_zj =readers_znunu[0] -> GetEntries();
                            std::cout << "entries_zj = " << entries_zj <<'\n';


                            Int_t Cycle;
                            (entries_gamma_jets >= entries_zj) ? Cycle=0 : Cycle=entries_zj/entries_gamma_jets;


                            Int_t Num_OMC;
                            (Cycle == 0) ?  Num_OMC = entries_gamma_jets : Num_OMC = entries_zj;

                            for (Int_t _ = 0; _ <= Cycle; _++){
                                Int_t stop;
                                ((_ != Cycle) || (Cycle == 0)) ? stop = entries_gamma_jets : stop = entries_zj-Cycle*entries_gamma_jets;


                                for (Int_t Gamma = 0; Gamma < stop; Gamma++) {
                                    ((_ == Cycle) && (Cycle > 0)) ? readers_gamma_jets[0] -> SetEntry((rand() % entries_gamma_jets)) : readers_gamma_jets[0] -> SetEntry(Gamma);

                                     bool action, end;
                                     while(true){
                                          Int_t z = rand() % entries_zj;
                                          readers_znunu[0] -> SetEntry(z);
                                          koef_gamma_jets=*koef_gamma;
                                          koef_znunu=*koef_Znunu;
                                          cross_section_gamma_jets=*cross_section_gamma;
                                          cross_section_znunu=*cross_section_z;
                                          lumin=*luminosity;
                                          sumw_gamma_jets=*sumw_gamma;
                                          sumw_znunu=*sumw_Znunu;

                                          TLorentzVector *jet_lead = new TLorentzVector();
                                          TLorentzVector *ph_g = new TLorentzVector();

                                          ph_g->SetPtEtaPhiM(*ph_pt_gamma, *ph_eta_gamma, *ph_phi_gamma, 0);
                                          ph_pt=(*ph_g).Pt();
                                          ph_phi=(*ph_g).Phi();
                                          ph_eta=(*ph_g).Eta();

                                          if (*n_jet_Znunu == 0 && *n_jet_gamma == 0) {
                                            n_jet=0;
                                            jet_lead->SetPtEtaPhiM(0, 0, 0, 0);
                                          }

                                          else if (*n_jet_Znunu == 0 && *n_jet_gamma >= 1) {
                                            n_jet=1;
                                            jet_lead->SetPtEtaPhiM(*jet_lead_pt_gamma, *jet_lead_eta_gamma, *jet_lead_phi_gamma,0);
                                          }

                                          else if (*n_jet_Znunu >= 1 && *n_jet_gamma == 0) {
                                            n_jet=1;
                                            jet_lead->SetPtEtaPhiM(*jet_lead_pt_Znunu, *jet_lead_eta_Znunu, *jet_lead_phi_Znunu, 0);
                                          }

                                          else if (*n_jet_Znunu >= 1 && *n_jet_gamma >= 1 && *jet_lead_pt_gamma > *jet_lead_pt_Znunu) {
                                            n_jet=1;
                                            jet_lead->SetPtEtaPhiM(*jet_lead_pt_gamma, *jet_lead_eta_gamma, *jet_lead_phi_gamma, 0);
                                          }

                                          else if (*n_jet_Znunu >= 1 && *n_jet_gamma >= 1 && *jet_lead_pt_Znunu > *jet_lead_pt_gamma) {
                                            n_jet=1;
                                            jet_lead->SetPtEtaPhiM(*jet_lead_pt_Znunu, *jet_lead_eta_Znunu, *jet_lead_phi_Znunu, 0);
                                          }
                                          else {
                                            n_jet=1;
                                            jet_lead->SetPtEtaPhiM(*jet_lead_pt_gamma, *jet_lead_eta_gamma, *jet_lead_phi_gamma, 0);
                                          }

                                          jet_lead_pt=(*jet_lead).Pt();
                                          jet_lead_phi=(*jet_lead).Phi();
                                          jet_lead_eta=(*jet_lead).Eta();
                                          Double_t deltar=(*jet_lead).DeltaR(*ph_g);


                                          TLorentzVector *metTST = new TLorentzVector();
                                          TLorentzVector *metTST_z = new TLorentzVector();
                                          TLorentzVector *metTST_g = new TLorentzVector();
                                          metTST_z->SetPtEtaPhiM(*metTST_pt_Znunu, 0, *metTST_phi_Znunu, 0);
                                          metTST_g->SetPtEtaPhiM(*metTST_pt_gamma, 0, *metTST_phi_gamma, 0);

                                          *metTST=*metTST_g+*metTST_z;
                                          metTST_pt=(*metTST).Pt();
                                          metTST_phi=(*metTST).Phi();

                                          Double_t dphi_met_gamma=abs((*metTST).DeltaPhi(*ph_g));
                                          Double_t dphi_met_jet_lead=abs((*metTST).DeltaPhi(*jet_lead));

                                          bool ZSelection = ((metTST_pt <= 130) && (dphi_met_gamma <= 0.6) && (dphi_met_jet_lead <= 0.3 && n_jet == 1));
                                          // bool action;
                                          // bool end;
                                          (ZSelection==false) ? action=1 : action=0;

                                          switch(action)
                                          {
                     	                      case 1:

                                             weight_znunu=*weight_Znunu;
                                             weight_gamma_jets=*weight_gamma;

                                             sumForItGammaItZ+=weight_znunu*weight_gamma_jets*cross_section_gamma_jets*cross_section_znunu*lumin;
                                             meanWeightGumma+=weight_gamma_jets;
                                             meanWeightZ+=weight_znunu;
                                             // Quad_w_gamma+=pow(((weight_znunu*cross_section_gamma_jets*cross_section_znunu*lumin*mu[company])/(sigma_inel*counter*meanWeightGumma*meanWeightZ))*(1-(weight_gamma_jets/(counter*meanWeightGumma)))*error_weight_gamma,2);
                                             // Quad_w_z+=pow(((weight_gamma_jets*cross_section_gamma_jets*cross_section_znunu*lumin*mu[company])/(sigma_inel*counter*meanWeightGumma*meanWeightZ))*(1-(weight_znunu/(counter*meanWeightZ)))*error_weight_z,2);
                                             Quad_w_gamma+=pow(weight_znunu,2);
                                             Quad_w_z+=pow(weight_gamma_jets,2);
                                             combined_tree -> Fill();
                     		                     end = true;
                     		                     break;


                     	                      case 0:

                                                end = false;
                                          }

                                          if (end) break;
                                     }
                                }

                            }

                            file_combined -> cd();
                            combined_tree -> Write("", TObject::kOverwrite);
                            file_combined -> Write("", TObject::kOverwrite);
                            file_combined -> Close();

                            meanWeightGumma=meanWeightGumma/Num_OMC;
                            meanWeightZ=meanWeightZ/Num_OMC;
                            sumForItGammaItZ=(sumForItGammaItZ*mu[company])/(sigma_inel*Num_OMC*meanWeightGumma*meanWeightZ);
                            Double_t errorForItGammaItZ=sqrt(Quad_w_gamma+Quad_w_z);

                            VectorSumAndErrorForEveryGamma[itZ] = std::make_pair(sumForItGammaItZ, errorForItGammaItZ);
                    /*Z file end */
                    }

              for (const auto& Element : VectorSumAndErrorForEveryGamma) {
                  SumForEveryGamma += Element.first;
                  ErrorForEveryGamma += pow((Element.second),2);
              }
              VectorSumAndErrorTotal[itGamma] = std::make_pair(SumForEveryGamma,sqrt(ErrorForEveryGamma));


              for ( Int_t itForEveryGamma=0; itForEveryGamma < VectorSumAndErrorForEveryGamma.size(); ++itForEveryGamma) {
                  cout << itForEveryGamma << ") From combination with Z file " << OutputFileZ[itForEveryGamma] << " = " << VectorSumAndErrorForEveryGamma[itForEveryGamma].first << " +- " << VectorSumAndErrorForEveryGamma[itForEveryGamma].second << endl;
              }
              std::cout <<  '\n';
              std::cout <<  '\n';
/*gamma file end */
          }

          Double_t sum=0;
          for (Int_t itTotal=0; itTotal < VectorSumAndErrorTotal.size(); ++itTotal) {
              sum += VectorSumAndErrorTotal[itTotal].first;
              cout << itTotal << ") Sum for " << OutputFileGamma[itTotal] << " with all Z files = " << VectorSumAndErrorTotal[itTotal].first << " +- " << VectorSumAndErrorTotal[itTotal].second << endl;
          }
          std::cout << "Number of pile-up for MC16a = " << sum << '\n';
}



































// std::vector<Double_t> VectorSumForEveryGamma(OutputFileZ.size());
// std::vector<Double_t> VectorErrorForEveryGamma(OutputFileZ.size());  //соотвтсвующие ошибки

// VectorSumForEveryGamma[itZ] = sumForItGammaItZ;
// VectorErrorForEveryGamma[itZ] = errorForItGammaItZ;
// std::cout << itZ << ") Sum for " << OutputFileGamma[itGamma] << " with " << OutputFileZ[itZ] << " = " << sumForItGammaItZ << '\n';
// std::cout << itZ << ") Error for " << OutputFileGamma[itGamma] << " with " << OutputFileZ[itZ] << " = " << errorForItGammaItZ << '\n';


// std::cout << itGamma << ") Sum for " << OutputFileGamma[itGamma] << " with all Z files = " << SumForEveryGamma <<  '\n';
// std::cout << itGamma << ") Error for " << OutputFileGamma[itGamma] << " with all Z files =  " << sqrt(ErrorForEveryGamma) <<  '\n';
// VectorSumTotal[itGamma]=SumForEveryGamma;
// VectorErrorTotal[itGamma]=sqrt(ErrorForEveryGamma);



//   std::vector<string>::iterator itGamma;
//   for (itGamma=OutputFileGamma.begin(); itGamma!=OutputFileGamma.end(); ++itGamma) {    // цикл по каждому исходному файлу gamma
//   std::cout << *itGamma << " ";
// }




// std::vector<Double_t> VectorSumTotal(OutputFileGamma.size());
// std::vector<Double_t> VectorErrorTotal(OutputFileGamma.size());



  // std::vector<std::string> NameOMC; // название набора OMC
  //
  // for (const std::string& ElemGamma : NameGamma) { // элемент, текущий набор gamma из вектора названий gamma
  //   for (const std::string& ElemZ : NameZ) { // элемент, текущий набор Z из вектора названий Z
  //
  //
  //     std::string ElemOMC = ElemGamma + ElemZ; // элемент, текущий набор OMC
  //     NameOMC.push_back(ElemOMC);
  //     std::cout << "Текущее имя  OMC файла : " << ElemOMC << std::endl;
  //     std::cout « "Текущее имя  Gamma файла : " <<  << std::endl;
  //     std::cout « "Текущее имя  Z файла : " <<  << std::endl;
  //
  //     TFile* file_combined = new TFile(ElemOMC.c_str(), "RECREATE");
  //     TTree *combined_tree = new TTree ("combined_tree", "combined_tree");
  //
  //     combined_tree->Branch("ph_pt",&ph_pt,"ph_pt/D");
  //
  //
  //   }
  // }







  // for (const std::string& mergedStr : NameOMC) {
  //   std::cout << mergedStr << std::endl;
  // }
  // std::cout << NameOMC.size() << std::endl;







  // vector<string> vector1 = {"A", "B", "C"};
  // vector<string> vector2 = {"X", "Y", "Z"};
  //
  // // Объединение векторов в вектор пар
  // vector<pair<string, string>> combinedVector;
  // for (int i = 0; i < vector1.size(); ++i) {
  //   combinedVector.push_back(make_pair(vector1[i], vector2[i]));
  // }
  //
  // // Использование одного итератора для обхода обоих векторов
  // vector<pair<string, string>>::iterator it;
  // for (it = combinedVector.begin(); it != combinedVector.end(); ++it) {
  //   cout << "Vector1: " << it->first << ", Vector2: " << it->second << endl;
  // }
