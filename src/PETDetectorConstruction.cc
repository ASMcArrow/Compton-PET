#include "PETDetectorConstruction.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4NistManager.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"
#include "G4VisAttributes.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4RunManager.hh"
#include "G4VSolid.hh"
#include "G4Sphere.hh"

using namespace CLHEP;

PETDetectorConstruction::PETDetectorConstruction()
{}

G4VPhysicalVolume* PETDetectorConstruction::Construct()
{
    // Cleanup old geometry
    G4GeometryManager::GetInstance()->OpenGeometry();
    G4PhysicalVolumeStore::GetInstance()->Clean();
    G4LogicalVolumeStore::GetInstance()->Clean();
    G4SolidStore::GetInstance()->Clean();

    G4VisAttributes* visAttributes = new G4VisAttributes;
    visAttributes->SetForceWireframe(true);
    visAttributes->SetForceAuxEdgeVisible(true);

    G4NistManager* nistManager = G4NistManager::Instance();
    G4Material* Water = nistManager->FindOrBuildMaterial("G4_WATER");
    G4Material* Air = nistManager->FindOrBuildMaterial("G4_AIR");
    G4Material* Bone = nistManager->FindOrBuildMaterial("G4_B-100_BONE");

    // World
    G4Box* world = new G4Box("World", 3*m, 3*m, 3*m);
    G4LogicalVolume *worldLogic = new G4LogicalVolume(world, Air, "WorldLogic");
    G4VPhysicalVolume *worldPhys = new G4PVPlacement(0, G4ThreeVector(), worldLogic, "WorldPhys", 0, false, 0);
    worldLogic->SetVisAttributes(visAttributes);

    // Phantom
    G4Box* phantom = new G4Box("Phantom", 15*cm, 15*cm, 30*cm);
    G4LogicalVolume *phantomLogic = new G4LogicalVolume(phantom, Bone, "PhantomLogic");
    G4VPhysicalVolume *phantomPhys = new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, 30*cm), phantomLogic, "PhantomPhys", worldLogic, false, 0);

    return worldPhys;
}
