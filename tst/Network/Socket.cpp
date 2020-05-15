#include <gtest/gtest.h>
#include "../../src/Network/Socket.hpp"
#include "../../src/Network/Exceptions.hpp"

TEST(Socket, socketDisconnection) {
    Mimp::Socket s;

    try {
        s.disconnect();
    } catch (Mimp::NotConnectedException &e) {
        ASSERT_EQ(std::string(e.what()), "This socket is not opened");
    }
}

TEST(SocketManipulaion, socketConnection1) {
    Mimp::Socket s;

    s.connect("8.8.8.8", 443);

    try {
        s.connect("8.8.8.8", 443);
    } catch (Mimp::AlreadyOpenedException &e) {
        ASSERT_EQ(std::string(e.what()), "This socket is already opened");
    }
}

TEST(SocketManipulaion, socketConnection2) {
    Mimp::Socket s;

    s.connect("8.8.8.8", 443);

    try {
        s.connect(8888, 443);
    } catch (Mimp::AlreadyOpenedException &e) {
        ASSERT_EQ(std::string(e.what()), "This socket is already opened");
    }
}

TEST(Socket, socketMakeHttpRequest) {
    Mimp::Socket s;
    Mimp::Socket::HttpRequest request;

    s.connect("8.8.8.8", 443);
    try {
        s.makeHttpRequest(request);
    } catch (Mimp::AlreadyOpenedException &e) {
        ASSERT_EQ(std::string(e.what()), "This socket is already opened");
    }
}

//TEST(Socket, socketRead) {
//    Mimp::Socket s;
//
//    s.connect("8.8.8.8", 443);
//    ASSERT_TRUE(s.read(0).size() != 0);
//}

TEST(Socket, openedSocket) {
    Mimp::Socket s;

    ASSERT_FALSE(s.isOpen());
    s.connect("8.8.8.8", 443);
    ASSERT_TRUE(s.isOpen());
}