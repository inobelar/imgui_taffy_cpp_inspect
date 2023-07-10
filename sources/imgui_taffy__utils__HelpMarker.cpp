#include <ImGui_Taffy/utils/HelpMarker.hpp>

#include <imgui.h>

/*
    Helper to display a little '(?)' mark which shows a tooltip when hovered.

    Based on code from `imgui_demo.cpp`
*/
void ImGui_Taffy::HelpMarker(bool is_interactive, const std::function<void()>& tooltip_content_func)
{
    ImGui::TextDisabled("(?)");

    if(is_interactive == false)
    {
        // Display tooltip
        if( ImGui::IsItemHovered() )
        {
            if( ImGui::BeginTooltip() )
            {
                ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
                {
                    tooltip_content_func();
                }
                ImGui::PopTextWrapPos();

                ImGui::EndTooltip();
            }
        }
    }
    else // is_interactive == true
    {
        // Display popup
        static bool marker_hovered = false;
        marker_hovered = ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup);
        if(marker_hovered)
        {
            ImGui::OpenPopup("taffy_help_marker_popup");
        }

        if( ImGui::BeginPopup("taffy_help_marker_popup") )
        {
            ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
            {
                tooltip_content_func();
            }
            ImGui::PopTextWrapPos();

            // Self-closing, when mouse out of popup or marker
            if( !ImGui::IsWindowHovered() && !marker_hovered )
            {
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }
    }
}
