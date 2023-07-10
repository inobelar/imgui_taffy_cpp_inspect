#include <ImGui_Taffy/types/style/mod/Style.hpp>

// -----------------------------------------------------------------------------

#include <ImGui_Taffy/types/common/Option.hpp>

#include <ImGui_Taffy/types/geometry/Size.hpp>
#include <ImGui_Taffy/types/geometry/Line.hpp>
#include <ImGui_Taffy/types/geometry/Point.hpp>
#include <ImGui_Taffy/types/geometry/Rect.hpp>

#include <ImGui_Taffy/types/style/alignment/AlignItems.hpp>
#include <ImGui_Taffy/types/style/alignment/AlignSelf.hpp>

#include <ImGui_Taffy/types/style/alignment/AlignContent.hpp>
#include <ImGui_Taffy/types/style/alignment/JustifyContent.hpp>

#include <ImGui_Taffy/types/style/mod/Display.hpp>
#include <ImGui_Taffy/types/style/mod/Overflow.hpp>
#include <ImGui_Taffy/types/style/mod/Position.hpp>

#include <ImGui_Taffy/types/style/dimensions/LengthPercentage.hpp>
#include <ImGui_Taffy/types/style/dimensions/LengthPercentageAuto.hpp>
#include <ImGui_Taffy/types/style/dimensions/Dimension.hpp>

#include <ImGui_Taffy/types/style/flex/FlexDirection.hpp>
#include <ImGui_Taffy/types/style/flex/FlexWrap.hpp>

#include <ImGui_Taffy/types/style/grid/GridPlacement.hpp>
#include <ImGui_Taffy/types/shared/GridTrackVec_NonRepeatedTrackSizingFunction.hpp>
#include <ImGui_Taffy/types/style/grid/TrackSizingFunction.hpp>
#include <ImGui_Taffy/types/style/grid/GridAutoFlow.hpp>

#include <ImGui_Taffy/types/util/sys/GridTrackVec.hpp>

// -----------------------------------------------------------------------------

#include <imgui.h>

#include <ImGui_Taffy/show_descriptions.hpp>
#include <ImGui_Taffy/utils/HelpMarker.hpp>
#include <ImGui_Taffy/utils/description.hpp>
#include <ImGui_Taffy/utils/draw_text_segments.hpp>

