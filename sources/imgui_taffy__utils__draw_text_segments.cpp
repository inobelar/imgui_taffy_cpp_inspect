#include <ImGui_Taffy/utils/draw_text_segments.hpp>

#include <imgui.h>
#include <imgui_internal.h>

#include <cstring> // for: strlen()

#include <ImGui_Taffy/open_link_func.hpp>

// -----------------------------------------------------------------------------

ImGui_Taffy::TextSegment::TextSegment(const char* text, uint32_t col, bool underline, const char* url)
    : textStart(text)
    , textEnd(text + strlen(text))
    , color(col)
    , underline(underline)
    , url(url)
{}

// -----------------------------------------------------------------------------

// based on: https://github.com/ocornut/imgui/issues/2313

/*
    This is my modified copy of `ImFont::CalcWordWrapPositionA`.

    Changes (in comparison to original function) marked with `CHANGED: ...` comments

    Author: https://github.com/Unit2Ed
    Published at: https://github.com/ocornut/imgui/issues/2313#issue-403605856
*/
const char* CalcWordWrapPositionA(
    const ImFont* font,

    float scale, const char* text, const char* text_end, float wrap_width,

    float line_start) // CHANGE: New line_start parameter
{
    // Simple word-wrapping for English, not full-featured. Please submit failing cases!
    // FIXME: Much possible improvements (don't cut things like "word !", "word!!!" but cut within "word,,,,", more sensible support for punctuations, support for Unicode punctuations, etc.)

    // For references, possible wrap point marked with ^
    //  "aaa bbb, ccc,ddd. eee   fff. ggg!"
    //      ^    ^    ^   ^   ^__    ^    ^

    // List of hardcoded separators: .,;!?'"

    // Skip extra blanks after a line returns (that includes not counting them in width computation)
    // e.g. "Hello    world" --> "Hello" "World"

    // Cut words that cannot possibly fit within one line.
    // e.g.: "The tropical fish" with ~5 characters worth of width --> "The tr" "opical" "fish"

    float line_width = line_start / scale; // CHANGE: This used to start at 0
    float word_width = 0.0f;
    float blank_width = 0.0f;
    wrap_width /= scale; // We work with unscaled widths to avoid scaling every characters

    const char* word_end = text;
    const char* prev_word_end = line_start > 0.0f ? word_end : nullptr; // CHANGE: Added condition
    bool inside_word = true;

    const char* s = text;
    while (s < text_end)
    {
        unsigned int c = (unsigned int)*s;
        const char* next_s;
        if (c < 0x80)
            next_s = s + 1;
        else
            next_s = s + ImTextCharFromUtf8(&c, s, text_end);
        if (c == 0)
            break;

        if (c < 32)
        {
            if (c == '\n')
            {
                line_width = word_width = blank_width = 0.0f;
                inside_word = true;
                s = next_s;
                continue;
            }
            if (c == '\r')
            {
                s = next_s;
                continue;
            }
        }

        const float char_width = ((int)c < font->IndexAdvanceX.Size ? font->IndexAdvanceX[(int)c] : font->FallbackAdvanceX);
        if (ImCharIsBlankW(c))
        {
            if (inside_word)
            {
                line_width += blank_width;
                blank_width = 0.0f;
                word_end = s;
            }
            blank_width += char_width;
            inside_word = false;
        }
        else
        {
            word_width += char_width;
            if (inside_word)
            {
                word_end = next_s;
            }
            else
            {
                prev_word_end = word_end;
                line_width += word_width + blank_width;
                word_width = blank_width = 0.0f;
            }

            // Allow wrapping after punctuation.
            inside_word = !(c == '.' || c == ',' || c == ';' || c == '!' || c == '?' || c == '\"');
        }

        // We ignore blank width at the end of the line (they can be skipped)
        if (line_width + word_width >= wrap_width)
        {
            // Words that cannot possibly fit within an entire line will be cut anywhere.
            if (word_width < wrap_width)
                s = prev_word_end ? prev_word_end : word_end;
            break;
        }

        s = next_s;
    }

    return s;
}

void UnderLine(ImU32 color, float thickness = 1.0f)
{
    ImVec2 min = ImGui::GetItemRectMin();
    ImVec2 max = ImGui::GetItemRectMax();
    min.y = max.y;
    ImGui::GetWindowDrawList()->AddLine(min, max, color, thickness);
}

/* 
    Based on @ocornut, with addition of 'indentation keeping' from @dougbinks
    
    Author: https://github.com/ocornut
    Published in: https://github.com/ocornut/imgui/issues/2313#issuecomment-458084296
    
    Author: https://gist.github.com/dougbinks
    Published in: https://gist.github.com/dougbinks/65d125e0c11fba81c5e78c546dcfe7af
 */
