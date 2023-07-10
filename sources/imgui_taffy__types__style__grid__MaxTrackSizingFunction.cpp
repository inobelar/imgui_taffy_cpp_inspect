#include <ImGui_Taffy/types/style/grid/MaxTrackSizingFunction.hpp>

#include <imgui.h>

#include <ImGui_Taffy/types/style/dimensions/LengthPercentage.hpp>

#include <ImGui_Taffy/show_descriptions.hpp>
#include <ImGui_Taffy/utils/HelpMarker.hpp>
#include <ImGui_Taffy/utils/description.hpp>
#include <ImGui_Taffy/utils/draw_text_segments.hpp>

static constexpr taffy::MaxTrackSizingFunction::Type MAX_TRACK_SIZING_FUNCTION_TYPES[]
{
    taffy::MaxTrackSizingFunction::Type::Fixed,
    taffy::MaxTrackSizingFunction::Type::MinContent,
    taffy::MaxTrackSizingFunction::Type::MaxContent,
    taffy::MaxTrackSizingFunction::Type::FitContent,
    taffy::MaxTrackSizingFunction::Type::Auto,
    taffy::MaxTrackSizingFunction::Type::Fraction
};

const char* MaxTrackSizingFunction_to_string(const taffy::MaxTrackSizingFunction::Type v)
{
    switch(v) {
    case taffy::MaxTrackSizingFunction::Type::Fixed      : return "Fixed";
    case taffy::MaxTrackSizingFunction::Type::MinContent : return "MinContent";
    case taffy::MaxTrackSizingFunction::Type::MaxContent : return "MaxContent";
    case taffy::MaxTrackSizingFunction::Type::FitContent : return "FitContent";
    case taffy::MaxTrackSizingFunction::Type::Auto       : return "Auto";
    case taffy::MaxTrackSizingFunction::Type::Fraction   : return "Fraction";

    default: return "Unknown";
    }
}

taffy::MaxTrackSizingFunction MaxTrackSizingFunction_from_type(const taffy::MaxTrackSizingFunction::Type v)
{
    switch(v) {
    case taffy::MaxTrackSizingFunction::Type::Fixed      : return taffy::MaxTrackSizingFunction::Fixed(taffy::LengthPercentage::ZERO());
    case taffy::MaxTrackSizingFunction::Type::MinContent : return taffy::MaxTrackSizingFunction::MinContent();
    case taffy::MaxTrackSizingFunction::Type::MaxContent : return taffy::MaxTrackSizingFunction::MaxContent();
    case taffy::MaxTrackSizingFunction::Type::FitContent : return taffy::MaxTrackSizingFunction::FitContent(taffy::LengthPercentage::ZERO());
    case taffy::MaxTrackSizingFunction::Type::Auto       : return taffy::MaxTrackSizingFunction::Auto();
    case taffy::MaxTrackSizingFunction::Type::Fraction   : return taffy::MaxTrackSizingFunction::Fraction(0.0f);
    default: return taffy::MaxTrackSizingFunction::Auto();
    }
}

void MaxTrackSizingFunction_show_description(const taffy::MaxTrackSizingFunction::Type v)
{
    switch(v) {
    case taffy::MaxTrackSizingFunction::Type::Fixed:
    {
        ImGui::TextUnformatted("Track maximum size should be a fixed length or percentage value");
    } break;
    case taffy::MaxTrackSizingFunction::Type::MinContent:
    {
        ImGui::TextUnformatted("Track maximum size should be content sized under a min-content constraint");
    } break;
    case taffy::MaxTrackSizingFunction::Type::MaxContent:
    {
        ImGui::TextUnformatted("Track maximum size should be content sized under a max-content constraint");
    } break;
    case taffy::MaxTrackSizingFunction::Type::FitContent:
    {
        ImGui::TextUnformatted("Track maximum size should be sized according to the fit-content formula");
    } break;
    case taffy::MaxTrackSizingFunction::Type::Auto:
    {
        ImGui::TextUnformatted("Track maximum size should be automatically sized");
    } break;
    case taffy::MaxTrackSizingFunction::Type::Fraction:
    {
        {
            static const ImGui_Taffy::TextSegment TEXT_SEGMENTS[]
            {
                {"The dimension as a fraction of the total available grid space ("},
                {"fr", ImGui_Taffy::description::CODE_INLINE_COLOR},
                {" units in CSS)"}
            };
            ImGui_Taffy::draw_text_segments(TEXT_SEGMENTS, false);
            ImGui::NewLine();
        }
        
        ImGui::TextUnformatted("Specified value is the numerator of the fraction. Denominator is the sum of all fraction specified in that grid dimension");
        
        {
            static const ImGui_Taffy::TextSegment TEXT_SEGMENTS[]
            {
                {"Spec: "},
                {
                    "https://www.w3.org/TR/css3-grid-layout/#fr-unit",
                    ImGui_Taffy::description::LINK_COLOR, false,
                    "https://www.w3.org/TR/css3-grid-layout/#fr-unit"
                }
            };
            ImGui_Taffy::draw_text_segments(TEXT_SEGMENTS, false);
        }
    } break;

    default:
    {
        ImGui::TextUnformatted("Unknown");
    } break;
    }
}

