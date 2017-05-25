// BoostWebClient.cpp : Defines the entry point for the console application.
// Source : https://theboostcpplibraries.com/boost.asio-network-programming

#include <iostream>
#include <array>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

class WebClient
	: public boost::enable_shared_from_this<WebClient>
{
public:

	/* Constructor */
	WebClient(boost::asio::io_service& io_service)
	:   io_service_(io_service),
		resolver_(io_service),
		socket_(io_service)
	{
		boost::asio::ip::tcp::resolver::query q{ "student00.cse.nd.edu", "9898" };
		resolver_.async_resolve(
			q,
			boost::bind(&WebClient::resolve_handler,
				this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::iterator));
	}

private:
	
	/* Handlers */
	void read_handler(const boost::system::error_code& error,
					  std::size_t bytes_transferred)
	{
		if (!error)
		{
			std::cout.write(bytes_.data(), bytes_transferred);
			socket_.async_read_some(
				boost::asio::buffer(bytes_, 4096),
				boost::bind(&WebClient::read_handler,
					shared_from_this(),
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
		}
	}

	void connect_handler(const boost::system::error_code& error)
	{
		if (!error)
		{
			std::string r =
				"GET / HTTP/1.0\r\nHost: student00.cse.nd.edu:9898\r\n\r\n";
			boost::asio::write(socket_, boost::asio::buffer(r));
			socket_.async_read_some(
				boost::asio::buffer(bytes_, 4096),
				boost::bind(&WebClient::read_handler,
					shared_from_this(),
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
		}
	}
	
	void resolve_handler(const boost::system::error_code& error,
						 boost::asio::ip::tcp::resolver::iterator it)
	{
		if (!error)
		{
			socket_.async_connect(
				*it,
				boost::bind(&WebClient::connect_handler,
					shared_from_this(),
					boost::asio::placeholders::error));
		}
	}

	/* Member Variables */
	boost::asio::io_service& io_service_;
	boost::asio::ip::tcp::socket socket_;
	boost::asio::ip::tcp::resolver resolver_;

	std::array<char, 4096> bytes_;
};

int main()
{
	boost::asio::io_service io_service;
	WebClient wc(io_service);
	
	io_service.run();
	
	return 0;
}