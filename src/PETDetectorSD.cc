#ifndef PETDETECTORSD_CC
#define PETDETECTORSD_CC

#include "PETDetectorSD.hh"
#include "PETDetectorHit.hh"

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
    PulseCollection = new PETDetectorHitsCollection(SensitiveDetectorName,
                                                       collectionName[0]);
    PulseCollection->SetColID(0);
}

G4bool
PETDetectorSD::ProcessHits(G4Step* aStep, G4TouchableHistory* obsolete)
{
    G4StepPoint* preStep = aStep->GetPreStepPoint();
    G4TouchableHistory* touchable = (G4TouchableHistory*)(preStep->GetTouchable());

    G4cout << "Local time in SD " << aStep->GetTrack()->GetLocalTime()/ns << G4endl;
}

void
PETDetectorSD::EndOfEvent(G4HCofThisEvent* HCE)
{
    int HCID = GetCollectionID(0);
    HCE->AddHitsCollection(HCID, PulseCollection);
}

#endif // PETDETECTORSD_CC
