#include <gtest/gtest.h>
#include "../src/Network/SecuredSocket.hpp"

TEST(SecuredSocketManipulation, sslDisconnection) {
    Mimp::SecuredSocket s;

    try {
        s.disconnect();
    } catch (std::exception &e) {
        ASSERT_EQ(std::string(e.what()), "This socket is not opened");
    }
}


TEST(SecuredSocketManipulaion, sslConnection1) {
    Mimp::SecuredSocket s;

    s.connect("8.8.8.8", 443);

    try {
        s.connect("8.8.8.8", 443);
    } catch (std::exception &e) {
        ASSERT_EQ(std::string(e.what()), "This socket is already opened");
    }
}

TEST(SecuredSocketManipulaion, sslConnection2) {
    Mimp::SecuredSocket s;

    s.connect("8.8.8.8", 443);

    try {
        s.connect(8888, 443);
    } catch (std::exception &e) {
        ASSERT_EQ(std::string(e.what()), "This socket is already opened");
    }
}