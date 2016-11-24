#ifndef PETDETECTORCONSTRUCTION_H
#define PETDETECTORCONSTRUCTION_H

#include "G4VUserDetectorConstruction.hh"
#include "G4Material.hh"

class PETDetectorMessenger;
class G4LogicalVolume;
class G4VPhysicalVolume;

using namespace CLHEP;

class PETDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    PETDetectorConstruction();
    ~PETDetectorConstruction() {}

    G4VPhysicalVolume* Construct();

 // void ConstructSDandField();
 // This method is used in multi-threaded applications to build
 // per-worker non-shared objects: SensitiveDetectors and Field managers
};

#endif

