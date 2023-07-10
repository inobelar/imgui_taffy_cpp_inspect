#pragma once

#include <taffy/style/grid/MinTrackSizingFunction.hpp>

#include <ImGui_Taffy/utils/TypeDescription.hpp>

namespace ImGui_Taffy {

bool edit_MinTrackSizingFunction(
    taffy::MinTrackSizingFunction& value,

    const TypeDescription& type_description = TypeDescription::Default()
);

} // namespace ImGui_Taffy
