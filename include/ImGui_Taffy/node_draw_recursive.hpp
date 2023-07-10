#pragma once

#include <taffy/tree/mod/LayoutTree.hpp>

#include <imgui.h>

namespace ImGui_Taffy {

struct Node_Draw_Style
{
    ImU32 node_nonfocused_color;
    ImU32 node_focused_color;

    float node_nonfocused_thickness;
    float node_focused_thickness;

    ImU32 position_offset_color;
    ImU32 margin_color;
    ImU32 border_color;
    ImU32 padding_color;

    ImU32 values_color;

    Node_Draw_Style();
};

void node_draw_recursive(
    const taffy::LayoutTree& tree,
    const taffy::NodeId node,

    ImDrawList* draw_list,

    const ImVec2& origin,
    const taffy::Option<taffy::NodeId>& focused_node = taffy::Option<taffy::NodeId>{}, // None

    const Node_Draw_Style* style = nullptr
);

} // namespace ImGui_Taffy
