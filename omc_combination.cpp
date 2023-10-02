#include <iostream>
#include <vector>

#include "TFile.h"
#include "TTreeReader.h"


using namespace std;

void omc_combination() {

    Double_t weight_znunu,weight_gamma_jets, ph_pt, ph_phi, ph_eta, soft_term_pt, soft_term_phi, jet_lead_phi,jet_lead_pt, jet_lead_eta, metTST_pt, metTST_phi;
    Int_t n_jet;
    Double_t koef_gamma_jets, koef_znunu, lumin, sumw_znunu, sumw_gamma_jets;
    string Z_nunu_tree_name = "Z_nunu_tree";

    TFile* file_combined = new TFile ("/home/valerian/programs/atom_progs/omc/combined_a.root", "RECREATE");
    TTree *combined_tree = new TTree ("combined_tree", "combined_tree");

    combined_tree->Branch("ph_pt",&ph_pt,"ph_pt/D");
    combined_tree->Branch("ph_eta",&ph_eta,"ph_eta/D");
    combined_tree->Branch("ph_phi",&ph_phi,"ph_phi/D");

    combined_tree->Branch("jet_lead_pt",&jet_lead_pt,"jet_lead_pt/D");
    combined_tree->Branch("jet_lead_eta",&jet_lead_eta,"jet_lead_eta/D");
    combined_tree->Branch("jet_lead_phi",&jet_lead_phi,"jet_lead_phi/D");
    combined_tree->Branch("n_jet",&n_jet,"n_jet/i");

    combined_tree->Branch("soft_term_pt",&soft_term_pt,"soft_term_pt/D");
    combined_tree->Branch("soft_term_phi",&soft_term_phi,"soft_term_phi/D");

    combined_tree->Branch("metTST_pt",&metTST_pt,"metTST_pt/D");
    combined_tree->Branch("metTST_phi",&metTST_phi,"metTST_phi/D");

    combined_tree->Branch("weight_znunu",&weight_znunu,"weight_znunu/D");
    combined_tree->Branch("weight_gamma_jets",&weight_gamma_jets,"weight_gamma_jets/D");
    combined_tree->Branch("koef_znunu",&koef_znunu,"koef_znunu/D");
    combined_tree->Branch("koef_gamma_jets",&koef_gamma_jets,"koef_gamma_jets/D");
    combined_tree->Branch("lumin",&lumin,"lumin/D");
    combined_tree->Branch("sumw_znunu",&sumw_znunu,"sumw_znunu/D");
    combined_tree->Branch("sumw_gamma_jets",&sumw_gamma_jets,"sumw_gamma_jets/D");


    Double_t sum=0;

    TFile* file_gamma_jets = new TFile ("/home/valerian/programs/atom_progs/omc/gamma_jets/gamma_jets_a/gamma_jets_a.root", "READ");
    TFile* file_znunu = new TFile ("/home/valerian/programs/atom_progs/omc/Zj/Zj_a/Zj_a.root", "READ");

    TTree* tree_gamma_jets = (TTree*)file_gamma_jets->Get("gamma_tree");
    TTree* tree_znunu = (TTree*)file_znunu->Get("Z_nunu_tree");

    vector<shared_ptr<TTreeReader>> readers_gamma_jets, readers_znunu;

        readers_gamma_jets.push_back(make_shared<TTreeReader>(tree_gamma_jets));
        readers_znunu.push_back(make_shared<TTreeReader>(tree_znunu));

        TTreeReaderValue<Double_t> weight_gamma(*readers_gamma_jets[0], "weight_gamma");
        TTreeReaderValue<Double_t> ph_pt_gamma(*readers_gamma_jets[0], "ph_pt_gamma");
        TTreeReaderValue<Double_t> ph_phi_gamma(*readers_gamma_jets[0], "ph_phi_gamma");
        TTreeReaderValue<Double_t> ph_eta_gamma(*readers_gamma_jets[0], "ph_eta_gamma");
        TTreeReaderValue<Double_t> soft_term_pt_gamma(*readers_gamma_jets[0], "soft_term_pt_gamma");
        TTreeReaderValue<Double_t> soft_term_phi_gamma(*readers_gamma_jets[0], "soft_term_phi_gamma");
        TTreeReaderValue<Double_t> jet_lead_phi_gamma(*readers_gamma_jets[0], "jet_lead_phi_gamma");
        TTreeReaderValue<Double_t> jet_lead_pt_gamma(*readers_gamma_jets[0], "jet_lead_pt_gamma");
        TTreeReaderValue<Double_t> jet_lead_eta_gamma(*readers_gamma_jets[0], "jet_lead_eta_gamma");
        TTreeReaderValue<Double_t> metTST_pt_gamma(*readers_gamma_jets[0], "metTST_pt_gamma");
        TTreeReaderValue<Double_t> metTST_phi_gamma(*readers_gamma_jets[0], "metTST_phi_gamma");
        TTreeReaderValue<UInt_t> n_jet_gamma(*readers_gamma_jets[0], "n_jet_gamma");
        TTreeReaderValue<Double_t> koef_gamma(*readers_gamma_jets[0], "koef_gamma");
        TTreeReaderValue<Double_t> luminosity(*readers_gamma_jets[0], "luminosity");
        TTreeReaderValue<Double_t> sumw_gamma(*readers_gamma_jets[0], "sumw_gamma");



        TTreeReaderValue<Double_t> weight_Znunu(*readers_znunu[0], "weight_Znunu");
        TTreeReaderValue<Double_t> ph_pt_Znunu(*readers_znunu[0], "ph_pt_Znunu");
        TTreeReaderValue<Double_t> ph_phi_Znunu(*readers_znunu[0], "ph_phi_Znunu");
        TTreeReaderValue<Double_t> ph_eta_Znunu(*readers_znunu[0], "ph_eta_Znunu");
        TTreeReaderValue<Double_t> soft_term_pt_Znunu(*readers_znunu[0], "soft_term_pt_Znunu");
        TTreeReaderValue<Double_t> soft_term_phi_Znunu(*readers_znunu[0], "soft_term_phi_Znunu");
        TTreeReaderValue<Double_t> jet_lead_phi_Znunu(*readers_znunu[0], "jet_lead_phi_Znunu");
        TTreeReaderValue<Double_t> jet_lead_pt_Znunu(*readers_znunu[0], "jet_lead_pt_Znunu");
        TTreeReaderValue<Double_t> jet_lead_eta_Znunu(*readers_znunu[0], "jet_lead_eta_Znunu");
        TTreeReaderValue<Double_t> metTST_pt_Znunu(*readers_znunu[0], "metTST_pt_Znunu");
        TTreeReaderValue<Double_t> metTST_phi_Znunu(*readers_znunu[0], "metTST_phi_Znunu");
        TTreeReaderValue<UInt_t> n_jet_Znunu(*readers_znunu[0], "n_jet_Znunu");
        TTreeReaderValue<Double_t> koef_Znunu(*readers_znunu[0], "koef_Znunu");
        TTreeReaderValue<Double_t> sumw_Znunu(*readers_znunu[0], "sumw_Znunu");

                Int_t entries_gamma_jets = readers_gamma_jets[0] -> GetEntries();

                // Int_t entities_gamma_jets = 20;

                // Int_t start=0;
                // Int_t end=readers_gamma_jets[0] -> GetEntries();
                Int_t start;
                Int_t end;

                std::cout << "Enter start-> " << '\n';
                cin >> start;

                std::cout << "Enter end-> " << '\n';
                cin >> end;

                for (Int_t j = start; j < end; j++) {
                    readers_gamma_jets[0] -> SetEntry(j);

                    cout << j << endl;

                    for (Int_t k = 0; k < readers_znunu[0] -> GetEntries(); k++) {
                    //for (Int_t k = 0; k < 3; k++) {
                        readers_znunu[0] -> SetEntry(k);

                        // koef_gamma_jets=*koef_gamma;
                        // koef_znunu=*koef_Znunu;
                        // lumin=*luminosity;
                        // sumw_gamma_jets=*sumw_gamma;
                        // sumw_znunu=*sumw_Znunu;



                        // std::cout << "koef_gamma=" <<   koef_gamma_jets << '\n';
                        // std::cout << "luminosity=" <<   lumin << '\n';
                        // TLorentzVector *jet_lead_z= new TLorentzVector();
                        // TLorentzVector *jet_lead_g= new TLorentzVector();
                        TLorentzVector *jet_lead = new TLorentzVector();
                        TLorentzVector *ph_g = new TLorentzVector();
                        // jet_lead_z->SetPtEtaPhiM(*jet_lead_pt_Znunu, *jet_lead_eta_Znunu, *jet_lead_phi_Znunu, 0);
                        // jet_lead_g->SetPtEtaPhiM(*jet_lead_pt_gamma, *jet_lead_eta_gamma, *jet_lead_phi_gamma, 0);
                        ph_g->SetPtEtaPhiM(*ph_pt_gamma, *ph_eta_gamma, *ph_phi_gamma, 0);
                        ph_pt=(*ph_g).Pt();
                        ph_phi=(*ph_g).Phi();
                        ph_eta=(*ph_g).Eta();

                        // std::cout << "n_jet_Znunu =" << *n_jet_Znunu << '\n';
                        // std::cout << "n_jet_gamma =" << *n_jet_gamma << '\n';
                        // std::cout << "jet_lead_pt_gamma =" << *jet_lead_pt_gamma << '\n';
                        // std::cout << "jet_lead_pt_Znunu =" << *jet_lead_pt_Znunu << '\n';
                        // std::cout  << '\n';


                        if (*n_jet_Znunu == 0 && *n_jet_gamma == 0) {
                          n_jet=1;
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
                        // std::cout << "jet_lead_pt =" << jet_lead_pt << '\n';

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

                        TLorentzVector *soft_term = new TLorentzVector();
                        TLorentzVector *soft_term_g = new TLorentzVector();
                        TLorentzVector *soft_term_z = new TLorentzVector();
                        soft_term_g->SetPtEtaPhiM(*soft_term_pt_gamma, 0, *soft_term_phi_gamma, 0);
                        soft_term_z->SetPtEtaPhiM(*soft_term_pt_Znunu, 0, *soft_term_phi_Znunu, 0);
                        *soft_term=*soft_term_g+*soft_term_z;
                        soft_term_pt=(*soft_term).Pt();
                        soft_term_phi=(*soft_term).Phi();

                        if (metTST_pt <= 130) continue;
                        if (dphi_met_gamma <= 0.7) continue;
                        if (dphi_met_jet_lead <= 0.4 && n_jet == 1) continue;
                        if (soft_term_pt >= 16) continue;

                        weight_znunu=*weight_Znunu;
                        weight_gamma_jets=*weight_gamma;

                        sum=weight_znunu*weight_gamma_jets;
                        combined_tree -> Fill();

                    }
                }
    file_combined -> cd();
    combined_tree -> Write("", TObject::kOverwrite);
    file_combined -> Write("", TObject::kOverwrite);
    file_combined -> Close();
}
