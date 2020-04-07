//
// Created by Gegel85 on 07/04/2020.
//

#ifndef MYGIMP_EXCEPTIONS_HPP
#define MYGIMP_EXCEPTIONS_HPP


#include <exception>
#include <string>

namespace Mimp
{
	//! @brief The base exception.
	class BaseException : public std::exception {
	private:
		std::string _msg;

	public:
		explicit BaseException(const std::string &&msg) :
			_msg(msg)
		{};
		const char *what() const noexcept override {
			return this->_msg.c_str();
		};

		~BaseException() override = default;
	};

	class CorruptedGuiFile : public BaseException {
	public:
		explicit CorruptedGuiFile(const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg))
		{};
	};
}



#endif //MYGIMP_EXCEPTIONS_HPP
