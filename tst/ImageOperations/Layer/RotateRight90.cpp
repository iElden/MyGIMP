#include <gtest/gtest.h>
#include <TGUI/TGUI.hpp>
#include "../../../src/ImageOperations/Layer/RotateRight90.hpp"
#include "../../../src/Editor.hpp"

//#define UNS(x) (static_cast<unsigned int>(x))

//! @todo Rotation tests only test the rotation member, not the actual rotation of the canvas.

TEST(RotateRigth90, noRotation) {
	tgui::Gui gui{};
	Mimp::ToolBox toolBox{gui};
	Mimp::Editor e{};
	Mimp::CanvasWidget::Ptr cw = Mimp::CanvasWidget::create(toolBox, Mimp::Vector2<unsigned int>{10, 10});
	Mimp::RotateRight90 rr90;

	ASSERT_TRUE(cw->getSelectedLayer().rotation == 0.f);
}

TEST(RotateRigth90, oneRotation) {
	tgui::Gui gui{};
	Mimp::ToolBox toolBox{gui};
	Mimp::Editor e{};
	Mimp::CanvasWidget::Ptr cw = Mimp::CanvasWidget::create(toolBox, Mimp::Vector2<unsigned int>{10, 10});
	Mimp::RotateRight90 rr90;

	cw->getSelectedLayer().buffer.clear(Mimp::Color::Black);

	cw->getSelectedLayer().buffer.drawAt({3, 3}, Mimp::Color::Red, 1, Mimp::SQUARE);

/*	auto buffer = cw->getSelectedLayer().buffer.getDrawBuffer();

	for (int i = 0; i < 100; i += 1) {
		if (i && i % 10 == 0) {
			std::cout << std::endl;
		}
		std::cout << (UNS(buffer[i]) == 0) << "|";
	}

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	ASSERT_TRUE(UNS(buffer[33]) == 255);
*/
	rr90.click(gui, cw, nullptr, e);

	//buffer = cw->getSelectedLayer().buffer.getDrawBuffer();
	ASSERT_TRUE(cw->getSelectedLayer().rotation == 90.f);

	/*for (int i = 0; i < 100; i += 1) {
		if (i && i % 10 == 0) {
			std::cout << std::endl;
		}
		std::cout << (UNS(buffer[i]) == 255) << "|";
	}*/
}

TEST(RotateRigth90, twoRotation) {
	tgui::Gui gui{};
	Mimp::ToolBox toolBox{gui};
	Mimp::Editor e{};
	Mimp::CanvasWidget::Ptr cw = Mimp::CanvasWidget::create(toolBox, Mimp::Vector2<unsigned int>{10, 10});
	Mimp::RotateRight90 rr90;

	rr90.click(gui, cw, nullptr, e);
	rr90.click(gui, cw, nullptr, e);

	ASSERT_TRUE(cw->getSelectedLayer().rotation == 180.f);
}

TEST(RotateRigth90, threeRotation) {
	tgui::Gui gui{};
	Mimp::ToolBox toolBox{gui};
	Mimp::Editor e{};
	Mimp::CanvasWidget::Ptr cw = Mimp::CanvasWidget::create(toolBox, Mimp::Vector2<unsigned int>{10, 10});
	Mimp::RotateRight90 rr90;

	rr90.click(gui, cw, nullptr, e);
	rr90.click(gui, cw, nullptr, e);
	rr90.click(gui, cw, nullptr, e);

	ASSERT_TRUE(cw->getSelectedLayer().rotation == 270.f);
}

TEST(RotateRigth90, fourRotation) {
	tgui::Gui gui{};
	Mimp::ToolBox toolBox{gui};
	Mimp::Editor e{};
	Mimp::CanvasWidget::Ptr cw = Mimp::CanvasWidget::create(toolBox, Mimp::Vector2<unsigned int>{10, 10});
	Mimp::RotateRight90 rr90;

	rr90.click(gui, cw, nullptr, e);
	rr90.click(gui, cw, nullptr, e);
	rr90.click(gui, cw, nullptr, e);
	rr90.click(gui, cw, nullptr, e);


	ASSERT_TRUE(cw->getSelectedLayer().rotation == 0.f);
}
