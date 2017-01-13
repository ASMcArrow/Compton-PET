#undef G4MULTITHREADED

#include "GateApplicationMgr.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "GateClock.hh"
#include "G4GeometryManager.hh"

#include "PETDetectorConstruction.hh"
#include "PETPhysicsList.hh"
#include "PETActionInitialization.hh"

GateApplicationMgr::GateApplicationMgr()
{
#ifdef G4MULTITHREADED
    RunManager = new G4MTRunManager;
    RunManager->SetNumberOfThreads(8);
#else
    RunManager = new G4RunManager;
#endif
}

void GateApplicationMgr::SetFrameTime(G4double start, G4double end, G4int numOfFrames)
{
    GateClock::GetInstance()->SetStartTime(start);
    GateClock::GetInstance()->SetEndTime(end);

    std::vector<G4double> frameVector;

    G4double frameLength = (end-start)/numOfFrames;
    for (G4int i = 0; i < numOfFrames; i++)
        frameVector.push_back(frameLength*i);

    // G4cout << frameVector.size() << G4endl;
    GateClock::GetInstance()->SetFrameVector(frameVector);
}

void GateApplicationMgr::Initialize()
{
    G4GeometryManager::GetInstance()->SetWorldMaximumExtent(30*cm);

    PETDetectorConstruction* massWorld = new PETDetectorConstruction;
    //massWorld->RegisterParallelWorld(new PETParallelWorld("PETParallelWorld"));
    RunManager->SetUserInitialization(massWorld);

    G4VModularPhysicsList* physicsList = new PETPhysicsList;
    physicsList->SetVerboseLevel(0);
    RunManager->SetUserInitialization(physicsList);

#ifdef G4MULTITHREADED
    PETActionInitialization* actionInit = new PETActionInitialization(massWorld, RunManager->GetNumberOfThreads());
#else
    PETActionInitialization* actionInit = new PETActionInitialization(massWorld, 1);
#endif
    RunManager->SetUserInitialization(actionInit);
    RunManager->Initialize();
}

GateApplicationMgr::~GateApplicationMgr()
{
    delete RunManager;
}

void GateApplicationMgr::StartPET()
{
    while (GateClock::GetInstance()->NextSlice())
    {
#ifdef G4MULTITHREADED
        RunManager->BeamOn(RunManager->GetNumberOfThreads());
#else
        RunManager->BeamOn(1);
#endif
    }
}
