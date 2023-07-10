#pragma once

#include <taffy/style/alignment/AlignContent.hpp>

#include <ImGui_Taffy/utils/TypeDescription.hpp>

namespace ImGui_Taffy {

bool edit_AlignContent(
    taffy::AlignContent& value,

    const TypeDescription& type_description = TypeDescription::Default()
);

} // namespace ImGui_Taffy
