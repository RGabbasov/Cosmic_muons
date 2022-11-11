#include "StackingAction.h"
//#include "ConfigArray.h"

#include "RunAction.h"
#include "EventAction.h"
#include "SteppingAction.h"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4TransportationManager.hh"

#include <math.h>

StackingAction::StackingAction(RunAction* runact, EventAction* evact, SteppingAction* stepact )
{
runaction = runact;
eventaction = evact;
stepaction=stepact;
navigator = G4TransportationManager::GetTransportationManager()->GetNavigatorForTracking();
incr=0;
}

StackingAction::~StackingAction()
{
//G4cout <<"incphot  "<<incr<<G4endl;
}

G4ClassificationOfNewTrack StackingAction::ClassifyNewTrack(const G4Track* Track)
{

G4ClassificationOfNewTrack classification = fUrgent;

G4ParticleDefinition* particle = Track->GetDefinition();
G4String pname = particle->GetParticleName();
G4String ptype = particle->GetParticleType();
//if (pname=="mu-")
 //eventaction->SetParticleEnergy  (Track->GetKineticEnergy());
//if (pname=="mu-")
G4int f1=1,f2=1;	
	

if ((ptype=="nucleus") && (pname!="deuteron") && (pname!="triton") && 
	(pname!="He3") && (pname!="alpha"))  
    {
    classification = fKill;
   // eventaction->AddEnergyDeposit(Track->GetKineticEnergy());
 //
    }

if ((1==1) && ((pname=="e-") || (pname=="e+")))
    {
    classification = fKill;
    //eventaction->AddEnergyDeposit(Track->GetKineticEnergy());
    }
if (pname=="opticalphoton")
{
  incr++;
  if (incr<50000)
   {
   classification = fUrgent;
   }
  else 
   {
   classification = fWaiting;
   }

//stackManager->ReClassify();
//G4double time=Track->GetGlobalTime()/microsecond;
//G4String vol= Track->GetVolume()->GetLogicalVolume()->GetName();
//G4cout <<"volume "<<time <<G4endl;
//runaction->AddPhotonsignal(phenergy/eV,time);
//stepaction-> Susp();
//classification = fKill;
//}
}
if ((pname!="neutron") || ((pname=="neutron")&&(0==1)))
   {}
return classification;
}

