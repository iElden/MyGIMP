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
    //! @brief Define the BaseException. All exceptions in Mimp must be inherited from here.
    class BaseException : public std::exception {
	private:
		std::string _msg; //!< Message of the exception

	public:
		//! @brief Constructor of the BaseException
		//! @param msg Exception message
		explicit BaseException(const std::string &&msg) : _msg(msg)	{};

		//! @brief what function
		//! @return char* The message of the exception
		const char *what() const noexcept override {
			return this->_msg.c_str();
		};

		~BaseException() override = default;
	};

    //! @brief Define a CorruptedGuiFileException.
    class CorruptedGuiFileException : public BaseException {
	public:
        //! @brief Create a CorruptedGuiFileException with a message.
        //! @param msg The error message.
		explicit CorruptedGuiFileException(const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg))
		{};
	};

    //! @brief Define a InvalidArgumentException.
    class InvalidArgumentException : public BaseException {
	public:
        //! @brief Create a InvalidArgumentException with a message.
        //! @param msg The error message.
		explicit InvalidArgumentException(const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg))
		{};
	};

    //! @brief Define a OutOfBoundException.
    class OutOfBoundException : public BaseException {
	public:
        //! @brief Create a OutOfBoundException with a message.
        //! @param msg The error message.
		explicit OutOfBoundException(const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg))
		{};
	};

    //! @brief Define a InvalidImageException.
    class InvalidImageException : public BaseException {
	public:
        //! @brief Create a InvalidImageException with a message.
        //! @param msg The error message.
		explicit InvalidImageException(const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg))
		{};
	};

    //! @brief Define a ExportErrorException.
    class ExportErrorException : public BaseException {
	public:
        //! @brief Create a ExportErrorException with a message.
        //! @param msg The error message.
		explicit ExportErrorException(const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg))
		{};
	};

    //! @brief Define a InvalidDrawShapeException.
    class InvalidDrawShapeException : public BaseException {
	public:
        //! @brief Create a InvalidDrawShapeException with a message.
        //! @param msg The error message.
		explicit InvalidDrawShapeException(const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg))
		{};
	};

    //! @brief Define a UnsupportedProtocolException.
	class UnsupportedProtocolException : public BaseException {
	public:
        //! @brief Create a UnsupportedProtocolException with a message.
        //! @param msg The error message.
		explicit UnsupportedProtocolException(const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg))
		{};
	};

    //! @brief Define a NotImplementedException.
    class NotImplementedException : public BaseException {
	public:
        //! @brief Create a NotImplementedException with a message.
        //! @param msg The error message.
		explicit NotImplementedException() :
			BaseException("Not implemented")
		{};
	};

    //! @brief Define a FileNotFoundException.
    class FileNotFoundException : public BaseException {
	public:
        //! @brief Create a FileNotFoundException with a message.
        //! @param path The error message.
		explicit FileNotFoundException(const std::string &path) :
			BaseException(path + ": " + strerror(errno))
		{};
	};

    //! @brief Define a TooMuchRecursionException.
    class TooMuchRecursionException : public BaseException {
	public:
        //! @brief Create a TooMuchRecursionException with a message.
        //! @param msg The error message.
		explicit TooMuchRecursionException(const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg))
		{};

        //! @brief Create a TooMuchRecursionException with a message.
        //! @param e The previous recursion exception.
        //! @param msg The error message.
		explicit TooMuchRecursionException(TooMuchRecursionException &e, const std::string &&msg) :
			BaseException(static_cast<const std::string &&>(msg) + "\n" + e.what())
		{};
	};
}



#endif //MYGIMP_EXCEPTIONS_HPP
