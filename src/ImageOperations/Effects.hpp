#ifndef MYGIMP_EFFECTS_HPP
#define MYGIMP_EFFECTS_HPP

#include <TGUI/TGUI.hpp>
#include "ImageOperation.hpp"
#include "Effects/Effect.hpp"

namespace Mimp {
	class Effects : public ImageOperation {
	public:
		Effects();
		void click(tgui::Gui &gui, CanvasWidget::Ptr, tgui::ChildWindow::Ptr window, Editor &editor) const override;

	private:
		std::shared_ptr<tgui::ChildWindow> _win;
		std::vector<std::shared_ptr<Effect>> _effects;
	};
}

#endif //MYGIMP_EFFECTS_HPP
