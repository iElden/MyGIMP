//
// Created by Gegel85 on 06/04/2020.
//

#ifndef MYGIMP_IMAGEEDITORWIDGET_HPP
#define MYGIMP_IMAGEEDITORWIDGET_HPP


#include <TGUI/Widgets/ChildWindow.hpp>
#include "Layer/LayerManager.hpp"
#include "ToolBox.hpp"

namespace Mimp
{
	class ImageEditorWidget : public tgui::ClickableWidget {
	private:
		LayerManager _layers;
		ToolBox &_box;

	public:
		ImageEditorWidget(ToolBox &box, Vector2<unsigned int> size);
		ImageEditorWidget(ToolBox &box, const std::string &path);
	};
}


#endif //MYGIMP_IMAGEEDITORWIDGET_HPP
