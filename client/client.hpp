
#include <iostream>
#include <boost/asio.hpp>
#include <boost/beast.hpp>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

class WebSocketClient
{
public:
  explicit WebSocketClient(net::io_context &ioc, const std::string &host, const std::string &port)
      : resolver_(ioc), ws_(ioc)
  {
    // Resolver
    auto results = resolver_.resolve(host, port);
    beast::get_lowest_layer(ws_).connect(results);

    // Handshake
    ws_.handshake(host, "/");
  }

  void send(const std::string &message)
  {
    ws_.write(net::buffer(message));
  }

  void receive()
  {
    ws_.async_read(buffer_, [this](beast::error_code ec, std::size_t)
                   {
            if (ec == websocket::error::closed) {
                std::cout << "Connexion fermée par le serveur" << std::endl;
            } else if (ec) {
                std::cerr << "Erreur de lecture : " << ec.message() << std::endl;
            } else {
                std::cout << "Reçu : " << beast::buffers_to_string(buffer_.data()) << std::endl;
                buffer_.consume(buffer_.size());
                receive();  // Continuer à recevoir
            } });
  }

  void close()
  {
    ws_.close(websocket::close_code::normal);
  }

private:
  tcp::resolver resolver_;
  websocket::stream<beast::tcp_stream> ws_;
  beast::flat_buffer buffer_;
};
