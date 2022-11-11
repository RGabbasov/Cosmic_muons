#include "PrimaryGeneratorAction.hh"
#include "EventAction.h"

#include "G4ParticleTypes.hh"
#include "G4GeneralParticleSource.hh"
#include "G4SPSAngDistribution.hh"
#include "G4SPSEneDistribution.hh"
#include "G4SPSPosDistribution.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4Event.hh"



PrimaryGeneratorAction::PrimaryGeneratorAction(EventAction* evtact)
{
eventaction=evtact;
ParticleGun = new G4GeneralParticleSource();

G4SPSEneDistribution* EnergyDist = ParticleGun->GetCurrentSource()->GetEneDist();
G4SPSAngDistribution* AngularDist = ParticleGun->GetCurrentSource()->GetAngDist();
G4SPSPosDistribution* PositionDist = ParticleGun->GetCurrentSource()->GetPosDist();


//ParticleGun->SetParticleDefinition(G4Gamma::GammaDefinition());
// ParticleGun->SetParticleDefinition(G4Electron::ElectronDefinition());
//ParticleGun->SetParticleDefinition(G4OpticalPhoton::OpticalPhotonDefinition());
ParticleGun->SetParticleDefinition(G4MuonMinus::MuonMinusDefinition());
//ParticleGun->SetParticleDefinition(G4Alpha::AlphaDefinition());
EnergyDist->SetEnergyDisType("Mono");EnergyDist->SetMonoEnergy(100*MeV);
//EnergyDist->SetEnergyDisType("Mono");EnergyDist->SetMonoEnergy(7*eV);
//EnergyDist->SetEnergyDisType("Lin");
//EnergyDist-> SetEmin(100*MeV);
//EnergyDist-> SetEmax(300*MeV);
//EnergyDist-> SetGradient(2);
//EnergyDist->SetInterCept(200*MeV);
//PositionDist->SetPosDisType("Point");
//PositionDist->SetCentreCoords(G4ThreeVector(-26.5*mm, 2.35*mm, -3.5*cm));

PositionDist->SetPosDisType("Plane");
PositionDist->SetPosDisShape("Circle");
PositionDist->SetRadius(5*cm);
PositionDist->SetCentreCoords(G4ThreeVector(0.*cm, 0.*cm, -5*cm));

AngularDist->SetAngDistType("iso");

//AngularDist->SetMaxTheta(1.077);
//AngularDist->SetMinTheta(1.077);
AngularDist->SetMaxTheta(5*pi/6);
AngularDist->SetMinTheta(2*pi/3);
//AngularDist->SetMaxPhi(pi-0.886);
//AngularDist->SetMinPhi(pi-0.886);
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
ParticleGun->GeneratePrimaryVertex(event);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
delete ParticleGun;
}




