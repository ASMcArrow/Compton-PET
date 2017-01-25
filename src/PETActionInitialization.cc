#include "PETPrimaryGeneratorAction.hh"
#include "PETActionInitialization.hh"
#include "PETRunAction.hh"
#include "PETSteppingAction.hh"
#include "PETTrackingAction.hh"
#include "GateClock.hh"
#include "G4MTRunManager.hh"

G4ThreadLocal std::vector<G4double> PETActionInitialization::FrameVector = GateClock::GetInstance()->GetFrameVector();
G4ThreadLocal G4double PETActionInitialization::Stop = GateClock::GetInstance()->GetEndTime();

PETActionInitialization::PETActionInitialization(PETDetectorConstruction *geometry, G4int numOfThreads)
    : G4VUserActionInitialization(), NumOfThreads(numOfThreads)
{}

PETActionInitialization::~PETActionInitialization()
{}

void PETActionInitialization::BuildForMaster() const
{
    SetUserAction(new PETRunAction);
}

void PETActionInitialization::Build() const
{
    SetUserAction(new PETPrimaryGeneratorAction(FrameVector, Stop, NumOfThreads));
    SetUserAction(new PETRunAction);
    SetUserAction(new PETSteppingAction);
    SetUserAction(new PETTrackingAction);
}
