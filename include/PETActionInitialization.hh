#ifndef PETACTIONINITIASLIZATION_HH
#define PETACTIONINITIASLIZATION_HH

#include "G4VUserActionInitialization.hh"
#include "PETDetectorConstruction.hh"

class PETActionInitialization : public G4VUserActionInitialization
{

public:
    PETActionInitialization(PETDetectorConstruction* geometry, G4int numOfThreads);
    virtual ~PETActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

    static G4ThreadLocal std::vector<G4double> FrameVector;
    static G4ThreadLocal G4double Stop;

    G4int NumOfThreads;
};

#endif // PETACTIONINITIASLIZATION_HH
