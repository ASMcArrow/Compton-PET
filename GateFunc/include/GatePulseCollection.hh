#ifndef GATEPULSECOLLECTION_HH
#define GATEPULSECOLLECTION_HH

#include "G4THitsCollection.hh"
#include "GatePulse.hh"

class GatePulseCollection : public G4THitsCollection<GatePulse>
{
public:
    GatePulseCollection(G4String detName,G4String colName):G4THitsCollection<GatePulse>(detName, colName){}
    virtual ~GatePulseCollection() {}


};

#endif // GATEPULSECOLLECTION_HH
