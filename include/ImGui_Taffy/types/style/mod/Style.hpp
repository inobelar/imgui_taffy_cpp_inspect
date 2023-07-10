#pragma once

#include <taffy/style/mod/Style.hpp>

#include <ImGui_Taffy/utils/TypeDescription.hpp>

namespace ImGui_Taffy {

bool edit_Style(
    taffy::Style& style,

    const TypeDescription& type_description = TypeDescription::Default()
);

} // namespace ImGui_Taffy
