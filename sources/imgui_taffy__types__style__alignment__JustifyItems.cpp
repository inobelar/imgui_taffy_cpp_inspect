#include <ImGui_Taffy/types/style/alignment/JustifyItems.hpp>

#include <ImGui_Taffy/types/style/alignment/AlignItems.hpp>

#include <imgui.h>
#include <ImGui_Taffy/utils/description.hpp>

static const ImGui_Taffy::TypeDescription DEFAULT_TYPE_DESCRIPTION {
    "JustifyItems",
    [] {
        ImGui::TextUnformatted(
            "Used to control how child nodes are aligned.\n"
            "Does not apply to Flexbox, and will be ignored if specified on a flex container\n"
            "For Grid it controls alignment in the inline axis\n"
            "\n"
        );
        ImGui_Taffy::description::Link("MDN", "https://developer.mozilla.org/en-US/docs/Web/CSS/justify-items");
    }, 
    true
};

bool ImGui_Taffy::edit_JustifyItems(
    taffy::JustifyItems& value,
    
    const TypeDescription& type_description
)
{
    const auto description = description_or_default(type_description, DEFAULT_TYPE_DESCRIPTION);
    
    // Same as 'AlignItems', since 'JustifyItems' is alias for 'AlignItems'
    return edit_AlignItems(
        value,
        
        description
    );
}
