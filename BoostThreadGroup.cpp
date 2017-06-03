// BoostThreadGroup.cpp : Defines the entry point for the console application.
// Source : https://stackoverflow.com/questions/27672591/boost-asio-send-and-receive-messages

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include<boost/thread.hpp>

	using namespace boost::asio;

static const int PORT = 52275;

struct Client
{
	io_service& io_service_;
	ip::tcp::socket socket_;

	Client(io_service& svc, std::string const& host, std::string const& port)
		: io_service_(svc), socket_(io_service_)
	{
		ip::tcp::resolver resolver(io_service_);
		ip::tcp::resolver::iterator endpoint = resolver.resolve(ip::tcp::resolver::query(host, port));
		connect(this->socket_, endpoint);
	}

	void send(std::string const& message)
	{
		socket_.send(buffer(message));
	}
};

void client_thread()
{
	io_service svc;
	Client client(svc, "127.0.0.1", std::to_string(PORT));

	client.send("hello world\n");
	client.send("bye world\n");
}

void server_thread()
{
	try
	{
		io_service io_service;
		ip::tcp::acceptor acceptor(io_service, ip::tcp::endpoint(ip::tcp::v4(), PORT));

		{
			ip::tcp::socket socket(io_service);
			acceptor.accept(socket);

			streambuf sb;
			boost::system::error_code ec;
			while (boost::asio::read(socket, sb, ec))
			{
				std::cout << "received:\n" << &sb;

				if (ec)
				{
					std::cout << "status: " << ec.message() << "\n";
					break;
				}
			}
		}
	}
	catch (std::exception& error)
	{
		std::cerr << "Exception: " << error.what() << std::endl;
	}
}

int main()
{
	boost::thread_group tg;
	tg.create_thread(server_thread);

	boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
	tg.create_thread(client_thread);

	tg.join_all();

	return 0;
}
