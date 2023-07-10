#pragma once

#include <taffy/geometry/Point.hpp>

#include <imgui.h>

#include <ImGui_Taffy/utils/TypeDescription.hpp>

#include <ImGui_Taffy/show_descriptions.hpp>
#include <ImGui_Taffy/utils/HelpMarker.hpp>
#include <ImGui_Taffy/utils/description.hpp>
#include <ImGui_Taffy/utils/draw_text_segments.hpp>

namespace ImGui_Taffy {

template <typename T>
inline bool edit_Point_T(
    taffy::Point<T>& value,
    bool (*edit_field_func) (T& field),

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
        constexpr char TABLE_ID[] = "taffy_point_table";

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
            ImGui::TextUnformatted("x");

            if(show_descriptions)
            {
                ImGui::SameLine();
                HelpMarker(false, [] {
                    ImGui::TextUnformatted("The x-coordinate");
                });
            }

            ImGui::TableNextColumn();
            if( edit_field_func(value.x) ) {
                modified = true;
            }

            // -----------------------------------------------------------------

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("y");

            if(show_descriptions)
            {
                ImGui::SameLine();
                HelpMarker(false, [] {
                    ImGui::TextUnformatted("The y-coordinate");
                });
            }

            ImGui::TableNextColumn();
            if( edit_field_func(value.y) ) {
                modified = true;
            }

            // -----------------------------------------------------------------

            ImGui::EndTable();
        }

        if(show_descriptions)
        {
            static const TypeDescription DEFAULT_TYPE_DESCRIPTION {
                "Point<T>",
                [] {
                    ImGui::TextUnformatted("A 2-dimensional coordinate.");
                    ImGui::NewLine();

                    static const TextSegment TEXT_SEGMENTS[]
                    {
                        {"When used in association with a "},
                        {"Rect", description::CODE_INLINE_COLOR},
                        {", represents the top-left corner."}
                    };
                    draw_text_segments(TEXT_SEGMENTS, false);
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
