//
// Created by Gegel85 on 06/04/2019.
//

#include <cstring>
#include <sstream>
#include <unistd.h>
#include "SecuredSocket.hpp"
#include "Exceptions.hpp"

namespace Mimp
{
	SecuredSocket::SecuredSocket() : Socket()
	{
		//Initialize OpenSSL
		SSL_load_error_strings();
		SSL_library_init();
		this->_ssl_ctx = SSL_CTX_new(SSLv23_client_method());
		this->_connection = nullptr;
	}

	SecuredSocket::~SecuredSocket()
	{
		if (this->isOpen())
			this->disconnect();
		SSL_CTX_free(this->_ssl_ctx);
	}

	void	SecuredSocket::connect(unsigned int ip, unsigned short portno)
	{
		Socket::connect(ip, portno);

		//Create an SSL connection and attach it to the socket
		this->_connection = SSL_new(this->_ssl_ctx);
		SSL_set_fd(this->_connection, this->_sockfd);

		// perform the SSL/TLS handshake with the server - when on the
		// server side, this would use SSL_accept()
		if (SSL_connect(this->_connection) != 1) {
			Socket::disconnect();
			throw ConnectException("SSL handshake failed");
		}
	}

	void	SecuredSocket::disconnect()
	{
		if (!this->isOpen())
			throw NotConnectedException("This socket is not connected to a server");

		//Cleanup
		SSL_shutdown(this->_connection);
		Socket::disconnect();
	}

	void	SecuredSocket::send(const std::string &msg)
	{
		unsigned	pos = 0;

		while (pos < msg.length()) {
			int bytes = SSL_write(this->_connection, &msg.c_str()[pos], msg.length() - pos);

			if (bytes < 0)
				throw EOFException(strerror(errno));
			pos += bytes;
		}
	}

	std::string	SecuredSocket::read(int size)
	{
		size_t totalSize = 0;
		char *result = nullptr;
		char  buffer[1024];

		while (size != 0) {
			int bytes = SSL_read(this->_connection, buffer, (static_cast<unsigned>(size) >= sizeof(buffer)) ? sizeof(buffer) : size);

			if (bytes <= 0) {
				if (size < 0)
					break;
				throw EOFException(strerror(errno));
			}
			result = reinterpret_cast<char *>(std::realloc(result, totalSize + bytes));
			std::memcpy(&result[totalSize], buffer, bytes);
			totalSize += bytes;
			size -= bytes;
		}
		return {result, totalSize};
	}

	std::string	SecuredSocket::readUntilEOF()
	{
		return this->read(-1);
	}
}
