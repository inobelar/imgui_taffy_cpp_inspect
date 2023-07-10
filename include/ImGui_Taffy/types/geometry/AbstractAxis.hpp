#pragma once

#include <taffy/geometry/AbstractAxis.hpp>

#include <ImGui_Taffy/utils/TypeDescription.hpp>

namespace ImGui_Taffy {

bool edit_AbstractAxis(
    taffy::AbstractAxis& value,

    const TypeDescription& type_description = TypeDescription::Default()
);

} // namespace ImGui_Taffy
