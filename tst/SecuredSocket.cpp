#include <gtest/gtest.h>
#include "../src/Network/SecuredSocket.hpp"
#include "../src/Network/Exceptions.hpp"


TEST(SecuredSocket, sslDisconnection) {
    Mimp::SecuredSocket s;

    try {
        s.disconnect();
    } catch (Mimp::NotConnectedException &e) {
        ASSERT_EQ(std::string(e.what()), "This socket is not connected to a server");
    }
}


TEST(SecuredSocket, sslConnection1) {
    Mimp::SecuredSocket s;

    s.connect("8.8.8.8", 443);

    try {
        s.connect("8.8.8.8", 443);
    } catch (Mimp::AlreadyOpenedException &e) {
        ASSERT_EQ(std::string(e.what()), "This socket is already opened");
    }
}

TEST(SecuredSocket, sslConnection2) {
    Mimp::SecuredSocket s;

    s.connect("8.8.8.8", 443);

    try {
        s.connect(8888, 443);
    } catch (Mimp::AlreadyOpenedException &e) {
        ASSERT_EQ(std::string(e.what()), "This socket is already opened");
    }
}