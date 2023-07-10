#include <ImGui_Taffy/types/style/flex/FlexWrap.hpp>

#include <imgui.h>

#include <ImGui_Taffy/show_descriptions.hpp>
#include <ImGui_Taffy/utils/HelpMarker.hpp>
#include <ImGui_Taffy/utils/description.hpp>
#include <ImGui_Taffy/utils/draw_text_segments.hpp>

static constexpr taffy::FlexWrap::Type FLEX_WRAP_TYPES[]
{
    taffy::FlexWrap::Type::NoWrap,
    taffy::FlexWrap::Type::Wrap,
    taffy::FlexWrap::Type::WrapReverse
};

const char* FlexWrap_to_string(const taffy::FlexWrap::Type v)
{
    switch(v) {
    case taffy::FlexWrap::Type::NoWrap      : return "NoWrap";
    case taffy::FlexWrap::Type::Wrap        : return "Wrap";
    case taffy::FlexWrap::Type::WrapReverse : return "WrapReverse";

    default: return "Unknown";
    }
}

taffy::FlexWrap FlexWrap_from_type(const taffy::FlexWrap::Type v)
{
    switch(v) {
    case taffy::FlexWrap::Type::NoWrap      : return taffy::FlexWrap::NoWrap();
    case taffy::FlexWrap::Type::Wrap        : return taffy::FlexWrap::Wrap();
    case taffy::FlexWrap::Type::WrapReverse : return taffy::FlexWrap::WrapReverse();

    default: return taffy::FlexWrap::Default();
    }
}

void FlexWrap_show_description(const taffy::FlexWrap::Type v)
{
    switch(v) {
    case taffy::FlexWrap::Type::NoWrap:
    {
        ImGui::TextUnformatted("Items will not wrap and stay on a single line");
    } break;
    case taffy::FlexWrap::Type::Wrap:
    {
        static const ImGui_Taffy::TextSegment TEXT_SEGMENTS[]
        {
            {"Items will wrap according to this item's "},
            {"FlexDirection", ImGui_Taffy::description::CODE_INLINE_COLOR}
        };
        
        ImGui_Taffy::draw_text_segments(TEXT_SEGMENTS, false);
    } break;
    case taffy::FlexWrap::Type::WrapReverse:
    {
        static const ImGui_Taffy::TextSegment TEXT_SEGMENTS[]
        {
            {"Items will wrap in the opposite direction to this item's "},
            {"FlexDirection", ImGui_Taffy::description::CODE_INLINE_COLOR}
        };
        
        ImGui_Taffy::draw_text_segments(TEXT_SEGMENTS, false);
    } break;

    default:
    {
        ImGui::TextUnformatted("Unknown");
    } break;
    }
}

static const ImGui_Taffy::TypeDescription DEFAULT_TYPE_DESCRIPTION {
    "FlexWrap",
    [] {
        ImGui::TextUnformatted(
            "Controls whether flex items are forced onto one line or can wrap onto multiple lines.\n"
            "\n"
        );
        
        ImGui_Taffy::description::Link("Specification", "https://www.w3.org/TR/css-flexbox-1/#flex-wrap-property");
    }, 
    true
};

bool ImGui_Taffy::edit_FlexWrap(
    taffy::FlexWrap& value,
    
    const TypeDescription& type_description
)
{
    const bool show_descriptions = is_show_descriptions();

    bool modified = false;

    ImGui::PushID(&value);
    {
        const char* combo_label = FlexWrap_to_string(value.type());
        if (ImGui::BeginCombo("##combo", combo_label))
        {
            for (const taffy::FlexWrap::Type flex_wrap_type_to_choose : FLEX_WRAP_TYPES)
            {
                const bool is_selected = (flex_wrap_type_to_choose == value.type());

                const char* selectable_label = FlexWrap_to_string(flex_wrap_type_to_choose);
                if (ImGui::Selectable(selectable_label, is_selected))
                {
                    value = FlexWrap_from_type(flex_wrap_type_to_choose);

                    modified = true;
                }

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected) {
                    ImGui::SetItemDefaultFocus();
                }

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [flex_wrap_type_to_choose] {
                        FlexWrap_show_description(flex_wrap_type_to_choose);
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
