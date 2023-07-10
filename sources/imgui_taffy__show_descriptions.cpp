#include <ImGui_Taffy/show_descriptions.hpp>

bool show_descriptions = false;

void ImGui_Taffy::set_show_descriptions(bool show)
{
    show_descriptions = show;
}

bool ImGui_Taffy::is_show_descriptions()
{
    return show_descriptions;
}
