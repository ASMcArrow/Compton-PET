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

    G4Element* Cd = nistManager->FindOrBuildElement(48);
    G4Element* Zn = nistManager->FindOrBuildElement(30);
    G4Element* Te = nistManager->FindOrBuildElement(52);
    G4Material* CZT = new G4Material("CZT", 5.78*g/cm3, 3, kStateSolid);
    CZT->AddElement(Cd, 0.368);
    CZT->AddElement(Zn, 0.214);
    CZT->AddElement(Te, 0.418);

    // World
    G4Box* world = new G4Box("World", 3*m, 3*m, 3*m);
    G4LogicalVolume *worldLogic = new G4LogicalVolume(world, Air, "WorldLogic");
    G4VPhysicalVolume *worldPhys = new G4PVPlacement(0, G4ThreeVector(), worldLogic, "WorldPhys", 0, false, 0);
    worldLogic->SetVisAttributes(visAttributes);

    // CZT Sphere
    G4Sphere* detector = new G4Sphere("CZTDetector", 5*cm, 10*cm, 0*deg, 360*deg, 0*deg, 180*deg);
    G4LogicalVolume *detectorLogic = new G4LogicalVolume(detector, CZT, "CZTDetectorLogic");
    G4VPhysicalVolume *detectorPhys = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), detectorLogic, "CZTDetectorPhys", worldLogic, false, 0);
    detectorLogic->SetVisAttributes(visAttributes);

    return worldPhys;
}
