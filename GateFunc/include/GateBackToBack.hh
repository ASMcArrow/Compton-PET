#ifndef GATEBACKTOBACK_H
#define GATEBACKTOBACK_H

#include <vector>

#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4SingleParticleSource.hh"
#include "G4PrimaryParticle.hh"

#include "G4SPSPosDistribution.hh"
#include "G4SPSEneDistribution.hh"
#include "G4SPSAngDistribution.hh"

class GateBackToBack : public G4SingleParticleSource
{

public:
    GateBackToBack(std::vector<G4double> frameVector, G4double stop, G4int numOfThreads, G4String name);
    virtual ~GateBackToBack();

    virtual void SetName( G4String value ) { Name = value; }
    virtual G4String GetName() { return Name; }

    virtual void SetAccolinearityFlag( G4bool value ) { AccolinearityFlag = value; }
    virtual G4bool GetAccolinearityFlag() { return AccolinearityFlag; }

    virtual void SetAccoValue( G4double value ) { AccoValue = value; }
    virtual G4double GetAccoValue() { return AccoValue; }

    virtual G4SPSPosDistribution* GetPosDist() { return PosSPS; }
    virtual G4SPSEneDistribution* GetEneDist() { return EneSPS; }
    virtual G4SPSAngDistribution* GetAngDist() { return AngSPS; }

    virtual void GeneratePrimaryVertex(G4Event* event);

protected:
    G4int NumOfThreads;

    G4SPSPosDistribution* PosSPS;
    G4SPSEneDistribution* EneSPS;
    G4SPSAngDistribution* AngSPS;

    std::vector<G4double> FrameVector;
    G4double Stop;

    G4String Name;
    G4bool AccolinearityFlag;
    G4double AccoValue;

    G4double Energy;
    G4double Weight;
    G4int TrackID;
    G4double t;
};

#endif
