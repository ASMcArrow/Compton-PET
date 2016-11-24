#include "PETPrimaryGeneratorAction.hh"

#include "G4Proton.hh"

using namespace CLHEP;

PETPrimaryGeneratorAction::PETPrimaryGeneratorAction()
{
    CircleSource = new G4SingleParticleSource;
    CircleSource->SetParticleDefinition(G4Proton::Definition());

    G4SPSEneDistribution* energy = CircleSource->GetEneDist();
    energy->SetEnergyDisType("Gauss");
    energy->SetBeamSigmaInE(0 *MeV);
    energy->SetMonoEnergy(110*MeV);

    G4SPSPosDistribution* position = CircleSource->GetPosDist();
    position->SetPosDisType("Plane");
    position->SetPosDisShape("Circle");
    position->SetRadius(1.5*cm);
    position->SetCentreCoords(G4ThreeVector(0*m, 0*m,  -1*cm));

    G4SPSAngDistribution* angular = CircleSource->GetAngDist();
    angular->SetParticleMomentumDirection(G4ThreeVector(0.0,0.0,1.0));
    angular->DefineAngRefAxes("angref1", G4ThreeVector(-1.0,0.0,0.0));
    CircleSource->SetNumberOfParticles(1);
}

PETPrimaryGeneratorAction::~PETPrimaryGeneratorAction()
{
    delete CircleSource;
}

void PETPrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
    CircleSource->GeneratePrimaryVertex(event);
}
