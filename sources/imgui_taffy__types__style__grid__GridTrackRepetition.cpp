#include <ImGui_Taffy/types/style/grid/GridTrackRepetition.hpp>

#include <imgui.h>

#include <ImGui_Taffy/show_descriptions.hpp>
#include <ImGui_Taffy/utils/HelpMarker.hpp>
#include <ImGui_Taffy/utils/description.hpp>
#include <ImGui_Taffy/utils/draw_text_segments.hpp>

static constexpr taffy::GridTrackRepetition::Type GRID_TRACK_REPETITION_TYPES[]
{
    taffy::GridTrackRepetition::Type::AutoFill,
    taffy::GridTrackRepetition::Type::AutoFit,
    taffy::GridTrackRepetition::Type::Count
};

const char* GridTrackRepetition_to_string(const taffy::GridTrackRepetition::Type v)
{
    switch(v) {
    case taffy::GridTrackRepetition::Type::AutoFill : return "AutoFill";
    case taffy::GridTrackRepetition::Type::AutoFit  : return "AutoFit";
    case taffy::GridTrackRepetition::Type::Count    : return "Count";

    default: return "Unknown";
    }
}

taffy::GridTrackRepetition GridTrackRepetition_from_type(const taffy::GridTrackRepetition::Type v)
{
    switch(v) {
    case taffy::GridTrackRepetition::Type::AutoFill : return taffy::GridTrackRepetition::AutoFill();
    case taffy::GridTrackRepetition::Type::AutoFit  : return taffy::GridTrackRepetition::AutoFit();
    case taffy::GridTrackRepetition::Type::Count    : return taffy::GridTrackRepetition::Count(0);
    default: return taffy::GridTrackRepetition::AutoFill();
    }
}

void GridTrackRepetition_show_description(const taffy::GridTrackRepetition::Type v)
{
    switch(v) {
    case taffy::GridTrackRepetition::Type::AutoFill:
    {
        ImGui::TextUnformatted("Auto-repeating tracks should be generated to fit the container");
        
        static const ImGui_Taffy::TextSegment TEXT_SEGMENTS[]
        {
            {"See: "},
            {
                "https://developer.mozilla.org/en-US/docs/Web/CSS/repeat#auto-fill", 
                ImGui_Taffy::description::LINK_COLOR, false, 
                "https://developer.mozilla.org/en-US/docs/Web/CSS/repeat#auto-fill"
            }
        };
        ImGui_Taffy::draw_text_segments(TEXT_SEGMENTS, false);
    } break;
    case taffy::GridTrackRepetition::Type::AutoFit:
    {
        ImGui::TextUnformatted("Auto-repeating tracks should be generated to fit the container");
        
        static const ImGui_Taffy::TextSegment TEXT_SEGMENTS[]
        {
            {"See: "},
            {
                "https://developer.mozilla.org/en-US/docs/Web/CSS/repeat#auto-fit", 
                ImGui_Taffy::description::LINK_COLOR, false, 
                "https://developer.mozilla.org/en-US/docs/Web/CSS/repeat#auto-fit"
            }
        };
        ImGui_Taffy::draw_text_segments(TEXT_SEGMENTS, false);
    } break;
    case taffy::GridTrackRepetition::Type::Count:
    {
        ImGui::TextUnformatted("The specified tracks should be repeated exacts N times");
    } break;

    default:
    {
        ImGui::TextUnformatted("Unknown");
    } break;
    }
}

bool GridTrackRepetition_is_description_interactive(const taffy::GridTrackRepetition::Type v)
{
    return 
        (v == taffy::GridTrackRepetition::Type::AutoFill) ||
        (v == taffy::GridTrackRepetition::Type::AutoFit);
}

static const ImGui_Taffy::TypeDescription DEFAULT_TYPE_DESCRIPTION {
    "GridTrackRepetition",
    [] {
        ImGui::TextUnformatted(
            "The first argument to a repeated track definition. This type represents the type of automatic repetition to perform.\n"
            "\n"
        );
        
        {
            static const ImGui_Taffy::TextSegment TEXT_SEGMENTS[]
            {
                {"See "},
                {
                    "https://www.w3.org/TR/css-grid-1/#auto-repeat",
                    ImGui_Taffy::description::LINK_COLOR, false,
                    "https://www.w3.org/TR/css-grid-1/#auto-repeat"
                },
                {" for an explanation of how auto-repeated track definitions work and the difference between AutoFit and AutoFill."}
            };
            ImGui_Taffy::draw_text_segments(TEXT_SEGMENTS, false);
        }
    }, 
    true
};

bool ImGui_Taffy::edit_GridTrackRepetition(
    taffy::GridTrackRepetition& value,
    
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
            for (const taffy::GridTrackRepetition::Type gtr_type_to_choose : GRID_TRACK_REPETITION_TYPES)
            {
                const bool is_selected = (gtr_type_to_choose == value.type());

                const char* selectable_label = GridTrackRepetition_to_string(gtr_type_to_choose);
                if (ImGui::Selectable(selectable_label, is_selected))
                {
                    value = GridTrackRepetition_from_type(gtr_type_to_choose);

                    modified = true;
                }

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected) {
                    ImGui::SetItemDefaultFocus();
                }
                
                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(GridTrackRepetition_is_description_interactive(gtr_type_to_choose),  [gtr_type_to_choose] {
                        GridTrackRepetition_show_description(gtr_type_to_choose);
                    });
                }
            }

            ImGui::EndCombo();
        }

        ImGui::SameLine();

        switch(value.type())
        {
        case taffy::GridTrackRepetition::Type::AutoFill: {
            ImGui::TextUnformatted("AutoFill");
        } break;
        case taffy::GridTrackRepetition::Type::AutoFit: {
            ImGui::TextUnformatted("AutoFit");
        } break;
        case taffy::GridTrackRepetition::Type::Count: {
            ImGui::TextUnformatted("Count");
            ImGui::SameLine();
            uint16_t v = value.value();
            if( ImGui::DragScalar("##value", ImGuiDataType_U16, &v) ) {
                value = taffy::GridTrackRepetition::Count(v);
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
