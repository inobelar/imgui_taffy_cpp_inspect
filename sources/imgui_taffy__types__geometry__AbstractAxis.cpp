#include <ImGui_Taffy/types/geometry/AbstractAxis.hpp>

#include <imgui.h>

#include <ImGui_Taffy/show_descriptions.hpp>
#include <ImGui_Taffy/utils/HelpMarker.hpp>
#include <ImGui_Taffy/utils/description.hpp>

static constexpr taffy::AbstractAxis::Type ABSTRACT_AXIS_TYPES[]
{
    taffy::AbstractAxis::Type::Inline,
    taffy::AbstractAxis::Type::Block
};

const char* AbstractAxis_to_string(const taffy::AbstractAxis::Type v)
{
    switch(v) {
    case taffy::AbstractAxis::Type::Inline : return "Inline";
    case taffy::AbstractAxis::Type::Block  : return "BLock";

    default: return "Unknown";
    }
}

taffy::AbstractAxis AbstractAxis_from_type(const taffy::AbstractAxis::Type v)
{
    switch(v) {
    case taffy::AbstractAxis::Type::Inline : return taffy::AbstractAxis::Inline();
    case taffy::AbstractAxis::Type::Block  : return taffy::AbstractAxis::Block();

    default: return taffy::AbstractAxis::Inline();
    }
}

void AbstractAxis_show_description(const taffy::AbstractAxis::Type v)
{
    switch(v) {
    case taffy::AbstractAxis::Type::Inline:
    {
        ImGui::TextUnformatted(
            "The axis in the inline dimension, i.e. the horizontal axis in horizontal writing modes and the vertical axis in vertical writing modes."
        );
    } break;
    case taffy::AbstractAxis::Type::Block:
    {
        ImGui::TextUnformatted(
            "The axis in the block dimension, i.e. the vertical axis in horizontal writing modes and the horizontal axis in vertical writing modes."
        );
    } break;

    default:
    {
        ImGui::TextUnformatted("Unknown");
    } break;
    }
}

static const ImGui_Taffy::TypeDescription DEFAULT_TYPE_DESCRIPTION {
    "AbstractAxis",
    [] {
        ImGui::TextUnformatted("The CSS abstract axis");
        ImGui_Taffy::description::Link("https://www.w3.org/TR/css-writing-modes-3/#abstract-axes");
    }, 
    true
};

bool ImGui_Taffy::edit_AbstractAxis(
    taffy::AbstractAxis& value,

    const TypeDescription& type_description
)
{
    const bool show_descriptions = is_show_descriptions();

    bool modified = false;

    ImGui::PushID(&value);
    {
        const char* combo_label = AbstractAxis_to_string(value.type());
        if (ImGui::BeginCombo("##combo", combo_label))
        {
            for (const taffy::AbstractAxis::Type abstract_axis_type_to_choose : ABSTRACT_AXIS_TYPES)
            {
                const bool is_selected = (abstract_axis_type_to_choose == value.type());

                const char* selectable_label = AbstractAxis_to_string(abstract_axis_type_to_choose);
                if (ImGui::Selectable(selectable_label, is_selected))
                {
                    value = AbstractAxis_from_type(abstract_axis_type_to_choose);

                    modified = true;
                }

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected) {
                    ImGui::SetItemDefaultFocus();
                }

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [abstract_axis_type_to_choose] {
                        AbstractAxis_show_description(abstract_axis_type_to_choose);
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
