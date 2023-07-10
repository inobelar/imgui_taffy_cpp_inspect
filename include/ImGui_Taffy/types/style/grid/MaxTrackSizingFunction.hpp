#pragma once

#include <taffy/style/grid/MaxTrackSizingFunction.hpp>

#include <ImGui_Taffy/utils/TypeDescription.hpp>

namespace ImGui_Taffy {

bool edit_MaxTrackSizingFunction(
    taffy::MaxTrackSizingFunction& value,

    const TypeDescription& type_description = TypeDescription::Default()
);

} // namespace ImGui_Taffy
