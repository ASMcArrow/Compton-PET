#include "PETRunAction.hh"
#include "PETRun.hh"
#include "GatePulseCollection.hh"

#include "G4RunManager.hh"
#include "G4CsvAnalysisManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

PETRunAction::PETRunAction() : G4UserRunAction()
{}

PETRunAction::~PETRunAction()
{}

G4Run* PETRunAction::GenerateRun()
{
    return new PETRun;
}

void PETRunAction::BeginOfRunAction(const G4Run* aRun)
{}

void PETRunAction::EndOfRunAction(const G4Run* aRun)
{
    if(!IsMaster()) return;

    PETRun* run = (PETRun*)aRun;
    std::vector<GatePulseCollection*>* collections = run->GetHCollections();
    FindCoincidences(collections);
}

void PETRunAction::FindCoincidences(std::vector<GatePulseCollection *>* collections)
{

    for (G4int num  = 0; num < collections->size(); num++)
    {
        GatePulseCollection* pristinePulseList = (*collections)[num];
        std::list<GatePulse*> sortedPulseList;
        std::list<GatePulse*>::iterator sortedIter;
        std::deque<GateCoincidencePulse*>::iterator coinceIter;

        // We will sort the pulses in time
        for (G4int i = 0; i < pristinePulseList->entries(); i++ )
        {
            GatePulse* pulse = (GatePulse*)pristinePulseList->GetHit(i);

            if(sortedPulseList.empty())
                sortedPulseList.push_back(pulse);

            else if(pulse->GetTime() < sortedPulseList.back()->GetTime())    // check if event is earlier than the earliest event in the buffer
                sortedPulseList.push_back(pulse);

            else
            {
                sortedIter = sortedPulseList.begin();
                while(pulse->GetTime() < (*sortedIter)->GetTime())
                    sortedIter++;
                sortedPulseList.insert(sortedIter, pulse);
            }

            // Look for coincidences. We will start from the earliest pulses.
            bool coincidenceOccured = false;
            for(G4int i = sortedPulseList.size()-1; i >= 0; i--)
            {
                GatePulse* pulse = sortedPulseList.back();
                sortedPulseList.pop_back();

                coinceIter = CoincidencePulses.begin();
                while( coinceIter != CoincidencePulses.end() && (*coinceIter)->IsInCoincidence(pulse) )
                {
                    coincidenceOccured = true;
                    (*coinceIter)->push_back(pulse);
                    coinceIter++;
                }
            }

            if(!coincidenceOccured)
            {
                GateCoincidencePulse* coincidence = new GateCoincidencePulse(pulse, CoincidenceWindow);
                CoincidencePulses.push_back(coincidence);
            }
            else
                delete pulse;
        }
    }
}
