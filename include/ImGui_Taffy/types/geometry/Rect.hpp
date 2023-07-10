#pragma once

#include <taffy/geometry/Rect.hpp>

#include <imgui.h>

#include <ImGui_Taffy/utils/TypeDescription.hpp>

#include <ImGui_Taffy/show_descriptions.hpp>
#include <ImGui_Taffy/utils/HelpMarker.hpp>
#include <ImGui_Taffy/utils/description.hpp>

namespace ImGui_Taffy {

template <typename T>
inline bool edit_Rect_T(
    taffy::Rect<T>& value,
    bool (*edit_field_func)(T& field),

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
        constexpr char TABLE_ID[] = "taffy_rect_table";

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
            ImGui::TextUnformatted("left");

            if(show_descriptions)
            {
                ImGui::SameLine();
                HelpMarker(false, [] {
                    ImGui::TextUnformatted(
                        "This can represent either the x-coordinate of the starting edge, "
                        "or the amount of padding on the starting side.\n"
                        "\n"
                        "The starting edge is the left edge when working with LTR text, "
                        "and the right edge when working with RTL text."
                    );
                });
            }

            ImGui::TableNextColumn();
            if( edit_field_func(value.left) ) {
                modified = true;
            }

            // -----------------------------------------------------------------

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("right");

            if(show_descriptions)
            {
                ImGui::SameLine();
                HelpMarker(false, [] {
                    ImGui::TextUnformatted(
                        "This can represent either the x-coordinate of the ending edge, "
                        "or the amount of padding on the ending side.\n"
                        "\n"
                        "The ending edge is the right edge when working with LTR text, "
                        "and the left edge when working with RTL text."
                    );
                });
            }

            ImGui::TableNextColumn();
            if( edit_field_func(value.right) ) {
                modified = true;
            }

            // -----------------------------------------------------------------

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("top");

            if(show_descriptions)
            {
                ImGui::SameLine();
                HelpMarker(false, [] {
                    ImGui::TextUnformatted(
                        "This can represent either the y-coordinate of the top edge, "
                        "or the amount of padding on the top side."
                    );
                });
            }

            ImGui::TableNextColumn();
            if( edit_field_func(value.top) ) {
                modified = true;
            }

            // -----------------------------------------------------------------

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("bottom");

            if(show_descriptions)
            {
                ImGui::SameLine();
                HelpMarker(false, [] {
                    ImGui::TextUnformatted(
                        "This can represent either the y-coordinate of the bottom edge, "
                        "or the amount of padding on the bottom side."
                    );
                });
            }

            ImGui::TableNextColumn();
            if( edit_field_func(value.bottom) ) {
                modified = true;
            }

            // -----------------------------------------------------------------

            ImGui::EndTable();
        }

        if(show_descriptions)
        {
            static const TypeDescription DEFAULT_TYPE_DESCRIPTION {
                "Rect<T>",
                [] {
                    ImGui::TextUnformatted("An axis-aligned UI rectangle");
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
