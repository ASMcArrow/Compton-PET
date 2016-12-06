#ifndef GATEVSOURCE_H
#define GATEVSOURCE_H

#include <vector>

#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4SingleParticleSource.hh"
#include "G4PrimaryParticle.hh"

#include "G4SPSPosDistribution.hh"
#include "G4SPSEneDistribution.hh"
#include "G4SPSAngDistribution.hh"

class GateVSource : public G4SingleParticleSource
{

public:
    GateVSource(G4String name, G4String type);
    virtual ~GateVSource();

    virtual void SetName( G4String value ) { Name = value; }
    virtual G4String GetName() { return Name; }

    virtual void SetType( G4String value ) { Type = value; }
    virtual G4String GetType() { return Type; }

    virtual void SetSourceID(G4int value) { SourceID = value; }
    virtual G4int GetSourceID() { return SourceID; }

    virtual void SetAccolinearityFlag( G4bool value ) { AccolinearityFlag = value; }
    virtual G4bool GetAccolinearityFlag() { return AccolinearityFlag; }

    virtual void SetAccoValue( G4double value ) { AccoValue = value; }
    virtual G4double GetAccoValue() { return AccoValue; }

    virtual G4SPSPosDistribution* GetPosDist() { return PosSPS; }
    virtual G4SPSEneDistribution* GetEneDist() { return EneSPS; }
    virtual G4SPSAngDistribution* GetAngDist() { return AngSPS; }

    // Main functions

    virtual void GeneratePrimaryVertex(G4Event* event);
    void GeneratePrimariesForBackToBackSource(G4Event* aEvent);

    void SetNumberOfParticles(int n) { NbOfParticles = n;}
    G4int GetNumberOfParticles() { return NbOfParticles; }

protected:
    G4SPSPosDistribution* PosSPS;
    G4SPSEneDistribution* EneSPS;
    G4SPSAngDistribution* AngSPS;

    G4String Name;
    G4String Type;
    G4int SourceID;
    G4bool AccolinearityFlag;
    G4double AccoValue;

    G4double Energy;
    G4double Weight;
    G4int NbOfParticles;
};

#endif
