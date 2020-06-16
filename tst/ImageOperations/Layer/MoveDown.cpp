#include <gtest/gtest.h>
#include <TGUI/TGUI.hpp>
#include "../../../src/ImageOperations/Layer/MoveDown.hpp"
#include "../../../src/Editor.hpp"

TEST(MoveDown, oneClick) {
	tgui::Gui gui{};
	Mimp::ToolBox toolBox{gui};
	Mimp::Editor e{};
	Mimp::CanvasWidget::Ptr cw = Mimp::CanvasWidget::create(toolBox, Mimp::Vector2<unsigned int>{10, 10});
	Mimp::MoveDown md;

	ASSERT_TRUE(cw->getSelectedLayer().pos.x == 0);
	ASSERT_TRUE(cw->getSelectedLayer().pos.y == 0);

	md.click(gui, cw, nullptr, e);

	ASSERT_TRUE(cw->getSelectedLayer().pos.x == 0);
	ASSERT_TRUE(cw->getSelectedLayer().pos.y == 1);
}

TEST(MoveDown, tenClick) {
	tgui::Gui gui{};
	Mimp::ToolBox toolBox{gui};
	Mimp::Editor e{};
	Mimp::CanvasWidget::Ptr cw = Mimp::CanvasWidget::create(toolBox, Mimp::Vector2<unsigned int>{10, 10});
	Mimp::MoveDown md;

	ASSERT_TRUE(cw->getSelectedLayer().pos.x == 0);
	ASSERT_TRUE(cw->getSelectedLayer().pos.y == 0);

	for (int i = 0; i < 10; i += 1)
		md.click(gui, cw, nullptr, e);

	ASSERT_TRUE(cw->getSelectedLayer().pos.x == 0);
	ASSERT_TRUE(cw->getSelectedLayer().pos.y == 10);
}