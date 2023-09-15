#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

void version_() {

      std::vector<std::thread> threads;
      std::mutex mtx; // Создание мьютекса

      Double_t  soft_term_pt_gamma, soft_term_pt_Znunu;
      Double_t  soft_term_pt;

      Int_t num_threads = 4; // Количество потоков
      Int_t start = 0; // Начальное число
      //Int_t end = 435504; // Конечное число
      Int_t end = 20;
      Int_t numbers_per_thread = (end - start + 1) / num_threads;

      TFile *file_1 = new TFile ("/home/valerian/programs/atom_progs/gamma_jets.root","READ");
      TFile *file_2 = new TFile ("/home/valerian/programs/atom_progs/Z_nunu.root","READ");

      // TFile *file1 = new TFile ("/home/valerian/programs/atom_progs/combined1.root","RECREATE");
      // TFile *file2 = new TFile ("/home/valerian/programs/atom_progs/combined2.root","RECREATE");
      // TFile *file3 = new TFile ("/home/valerian/programs/atom_progs/combined3.root","RECREATE");
      // TFile *file4 = new TFile ("/home/valerian/programs/atom_progs/combined4.root","RECREATE");

      TTree *tree_gamma = (TTree*)file_1->Get("gamma_tree");
      TTree *tree_z = (TTree*)file_2->Get("Z_nunu_tree");
      tree_gamma->SetBranchAddress("soft_term_pt_gamma", &soft_term_pt_gamma);
      tree_z->SetBranchAddress("soft_term_pt_Znunu", &soft_term_pt_Znunu);
      Int_t entries_gamma = (Int_t)tree_gamma->GetEntries();
      Int_t entries_z = (Int_t)tree_z->GetEntries();

      TTree *combined_tree_1 = new TTree ("combined_tree","combined_tree");
      TTree *combined_tree_2 = new TTree ("combined_tree","combined_tree");
      TTree *combined_tree_3 = new TTree ("combined_tree","combined_tree");
      TTree *combined_tree_4 = new TTree ("combined_tree","combined_tree");

      combined_tree_1->Branch("soft_term_pt",&soft_term_pt,"soft_term_pt/D");
      combined_tree_2->Branch("soft_term_pt",&soft_term_pt,"soft_term_pt/D");
      combined_tree_3->Branch("soft_term_pt",&soft_term_pt,"soft_term_pt/D");
      combined_tree_4->Branch("soft_term_pt",&soft_term_pt,"soft_term_pt/D");

      std::vector<std::pair<int, int>> ranges(num_threads);

      for (Int_t i = 0; i < num_threads; i++)
      {
            // Вычисляем начальное и конечное число для текущего потока
            Int_t thread_start = start + i * numbers_per_thread;
            Int_t thread_end = thread_start + numbers_per_thread - 1;
            ranges[i].first = thread_start;
            // Если это последний поток, то увеличиваем его диапазон до конца
              if (i == num_threads - 1)
                {
                  ranges[i].second = end;
                  break;
                }
              else
                {
                  ranges[i].second = thread_end;
                }
      }

      for (int i = 0; i < num_threads; i++)
      {
          // Создание и запуск потока с лямбда-функцией
          threads.push_back(std::thread([&,i]() {

          mtx.lock();
          for (int i_gamma = ranges[i].first ; i_gamma < ranges[i].second; i_gamma++)
          {
            tree_gamma->GetEntry(i_gamma);

             for (int i_z = 0; i_z < 10 ; i_z++){
            //for (int i_z = 0; i_z < 361935 ; i_z++){


            tree_z->GetEntry(i_z);
            // std::cout << "soft_term_pt_gamma=" <<soft_term_pt_gamma << '\n';
            // std::cout << "soft_term_pt_Znunu=" <<soft_term_pt_Znunu << '\n';
            TLorentzVector *soft_term_ = new TLorentzVector();
            TLorentzVector *soft_term_photon = new TLorentzVector();
            TLorentzVector *soft_term_Z_boson = new TLorentzVector();
            soft_term_photon->SetPtEtaPhiM(soft_term_pt_gamma, 0, 0, 0);
            soft_term_Z_boson->SetPtEtaPhiM(soft_term_pt_Znunu, 0, 0, 0);
            *soft_term_=*soft_term_photon+*soft_term_Z_boson;
            soft_term_pt=(*soft_term_).Pt();
            if (soft_term_pt >= 16) continue;
            // std::cout << "soft_term_pt=" <<soft_term_pt << '\n';

            if (i==0) {
              combined_tree_1->Fill();
            }
            else if (i==1) {
              combined_tree_2->Fill();
            }
            else if (i==2) {
              combined_tree_3->Fill();
            }
            else {
              combined_tree_4->Fill();
            }
          }
            std::cout << "Hello from thread " << i << std::endl;
          }

          if (i==0) {
            TFile *file1 = new TFile ("/home/valerian/programs/atom_progs/combined1.root","RECREATE");
            combined_tree_1->Write();
            file1->Write();
            file1->Close();
          }
          else if (i==1) {
            TFile *file2 = new TFile ("/home/valerian/programs/atom_progs/combined2.root","RECREATE");
            combined_tree_2->Write();
            file2->Write();
            file2->Close();
          }
          else if (i==2) {
            TFile *file3 = new TFile ("/home/valerian/programs/atom_progs/combined3.root","RECREATE");
            combined_tree_3->Write();
            file3->Write();
            file3->Close();
          }
          else {
            TFile *file4 = new TFile ("/home/valerian/programs/atom_progs/combined4.root","RECREATE");
            combined_tree_4->Write();
            file4->Write();
            file4->Close();
          }
          mtx.unlock();
        }));
      }

      // Дождитесь завершения всех потоков перед выходом
    for (auto& thread : threads)
    {
      thread.join();
    }
}
