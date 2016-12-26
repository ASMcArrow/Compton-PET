#include "GateApplicationMgr.hh"

#include "GateClock.hh"
#include "G4UImanager.hh"
#include "GateVSource.hh"
#include "GateSourceMgr.hh"

GateApplicationMgr::GateApplicationMgr()
{
#ifdef G4MULTITHREADED
    RunManager = new G4MTRunManager;
    RunManager->SetNumberOfThreads(8);
#else
    RunManager = new G4RunManager;
#endif
}

GateApplicationMgr::~GateApplicationMgr()
{
    delete RunManager;
}

void GateApplicationMgr::StartPET()
{
    while (GateClock::GetInstance()->NextSlice())
    {
        RunManager->BeamOn(GateClock::GetInstance()->GetCurrentActivitySlice());
    }
}
