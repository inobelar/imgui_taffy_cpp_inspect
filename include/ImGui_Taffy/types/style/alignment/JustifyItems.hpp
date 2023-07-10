#pragma once

#include <taffy/style/alignment/AlignItems.hpp>

#include <ImGui_Taffy/utils/TypeDescription.hpp>

namespace ImGui_Taffy {

bool edit_JustifyItems(
    taffy::JustifyItems& value,

    const TypeDescription& type_description = TypeDescription::Default()
);

} // namespace ImGui_Taffy
