#ifndef MYGIMP_SYMMETRY_HPP
#define MYGIMP_SYMMETRY_HPP

#include "Effect.hpp"

namespace Mimp {
	class Symmetry : public Effect {
	public:
		Symmetry(std::shared_ptr<tgui::ChildWindow> window);

		void setImage(CanvasWidget::Ptr &image) override;

	private:
		Vector2<bool> _symmetry = {false, false};
		Vector2<int> _axis = {0, 0};
		bool _axialSymmetry = false;
	};
}


#endif //MYGIMP_SYMMETRY_HPP
