#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

std::string make_daytime_string()
{
	using namespace std;
	time_t now = time(0);
	return ctime(&now);
}

int main()
{
	try
	{
		boost::asio::io_service io_service;
		tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 12280));
		std::string name; // define name
		//for (;;)
		//{
			tcp::socket socket(io_service);
			acceptor.accept(socket);

			std::string msg = make_daytime_string();
			boost::system::error_code ignore_error;
			boost::asio::write(socket, boost::asio::buffer(msg), ignore_error);

			for (;;)
			{
				std::cin >> name; // read into
				boost::asio::write(socket, boost::asio::buffer(name), ignore_error);
			}
			

		//}

	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}