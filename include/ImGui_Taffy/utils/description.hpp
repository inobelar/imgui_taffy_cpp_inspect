#pragma once

#include <cstdint> // for: uint32_t

namespace ImGui_Taffy {

namespace description {

    // NOTE: colors here must be in 'ImU32' type, but we dont want to include 
    // the whole <imgui.h> here for only that type
    extern const uint32_t TYPE_NAME_COLOR;
    extern const uint32_t CODE_INLINE_COLOR;
    extern const uint32_t LINK_COLOR;
    extern const uint32_t WARNING_COLOR;

    void TypeName(const char* text);

    void CodeInline(const char* text);

    void Link(const char* text, const char* url);
    void Link(const char* url);

} // namespace description

} // namespace ImGui_Taffy
