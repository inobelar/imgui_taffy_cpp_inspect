#include <ImGui_Taffy/types/style/grid/GridPlacement.hpp>

#include <ImGui_Taffy/types/style/grid/GenericGridPlacement.hpp>

#include <imgui.h>
#include <ImGui_Taffy/utils/description.hpp>

static const ImGui_Taffy::TypeDescription DEFAULT_TYPE_DESCRIPTION {
    "GridPlacement",
    [] {
        ImGui::TextUnformatted(
            "A grid line placement specification. Used for grid-[row/column]-[start/end]. Named tracks are not implemented.\n"
            "\n"
        );
        
        ImGui_Taffy::description::Link("Specification", "https://www.w3.org/TR/css3-grid-layout/#typedef-grid-row-start-grid-line");
    }, 
    true
};

bool ImGui_Taffy::edit_GridPlacement(
    taffy::GridPlacement& value,
    
    const TypeDescription& type_description
)
{
    const auto description = description_or_default(type_description, DEFAULT_TYPE_DESCRIPTION);

    return edit_GenericGridPlacement_T<taffy::GridLine>(
        value,

        [] { return taffy::GenericGridPlacement<taffy::GridLine>::Auto(); }, // same as: taffy::GridPlacement::Default()
        [] { return taffy::GridLine(0); },
        [] (taffy::GridLine& v) -> bool
        {
            bool modified = false;

            int16_t value = v.as_i16();
            if( ImGui::DragScalar("##value", ImGuiDataType_S16, &value) ) {
                v = taffy::GridLine(value);
                modified = true;
            }

            return modified;
        },

        description
    );
}
