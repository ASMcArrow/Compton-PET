#ifndef PETPRIMARYGENERATORACTION_H
#define PETPRIMARYGENERATORACTION_H

#include "G4VUserPrimaryGeneratorAction.hh"
#include "GateBackToBack.hh"

class G4Event;

class PETPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{

public:
    PETPrimaryGeneratorAction(std::vector<G4double> frameVector, G4double stop, G4int numOfThreads);
    ~PETPrimaryGeneratorAction();

    void GeneratePrimaries(G4Event* event);

private:
    GateBackToBack* GateSource;
    std::vector<G4double> FrameVector;
    G4double Stop;
};

#endif


