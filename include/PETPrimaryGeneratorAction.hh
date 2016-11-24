#ifndef PETPRIMARYGENERATORACTION_H
#define PETPRIMARYGENERATORACTION_H

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4SingleParticleSource.hh"

class G4Event;

class PETPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{

public:
    PETPrimaryGeneratorAction();
    ~PETPrimaryGeneratorAction();

    void GeneratePrimaries(G4Event* event);

private:
    G4SingleParticleSource* CircleSource;
};

#endif


