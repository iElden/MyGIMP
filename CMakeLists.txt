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

add_executable(
	MyGimp
	src/main.cpp
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
	src/Utils.cpp src/Utils.hpp src/Tools/Fill.cpp src/Tools/Fill.hpp src/Image.cpp src/Image.hpp src/SelectedArea.cpp src/SelectedArea.hpp src/Tools/ColorPick.cpp src/Tools/ColorPick.hpp src/Tools/SelectionTool.cpp src/Tools/SelectionTool.hpp src/Tools/RectSelectTool.cpp src/Tools/RectSelectTool.hpp src/Tools/SelectByColorTool.cpp src/Tools/SelectByColorTool.hpp src/Tools/FillSelection.cpp src/Tools/FillSelection.hpp src/Tools/ElipseSelectionTool.cpp src/Tools/ElipseSelectionTool.hpp src/Tools/SelectAll.cpp src/Tools/SelectAll.hpp src/Tools/UnselectAll.cpp src/Tools/UnselectAll.hpp src/ImageOperations/ImageOperation.cpp src/ImageOperations/ImageOperation.hpp src/ImageOperations/ImageOperationFactory.cpp src/ImageOperations/ImageOperationFactory.hpp src/ImageOperations/Selection/FillSelectionOperation.cpp src/ImageOperations/Selection/FillSelectionOperation.hpp src/Tools/InvertSelection.cpp src/Tools/InvertSelection.hpp src/ImageOperations/Selection/SelectAllOperation.cpp src/ImageOperations/Selection/SelectAllOperation.hpp src/ImageOperations/Selection/UnselectOperation.cpp src/ImageOperations/Selection/UnselectOperation.hpp src/ImageOperations/Selection/InvertSelectionOperation.cpp src/ImageOperations/Selection/InvertSelectionOperation.hpp)

target_link_libraries(
	MyGimp
	tgui
	sfml-graphics
	sfml-window
	sfml-system
	pthread
	stdc++fs
)