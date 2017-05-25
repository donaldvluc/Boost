// BoostTimeServer.cpp : Defines the entry point for the console application.
// Source : https://theboostcpplibraries.com/boost.asio-network-programming

#include <iostream>
#include <ctime>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
//#include <boost/enable_shared_from_this.hpp>

#pragma warning( disable : 4996 )
//: public boost::enable_shared_from_this<TimeServer>
class TimeServer
	
{
public:

	/* Constructor */
	TimeServer(boost::asio::io_service& ios)
	:	ios_(ios),
		socket_(ios),
		acceptor_(ios, boost::asio::ip::tcp::endpoint(
			boost::asio::ip::tcp::v4(),
			2014))
	{
		start();
	}

private:
	void write_handler(const boost::system::error_code& error,
					   std::size_t bytes_transferred)
	{
		if (!error)
		{
			socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_send);
		}
	}
	
	void accept_handler(const boost::system::error_code& error)
	{
		if (!error)
		{
			std::time_t now = std::time(nullptr);
			data_ = std::ctime(&now);
			
			boost::asio::async_write(
				socket_,
				boost::asio::buffer(data_),
				boost::bind(
					&TimeServer::write_handler,
					this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
		}
	}
	
	void start()
	{
		acceptor_.async_accept(
			socket_,
			boost::bind(
				&TimeServer::accept_handler,
				this,
				boost::asio::placeholders::error));
	}

	boost::asio::io_service& ios_;
	boost::asio::ip::tcp::socket socket_;
	boost::asio::ip::tcp::acceptor acceptor_;
	std::string data_;
};


int main()
{
	try
	{
		boost::asio::io_service io_service;
		TimeServer ts(io_service);
		io_service.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}

