#include "RuntimeEngine.hpp"

void RuntimeEngine::ExtractSegment () {

    //Allocate memory for segment.
    int alloca = reinterpret_cast <int> (VirtualAlloc (reinterpret_cast <void*> (Primal::AllocParameters.m_base), Primal::AllocParameters.m_size, Primal::AllocParameters.m_type, Primal::AllocParameters.m_protect));

    //Verify it.
    if (alloca == 0x00000000) {
        Primal::PanicUtil::Release ("RuntimeEngine@ExtractSegment->VirtualAlloc", "Can't allocate virtual memory.");
    }

    //Copy segment into new memory & verify it.
    if (!memcpy (reinterpret_cast <void*> (alloca), SegmentNativeData, GetSegmentData ().m_size)) {
        Primal::PanicUtil::Release ("RuntimeEngine@ExtractSegment->memcpy", "Can't copy segment to allocation memory.");
    }

    //Set new global allocation base.
    Primal::AllocParameters.m_base = alloca;

}

void RuntimeEngine::ExecuteReconstruction () {

    //Check if iat present.
    if (!GetReconstructProcessorDefinition().m_iat->empty ()) {
        //Do reconstruction...
        GetIatReconstructor().ReconstructNative();
    }

    //Check if reloc's array present.
    if (GetReconstructProcessorDefinition().m_relocations->m_relocations != 0x00000000) {
        //Do reconstruction...
        GetRelocReconstructor().ReconstructNative();
    }

}

void RuntimeEngine::InvokeOEP () {

    //Set template of oep & set call address.
    AdditionalRuntime::DllEntryPoint EntryPoint = reinterpret_cast <AdditionalRuntime::DllEntryPoint> (Primal::AllocParameters.m_base + GetSegmentData().m_oep);

    //Call OEP a.k.a DllEntryPoint.
    EntryPoint (reinterpret_cast <HMODULE> (Primal::AllocParameters.m_base), DLL_PROCESS_ATTACH, NULL);

}