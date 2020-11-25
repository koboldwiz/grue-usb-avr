//Copyright (C) goon 2020. See the LICENSE file for details

#include "usbdriver.h"

int main (int argc, char *argv[])
{

	UsbDriver usbd;
	//usbd.printHeader(0);
	usbd.printAllConnectedDevices();

	return 0;
}
