#include <gtest/gtest.h>
#include <TGUI/TGUI.hpp>
#include "../../../src/ImageOperations/Clipboard/CutOperation.hpp"
#include "../../../src/Editor.hpp"
#include "clip.h"

#define INT(x) (static_cast<int>(x))

TEST(CutOperation, clickNoSelection) {
	tgui::Gui gui{};
	Mimp::ToolBox toolBox{gui};
	Mimp::Editor e{};
	Mimp::CanvasWidget::Ptr cw = Mimp::CanvasWidget::create(toolBox, Mimp::Vector2<unsigned int>{10, 10});
	Mimp::CutOperation co;

	co.click(gui, cw, nullptr, e);

	clip::image i;
	clip::get_image(i);

	ASSERT_TRUE(i.spec().height != 10);
	ASSERT_TRUE(i.spec().width != 10);
}

TEST(CutOperation, clickSelectAllLayer) {
	tgui::Gui gui{};
	Mimp::ToolBox toolBox{gui};
	Mimp::Editor e{};
	Mimp::CanvasWidget::Ptr cw = Mimp::CanvasWidget::create(toolBox, Mimp::Vector2<unsigned int>{10, 10});
	Mimp::CutOperation co;

	cw->selectedArea.selectAll();
	co.click(gui, cw, nullptr, e);

	clip::image i;
	clip::get_image(i);

	ASSERT_TRUE(i.spec().height == 10);
	ASSERT_TRUE(i.spec().width == 10);
}

TEST(CutOperation, clickSelectOnePixel) {
	tgui::Gui gui{};
	Mimp::ToolBox toolBox{gui};
	Mimp::Editor e{};
	Mimp::CanvasWidget::Ptr cw = Mimp::CanvasWidget::create(toolBox, Mimp::Vector2<unsigned int>{10, 10});
	Mimp::CutOperation co;

	cw->selectedArea.add(5, 5);
	co.click(gui, cw, nullptr, e);

	clip::image i;
	clip::get_image(i);

	ASSERT_TRUE(i.spec().height == 1);
	ASSERT_TRUE(i.spec().width == 1);
}

TEST(CutOperation, clickWholeLayerSquare) {
	tgui::Gui gui{};
	Mimp::ToolBox toolBox{gui};
	Mimp::Editor e{};
	Mimp::CanvasWidget::Ptr cw = Mimp::CanvasWidget::create(toolBox, Mimp::Vector2<unsigned int>{10, 10});
	Mimp::CutOperation co;

	cw->getSelectedLayer()->buffer.drawAt({5, 5}, Mimp::Color::Green, 2, Mimp::SQUARE);
	cw->selectedArea.selectAll();
	co.click(gui, cw, nullptr, e);

	clip::image i;
	clip::get_image(i);

	ASSERT_TRUE(i.spec().height == 10);
	ASSERT_TRUE(i.spec().width == 10);

	std::stringstream ss;

	for (int idx = 0; idx < 400; idx += 4) {
		ss << INT(i.data()[idx + 0]) << INT(i.data()[idx + 1]) << INT(i.data()[idx + 2]) << INT(i.data()[idx + 3])
		   << ",";
	}

	std::string correct =
			"-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,"
			"-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,"
			"-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,"
			"-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,"
			"-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-10-10,-10-10,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,"
			"-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-10-10,-10-10,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,"
			"-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,"
			"-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,"
			"-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,"
			"-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,-1-1-1-1,";

	std::cout << ss.str() << std::endl;

	ASSERT_EQ(ss.str(), correct);

	auto buffer = cw->getSelectedLayer()->buffer.getBuffer();
	std::stringstream ssbuffer;

	for (int idx = 0; idx < 100; idx += 1) {
		ssbuffer << (buffer[idx] == Mimp::Color::Green);
	}

	correct =
			"0000000000"
			"0000000000"
			"0000000000"
			"0000000000"
			"0000000000"
			"0000000000"
			"0000000000"
			"0000000000"
			"0000000000"
			"0000000000";


	ASSERT_EQ(ssbuffer.str(), correct);

}