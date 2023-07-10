#include <ImGui_Taffy/types/geometry/AbsoluteAxis.hpp>

#include <imgui.h>

#include <ImGui_Taffy/show_descriptions.hpp>
#include <ImGui_Taffy/utils/HelpMarker.hpp>
#include <ImGui_Taffy/utils/description.hpp>

static constexpr taffy::AbsoluteAxis::Type ABSOLUTE_AXIS_TYPES[]
{
    taffy::AbsoluteAxis::Type::Horizontal,
    taffy::AbsoluteAxis::Type::Vertical
};

const char* AbsoluteAxis_to_string(const taffy::AbsoluteAxis::Type v)
{
    switch(v) {
    case taffy::AbsoluteAxis::Type::Horizontal : return "Horizontal";
    case taffy::AbsoluteAxis::Type::Vertical   : return "Vertical";

    default: return "Unknown";
    }
}

taffy::AbsoluteAxis AbsoluteAxis_from_type(const taffy::AbsoluteAxis::Type v)
{
    switch(v) {
    case taffy::AbsoluteAxis::Type::Horizontal : return taffy::AbsoluteAxis::Horizontal();
    case taffy::AbsoluteAxis::Type::Vertical   : return taffy::AbsoluteAxis::Vertical();

    default: return taffy::AbsoluteAxis::Horizontal();
    }
}

void AbsoluteAxis_show_description(const taffy::AbsoluteAxis::Type v)
{
    switch(v) {
    case taffy::AbsoluteAxis::Type::Horizontal:
    {
        ImGui::TextUnformatted("The horizontal axis");
    } break;
    case taffy::AbsoluteAxis::Type::Vertical:
    {
        ImGui::TextUnformatted("The vertical axis");
    } break;

    default:
    {
        ImGui::TextUnformatted("Unknown");
    } break;
    }
}

static const ImGui_Taffy::TypeDescription DEFAULT_TYPE_DESCRIPTION {
    "AbsoluteAxis",
    [] {
        ImGui::TextUnformatted("The simple absolute horizontal and vertical axis");
    }, 
    false
};

bool ImGui_Taffy::edit_AbsoluteAxis(
    taffy::AbsoluteAxis& value,

    const TypeDescription& type_description
)
{
    const bool show_descriptions = is_show_descriptions();

    bool modified = false;

    ImGui::PushID(&value);
    {
        const char* combo_label = AbsoluteAxis_to_string(value.type());
        if (ImGui::BeginCombo("##combo", combo_label))
        {
            for (const taffy::AbsoluteAxis::Type absolute_axis_type_to_choose : ABSOLUTE_AXIS_TYPES)
            {
                const bool is_selected = (absolute_axis_type_to_choose == value.type());

                const char* selectable_label = AbsoluteAxis_to_string(absolute_axis_type_to_choose);
                if (ImGui::Selectable(selectable_label, is_selected))
                {
                    value = AbsoluteAxis_from_type(absolute_axis_type_to_choose);

                    modified = true;
                }

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected) {
                    ImGui::SetItemDefaultFocus();
                }

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [absolute_axis_type_to_choose] {
                        AbsoluteAxis_show_description(absolute_axis_type_to_choose);
                    });
                }
            }

            ImGui::EndCombo();
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
