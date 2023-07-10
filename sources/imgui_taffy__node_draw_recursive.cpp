#include <ImGui_Taffy/node_draw_recursive.hpp>

// -------------------------------------------------------------------------
// Constants

// Colors similar to present on yogalayout.com. TODO: change them to something more unique
ImGui_Taffy::Node_Draw_Style::Node_Draw_Style()
    : node_nonfocused_color( IM_COL32( 48,  56,  69,  51) ) // Semi-transmarent gray: rgba(48, 56, 69, 0.2)
    , node_focused_color   ( IM_COL32(107, 206, 187, 255) ) // Non-transparent  cyan: rgba(107, 206, 187, 1.0)

    , node_nonfocused_thickness( 1.0f )
    , node_focused_thickness   ( 2.0f )

    , position_offset_color( IM_COL32(115, 51, 205, 25) ) // Semi-transparent violet: rgba(115, 51, 205, 0.1)
    , margin_color         ( IM_COL32(214, 43,  28, 25) ) // Semi-transparent red:    rgba(214, 43, 28, 0.1)
    , border_color         ( IM_COL32(251, 170, 51, 38) ) // Semi-transparent yellow: rgba(251, 170, 51, 0.15)
    , padding_color        ( IM_COL32(123, 179, 41, 25) ) // Semi-transparent green:  rgba(123, 179, 41, 0.1)

    , values_color         ( IM_COL32(255, 255, 255, 127) ) // Semi-transparent white
{ }

static ImGui_Taffy::Node_Draw_Style DEFAULT_STYLE = {};

static constexpr size_t TEXT_BUFFER_SIZE = 32;
static char text_buffer[TEXT_BUFFER_SIZE];
static constexpr char FLOAT_FMT[] = "%0.1f";

// -------------------------------------------------------------------------
// Utility functions

namespace utils
{

void draw_text_centered(ImDrawList* draw_list, const ImVec2& pos, ImU32 text_col, const char* text_begin, const char* text_end = nullptr)
{
    const ImVec2 text_size = ImGui::CalcTextSize(text_begin, text_end);
    const ImVec2 text_pos = {pos.x - (text_size.x / 2.0f), pos.y - (text_size.y / 2.0f) };

    draw_list->AddText(text_pos, text_col, text_begin, text_end);
}

inline ImVec2 rect_center(const ImVec2& topLeft, const ImVec2& botRight)
{
    return { (topLeft.x + botRight.x) / 2.0f, (topLeft.y + botRight.y) / 2.0f };
}

// via: https://stackoverflow.com/a/2412046/
int print_float_without_trailing_zeros(char* buffer, size_t buffer_size, float value)
{
    int count = snprintf(buffer, buffer_size, FLOAT_FMT, value);

    if(count > (int)buffer_size) {
        return count;
    }

    // Shift position, prior to '\0',
    count--;

    // Traverse from end to start, until not-zero, or (dot sign or comma) found
    while(buffer[count] == '0')
    {
        count--;

        if( (buffer[count] == '.') || (buffer[count] == ',') )
        {
            count--;
            break;
        }
    }

    buffer[count + 1] = '\0';
    return count + 1;
}

} // namespace utils

// -----------------------------------------------------------------------------

void ImGui_Taffy::node_draw_recursive(
    const taffy::LayoutTree& tree,
    const taffy::NodeId node,

    ImDrawList* draw_list,

    const ImVec2& origin,
    const taffy::Option<taffy::NodeId>& focused_node,

    const Node_Draw_Style* style
)
{
    // -------------------------------------------------------------------------

    // If style not specified - use default
    if(style == nullptr)
    {
        style = &DEFAULT_STYLE;
    }

    // -------------------------------------------------------------------------

    const taffy::Layout& layout = tree.impl_layout(node);

    // ---------------------------------------------------------------------
    // Extract node rect values

    const float left   = layout.location.x;
    const float top    = layout.location.y;

    const float width  = layout.size.width;
    const float height = layout.size.height;

    // ---------------------------------------------------------------------

    const bool is_focused = (focused_node.is_some() && focused_node.value() == node);

    const ImVec2 node_rect__top_left  = {origin.x + left,         origin.y + top};
    const ImVec2 node_rect__bot_right = {origin.x + left + width, origin.y + top + height};

    // Draw node rect
    draw_list->AddRect(
        node_rect__top_left,  // p_min
        node_rect__bot_right, // p_max
        (is_focused ? style->node_focused_color : style->node_nonfocused_color), // col
        0.0f, // rounding
        0,    // flags
        (is_focused ? style->node_focused_thickness : style->node_nonfocused_thickness) // thickness
    );

    if(is_focused)
    {
        // ... TODO: draw additional info
    }

    // Draw childs recursively
    const auto childs = tree.impl_children(node);
    for(const auto& child : childs)
    {
        node_draw_recursive(
            tree,
            child,

            draw_list,

            node_rect__top_left, // origin is 'parent TopLeft corner'
            focused_node,

            style
        );
    }
}
