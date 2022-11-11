#include "SteppingAction.h"

#include "DetectorConstruction.hh"
#include "EventAction.h"
#include "G4ParticleDefinition.hh"

//#include "G4Track.hh"
#include "G4VPhysicalVolume.hh"
//#include "G4NavigationHistory.hh"  // Needed to make the way of gettig the local position work
//#include "globals.hh"

SteppingAction::SteppingAction (DetectorConstruction* det, EventAction* evt)
{
detector = det;
eventaction = evt;
flag=0;
photnum=0;
}

SteppingAction::~SteppingAction()
{

}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
G4TouchableHandle handle;


// Energy losses in this step
G4ParticleDefinition* particle =step->GetTrack()->GetDefinition();
G4String pname = particle->GetParticleName();
handle = step->GetPreStepPoint()->GetTouchableHandle();
//G4String volname=handle->GetVolume()->GetLogicalVolume()->GetName();
G4String phname=handle->GetVolume()->GetName();
//Muons
if  (pname=="mu-")
 {
 muontr=step->GetTrack();
 G4ThreeVector point = step->GetPostStepPoint()->GetPosition();
 G4double time=step->GetTrack()->GetGlobalTime();
 if ((point.z()<-30 *mm) && (point.z()>-57* mm) && (point.perp()<52*mm)
	 && (flag==0))
   { 
   flag=1;
   G4double En = (step->GetTrack()->GetDynamicParticle()->GetKineticEnergy())/MeV;
   eventaction->SetMuonEnergy(En);
   }
 if (flag>0)
   {	
    G4double destep = step->GetTotalEnergyDeposit();
    eventaction->AddMuoninf(destep,point,time);	
   }
 if (!((point.z()<-30 *mm) && (point.z()>-57* mm) && (point.perp()<52*mm)))
    flag=0;
 }
//Photons
if (pname=="opticalphoton")
 {
  G4ThreeVector point1 = step->GetPreStepPoint()->GetPosition();
  G4int copy=handle->GetVolume()->GetCopyNo();
  if (point1.z()<-60*mm)
     step->GetTrack()->SetTrackStatus(fStopAndKill);
  //G4cout <<"fgggg  "<<point1<<G4endl;}
  if ((strncmp(phname, "PTM", 3)==0) && (copy>0) )
    {
	G4double time=step->GetTrack()->GetGlobalTime();
	eventaction->incphotonnumber();
	eventaction->PMTsig(1,time,copy);
	photnum++;
	step->GetTrack()->SetTrackStatus(fStopAndKill);
	//G4cout <<"fgggged  "<<copy <<G4endl;
    }
 }

}
void SteppingAction::Susp()
{
muontr->SetTrackStatus(fSuspend);
}






