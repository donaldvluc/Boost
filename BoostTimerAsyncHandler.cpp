// BoostTimerAsyncHandler.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

void print(const boost::system::error_code& /*e*/,
	boost::asio::deadline_timer* d_t, int* count)
{
	if (*count < 5)
	{
		std::cout << *count << std::endl;
		++(*count);

		d_t->expires_at(d_t->expires_at() + boost::posix_time::seconds(1));
		d_t->async_wait(boost::bind(print,
			boost::asio::placeholders::error, d_t, count));
	}

	
}

int main()
{
	boost::asio::io_service io_service;
	int count = 0;
	boost::asio::deadline_timer deadline_timer(io_service, boost::posix_time::seconds(1));
	deadline_timer.async_wait(boost::bind(print,
		boost::asio::placeholders::error, &deadline_timer, &count));

	io_service.run();

	std::cout << "Final count is " << count << std::endl;

	return 0;
}

