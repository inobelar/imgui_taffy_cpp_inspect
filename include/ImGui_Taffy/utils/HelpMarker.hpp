#pragma once

#include <functional> // for: std::function<Ret(Args...)>

namespace ImGui_Taffy {

void HelpMarker(bool is_interactive, const std::function<void()>& tooltip_content_func);

} // namespace ImGui_Taffy
