#include <ImGui_Taffy/types/style/alignment/JustifyContent.hpp>

#include <ImGui_Taffy/types/style/alignment/AlignContent.hpp>

#include <imgui.h>
#include <ImGui_Taffy/utils/description.hpp>

static const ImGui_Taffy::TypeDescription DEFAULT_TYPE_DESCRIPTION {
    "JustifyContent",
    [] {
        ImGui::TextUnformatted(
            "Sets the distribution of space between and around content items\n"
            "For Flexbox it controls alignment in the main axis\n"
            "For Grid it controls alignment in the inline axis\n"
            "\n"
        );
        ImGui_Taffy::description::Link("MDN", "https://developer.mozilla.org/en-US/docs/Web/CSS/justify-content");
    }, 
    true
};

bool ImGui_Taffy::edit_JustifyContent(
    taffy::JustifyContent& value,
    
    const TypeDescription& type_description
)
{
    const auto description = description_or_default(type_description, DEFAULT_TYPE_DESCRIPTION);
    
    // Same as 'AlignContent', since 'JustifyContent' is an alias for 'AlignContent'
    return edit_AlignContent(
        value,
        
        description
    );
}
