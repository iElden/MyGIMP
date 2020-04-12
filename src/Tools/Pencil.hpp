//
// Created by Gegel85 on 07/04/2020.
//

#ifndef MYGIMP_PENCIL_HPP
#define MYGIMP_PENCIL_HPP


#include "Tool.hpp"
#include "../ToolBox.hpp"

namespace Mimp
{
    //! @brief Class For the Pencil Tool
    //! @inherit Tool
    //! @details Pencil tool draw in the clicked area
	class Pencil : public Tool {
	private:
        //! @brief Reference of the Toolbox
	    ToolBox &_box;

	public:
        //! @brief Constructor of the Pencil Class
        //! @param toolBox ToolBox to create the Pencil Tool
		Pencil(ToolBox &);
		void onMouseDrag(Vector2<int> oldPos, Vector2<int> newPos, MouseClick click, Layer &layer) override;
		void onClick(Vector2<int> pos, MouseClick click, Layer &layer) override;
		tgui::ScrollablePanel::Ptr getParametersPanel() const override;
	};
}


#endif //MYGIMP_PENCIL_HPP