bool MaxTrackSizingFunction_is_description_interactive(const taffy::MaxTrackSizingFunction::Type v)
{
    return (v == taffy::MaxTrackSizingFunction::Type::Fraction);
}

static const ImGui_Taffy::TypeDescription DEFAULT_TYPE_DESCRIPTION {
    "MaxTrackSizingFunction",
    [] {
        ImGui::TextUnformatted(
            "Maximum track sizing function\n"
            "\n"
            "Specifies the maximum size of a grid track. A grid track will automatically size between it's minimum and maximum size based "
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

bool ImGui_Taffy::edit_MaxTrackSizingFunction(
    taffy::MaxTrackSizingFunction& value,
    
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
            for (const taffy::MaxTrackSizingFunction::Type mts_type_to_choose : MAX_TRACK_SIZING_FUNCTION_TYPES)
            {
                const bool is_selected = (mts_type_to_choose == value.type());

                const char* selectable_label = MaxTrackSizingFunction_to_string(mts_type_to_choose);
                if (ImGui::Selectable(selectable_label, is_selected))
                {
                    value = MaxTrackSizingFunction_from_type(mts_type_to_choose);

                    modified = true;
                }

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected) {
                    ImGui::SetItemDefaultFocus();
                }
                
                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(MaxTrackSizingFunction_is_description_interactive(mts_type_to_choose), [mts_type_to_choose] {            
                        MaxTrackSizingFunction_show_description(mts_type_to_choose);
                    });
                }
            }

            ImGui::EndCombo();
        }

        ImGui::SameLine();

        switch(value.type())
        {
        case taffy::MaxTrackSizingFunction::Type::Fixed: {
            ImGui::TextUnformatted("Fixed");
            ImGui::SameLine();
            taffy::LengthPercentage v = value.length_percentage();
            if( edit_LengthPercentage(v) ) {
                value = taffy::MaxTrackSizingFunction::Fixed(v);
                modified = true;
            }
        } break;
        case taffy::MaxTrackSizingFunction::Type::MinContent: {
            ImGui::TextUnformatted("MinContent");
        } break;
        case taffy::MaxTrackSizingFunction::Type::MaxContent: {
            ImGui::TextUnformatted("MaxContent");
        } break;
        case taffy::MaxTrackSizingFunction::Type::FitContent: {
            ImGui::TextUnformatted("FitContent");
            ImGui::SameLine();
            taffy::LengthPercentage v = value.length_percentage();
            if( edit_LengthPercentage(v) ) {
                value = taffy::MaxTrackSizingFunction::FitContent(v);
                modified = true;
            }
        } break;
        case taffy::MaxTrackSizingFunction::Type::Auto: {
            ImGui::TextUnformatted("Auto");
        } break;
        case taffy::MaxTrackSizingFunction::Type::Fraction: {
            ImGui::TextUnformatted("Fraction");
            ImGui::SameLine();
            float v = value.fraction();
            if( ImGui::DragFloat("##fraction", &v) ) {
                value = taffy::MaxTrackSizingFunction::Fraction(v);
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
