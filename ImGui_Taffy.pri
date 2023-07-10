# QMake project include file
#
# Example of usage
#
# Add into your *.pro project file the next line:
#
#   include(/path/to/imgui_taffy_cpp_inspect/ImGui_Taffy.pri)
#
# NOTE: content is based on ImGui_Taffy.cmake

INCLUDEPATH += \
    $$PWD/include/

HEADERS += \
    $$PWD/include/ImGui_Taffy/node_draw_recursive.hpp \
    $$PWD/include/ImGui_Taffy/show_descriptions.hpp \
    $$PWD/include/ImGui_Taffy/open_link_func.hpp \
    \
    $$PWD/include/ImGui_Taffy/utils/draw_text_segments.hpp \
    $$PWD/include/ImGui_Taffy/utils/HelpMarker.hpp \
    $$PWD/include/ImGui_Taffy/utils/description.hpp \
    $$PWD/include/ImGui_Taffy/utils/TypeDescription.hpp \
    \
    \
    $$PWD/include/ImGui_Taffy/types/common/Option.hpp \
    \
    $$PWD/include/ImGui_Taffy/types/shared/GridTrackVec_NonRepeatedTrackSizingFunction.hpp \
    \
    $$PWD/include/ImGui_Taffy/types/geometry/AbsoluteAxis.hpp \
    $$PWD/include/ImGui_Taffy/types/geometry/AbstractAxis.hpp \
    $$PWD/include/ImGui_Taffy/types/geometry/InBothAbsAxis.hpp \
    $$PWD/include/ImGui_Taffy/types/geometry/Line.hpp \
    $$PWD/include/ImGui_Taffy/types/geometry/MinMax.hpp \
    $$PWD/include/ImGui_Taffy/types/geometry/Point.hpp \
    $$PWD/include/ImGui_Taffy/types/geometry/Rect.hpp \
    $$PWD/include/ImGui_Taffy/types/geometry/Size.hpp \
    \
    $$PWD/include/ImGui_Taffy/types/style/alignment/AlignContent.hpp \
    $$PWD/include/ImGui_Taffy/types/style/alignment/AlignItems.hpp \
    $$PWD/include/ImGui_Taffy/types/style/alignment/AlignSelf.hpp \
    $$PWD/include/ImGui_Taffy/types/style/alignment/JustifyContent.hpp \
    $$PWD/include/ImGui_Taffy/types/style/alignment/JustifyItems.hpp \
    $$PWD/include/ImGui_Taffy/types/style/alignment/JustifySelf.hpp \
    \
    $$PWD/include/ImGui_Taffy/types/style/dimensions/AvailableSpace.hpp \
    $$PWD/include/ImGui_Taffy/types/style/dimensions/Dimension.hpp \
    $$PWD/include/ImGui_Taffy/types/style/dimensions/LengthPercentage.hpp \
    $$PWD/include/ImGui_Taffy/types/style/dimensions/LengthPercentageAuto.hpp \
    \
    $$PWD/include/ImGui_Taffy/types/style/flex/FlexDirection.hpp \
    $$PWD/include/ImGui_Taffy/types/style/flex/FlexWrap.hpp \
    \
    $$PWD/include/ImGui_Taffy/types/style/grid/GenericGridPlacement.hpp \
    $$PWD/include/ImGui_Taffy/types/style/grid/GridAutoFlow.hpp \
    $$PWD/include/ImGui_Taffy/types/style/grid/GridPlacement.hpp \
    $$PWD/include/ImGui_Taffy/types/style/grid/GridTrackRepetition.hpp \
    $$PWD/include/ImGui_Taffy/types/style/grid/MaxTrackSizingFunction.hpp \
    $$PWD/include/ImGui_Taffy/types/style/grid/MinTrackSizingFunction.hpp \
    $$PWD/include/ImGui_Taffy/types/style/grid/NonRepeatedTrackSizingFunction.hpp \
    $$PWD/include/ImGui_Taffy/types/style/grid/OriginZeroGridPlacement.hpp \
    $$PWD/include/ImGui_Taffy/types/style/grid/TrackSizingFunction.hpp \
    \
    $$PWD/include/ImGui_Taffy/types/style/mod/Display.hpp \
    $$PWD/include/ImGui_Taffy/types/style/mod/Overflow.hpp \
    $$PWD/include/ImGui_Taffy/types/style/mod/Position.hpp \
    $$PWD/include/ImGui_Taffy/types/style/mod/Style.hpp \
    \
    $$PWD/include/ImGui_Taffy/types/util/sys/GridTrackVec.hpp