void ImGui_Taffy::draw_text_segments(const TextSegment* segments, size_t segments_count, float wrapWidth, bool keepIndent)
{
    const ImVec2 initialCursorScreenPos = ImGui::GetCursorScreenPos();
    
    float indentX = 0.0f;

    const ImFont* Font = ImGui::GetFont();

    for (size_t i = 0; i < segments_count; ++i)
    {
        const TextSegment& segment = segments[i];

        const char* textStart = segment.textStart;
        const char* textEnd   = segment.textEnd ? segment.textEnd : textStart + strlen(textStart);

        do
        {
            const float widthRemaining = ImGui::CalcWrapWidthForPos(ImGui::GetCursorScreenPos(), 0.0f);
            const char* drawEnd = CalcWordWrapPositionA(Font, 1.0f, textStart, textEnd, wrapWidth, wrapWidth - widthRemaining);
            if (textStart == drawEnd)
            {
                ImGui::NewLine();
                drawEnd = CalcWordWrapPositionA(Font, 1.0f, textStart, textEnd, wrapWidth, wrapWidth - widthRemaining);
            }

            // -----------------------------------------------------------------
            // Draw text segment

            if (segment.color != 0) {
                ImGui::PushStyleColor(ImGuiCol_Text, segment.color);
            }

            ImGui::TextUnformatted(textStart, (textStart == drawEnd) ? nullptr : drawEnd);

            if (segment.color != 0) {
                ImGui::PopStyleColor();
            }
            if (segment.underline)
            {
                UnderLine(segment.color);

                if (ImGui::IsItemHovered(ImGuiHoveredFlags_RectOnly)) {
                    ImGui::SetMouseCursor(ImGuiMouseCursor_TextInput);
                }
            }
            if(segment.url != nullptr)
            {
                if (ImGui::IsItemHovered(ImGuiHoveredFlags_RectOnly))
                {
                    // On hover: cursor::hand
                    ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);

                    // On hover: show tooltip with 'url'
                    if (ImGui::BeginTooltip())
                    {
                        ImGui::TextUnformatted(segment.url);
                     
                        ImGui::EndTooltip();
                    }
                }
                
                if (ImGui::IsItemClicked(ImGuiMouseButton_Left) )
                {
                    const auto open_link = get_open_link_func();

                    // On click: open url
                    if( open_link != nullptr)
                    {
                        open_link(segment.url);
                    }
                }
            }

            // -----------------------------------------------------------------
            // Indentation adding (if needed)

            if (keepIndent)
            {
                const float widthRemaining2 = ImGui::CalcWrapWidthForPos({initialCursorScreenPos.x, ImGui::GetCursorScreenPos().y}, 0.0f);
                const float indentNeeded = ImGui::GetContentRegionAvail().x - widthRemaining2;
                if (indentNeeded)
                {
                    ImGui::Indent( indentNeeded );
                    indentX += indentNeeded;
                }
            }

            // -----------------------------------------------------------------

            if ( (textStart == drawEnd) || (drawEnd == textEnd) )
            {
                ImGui::SameLine(0.0f, 0.0f);
                break;
            }

            textStart = drawEnd;

            while (textStart < textEnd)
            {
                const char c = *textStart;
                if (ImCharIsBlankA(c)) { textStart++; }
                else if (c == '\n') { textStart++; break; }
                else { break; }
            }
        } while (true);

    }

    // Reset indentation
    {
        if( indentX > 0.0f )
        {
            ImGui::Unindent( indentX );
        }
        indentX = 0.0f;
    }
}

void ImGui_Taffy::draw_text_segments(const TextSegment* segments, size_t segments_count, bool keepIndent)
{
    /*
        Function to get 'Text Wrap Width', that can be set via:
    
        ImGui::PushTextWrapPos( width );
        // ...
        ImGui::PopTextWrapPos();
    */
    static const auto getTextWrapWidth = []
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        return window->DC.TextWrapPos;
    };

    float wrapWidth =
        ImGui::GetWindowContentRegionWidth();
        // ImGui::GetContentRegionAvail().x;

    const float textWrapWidth = getTextWrapWidth();
    if(textWrapWidth > 0.0f) // Text wrapping is set
    {
        if(textWrapWidth < wrapWidth)
        {
            wrapWidth = textWrapWidth;
        }
    }

    draw_text_segments(segments, segments_count, wrapWidth, keepIndent);
}