namespace ImGui_Taffy {

bool edit_Option_float(taffy::Option<float>& value)
{
    return edit_Option_T<float>(
        value,
        [] { return taffy::Option<float>{0.0f}; },
        [](float& v) {
            return ImGui::DragFloat("##value", &v);
        }
    );
}

bool edit_Option_AlignItems(taffy::Option<taffy::AlignItems>& value)
{
    return edit_Option_T<taffy::AlignItems>(
        value,
        [] { return taffy::Option<taffy::AlignItems>{taffy::AlignItems::Start}; },
        [](taffy::AlignItems& v) {
            return edit_AlignItems(v);
        }
    );
}

bool edit_Option_AlignSelf(taffy::Option<taffy::AlignSelf>& value)
{
    return edit_Option_T<taffy::AlignSelf>(
        value,
        [] { return taffy::Option<taffy::AlignSelf>{taffy::AlignSelf::Start}; },
        [](taffy::AlignSelf& v) {
            return edit_AlignSelf(v);
        }
    );
}

bool edit_Option_AlignContent(taffy::Option<taffy::AlignContent>& value)
{
    return edit_Option_T<taffy::AlignContent>(
        value,
        [] { return taffy::Option<taffy::AlignContent>{taffy::AlignContent::Start}; },
        [](taffy::AlignContent& v) {
            return edit_AlignContent(v);
        }
    );
}

bool edit_Option_JustifyContent(taffy::Option<taffy::JustifyContent>& value)
{
    return edit_Option_T<taffy::JustifyContent>(
        value,
        [] { return taffy::Option<taffy::JustifyContent>{taffy::JustifyContent::Start}; },
        [](taffy::JustifyContent& v) {
            return edit_JustifyContent(v);
        }
    );
}



bool edit_Size_Dimension(taffy::Size<taffy::Dimension>& size)
{
    return edit_Size_T<taffy::Dimension>(
        size,
        [](taffy::Dimension& v) {
            return edit_Dimension(v);
        },
        
        TypeDescription::NameOnly("Size<Dimension>")
    );
}

bool edit_Size_LengthPercentage(taffy::Size<taffy::LengthPercentage>& size)
{
    return edit_Size_T<taffy::LengthPercentage>(
        size,
        [](taffy::LengthPercentage& v) {
            return edit_LengthPercentage(v);
        },
        
        TypeDescription::NameOnly("Size<LengthPercentage>")
    );
}

bool edit_Line_GridPlacement(taffy::Line<taffy::GridPlacement>& line)
{
    return edit_Line_T<taffy::GridPlacement>(
        line,
        [](taffy::GridPlacement& v) {
            return edit_GridPlacement(v);
        },
        
        TypeDescription::NameOnly("Line<GridPlacement>")
    );
}

bool edit_Point_Overflow(taffy::Point<taffy::Overflow>& point)
{
    return edit_Point_T<taffy::Overflow>(
        point,
        [](taffy::Overflow& v) {
            return edit_Overflow(v);
        },
        
        TypeDescription::NameOnly("Point<Overflow>")
    );
}

bool edit_Rect_LengthPercentage(taffy::Rect<taffy::LengthPercentage>& rect)
{
    return edit_Rect_T<taffy::LengthPercentage>(
        rect,
        [](taffy::LengthPercentage& v) {
            return edit_LengthPercentage(v);
        },
        
        TypeDescription::NameOnly("Rect<LengthPercentage>")
    );
}

bool edit_Rect_LengthPercentageAuto(taffy::Rect<taffy::LengthPercentageAuto>& rect)
{
    return edit_Rect_T<taffy::LengthPercentageAuto>(
        rect,
        [](taffy::LengthPercentageAuto& v) {
            return edit_LengthPercentageAuto(v);
        },
        
        TypeDescription::NameOnly("Rect<LengthPercentageAuto>")
    );
}



bool edit_GridTrackVec_TrackSizingFunction(taffy::GridTrackVec<taffy::TrackSizingFunction>& vec)
{
    return edit_GridTrackVec_T<taffy::TrackSizingFunction>(
        vec,
        [] { return taffy::TrackSizingFunction::AUTO(); },
        [](taffy::TrackSizingFunction& item) {
            return edit_TrackSizingFunction(item);
        }
    );
}

} // namespace ImGui_Taffy

// -----------------------------------------------------------------------------

static const ImGui_Taffy::TypeDescription DEFAULT_TYPE_DESCRIPTION {
    "Style",
    [] {
        ImGui::TextUnformatted(
            "The flexbox layout information for a single node.\n"
            "\n"
            "The most important idea in flexbox is the notion of a \"main\" and \"cross\" axis, which are always perpendicular to each other.\n"
        );
        
        {
            static const ImGui_Taffy::TextSegment TEXT_SEGMENTS[]
            {
                {"The orientation of these axes are controlled via the "},
                {"FlexDirection", ImGui_Taffy::description::CODE_INLINE_COLOR},
                {" field of this struct."}
            };
            ImGui_Taffy::draw_text_segments(TEXT_SEGMENTS, false);
            ImGui::NewLine();
        }
        
        ImGui::NewLine();
        
        {
            static const ImGui_Taffy::TextSegment TEXT_SEGMENTS[]
            {
                {"This struct follows the "},
                {
                    "CSS equivalent",
                    ImGui_Taffy::description::LINK_COLOR, false,
                    "https://developer.mozilla.org/en-US/docs/Web/CSS/CSS_Flexible_Box_Layout/Basic_Concepts_of_Flexbox"
                },
                {" directly; information about the behavior on the web should transfer directly."}
            };
            ImGui_Taffy::draw_text_segments(TEXT_SEGMENTS, false);
            ImGui::NewLine();
        }
        
        ImGui::NewLine();
        
        {
            static const ImGui_Taffy::TextSegment TEXT_SEGMENTS[]
            {
                {"Detailed information about the exact behavior of each of these fields can be found on "},
                {
                    "MDN",
                    ImGui_Taffy::description::LINK_COLOR, false,
                    "https://developer.mozilla.org/en-US/docs/Web/CSS"
                },
                {" by searching for the field name."}
            };
            ImGui_Taffy::draw_text_segments(TEXT_SEGMENTS, false);
            ImGui::NewLine();
        }
        
        {
            static const ImGui_Taffy::TextSegment TEXT_SEGMENTS[]
            {
                {"The distinction between margin, padding and border is explained well in this "},
                {
                    "introduction to the box model",
                    ImGui_Taffy::description::LINK_COLOR, false,
                    "https://developer.mozilla.org/en-US/docs/Web/CSS/CSS_Box_Model/Introduction_to_the_CSS_box_model"
                },
                {"."}
            };
            ImGui_Taffy::draw_text_segments(TEXT_SEGMENTS, false);
            ImGui::NewLine();
        }
        
        ImGui::NewLine();

        ImGui::TextUnformatted("If the behavior does not match the flexbox layout algorithm on the web, please file a bug!");
    },
    true
};

