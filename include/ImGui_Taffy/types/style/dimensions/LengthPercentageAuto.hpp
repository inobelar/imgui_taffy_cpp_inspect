#pragma once

#include <taffy/style/dimensions/LengthPercentageAuto.hpp>

#include <ImGui_Taffy/utils/TypeDescription.hpp>

namespace ImGui_Taffy {

bool edit_LengthPercentageAuto(
    taffy::LengthPercentageAuto& value,

    const TypeDescription& type_description = TypeDescription::Default()
);

} // namespace ImGui_Taffy
