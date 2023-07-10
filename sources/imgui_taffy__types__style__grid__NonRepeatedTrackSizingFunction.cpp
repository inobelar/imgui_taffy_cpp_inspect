#include <ImGui_Taffy/types/style/grid/NonRepeatedTrackSizingFunction.hpp>

#include <ImGui_Taffy/types/geometry/MinMax.hpp>
#include <ImGui_Taffy/types/style/grid/MinTrackSizingFunction.hpp>
#include <ImGui_Taffy/types/style/grid/MaxTrackSizingFunction.hpp>

#include <imgui.h>

static const ImGui_Taffy::TypeDescription DEFAULT_TYPE_DESCRIPTION {
    "NonRepeatedTrackSizingFunction",
    [] {
        ImGui::TextUnformatted(
            "The sizing function for a grid track (row/column) (either auto-track or template track)\n"
            "May either be a MinMax variant which specifies separate values for the min-/max- track sizing functions "
            "or a scalar value which applies to both track sizing functions."
        );
    },
    false
};

bool ImGui_Taffy::edit_NonRepeatedTrackSizingFunction(
    taffy::NonRepeatedTrackSizingFunction& value,
    
    const TypeDescription& type_description
)
{
    const auto description = description_or_default(type_description, DEFAULT_TYPE_DESCRIPTION);
    
    return edit_MinMax_T<taffy::MinTrackSizingFunction, taffy::MaxTrackSizingFunction>(
        value,
        [](taffy::MinTrackSizingFunction& v) { return edit_MinTrackSizingFunction(v); },
        [](taffy::MaxTrackSizingFunction& v) { return edit_MaxTrackSizingFunction(v); },
                                                                                       
        description
    );
}