SOURCES += \
    $$PWD/sources/imgui_taffy__node_draw_recursive.cpp \
    $$PWD/sources/imgui_taffy__show_descriptions.cpp \
    $$PWD/sources/imgui_taffy__open_link_func.cpp \
    \
    $$PWD/sources/imgui_taffy__utils__draw_text_segments.cpp \
    $$PWD/sources/imgui_taffy__utils__HelpMarker.cpp \
    $$PWD/sources/imgui_taffy__utils__description.cpp \
    \
    \
    $$PWD/sources/imgui_taffy__types__shared__GridTrackVec_NonRepeatedTrackSizingFunction.cpp \
    \
    $$PWD/sources/imgui_taffy__types__geometry__AbsoluteAxis.cpp \
    $$PWD/sources/imgui_taffy__types__geometry__AbstractAxis.cpp \
    \
    $$PWD/sources/imgui_taffy__types__style__alignment__AlignContent.cpp \
    $$PWD/sources/imgui_taffy__types__style__alignment__AlignItems.cpp \
    $$PWD/sources/imgui_taffy__types__style__alignment__AlignSelf.cpp \
    $$PWD/sources/imgui_taffy__types__style__alignment__JustifyContent.cpp \
    $$PWD/sources/imgui_taffy__types__style__alignment__JustifyItems.cpp \
    $$PWD/sources/imgui_taffy__types__style__alignment__JustifySelf.cpp \
    \
    $$PWD/sources/imgui_taffy__types__style__dimensions__AvailableSpace.cpp \
    $$PWD/sources/imgui_taffy__types__style__dimensions__Dimension.cpp \
    $$PWD/sources/imgui_taffy__types__style__dimensions__LengthPercentage.cpp \
    $$PWD/sources/imgui_taffy__types__style__dimensions__LengthPercentageAuto.cpp \
    \
    $$PWD/sources/imgui_taffy__types__style__flex__FlexDirection.cpp \
    $$PWD/sources/imgui_taffy__types__style__flex__FlexWrap.cpp \
    \
    $$PWD/sources/imgui_taffy__types__style__grid__GridAutoFlow.cpp \
    $$PWD/sources/imgui_taffy__types__style__grid__GridPlacement.cpp \
    $$PWD/sources/imgui_taffy__types__style__grid__GridTrackRepetition.cpp \
    $$PWD/sources/imgui_taffy__types__style__grid__MaxTrackSizingFunction.cpp \
    $$PWD/sources/imgui_taffy__types__style__grid__MinTrackSizingFunction.cpp \
    $$PWD/sources/imgui_taffy__types__style__grid__NonRepeatedTrackSizingFunction.cpp \
    $$PWD/sources/imgui_taffy__types__style__grid__OriginZeroGridPlacement.cpp \
    $$PWD/sources/imgui_taffy__types__style__grid__TrackSizingFunction.cpp \
    \
    $$PWD/sources/imgui_taffy__types__style__mod__Display.cpp \
    $$PWD/sources/imgui_taffy__types__style__mod__Overflow.cpp \
    $$PWD/sources/imgui_taffy__types__style__mod__Position.cpp \
    $$PWD/sources/imgui_taffy__types__style__mod__Style.cpp
