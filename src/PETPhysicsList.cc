#include "PETPhysicsList.hh"

// Physic lists (contained inside the Geant4 source code, in the 'physicslists folder')
#include "G4HadronPhysicsQGSP_BIC.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4StoppingPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronElasticPhysicsHP.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4IonBinaryCascadePhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4NeutronTrackingCut.hh"
#include "G4LossTableManager.hh"
#include "G4UnitsTable.hh"
#include "G4ProcessManager.hh"
#include "G4IonFluctuations.hh"
#include "G4IonParametrisedLossModel.hh"
#include "G4EmProcessOptions.hh"
#include "G4ParallelWorldPhysics.hh"
#include "G4ParallelWorldScoringProcess.hh"
#include "G4EmParameters.hh"
#include "CLHEP/Units/SystemOfUnits.h"
#include "G4WentzelVIModel.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4EmDNAPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"

using namespace CLHEP;

PETPhysicsList::PETPhysicsList() : G4VModularPhysicsList()
{
  G4LossTableManager::Instance();
  defaultCutValue = 0.1*mm;
  cutForGamma     = defaultCutValue;
  cutForElectron  = defaultCutValue;
  cutForPositron  = defaultCutValue;

  G4EmParameters* emParameters = G4EmParameters::Instance();
  emParameters->SetMinEnergy(0*eV);
  emParameters->SetMaxEnergy(160*MeV);
  emParameters->SetNumberOfBinsPerDecade(50);

  emParameters->SetApplyCuts(true);
  emParameters->SetVerbose(true);

  SetVerboseLevel(1);

  RegisterPhysics(new G4EmStandardPhysics_option4);
  RegisterPhysics(new G4RadioactiveDecayPhysics);
  RegisterPhysics(new G4HadronPhysicsQGSP_BIC);
  RegisterPhysics(new G4EmExtraPhysics);
  RegisterPhysics(new G4HadronElasticPhysics);
  RegisterPhysics(new G4StoppingPhysics);
  RegisterPhysics(new G4IonBinaryCascadePhysics);
  RegisterPhysics(new G4NeutronTrackingCut);
}

PETPhysicsList::~PETPhysicsList()
{}

void PETPhysicsList::ConstructProcess()
{
    AddParallelScoring();
    G4VModularPhysicsList::ConstructProcess();
}

void PETPhysicsList::AddParallelScoring()
{
    G4ParallelWorldScoringProcess* theParallelWorldScoringProcess
            = new G4ParallelWorldScoringProcess("ParaWorldScoringProc");
    theParallelWorldScoringProcess->SetParallelWorld("PETParallelWorld");

    theParticleIterator->reset();
    while((*theParticleIterator)())
    {
        G4ProcessManager* pmanager = theParticleIterator->value()->GetProcessManager();
        pmanager->AddProcess(theParallelWorldScoringProcess);
        pmanager->SetProcessOrderingToLast(theParallelWorldScoringProcess, idxAtRest);
        pmanager->SetProcessOrdering(theParallelWorldScoringProcess, idxAlongStep, 1);
        pmanager->SetProcessOrderingToLast(theParallelWorldScoringProcess, idxPostStep);
    }
}

void PETPhysicsList::SetCuts()
{
 // set cut values for gamma at first and for e- second and next for e+,
 // because some processes for e+/e- need cut values for gamma
    SetCutValue(cutForGamma, "gamma");
    SetCutValue(cutForElectron, "e-");
    SetCutValue(cutForPositron, "e+");
}

