#ifndef PETSTEPPINGACTION_H
#define PETSTEPPINGACTION_H

#include "G4UserSteppingAction.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

class PrimaryGeneratorAction;

class PETSteppingAction : public G4UserSteppingAction {

public:
    PETSteppingAction()
    {}

    ~PETSteppingAction()
    {}

    void UserSteppingAction(const G4Step* aStep);

private:
    G4int TrackID = 0;
    G4int IsPair = 0;
    G4double AzimAngle = 0;
    G4bool Verbosity = 0;
};

#endif
