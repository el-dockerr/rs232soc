// Session.cpp
// Author: Swen Kalski <swen.kalski@camaleao-studio.com>

#include "Session.h"


void Session::fail(beast::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}

void Session::run()
{
    net::dispatch(ws_.get_executor(),
        beast::bind_front_handler(
            &Session::on_run,
            shared_from_this()));
}

void Session::on_run()
{
    ws_.set_option(
        websocket::stream_base::timeout::suggested(
            beast::role_type::server));

    ws_.set_option(websocket::stream_base::decorator(
        [](websocket::response_type& res)
        {
            res.set(http::field::server,
                std::string(BOOST_BEAST_VERSION_STRING) +
                " websocket-server-async");
        }));
    ws_.async_accept(
        beast::bind_front_handler(
            &Session::on_accept,
            shared_from_this()));
}

void Session::on_accept(beast::error_code ec)
{
    if (ec) {
        return fail(ec, "accept");
    }
    do_read();
}

void Session::do_read()
{
    std::string response = serialPort.readFromSerialPort(serial);
    if (!response.empty()) {
        ws_.async_write(
            net::buffer(response.c_str(), (response.size())),
            beast::bind_front_handler(
                &Session::on_write,
                shared_from_this()));
    }
    ws_.async_read(buffer_, beast::bind_front_handler(&Session::on_read, shared_from_this()));
}

void Session::on_read(
    beast::error_code ec,
    std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);
    if (ec == websocket::error::closed) {
        return;
    }

    if (ec)
        return fail(ec, "read");
    ws_.text(ws_.got_text());
    string cmd{ beast::buffers_to_string(buffer_.data()) };
    serialPort.writeToSerialPort(serial, cmd);

    ws_.async_write(
        net::buffer(cmd.c_str(), (cmd.size())),
        beast::bind_front_handler(
            &Session::on_write,
            shared_from_this()));

}

void Session::on_write(beast::error_code ec, std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);

    if (ec)
        return fail(ec, "write");

    buffer_.consume(buffer_.size());
    do_read();
}
