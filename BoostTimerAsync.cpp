// BoostTimerAsync.cpp : Defines the entry point for the console application.
// Source : http://www.boost.org/doc/libs/1_64_0/doc/html/boost_asio/tutorial/tuttimer2.html

#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

void print(const boost::system::error_code& /*e*/)
{
	std::cout << "Hello, World!" << std::endl;
}

void hello(const boost::system::error_code& /*e*/)
{
	std::cout << "Hello, Donny!" << std::endl;
}

int main()
{
	boost::asio::io_service io_service;
	
	boost::asio::deadline_timer deadline_timer_a(io_service, boost::posix_time::seconds(5));
	deadline_timer_a.async_wait(&print);
	
	boost::asio::deadline_timer deadline_timer_b(io_service, boost::posix_time::seconds(3));
	deadline_timer_b.async_wait(&hello);

	io_service.run();

	return 0;
}

