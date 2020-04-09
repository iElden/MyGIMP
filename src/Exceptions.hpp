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

	class CorruptedGuiFileException : public BaseException {
	public:
		explicit CorruptedGuiFileException(const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg))
		{};
	};

	class InvalidArgumentException : public BaseException {
	public:
		explicit InvalidArgumentException(const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg))
		{};
	};

	class OutOfBoundException : public BaseException {
	public:
		explicit OutOfBoundException(const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg))
		{};
	};

	class InvalidImageException : public BaseException {
	public:
		explicit InvalidImageException(const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg))
		{};
	};
}



#endif //MYGIMP_EXCEPTIONS_HPP
