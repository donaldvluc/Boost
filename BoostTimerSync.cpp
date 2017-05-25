// BoostTimerSync.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

int main()
{
	boost::asio::io_service io_service;
	boost::asio::deadline_timer deadline_timer(io_service, boost::posix_time::seconds(5));
	deadline_timer.wait();
	std::cout << "Hello, World!" << std::endl;
	return 0;
}

