#pragma once

#include <taffy/style/grid/TrackSizingFunction.hpp>

#include <ImGui_Taffy/utils/TypeDescription.hpp>

namespace ImGui_Taffy {

bool edit_TrackSizingFunction(
    taffy::TrackSizingFunction& value,

    const TypeDescription& type_description = TypeDescription::Default()
);

} // namespace ImGui_Taffy
