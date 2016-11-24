#ifndef PETPARALLELWORLD_HH
#define PETPARALLELWORLD_HH

#include "globals.hh"
#include "G4VUserParallelWorld.hh"
#include "CLHEP/Units/SystemOfUnits.h"

using namespace CLHEP;

class PETParallelWorld : public G4VUserParallelWorld
{
public:
    PETParallelWorld(G4String worldName);
    ~PETParallelWorld();

    void Construct();
    void ConstructSD();

private:
    G4LogicalVolume *GhostZBoxLog;
};

#endif // PETPARALLELWORLD_HH
