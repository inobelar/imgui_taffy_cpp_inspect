#pragma once

#include <taffy/style/grid/GridTrackRepetition.hpp>

#include <ImGui_Taffy/utils/TypeDescription.hpp>

namespace ImGui_Taffy {

bool edit_GridTrackRepetition(
    taffy::GridTrackRepetition& value,

    const TypeDescription& type_description = TypeDescription::Default()
);

} // namespace ImGui_Taffy
