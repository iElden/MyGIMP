/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** Undo.hpp
*/
#ifndef MYGIMP_UNDO_HPP
#define MYGIMP_UNDO_HPP

#include "ImageOperation.hpp"

namespace Mimp {
	class Undo : public ImageOperation {
	public:
		Undo();
		void click(tgui::Gui &gui, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr window, Editor &editor) const override;
	};
}


#endif //MYGIMP_UNDO_HPP
