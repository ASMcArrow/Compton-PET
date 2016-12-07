#include "PETRunAction.hh"
#include "PETRun.hh"

#include "G4RunManager.hh"
#include "PETDetectorConstruction.hh"
#include "G4THitsMap.hh"
#include "G4SDManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4Run.hh"
#include "G4HadronicInteraction.hh"
#include "G4HadronicInteractionRegistry.hh"
#include "G4CascadeInterface.hh"
#include "G4BinaryCascade.hh"
#include "G4AblaInterface.hh"
#include "G4INCLXXInterface.hh"
#include "G4INCLXXInterfaceStore.hh"
#include "G4FermiBreakUp.hh"
#include "G4NistManager.hh"
#include "G4Evaporation.hh"

#include <fstream>
#define _USE_MATH_DEFINES

PETRunAction::PETRunAction(const G4String detectorName) : G4UserRunAction()
{
    DetectorName = detectorName;
}

PETRunAction::~PETRunAction()
{}

G4Run* PETRunAction::GenerateRun()
{
    return new PETRun(DetectorName, 0);
}

void PETRunAction::BeginOfRunAction(const G4Run* aRun)
{}

void PETRunAction::EndOfRunAction(const G4Run* aRun)
{
    if(!IsMaster()) return;

//    PETRun* run = (PETRun*)aRun;
//    std::vector<G4double*>* collections = run->GetHCollections();

//    std::ofstream eDepFile("PET_EnergyDistribution.txt");

//    for (int j = 0; j < 300; j++)
//    {
//        eDepFile << j << " " << (*collections)[0][j] << "\n";
//    }

//    std::ofstream C11File("PET_C11Distribution.txt");

//    for (int j = 0; j < 300; j++)
//    {
//        C11File << j << " " << (*collections)[1][j] << "\n";
//    }

//    std::ofstream C10File("PET_C10Distribution.txt");

//    for (int j = 0; j < 300; j++)
//    {
//        C10File << j << " " << (*collections)[2][j] << "\n";
//    }

//    std::ofstream O15File("PET_O15Distribution.txt");

//    for (int j = 0; j < 300; j++)
//    {
//        O15File << j << " " << (*collections)[3][j] << "\n";
//    }

//    std::ofstream PosFile("PET_PositronDistribution.txt");

//    for (int j = 0; j < 300; j++)
//    {
//        PosFile << j << " " << (*collections)[4][j] << "\n";
//    }
}
