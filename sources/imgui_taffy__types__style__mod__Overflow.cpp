#include <ImGui_Taffy/types/style/mod/Overflow.hpp>

#include <imgui.h>

#include <ImGui_Taffy/show_descriptions.hpp>
#include <ImGui_Taffy/utils/HelpMarker.hpp>
#include <ImGui_Taffy/utils/description.hpp>
#include <ImGui_Taffy/utils/draw_text_segments.hpp>

static constexpr taffy::Overflow::Type OVERFLOW_TYPES[]
{
    taffy::Overflow::Type::Visible,
    taffy::Overflow::Type::Hidden,
    taffy::Overflow::Type::Scroll
};

const char* Overflow_to_string(const taffy::Overflow::Type v)
{
    switch(v) {
        case taffy::Overflow::Type::Visible : return "Visible";
        case taffy::Overflow::Type::Hidden  : return "Hidden";
        case taffy::Overflow::Type::Scroll  : return "Scroll";

        default: return "Unknown";
    }
}

taffy::Overflow Overflow_from_type(const taffy::Overflow::Type v)
{
    switch(v) {
        case taffy::Overflow::Type::Visible : return taffy::Overflow::Visible();
        case taffy::Overflow::Type::Hidden  : return taffy::Overflow::Hidden();
        case taffy::Overflow::Type::Scroll  : return taffy::Overflow::Scroll();

        default: return taffy::Overflow::Default();
    }
}

void Overflow_show_description(const taffy::Overflow::Type v)
{
    switch(v) {
    case taffy::Overflow::Type::Visible:
    {
        ImGui::TextUnformatted(
            "The automatic minimum size of this node as a flexbox/grid item should be based on the size of it's content."
        );
    } break;
    case taffy::Overflow::Type::Hidden:
    {
        static const ImGui_Taffy::TextSegment TEXT_SEGMENTS[]
        {
            {"The automatic minimum size of this node as a flexbox/grid item should be "},
            {"0", ImGui_Taffy::description::CODE_INLINE_COLOR},
            {"."}
        };
        ImGui_Taffy::draw_text_segments(TEXT_SEGMENTS, false);
    } break;
    case taffy::Overflow::Type::Scroll:
    {
        static const ImGui_Taffy::TextSegment SEGMENTS[]
        {
            {"The automatic minimum size of this node as a flexbox/grid item should be "},
            {"0", ImGui_Taffy::description::CODE_INLINE_COLOR},
            {". Additionally, space should be reserved for a scrollbar. The amount of space reserved is controlled by the "},
            {"scrollbar_width", ImGui_Taffy::description::CODE_INLINE_COLOR},
            {" property."}
        };
        ImGui_Taffy::draw_text_segments(SEGMENTS, false);
    } break;

    default:
    {
        ImGui::TextUnformatted("Unknown");
    } break;
    }
}

static const ImGui_Taffy::TypeDescription DEFAULT_TYPE_DESCRIPTION {
    "Overflow",
    [] {
        ImGui::TextUnformatted(
            "How children overflowing their container should affect layout\n"
            "\n"
            "In CSS the primary effect of this property is to control whether contents of a parent container that overflow that container should "
            "be displayed anyway, be clipped, or trigger the container to become a scroll container. However it also has secondary effects on layout, "
            "the main ones being:\n"
            "\n"
        );

        {
            static const ImGui_Taffy::TextSegment TEXT_SEGMENTS[]
            {
                {"The automatic minimum size Flexbox/CSS Grid items with non-"},
                {"Visible", ImGui_Taffy::description::CODE_INLINE_COLOR},
                {" overflow is "},
                {"0", ImGui_Taffy::description::CODE_INLINE_COLOR},
                {" rather than being content based"}
            };

            ImGui::Bullet();
            ImGui::SameLine();
            ImGui_Taffy::draw_text_segments(TEXT_SEGMENTS, true);
            ImGui::NewLine();
        }

        {
            static const ImGui_Taffy::TextSegment TEXT_SEGMENTS[]
            {
                {"Overflow::Scroll", ImGui_Taffy::description::CODE_INLINE_COLOR},
                {" nodes have space in the layout reserved for a scrollbar (width controlled by the "},
                {"scrollbar_width", ImGui_Taffy::description::CODE_INLINE_COLOR},
                {" property)"}
            };

            ImGui::Bullet();
            ImGui::SameLine();
            ImGui_Taffy::draw_text_segments(TEXT_SEGMENTS, true);
            ImGui::NewLine();
        }

        ImGui::NewLine();

        {
            static const ImGui_Taffy::TextSegment TEXT_SEGMENTS[]
            {
                {"In Taffy, we only implement the layout related secondary effects as we are not concerned with drawing/painting. The amount of space reserved for "},
                {"a scrollbar is controlled by the "},
                {"scrollbar_width", ImGui_Taffy::description::CODE_INLINE_COLOR},
                {" property. If this is "},
                {"0", ImGui_Taffy::description::CODE_INLINE_COLOR},
                {" then "},
                {"Scroll", ImGui_Taffy::description::CODE_INLINE_COLOR},
                {" behaves identically to "},
                {"Hidden", ImGui_Taffy::description::CODE_INLINE_COLOR},
                {"."}
            };

            ImGui_Taffy::draw_text_segments(TEXT_SEGMENTS, false);
            ImGui::NewLine();
        }

        ImGui::NewLine();

        ImGui_Taffy::description::Link("https://developer.mozilla.org/en-US/docs/Web/CSS/overflow");
    },
    true
};

bool ImGui_Taffy::edit_Overflow(
    taffy::Overflow& value,

    const TypeDescription& type_description
)
{
    const bool show_descriptions = is_show_descriptions();

    bool modified = false;

    ImGui::PushID(&value);
    {
        const char* combo_label = Overflow_to_string(value.type());
        if (ImGui::BeginCombo("##combo", combo_label))
        {
            for (const taffy::Overflow::Type overflow_type_to_choose : OVERFLOW_TYPES)
            {
                const bool is_selected = (overflow_type_to_choose == value.type());

                const char* selectable_label = Overflow_to_string(overflow_type_to_choose);
                if (ImGui::Selectable(selectable_label, is_selected))
                {
                    value = Overflow_from_type(overflow_type_to_choose);

                    modified = true;
                }

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected) {
                    ImGui::SetItemDefaultFocus();
                }

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [overflow_type_to_choose] {
                        Overflow_show_description(overflow_type_to_choose);
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
