#include <iostream>
#include "embeddedPython.h"
using namespace std;

int main()
{
	pyWeb webInterface;
	webInterface.initialize();
	webInterface.updateHtml("ko");
	webInterface.getValue("ko");
	webInterface.getEmployeeNumber("ko");
	webInterface.getIncome("ko");
	webInterface.getRevenue("ko");
	webInterface.getVolume("ko");

	return 1;
}