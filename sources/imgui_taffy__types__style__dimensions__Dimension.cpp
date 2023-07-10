#include <ImGui_Taffy/types/style/dimensions/Dimension.hpp>

#include <imgui.h>

#include <ImGui_Taffy/show_descriptions.hpp>
#include <ImGui_Taffy/utils/HelpMarker.hpp>
#include <ImGui_Taffy/utils/description.hpp>

static constexpr taffy::Dimension::Type DIMENSION_TYPES[]
{
    taffy::Dimension::Type::Length,
    taffy::Dimension::Type::Percent,
    taffy::Dimension::Type::Auto
};

const char* Dimension_to_string(const taffy::Dimension::Type v)
{
    switch(v) {
    case taffy::Dimension::Type::Length : return "Length";
    case taffy::Dimension::Type::Percent: return "Percent";
    case taffy::Dimension::Type::Auto   : return "Auto";

    default: return "Unknown";
    }
}

taffy::Dimension Dimension_from_type(const taffy::Dimension::Type v)
{
    switch(v) {
    case taffy::Dimension::Type::Length : return taffy::Dimension::Length(0.0f);
    case taffy::Dimension::Type::Percent: return taffy::Dimension::Percent(0.0f);
    case taffy::Dimension::Type::Auto   : return taffy::Dimension::Auto();
    default: return taffy::Dimension::Auto();
    }
}

void Dimension_show_description(const taffy::Dimension::Type v)
{
    switch(v) {
    case taffy::Dimension::Type::Length:
    {
        ImGui::TextUnformatted(
            "An absolute length in some abstract units. Users of Taffy may define what they correspond "
            "to in their application (pixels, logical pixels, mm, etc) as they see fit."
        );
    } break;
    case taffy::Dimension::Type::Percent:
    {
        ImGui::TextUnformatted("The dimension is stored in percentage relative to the parent item.");
    } break;
    case taffy::Dimension::Type::Auto:
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
    "Dimension",
    [] {
        ImGui::TextUnformatted("A unit of linear measurement");
    }, 
    false
};


bool ImGui_Taffy::edit_Dimension(
    taffy::Dimension& value,
    
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
            for (const taffy::Dimension::Type dimension_type_to_choose : DIMENSION_TYPES)
            {
                const bool is_selected = (dimension_type_to_choose == value.type());

                const char* selectable_label = Dimension_to_string(dimension_type_to_choose);
                if (ImGui::Selectable(selectable_label, is_selected))
                {
                    value = Dimension_from_type(dimension_type_to_choose);

                    modified = true;
                }

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected) {
                    ImGui::SetItemDefaultFocus();
                }

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [dimension_type_to_choose] {
                        Dimension_show_description(dimension_type_to_choose);
                    });
                }
            }

            ImGui::EndCombo();
        }

        ImGui::SameLine();

        switch(value.type())
        {
        case taffy::Dimension::Type::Length: {
            ImGui::TextUnformatted("Length");
            ImGui::SameLine();
            float length = value.value();
            if( ImGui::DragFloat("##length", &length) ) {
                value = taffy::Dimension::Length(length);
                modified = true;
            }
        } break;
        case taffy::Dimension::Type::Percent: {
            ImGui::TextUnformatted("Percent");
            ImGui::SameLine();
            float percent = value.value();
            if( ImGui::DragFloat("##percent", &percent, 0.01f) ) {
                value = taffy::Dimension::Percent(percent);
                modified = true;
            }
        } break;
        case taffy::Dimension::Type::Auto: {
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
