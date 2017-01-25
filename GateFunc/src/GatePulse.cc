#include "GatePulse.hh"
#include "G4NavigationHistory.hh"
#include "G4PrimaryParticle.hh"

G4ThreadLocal G4Allocator<GatePulse>* GatePulseAllocator = 0;

using namespace CLHEP;

GatePulse::GatePulse(G4Step* step)
{
    Time = step->GetTrack()->GetGlobalTime();
    Energy = step->GetTrack()->GetTotalEnergy()/keV;
    HitPosition = step->GetPostStepPoint()->GetPosition();

//    if(step->GetTrack()->GetTotalEnergy()/keV > 511*keV)
//        G4cout << step->GetTrack()->GetParticleDefinition()->GetParticleName() << G4endl;
}

GatePulse::~GatePulse()
{}

GatePulse::GatePulse(const GatePulse &right)
    :G4VHit()
{
    Time = right.Time;
    Energy = right.Energy;
    HitPosition = right.HitPosition;
}

const GatePulse&
GatePulse::operator=(const GatePulse &right)
{
    Time = right.Time;
    Energy = right.Energy;
    HitPosition = right.HitPosition;

    return *this;
}

int GatePulse::operator==(const GatePulse &right) const
{
    return((Time==right.Time)&&(Energy==right.Energy)&&(HitPosition==right.HitPosition));
}
