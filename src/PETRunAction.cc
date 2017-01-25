#include "PETRunAction.hh"
#include "PETRun.hh"

#include "G4RunManager.hh"
#include "G4CsvAnalysisManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

PETRunAction::PETRunAction() : G4UserRunAction()
{}

PETRunAction::~PETRunAction()
{}

G4Run* PETRunAction::GenerateRun()
{
    return new G4Run;
}

void PETRunAction::BeginOfRunAction(const G4Run* aRun)
{
//    G4CsvAnalysisManager* analysisManager = G4CsvAnalysisManager::Instance();
//    G4cout << " Histogram id is " <<
//              analysisManager->CreateH2("Stokes", "Distribution of Azimuthal Angles",
//                                        100, (G4double)(-180*deg), (G4double)(180*deg),
//                                        100, (G4double)(-180*deg), (G4double)(180*deg),
//                                        "deg", "deg") << G4endl;
}

void PETRunAction::EndOfRunAction(const G4Run* aRun)
{
 //   if(!IsMaster()) return;

/*    G4CsvAnalysisManager* analysisManager = G4CsvAnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile()*/;
}
