#pragma once

#include <taffy/style/grid/OriginZeroGridPlacement.hpp>

#include <ImGui_Taffy/utils/TypeDescription.hpp>

namespace ImGui_Taffy {

bool edit_OriginZeroGridPlacement(
    taffy::OriginZeroGridPlacement& value,

    const TypeDescription& type_description = TypeDescription::Default()
);

} // namespace ImGui_Taffy
