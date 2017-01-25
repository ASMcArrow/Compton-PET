#ifndef PETTRACKINGACTION_HH
#define PETTRACKINGACTION_HH

#include "G4UserTrackingAction.hh"
#include "G4Track.hh"
#include "G4String.hh"
#include "globals.hh"

class PETTrackingAction : public G4UserTrackingAction
{

public:
    PETTrackingAction()  {}
    ~PETTrackingAction() {}

    void PreUserTrackingAction(const G4Track *track);
    void PostUserTrackingAction(const G4Track *track);
};

#endif // PETTRACKINGACTION_HH
