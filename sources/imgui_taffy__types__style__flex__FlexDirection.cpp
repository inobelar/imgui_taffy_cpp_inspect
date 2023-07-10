#include <ImGui_Taffy/types/style/flex/FlexDirection.hpp>

#include <imgui.h>

#include <ImGui_Taffy/show_descriptions.hpp>
#include <ImGui_Taffy/utils/HelpMarker.hpp>
#include <ImGui_Taffy/utils/description.hpp>

static constexpr taffy::FlexDirection::Type FLEX_DIRECTION_TYPES[]
{
    taffy::FlexDirection::Type::Row,
    taffy::FlexDirection::Type::Column,
    taffy::FlexDirection::Type::RowReverse,
    taffy::FlexDirection::Type::ColumnReverse
};

const char* FlexDirection_to_string(const taffy::FlexDirection::Type v)
{
    switch(v) {
    case taffy::FlexDirection::Type::Row           : return "Row";
    case taffy::FlexDirection::Type::Column        : return "Column";
    case taffy::FlexDirection::Type::RowReverse    : return "RowReverse";
    case taffy::FlexDirection::Type::ColumnReverse : return "ColumnReverse";

    default: return "Unknown";
    }
}

taffy::FlexDirection FlexDirection_from_type(const taffy::FlexDirection::Type v)
{
    switch(v) {
    case taffy::FlexDirection::Type::Row           : return taffy::FlexDirection::Row();
    case taffy::FlexDirection::Type::Column        : return taffy::FlexDirection::Column();
    case taffy::FlexDirection::Type::RowReverse    : return taffy::FlexDirection::RowReverse();
    case taffy::FlexDirection::Type::ColumnReverse : return taffy::FlexDirection::ColumnReverse();

    default: return taffy::FlexDirection::Row();
    }
}

void FlexDirection_show_description(const taffy::FlexDirection::Type v)
{
    switch(v) {
    case taffy::FlexDirection::Type::Row:
    {
        ImGui::TextUnformatted(
            "Defines +x as the main axis\n"
            "\n"
            "Items will be added from left to right in a row."
        );
    } break;
    case taffy::FlexDirection::Type::Column:
    {
        ImGui::TextUnformatted(
            "Defines +y as the main axis\n"
            "\n"
            "Items will be added from top to bottom in a column."
        );
    } break;
    case taffy::FlexDirection::Type::RowReverse:
    {
        ImGui::TextUnformatted(
            "Defines -x as the main axis\n"
            "\n"
            "Items will be added from right to left in a row."
        );
    } break;
    case taffy::FlexDirection::Type::ColumnReverse:
    {
        ImGui::TextUnformatted(
            "Defines -y as the main axis\n"
            "\n"
            "Items will be added from bottom to top in a column."
        );
    } break;

    default:
    {
        ImGui::TextUnformatted("Unknown");
    } break;
    }
}

static const ImGui_Taffy::TypeDescription DEFAULT_TYPE_DESCRIPTION {
    "FlexDirection",
    [] {
        ImGui::TextUnformatted(
            "The direction of the flexbox layout main axis.\n"
            "\n"
            "There are always two perpendicular layout axes: main (or primary) and cross (or secondary).\n"
            "Adding items will cause them to be positioned adjacent to each other along the main axis.\n"
            "By varying this value throughout your tree, you can create complex axis-aligned layouts.\n"
            "\n"
            "Items are always aligned relative to the cross axis, and justified relative to the main axis.\n"
            "\n"
        );
        
        ImGui_Taffy::description::Link("Specification", "https://www.w3.org/TR/css-flexbox-1/#flex-direction-property");
    }, 
    true
};

bool ImGui_Taffy::edit_FlexDirection(
    taffy::FlexDirection& value,
    
    const TypeDescription& type_description
)
{
    const bool show_descriptions = is_show_descriptions();

    bool modified = false;

    ImGui::PushID(&value);
    {
        const char* combo_label = FlexDirection_to_string(value.type());
        if (ImGui::BeginCombo("##combo", combo_label))
        {
            for (const taffy::FlexDirection::Type flex_direction_type_to_choose : FLEX_DIRECTION_TYPES)
            {
                const bool is_selected = (flex_direction_type_to_choose == value.type());

                const char* selectable_label = FlexDirection_to_string(flex_direction_type_to_choose);
                if (ImGui::Selectable(selectable_label, is_selected))
                {
                    value = FlexDirection_from_type(flex_direction_type_to_choose);

                    modified = true;
                }

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected) {
                    ImGui::SetItemDefaultFocus();
                }

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [flex_direction_type_to_choose] {
                        FlexDirection_show_description(flex_direction_type_to_choose);
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
