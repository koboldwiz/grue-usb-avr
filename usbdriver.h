//Copyright (C) goon 2020. See the LICENSE file for details

#include <map>
#include <string>

class UsbDriver
{
	public:
	UsbDriver();
	virtual ~UsbDriver();

	protected:

	private:
	int openForReading(int usbDeviceNumber);
	int openForWriting(int usbDeviceNumber);
	int close();

	int open(int usbDeviceNumber, int flags);

	void initUsbDevices();

	public:
	void printHeader(int usbDeviceNumber);
	void printAllConnectedDevices();
	
	void readFromDevice(int usbDeviceNumber);
	
	private:
	int fileno;
	std::map<int, std::string> usbDevices;

};


