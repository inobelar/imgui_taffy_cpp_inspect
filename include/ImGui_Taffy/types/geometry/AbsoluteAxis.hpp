#pragma once

#include <taffy/geometry/AbsoluteAxis.hpp>

#include <ImGui_Taffy/utils/TypeDescription.hpp>

namespace ImGui_Taffy {

bool edit_AbsoluteAxis(
    taffy::AbsoluteAxis& value,

    const TypeDescription& type_description = TypeDescription::Default()
);

} // namespace ImGui_Taffy
