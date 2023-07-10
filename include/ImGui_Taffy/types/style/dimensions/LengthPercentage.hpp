#pragma once

#include <taffy/style/dimensions/LengthPercentage.hpp>

#include <ImGui_Taffy/utils/TypeDescription.hpp>

namespace ImGui_Taffy {

bool edit_LengthPercentage(
    taffy::LengthPercentage& value,

    const TypeDescription& type_description = TypeDescription::Default()
);

} // namespace ImGui_Taffy
