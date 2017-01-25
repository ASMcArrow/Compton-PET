#include "PETRun.hh"
#include "G4SDManager.hh"
#include "G4THitsMap.hh"
#include "GatePulse.hh"
#include "GatePulseCollection.hh"

PETRun::PETRun() : G4Run()
{
    CollNames = new std::vector<G4String>;
    CollIDs = new std::vector<G4int>;
//    HCollections = new std::vector<G4double*>;

    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    G4VSensitiveDetector* detector = SDman->FindSensitiveDetector("Detector");

    CollNum = detector->GetNumberOfCollections();
    for (G4int i = 0; i < CollNum; i++)
    {
        G4String collName =  detector->GetCollectionName(i);
        CollNames->push_back(collName);
        CollIDs->push_back(SDman->GetCollectionID(collName));

//        G4double* collection = new G4double[300];
//        for (int i = 0; i < 300; i++)
//            collection[i] = 0;

 //       HCollections->push_back(collection);
    }

    Verbose = 0;
}

PETRun::~PETRun() {}

void PETRun::RecordEvent(const G4Event* aEvent)
{
    numberOfEvent++;

    G4HCofThisEvent* HCE = aEvent->GetHCofThisEvent();
    if(HCE!=NULL)
    {
        GatePulseCollection* HC = (GatePulseCollection*)(HCE -> GetHC((*CollIDs)[0]));
        if(HC!=NULL)
        {
            for (G4int i = 0; i < HC->entries(); i++)
            {
                GatePulse *pulse = (GatePulse*)(HC->GetHit(i));
                if (Verbose)
                {
                    G4cout << "GatePulseCollection: " << "i = "<< i << " Energy is " << pulse->GetEnergy()
                           << " Time is" << pulse->GetTime() << G4endl;
                }
//                G4int num = hit->GetReplicaNum();
//                (*HCollections)[0][num] += hit->GetEdep();
            }
        }
    }
}

void PETRun::Merge(const G4Run * aRun)
{
//    const PETRun *localRun = static_cast<const PETRun*>(aRun);
//    std::vector<G4double*>* localcollection = localRun->HCollections;

//    for (int i = 0; i < CollNum; i++)
//    {
//        for (int j = 0; j < 300; j++)
//        {
//            (*HCollections)[i][j]+=(*localcollection)[i][j];
//        }
//    }

//    G4Run::Merge(aRun);
}

