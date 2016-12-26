#ifndef GATESOURCEMGR_HH
#define GATESOURCEMGR_HH

#include "globals.hh"
#include <vector>
#include "G4Event.hh"
#include "GateVSource.hh"

class GateSourceMgr
{

public:
    GateSourceMgr();
    ~GateSourceMgr();

    void AddSource(GateVSource* pSource);

    // It is used internally by PrepareNextEvent
    // to decide which source has to be used for the current event.
    // GateVSource* GetNextSource();

    G4int GeneratePrimaries( G4Event* event );
    G4int GetNumberOfSources() { return Sources.size(); }

private:
    std::vector<GateVSource*> Sources;
    GateVSource* SelectedSource;
};

#endif
