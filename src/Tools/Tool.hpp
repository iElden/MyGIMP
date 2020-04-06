//
// Created by Gegel85 on 06/04/2020.
//

#ifndef MYGIMP_TOOL_HPP
#define MYGIMP_TOOL_HPP


#include <TGUI/Widgets/ScrollablePanel.hpp>
#include "../Layer/Layer.hpp"

namespace Mimp
{
	class Tool {
	public:
		virtual void operator()(Vector2<int> pos, Layer &layer) = 0;
		virtual tgui::ScrollablePanel::Ptr makeParametersPanel() = 0;
	};
}


#endif //MYGIMP_TOOL_HPP
