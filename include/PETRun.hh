#ifndef PETRUN_HH
#define PETRUN_HH

#include "G4Run.hh"
#include "G4Event.hh"
#include "GatePulseCollection.hh"

#include <vector>

class PETRun : public G4Run
{
public:

  PETRun();
  virtual ~PETRun();

  // virtual method from G4Run.
  // The method is overriden in this class for scoring.
  virtual void RecordEvent(const G4Event*);
  virtual void Merge(const G4Run*);

  std::vector<GatePulseCollection*>* GetHCollections() { return HCollections; }

private:
  G4int CollNum;
  std::vector<G4String>* CollNames;
  std::vector<G4int>* CollIDs;

  G4bool Verbose;

  std::vector<GatePulseCollection*>* HCollections;
};

#endif // PETRUN_HH
