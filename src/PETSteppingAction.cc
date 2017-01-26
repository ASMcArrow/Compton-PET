#include "PETSteppingAction.hh"

#include "G4Track.hh"
#include "G4TrackStatus.hh"
#include "G4CsvAnalysisManager.hh"
#include "G4ThreeVector.hh"
#include "G4VProcess.hh"
#include "G4PrimaryParticle.hh"

void PETSteppingAction::UserSteppingAction(const G4Step* aStep)
{

//    if (!aStep->GetTrack()->GetCreatorProcess()&&(aStep->GetTrack()->GetTotalEnergy() > 511*keV))
//           G4cout << "Energy is " << aStep->GetTrack()->GetTotalEnergy()/keV << " "
//                  << aStep->GetTrack()->GetParticleDefinition()->GetParticleName() << " "
//                  << aStep->GetTrack()->GetParentID() << G4endl;

    //    if (aStep->GetPostStepPoint()->GetMaterial())
    //    {
    //        if ((aStep->GetPostStepPoint()->GetMaterial()->GetName() == "CZT")&&
    //                (aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() == "pol-compt")&&
    //                (aStep->IsFirstStepInVolume())&&(!aStep->GetTrack()->GetCreatorProcess()))
    //        {
    //            G4CsvAnalysisManager* analysisManager = G4CsvAnalysisManager::Instance();
    //            G4int trackID =  aStep->GetTrack()->GetTrackID();
    //            if (Verbosity > 0)
    //            {
    //                G4cout << "TrackID inside stepping action is " << trackID << G4endl;
    //                G4cout << "The Point is " << aStep->GetPostStepPoint()->GetPosition() << G4endl;
    //            }

    //            G4ThreeVector reference = G4ThreeVector(1,0,0);
    //            G4ThreeVector initDir =  aStep->GetPreStepPoint()->GetMomentumDirection();
    //            reference = reference.rotateUz(initDir);

    //            G4ThreeVector endDir = aStep->GetPostStepPoint()->GetMomentumDirection();
    //            G4ThreeVector endDirPerp = endDir.perpPart(initDir);

    //            // G4cout << endDirPerp.azimAngle(reference, initDir)/deg << G4endl;
    //            G4double azimAngle = endDir.azimAngle(reference, initDir)/deg;
    //            if (Verbosity > 0)
    //                G4cout << endDir.azimAngle(reference, initDir)/deg << G4endl;

    //            aStep->GetTrack()->SetTrackStatus(fStopAndKill);

    //            if (TrackID == trackID)
    //                IsPair++;
    //            else
    //                IsPair = 0;

    //            if (IsPair == 1)
    //            {
    //                if (Verbosity > 0)
    //                    G4cout << "It is a pair. Writing " << AzimAngle << " and " << azimAngle
    //                           << " in the histogram." << G4endl;
    //                analysisManager->FillH2(0, AzimAngle*deg, azimAngle*deg);
    //            }
    //            else if (IsPair > 1)
    //            {
    //                if (Verbosity > 0)
    //                    G4cout << "Error! More than two photons." << G4endl;
    //                AzimAngle = 0;
    //            }
    //            else if (IsPair == 0)
    //                AzimAngle = azimAngle;

    //            TrackID = trackID;
    //        }
    //    }
}


