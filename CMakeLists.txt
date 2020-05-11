cmake_minimum_required(VERSION 3.14)
project(MyGimp)

set(CMAKE_CXX_STANDARD 17)

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
    src/Layer/Layer.cpp
    src/Layer/Layer.hpp
    src/Data/Vector2.hpp
    src/Data/Color.hpp
    src/Data/Color.cpp
    src/Layer/FrameBuffer.cpp
    src/Layer/FrameBuffer.hpp
    src/Layer/LayerManager.cpp
    src/Layer/LayerManager.hpp
    src/Tools/Tool.hpp
    src/Editor.cpp
    src/Editor.hpp
    src/ToolBox.cpp
    src/ToolBox.hpp
    src/CanvasWidget.cpp
    src/CanvasWidget.hpp
    src/Data/MouseClick.hpp
    src/Tools/ToolFactory.cpp
    src/Tools/ToolFactory.hpp
    src/Exceptions.hpp
    src/Tools/Pencil.cpp
    src/Tools/Pencil.hpp
    src/Utils.cpp
    src/Utils.hpp
    src/Tools/Fill.cpp
    src/Tools/Fill.hpp
    src/Image.cpp
    src/Image.hpp
    src/SelectedArea.cpp
    src/SelectedArea.hpp
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
    src/Tools/ElipseSelectionTool.cpp
    src/Tools/ElipseSelectionTool.hpp
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
    src/Tools/Eraser.cpp
    src/Tools/Eraser.hpp
    src/Enum.hpp
    src/Network/SecuredSocket.cpp
    src/Network/SecuredSocket.hpp
    src/Network/Socket.cpp
    src/Network/Socket.hpp
    src/ImageOperations/Selection/ExpandSelection.cpp
    src/ImageOperations/Selection/ExpandSelection.hpp
)

add_executable(
    MyGimp
    src/main.cpp
    ${MIMP_SRCS}
)

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
    )
endif ()

# --------------

add_executable(
        MyGimp_test

        tst/main.cpp
        ${MIMP_SRCS}
        tst/Vector.cpp
        tst/Color.cpp
        tst/Utils.cpp
        tst/FrameBuffer.cpp
        #tst/Exceptions.cpp
        tst/Image.cpp
        tst/Layer.cpp
        tst/LayerManager.cpp
        tst/SelectedArea.cpp
        tst/ToolBox.cpp
)

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
    )
endif ()
