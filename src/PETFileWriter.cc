#include "PETFileWriter.hh"

using namespace CLHEP;

bool PETFileWriter::WriteFile(std::deque<GateCoincidencePulse*>* pulses, G4String mode)
{
    if (mode == "GPURECON")
        return WriteGPUReconFile(pulses);
    else if (mode == "LMF")
        return WriteLMFFile(pulses);
    else
    {
        G4cout << "Wrong writing mode!" << G4endl;
        return false;
    }
}

bool PETFileWriter::WriteGPUReconFile(std::deque<GateCoincidencePulse*>* pulses)
{
    FILE* f;
    f = fopen("testfile.lm","wb");

    for (G4int i = 0; i < pulses->size(); i++)
    {
        if ((*pulses)[i]->size() == 2)
        {
            GateCoincidencePulse* pulse = (*pulses)[i];
            float x[10]={(float)(*pulse)[0]->GetHitPosition()[0],
                         (float)(*pulse)[0]->GetHitPosition()[1],
                         (float)(*pulse)[0]->GetHitPosition()[2],
                         (float) 0, // ToF value (float)
                         (float) 0, // Random estimation (float)
                         (float)(*pulse)[1]->GetHitPosition()[0],
                         (float)(*pulse)[1]->GetHitPosition()[1],
                         (float)(*pulse)[1]->GetHitPosition()[2],
                         (float) 0, // ToF scatter estimation (float)
                         (float) 0}; // non-ToF scatter estimation float)
            fwrite(x, sizeof(x[0]), sizeof(x)/sizeof(x[0]), f);
        }
    }

    fclose(f);

    f = fopen("testfileToF.lm","wb");

    for (G4int i = 0; i < pulses->size(); i++)
    {
        if ((*pulses)[i]->size() == 2)
        {
            GateCoincidencePulse* pulse = (*pulses)[i];
            float x[10]={(float)(*pulse)[0]->GetHitPosition()[0],
                         (float)(*pulse)[0]->GetHitPosition()[1],
                         (float)(*pulse)[0]->GetHitPosition()[2],
                         (float)(((*pulse)[1]->GetTime() - (*pulse)[0]->GetTime())/s)*(c_light/(mm/s)), // ToF value (float)
                         (float) 0, // Random estimation (float)
                         (float)(*pulse)[1]->GetHitPosition()[0],
                         (float)(*pulse)[1]->GetHitPosition()[1],
                         (float)(*pulse)[1]->GetHitPosition()[2],
                         (float) 0, // ToF scatter estimation (float)
                         (float) 0}; // non-ToF scatter estimation float)
            fwrite(x, sizeof(x[0]), sizeof(x)/sizeof(x[0]), f);
            G4cout << "ToF value is " << ((*pulse)[1]->GetTime() - (*pulse)[0]->GetTime())*c_light/mm << G4endl;
        }
    }

    fclose(f);
}
