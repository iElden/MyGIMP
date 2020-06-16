/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** Redo.hpp
*/
#ifndef MYGIMP_REDO_HPP
#define MYGIMP_REDO_HPP


#include "ImageOperation.hpp"

namespace Mimp {
	class Redo : public ImageOperation {
	public:
		Redo();
		void click(tgui::Gui &gui, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr window, Editor &editor) const override;
	};
}


#endif //MYGIMP_REDO_HPP
