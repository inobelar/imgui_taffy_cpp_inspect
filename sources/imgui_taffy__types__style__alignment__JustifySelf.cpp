#include <ImGui_Taffy/types/style/alignment/JustifySelf.hpp>

#include <ImGui_Taffy/types/style/alignment/AlignItems.hpp>

#include <imgui.h>
#include <ImGui_Taffy/utils/description.hpp>
#include <ImGui_Taffy/utils/draw_text_segments.hpp>

static const ImGui_Taffy::TypeDescription DEFAULT_TYPE_DESCRIPTION {
    "JustifySelf",
    [] {
        ImGui::TextUnformatted(
            "Used to control how the specified nodes is aligned."
        );
        
        {
            static const ImGui_Taffy::TextSegment TEXT_SEGMENTS[]
            {
                {"Overrides the parent Node's "},
                {"JustifyItems", ImGui_Taffy::description::CODE_INLINE_COLOR},
                {" property."}
            };
            
            ImGui_Taffy::draw_text_segments(TEXT_SEGMENTS, false);
            ImGui::NewLine();
        }
        
        ImGui::TextUnformatted(
            "Does not apply to Flexbox, and will be ignored if specified on a flex child\n"
            "For Grid it controls alignment in the inline axis\n"
            "\n"
        );
        ImGui_Taffy::description::Link("MDN", "https://developer.mozilla.org/en-US/docs/Web/CSS/justify-self");
    }, 
    true
};

bool ImGui_Taffy::edit_JustifySelf(
    taffy::JustifySelf& value,
    
    const TypeDescription& type_description
)
{
    const auto description = description_or_default(type_description, DEFAULT_TYPE_DESCRIPTION);
    
    // Same as 'AlignItems', since 'JustifySelf' is alias for 'AlignItems'
    return edit_AlignItems(
        value,

        description
    );
}
