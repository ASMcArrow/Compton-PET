#include "GateBackToBack.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4Gamma.hh"
#include "G4GenericIon.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include "GateConstants.hh"
#include "G4PhysicalConstants.hh"
#include "G4StokesVector.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

GateBackToBack::GateBackToBack(std::vector<G4double> frameVector, G4double stop, G4int numOfThreads, G4String name) :
    FrameVector(frameVector), Stop(stop), NumOfThreads(numOfThreads), Name(name)
{
    SetParticleDefinition(G4Gamma::Definition());
    particle_position = G4ThreeVector(0, 0, 0);

    PosSPS = new G4SPSPosDistribution();
    PosSPS->SetBiasRndm(GetBiasRndm());
    PosSPS->SetPosDisType("Volume");
    PosSPS->SetPosDisShape("Sphere");
    PosSPS->SetRadius(1*cm);
    PosSPS->SetCentreCoords(G4ThreeVector(0*m, 0*m, 0*m));

    AngSPS = new G4SPSAngDistribution();
    AngSPS->SetPosDistribution(PosSPS);
    AngSPS->SetBiasRndm(GetBiasRndm());
    AngSPS->SetAngDistType("iso");

    AccolinearityFlag = false;
    AccoValue = 0.58*deg;

    HalfLife = /*20.334*60*/1*s;
    Intensity = 1000*becquerel;

    NextTime = 0;

    t = 0;
}

GateBackToBack::~GateBackToBack()
{
    delete PosSPS;
    delete AngSPS;
}

G4double GateBackToBack::CalculateCurrentIntensity()
{
    return Intensity*pow(2, -(FrameVector[t]-FrameVector[0])/HalfLife);
}

void GateBackToBack::GeneratePrimaryVertex(G4Event* aEvent)
{
    G4double intensity = CalculateCurrentIntensity();

    if (t > FrameVector.size()-1)
    {
        G4cout << "ERROR: The time frame is already finished." << G4endl;
        return;
    }

    // We need to split the time interval into the number of threads
    G4double timeThreshold = 0;
    G4double timeInFrame = FrameVector[t];
    if (t <= (int)FrameVector.size()-2)
        timeThreshold = (FrameVector[t+1] - FrameVector[t])/NumOfThreads + FrameVector[t];
    else
        timeThreshold = (Stop - FrameVector[FrameVector.size()-1])/NumOfThreads + FrameVector[FrameVector.size()-1];

    while (timeInFrame < timeThreshold)
    {
        if (NextTime != 0)
        {
            timeInFrame = NextTime;
            NextTime = 0;
        }
        else
        {

            timeInFrame = timeInFrame + (-log(G4UniformRand())*(1.0/(intensity/becquerel)))*s;
        }

        if (timeInFrame <= timeThreshold)
        {
            //        G4int trackID = G4UniformRand()*100;
            //        while (TrackID == trackID)
            //            trackID = G4UniformRand()*100;
            //        TrackID = trackID;

            G4cout << "TimeInFrame " << timeInFrame/s << G4endl;
            G4cout << "TimeThreshold " << timeThreshold/s << G4endl;
            G4cout << "Intensity " << intensity << G4endl;

            particle_position = PosSPS->GenerateOne();
            G4PrimaryVertex* vertex = new G4PrimaryVertex(particle_position, timeInFrame);

            G4ParticleMomentum particleMomDir = AngSPS->GenerateOne();
            G4double mass = GetParticleDefinition()->GetPDGMass();
            G4double totEnergy = 511*keV;
            G4double particleMom = std::sqrt(totEnergy*totEnergy - mass*mass);
            G4double px = particleMom * particleMomDir.x();
            G4double py = particleMom * particleMomDir.y();
            G4double pz = particleMom * particleMomDir.z();

            G4ThreeVector direction;

            if (AccolinearityFlag == true)
            {
                G4double dev = G4RandGauss::shoot(0., AccoValue/GateConstants::fwhm_to_sigma);
                G4double phi = (twopi*G4UniformRand())/2.0;
                direction = {sin(dev)*cos(phi), sin(dev)*sin(phi), cos(dev)};
                direction.rotateUz(particleMomDir);
            }
            else
            {
                direction = {-particleMomDir.x(), -particleMomDir.y(), -particleMomDir.z()};
            }

            // Polarization
            G4double a1 = 0.22;
            G4double a2 = 1 - a1*a1;
            G4StokesVector* polarization1 = new G4StokesVector(G4ThreeVector(a1*a1-a2*a2, 2*a1*a2, 0));
            G4StokesVector* polarization2 = new G4StokesVector(G4ThreeVector(-(a1*a1-a2*a2), -2*a1*a2, 0));

            G4PrimaryParticle* particle1 = new G4PrimaryParticle(GetParticleDefinition(), px, py, pz);
            particle1->SetMass(mass);
            particle1->SetTotalEnergy(totEnergy);
            particle1->SetCharge(GetParticleDefinition()->GetPDGCharge());
            particle1->SetWeight(1);
            particle1->SetPolarization(polarization1->p1(), polarization1->p2(), polarization1->p3());
            // particle1->SetTrackID(trackID);
            vertex->SetPrimary(particle1);
            vertex->SetT0(timeInFrame);

            G4PrimaryParticle* particle2 = new G4PrimaryParticle(GetParticleDefinition(), px, py, pz);
            particle2->SetMass(mass);
            particle2->SetTotalEnergy(511*keV);
            particle2->SetCharge(GetParticleDefinition()->GetPDGCharge());
            particle2->SetWeight(1);
            particle2->SetMomentumDirection(G4ThreeVector(direction.x(), direction.y(), direction.z()));
            particle2->SetPolarization(polarization2->p1(), polarization2->p2(), polarization2->p3());
            // particle2->SetTrackID(trackID);
            vertex->SetPrimary(particle2);
            vertex->SetT0(timeInFrame);

            aEvent->AddPrimaryVertex(vertex);
        }
        else
        {
            NextTime = timeInFrame;
        }
    }

    t = t + 1;
}



