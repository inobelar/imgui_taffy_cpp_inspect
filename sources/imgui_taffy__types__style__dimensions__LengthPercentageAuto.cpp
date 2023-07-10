#include <ImGui_Taffy/types/style/dimensions/LengthPercentageAuto.hpp>

#include <imgui.h>

#include <ImGui_Taffy/show_descriptions.hpp>
#include <ImGui_Taffy/utils/HelpMarker.hpp>
#include <ImGui_Taffy/utils/description.hpp>

static constexpr taffy::LengthPercentageAuto::Type LENGTH_PERCENTAGE_AUTO_TYPES[]
{
    taffy::LengthPercentageAuto::Type::Length,
    taffy::LengthPercentageAuto::Type::Percent,
    taffy::LengthPercentageAuto::Type::Auto
};

const char* LengthPercentageAuto_to_string(const taffy::LengthPercentageAuto::Type v)
{
    switch(v) {
    case taffy::LengthPercentageAuto::Type::Length : return "Length";
    case taffy::LengthPercentageAuto::Type::Percent: return "Percent";
    case taffy::LengthPercentageAuto::Type::Auto   : return "Auto";

    default: return "Unknown";
    }
}

taffy::LengthPercentageAuto LengthPercentageAuto_from_type(const taffy::LengthPercentageAuto::Type v)
{
    switch(v) {
    case taffy::LengthPercentageAuto::Type::Length : return taffy::LengthPercentageAuto::Length(0.0f);
    case taffy::LengthPercentageAuto::Type::Percent: return taffy::LengthPercentageAuto::Percent(0.0f);
    case taffy::LengthPercentageAuto::Type::Auto   : return taffy::LengthPercentageAuto::Auto();
    default: return taffy::LengthPercentageAuto::Auto();
    }
}

void LengthPercentageAuto_show_description(const taffy::LengthPercentageAuto::Type v)
{
    switch(v) {
    case taffy::LengthPercentageAuto::Type::Length:
    {
        ImGui::TextUnformatted(
            "An absolute length in some abstract units. Users of Taffy may define what they correspond "
            "to in their application (pixels, logical pixels, mm, etc) as they see fit."
        );
    } break;
    case taffy::LengthPercentageAuto::Type::Percent:
    {
        ImGui::TextUnformatted("The dimension is stored in percentage relative to the parent item.");
    } break;
    case taffy::LengthPercentageAuto::Type::Auto:
    {
        ImGui::TextUnformatted("The dimension should be automatically computed");
    } break;

    default:
    {
        ImGui::TextUnformatted("Unknown");
    } break;
    }
}

static const ImGui_Taffy::TypeDescription DEFAULT_TYPE_DESCRIPTION {
    "LengthPercentageAuto",
    [] {
        ImGui::TextUnformatted("A unit of linear measurement");
    }, 
    false
};

bool ImGui_Taffy::edit_LengthPercentageAuto(
    taffy::LengthPercentageAuto& value,
    
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
            for (const taffy::LengthPercentageAuto::Type lpa_type_to_choose : LENGTH_PERCENTAGE_AUTO_TYPES)
            {
                const bool is_selected = (lpa_type_to_choose == value.type());

                const char* selectable_label = LengthPercentageAuto_to_string(lpa_type_to_choose);
                if (ImGui::Selectable(selectable_label, is_selected))
                {
                    value = LengthPercentageAuto_from_type(lpa_type_to_choose);

                    modified = true;
                }

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected) {
                    ImGui::SetItemDefaultFocus();
                }
                
                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [lpa_type_to_choose] {
                        LengthPercentageAuto_show_description(lpa_type_to_choose);
                    });
                }
            }

            ImGui::EndCombo();
        }

        ImGui::SameLine();

        switch(value.type())
        {
        case taffy::LengthPercentageAuto::Type::Length: {
            ImGui::TextUnformatted("Length");
            ImGui::SameLine();
            float length = value.value();
            if( ImGui::DragFloat("##length", &length) ) {
                value = taffy::LengthPercentageAuto::Length(length);
                modified = true;
            }
        } break;
        case taffy::LengthPercentageAuto::Type::Percent: {
            ImGui::TextUnformatted("Percent");
            ImGui::SameLine();
            float percent = value.value();
            if( ImGui::DragFloat("##percent", &percent, 0.01f) ) {
                value = taffy::LengthPercentageAuto::Percent(percent);
                modified = true;
            }
        } break;
        case taffy::LengthPercentageAuto::Type::Auto: {
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