bool ImGui_Taffy::edit_Style(
    taffy::Style& style,
    
    const TypeDescription& type_description
)
{
    const bool show_descriptions = is_show_descriptions();

    bool modified = false;

    ImGui::PushID(&style);
    {
        constexpr ImGuiTableFlags TABLE_FLAGS =
            ImGuiTableFlags_Resizable      |
            ImGuiTableFlags_BordersInnerV  |
          //ImGuiTableFlags_SizingFixedFit |
            ImGuiTableFlags_NoSavedSettings;
        constexpr char TABLE_ID[] = "taffy_style_table";

        const ImVec2 table_size =
            show_descriptions ?
                ImVec2{ ImGui::GetContentRegionAvail().x-30.0f, 0.0f } // Extra offset for `HelpMarker`
            :
                ImVec2{ 0.0f, 0.0f };

        // display
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS, table_size) )
        {
            ImGui::TableNextColumn();
            ImGui::TextUnformatted("Display");

            if(show_descriptions)
            {
                ImGui::SameLine();
                HelpMarker(false, [] {
                    ImGui::TextUnformatted("What layout strategy should be used?");
                });
            }

            ImGui::TableNextColumn();
            if( edit_Display(style.display) ) {
                modified = true;
            }

            ImGui::EndTable();
        }

        // In such uncommon case (multiple tables act as single one), we need
        // to display 'HelpMarker' properly (in top-right corner) - so we need
        // to show it after 'first' table.
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

        ImGui::SeparatorText("Overflow properties");
        {
            // overflow
            if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS, table_size) )
            {
                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Overflow");

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [] {
                        ImGui::TextUnformatted("How children overflowing their container should affect layout");
                    });
                }

                ImGui::TableNextColumn();
                if( edit_Point_Overflow(style.overflow) ) {
                    modified = true;
                }

                ImGui::EndTable();
            }

            // scrollbar_width
            if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS, table_size) )
            {
                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Scrollbar width");

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, []
                    {
                        static const TextSegment TEXT_SEGMENTS[]
                        {
                            {"How much space (in points) should be reserved for the scrollbars of "},
                            {"Overflow::Scroll", ImGui_Taffy::description::CODE_INLINE_COLOR},
                            {" and "},
                            {"Overflow::Auto", ImGui_Taffy::description::CODE_INLINE_COLOR},
                            {" nodes."}
                        };
                        ImGui_Taffy::draw_text_segments(TEXT_SEGMENTS, false);
                    });
                }

                ImGui::TableNextColumn();
                if( ImGui::DragFloat("##scrollbar_width", &style.scrollbar_width) ) {
                    modified = true;
                }

                ImGui::EndTable();
            }
        }

        ImGui::SeparatorText("Position properties");
        {
            // overflow
            if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS, table_size) )
            {
                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Position");

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, []
                    {
                        static const TextSegment TEXT_SEGMENTS[]
                        {
                            {"What should the "},
                            {"position", ImGui_Taffy::description::CODE_INLINE_COLOR},
                            {" value of this struct use as a base offset?"}
                        };
                        ImGui_Taffy::draw_text_segments(TEXT_SEGMENTS, false);
                    });
                }

                ImGui::TableNextColumn();
                if( edit_Position(style.position) ) {
                    modified = true;
                }

                ImGui::EndTable();
            }

            // inset
            if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS, table_size) )
            {
                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Inset");

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [] {
                        ImGui::TextUnformatted("How should the position of this element be tweaked relative to the layout defined?");
                    });
                }

                ImGui::TableNextColumn();
                if( edit_Rect_LengthPercentageAuto(style.inset) ) {
                    modified = true;
                }

                ImGui::EndTable();
            }
        }

        ImGui::SeparatorText("Size properties");
        {
            // size
            if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS, table_size) )
            {
                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Size");

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [] {
                        ImGui::TextUnformatted("Sets the initial size of the item");
                    });
                }

                ImGui::TableNextColumn();
                if( edit_Size_Dimension(style.size) ) {
                    modified = true;
                }

                ImGui::EndTable();
            }

            // min_size
            if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS, table_size) )
            {
                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Min size");

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [] {
                        ImGui::TextUnformatted("Controls the minimum size of the item");
                    });
                }

                ImGui::TableNextColumn();
                if( edit_Size_Dimension(style.min_size) ) {
                    modified = true;
                }

                ImGui::EndTable();
            }

            // max_size
            if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS, table_size) )
            {
                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Max size");

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [] {
                        ImGui::TextUnformatted("Controls the maximum size of the item");
                    });
                }

                ImGui::TableNextColumn();
                if( edit_Size_Dimension(style.max_size) ) {
                    modified = true;
                }

                ImGui::EndTable();
            }

            // aspect_ratio
            if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS, table_size) )
            {
                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Aspect ratio");

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, []
                    {
                        ImGui::TextUnformatted(
                            "Sets the preferred aspect ratio for the item\n"
                            "\n"
                            "The ratio is calculated as width divided by height."
                        );
                    });
                }

                ImGui::TableNextColumn();
                if( edit_Option_float(style.aspect_ratio) ) {
                    modified = true;
                }

                ImGui::EndTable();
            }
        }

        ImGui::SeparatorText("Spacing properties");
        {
            // margin
            if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS, table_size) )
            {
                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Margin");

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [] {
                        ImGui::TextUnformatted("How large should the margin be on each side?");
                    });
                }

                ImGui::TableNextColumn();
                if( edit_Rect_LengthPercentageAuto(style.margin) ) {
                    modified = true;
                }

                ImGui::EndTable();
            }

            // padding
            if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS, table_size) )
            {
                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Padding");

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [] {
                        ImGui::TextUnformatted("How large should the padding be on each side?");
                    });
                }

                ImGui::TableNextColumn();
                if( edit_Rect_LengthPercentage(style.padding) ) {
                    modified = true;
                }

                ImGui::EndTable();
            }

            // border
            if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS, table_size) )
            {
                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Border");

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [] {
                        ImGui::TextUnformatted("How large should the border be on each side?");
                    });
                }

                ImGui::TableNextColumn();
                if( edit_Rect_LengthPercentage(style.border) ) {
                    modified = true;
                }

                ImGui::EndTable();
            }
        }

        #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
        ImGui::SeparatorText("Alignment properties");
        {
            // align_items
            #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
            if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS, table_size) )
            {
                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Align items");

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [] {
                        ImGui::TextUnformatted("How this node's children aligned in the cross/block axis?");
                    });
                }

                ImGui::TableNextColumn();
                if( edit_Option_AlignItems(style.align_items) ) {
                    modified = true;
                }

                ImGui::EndTable();
            }
            #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID

            // align_self
            #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
            if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS, table_size) )
            {
                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Align self");

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, []
                    {
                        ImGui::TextUnformatted("How this node should be aligned in the cross/block axis");
                        
                        static const TextSegment TEXT_SEGMENTS[]
                        {
                            {"Falls back to the parents "},
                            {"AlignItems", ImGui_Taffy::description::CODE_INLINE_COLOR},
                            {" if not set"}
                        };
                        ImGui_Taffy::draw_text_segments(TEXT_SEGMENTS, false);
                    });
                }

                ImGui::TableNextColumn();
                if( edit_Option_AlignSelf(style.align_self) ) {
                    modified = true;
                }

                ImGui::EndTable();
            }
            #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID

            // justify_items
            #if defined(TAFFY_FEATURE_GRID)
            if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS, table_size) )
            {
                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Justify items");

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [] {
                        ImGui::TextUnformatted("How this node's children should be aligned in the inline axis");
                    });
                }

                ImGui::TableNextColumn();
                if( edit_Option_AlignItems(style.justify_items) ) {
                    modified = true;
                }

                ImGui::EndTable();
            }
            #endif // TAFFY_FEATURE_GRID

            // justify_self
            #if defined(TAFFY_FEATURE_GRID)
            if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS, table_size) )
            {
                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Justify self");

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, []
                    {
                        ImGui::TextUnformatted("How this node should be aligned in the inline axis");
                        
                        static const TextSegment TEXT_SEGMENTS[]
                        {
                            {"Falls back to the parents "},
                            {"JustifyItems", ImGui_Taffy::description::CODE_INLINE_COLOR},
                            {" if not set"}
                        };
                        ImGui_Taffy::draw_text_segments(TEXT_SEGMENTS, false);
                    });
                }

                ImGui::TableNextColumn();
                if( edit_Option_AlignSelf(style.justify_self) ) {
                    modified = true;
                }

                ImGui::EndTable();
            }
            #endif // TAFFY_FEATURE_GRID

            // align_content
            #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
            if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS, table_size) )
            {
                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Align content");

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [] {
                        ImGui::TextUnformatted("How should content contained within this item be aligned in the cross/block axis");
                    });
                }

                ImGui::TableNextColumn();
                if( edit_Option_AlignContent(style.align_content) ) {
                    modified = true;
                }

                ImGui::EndTable();
            }
            #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID

            // justify_content
            #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
            if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS, table_size) )
            {
                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Justify content");

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [] {
                        ImGui::TextUnformatted("How should contained within this item be aligned in the main/inline axis");
                    });
                }

                ImGui::TableNextColumn();
                if( edit_Option_JustifyContent(style.justify_content) ) {
                    modified = true;
                }

                ImGui::EndTable();
            }
            #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID

            // gap
            #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
            if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS, table_size) )
            {
                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Gap");

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [] {
                        ImGui::TextUnformatted("How large should the gaps between items in a grid or flex container be?");
                    });
                }

                ImGui::TableNextColumn();
                if( edit_Size_LengthPercentage(style.gap) ) {
                    modified = true;
                }

                ImGui::EndTable();
            }
            #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID
        }
        #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID

        #if defined(TAFFY_FEATURE_FLEXBOX)
        ImGui::SeparatorText("Flexbox properties");
        {
            // flex_direction
            #if defined(TAFFY_FEATURE_FLEXBOX)
            if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS, table_size) )
            {
                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Flex direction");

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [] {
                        ImGui::TextUnformatted("Which direction does the main axis flow in?");
                    });
                }

                ImGui::TableNextColumn();
                if( edit_FlexDirection(style.flex_direction) ) {
                    modified = true;
                }

                ImGui::EndTable();
            }
            #endif // TAFFY_FEATURE_FLEXBOX

            // flex_wrap
            #if defined(TAFFY_FEATURE_FLEXBOX)
            if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS, table_size) )
            {
                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Flex wrap");

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [] {
                        ImGui::TextUnformatted("Should elements wrap, or stay in a single line?");
                    });
                }

                ImGui::TableNextColumn();
                if( edit_FlexWrap(style.flex_wrap) ) {
                    modified = true;
                }

                ImGui::EndTable();
            }
            #endif // TAFFY_FEATURE_FLEXBOX

            // flex_basis
            #if defined(TAFFY_FEATURE_FLEXBOX)
            if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS, table_size) )
            {
                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Flex basis");

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [] {
                        ImGui::TextUnformatted("Sets the initial main axis size of the item");
                    });
                }

                ImGui::TableNextColumn();
                if( edit_Dimension(style.flex_basis) ) {
                    modified = true;
                }

                ImGui::EndTable();
            }
            #endif // TAFFY_FEATURE_FLEXBOX

            // flex_grow
            #if defined(TAFFY_FEATURE_FLEXBOX)
            if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS, table_size) )
            {
                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Flex grow");

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, []
                    {
                        ImGui::TextUnformatted(
                            "The relative rate at which this item grows when it is expanding to fill space\n"
                            "\n"
                            "0.0 is the default value, and this value must be positive."
                        );
                    });
                }

                ImGui::TableNextColumn();
                if( ImGui::DragFloat("##flex_grow", &style.flex_grow) ) {
                    modified = true;
                }

                ImGui::EndTable();
            }
            #endif // TAFFY_FEATURE_FLEXBOX

            // flex_shrink
            #if defined(TAFFY_FEATURE_FLEXBOX)
            if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS, table_size) )
            {
                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Flex shrink");

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, []
                    {
                        ImGui::TextUnformatted(
                            "The relative rate at which this item shrinks when it is contracting to fit into space\n"
                            "\n"
                            "1.0 is the default value, and this value must be positive."
                        );
                    });
                }

                ImGui::TableNextColumn();
                if( ImGui::DragFloat("##flex_shrink", &style.flex_shrink) ) {
                    modified = true;
                }

                ImGui::EndTable();
            }
            #endif // TAFFY_FEATURE_FLEXBOX
        }
        #endif // TAFFY_FEATURE_FLEXBOX

        #if defined(TAFFY_FEATURE_GRID)
        ImGui::SeparatorText("Grid container properties");
        {
            // grid_template_rows
            #if defined(TAFFY_FEATURE_GRID)
            if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS, table_size) )
            {
                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Grid template rows");

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [] {
                        ImGui::TextUnformatted("Defines the track sizing functions (widths) of the grid rows");
                    });
                }

                ImGui::TableNextColumn();
                if( edit_GridTrackVec_TrackSizingFunction(style.grid_template_rows) ) {
                    modified = true;
                }

                ImGui::EndTable();
            }
            #endif // TAFFY_FEATURE_GRID

            // grid_template_columns
            #if defined(TAFFY_FEATURE_GRID)
            if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS, table_size) )
            {
                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Grid template columns");

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [] {
                        ImGui::TextUnformatted("Defines the track sizing functions (heights) of the grid columns");
                    });
                }

                ImGui::TableNextColumn();
                if( edit_GridTrackVec_TrackSizingFunction(style.grid_template_columns) ) {
                    modified = true;
                }

                ImGui::EndTable();
            }
            #endif // TAFFY_FEATURE_GRID

            // grid_auto_rows
            #if defined(TAFFY_FEATURE_GRID)
            if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS, table_size) )
            {
                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Grid auto rows");

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [] {
                        ImGui::TextUnformatted("Defines the size of implicitly created rows");
                    });
                }

                ImGui::TableNextColumn();
                if( edit_GridTrackVec_NonRepeatedTrackSizingFunction(style.grid_auto_rows) ) {
                    modified = true;
                }

                ImGui::EndTable();
            }
            #endif // TAFFY_FEATURE_GRID

            // grid_auto_columns
            #if defined(TAFFY_FEATURE_GRID)
            if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS, table_size) )
            {
                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Grid auto columns");

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [] {
                        ImGui::TextUnformatted("Defined the size of implicitly created columns");
                    });
                }

                ImGui::TableNextColumn();
                if( edit_GridTrackVec_NonRepeatedTrackSizingFunction(style.grid_auto_columns) ) {
                    modified = true;
                }

                ImGui::EndTable();
            }
            #endif // TAFFY_FEATURE_GRID

            // grid_auto_flow
            #if defined(TAFFY_FEATURE_GRID)
            if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS, table_size) )
            {
                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Grid auto flow");

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [] {
                        ImGui::TextUnformatted("Controls how items get placed into the grid for auto-placed items");
                    });
                }

                ImGui::TableNextColumn();
                if( edit_GridAutoFlow(style.grid_auto_flow) ) {
                    modified = true;
                }

                ImGui::EndTable();
            }
            #endif // TAFFY_FEATURE_GRID
        }
        #endif // TAFFY_FEATURE_GRID

        #if defined(TAFFY_FEATURE_GRID)
        ImGui::SeparatorText("Grid child properties");
        {
            // grid_row
            #if defined(TAFFY_FEATURE_GRID)
            if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS, table_size) )
            {
                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Grid row");

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [] {
                        ImGui::TextUnformatted("Defines which row in the grid the item should start and end at");
                    });
                }

                ImGui::TableNextColumn();
                if( edit_Line_GridPlacement(style.grid_row) ) {
                    modified = true;
                }

                ImGui::EndTable();
            }
            #endif // TAFFY_FEATURE_GRID

            // grid_column
            #if defined(TAFFY_FEATURE_GRID)
            if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS, table_size) )
            {
                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Grid column");

                if(show_descriptions)
                {
                    ImGui::SameLine();
                    HelpMarker(false, [] {
                        ImGui::TextUnformatted("Defines which column in the grid the item should start and end at");
                    });
                }

                ImGui::TableNextColumn();
                if( edit_Line_GridPlacement(style.grid_column) ) {
                    modified = true;
                }

                ImGui::EndTable();
            }
            #endif // TAFFY_FEATURE_GRID
        }
        #endif // TAFFY_FEATURE_GRID
    }
    ImGui::PopID();

    return modified;
}
