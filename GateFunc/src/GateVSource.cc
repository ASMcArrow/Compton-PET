#include "GateVSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4Gamma.hh"
#include "G4GenericIon.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include "GateConstants.hh"
#include "G4PhysicalConstants.hh"

GateVSource::GateVSource(G4String name, G4String type) : Name(name), Type(type)
{
    particle_position = G4ThreeVector(0, 0, 0);

    PosSPS = new G4SPSPosDistribution();
    PosSPS->SetBiasRndm(GetBiasRndm());

    EneSPS = new G4SPSEneDistribution();
    EneSPS->SetBiasRndm(GetBiasRndm());

    AngSPS = new G4SPSAngDistribution();
    AngSPS->SetPosDistribution(PosSPS);
    AngSPS->SetBiasRndm(GetBiasRndm());

    AccolinearityFlag = false;

    if (Type == G4String("backtoback"))
    {
        SetNumberOfParticles(2);
    }
}

GateVSource::~GateVSource()
{
    delete PosSPS;
    delete EneSPS;
    delete AngSPS;
}

void GateVSource::GeneratePrimariesForBackToBackSource(G4Event* aEvent)
{
    // Gammas Pair
    G4PrimaryParticle* particle1 = aEvent->GetPrimaryVertex(0)->GetPrimary(0);
    G4PrimaryParticle* particle2 = aEvent->GetPrimaryVertex(0)->GetPrimary(1);

    if(AccolinearityFlag == true)
    {
        G4ThreeVector gammaMom = particle1->GetMomentum();

        G4double dev = G4RandGauss::shoot(0., AccoValue/GateConstants::fwhm_to_sigma);
        G4double phi = (twopi*G4UniformRand())/2.0;

        G4ThreeVector direction(sin(dev)*cos(phi), sin(dev)*sin(phi), cos(dev));
        direction.rotateUz(gammaMom);

        particle1->SetMomentum(-gammaMom.x(), -gammaMom.y(), -gammaMom.z());
        particle2->SetMomentum(direction.x(), direction.y(), direction.z());
    }
    else
    {
        G4ThreeVector gammaMom = particle1->GetMomentum();
        particle2->SetMomentum(-gammaMom.x(),-gammaMom.y(),-gammaMom.z());
    }

    G4double phi = twopi * G4UniformRand();
    G4ThreeVector lpolarization(cos(phi), sin(phi), 0.0);
    lpolarization.rotateUz(particle1->GetMomentumDirection());
    G4ThreeVector ortlPolarization = lpolarization.orthogonal();

    particle1->SetPolarization(lpolarization.x(), lpolarization.y(), lpolarization.z());
    particle2->SetPolarization(ortlPolarization.x(), ortlPolarization.y(), ortlPolarization.z());
}

void GateVSource::GeneratePrimaryVertex(G4Event* aEvent)
{
    if(GetParticleDefinition() == NULL) return;

    particle_position = PosSPS->GenerateOne();

    G4PrimaryVertex* vertex = new G4PrimaryVertex(particle_position, GetParticleTime());

    for(G4int i = 0; i != GetNumberOfParticles(); ++i)
    {
        G4ParticleMomentum particleMomDir = AngSPS->GenerateOne();
        G4double kinEnergy = EneSPS->GenerateOne(GetParticleDefinition());
        G4double mass = GetParticleDefinition()->GetPDGMass();
        G4double totEnergy = kinEnergy + mass;
        G4double pMom = std::sqrt(totEnergy*totEnergy - mass*mass);
        G4double px = pMom * particleMomDir.x();
        G4double py = pMom * particleMomDir.y();
        G4double pz = pMom * particleMomDir.z();

        G4PrimaryParticle* particle = new G4PrimaryParticle(GetParticleDefinition(), px, py, pz);
        particle->SetMass(mass);
        particle->SetTotalEnergy(totEnergy);
        particle->SetKineticEnergy(kinEnergy);
        particle->SetCharge(GetParticleDefinition()->GetPDGCharge());
        particle->SetWeight(1);
        vertex->SetPrimary(particle);
    }

    aEvent->AddPrimaryVertex(vertex);

    if (Type == G4String("backtoback"))
        GeneratePrimariesForBackToBackSource(aEvent);
}



