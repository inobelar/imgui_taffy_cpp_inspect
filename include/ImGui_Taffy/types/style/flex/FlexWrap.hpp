#pragma once

#include <taffy/style/flex/FlexWrap.hpp>

#include <ImGui_Taffy/utils/TypeDescription.hpp>

namespace ImGui_Taffy {

bool edit_FlexWrap(
    taffy::FlexWrap& value,

    const TypeDescription& type_description = TypeDescription::Default()
);

} // namespace ImGui_Taffy
