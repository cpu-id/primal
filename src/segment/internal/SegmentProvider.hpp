#pragma once

#include "../../Vendor.hpp"

//Segment data.
extern const unsigned char SegmentNativeData [];

//Provider for segment.
class Segment {

public:

    struct SegmentData {

        //Size of segment. (For memcpy)
        int m_size;
        //RVA to OriginalEntryPoint.
        int m_oep;

    };

    struct ReconstructProcessorDefinition {

        // ____________________________________
        //
        // RELOCATIONS.
        //
        // Process view:
        //
        // Get RVA from iterator ->
        // Get address from segment by this RVA ->
        // Subtract old allocation from address ->
        // Add new allocation address to address ->
        // Get next relocation from iterator...
        //
           AdditionalRuntime::RelocationDefinition* m_relocations;
        //
        // ------------------------------------
        //
        // IMPORT ADDRESS TABLE.
        //
        // Process view:
        //
        // Get ImportInfo from iterator ->
        // Get function address by ImportInfo [lib|name] ->
        // Get RelocationInfo from iterator ->
        // Get RVA's & RVA's type from RelocationInfo ->
        // Get new IAA* by RelocationInfo [PUBLIC/INTERNAL] ->
        // Set new IAA* to allocation + RVA for current RVA's type ->
        // Get next RVA's type from iterator...
        //
        // Remarks [1]: IAA - Import Absolute Address.
        //
           std::map <std::string, std::vector <AdditionalRuntime::ImportDefinition>>* m_iat;
        //
        // ____________________________________

    };

    /**
     *
     * @point - Get segment size & oep to offset.
     *
     */

    virtual SegmentData GetSegmentData () = 0;

    /**
     *
     * @point - Get allocation size. (& Additional stuff like base, type, protect)
     *
     */

    virtual AdditionalRuntime::AllocaParameters GetAllocationParameters () = 0;

    /**
     *
     * @point - Get pointer to relocations and IAT data.
     *
     */

    virtual ReconstructProcessorDefinition GetReconstructProcessorDefinition () = 0;

};