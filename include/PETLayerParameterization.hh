#ifndef PETLAYERPARAMETERIZATION_HH
#define PETLAYERPARAMETERIZATION_HH

#include "G4VPVParameterisation.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Box.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

class PETLayerParameterization : public G4VPVParameterisation
{
public:
    PETLayerParameterization() {}
    virtual ~PETLayerParameterization(){}

    void ComputeDimensions (G4Box& box, const G4int copyNo, const G4VPhysicalVolume* physVol) const
    {}

    virtual void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume *physVol ) const
    {
        physVol->SetTranslation(G4ThreeVector(0.0 ,0.0, -30*cm + 30.0*cm/300.0 + copyNo*2*30.0*cm/300.0));
    }
};

#endif // PETLAYERPARAMETERIZATION_HH
