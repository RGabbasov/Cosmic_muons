#ifndef RunAction_header
#define RunAction_header

#include "EventAction.h"
#include "StackingAction.h"

#include "G4UserRunAction.hh"
#include "globals.hh"

#include "TTree.h"
#include "TBranch.h"
#include "TFile.h"

class RunAction : public G4UserRunAction
{
    public:
	RunAction();
	~RunAction();
	
	void BeginOfRunAction(const G4Run*);
	void EndOfRunAction(const G4Run*);
	void AddEvent(Signal_st,Muon_inf);
	//void AddParticle_inf(Muon_inf);
	void AddPhotonsignal();
	
	void Addtime (G4double,G4double);
	  
    private:
	TFile* file1;
	G4int stime[3000];	
	//TTree* SignalTree;
	TBranch* Signal;
	TBranch* TimeBr;
	G4int ince;
	TTree* TrekTree;
	TBranch* muon_inf;
        TBranch* EvBr;
	/*TBranch* PMTsignal2;
	TBranch* PMTsignal3;
	TBranch* PMTsignal4;
	TBranch* PMTsignal5;
	TBranch* PMTsignal6;
	G4double sig[7][300];*/
	//TBranch* TimeBr;
	//TBranch* PMTDataBranch;

};

#endif



