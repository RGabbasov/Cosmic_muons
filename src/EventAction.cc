#include "EventAction.h"
#include "RunAction.h"

#include "G4Event.hh"
//#include "TNtuple.h"
#include "globals.hh"
//#include <iostream>
//#include <fstream>
//#include <math.h>

EventAction::EventAction(RunAction* run) 
{
//G4cout << "rfnfr"<< "hqwjduhuieierfhwuie"<< G4endl;
runaction=run;
numberofphotons=0;
}

EventAction::~EventAction()
{
}

void EventAction::BeginOfEventAction(const G4Event* event)
{ sema=0;
 G4int j;
 for (j=0;j<2000;j++)
	{  
	sig_st.sig0[j]=0; 
	sig_st.sig1[j]=0; 
	sig_st.sig2[j]=0; 
	sig_st.sig3[j]=0; 
	sig_st.sig4[j]=0; 
	sig_st.sig5[j]=0; 
	sig_st.sig6[j]=0; 
	}
for (j=0;j<100;j++)
	{
	muon_st.deposit[j]=0;
	muon_st.X[j]=0;
	muon_st.Y[j]=0;
	muon_st.Z[j]=0;
	muon_st.T[j]=0;
	}
	muon_st.energy=0;
	sig_st.numberph=0;
	numberofphotons=0;
	inc=0;
}
 
void EventAction::EndOfEventAction(const G4Event* event)
{ 
 G4int EventID = event->GetEventID() + 1;
// runaction->AddPhotonsignal();
 runaction->AddEvent(sig_st, muon_st);
 //runaction->AddParticle_inf(muon_st);
 G4cout << "end of event. Photons created: "<< numberofphotons<< G4endl;
}

void EventAction::SetMuonEnergy(G4double en)
{
muon_st.energy=en;
inc=0;
G4cout << "setting------------->>>>>>>" << en<<G4endl;
}

void EventAction::AddMuoninf (G4double destep, G4ThreeVector point, G4double time)
{
//G4cout <<"trek  "<<inc<<"   "<<point<<G4endl;
muon_st.deposit[inc]=destep;
muon_st.X[inc]=point.x();
muon_st.Y[inc]=point.y();
muon_st.Z[inc]=point.z();
muon_st.T[inc]=time;
inc++;
	//G4cout<<"dfghdfghdfgh "<<destep<<" "<<point<<G4endl;
}

void EventAction::SetParticleEnergy(G4double ParticleEnergy)
{
//EventData.ParticleEnergy = ParticleEnergy / MeV;
}
void EventAction::incphotonnumber() 
{
numberofphotons++;
sig_st.numberph++;
}

void EventAction::PMTsig(G4double energy, G4double time, G4int copy)
{
G4double Time=time;
//G4double al[7]={1.,1.,1.,1.,1.,1.,1.};
G4int j;
G4double gap=5*nanosecond;

for (j=0; j<3000;j++)
 if ((Time>j*gap) && (Time<(j+1)*gap))
  { 
	switch(copy-1) {
	case 0:	sig_st.sig0[j]+=1;break;
	case 1:	sig_st.sig1[j]+=1;break;
	case 2:	sig_st.sig2[j]+=1;break;
	case 3:	sig_st.sig3[j]+=1;break;
	case 4:	sig_st.sig4[j]+=1;break;
	case 5:	sig_st.sig5[j]+=1;break;
	case 6:	sig_st.sig6[j]+=1;break;
 	default : G4cout<<"ne tyda popal "<<copy<<G4endl;
		}
  }	
}
/*
G4int EventAction::Getsus()
{
return sus
};*/
/*G4double EventAction::GetEventID()
{
//return EventData.EventID;
}*/





