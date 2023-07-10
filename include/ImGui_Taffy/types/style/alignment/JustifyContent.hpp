#pragma once

#include <taffy/style/alignment/AlignContent.hpp>

#include <ImGui_Taffy/utils/TypeDescription.hpp>

namespace ImGui_Taffy {

bool edit_JustifyContent(
    taffy::JustifyContent& value,

    const TypeDescription& type_description = TypeDescription::Default()
);

} // namespace ImGui_Taffy
