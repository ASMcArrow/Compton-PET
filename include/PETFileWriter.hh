#ifndef PETFILEWRITER_HH
#define PETFILEWRITER_HH

#include "GateCoincidencePulse.hh"
#include <deque>

class PETFileWriter
{
public:
    PETFileWriter(){}
    ~PETFileWriter(){}

    bool WriteFile(std::deque<GateCoincidencePulse*>* pulses, G4String mode);

private:
    bool WriteGPUReconFile(std::deque<GateCoincidencePulse*>* pulses);
    bool WriteLMFFile(std::deque<GateCoincidencePulse*>* pulses) {}
};

#endif
