#include <ImGui_Taffy/types/style/grid/MinTrackSizingFunction.hpp>

#include <imgui.h>

#include <ImGui_Taffy/types/style/dimensions/LengthPercentage.hpp>

#include <ImGui_Taffy/show_descriptions.hpp>
#include <ImGui_Taffy/utils/HelpMarker.hpp>
#include <ImGui_Taffy/utils/description.hpp>
#include <ImGui_Taffy/utils/draw_text_segments.hpp>

static constexpr taffy::MinTrackSizingFunction::Type MIN_TRACK_SIZING_FUNCTION_TYPES[]
{
    taffy::MinTrackSizingFunction::Type::Fixed,
    taffy::MinTrackSizingFunction::Type::MinContent,
    taffy::MinTrackSizingFunction::Type::MaxContent,
    taffy::MinTrackSizingFunction::Type::Auto
};

const char* MinTrackSizingFunction_to_string(const taffy::MinTrackSizingFunction::Type v)
{
    switch(v) {
    case taffy::MinTrackSizingFunction::Type::Fixed      : return "Fixed";
    case taffy::MinTrackSizingFunction::Type::MinContent : return "MinContent";
    case taffy::MinTrackSizingFunction::Type::MaxContent : return "MaxContent";
    case taffy::MinTrackSizingFunction::Type::Auto       : return "Auto";

    default: return "Unknown";
    }
}

taffy::MinTrackSizingFunction MinTrackSizingFunction_from_type(const taffy::MinTrackSizingFunction::Type v)
{
    switch(v) {
    case taffy::MinTrackSizingFunction::Type::Fixed      : return taffy::MinTrackSizingFunction::Fixed(taffy::LengthPercentage::ZERO());
    case taffy::MinTrackSizingFunction::Type::MinContent : return taffy::MinTrackSizingFunction::MinContent();
    case taffy::MinTrackSizingFunction::Type::MaxContent : return taffy::MinTrackSizingFunction::MaxContent();
    case taffy::MinTrackSizingFunction::Type::Auto       : return taffy::MinTrackSizingFunction::Auto();
    default: return taffy::MinTrackSizingFunction::Auto();
    }
}

void MinTrackSizingFunction_show_description(const taffy::MinTrackSizingFunction::Type v)
{
    switch(v) {
    case taffy::MinTrackSizingFunction::Type::Fixed:
    {
        ImGui::TextUnformatted("Track minimum size should be a fixed length or percentage value");
    } break;
    case taffy::MinTrackSizingFunction::Type::MinContent:
    {
        ImGui::TextUnformatted("Track minimum size should be content sized under a min-content constraint");
    } break;
    case taffy::MinTrackSizingFunction::Type::MaxContent:
    {
        ImGui::TextUnformatted("Track minimum size should be content sized under a max-content constraint");
    } break;
    case taffy::MinTrackSizingFunction::Type::Auto:
    {
        ImGui::TextUnformatted("Track minimum size should be automatically sized");
    } break;

    default:
    {
        ImGui::TextUnformatted("Unknown");
    } break;
    }
}

static const ImGui_Taffy::TypeDescription DEFAULT_TYPE_DESCRIPTION {
    "MinTrackSizingFunction",
    [] {
        ImGui::TextUnformatted(
            "Minimum track sizing function\n"
            "\n"
            "Specifies the minimum size of a grid track. A grid track will automatically size between it's minimum and maximum size based "
            "on the size of it's contents, the amount of available space, and the sizing constraint the grid is being size under."
        );
        
        {
            static const ImGui_Taffy::TextSegment TEXT_SEGMENTS[]
            {
                {"See "},
                {
                    "https://developer.mozilla.org/en-US/docs/Web/CSS/grid-template-columns", 
                    ImGui_Taffy::description::LINK_COLOR, false,
                    "https://developer.mozilla.org/en-US/docs/Web/CSS/grid-template-columns"
                }
            };
            ImGui_Taffy::draw_text_segments(TEXT_SEGMENTS, false);
        }
    }, 
    true
};

bool ImGui_Taffy::edit_MinTrackSizingFunction(
    taffy::MinTrackSizingFunction& value,
    
    const TypeDescription& type_description
)
{
    const bool show_descriptions = is_show_descriptions();

    bool modified = false;

    ImGui::PushID(&value);
    {
        constexpr ImGuiComboFlags COMBO_FLAGS = ImGuiComboFlags_NoPreview;
        if (ImGui::BeginCombo("##combo", nullptr, COMBO_FLAGS))
        {
            for (const taffy::MinTrackSizingFunction::Type mts_type_to_choose : MIN_TRACK_SIZING_FUNCTION_TYPES)
            {
                const bool is_selected = (mts_type_to_choose == value.type());

                const char* selectable_label = MinTrackSizingFunction_to_string(mts_type_to_choose);
                if (ImGui::Selectable(selectable_label, is_selected))
                {
                    value = MinTrackSizingFunction_from_type(mts_type_to_choose);

                    modified = true;
                }

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected) {
                    ImGui::SetItemDefaultFocus();
                }
                
                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [mts_type_to_choose] {
                        MinTrackSizingFunction_show_description(mts_type_to_choose);
                    });
                }
            }

            ImGui::EndCombo();
        }

        ImGui::SameLine();

        switch(value.type())
        {
        case taffy::MinTrackSizingFunction::Type::Fixed: {
            ImGui::TextUnformatted("Fixed");
            ImGui::SameLine();
            taffy::LengthPercentage v = value.value();
            if( edit_LengthPercentage(v) ) {
                value = taffy::MinTrackSizingFunction::Fixed(v);
                modified = true;
            }
        } break;
        case taffy::MinTrackSizingFunction::Type::MinContent: {
            ImGui::TextUnformatted("MinContent");
        } break;
        case taffy::MinTrackSizingFunction::Type::MaxContent: {
            ImGui::TextUnformatted("MaxContent");
        } break;
        case taffy::MinTrackSizingFunction::Type::Auto: {
            ImGui::TextUnformatted("Auto");
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
