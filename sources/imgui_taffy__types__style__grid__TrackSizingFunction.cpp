#include <ImGui_Taffy/types/style/grid/TrackSizingFunction.hpp>

#include <imgui.h>

#include <ImGui_Taffy/types/style/grid/NonRepeatedTrackSizingFunction.hpp>
#include <ImGui_Taffy/types/style/grid/GridTrackRepetition.hpp>
#include <ImGui_Taffy/types/shared/GridTrackVec_NonRepeatedTrackSizingFunction.hpp>

#include <ImGui_Taffy/show_descriptions.hpp>
#include <ImGui_Taffy/utils/HelpMarker.hpp>
#include <ImGui_Taffy/utils/description.hpp>
#include <ImGui_Taffy/utils/draw_text_segments.hpp>

static constexpr taffy::TrackSizingFunction::Type TRACK_SIZING_FUNCTION_TYPES[]
{
    taffy::TrackSizingFunction::Type::Single,
    taffy::TrackSizingFunction::Type::Repeat
};

const char* TrackSizingFunction_to_string(const taffy::TrackSizingFunction::Type v)
{
    switch(v) {
    case taffy::TrackSizingFunction::Type::Single : return "Single";
    case taffy::TrackSizingFunction::Type::Repeat : return "Repeat";

    default: return "Unknown";
    }
}

taffy::TrackSizingFunction TrackSizingFunction_from_type(const taffy::TrackSizingFunction::Type v)
{
    switch(v) {
    case taffy::TrackSizingFunction::Type::Single : return taffy::TrackSizingFunction::Single(taffy::NonRepeatedTrackSizingFunction::AUTO());
    case taffy::TrackSizingFunction::Type::Repeat : return taffy::TrackSizingFunction::Repeat(taffy::GridTrackRepetition::AutoFill(), {});
    default: return taffy::TrackSizingFunction::Single(taffy::NonRepeatedTrackSizingFunction::AUTO());
    }
}

void TrackSizingFunction_show_description(const taffy::TrackSizingFunction::Type v)
{
    switch(v) {
    case taffy::TrackSizingFunction::Type::Single:
    {
        ImGui::TextUnformatted("A single non-repeated track");
    } break;
    case taffy::TrackSizingFunction::Type::Repeat:
    {
        ImGui::TextUnformatted(
            "Automatically generate grid tracks to fit the available space using the specified definite track lengths\n"
            "Only valid if every track in template (not just the repitition) has a fixed size."
        );
    } break;

    default:
    {
        ImGui::TextUnformatted("Unknown");
    } break;
    }
}

static const ImGui_Taffy::TypeDescription DEFAULT_TYPE_DESCRIPTION {
    "TrackSizingFunction",
    [] {
        ImGui::TextUnformatted("The sizing function for a grid track (row/column)");
        
        {
            static const ImGui_Taffy::TextSegment TEXT_SEGMENTS[]
            {
                {"See "},
                {
                    "https://developer.mozilla.org/en-US/docs/Web/CSS/grid-template-columns", 
                    ImGui_Taffy::description::LINK_COLOR, false,
                    "https://developer.mozilla.org/en-US/docs/Web/CSS/grid-template-columns"
                }
            };
            ImGui_Taffy::draw_text_segments(TEXT_SEGMENTS, false);
        }
    },
    true
};

bool ImGui_Taffy::edit_TrackSizingFunction(
    taffy::TrackSizingFunction& value,
    
    const TypeDescription& type_description
)
{
    const bool show_descriptions = is_show_descriptions();

    bool modified = false;

    ImGui::PushID(&value);
    {
        constexpr ImGuiComboFlags COMBO_FLAGS = ImGuiComboFlags_NoPreview;
        if (ImGui::BeginCombo("##combo", nullptr, COMBO_FLAGS))
        {
            for (const taffy::TrackSizingFunction::Type tsf_type_to_choose : TRACK_SIZING_FUNCTION_TYPES)
            {
                const bool is_selected = (tsf_type_to_choose == value.type());

                const char* selectable_label = TrackSizingFunction_to_string(tsf_type_to_choose);
                if (ImGui::Selectable(selectable_label, is_selected))
                {
                    value = TrackSizingFunction_from_type(tsf_type_to_choose);

                    modified = true;
                }

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected) {
                    ImGui::SetItemDefaultFocus();
                }

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [tsf_type_to_choose] {
                        TrackSizingFunction_show_description(tsf_type_to_choose);
                    });
                }
            }

            ImGui::EndCombo();
        }

        ImGui::SameLine();

        switch(value.type())
        {
        case taffy::TrackSizingFunction::Type::Single:
        {
            ImGui::TextUnformatted("Single");
            ImGui::SameLine();
            auto v = value.single_func();
            if( edit_NonRepeatedTrackSizingFunction(v) ) {
                value = taffy::TrackSizingFunction::Single(v);
                modified = true;
            }
        } break;
        case taffy::TrackSizingFunction::Type::Repeat:
        {
            ImGui::TextUnformatted("Repeat");

            constexpr ImGuiTableFlags TABLE_FLAGS =
                ImGuiTableFlags_Resizable      |
                ImGuiTableFlags_BordersInnerV  |
              //ImGuiTableFlags_SizingFixedFit |
                ImGuiTableFlags_NoSavedSettings;
            constexpr char TABLE_ID[] = "taffy_track_sizing_func__repeat__table";

            if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
            {
                // Table columns specification, needed to set 'fixed' & 'stretch' flags
                ImGui::TableSetupColumn("Name",  ImGuiTableColumnFlags_WidthFixed);
                ImGui::TableSetupColumn("Value", ImGuiTableColumnFlags_WidthStretch);
                //ImGui::TableHeadersRow(); // <-- commented to not show table header

                // -----------------------------------------------------------------

                {
                    ImGui::TableNextColumn();
                    ImGui::TextUnformatted("repetition");

                    ImGui::TableNextColumn();
                    auto v = value.repeat_repetition();
                    if( edit_GridTrackRepetition(v) ) {
                        value = taffy::TrackSizingFunction::Repeat(v, value.repeat_funcs());
                        modified = true;
                    }
                }

                {
                    ImGui::TableNextColumn();
                    ImGui::TextUnformatted("repeat_funcs");

                    ImGui::TableNextColumn();
                    auto v = value.repeat_funcs();
                    if( edit_GridTrackVec_NonRepeatedTrackSizingFunction(v) ) {
                        value = taffy::TrackSizingFunction::Repeat(value.repeat_repetition(), v);
                        modified = true;
                    }
                }

                ImGui::EndTable();
            }
        } break;
        default: {
            ImGui::TextUnformatted("Unknown");
        } break;
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
