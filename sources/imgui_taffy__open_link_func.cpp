#include <ImGui_Taffy/open_link_func.hpp>

static ImGui_Taffy::open_link_fn_t open_link = nullptr;


void ImGui_Taffy::set_open_link_func(const open_link_fn_t callback)
{
    open_link = callback;
}

ImGui_Taffy::open_link_fn_t ImGui_Taffy::get_open_link_func()
{
    return open_link;
}
