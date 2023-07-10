#include <ImGui_Taffy/types/style/grid/GridAutoFlow.hpp>

#include <imgui.h>

#include <ImGui_Taffy/show_descriptions.hpp>
#include <ImGui_Taffy/utils/HelpMarker.hpp>
#include <ImGui_Taffy/utils/description.hpp>
#include <ImGui_Taffy/utils/draw_text_segments.hpp>

static constexpr taffy::GridAutoFlow::Type GRID_AUTO_FLOW_TYPES[]
{
    taffy::GridAutoFlow::Type::Row,
    taffy::GridAutoFlow::Type::Column,
    taffy::GridAutoFlow::Type::RowDense,
    taffy::GridAutoFlow::Type::ColumnDense
};

const char* GridAutoFlow_to_string(const taffy::GridAutoFlow::Type v)
{
    switch(v) {
    case taffy::GridAutoFlow::Type::Row         : return "Row";
    case taffy::GridAutoFlow::Type::Column      : return "Column";
    case taffy::GridAutoFlow::Type::RowDense    : return "RowDense";
    case taffy::GridAutoFlow::Type::ColumnDense : return "ColumnDense";

    default: return "Unknown";
    }
}

taffy::GridAutoFlow GridAutoFlow_from_type(const taffy::GridAutoFlow::Type v)
{
    switch(v) {
    case taffy::GridAutoFlow::Type::Row         : return taffy::GridAutoFlow::Row();
    case taffy::GridAutoFlow::Type::Column      : return taffy::GridAutoFlow::Column();
    case taffy::GridAutoFlow::Type::RowDense    : return taffy::GridAutoFlow::RowDense();
    case taffy::GridAutoFlow::Type::ColumnDense : return taffy::GridAutoFlow::ColumnDense();

    default: return taffy::GridAutoFlow::Default();
    }
}

void GridAutoFlow_show_description(const taffy::GridAutoFlow::Type v)
{
    switch(v) {
    case taffy::GridAutoFlow::Type::Row:
    {
        ImGui::TextUnformatted("Items are placed by filling each row in turn, adding new rows as necessary");
    } break;
    case taffy::GridAutoFlow::Type::Column:
    {
        ImGui::TextUnformatted("Items are placed by filling each column in turn, adding new columns as necessary.");
    } break;
    case taffy::GridAutoFlow::Type::RowDense:
    {
        static const ImGui_Taffy::TextSegment TEXT_SEGMENTS[]
        {
            {"Combines "},
            {"Row", ImGui_Taffy::description::CODE_INLINE_COLOR},
            {" with the dense packing algorithm."}
        };
        
        ImGui_Taffy::draw_text_segments(TEXT_SEGMENTS, false);
    } break;
    case taffy::GridAutoFlow::Type::ColumnDense:
    {
        static const ImGui_Taffy::TextSegment TEXT_SEGMENTS[]
        {
            {"Combines "},
            {"Column", ImGui_Taffy::description::CODE_INLINE_COLOR},
            {" with the dense packing algorithm."}
        };
        
        ImGui_Taffy::draw_text_segments(TEXT_SEGMENTS, false);
    } break;

    default:
    {
        ImGui::TextUnformatted("Unknown");
    } break;
    }
}

static const ImGui_Taffy::TypeDescription DEFAULT_TYPE_DESCRIPTION {
    "GridAutoFlow",
    [] {
        ImGui::TextUnformatted(
            "Controls whether grid items are placed row-wise or column-wise. And whether the sparse or dense packing algorithm is used.\n"
            "\n"
            "The \"dense\" packing algorithm attempts to fill in holes earlier in the grid, if smaller items come up later. This may cause items to appear out-of-order, when doing so would fill in holes left by larger items.\n"
            "\n"
        );
        
        ImGui_Taffy::description::Link("MDN", "https://developer.mozilla.org/en-US/docs/Web/CSS/grid-auto-flow");
    }, 
    true
};

bool ImGui_Taffy::edit_GridAutoFlow(
    taffy::GridAutoFlow& value,
    
    const TypeDescription& type_description
)
{
    const bool show_descriptions = is_show_descriptions();

    bool modified = false;

    ImGui::PushID(&value);
    {
        const char* combo_label = GridAutoFlow_to_string(value.type());
        if (ImGui::BeginCombo("##combo", combo_label))
        {
            for (const taffy::GridAutoFlow::Type grid_auto_flow_type_to_choose : GRID_AUTO_FLOW_TYPES)
            {
                const bool is_selected = (grid_auto_flow_type_to_choose == value.type());

                const char* selectable_label = GridAutoFlow_to_string(grid_auto_flow_type_to_choose);
                if (ImGui::Selectable(selectable_label, is_selected))
                {
                    value = GridAutoFlow_from_type(grid_auto_flow_type_to_choose);

                    modified = true;
                }

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected) {
                    ImGui::SetItemDefaultFocus();
                }

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [grid_auto_flow_type_to_choose] {
                        GridAutoFlow_show_description(grid_auto_flow_type_to_choose);
                    });
                }
            }

            ImGui::EndCombo();
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
    }
    ImGui::PopID();

    return modified;
}
