#include "PETPrimaryGeneratorAction.hh"
#include "G4Gamma.hh"
#include "G4DynamicParticle.hh"

using namespace CLHEP;

PETPrimaryGeneratorAction::PETPrimaryGeneratorAction(std::vector<G4double> frameVector, G4double stop, G4int numOfThreads) : FrameVector(frameVector), Stop(stop)
{
    GateSource = new GateBackToBack(FrameVector, Stop, numOfThreads, "HotSpot");
}

PETPrimaryGeneratorAction::~PETPrimaryGeneratorAction()
{
    delete GateSource;
}

void PETPrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
    GateSource->GeneratePrimaryVertex(event);
}
