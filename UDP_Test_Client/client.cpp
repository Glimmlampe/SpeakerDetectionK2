#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>


using boost::asio::ip::udp;
using std::cout;
using std::endl;

const char IPADRESSE[] = "134.103.120.233";
const char PORT[] = "8888";

int main(int argc, char* argv[])
{
	try
	{
		if (argc != 2)
		{
			std::cerr << "Usage: client <host>" << std::endl;
			return 1;
		}

		boost::asio::io_service io_service;


		udp::resolver resolver(io_service);
		udp::resolver::query query(udp::v4(), argv[1], "daytime");

		udp::endpoint receiver_endpoint = *resolver.resolve(query);

		udp::socket socket(io_service);
		socket.open(udp::v4());

		boost::array<char, 1> send_buf = { 0 };
		socket.send_to(boost::asio::buffer(send_buf), receiver_endpoint);

		boost::array<char, 128> recv_buf;
		udp::endpoint sender_endpoint;
		size_t len = socket.receive_from(
			boost::asio::buffer(recv_buf), sender_endpoint);

		std::cout.write(recv_buf.data(), len);
	}

	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
