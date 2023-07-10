#include <ImGui_Taffy/types/style/grid/OriginZeroGridPlacement.hpp>

#include <ImGui_Taffy/types/style/grid/GenericGridPlacement.hpp>

#include <imgui.h>
#include <ImGui_Taffy/show_descriptions.hpp>
#include <ImGui_Taffy/utils/description.hpp>

namespace ImGui_Taffy {

bool edit_OriginZeroLine(
    taffy::OriginZeroLine& value,

    const TypeDescription& type_description = TypeDescription::Default()
)
{
    static const ImGui_Taffy::TypeDescription DEFAULT_TYPE_DESCRIPTION {
        "OriginZeroLine",
        [] {
            ImGui::TextUnformatted(
                "Represents a grid line position in \"OriginZero\" coordinates\n"
                "\n"
                "\"OriginZero\" coordinates are a normalized form:\n"
            );

            ImGui::Bullet();
            ImGui::SameLine();
            ImGui::TextUnformatted("The line at left hand (or top) edge of the explicit grid is line 0");

            ImGui::Bullet();
            ImGui::SameLine();
            ImGui::TextUnformatted("The next line to the right (or down) is 1, and so on");

            ImGui::Bullet();
            ImGui::SameLine();
            ImGui::TextUnformatted("The next line to the left (or up) is -1, and so on");
        },
        false
    };

    const bool show_descriptions = is_show_descriptions();

    bool modified = false;

    int16_t v = value.v0;
    if( ImGui::DragScalar("##origin_zero_line_value", ImGuiDataType_S16, &v) ) {
        value = taffy::OriginZeroLine(v);
        modified = true;
    }

    if(show_descriptions)
    {
        const auto description = description_or_default(type_description, DEFAULT_TYPE_DESCRIPTION);

        ImGui::SameLine();
        HelpMarker(description.type_description_interactive, [description]
        {
            description::TypeName(description.type_name);
            ImGui::NewLine();
            description.type_description_fn();
        });
    }

    return modified;
}

} // namespace ImGui_Taffy

static const ImGui_Taffy::TypeDescription DEFAULT_TYPE_DESCRIPTION {
    "OriginZeroGridPlacement",
    [] {
        ImGui::TextUnformatted(
            "A grid line placement using the normalized OriginZero coordinates to specify line positions."
        );
    },
    false
};

bool ImGui_Taffy::edit_OriginZeroGridPlacement(
    taffy::OriginZeroGridPlacement& value,

    const TypeDescription& type_description
)
{
    const auto description = description_or_default(type_description, DEFAULT_TYPE_DESCRIPTION);

    return edit_GenericGridPlacement_T<taffy::OriginZeroLine>(
        value,

        [] { return taffy::GenericGridPlacement<taffy::OriginZeroLine>::Auto(); },
        [] { return taffy::OriginZeroLine(0); },
        [] (taffy::OriginZeroLine& v) -> bool
        {
            return edit_OriginZeroLine(v);
        },

        description
    );
}
