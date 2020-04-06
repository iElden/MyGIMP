cmake_minimum_required(VERSION 3.15)
project(MyGimp)

set(CMAKE_CXX_STANDARD 14)

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
	src/ImageEditorWidget.cpp
	src/ImageEditorWidget.hpp
)