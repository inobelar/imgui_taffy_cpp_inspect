#pragma once

#include <taffy/geometry/MinMax.hpp>

#include <imgui.h>

#include <ImGui_Taffy/utils/TypeDescription.hpp>

#include <ImGui_Taffy/show_descriptions.hpp>
#include <ImGui_Taffy/utils/HelpMarker.hpp>
#include <ImGui_Taffy/utils/description.hpp>

namespace ImGui_Taffy {

template <typename Min, typename Max>
inline bool edit_MinMax_T(
    taffy::MinMax<Min, Max>& value,
    bool (*edit_min_func) (Min& field),
    bool (*edit_max_func) (Max& field),

    const TypeDescription& type_description = TypeDescription::Default()
)
{
    const bool show_descriptions = is_show_descriptions();

    bool modified = false;

    ImGui::PushID(&value);
    {
        constexpr ImGuiTableFlags TABLE_FLAGS =
            ImGuiTableFlags_Resizable      |
            ImGuiTableFlags_BordersInnerV  |
          //ImGuiTableFlags_SizingFixedFit |
            ImGuiTableFlags_NoSavedSettings;
        constexpr char TABLE_ID[] = "taffy_min_max_table";

        const ImVec2 table_size =
            show_descriptions ?
                ImVec2{ ImGui::GetContentRegionAvail().x-30.0f, 0.0f } // Extra offset for `HelpMarker`
            :
                ImVec2{ 0.0f, 0.0f };

        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS, table_size) )
        {
            // Table columns specification, needed to set 'fixed' & 'stretch' flags
            ImGui::TableSetupColumn("Name",  ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn("Value", ImGuiTableColumnFlags_WidthStretch);
            //ImGui::TableHeadersRow(); // <-- commented to not show table header

            // -----------------------------------------------------------------

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("min");

            if(show_descriptions)
            {
                ImGui::SameLine();
                HelpMarker(false, [] {
                    ImGui::TextUnformatted("The value representing the minimum");
                });
            }

            ImGui::TableNextColumn();
            if( edit_min_func(value.min) ) {
                modified = true;
            }

            // -----------------------------------------------------------------

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("max");

            if(show_descriptions)
            {
                ImGui::SameLine();
                HelpMarker(false, [] {
                    ImGui::TextUnformatted("The value representing the maximum");
                });
            }

            ImGui::TableNextColumn();
            if( edit_max_func(value.max) ) {
                modified = true;
            }

            // -----------------------------------------------------------------

            ImGui::EndTable();
        }

        if(show_descriptions)
        {
            static const TypeDescription DEFAULT_TYPE_DESCRIPTION {
                "MinMax<Min,Max>",
                [] {
                    ImGui::TextUnformatted("Generic struct which holds a \"min\" value and a \"max\" value");
                },
                false
            };
            
            const auto description = description_or_default(type_description, DEFAULT_TYPE_DESCRIPTION);

            ImGui::SameLine();
            HelpMarker(description.type_description_interactive, [description]
            {
                description::TypeName(description.type_name);
                ImGui::NewLine();
                description.type_description_fn();
            });
        }
    }
    ImGui::PopID();

    return modified;
}

} // namespace ImGui_Taffy
