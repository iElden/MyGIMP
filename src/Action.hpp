#ifndef MYGIMP_ACTION_HPP
#define MYGIMP_ACTION_HPP

#include "Keys.hpp"

namespace Mimp {

	class Action {
	private:
		Keys::KeyCombination _kc{Keys::KEY_UNKNOWN, false, false, false};

	public:
		Keys::KeyCombination getKeyCombination()
		{
			return this->_kc;
		}

		void setKeyCombination(Keys::KeyCombination kc)
		{
			this->_kc = kc;
		}
	};
}

#endif //MYGIMP_ACTION_HPP
