#ifndef PETRUN_HH
#define PETRUN_HH

#include "G4Run.hh"
#include "G4Event.hh"

#include <vector>

class PETRun : public G4Run
{
public:

  PETRun(const G4String detectorName, G4bool verbose);
  virtual ~PETRun();

  // virtual method from G4Run.
  // The method is overriden in this class for scoring.
  virtual void RecordEvent(const G4Event*);
  virtual void Merge(const G4Run*);

   std::vector<G4double*>* GetHCollections() { return HCollections; }

private:
  G4int CollNum;
  std::vector<G4String>* CollNames;
  std::vector<G4int>* CollIDs;

  G4bool Verbose;

  std::vector<G4double*>* HCollections;

//  G4double* EDep;
//  G4double* C11;
};

#endif // PETRUN_HH
