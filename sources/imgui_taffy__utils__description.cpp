#include <ImGui_Taffy/utils/description.hpp>

#include <imgui.h>

#include <ImGui_Taffy/open_link_func.hpp>

static constexpr ImVec4 TYPE_NAME_COLOR_VEC4   = {0.9f, 0.7f, 0.0f, 1.0f};  // Orange
static constexpr ImVec4 CODE_INLINE_COLOR_VEC4 = {0.5f, 0.5f, 0.5f, 1.0f};  // Gray
static constexpr ImVec4 LINK_COLOR_VEC4        = {0.25f, 0.5f, 1.0f, 1.0f}; // Blue
static constexpr ImVec4 WARNING_COLOR_VEC4     = {1.0f, 1.0f, 0.0f, 1.0f}; // Yellow

// Export colors, packet from 'ImVec4' into 'ImU32'
const uint32_t ImGui_Taffy::description::TYPE_NAME_COLOR   = ImColor(TYPE_NAME_COLOR_VEC4);
const uint32_t ImGui_Taffy::description::CODE_INLINE_COLOR = ImColor(CODE_INLINE_COLOR_VEC4);
const uint32_t ImGui_Taffy::description::LINK_COLOR        = ImColor(LINK_COLOR_VEC4);
const uint32_t ImGui_Taffy::description::WARNING_COLOR     = ImColor(WARNING_COLOR_VEC4);

void ImGui_Taffy::description::TypeName(const char* text)
{
    ImGui::TextColored(TYPE_NAME_COLOR_VEC4, "%s", text);
}

void ImGui_Taffy::description::CodeInline(const char* text)
{
    ImGui::TextColored(CODE_INLINE_COLOR_VEC4, "%s", text);
}

void ImGui_Taffy::description::Link(const char* text, const char* url)
{
    ImGui::TextColored(LINK_COLOR_VEC4, "%s", text);
    
    if( ImGui::IsItemHovered() )
    {
        // On hover: cursor::hand
        ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);

        // On hover: show tooltip with 'url'
        if( ImGui::BeginTooltip() )
        {
            ImGui::TextUnformatted(url);

            ImGui::EndTooltip();
        }
    }

    if (ImGui::IsItemClicked(ImGuiMouseButton_Left) )
    {
        const auto open_link = get_open_link_func();

        // On click: open url
        if( open_link != nullptr)
        {
            open_link(url);
        }
    }
}

void ImGui_Taffy::description::Link(const char* url)
{
    Link(url, url);
}
