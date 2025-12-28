#include <boost/asio.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace boost::asio::ip;

class HttpServer {
private:
  class Connection {
  public:
    tcp::socket socket;
    Connection(boost::asio::io_context &io_context) : socket(io_context) {}
  };

  boost::asio::io_context io_context;

  tcp::endpoint endpoint;
  tcp::acceptor acceptor;

  static string make_http_response(int code, const string& reason, const string& body) {
    string headers;
    headers += "HTTP/1.1 " + to_string(code) + " " + reason + "\r\n";
    headers += "Content-Type: text/plain; charset=utf-8\r\n";
    headers += "Content-Length: " + to_string(body.size()) + "\r\n";
    headers += "Connection: close\r\n";
    headers += "\r\n";
    return headers + body;
  }

  void handle_request(shared_ptr<Connection> connection) {
    auto read_buffer = make_shared<boost::asio::streambuf>();
    // Read from client until newline ("\r\n")
    async_read_until(connection->socket, *read_buffer, "\r\n", [this, connection, read_buffer](const boost::system::error_code &ec, size_t) {
      // If not error:
      if (ec) {
        return;
      }
      // Retrieve message from client as string:
      istream is(read_buffer.get());
      string method, target, version;

      if (!(is >> method >> target >> version)) {
        auto res = make_http_response(400, "Bad Request", "Bad Request");
        write_response_and_close(connection, res);
        return;
      }
       // Remove "\r" at the end of message

      // Close connection when "exit" is retrieved from client
      string line;
      getline(is, line);
      while (getline(is, line) && line != "\r" ) 

      if (method == "GET" && target == "/") {
        write_response_and_close(connection, make_http_response(200, "OK", "Dette er hovedsiden"));
      } else if (method == "GET" && target == "/en_side") {
        write_response_and_close(connection, make_http_response(200, "OK", "Dette er en side"));
      } else {
        write_response_and_close(connection, make_http_response(400, "Not Found", "404 Not Found"));
      }
    });
  }

  void write_response_and_close(const shared_ptr<Connection>& connection, const string& response) {
    auto out = make_shared<string>(response);
    boost::asio::async_write(
      connection->socket, boost::asio::buffer(*out),
      [connection, out](const boost::system::error_code& /*ec*/, size_t /*n*/) {
        boost::system::error_code ignored;
        connection->socket.shutdown(tcp::socket::shutdown_both, ignored);
        connection->socket.close(ignored);
      }
    );
  }

  void accept() {
    // The (client) connection is added to the lambda parameter and handle_request
    // in order to keep the object alive for as long as it is needed.
    auto connection = make_shared<Connection>(io_context);

    // Accepts a new (client) connection. On connection, immediately start accepting a new connection
    acceptor.async_accept(connection->socket, [this, connection](const boost::system::error_code &ec) {
      accept();
      // If not error:
      if (!ec) {
        handle_request(connection);
      }
    });
  }

public:
  HttpServer() : endpoint(tcp::v4(), 8080), acceptor(io_context, endpoint) {}

  void start() {
    accept();

    io_context.run();
  }
};

int main() {
  HttpServer http_server;

  cout << "Starting http server" << endl
       << "Connect in a terminal with: telnet localhost 8080. Type 'exit' to end connection." << endl;

  http_server.start();
}
