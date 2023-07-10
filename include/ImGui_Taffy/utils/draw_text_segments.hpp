#pragma once

#include <cstdint> // for: uint32_t
#include <cstddef> // for: size_t

namespace ImGui_Taffy {

// NOTE: originally `color` here was 'ImU32' type, but we dont want to include
// the whole <imgui.h> here for only that type

struct TextSegment
{
    const char* textStart = nullptr;
    const char* textEnd   = nullptr;

    uint32_t    color     = 0;
    bool        underline = false;
    const char* url       = nullptr;

    constexpr TextSegment(
        const char* text_start, const char* text_end, 
        uint32_t col = 0, bool underline = false, const char* url = nullptr)
        : textStart(text_start)
        , textEnd(text_end)
        , color(col)
        , underline(underline)
        , url(url)
    {}

    template <size_t N>
    constexpr TextSegment(
        const char (&text)[N], 
        uint32_t col = 0, bool underline = false, const char* url = nullptr)
        : textStart(text)
        , textEnd(text + (N-1))
        , color(col)
        , underline(underline)
        , url(url)
    {}

    TextSegment(const char* text, uint32_t col = 0, bool underline = false, const char* url = nullptr);
};

// -----------------------------------------------------------------------------

void draw_text_segments(const TextSegment* segments, size_t segments_count, float wrapWidth, bool keepIndent);

void draw_text_segments(const TextSegment* segments, size_t segments_count, bool keepIndent);

// -----------------------------------------------------------------------------

template <size_t N>
inline void draw_text_segments(const TextSegment (&segments)[N], float wrapWidth, bool keepIndent)
{
    draw_text_segments(segments, N, wrapWidth, keepIndent);
}

template <size_t N>
inline void draw_text_segments(const TextSegment (&segments)[N], bool keepIndent)
{
    draw_text_segments(segments, N, keepIndent);
}

} // namespace ImGui_Taffy
