#include <boost/asio.hpp>
#include <ctime>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;

std::string make_daytime_string() {
    using std::ctime;
    time_t now = time(0);
    return ctime(&now);
}

int main(int argc, char **argv) {
    try {
        boost::asio::io_service io_service;
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 13));
        for (;;) {
            tcp::socket socket(io_service);
            acceptor.accept(socket);
            std::cout << "IP:" << socket.local_endpoint().address().to_string()
                      << std::endl;
            std::string message = make_daytime_string();
            boost::system::error_code ignored_error;
            boost::asio::write(socket, boost::asio::buffer(message));
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
