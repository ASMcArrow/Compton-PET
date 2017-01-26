#include "PETTrackingAction.hh"
#include "G4TrackingManager.hh"
#include "G4Track.hh"
#include "G4TrackVector.hh"
#include "G4TrackStatus.hh"

using namespace CLHEP;

void PETTrackingAction::PreUserTrackingAction(const G4Track* track)
{
    if (track->GetParticleDefinition()->GetParticleName() == "e-")
        G4cout << "Electron " << track->GetCreatorProcess()->GetProcessName() << G4endl;

}

void PETTrackingAction::PostUserTrackingAction(const G4Track* track)
{}
