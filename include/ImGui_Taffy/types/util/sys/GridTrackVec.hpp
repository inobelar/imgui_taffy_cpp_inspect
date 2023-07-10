#pragma once

#include <taffy/util/sys/GridTrackVec.hpp>

#include <imgui.h>

namespace ImGui_Taffy {

template <typename T>
inline bool edit_GridTrackVec_T(
    taffy::GridTrackVec<T>& vec,
    T (*make_default_value_func)(),
    bool (*edit_item_func)(T&)
)
{
    bool modified = false;

    ImGui::PushID(&vec);
    {
        constexpr ImGuiTableFlags TABLE_FLAGS =
            ImGuiTableFlags_Resizable      |
            ImGuiTableFlags_BordersInnerV  |
          //ImGuiTableFlags_SizingFixedFit |
            ImGuiTableFlags_NoSavedSettings;
        constexpr char TABLE_ID[] = "taffy_grid_track_vec_table";

        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            // Table columns specification, needed to set 'fixed' & 'stretch' flags
            ImGui::TableSetupColumn("Index", ImGuiTableColumnFlags_WidthFixed, 20.0f);
            ImGui::TableSetupColumn("Value", ImGuiTableColumnFlags_WidthStretch);
            //ImGui::TableHeadersRow(); // <-- commented to not show table header

            // -----------------------------------------------------------------

            for(size_t i = 0; i < vec.size();)
            {
                T& item = vec[i];

                bool need_remove = false;

                ImGui::PushID(&item);
                {
                    ImGui::TableNextColumn();
                    ImGui::Text("%zu", i);
                    if( ImGui::SmallButton("x") ) {
                        need_remove = true;
                    }

                    ImGui::TableNextColumn();
                    if( edit_item_func(item) ) {
                        modified = true;
                    }
                }
                ImGui::PopID();

                if(need_remove)
                {
                    vec.erase(vec.begin() + i);
                    modified = true;
                }
                else
                {
                    ++i;
                }
            }

            ImGui::EndTable();
        }

        if( ImGui::Button("Add") )
        {
            vec.push_back( make_default_value_func() );
            modified = true;
        }
    }
    ImGui::PopID();

    return modified;
}

} // namespace ImGui_Taffy
