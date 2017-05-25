// BoostTimerAsyncHandlerMember.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

class printer
{
public:
	printer(boost::asio::io_service& io_service)
		: timer_(io_service, boost::posix_time::seconds(1)),
		  count_(0)
	{
		timer_.async_wait(boost::bind(&printer::print, this));
	}

	~printer()
	{
		std::cout << "Final count is " << count_ << std::endl;
	}

private:
	void print()
	{
		if (count_ < 5)
		{
			std::cout << count_ << std::endl;
			++count_;

			timer_.expires_at(timer_.expires_at() + boost::posix_time::seconds(1));
			timer_.async_wait(boost::bind(&printer::print, this));
		}
	}
	
	boost::asio::deadline_timer timer_;
	int count_;
};

int main()
{
	boost::asio::io_service io;
	printer p(io);
	io.run();

	return 0;
}

