#ifndef DISCXXORD_EXCEPTION_HPP
#define DISCXXORD_EXCEPTION_HPP


#include <string>
#include "../Exceptions.hpp"

namespace Mimp
{
	class NetworkException : public BaseException {
	public:
		explicit NetworkException(const std::string &&msg) : BaseException(static_cast<const std::string &&>(msg)) {};
	};

	class SocketCreationErrorException : public NetworkException {
	public:
		explicit SocketCreationErrorException(const std::string &&msg) : NetworkException(static_cast<const std::string &&>(msg)) {};
	};

	class HostNotFoundException : public NetworkException {
	public:
		explicit HostNotFoundException(const std::string &&msg) : NetworkException(static_cast<const std::string &&>(msg)) {};
	};

	class ConnectException : public NetworkException {
	public:
		explicit ConnectException(const std::string &&msg) : NetworkException(static_cast<const std::string &&>(msg)) {};
	};

	class NotConnectedException : public NetworkException {
	public:
		explicit NotConnectedException(const std::string &&msg) : NetworkException(static_cast<const std::string &&>(msg)) {};
	};

	class AlreadyOpenedException : public NetworkException {
	public:
		explicit AlreadyOpenedException(const std::string &&msg) : NetworkException(static_cast<const std::string &&>(msg)) {};
	};

	class EOFException : public NetworkException {
	public:
		explicit EOFException(const std::string &&msg) : NetworkException(static_cast<const std::string &&>(msg)) {};
	};

	class HTTPErrorException : public NetworkException {
	private:
		Socket::HttpResponse _response;

	public:
		HTTPErrorException(const Socket::HttpResponse &response) :
			NetworkException(response.request.host + " responded with code " + std::to_string(response.returnCode) + " " + response.codeName),
			_response(response)
		{}

		Socket::HttpResponse getResponse() const { return this->_response; }
	};
}


#endif //DISCXXORD_EXCEPTION_HPP
