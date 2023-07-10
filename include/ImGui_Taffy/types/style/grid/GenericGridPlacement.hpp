#pragma once

#include <taffy/style/grid/GenericGridPlacement.hpp>

#include <array>

#include <imgui.h>

#include <ImGui_Taffy/utils/TypeDescription.hpp>

#include <ImGui_Taffy/show_descriptions.hpp>
#include <ImGui_Taffy/utils/HelpMarker.hpp>
#include <ImGui_Taffy/utils/description.hpp>

namespace ImGui_Taffy {

template <typename LineType>
inline bool edit_GenericGridPlacement_T(
    taffy::GenericGridPlacement<LineType>& value,
    taffy::GenericGridPlacement<LineType> (*make_default_func) (),
    LineType (*make_default_line_type_func) (),
    bool (*edit_line_type_func) (LineType& line_type),

    const TypeDescription& type_description = TypeDescription::Default()
)
{
    // -------------------------------------------------------------------------

    using Type = typename taffy::GenericGridPlacement<LineType>::Type;

    static constexpr Type GENERIC_GRID_PLACEMENT_TYPES[]
    {
        Type::Auto,
        Type::Line,
        Type::Span
    };

    static const auto GenericGridPlacement_to_string = [](const Type v) -> const char*
    {
        switch(v) {
        case Type::Auto : return "Auto";
        case Type::Line : return "AutoLine";
        case Type::Span : return "Span";

        default: return "Unknown";
        }
    };

    const auto GenericGridPlacement_from_type = [make_default_func, make_default_line_type_func](const Type v) -> taffy::GenericGridPlacement<LineType>
    {
        switch(v) {
        case Type::Auto : return taffy::GenericGridPlacement<LineType>::Auto();
        case Type::Line : return taffy::GenericGridPlacement<LineType>::Line(make_default_line_type_func());
        case Type::Span : return taffy::GenericGridPlacement<LineType>::Span(0);
        default: return make_default_func();
        }
    };

    static const auto GenericGridPlacement_show_description = [](const Type v)
    {
        switch(v) {
        case Type::Auto:
        {
            ImGui::TextUnformatted("Place item according to the auto-placement algorithm, and the parent's grid_auto_flow property");
        } break;
        case Type::Line:
        {
            ImGui::TextUnformatted("Place item at specified line (column or row) index");
        } break;
        case Type::Span:
        {
            ImGui::TextUnformatted("Item should span specified number of tracks (columns or rows)");
        } break;

        default:
        {
            ImGui::TextUnformatted("Unknown");
        } break;
        }
    };

    static const ImGui_Taffy::TypeDescription DEFAULT_TYPE_DESCRIPTION {
        "GenericGridPlacement<LineType>",
        [] {
            ImGui::TextUnformatted(
                "A grid line placement specification which is generic over the coordinate system that it uses to define "
                "grid line positions."
            );
        },
        false
    };

    // -------------------------------------------------------------------------

    const bool show_descriptions = is_show_descriptions();

    bool modified = false;

    ImGui::PushID(&value);
    {
        constexpr ImGuiComboFlags COMBO_FLAGS = ImGuiComboFlags_NoPreview;
        if (ImGui::BeginCombo("##combo", nullptr, COMBO_FLAGS))
        {
            for (const Type generic_grid_placement_type_to_choose : GENERIC_GRID_PLACEMENT_TYPES)
            {
                const bool is_selected = (generic_grid_placement_type_to_choose == value.type());

                const char* selectable_label = GenericGridPlacement_to_string(generic_grid_placement_type_to_choose);
                if (ImGui::Selectable(selectable_label, is_selected))
                {
                    value = GenericGridPlacement_from_type(generic_grid_placement_type_to_choose);

                    modified = true;
                }

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected) {
                    ImGui::SetItemDefaultFocus();
                }

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [generic_grid_placement_type_to_choose] {
                        GenericGridPlacement_show_description(generic_grid_placement_type_to_choose);
                    });
                }
            }

            ImGui::EndCombo();
        }

        ImGui::SameLine();

        switch(value.type())
        {
        case Type::Auto:
        {
            ImGui::TextUnformatted("Auto");
        } break;
        case Type::Line:
        {
            ImGui::TextUnformatted("Line");
            ImGui::SameLine();

            LineType v = value.line_type();
            if( edit_line_type_func(v) )
            {
                value = taffy::GenericGridPlacement<LineType>::Line(v);
                modified = true;
            }
        } break;
        case Type::Span:
        {
            ImGui::TextUnformatted("Span");
            ImGui::SameLine();
            uint16_t v = value.span();
            if( ImGui::DragScalar("##value", ImGuiDataType_U16, &v) ) {
                value = taffy::GenericGridPlacement<LineType>::Span(v);
                modified = true;
            }
        } break;
        default: {
            ImGui::TextUnformatted("Unknown");
        } break;
        }

        if(show_descriptions)
        {
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
