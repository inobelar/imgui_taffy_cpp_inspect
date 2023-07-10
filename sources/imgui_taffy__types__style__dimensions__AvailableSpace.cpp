#include <ImGui_Taffy/types/style/dimensions/AvailableSpace.hpp>

#include <imgui.h>

#include <ImGui_Taffy/show_descriptions.hpp>
#include <ImGui_Taffy/utils/HelpMarker.hpp>
#include <ImGui_Taffy/utils/description.hpp>

static constexpr taffy::AvailableSpace::Type AVAILABLE_SPACE_TYPES[]
{
    taffy::AvailableSpace::Type::Definite,
    taffy::AvailableSpace::Type::MinContent,
    taffy::AvailableSpace::Type::MaxContent
};

const char* AvailableSpace_to_string(const taffy::AvailableSpace::Type v) 
{
    switch(v) {
    case taffy::AvailableSpace::Type::Definite   : return "Definite";
    case taffy::AvailableSpace::Type::MinContent : return "MinContent";
    case taffy::AvailableSpace::Type::MaxContent : return "MaxContent";

    default: return "Unknown";
    }
}

taffy::AvailableSpace AvailableSpace_from_type(const taffy::AvailableSpace::Type v)
{
    switch(v) {
    case taffy::AvailableSpace::Type::Definite   : return taffy::AvailableSpace::Definite(0.0f);
    case taffy::AvailableSpace::Type::MinContent : return taffy::AvailableSpace::MinContent();
    case taffy::AvailableSpace::Type::MaxContent : return taffy::AvailableSpace::MaxContent();

    default: return taffy::AvailableSpace::Definite(0.0f);
    }
}

void AvailableSpace_show_description(const taffy::AvailableSpace::Type v)
{
    switch(v) {
    case taffy::AvailableSpace::Type::Definite:
    {
        ImGui::TextUnformatted("The amount of space available is the specified number of pixels");
    } break;
    case taffy::AvailableSpace::Type::MinContent:
    {
        ImGui::TextUnformatted(
            "The amount of space available is indefinite and the node should be laid out under a min-content constraint"
        );
    } break;
    case taffy::AvailableSpace::Type::MaxContent:
    {
        ImGui::TextUnformatted(
            "The amount of space available is indefinite and the node should be laid out under a max-content constraint"
        );
    } break;

    default:
    {
        ImGui::TextUnformatted("Unknown");
    } break;
    }
}

static const ImGui_Taffy::TypeDescription DEFAULT_TYPE_DESCRIPTION {
    "AvailableSpace",
    [] {
        ImGui::TextUnformatted(
            "The amount of space available to a node in a given axis"
        );
        ImGui_Taffy::description::Link("https://www.w3.org/TR/css-sizing-3/#available");
    }, 
    true
};

bool ImGui_Taffy::edit_AvailableSpace(
    taffy::AvailableSpace& value,
    
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
            for (const taffy::AvailableSpace::Type availabe_space_to_choose : AVAILABLE_SPACE_TYPES)
            {
                const bool is_selected = (availabe_space_to_choose == value.type());

                const char* selectable_label = AvailableSpace_to_string(availabe_space_to_choose);
                if (ImGui::Selectable(selectable_label, is_selected))
                {
                    value = AvailableSpace_from_type(availabe_space_to_choose);

                    modified = true;
                }

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected) {
                    ImGui::SetItemDefaultFocus();
                }

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [availabe_space_to_choose] {
                        AvailableSpace_show_description(availabe_space_to_choose);
                    });
                }
            }

            ImGui::EndCombo();
        }

        ImGui::SameLine();

        switch(value.type())
        {
        case taffy::AvailableSpace::Type::Definite: {
            ImGui::TextUnformatted("Definite");
            ImGui::SameLine();
            float v = value.value();
            if( ImGui::DragFloat("##value", &v) ) {
                value = taffy::AvailableSpace::Definite(v);
                modified = true;
            }
        } break;
        case taffy::AvailableSpace::Type::MinContent: {
            ImGui::TextUnformatted("MinContent");
        } break;
        case taffy::AvailableSpace::Type::MaxContent: {
            ImGui::TextUnformatted("MaxContent");
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
