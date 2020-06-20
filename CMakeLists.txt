cmake_minimum_required(VERSION 3.14)
project(MyGimp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/packages)

if ("${CMAKE_BUILD_TYPE}" STREQUAL Debug)
    if (CMAKE_COMPILER_IS_GNUCC)
        add_compile_options(-Wall -Wextra -W -g -D_DEBUG)
    endif (CMAKE_COMPILER_IS_GNUCC)
endif ()

if ("${CMAKE_BUILD_TYPE}" STREQUAL Release)
    if (CMAKE_COMPILER_IS_GNUCC)
        if (WIN32)
            add_link_options(-mwindows)
        endif (WIN32)
    endif (CMAKE_COMPILER_IS_GNUCC)
endif ()

set(MIMP_SRCS
    # Root
    src/Editor.cpp
    src/Editor.hpp
    src/ToolBox.cpp
    src/ToolBox.hpp
    src/Widgets/CanvasWidget.cpp
    src/Widgets/CanvasWidget.hpp
    src/Data/MouseClick.hpp
    src/Exceptions.hpp
    src/Utils.cpp
    src/Utils.hpp
    src/Image.cpp
    src/Image.hpp
    src/SelectedArea.cpp
    src/SelectedArea.hpp
    src/Enum.hpp
    src/Widgets/LayerWidget.cpp
    src/Widgets/LayerWidget.hpp
    src/Keys.cpp
    src/Keys.hpp
    src/ShortcutManager.cpp
    src/ShortcutManager.hpp
    src/Widgets/KeyWidget.cpp
    src/Widgets/KeyWidget.hpp
    src/Action.hpp

    # Misc data
    src/Data/Vector2.hpp
    src/Data/Color.hpp
    src/Data/Color.cpp

    # Network
    src/Network/SecuredSocket.cpp
    src/Network/SecuredSocket.hpp
    src/Network/Socket.cpp
    src/Network/Socket.hpp

    # Snapshot
    src/Snapshot/Snapshot.hpp
    src/Snapshot/FrameBufferSnapshot.cpp
    src/Snapshot/FrameBufferSnapshot.hpp

    # Layer manipulation
    src/Layer/Layer.cpp
    src/Layer/Layer.hpp
    src/Layer/FrameBuffer.cpp
    src/Layer/FrameBuffer.hpp
    src/Layer/LayerManager.cpp
    src/Layer/LayerManager.hpp

    # Tools
    src/Tools/Tool.hpp
    src/Tools/ToolFactory.cpp
    src/Tools/ToolFactory.hpp
    src/Tools/Pencil.cpp
    src/Tools/Pencil.hpp
    src/Tools/Fill.cpp
    src/Tools/Fill.hpp
    src/Tools/ColorPick.cpp
    src/Tools/ColorPick.hpp
    src/Tools/SelectionTool.cpp
    src/Tools/SelectionTool.hpp
    src/Tools/RectSelectTool.cpp
    src/Tools/RectSelectTool.hpp
    src/Tools/SelectByColorTool.cpp
    src/Tools/SelectByColorTool.hpp
    src/Tools/FillSelection.cpp
    src/Tools/FillSelection.hpp
    src/Tools/EllipseSelectionTool.cpp
    src/Tools/EllipseSelectionTool.hpp
    src/Tools/Eraser.cpp
    src/Tools/Eraser.hpp
    src/Tools/Move.cpp
    src/Tools/Move.hpp
    src/Tools/Text.cpp
    src/Tools/Text.hpp

    # Image Operations
    src/ImageOperations/ImageOperation.cpp
    src/ImageOperations/ImageOperation.hpp
    src/ImageOperations/ImageOperationFactory.cpp
    src/ImageOperations/ImageOperationFactory.hpp
    src/ImageOperations/Selection/FillSelectionOperation.cpp
    src/ImageOperations/Selection/FillSelectionOperation.hpp
    src/ImageOperations/Selection/SelectAllOperation.cpp
    src/ImageOperations/Selection/SelectAllOperation.hpp
    src/ImageOperations/Selection/UnselectOperation.cpp
    src/ImageOperations/Selection/UnselectOperation.hpp
    src/ImageOperations/Selection/InvertSelectionOperation.cpp
    src/ImageOperations/Selection/InvertSelectionOperation.hpp
    src/ImageOperations/Selection/DelSelectionOperation.cpp
    src/ImageOperations/Selection/DelSelectionOperation.hpp
    src/ImageOperations/Selection/ExpandSelection.cpp
    src/ImageOperations/Selection/ExpandSelection.hpp
    src/ImageOperations/Selection/ExpandMoreSelection.cpp
    src/ImageOperations/Selection/ExpandMoreSelection.hpp
    src/ImageOperations/Selection/OutlineMoreSelectionOperation.cpp
    src/ImageOperations/Selection/OutlineMoreSelectionOperation.hpp
    src/ImageOperations/Selection/ShrinkSelection.cpp
    src/ImageOperations/Selection/ShrinkSelection.hpp
    src/ImageOperations/Selection/ShrinkMoreSelection.cpp
    src/ImageOperations/Selection/ShrinkMoreSelection.hpp
    src/ImageOperations/Selection/OutlineSelectionOperation.cpp
    src/ImageOperations/Selection/OutlineSelectionOperation.hpp
    src/ImageOperations/Clipboard/PasteOperation.cpp
    src/ImageOperations/Clipboard/PasteOperation.hpp
    src/ImageOperations/Clipboard/CopyOperation.cpp
    src/ImageOperations/Clipboard/CopyOperation.hpp
    src/ImageOperations/Clipboard/CutOperation.cpp
    src/ImageOperations/Clipboard/CutOperation.hpp
    src/ImageOperations/Clipboard/CopyOperation.cpp
    src/ImageOperations/Clipboard/CopyOperation.hpp
    src/ImageOperations/Clipboard/CutOperation.cpp
    src/ImageOperations/Clipboard/CutOperation.hpp
    src/ImageOperations/Layer/MoveLeft.cpp
    src/ImageOperations/Layer/MoveLeft.hpp
    src/ImageOperations/Layer/MoveRight.cpp
    src/ImageOperations/Layer/MoveRight.hpp
    src/ImageOperations/Layer/MoveUp.cpp
    src/ImageOperations/Layer/MoveUp.hpp
    src/ImageOperations/Layer/MoveDown.cpp
    src/ImageOperations/Layer/MoveDown.hpp
    src/ImageOperations/Layer/RotateLeft90.cpp
    src/ImageOperations/Layer/RotateLeft90.hpp
    src/ImageOperations/Layer/RotateRight90.cpp
    src/ImageOperations/Layer/RotateRight90.hpp
    src/Keys.cpp
    src/Keys.hpp
    src/ShortcutManager.cpp
    src/ShortcutManager.hpp
    src/Snapshot/Snapshot.hpp
    src/Snapshot/FrameBufferSnapshot.cpp
    src/Snapshot/FrameBufferSnapshot.hpp
    src/Action.hpp
    src/ImageOperations/Redo.cpp
    src/ImageOperations/Redo.hpp
    src/ImageOperations/Undo.cpp
    src/ImageOperations/Undo.hpp
    src/Widgets/CheckBoardScrollablePanel.cpp
    src/Widgets/CheckBoardScrollablePanel.hpp
    src/ImageOperations/Layer/Rotate.cpp
    src/ImageOperations/Layer/Rotate.hpp
    src/ImageOperations/Layer/SetRotation.cpp
    src/ImageOperations/Layer/SetRotation.hpp
    src/ImageOperations/Grid/DrawGrid.cpp
    src/ImageOperations/Grid/DrawGrid.hpp
    src/ImageOperations/Grid/IncreaseGrid.cpp
    src/ImageOperations/Grid/IncreaseGrid.hpp
    src/ImageOperations/Grid/DecreaseGrid.cpp
    src/ImageOperations/Grid/DecreaseGrid.hpp
    src/ImageOperations/Effects.cpp
    src/ImageOperations/Effects.hpp
    src/ImageOperations/Effects/Light.cpp
    src/ImageOperations/Effects/Light.hpp
    src/ImageOperations/Effects/Effect.hpp
    src/ImageOperations/Effects/Saturation.cpp
    src/ImageOperations/Effects/Saturation.hpp
    src/ImageOperations/Effects/Symmetry.cpp
    src/ImageOperations/Effects/Symmetry.hpp
    src/Snapshot/LayerSnapshot.cpp
    src/Snapshot/LayerSnapshot.hpp
    src/Snapshot/SelectionSnapshot.cpp
    src/Snapshot/SelectionSnapshot.hpp
    src/Tools/PolygonSelection.cpp
    src/Tools/PolygonSelection.hpp
    src/Tools/Lasso.cpp
    src/Tools/Lasso.hpp
    src/Tools/Polygon.cpp
    src/Tools/Polygon.hpp
    src/Tools/Finger.cpp
    src/Tools/Finger.hpp
    src/Snapshot/LayerManagerSnapshot.cpp
    src/Snapshot/LayerManagerSnapshot.hpp)


