#include <gtest/gtest.h>
#include <TGUI/TGUI.hpp>
#include "../../../src/ImageOperations/Layer/MoveUp.hpp"
#include "../../../src/Editor.hpp"

TEST(MoveUp, oneClick) {
	tgui::Gui gui{};
	Mimp::ToolBox toolBox{gui};
	Mimp::Editor e{};
	Mimp::CanvasWidget::Ptr cw = Mimp::CanvasWidget::create(toolBox, Mimp::Vector2<unsigned int>{10, 10});
	Mimp::MoveUp mu;

	ASSERT_TRUE(cw->getSelectedLayer().pos.x == 0);
	ASSERT_TRUE(cw->getSelectedLayer().pos.y == 0);

	mu.click(gui, cw, nullptr, e);

	ASSERT_TRUE(cw->getSelectedLayer().pos.x == 0);
	ASSERT_TRUE(cw->getSelectedLayer().pos.y == -1);
}

TEST(MoveUp, tenClick) {
	tgui::Gui gui{};
	Mimp::ToolBox toolBox{gui};
	Mimp::Editor e{};
	Mimp::CanvasWidget::Ptr cw = Mimp::CanvasWidget::create(toolBox, Mimp::Vector2<unsigned int>{10, 10});
	Mimp::MoveUp mu;

	ASSERT_TRUE(cw->getSelectedLayer().pos.x == 0);
	ASSERT_TRUE(cw->getSelectedLayer().pos.y == 0);

	for (int i = 0; i < 10; i += 1)
		mu.click(gui, cw, nullptr, e);

	ASSERT_TRUE(cw->getSelectedLayer().pos.x == 0);
	ASSERT_TRUE(cw->getSelectedLayer().pos.y == -10);
}