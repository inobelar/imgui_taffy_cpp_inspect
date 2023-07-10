#include <ImGui_Taffy/types/style/alignment/AlignItems.hpp>

#include <imgui.h>

#include <ImGui_Taffy/show_descriptions.hpp>
#include <ImGui_Taffy/utils/HelpMarker.hpp>
#include <ImGui_Taffy/utils/description.hpp>

static constexpr taffy::AlignItems ALIGN_ITEMS[]
{
    taffy::AlignItems::Start,
    taffy::AlignItems::End,
    taffy::AlignItems::FlexStart,
    taffy::AlignItems::FlexEnd,
    taffy::AlignItems::Center,
    taffy::AlignItems::Baseline,
    taffy::AlignItems::Stretch
};

const char* AlignItems_to_string(const taffy::AlignItems v)
{
    switch(v) {
    case taffy::AlignItems::Start     : return "Start";
    case taffy::AlignItems::End       : return "End";
    case taffy::AlignItems::FlexStart : return "FlexStart";
    case taffy::AlignItems::FlexEnd   : return "FlexEnd";
    case taffy::AlignItems::Center    : return "Center";
    case taffy::AlignItems::Baseline  : return "Baseline";
    case taffy::AlignItems::Stretch   : return "Stretch";

    default: return "Unknown";
    }
}

void AlignItems_show_description(const taffy::AlignItems v)
{
    switch(v) {
    case taffy::AlignItems::Start:
    {
        ImGui::TextUnformatted("Items are packed toward the start of the axis");
    } break;
    case taffy::AlignItems::End:
    {
        ImGui::TextUnformatted("Items are packed toward the end of the axis");
    } break;
    case taffy::AlignItems::FlexStart:
    {
        ImGui::TextUnformatted(
            "Items are packed towards the flex-relative start of the axis.\n"
            "\n"
            "For flex containers with flex_direction RowReverse or ColumnReverse this is equivalent "
            "to End. In all other cases it is equivalent to Start."
        );
    } break;
    case taffy::AlignItems::FlexEnd:
    {
        ImGui::TextUnformatted(
            "Items are packed towards the flex-relative end of the axis.\n"
            "\n"
            "For flex containers with flex_direction RowReverse or ColumnReverse this is equivalent "
            "to Start. In all other cases it is equivalent to End."
        );
    } break;
    case taffy::AlignItems::Center:
    {
        ImGui::TextUnformatted("Items are packed along the center of the cross axis");
    } break;
    case taffy::AlignItems::Baseline:
    {
        ImGui::TextUnformatted("Items are aligned such as their baselines align");
    } break;
    case taffy::AlignItems::Stretch:
    {
        ImGui::TextUnformatted("Stretch to fill the container");
    } break;

    default: {
        ImGui::TextUnformatted("Unknown");
    } break;
    }
}

static const ImGui_Taffy::TypeDescription DEFAULT_TYPE_DESCRIPTION {
    "AlignItems",
    [] {
        ImGui::TextUnformatted(
            "Used to control how child nodes are aligned.\n"
            "For Flexbox it controls alignment in the cross axis\n"
            "For Grid it controls alignment in the block axis\n"
            "\n"
        );
        ImGui_Taffy::description::Link("MDN", "https://developer.mozilla.org/en-US/docs/Web/CSS/align-items");
    }, 
    true
};

bool ImGui_Taffy::edit_AlignItems(
    taffy::AlignItems& value,

    const TypeDescription& type_description
)
{
    const bool show_descriptions = is_show_descriptions();

    bool modified = false;

    ImGui::PushID(&value);
    {
        const char* combo_label = AlignItems_to_string(value);
        if (ImGui::BeginCombo("##combo", combo_label))
        {
            for (const taffy::AlignItems align_items_to_choose : ALIGN_ITEMS)
            {
                const bool is_selected = (align_items_to_choose == value);

                const char* selectable_label = AlignItems_to_string(align_items_to_choose);
                if (ImGui::Selectable(selectable_label, is_selected))
                {
                    value = align_items_to_choose;

                    modified = true;
                }

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected) {
                    ImGui::SetItemDefaultFocus();
                }

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [align_items_to_choose] {
                        AlignItems_show_description(align_items_to_choose);
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
