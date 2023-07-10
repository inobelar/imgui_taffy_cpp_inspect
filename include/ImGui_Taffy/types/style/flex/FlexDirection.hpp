#pragma once

#include <taffy/style/flex/FlexDirection.hpp>

#include <ImGui_Taffy/utils/TypeDescription.hpp>

namespace ImGui_Taffy {

bool edit_FlexDirection(
    taffy::FlexDirection& value,

    const TypeDescription& type_description = TypeDescription::Default()
);

} // namespace ImGui_Taffy
