#pragma once

namespace ImGui_Taffy {

using open_link_fn_t = void (*) (const char* url);

void set_open_link_func(const open_link_fn_t callback);

open_link_fn_t get_open_link_func();

} // namespace ImGui_Taffy