find_library(PNG_LIBRARY png)

find_package(clip REQUIRED)
include_directories(${clip_INCLUDE_DIRS})

if (WIN32)
    add_executable(
        MyGimp
        src/main.cpp
        icon.rc
        ${MIMP_SRCS}
    )
else ()
    add_executable(
            MyGimp
            src/main.cpp
            ${MIMP_SRCS}
    )
endif()

if (WIN32)
    target_link_libraries(
        MyGimp
        tgui
        sfml-graphics
        sfml-window
        sfml-system
        pthread
        stdc++fs
        ssl
        ws2_32
        ${PNG_LIBRARY}
        ${clip_LIBRARIES}
    )
else ()
    target_link_libraries(
        MyGimp
        tgui
        sfml-graphics
        sfml-window
        sfml-system
        pthread
        stdc++fs
        ssl
        ${PNG_LIBRARY}
        xcb
        ${clip_LIBRARIES}
    )
endif ()

# --------------

add_compile_options(--coverage)

add_executable(
        MyGimp_test

        tst/main.cpp
        ${MIMP_SRCS}
        tst/Utils.cpp
        tst/CanvasWidget.cpp
        tst/Image.cpp
        tst/Exceptions.cpp
        tst/SelectedArea.cpp
        tst/ToolBox.cpp
        tst/LayerWidget.cpp
        tst/Keys.cpp
        tst/Data/Vector.cpp
        tst/Data/Color.cpp
        tst/Layer/Layer.cpp
        tst/Layer/LayerManager.cpp
        tst/Layer/FrameBuffer.cpp
        tst/Network/Socket.cpp
        tst/Network/SecuredSocket.cpp
        tst/Tools/Fill.cpp
        tst/Tools/ColorPick.cpp
        tst/Tools/FillSelection.cpp
        tst/Tools/Eraser.cpp
        tst/Tools/Pencil.cpp
        tst/Tools/RectSelectTool.cpp
        tst/Tools/SelectByColorTool.cpp
        tst/Tools/SelectionTool.cpp
        tst/Tools/Move.cpp
        tst/ImageOperations/ImageOperation.cpp
        tst/ImageOperations/ImageOperationFactory.cpp
        tst/ImageOperations/Selection/DelSelectOperation.cpp
        tst/ImageOperations/Selection/UnselectOperation.cpp
        tst/ImageOperations/Selection/SelectAllOperation.cpp
        tst/ImageOperations/Selection/InvertSelectionOperation.cpp
        tst/ImageOperations/Selection/ExpandSelection.cpp
        tst/ImageOperations/Selection/FillSelectionOperation.cpp
        tst/ImageOperations/Selection/ShrinkSelection.cpp
        tst/ImageOperations/Selection/ExpandMoreSelection.cpp
        tst/ImageOperations/Selection/ShrinkMoreSelection.cpp
        tst/ImageOperations/Selection/OutlineMoreSelectionOperation.cpp
        tst/ImageOperations/Selection/OutlineSelectionOperation.cpp
        tst/ImageOperations/Clipboard/CopyOperation.cpp
        tst/ImageOperations/Clipboard/CutOperation.cpp
        tst/ImageOperations/Layer/MoveDown.cpp
        tst/ImageOperations/Layer/MoveLeft.cpp
        tst/ImageOperations/Layer/MoveRight.cpp
        tst/ImageOperations/Layer/MoveUp.cpp
        tst/ImageOperations/Layer/RotateRight90.cpp tst/KeyWidget.cpp)

if (WIN32)
    target_link_libraries(
            MyGimp_test
            tgui
            sfml-graphics
            sfml-window
            sfml-system
            pthread
            stdc++fs
            ssl
            ws2_32
            gtest
            gcov
            ${PNG_LIBRARY}
            ${clip_LIBRARIES}
    )
else ()
    target_link_libraries(
            MyGimp_test
            tgui
            sfml-graphics
            sfml-window
            sfml-system
            pthread
            stdc++fs
            ssl
            gtest
            gcov
            ${PNG_LIBRARY}
            xcb
            ${clip_LIBRARIES}
    )
endif ()
