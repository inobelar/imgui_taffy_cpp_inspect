#[[
    CMake project include file

    # Example of usage

    Add into your CMakeLists.txt the next lines:

    # --------------------------------------------------------------------------

    # Include 'ImGui_Taffy' file (to get variables)
    include("/path/to/imgui_taffy_cpp_inspect/ImGui_Taffy.cmake")

    add_executable( <YOUR_EXECUTABLE>
        # ...
        ${IMGUI_TAFFY_HEADERS} ${IMGUI_TAFFY_SOURCES}
    )

    # Add 'ImGui_Taffy' includes search path
    target_include_directories( <YOUR_EXECUTABLE> ${IMGUI_TAFFY_INCLUDE_DIRECTORIES} )

    # (Example) Add 'ImGui_Taffy' dependency libraries ('ImGui' and 'taffy_cpp' libraries)
    target_link_libraries( <YOUR_EXECUTABLE> imgui taffy_cpp )

    # --------------------------------------------------------------------------
]]

set(IMGUI_TAFFY_INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_LIST_DIR}/include/
)

set(IMGUI_TAFFY_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/node_draw_recursive.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/show_descriptions.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/open_link_func.hpp

    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/utils/draw_text_segments.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/utils/HelpMarker.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/utils/description.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/utils/TypeDescription.hpp

    # common -------------------------------------------------------------------

    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/types/common/Option.hpp

    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/types/shared/GridTrackVec_NonRepeatedTrackSizingFunction.hpp

    # geometry -----------------------------------------------------------------
    
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/types/geometry/AbsoluteAxis.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/types/geometry/AbstractAxis.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/types/geometry/InBothAbsAxis.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/types/geometry/Line.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/types/geometry/MinMax.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/types/geometry/Point.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/types/geometry/Rect.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/types/geometry/Size.hpp

    # style :: alignment -------------------------------------------------------

    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/types/style/alignment/AlignContent.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/types/style/alignment/AlignItems.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/types/style/alignment/AlignSelf.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/types/style/alignment/JustifyContent.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/types/style/alignment/JustifyItems.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/types/style/alignment/JustifySelf.hpp

    # style :: dimensions ------------------------------------------------------

    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/types/style/dimensions/AvailableSpace.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/types/style/dimensions/Dimension.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/types/style/dimensions/LengthPercentage.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/types/style/dimensions/LengthPercentageAuto.hpp

    # style :: flex ------------------------------------------------------------

    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/types/style/flex/FlexDirection.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/types/style/flex/FlexWrap.hpp

    # style :: grid ------------------------------------------------------------
    
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/types/style/grid/GenericGridPlacement.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/types/style/grid/GridAutoFlow.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/types/style/grid/GridPlacement.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/types/style/grid/GridTrackRepetition.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/types/style/grid/MaxTrackSizingFunction.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/types/style/grid/MinTrackSizingFunction.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/types/style/grid/NonRepeatedTrackSizingFunction.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/types/style/grid/OriginZeroGridPlacement.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/types/style/grid/TrackSizingFunction.hpp

    # style :: mod -------------------------------------------------------------

    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/types/style/mod/Display.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/types/style/mod/Overflow.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/types/style/mod/Position.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/types/style/mod/Style.hpp

    # util :: sys --------------------------------------------------------------

    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Taffy/types/util/sys/GridTrackVec.hpp
)

set(IMGUI_TAFFY_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_taffy__node_draw_recursive.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_taffy__show_descriptions.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_taffy__open_link_func.cpp
    
    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_taffy__utils__draw_text_segments.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_taffy__utils__HelpMarker.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_taffy__utils__description.cpp


    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_taffy__types__shared__GridTrackVec_NonRepeatedTrackSizingFunction.cpp

    # geometry -----------------------------------------------------------------

    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_taffy__types__geometry__AbsoluteAxis.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_taffy__types__geometry__AbstractAxis.cpp

    # style :: alignment -------------------------------------------------------

    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_taffy__types__style__alignment__AlignContent.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_taffy__types__style__alignment__AlignItems.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_taffy__types__style__alignment__AlignSelf.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_taffy__types__style__alignment__JustifyContent.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_taffy__types__style__alignment__JustifyItems.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_taffy__types__style__alignment__JustifySelf.cpp

    # style :: dimensions ------------------------------------------------------

    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_taffy__types__style__dimensions__AvailableSpace.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_taffy__types__style__dimensions__Dimension.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_taffy__types__style__dimensions__LengthPercentage.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_taffy__types__style__dimensions__LengthPercentageAuto.cpp

    # style :: flex ------------------------------------------------------------

    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_taffy__types__style__flex__FlexDirection.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_taffy__types__style__flex__FlexWrap.cpp

    # style :: grid ------------------------------------------------------------

    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_taffy__types__style__grid__GridAutoFlow.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_taffy__types__style__grid__GridPlacement.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_taffy__types__style__grid__GridTrackRepetition.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_taffy__types__style__grid__MaxTrackSizingFunction.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_taffy__types__style__grid__MinTrackSizingFunction.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_taffy__types__style__grid__NonRepeatedTrackSizingFunction.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_taffy__types__style__grid__OriginZeroGridPlacement.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_taffy__types__style__grid__TrackSizingFunction.cpp

    # style :: mod -------------------------------------------------------------

    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_taffy__types__style__mod__Display.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_taffy__types__style__mod__Overflow.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_taffy__types__style__mod__Position.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_taffy__types__style__mod__Style.cpp
)
