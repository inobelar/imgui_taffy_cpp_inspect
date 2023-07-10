#include <ImGui_Taffy/types/style/mod/Position.hpp>

#include <imgui.h>

#include <ImGui_Taffy/show_descriptions.hpp>
#include <ImGui_Taffy/utils/HelpMarker.hpp>
#include <ImGui_Taffy/utils/description.hpp>
#include <ImGui_Taffy/utils/draw_text_segments.hpp>

static constexpr taffy::Position::Type POSITION_TYPES[]
{
    taffy::Position::Type::Relative,
    taffy::Position::Type::Absolute
};

const char* Position_to_string(const taffy::Position::Type v) 
{
    switch(v) {
    case taffy::Position::Type::Relative: return "Relative";
    case taffy::Position::Type::Absolute: return "Absolute";

    default: return "Unknown";
    }
}

taffy::Position Position_from_type(const taffy::Position::Type v)
{
    switch(v) {
    case taffy::Position::Type::Relative : return taffy::Position::Relative();
    case taffy::Position::Type::Absolute : return taffy::Position::Absolute();

    default: return taffy::Position::Default();
    }
}

void Position_show_description(const taffy::Position::Type v)
{
    switch(v) {
    case taffy::Position::Type::Relative: {
        ImGui::TextUnformatted(
            "The offset is computed relative to the final position given by the layout algorithm.\n"
            "Offsets do not affect the position of any other items; they are effectively a correction factor applied at the end."
        );
    } break;
    case taffy::Position::Type::Absolute: {
        ImGui::TextUnformatted(
            "The offset is computed relative to this item's closest positioned ancestor, if any.\n"
            "Otherwise, it is placed relative to the origin.\n"
            "No space is created for the item in the page layout, and its size will not be altered."
        );
        ImGui::NewLine();

        static const ImGui_Taffy::TextSegment TEXT_SEGMENTS[]
        {
            {"WARNING", ImGui_Taffy::description::WARNING_COLOR},
            {": to opt-out of layouting entirely, you must use "},
            {"Display::None", ImGui_Taffy::description::CODE_INLINE_COLOR},
            {" instead on your "},
            {"Style", ImGui_Taffy::description::CODE_INLINE_COLOR},
            {" object."}
        };

        ImGui_Taffy::draw_text_segments(TEXT_SEGMENTS, false);
    } break;

    default: {
        ImGui::TextUnformatted("Unknown");
    } break;
    }
}

static const ImGui_Taffy::TypeDescription DEFAULT_TYPE_DESCRIPTION {
    "Overflow",
    [] {
        ImGui::TextUnformatted(
            "The positioning strategy for this item.\n"
            "\n"
        );
        
        {
            static const ImGui_Taffy::TextSegment TEXT_SEGMENTS[]
            {
                {"This controls both how the origin is determined for the "},
                {"Style::position", ImGui_Taffy::description::CODE_INLINE_COLOR},
                {" field, and whether or not the item will be controlled by flexbox's layout algorithm."},
            };
            ImGui_Taffy::draw_text_segments(TEXT_SEGMENTS, true);
            ImGui::NewLine();
        }
        
        ImGui::NewLine();
        
        {
            static const ImGui_Taffy::TextSegment TEXT_SEGMENTS[]
            {
                {"WARNING", ImGui_Taffy::description::WARNING_COLOR},
                {": this enum follows the behavior of "},
                {
                    "CSS's `position` property", 
                    ImGui_Taffy::description::LINK_COLOR, false,
                    "https://developer.mozilla.org/en-US/docs/Web/CSS/position"
                },
                {", which can be unintuitive."}
            };
            ImGui_Taffy::draw_text_segments(TEXT_SEGMENTS, true);
            ImGui::NewLine();
        }
        
        ImGui::NewLine();
        
        {
            static const ImGui_Taffy::TextSegment TEXT_SEGMENTS[]
            {
                {"Position::Relative", ImGui_Taffy::description::CODE_INLINE_COLOR},
                {" is the default value, in contrast to the default behavior in CSS."}
            };
            ImGui_Taffy::draw_text_segments(TEXT_SEGMENTS, true);
            ImGui::NewLine();
        }
    },
    true
};

bool ImGui_Taffy::edit_Position(
    taffy::Position& value,
    
    const TypeDescription& type_description
)
{
    const bool show_descriptions = is_show_descriptions();

    bool modified = false;

    ImGui::PushID(&value);
    {
        const char* combo_label = Position_to_string(value.type());
        if (ImGui::BeginCombo("##combo", combo_label))
        {
            for (const taffy::Position::Type position_type_to_choose : POSITION_TYPES)
            {
                const bool is_selected = (position_type_to_choose == value.type());

                const char* selectable_label = Position_to_string(position_type_to_choose);
                if (ImGui::Selectable(selectable_label, is_selected))
                {
                    value = Position_from_type(position_type_to_choose);

                    modified = true;
                }

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected) {
                    ImGui::SetItemDefaultFocus();
                }

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [position_type_to_choose] {
                        Position_show_description(position_type_to_choose);
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
