/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** SelectionTools.hpp
*/
#ifndef MYGIMP_SELECTIONTOOL_HPP
#define MYGIMP_SELECTIONTOOL_HPP

#include "../Image.hpp"
#include "Tool.hpp"

namespace Mimp {
	class SelectionTool : public Tool {
	protected:
		Image _image;
	public:
		SelectionTool(const std::string &name, Image &image);
		void onSelect() override;
		virtual void clear() {};
	};
}


#endif //MYGIMP_SELECTIONTOOL_HPP
