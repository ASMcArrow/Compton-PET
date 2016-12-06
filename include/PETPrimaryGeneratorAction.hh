#ifndef PETPRIMARYGENERATORACTION_H
#define PETPRIMARYGENERATORACTION_H

#include "G4VUserPrimaryGeneratorAction.hh"
#include "GateVSource.hh"

class G4Event;

class PETPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{

public:
    PETPrimaryGeneratorAction();
    ~PETPrimaryGeneratorAction();

    void GeneratePrimaries(G4Event* event);

private:
    GateVSource* GateSource;
};

#endif


