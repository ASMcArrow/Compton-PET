#ifndef GATEAPPLICATIONMGR_HH
#define GATEAPPLICATIONMGR_HH

#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4MTRunManager.hh"
#include "G4RunManager.hh"
#include <vector>

class GateApplicationMgr
{

public:
    GateApplicationMgr();
    virtual ~GateApplicationMgr();

    void Initialize();
    void StartPET();

private:
#ifdef G4MULTITHREADED
    G4MTRunManager* RunManager;
#else
    G4RunManager* RunManager;
#endif
};

#endif

