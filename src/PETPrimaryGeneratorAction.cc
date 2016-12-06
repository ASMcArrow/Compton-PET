#include "PETPrimaryGeneratorAction.hh"
#include "G4Gamma.hh"

using namespace CLHEP;

PETPrimaryGeneratorAction::PETPrimaryGeneratorAction()
{
    GateSource = new GateVSource("HotSpot", "backtoback");
    GateSource->SetParticleDefinition(G4Gamma::Definition());

    G4SPSEneDistribution* energy = GateSource->GetEneDist();
    energy->SetEnergyDisType("Mono");
    energy->SetMonoEnergy(0.511*MeV);

    G4SPSPosDistribution* position = GateSource->GetPosDist();
    position->SetPosDisType("Volume");
    position->SetPosDisShape("Sphere");
    position->SetRadius(1*mm);
    position->SetCentreCoords(G4ThreeVector(0*m, 0*m, 0*m));

    G4SPSAngDistribution* angular = GateSource->GetAngDist();
    angular->SetAngDistType("iso");
}

PETPrimaryGeneratorAction::~PETPrimaryGeneratorAction()
{
    delete GateSource;
}

void PETPrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
    GateSource->GeneratePrimaryVertex(event);
}
