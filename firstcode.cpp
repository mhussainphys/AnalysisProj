// Load the tree from the file
TFile *f = TFile::Open("/home/public/Example_tree.root");
TTree *tree = static_cast<TTree*>(f->Get("tree"));
// Declare and initialize branch variables
int nlep(0), njet(0);
double met(0);
TLorentzVector *mu = nullptr;
// Set addresses for tree branches
tree->SetBranchAddress("nleps",&nlep);
tree->SetBranchAddress("njets",&njet);
tree->SetBranchAddress("met",&met);
tree->SetBranchAddress("muon",&mu);
// Declare histograms to be filled in loop
TH1D *met_hist = new TH1D("met_hist","Missing tranvsverse momentum",100,0,400);
TH1D *tot_objects = new TH1D("tot_objects", "N_{leps} + N_{jets}",10,-0.5,9.5);
TH1D *boosted_e = new TH1D("boosted_e","Energy of boosted muon",100,0,400);
// Loop over tree entries
for(int i = 0; i < tree->GetEntries(); i++) {
    tree->GetEntry(i); // Fills branch variables with values
    met_hist->Fill(met);
    tot_objects->Fill(nlep+njet);
    mu->Boost(0,0,0.5);
    if(njet > 2 && nlep > 1) boosted_e->Fill(mu->E());
}
TCanvas can1("can1","can1",1000,750);
can1.cd();
met_hist->Draw();
can1.Draw();
TCanvas can2("can2","can2",1000,750);
can2.cd();
tot_objects->Draw();
can2.Draw();
TCanvas can3("can3","can3",1000,750);
can3.cd();
boosted_e->Draw();
can3.Draw();