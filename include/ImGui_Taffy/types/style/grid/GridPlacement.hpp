#pragma once

#include <taffy/style/grid/GridPlacement.hpp>

#include <ImGui_Taffy/utils/TypeDescription.hpp>

namespace ImGui_Taffy {

bool edit_GridPlacement(
    taffy::GridPlacement& value,

    const TypeDescription& type_description = TypeDescription::Default()
);

} // namespace ImGui_Taffy
