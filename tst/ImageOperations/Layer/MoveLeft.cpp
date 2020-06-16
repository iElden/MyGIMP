#include <gtest/gtest.h>
#include <TGUI/TGUI.hpp>
#include "../../../src/ImageOperations/Layer/MoveLeft.hpp"
#include "../../../src/Editor.hpp"

TEST(MoveLeft, oneClick) {
	tgui::Gui gui{};
	Mimp::ToolBox toolBox{gui};
	Mimp::Editor e{};
	Mimp::CanvasWidget::Ptr cw = Mimp::CanvasWidget::create(toolBox, Mimp::Vector2<unsigned int>{10, 10});
	Mimp::MoveLeft mf;

	ASSERT_TRUE(cw->getSelectedLayer().pos.x == 0);
	ASSERT_TRUE(cw->getSelectedLayer().pos.y == 0);

	mf.click(gui, cw, nullptr, e);

	ASSERT_TRUE(cw->getSelectedLayer().pos.x == -1);
	ASSERT_TRUE(cw->getSelectedLayer().pos.y == 0);
}

TEST(MoveLeft, tenClick) {
	tgui::Gui gui{};
	Mimp::ToolBox toolBox{gui};
	Mimp::Editor e{};
	Mimp::CanvasWidget::Ptr cw = Mimp::CanvasWidget::create(toolBox, Mimp::Vector2<unsigned int>{10, 10});
	Mimp::MoveLeft mf;

	ASSERT_TRUE(cw->getSelectedLayer().pos.x == 0);
	ASSERT_TRUE(cw->getSelectedLayer().pos.y == 0);

	for (int i = 0; i < 10; i += 1)
		mf.click(gui, cw, nullptr, e);

	ASSERT_TRUE(cw->getSelectedLayer().pos.x == -10);
	ASSERT_TRUE(cw->getSelectedLayer().pos.y == 0);
}