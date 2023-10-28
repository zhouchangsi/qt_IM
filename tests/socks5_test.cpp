#include <gtest/gtest.h>
#include <iostream>

using string = std::string;

string http_request =
    "GET /ip HTTP/1.1Host: ipinfo.io\r\nUser-Agent: curl/7.65.2\r\n\r\n";

TEST(socks5, ok) {
  //   socket.connect()
}