#include <ImGui_Taffy/types/style/alignment/AlignSelf.hpp>

#include <ImGui_Taffy/types/style/alignment/AlignItems.hpp>

#include <imgui.h>
#include <ImGui_Taffy/utils/description.hpp>
#include <ImGui_Taffy/utils/draw_text_segments.hpp>

static const ImGui_Taffy::TypeDescription DEFAULT_TYPE_DESCRIPTION {
    "AlignSelf",
    [] {
        ImGui::TextUnformatted(
            "Used to control how the specified nodes is aligned."
        );
        
        {
            static const ImGui_Taffy::TextSegment TEXT_SEGMENTS[]
            {
                {"Overrides the parent Node's "},
                {"AlignItems", ImGui_Taffy::description::CODE_INLINE_COLOR},
                {" property."}
            };
            
            ImGui_Taffy::draw_text_segments(TEXT_SEGMENTS, false);
            ImGui::NewLine();
        }
        
        ImGui::TextUnformatted(
            "For Flexbox it controls alignment in the cross axis\n"
            "For Grid it controls alignment in the block axis\n"
            "\n"
        );
        ImGui_Taffy::description::Link("MDN", "https://developer.mozilla.org/en-US/docs/Web/CSS/align-self");
    }, 
    true
};

bool ImGui_Taffy::edit_AlignSelf(
    taffy::AlignSelf& value,
    
    const TypeDescription& type_description
)
{
    const auto description = description_or_default(type_description, DEFAULT_TYPE_DESCRIPTION);
            
    // Same as 'AlignItems', since 'AlignSelf' is alias for 'AlignItems'
    return edit_AlignItems(
        value,
        
        description
    );
}
