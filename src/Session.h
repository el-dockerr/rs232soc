// Session.h
// Author: Swen Kalski <swen.kalski@camaleao-studio.com>

#ifndef SESSION_H
#define SESSION_H

#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include "SerialPort.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

class Session : public std::enable_shared_from_this<Session>
{
    websocket::stream<beast::tcp_stream> ws_;
    beast::flat_buffer buffer_;
    asio::serial_port& serial;
    SerialPort serialPort;

public:
    explicit Session(tcp::socket&& socket, asio::serial_port& fserial, SerialPort fserialPort) : ws_(std::move(socket)), serial(fserial), serialPort(fserialPort)
    {
    };

    // Get on the correct executor
    void run();
    // Start the asynchronous operation
    void on_run();
    void on_accept(beast::error_code ec);
    void do_read();
    void on_read(beast::error_code ec, std::size_t bytes_transferred);
    void on_write(beast::error_code ec, std::size_t bytes_transferred);

private:
    void fail(beast::error_code ec, char const* what);
};

#endif
