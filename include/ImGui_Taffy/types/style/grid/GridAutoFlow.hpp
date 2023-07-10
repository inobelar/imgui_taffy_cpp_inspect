#pragma once

#include <taffy/style/grid/GridAutoFlow.hpp>

#include <ImGui_Taffy/utils/TypeDescription.hpp>

namespace ImGui_Taffy {

bool edit_GridAutoFlow(
    taffy::GridAutoFlow& value,

    const TypeDescription& type_description = TypeDescription::Default()
);

} // namespace ImGui_Taffy
