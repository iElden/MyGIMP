//
// Created by Gegel85 on 07/04/2020.
//

#ifndef MYGIMP_EXCEPTIONS_HPP
#define MYGIMP_EXCEPTIONS_HPP


#include <exception>
#include <string>
#include <cstring>

namespace Mimp
{
	//! @brief The base exception.
	//! @inherit std::exception
	class BaseException : public std::exception {
	private:
		//! @brief Message of the exception
		std::string _msg;

	public:
		//! @brief Constructor of the BaseException class
		//! @param msg Exception message
		explicit BaseException(const std::string &&msg) :
			_msg(msg)
		{};
		//! @brief what function
		//! @return char* The message of the exception
		const char *what() const noexcept override {
			return this->_msg.c_str();
		};

		~BaseException() override = default;
	};
	//! @brief Corrupted Gui File Exception
	//! @inherit BaseException
	class CorruptedGuiFileException : public BaseException {
	public:
		//! @brief Function to print
		//! @param msg Message of the Exception
		explicit CorruptedGuiFileException(const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg))
		{};
	};

	//! @brief Invalid Argument Exception
	//! @inherit BaseException
	class InvalidArgumentException : public BaseException {
	public:
		//! @brief Function to print
		//! @param msg Message of the Exception
		explicit InvalidArgumentException(const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg))
		{};
	};

	//! @brief Out of Bound Exception
	//! @inherit BaseException
	class OutOfBoundException : public BaseException {
	public:
		//! @brief Function to print
		//! @param msg Message of the Exception
		explicit OutOfBoundException(const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg))
		{};
	};

	//! @brief Invalid Image Exception
	//! @inherit BaseException
	class InvalidImageException : public BaseException {
	public:
		//! @brief Function to print
		//! @param msg Message of the Exception
		explicit InvalidImageException(const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg))
		{};
	};

	//! @brief Export Error Exception
	//! @inherit BaseException
	class ExportErrorException : public BaseException {
	public:
		//! @brief Function to print
		//! @param msg Message of the Exception
		explicit ExportErrorException(const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg))
		{};
	};

	class InvalidDrawShapeException : public BaseException {
	public:
		//! @brief Function to print
		//! @param msg Message of the Exception
		explicit InvalidDrawShapeException(const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg))
		{};
	};

	class UnsupportedProtocolException : public BaseException {
	public:
		//! @brief Function to print
		//! @param msg Message of the Exception
		explicit UnsupportedProtocolException(const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg))
		{};
	};

	class NotImplementedException : public BaseException {
	public:
		//! @brief Function to print
		//! @param msg Message of the Exception
		explicit NotImplementedException() :
			BaseException("Not implemented")
		{};
	};

	class FileNotFoundException : public BaseException {
	public:
		//! @brief Function to print
		//! @param msg Message of the Exception
		explicit FileNotFoundException(const std::string &path) :
			BaseException(path + ": " + strerror(errno))
		{};
	};
}



#endif //MYGIMP_EXCEPTIONS_HPP
