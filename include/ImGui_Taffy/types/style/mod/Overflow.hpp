#pragma once

#include <taffy/style/mod/Overflow.hpp>

#include <ImGui_Taffy/utils/TypeDescription.hpp>

namespace ImGui_Taffy {

bool edit_Overflow(
    taffy::Overflow& value,

    const TypeDescription& type_description = TypeDescription::Default()
);

} // namespace ImGui_Taffy
