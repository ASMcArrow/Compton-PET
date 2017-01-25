#ifndef GATEPULSE_HH
#define GATEPULSE_HH

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4Event.hh"

class GatePulse : public G4VHit
{

public:
    GatePulse(G4Step* step);
    ~GatePulse();

    GatePulse(const GatePulse &right);
    const GatePulse& operator = (const GatePulse &right);
    int operator == (const GatePulse &right) const;

    inline void *operator new(size_t);
    inline void operator delete(void *aHit);

    G4double GetTime() { return Time; }
    G4double GetEnergy() { return Energy; }
    G4ThreeVector GetHitPosition() { return HitPosition; }

private:
   // G4ThreeVector SourcePosition;
   // For the source position we need to use UserTrackInformation class
   // as Primary Vertex is contained only in G4Event.
    G4double Time;
    G4double Energy;
    G4ThreeVector HitPosition;
};

typedef G4THitsCollection<GatePulse> GatePulseCollection;
extern G4ThreadLocal G4Allocator<GatePulse>* GatePulseAllocator;

inline void* GatePulse::operator new(size_t)
{
    if(!GatePulseAllocator)
        GatePulseAllocator = new G4Allocator<GatePulse>;

    return (void *)GatePulseAllocator->MallocSingle();
}

inline void GatePulse::operator delete(void *aHit)
{
    GatePulseAllocator->FreeSingle((GatePulse*) aHit);
}


#endif // GATEPULSE_HH
