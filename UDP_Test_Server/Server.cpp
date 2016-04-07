#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>

using boost::asio::ip::udp;
using std::cout;
using std::endl;

const char IPADRESSE[] = "134.103.120.233";
const char PORT[] = "8888";

int main()
{
	try
	{
		boost::asio::io_service io_service;

		udp::socket socket(io_service, udp::endpoint(udp::v4(), 13));

		for (;;)
		{
			boost::array<char, 1> recv_buf;
			udp::endpoint remote_endpoint;
			boost::system::error_code error;
			socket.non_blocking(true);
			
			int size = 0;
			do {
				size = socket.receive_from(boost::asio::buffer(recv_buf),
					remote_endpoint, 0, error);
				cout << ".";
			} while (size == 0);

			if (error && error != boost::asio::error::message_size)
				throw boost::system::system_error(error);

			std::string message = "Test";

			boost::system::error_code ignored_error;
			socket.send_to(boost::asio::buffer(message),
				remote_endpoint, 0, ignored_error);
		}
	}

	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
