#include <ImGui_Taffy/types/style/alignment/AlignContent.hpp>

#include <imgui.h>

#include <ImGui_Taffy/show_descriptions.hpp>
#include <ImGui_Taffy/utils/HelpMarker.hpp>
#include <ImGui_Taffy/utils/description.hpp>

static constexpr taffy::AlignContent ALIGN_CONTENT[]
{
    taffy::AlignContent::Start,
    taffy::AlignContent::End,
    taffy::AlignContent::FlexStart,
    taffy::AlignContent::FlexEnd,
    taffy::AlignContent::Center,
    taffy::AlignContent::Stretch,
    taffy::AlignContent::SpaceBetween,
    taffy::AlignContent::SpaceEvenly,
    taffy::AlignContent::SpaceAround
};

const char* AlignContent_to_string(const taffy::AlignContent v)
{
    switch(v) {
    case taffy::AlignContent::Start        : return "Start";
    case taffy::AlignContent::End          : return "End";
    case taffy::AlignContent::FlexStart    : return "FlexStart";
    case taffy::AlignContent::FlexEnd      : return "FlexEnd";
    case taffy::AlignContent::Center       : return "Center";
    case taffy::AlignContent::Stretch      : return "Stretch";
    case taffy::AlignContent::SpaceBetween : return "SpaceBetween";
    case taffy::AlignContent::SpaceEvenly  : return "SpaceEvenly";
    case taffy::AlignContent::SpaceAround  : return "SpaceAround";

    default: return "Unknown";
    }
}

void AlignContent_show_descriptions(const taffy::AlignContent v)
{
    switch(v) {
    case taffy::AlignContent::Start:
    {
        ImGui::TextUnformatted("Items are packed toward the start of the axis");
    } break;
    case taffy::AlignContent::End:
    {
        ImGui::TextUnformatted("Items are packed toward the end of the axis");
    } break;
    case taffy::AlignContent::FlexStart:
    {
        ImGui::TextUnformatted(
            "Items are packed towards the flex-relative start of the axis.\n"
            "\n"
            "For flex containers with flex_direction RowReverse or ColumnReverse this is equivalent "
            "to End. In all other cases it is equivalent to Start."
        );
    } break;
    case taffy::AlignContent::FlexEnd:
    {
        ImGui::TextUnformatted(
            "Items are packed towards the flex-relative end of the axis.\n"
            "\n"
            "For flex containers with flex_direction RowReverse or ColumnReverse this is equivalent "
            "to Start. In all other cases it is equivalent to End."
        );
    } break;
    case taffy::AlignContent::Center:
    {
        ImGui::TextUnformatted("Items are centered around the middle of the axis");
    } break;
    case taffy::AlignContent::Stretch:
    {
        ImGui::TextUnformatted("Items are stretched to fill the container");
    } break;
    case taffy::AlignContent::SpaceBetween:
    {
        ImGui::TextUnformatted(
            "The first and last items are aligned flush with the edges of the container (no gap)\n"
            "The gap between items is distributed evenly."
        );
    } break;
    case taffy::AlignContent::SpaceEvenly:
    {
        ImGui::TextUnformatted(
            "The gap between the first and last items is exactly THE SAME as the gap between items.\n"
            "The gaps are distributed evenly"
        );
    } break;
    case taffy::AlignContent::SpaceAround:
    {
        ImGui::TextUnformatted(
            "The gap between the first and last items is exactly HALF the gap between items.\n"
            "The gaps are distributed evenly in proportion to these ratios."
        );
    } break;

    default:
    {
        ImGui::TextUnformatted("Unknown");
    } break;
    }
}

static const ImGui_Taffy::TypeDescription DEFAULT_TYPE_DESCRIPTION {
    "AlignContent",
    [] {
        ImGui::TextUnformatted(
            "Sets the distribution of space between and around content items\n"
            "For Flexbox it controls alignment in the cross axis\n"
            "For Grid it controls alignment in the block axis\n"
            "\n"
        );
        ImGui_Taffy::description::Link("MDN", "https://developer.mozilla.org/en-US/docs/Web/CSS/align-content");
    }, 
    true
};

bool ImGui_Taffy::edit_AlignContent(
    taffy::AlignContent& value,

    const TypeDescription& type_description
)
{
    const bool show_descriptions = is_show_descriptions();

    bool modified = false;

    ImGui::PushID(&value);
    {
        const char* combo_label = AlignContent_to_string(value);
        if (ImGui::BeginCombo("##combo", combo_label))
        {
            for (const taffy::AlignContent align_content_to_choose : ALIGN_CONTENT)
            {
                const bool is_selected = (align_content_to_choose == value);

                const char* selectable_label = AlignContent_to_string(align_content_to_choose);
                if (ImGui::Selectable(selectable_label, is_selected))
                {
                    value = align_content_to_choose;

                    modified = true;
                }

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected) {
                    ImGui::SetItemDefaultFocus();
                }

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [align_content_to_choose] {
                        AlignContent_show_descriptions(align_content_to_choose);
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
