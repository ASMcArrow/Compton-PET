#include "PETSteppingAction.hh"

#include "G4Track.hh"
#include "G4TrackStatus.hh"
#include "G4CsvAnalysisManager.hh"
#include "G4ThreeVector.hh"
#include "G4VProcess.hh"
#include "G4PrimaryParticle.hh"

static G4int i = 0;

void PETSteppingAction::UserSteppingAction(const G4Step* aStep)
{
    if (aStep->GetPostStepPoint()->GetMaterial())
    {
        if ((aStep->GetPostStepPoint()->GetMaterial()->GetName() == "CZT")&&
                (aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() == "compt")&&
                (aStep->IsFirstStepInVolume())&&(!aStep->GetTrack()->GetCreatorProcess()))
        {
            G4int trackID =  aStep->GetTrack()->GetTrackID();

            G4ThreeVector reference = G4ThreeVector(1,0,0);
            G4ThreeVector initDir =  aStep->GetPreStepPoint()->GetMomentumDirection();
            reference = reference.rotateUz(initDir);

            G4ThreeVector endDir = aStep->GetPostStepPoint()->GetMomentumDirection();
            G4ThreeVector endDirPerp = endDir.perpPart(initDir);

            // G4cout << endDirPerp.azimAngle(reference, initDir)/deg << G4endl;
            G4cout << endDir.azimAngle(reference, initDir)/deg << G4endl;

            if (TrackID == trackID)
                IsPair++;
            else
                IsPair = 0;

            if (IsPair == 1)
                G4cout << "It is a pair" << G4endl;
            else if (IsPair > 1)
                G4cout << "Error! More than two photons." << G4endl;
            else if (IsPair == 0)
                G4cout << "It is a new photon" << G4endl;

            TrackID = trackID;
        }


    }
}


