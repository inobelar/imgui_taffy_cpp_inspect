#pragma once

#include <taffy/support/rust_utils/Option.hpp>

#include <imgui.h>

namespace ImGui_Taffy {

template <typename T>
inline bool edit_Option_T(
    taffy::Option<T>& value,

    taffy::Option<T> (*get_some_func)(),
    bool (*edit_some_func)(T& value)
)
{
    bool modified = false;

    ImGui::PushID(&value);
    {
        constexpr ImGuiComboFlags COMBO_FLAGS = ImGuiComboFlags_NoPreview;
        if (ImGui::BeginCombo("##combo", nullptr, COMBO_FLAGS))
        {
            // Case: Some
            {
                const bool is_selected = value.is_some();

                if(ImGui::Selectable("Some", is_selected))
                {
                    value = get_some_func();
                    modified = true;
                }

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected) {
                    ImGui::SetItemDefaultFocus();
                }
            }

            // Case: None
            {
                const bool is_selected = !value.is_some();

                if(ImGui::Selectable("None", is_selected))
                {
                    value = taffy::Option<T>{}; // None
                    modified = true;
                }

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected) {
                    ImGui::SetItemDefaultFocus();
                }
            }

            ImGui::EndCombo();
        }

        ImGui::SameLine();

        if(value.is_some())
        {
            ImGui::TextUnformatted("Some");
            ImGui::SameLine();

            T v = value.value();
            if( edit_some_func(v) ) {
                value = taffy::Option<T>{v};
                modified = true;
            }
        }
        else
        {
            ImGui::TextUnformatted("None");
        }
    }
    ImGui::PopID();

    return modified;
}

} // namespace ImGui_Taffy
