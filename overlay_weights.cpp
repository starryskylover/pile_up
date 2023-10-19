using namespace std;

void overlay_weights() {

    Double_t weight_znunu,weight_gamma_jets, koef_gamma_jets, koef_znunu, lumin, sumw_znunu, sumw_gamma_jets;
    Double_t weight_gamma, weight_Znunu;
    Double_t sigma_inel=80000000000;
    Double_t mu=34;

    Double_t sumw_tot_ph=0;
    Double_t sumw_tot_z=0;
    Double_t sumw_omc_ph=0;
    Double_t sumw_omc_z=0;

    const char *path = "/home/valerian/programs/atom_progs/omc/gamma_jets/gamma_jets_a/";
    const char *nabor[] = {"140280_inc_a.root","280500_inc_a.root","5001000_inc_a.root","10002000_inc_a.root"};

    int Num_tree1;
    for (int l = 0; l <= 3; l++) {
      char *Nabor = new char[strlen(path) + strlen(nabor[l]) + 1];
      strcpy(Nabor, path);
      strcat(Nabor, nabor[l]);
      TFile *file1 = new TFile(Nabor, "READ");
      TTree *tree1 = (TTree*)file1->Get("gamma_tree");

      tree1->SetBranchAddress("weight_gamma", &weight_gamma);
      Num_tree1 = (int)tree1->GetEntries();

              for (int i=0; i<Num_tree1; i++){
                tree1->GetEntry(i);
                sumw_tot_ph+=weight_gamma;
              }
     }

     TFile *file2 = new TFile("/home/valerian/programs/atom_progs/omc/Zj/Zj_a.root", "READ");
     TTree *tree2 = (TTree*)file2->Get("Z_nunu_tree");

      tree2->SetBranchAddress("weight_Znunu", &weight_Znunu);
      int Num_tree2 = (int)tree2->GetEntries();
               for (int i=0; i<Num_tree2; i++){
                 tree2->GetEntry(i);
                 sumw_tot_z+=weight_Znunu;
               }

    TFile* file3 = new TFile ("/home/valerian/programs/atom_progs/omc/combined_merge_a.root", "READ");
    TTree* tree3 = (TTree*)file3->Get("combined_tree");

    tree3->SetBranchAddress("weight_gamma_jets",&weight_gamma_jets);
    tree3->SetBranchAddress("weight_znunu",&weight_znunu);

    int Num_tree3 = (int)tree3->GetEntries();

              for (int i=0; i<Num_tree3; i++){
                  tree3->GetEntry(i);
                  sumw_omc_ph+=weight_gamma_jets;
                  sumw_omc_z+=weight_znunu;
                }

    std::cout << "sumw_tot_ph = " << sumw_tot_ph << '\n';
    std::cout << "sumw_tot_z = " << sumw_tot_z*4 << '\n';
    std::cout << "sumw_omc_ph = " << sumw_omc_ph << '\n';
    std::cout << "sumw_omc_z = " << sumw_omc_z << '\n';


    TFile* file_combined = new TFile ("/home/valerian/programs/atom_progs/omc/combined_merge_a.root", "READ");
    TTree* combined_tree = (TTree*)file_combined->Get("combined_tree");

    combined_tree->SetBranchAddress("weight_znunu",&weight_znunu);
    combined_tree->SetBranchAddress("weight_gamma_jets",&weight_gamma_jets);
    combined_tree->SetBranchAddress("koef_znunu",&koef_znunu);
    combined_tree->SetBranchAddress("koef_gamma_jets",&koef_gamma_jets);
    combined_tree->SetBranchAddress("lumin",&lumin);

    Double_t sum=0;

    int Num_tree = (int)combined_tree->GetEntries();
    std::cout << "entries=" << Num_tree <<'\n';
    for (int i=0; i<Num_tree; i++){

            combined_tree->GetEntry(i);

            // sum+=(weight_znunu*weight_gamma_jets*lumin*koef_gamma_jets*koef_znunu*Num_tree*mu)/(sigma_inel*sumw_omc_z*sumw_omc_ph);

            sum+=(weight_znunu*weight_gamma_jets*lumin*koef_gamma_jets*koef_znunu*Num_tree2*Num_tree2*16*mu)/(sigma_inel*sumw_tot_z*sumw_tot_ph*Num_tree);

    }

    std::cout << "sum = " << sum <<'\n';
}
