#include <stdint.h>
#include <QNetworkProxy>

void test() {
  QNetworkProxy proxy;
  proxy.setType(QNetworkProxy::Socks5Proxy);
  proxy.setHostName("127.0.0.1");
  proxy.setPort(10809);
  // proxy.setUser("username");
  // proxy.setPassword("password");
  QNetworkProxy::setApplicationProxy(proxy);
}

namespace socks5 {
struct Ipv4Address {
  union {
    uint32_t addr;
    uint8_t parts[4];
    struct {
      uint8_t part4;
      uint8_t part3;
      uint8_t part2;
      uint8_t part1;
    };
  };
  uint16_t port;
};

struct Ipv6Address {
  union {
    uint16_t parts[8];
    struct {
      uint16_t part8;
      uint16_t part7;
      uint16_t part6;
      uint16_t part5;
      uint16_t part4;
      uint16_t part3;
      uint16_t part2;
      uint16_t part1;
    };
  };
  uint16_t port;
};

const unsigned int conventionally_port = 1080;

// clang-format off
enum class authentication_method : uint8_t {
  no_authentication_required = 0x00,  // - X'00' NO AUTHENTICATION REQUIRED
  GSSAPI = 0x01,                      // - X'01' GSSAPI, must support
  username_password = 0x02,           // - X'02' USERNAME/PASSWORD, should support
                                      // - X'03' to X'7F' IANA ASSIGNED
                                      // - X'80' to X'FE' RESERVED FOR PRIVATE METHODS
  no_acceptable = 0xFF                // - X'FF' NO ACCEPTABLE METHODS
};
// clang-format on

/**
 +----+----------+----------+
 |VER | NMETHODS | METHODS  |
 +----+----------+----------+
 | 1  | 1        | 1 to 255 |
 +----+----------+----------+
 */
struct method_selection_request {
  uint8_t VER = 0x05;       // version
  uint8_t NMETHODS = 0x01;  // count of methods
  authentication_method METHODS[255] = {
      authentication_method::no_authentication_required};
};

/**
 +----+--------+
 |VER | METHOD |
 +----+--------+
 | 1  | 1      |
 +----+--------+
 */
struct method_selection_response {
  uint8_t VER = 0x05;  // version
  authentication_method METHOD =
      authentication_method::no_authentication_required;  // method
};

struct address_type {
  uint32_t ipv4_address = 0x01;
  uint32_t domain_name = 0x03;
  uint8_t ipv6_address[16] = {0};
};

struct domain_name {
  uint8_t length;  // count of byte in name
  char name[255];
};

/**
+----+-----+-------+------+----------+----------+
|VER | CMD | RSV   | ATYP | DST.ADDR | DST.PORT |
+----+-----+-------+------+----------+----------+
| 1  | 1   | X’00’ | 1    | Variable | 2        |
+----+-----+-------+------+----------+----------+
*/
struct subnegotiation_request {
  enum class command : uint8_t {
    undefined = 0x00,
    connect = 0x01,
    bind = 0x02,
    udp_associate = 0x03,
  };
  uint8_t version = 0x05;
  command command = command::connect;
  uint8_t reserved = 0x01;
  address_type address_type;
  uint32_t desired_destination_address;
  uint16_t desired_destination_port;
};

/**
+----+-----+-------+------+----------+----------+
|VER | REP | RSV   | ATYP | BND.ADDR | BND.PORT |
+----+-----+-------+------+----------+----------+
| 1  | 1   | X’00’ | 1    | Variable | 2        |
+----+-----+-------+------+----------+----------+
 */
struct subnegotiation_response {
  uint8_t version = 0x05;
  uint8_t reply;
  uint8_t reserved = 0x00;
  address_type address_type;
  uint32_t server_bound_address;
  uint16_t server_bound_port;
};

// https://datatracker.ietf.org/doc/html/rfc1929
struct username_password_authentication_request {
  uint8_t version = 0x01;
  uint8_t username_length;
  uint8_t username[255];
  uint8_t password_length;
  uint8_t password[255];
};

struct username_password_authentication_response {
  enum class status {
    success = 0x00,
    failure = 0x01,
  };
  uint8_t version = 0x01;
  status status = status::success;
};

enum class reply_type : uint8_t {
  succeeded = 0x00,
  general_SOCKS_server_failure = 0x01,
  connection_not_allowed_by_ruleset = 0x02,
  network_unreachable = 0x03,
  host_unreachable = 0x04,
  connection_refused = 0x05,
  TTL_expired = 0x06,
  command_not_supported = 0x07,
  address_type_not_supported = 0x08,
  undefined = 0xFF
};

void connect();
void bind();
void udp_associate();

/**
 * @brief
 When a reply (REP value other than X’00’) indicates a failure, the
 SOCKS server MUST terminate the TCP connection shortly after sending
 the reply. This must be no more than 10 seconds after detecting the
 condition that caused a failure.
 If the reply code (REP value of X’00’) indicates a success, and the
 request was either a BIND or a CONNECT, the client may now start
 passing data. If the selected authentication method supports
 encapsulation for the purposes of integrity, authentication and/or
 confidentiality, the data are encapsulated using the method-dependent
 encapsulation. Similarly, when data arrives at the SOCKS server for
 the client, the server MUST encapsulate the data as appropriate for
 the authentication method in use.
 *
 */
void reply_processing(){

};
}  // namespace socks5
