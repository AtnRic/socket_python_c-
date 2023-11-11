#include <cstdio>
#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace boost;
using namespace std;
using namespace boost::asio::ip;

void client_contact(const string msg2)
{
  cout << "send request" << endl;
  int port = 8000;
  try
  {
    boost::asio::io_service io_service;
    // socket creation
    tcp::socket socket(io_service);
    // connection
    socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("localhost"), port));
    // request/message from client
    const string msg = msg2;
    boost::system::error_code error;
    boost::asio::write(socket, boost::asio::buffer(msg), error);
    if (!error)
    {
      if (msg2 == "id_request\n")
      {
        std::cout << "bank sent id_request" << std::endl;
      }
    }
    else
    {
      cout << "send failed: " << error.message() << endl;
    }

    // getting response from server
    boost::asio::streambuf buf;
    boost::asio::read_until(socket, buf, "\n");

    if (error && error != boost::asio::error::eof)
    {
      cout << "receive failed: " << error.message() << endl;
    }
    else
    {
      std::string message = boost::asio::buffer_cast<const char *>(buf.data());

      std::cout << message << std::endl;

      if (msg == "id_request\n")
      {
        int id = std::stoi(message);
        cout << "id :" << id << endl;
      }
    }
  }
  catch (std::exception &e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }
}