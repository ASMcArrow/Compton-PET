#include "PETRun.hh"
#include "G4SDManager.hh"
#include "G4THitsMap.hh"
#include "PETDetectorHit.hh"

PETRun::PETRun() : G4Run()
{
//    CollNames = new std::vector<G4String>;
//    CollIDs = new std::vector<G4int>;
//    HCollections = new std::vector<G4double*>;

//    G4SDManager* SDman = G4SDManager::GetSDMpointer();
//    G4VSensitiveDetector* detector = SDman->FindSensitiveDetector(detectorName);

//    CollNum = detector->GetNumberOfCollections();
//    for (G4int i = 0; i < CollNum; i++)
//    {
//        G4String collName =  detector->GetCollectionName(i);
//        CollNames->push_back(collName);
//        G4int collID = SDman->GetCollectionID(collName);
//        CollIDs->push_back(SDman->GetCollectionID(collName));

//        G4double* collection = new G4double[300];
//        for (int i = 0; i < 300; i++)
//            collection[i] = 0;

//        HCollections->push_back(collection);
//    }

   // Verbose = verbose;
}

PETRun::~PETRun() {}

void PETRun::RecordEvent(const G4Event* aEvent)
{
//    numberOfEvent++;

//    G4HCofThisEvent* HCE = aEvent->GetHCofThisEvent();
//    if(HCE!=NULL)
//    {
//        PETDetectorHitsCollection* HC = (PETDetectorHitsCollection*)(HCE -> GetHC((*CollIDs)[0]));
//        if(HC!=NULL)
//        {
//            for (G4int i = 0; i < HC->entries(); i++)
//            {
//                PETDetectorHit *hit = (PETDetectorHit*)(HC->GetHit(i));
//                if (Verbose)
//                {
//                    G4cout << "HitsVector Initial: " << "i = "<< i << " Energy deposition is " << hit->GetEdep()
//                           << " Position is" << hit->GetReplicaNum() << G4endl;
//                }
//                G4int num = hit->GetReplicaNum();
//                (*HCollections)[0][num] += hit->GetEdep();
//            }
//        }

//        for (G4int i = 1; i < CollNum; i++)
//        {
//            HC = (PETDetectorHitsCollection*)(HCE -> GetHC((*CollIDs)[i]));
//            if(HC!=NULL)
//            {
//                for (G4int j = 0; j < HC->entries(); j++)
//                {
//                    PETDetectorHit *hit = (PETDetectorHit*)(HC->GetHit(j));
//                    G4int num = hit->GetReplicaNum();
//                    (*HCollections)[i][num] += 1;
//                }
//            }
//        }
//    }
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

