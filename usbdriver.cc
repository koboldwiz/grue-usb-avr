//Copyright (C) goon 2020. See the LICENSE file for details

#include <dev/usb/usb.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <stdlib.h>
#include <string.h>

#include <string>
//#include <bits/basic_string.h>  // kludge
#include <iostream>

#include "usbdriver.h"

// ctors
UsbDriver::UsbDriver()
{
	initUsbDevices();
}

// dtors
UsbDriver::~UsbDriver()
{}

// private functions
void UsbDriver::initUsbDevices()
{
	usbDevices[0] = "/dev/usb0";
	usbDevices[1] = "/dev/usb1";
	usbDevices[2] = "/dev/usb2";
	usbDevices[3] = "/dev/usb3";
	usbDevices[4] = "/dev/usb4";
	usbDevices[5] = "/dev/usb5";
	usbDevices[6] = "/dev/usb6";
	usbDevices[7] = "/dev/usb7";

}

int UsbDriver::openForReading(int usbDeviceNumber)
{
	this->open(usbDeviceNumber, O_RDONLY);
}

int UsbDriver::openForWriting(int usbDeviceNumber)
{
	this->open(usbDeviceNumber, O_WRONLY);
}

int UsbDriver::close()
{
	::close(fileno);
	return 0;
}

int UsbDriver::open(int usbDeviceNumber, int flags)
{
	std::string deviceName = usbDevices[usbDeviceNumber];

	int returnCode;
		
	if ((returnCode = ::open(deviceName.c_str(), flags)) < 0) {
		std::cerr << "Cannot open device : ";
		std::cerr <<  deviceName.c_str();
		std::cerr << std::endl; 
		//	std::cerr << ", exiting ..." << std::endl;
		//	exit(0);
	} else {
	//FIXME DEBUG	#if 0
		std::cout << "Opened usb device ";
		std::cout << deviceName.c_str();
		std::cout << ", proceeding ... " << std::endl;
	//FIXME DEBUG #endif
	}

	if (returnCode >= 0) {
		fileno = returnCode;
	}

	return returnCode;	
}

// public functions

void UsbDriver::printHeader(int usbDeviceNumber)
{
	int returnCode;
	struct usb_device_info info;

	if ((returnCode = this->openForReading(usbDeviceNumber)) >= 0) {
		if ((returnCode = ioctl(fileno, USB_DEVICEINFO, &info)) >= 0) {
			std::cout << " DEVICEINFO : " << std::endl;
			const char *product = strdup(info.udi_product);
			std::cout << product << std::endl;
			const char *vendor = strdup(info.udi_vendor);
			std::cout << vendor << std::endl;
			const char *release = strdup(info.udi_release);
			std::cout << release << std::endl;
			const char *serial = strdup(info.udi_serial);
			std::cout << serial << std::endl;
		} else {
			std::cerr << "Cannot retrieve device info." << std::endl;
		}
	}

	this->close();	
}

// Does the first 8 usb devices 
void UsbDriver::printAllConnectedDevices()
{
	for (int i = 0; i < 8; i++) {
		std::cout << "=== Device " << i << std::endl; 
		this->printHeader(i);
	}	
}

void UsbDriver::readFromDevice(int usbDeviceNumber)
{
	this->open(usbDeviceNumber, O_RDONLY);
	// FIXME control flags for reading etc.	
}


	

