#ifndef PETDETECTORSD_HH
#define PETDETECTORSD_HH

#include "G4VSensitiveDetector.hh"
#include "PETDetectorHit.hh"
#include "globals.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class PETDetectorSD : public G4VSensitiveDetector
{

public:
  PETDetectorSD(G4String name, std::vector<G4String>* collnames);
  ~PETDetectorSD();

  void Initialize(G4HCofThisEvent* );
  G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* obsolete);
  void EndOfEvent(G4HCofThisEvent* HCE);

private:
  PETDetectorHitsCollection* EdepHitsCollection;
  PETDetectorHitsCollection* C11HitsCollection;
  PETDetectorHitsCollection* C10HitsCollection;
  PETDetectorHitsCollection* O15HitsCollection;
  PETDetectorHitsCollection* PositronHitsCollection;

  G4String SensitiveDetectorName;
};

#endif // PETDETECTORSD_HH
