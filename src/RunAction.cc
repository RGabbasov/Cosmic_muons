//#include "ConfigArray.h"
#include "RunAction.h"
#include "EventAction.h"

#include<G4Step.hh>

#include "globals.hh"
#include "G4Run.hh"
#include "Randomize.hh"

#include "TTree.h"
#include "TBranch.h"
#include "TFile.h"


#include<iostream>
#include<fstream>
RunAction::RunAction()
{

}

RunAction::~RunAction()
{
}

void RunAction::BeginOfRunAction(const G4Run* run)
{


run->GetRunID();
//if (1==1) 
    // It is the only way to save/restore status into/from the user defined file
 //   CLHEP::HepRandom::getTheEngine()->restoreStatus("JamesRandom.status"); 
//CLHEP::HepRandom::showEngineStatus();
/*if (0==1) 
    {
    int filenum=0;
    FILE* opened = NULL;
    G4String name(30);
    char buf[10];
//  name = "MyExample0.root";
//opened = fopen(name.data(), "r");
    do 
	{
	if (filenum!=0) fclose(opened);
	filenum++; 
	sprintf(buf, "%d", filenum-1);
	name = "my";
	name += buf;
	name += ".root";
	opened = fopen(name.data(), "r");
	}
    while (opened!=NULL) ;
    file1 = new TFile(name, "RECREATE");

    }
else */
file1 = new TFile("phot.root", "RECREATE");
TrekTree = new TTree("T", "trek_information_tree");
muon_inf=TrekTree->Branch("Muon_inf", NULL, "energy/D:deposit[100]/D:X[100]/D:Y[100]/D:Z[100]/D:T[100]/D");
Signal = TrekTree->Branch("signal",NULL, "numph/I:sig0[2000]/I:sig1[2000]/I:sig2[2000]/I:sig3[2000]/I:sig4[2000]/I:sig5[2000]/I:sig6[2000]/I");
TimeBr=TrekTree->Branch("time", NULL, "Time[2000]/I");
EvBr=TrekTree->Branch("ev",NULL,"event/I");
G4int i;
for(i=0;i<3000;i++)
	stime[i]=i;
TimeBr->SetAddress(stime);


ince=0;

//Treetime = new TTree("Treetime", "time_information_tree");
//first=Treetime->Branch("first", NULL, "tfirst/D");
//last=Treetime->Branch("last", NULL, "tlast/D");

}

void RunAction::EndOfRunAction(const G4Run* run)
{
//run->GetRunID();
TrekTree->Write();
file1->Write();

//CLHEP::HepRandom::showEngineStatus();
CLHEP::HepRandom::getTheEngine()->saveStatus("JamesRandom.status"); 
delete TrekTree;

delete file1;
}

/*void RunAction::AddParticle_inf(Muon_inf muon)
{
G4double der=2;
//G4cout <<"y345423424yu "<<muon.X[2]<<"  "<<muon.Y[2]<<muon.Z[2]<<G4endl;
muon_inf->SetAddress(&muon);
TrekTree->Fill();
}*/

void RunAction::AddEvent(Signal_st sig_st,Muon_inf muon)
{
muon_inf->SetAddress(&muon);
Signal->SetAddress(&sig_st);
EvBr->SetAddress(&ince);
TrekTree->Fill();
ince++;
G4cout <<"event "<< ince<<G4endl;
}
void RunAction::Addtime(G4double f, G4double l)
{
//first->SetAddress(&f);
//last->SetAddress(&l);
//Treetime->Fill();
}





