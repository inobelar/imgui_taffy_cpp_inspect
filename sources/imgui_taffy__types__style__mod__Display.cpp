#include <ImGui_Taffy/types/style/mod/Display.hpp>

#include <imgui.h>

#include <ImGui_Taffy/show_descriptions.hpp>
#include <ImGui_Taffy/utils/HelpMarker.hpp>
#include <ImGui_Taffy/utils/description.hpp>

static constexpr taffy::Display::Type DISPLAY_TYPES[]
{
    #if defined(TAFFY_FEATURE_BLOCK_LAYOUT)
    taffy::Display::Type::Block,
    #endif // TAFFY_FEATURE_BLOCK_LAYOUT

    #if defined(TAFFY_FEATURE_FLEXBOX)
    taffy::Display::Type::Flex,
    #endif // TAFFY_FEATURE_FLEXBOX

    #if defined(TAFFY_FEATURE_GRID)
    taffy::Display::Type::Grid,
    #endif // TAFFY_FEATURE_GRID

    taffy::Display::Type::None
};

const char* Display_to_string(const taffy::Display::Type v)
{
    switch(v) {
    #if defined(TAFFY_FEATURE_BLOCK_LAYOUT)
    case taffy::Display::Type::Block: return "Block";
    #endif // TAFFY_FEATURE_BLOCK_LAYOUT

    #if defined(TAFFY_FEATURE_FLEXBOX)
    case taffy::Display::Type::Flex: return "Flex";
    #endif // TAFFY_FEATURE_FLEXBOX

    #if defined(TAFFY_FEATURE_GRID)
    case taffy::Display::Type::Grid: return "Grid";
    #endif // TAFFY_FEATURE_GRID

    case taffy::Display::Type::None: return "None";

    default: return "Unknown";
    }
}

taffy::Display Display_from_type(const taffy::Display::Type v)
{
    switch(v) {
    #if defined(TAFFY_FEATURE_BLOCK_LAYOUT)
    case taffy::Display::Type::Block: return taffy::Display::Block();
    #endif // TAFFY_FEATURE_BLOCK_LAYOUT

    #if defined(TAFFY_FEATURE_FLEXBOX)
    case taffy::Display::Type::Flex: return taffy::Display::Flex();
    #endif // TAFFY_FEATURE_FLEXBOX

    #if defined(TAFFY_FEATURE_GRID)
    case taffy::Display::Type::Grid: return taffy::Display::Grid();
    #endif // TAFFY_FEATURE_GRID

    case taffy::Display::Type::None: return taffy::Display::None();

    default: return taffy::Display::Default();
    }
}

void Display_show_description(const taffy::Display::Type v)
{
    switch(v) {
    #if defined(TAFFY_FEATURE_BLOCK_LAYOUT)
    case taffy::Display::Type::Block:
    {
        ImGui::TextUnformatted("The children will follow the block layout algorithm");
    } break;
    #endif // TAFFY_FEATURE_BLOCK_LAYOUT

    #if defined(TAFFY_FEATURE_FLEXBOX)
    case taffy::Display::Type::Flex:
    {
        ImGui::TextUnformatted("The children will follow the flexbox layout algorithm");
    } break;
    #endif // TAFFY_FEATURE_FLEXBOX

    #if defined(TAFFY_FEATURE_GRID)
    case taffy::Display::Type::Grid:
    {
        ImGui::TextUnformatted("The children will follow the CSS Grid layout algorithm");
    } break;
    #endif // TAFFY_FEATURE_GRID

    case taffy::Display::Type::None:
    {
        ImGui::TextUnformatted("The children will not be laid out, and will follow absolute positioning");
    } break;

    default:
    {
        ImGui::TextUnformatted("Unknown");
    } break;
    }
}

static const ImGui_Taffy::TypeDescription DEFAULT_TYPE_DESCRIPTION {
    "Display",
    [] {
        ImGui::TextUnformatted("Sets the layout used for the children of this node");
    },
    false
};

bool ImGui_Taffy::edit_Display(
    taffy::Display& value,

    const TypeDescription& type_description
)
{
    const bool show_descriptions = is_show_descriptions();

    bool modified = false;

    ImGui::PushID(&value);
    {
        const char* combo_label = Display_to_string(value.type());
        if (ImGui::BeginCombo("##combo", combo_label))
        {
            for (const taffy::Display::Type display_type_to_choose : DISPLAY_TYPES)
            {
                const bool is_selected = (display_type_to_choose == value.type());

                const char* selectable_label = Display_to_string(display_type_to_choose);
                if (ImGui::Selectable(selectable_label, is_selected))
                {
                    value = Display_from_type(display_type_to_choose);

                    modified = true;
                }

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected) {
                    ImGui::SetItemDefaultFocus();
                }

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [display_type_to_choose] {
                        Display_show_description(display_type_to_choose);
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
