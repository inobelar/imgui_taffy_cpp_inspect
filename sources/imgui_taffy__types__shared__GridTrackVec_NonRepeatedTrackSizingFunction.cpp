#include <ImGui_Taffy/types/shared/GridTrackVec_NonRepeatedTrackSizingFunction.hpp>

#include <ImGui_Taffy/types/util/sys/GridTrackVec.hpp>
#include <ImGui_Taffy/types/style/grid/NonRepeatedTrackSizingFunction.hpp>

bool ImGui_Taffy::edit_GridTrackVec_NonRepeatedTrackSizingFunction(
    taffy::GridTrackVec<taffy::NonRepeatedTrackSizingFunction>& value
)
{
    return edit_GridTrackVec_T<taffy::NonRepeatedTrackSizingFunction>(
        value,
        [] { return taffy::NonRepeatedTrackSizingFunction::AUTO(); },
        [](taffy::NonRepeatedTrackSizingFunction& item) {
            return edit_NonRepeatedTrackSizingFunction(item);
        }
    );
}
