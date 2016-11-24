#ifndef PETACTIONINITIASLIZATION_HH
#define PETACTIONINITIASLIZATION_HH

#include "G4VUserActionInitialization.hh"
#include "PETDetectorConstruction.hh"

class PETActionInitialization : public G4VUserActionInitialization
{
public:

    PETActionInitialization(PETDetectorConstruction* geometry);
    virtual ~PETActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

#endif // PETACTIONINITIASLIZATION_HH
