#include <ImGui_Taffy/types/style/dimensions/LengthPercentage.hpp>

#include <imgui.h>

#include <ImGui_Taffy/show_descriptions.hpp>
#include <ImGui_Taffy/utils/HelpMarker.hpp>
#include <ImGui_Taffy/utils/description.hpp>

static constexpr taffy::LengthPercentage::Type LENGTH_PERCENTAGE_TYPES[]
{
    taffy::LengthPercentage::Type::Length,
    taffy::LengthPercentage::Type::Percent
};

const char* LengthPercentage_to_string(const taffy::LengthPercentage::Type v)
{
    switch(v) {
    case taffy::LengthPercentage::Type::Length : return "Length";
    case taffy::LengthPercentage::Type::Percent: return "Percent";

    default: return "Unknown";
    }
}

taffy::LengthPercentage LengthPercentage_from_type(const taffy::LengthPercentage::Type v)
{
    switch(v) {
    case taffy::LengthPercentage::Type::Length : return taffy::LengthPercentage::Length(0.0f);
    case taffy::LengthPercentage::Type::Percent: return taffy::LengthPercentage::Percent(0.0f);
    default: return taffy::LengthPercentage::Length(0.0f);
    }
}

void LengthPercentage_show_description(const taffy::LengthPercentage::Type v)
{
    switch(v) {
    case taffy::LengthPercentage::Type::Length:
    {
        ImGui::TextUnformatted(
            "An absolute length in some abstract units. Users of Taffy may define what they correspond "
            "to in their application (pixels, logical pixels, mm, etc) as they see fit."
        );
    } break;
    case taffy::LengthPercentage::Type::Percent:
    {
        ImGui::TextUnformatted("The dimension is stored in percentage relative to the parent item.");
    } break;

    default:
    {
        ImGui::TextUnformatted("Unknown");
    } break;
    }
}

static const ImGui_Taffy::TypeDescription DEFAULT_TYPE_DESCRIPTION {
    "LengthPercentage",
    [] {
        ImGui::TextUnformatted("A unit of linear measurement");
    }, 
    false
};

bool ImGui_Taffy::edit_LengthPercentage(
    taffy::LengthPercentage& value,
    
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
            for (const taffy::LengthPercentage::Type lp_type_to_choose : LENGTH_PERCENTAGE_TYPES)
            {
                const bool is_selected = (lp_type_to_choose == value.type());

                const char* selectable_label = LengthPercentage_to_string(lp_type_to_choose);
                if (ImGui::Selectable(selectable_label, is_selected))
                {
                    value = LengthPercentage_from_type(lp_type_to_choose);

                    modified = true;
                }

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected) {
                    ImGui::SetItemDefaultFocus();
                }
                
                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [lp_type_to_choose] {
                        LengthPercentage_show_description(lp_type_to_choose);
                    });
                }
            }

            ImGui::EndCombo();
        }

        ImGui::SameLine();

        switch(value.type())
        {
        case taffy::LengthPercentage::Type::Length: {
            ImGui::TextUnformatted("Length");
            ImGui::SameLine();
            float length = value.value();
            if( ImGui::DragFloat("##length", &length) ) {
                value = taffy::LengthPercentage::Length(length);
                modified = true;
            }
        } break;
        case taffy::LengthPercentage::Type::Percent: {
            ImGui::TextUnformatted("Percent");
            ImGui::SameLine();
            float percent = value.value();
            if( ImGui::DragFloat("##percent", &percent, 0.01f) ) {
                value = taffy::LengthPercentage::Percent(percent);
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
