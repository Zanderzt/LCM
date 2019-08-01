/*  Designed By ZhangTong
*   2019/07/13
*   file: listener.cpp
*   LCM example program.
*   compile with:
*  $ gcc -o listener listener.cpp -llcm
*/

#include <iostream>
#include "lcm/lcm-cpp.hpp"
 
class MyMessageHandler 
{
public:
	void onMessage(const lcm::ReceiveBuffer* rbuf, const std::string& channel) 
	{
		std::cout << (int)((unsigned char*)rbuf->data)[0] << std::endl;
		std::cout << (int)((unsigned char*)rbuf->data)[1] << std::endl;
		std::cout << (int)((unsigned char*)rbuf->data)[2] << std::endl;
		std::cout << (int)((unsigned char*)rbuf->data)[3] << std::endl;
		std::cout << (int)((unsigned char*)rbuf->data)[4] << std::endl;
		std::cout << "接收成功!";
	}
};
 
int main() {
	lcm::LCM lcm;
	MyMessageHandler handler;
	lcm.subscribe("EXAMPLE", &MyMessageHandler::onMessage, &handler);
	while (true)
		lcm.handle();
	return 0;
}
