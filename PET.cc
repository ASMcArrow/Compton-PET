// #undef G4MULTITHREADED
//#undef G4VIS_USE

#include <cstdio>
#include <ctime>

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#include "G4UImanager.hh"
#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include "PETPhysicsList.hh"
#include "PETDetectorConstruction.hh"
#include "PETPrimaryGeneratorAction.hh"
#include "PETActionInitialization.hh"
#include "PETParallelWorld.hh"
#include "GateApplicationMgr.hh"
#include "G4GeometryManager.hh"

#include <math.h>

int main(int argc,char** argv)
{
    // Set the custom seed for the random engine
    G4Random::setTheEngine(new CLHEP::RanecuEngine);
    G4long seed = time(NULL);
    G4Random::setTheSeed(seed);

    // Set PET aquisition time.
    // StartTime indicates the time since the isotopes were created or approximately the stop of irradiation.
    GateApplicationMgr* appManager = new GateApplicationMgr;
    appManager->SetFrameTime(0*s, 6*s, 6);
    appManager->Initialize();

//    G4GeometryManager::GetInstance()->SetWorldMaximumExtent(30*cm);

//    PETDetectorConstruction* massWorld = new PETDetectorConstruction;
//    //massWorld->RegisterParallelWorld(new PETParallelWorld("PETParallelWorld"));
//    runManager->SetUserInitialization(massWorld);

//    G4VModularPhysicsList* physicsList = new PETPhysicsList;
//    physicsList->SetVerboseLevel(0);
//    runManager->SetUserInitialization(physicsList);

//    PETActionInitialization* actionInit = new PETActionInitialization(massWorld);
//    runManager->SetUserInitialization(actionInit);
//    runManager->Initialize();

#ifdef G4VIS_USE
    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
    delete visManager;
#else
    appManager->StartPET();
#endif

    delete appManager;
    return 0;
}
