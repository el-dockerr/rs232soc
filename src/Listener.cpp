// Listener.cpp
// Author: Swen Kalski <swen.kalski@camaleao-studio.com>

#include "Listener.h"

void Listener::fail(beast::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}

Listener::Listener(net::io_context& ioc, tcp::endpoint endpoint, asio::serial_port& fserial, SerialPort fserialPort) : ioc_(ioc), acceptor_(ioc), serial(fserial), serialPort(fserialPort)
{
    beast::error_code ec;

    // Open the acceptor
    acceptor_.open(endpoint.protocol(), ec);
    if (ec)
    {
        fail(ec, "open");
        return;
    }

    // Allow address reuse
    acceptor_.set_option(net::socket_base::reuse_address(true), ec);
    if (ec)
    {
        fail(ec, "set_option");
        return;
    }

    // Bind to the server address
    acceptor_.bind(endpoint, ec);
    if (ec)
    {
        fail(ec, "bind");
        return;
    }

    // Start listening for connections
    acceptor_.listen(
        net::socket_base::max_listen_connections, ec);
    if (ec)
    {
        fail(ec, "listen");
        return;
    }
}

// Start accepting incoming connections
void Listener::run()
{
    do_accept();
}

void Listener::do_accept()
    {
        // The new connection gets its own strand
        acceptor_.async_accept(
            net::make_strand(ioc_),
            beast::bind_front_handler(
                &Listener::on_accept,
                shared_from_this()));
    }

void Listener::on_accept(beast::error_code ec, tcp::socket socket)
{
    if (ec)
    {
        fail(ec, "accept");
    }
    else
    {
        std::make_shared<Session>(std::move(socket), serial, serialPort)->run();
    }
    do_accept();
}
