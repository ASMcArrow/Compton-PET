#include "PETParallelWorld.hh"

#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"
#include "G4PVReplica.hh"
#include "G4VisAttributes.hh"
#include "G4SDManager.hh"
#include "G4PVDivision.hh"
#include "G4PVParameterised.hh"
#include "G4PSDoseDeposit3D.hh"
#include "G4PSEnergyDeposit.hh"
#include "PETLayerParameterization.hh"
#include "PETDetectorSD.hh"

PETParallelWorld::PETParallelWorld(G4String worldName)
    :G4VUserParallelWorld(worldName)
{}

PETParallelWorld::~PETParallelWorld()
{}

void PETParallelWorld::Construct()
{
    G4VisAttributes* visAttributes = new G4VisAttributes;
    visAttributes->SetColor(0,0,1);

    G4VPhysicalVolume *ghostWorld = GetWorld();
    G4LogicalVolume *worldLog = ghostWorld->GetLogicalVolume();

    // Place volumes in the parallel world

    G4double nDivisions = 300.0;

    G4Box* ghostDetector = new G4Box("GhostDetectorBox", 15.0*cm, 15.0*cm, 30.0*cm);
    G4LogicalVolume* ghostDetectorLog = new G4LogicalVolume(ghostDetector, 0, "GhostDetectorLog");
    new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, 30.0*cm), ghostDetectorLog, "GhostDetectorPhys", worldLog, 0, 0);
    ghostDetectorLog->SetVisAttributes(visAttributes);

    // Divide along Z coordinate

    G4VSolid *layer  = new G4Box("Layer", 15.0*cm, 15.0*cm, 30.0*cm/nDivisions);
    GhostZBoxLog = new G4LogicalVolume(layer, 0, "LayerLog");
    G4VPVParameterisation* layerParam = new PETLayerParameterization;
    new G4PVParameterised("Layers", GhostZBoxLog, ghostDetectorLog, kZAxis, nDivisions, layerParam);
    GhostZBoxLog->SetVisAttributes(visAttributes);
}

void PETParallelWorld::ConstructSD()
{
    G4SDManager::GetSDMpointer()->SetVerboseLevel(1);

    G4CollectionNameVector* collections = new G4CollectionNameVector;
    collections->insert("EdepHitsCollection");
    collections->insert("C11HitsCollection");
    collections->insert("C10HitsCollection");
    collections->insert("O15HitsCollection");
    collections->insert("PositronHitsCollection");

    G4VSensitiveDetector* isoDetector = new PETDetectorSD("IsoDetector", collections);
    G4SDManager::GetSDMpointer()->AddNewDetector(isoDetector);
    SetSensitiveDetector(GhostZBoxLog, isoDetector);
}
