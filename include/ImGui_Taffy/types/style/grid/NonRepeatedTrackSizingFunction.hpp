#pragma once

#include <taffy/style/grid/NonRepeatedTrackSizingFunction.hpp>

#include <ImGui_Taffy/utils/TypeDescription.hpp>

namespace ImGui_Taffy {

bool edit_NonRepeatedTrackSizingFunction(
    taffy::NonRepeatedTrackSizingFunction& value,

    const TypeDescription& type_description = TypeDescription::Default()
);

} // namespace ImGui_Taffy
