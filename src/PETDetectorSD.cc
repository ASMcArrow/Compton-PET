#ifndef PETDETECTORSD_CC
#define PETDETECTORSD_CC

#include "PETDetectorSD.hh"
#include "GatePulse.hh"

#include "G4Step.hh"
#include "G4VTouchable.hh"
#include "G4VProcess.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
#include "G4TrackVector.hh"

#include <cstdio>

using namespace CLHEP;

PETDetectorSD::PETDetectorSD(G4String name, std::vector<G4String> *collnames):
    G4VSensitiveDetector(name)
{
    for (G4int i = 0; i < collnames->size(); i++)
    {
        collectionName.insert((*collnames)[i]);
    }

    SensitiveDetectorName = name;
}

PETDetectorSD::~PETDetectorSD()
{}

void
PETDetectorSD::Initialize(G4HCofThisEvent*)
{
    PulseCollection = new GatePulseCollection(SensitiveDetectorName,
                                              collectionName[0]);
    PulseCollection->SetColID(0);
}

G4bool
PETDetectorSD::ProcessHits(G4Step* aStep, G4TouchableHistory* obsolete)
{
    if (aStep->GetTrack()->GetParticleDefinition()->GetParticleName() == "gamma")
    {
        if (aStep->GetTrack()->GetTotalEnergy() == 0)
        {
            G4cout << "Energy is zero " << aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() << " " <<
                      aStep->GetTrack()->GetTrackStatus() << G4endl;
            const std::vector<const G4Track*>* secondaries = aStep->GetSecondaryInCurrentStep();
            G4cout << "Secondaries are " << secondaries->size() << G4endl;
            for (G4int i = 0; i < secondaries->size(); i++)
                G4cout << (*secondaries)[0]->GetParticleDefinition()->GetParticleName() << G4endl;
        }
        else
            G4cout << aStep->GetTrack()->GetTrackStatus() << G4endl;

        GatePulse* pulse = new GatePulse(aStep);
        PulseCollection->insert(pulse);
        aStep->GetTrack()->SetTrackStatus(fStopAndKill);
    }
}

void
PETDetectorSD::EndOfEvent(G4HCofThisEvent* HCE)
{
    int HCID = GetCollectionID(0);
    HCE->AddHitsCollection(HCID, PulseCollection);
}

#endif // PETDETECTORSD_CC
