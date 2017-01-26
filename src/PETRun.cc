#include "PETRun.hh"
#include "G4SDManager.hh"
#include "G4THitsMap.hh"
#include "GatePulse.hh"
#include "GatePulseCollection.hh"

PETRun::PETRun() : G4Run()
{
    CollNames = new std::vector<G4String>;
    CollIDs = new std::vector<G4int>;
    HCollections = new std::vector<GatePulseCollection*>;

    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    G4VSensitiveDetector* detector = SDman->FindSensitiveDetector("Detector");

    CollNum = detector->GetNumberOfCollections();
    for (G4int i = 0; i < CollNum; i++)
    {
        G4String collName =  detector->GetCollectionName(i);
        CollNames->push_back(collName);
        CollIDs->push_back(SDman->GetCollectionID(collName));

        GatePulseCollection* collection = new GatePulseCollection("Detector", collName);
        HCollections->push_back(collection);
    }

    Verbose = 1;
}

PETRun::~PETRun() {}

void PETRun::RecordEvent(const G4Event* aEvent)
{
    numberOfEvent++;

    G4HCofThisEvent* HCE = aEvent->GetHCofThisEvent();
    if(HCE!=NULL)
    {
        for (G4int i = 0; i < CollNum; i++)
        {
            GatePulseCollection* HC = (GatePulseCollection*)(HCE -> GetHC((*CollIDs)[i]));
            if(HC!=NULL)
            {
                for (G4int j = 0; j < HC->entries(); j++)
                {
                    GatePulse* p = (GatePulse*)HC->GetHit(j);
                    GatePulse* pulse = new GatePulse(*p);
                    if (Verbose)
                    {
                        G4cout << "GatePulseCollection: " << " j = "<< j << " Energy is " << pulse->GetEnergy()
                               << " Time is " << pulse->GetTime() << G4endl;
                    }
                    (*HCollections)[i]->insert(pulse);
                }
            }
        }
    }
}

void PETRun::Merge(const G4Run * aRun)
{
    const PETRun *localRun = static_cast<const PETRun*>(aRun);
    std::vector<GatePulseCollection*>* localcollection = localRun->HCollections;

    for (int i = 0; i < CollNum; i++)
    {
        GatePulseCollection* HC;
        for (int j = 0; j < (*localcollection)[i]->entries(); j++)
        {
            (*HCollections)[i]->insert((GatePulse*)(*localcollection)[i]->GetHit(j));
            if (Verbose)
            {
                GatePulse* pulse = (GatePulse*)(*localcollection)[i]->GetHit(j);
                G4cout << "Copying GatePulse number " << j << " Energy is " << pulse->GetEnergy()
                       << " Time is " << pulse->GetTime() << G4endl;
            }
        }

    }

    G4Run::Merge(aRun);
}

