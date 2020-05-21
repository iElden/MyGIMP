//
// Created by Gegel85 on 06/04/2019.
//

#ifndef DISC_ORD_SECUREDSOCKET_HPP
#define DISC_ORD_SECUREDSOCKET_HPP


#include <openssl/ssl.h>
#include "Socket.hpp"

namespace Mimp
{
    //! @brief Define a SecuredSocket
	class SecuredSocket : public Socket {
	protected:
		SSL_CTX *_ssl_ctx;
		SSL	*_connection;

	public:
		using Socket::connect;

		//! @brief Construct a SecuredSocket.
		SecuredSocket();

		//! @brief SecuredSocket Destructor
		~SecuredSocket();

		//! @brief Connect the socket to an ip.
		//! @param ip The ip to connect to.
        //! @param portno The port number used to connect to the ip address.
		void        connect(unsigned int ip, unsigned short portno) override;

		//! @brief Disconnect the SecuredSocket.
		void        disconnect() override;

		//! @brief Send a message.
		//! @param msg The message to send.
		void        send(const std::string &msg) override;
		
		std::string read(int size) override;
		std::string readUntilEOF() override;
	};
}


#endif //DISC_ORD_SECUREDSOCKET_HPP
