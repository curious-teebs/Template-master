#include "stdafx.h"
#include "CControl.h"

CControl::CControl()
{
}

CControl::~CControl()
{
}

void CControl::init_com(int comport)
{
    // Comport class
    std::string port = "COM" + std::to_string(comport);
    _com.open(port);
}

bool CControl::get_data(int type, int channel, int& result)
{
    std::string empty = "";
    std::string space = " ";
    std::string typ_s = std::to_string(type);
    std::string chan_s = std::to_string(channel);
    // TX and RX strings
    std::string tx_str = "G " + typ_s + space + chan_s + "\n";
    std::string rx_str;

    // temporary storage
    char buff[2];
  
    // Send TX string
    _com.write(tx_str.c_str(), tx_str.length());
    Sleep(10); // wait for ADC conversion, etc. May not be needed?

    rx_str = "";
    // start timeout count
    double start_time = cv::getTickCount();

    buff[0] = 0;
    // Read 1 byte and if an End Of Line then exit loop
    // Timeout after 1 second, if debugging step by step this will cause you to exit the loop
    while (buff[0] != '\n' && (cv::getTickCount() - start_time) / cv::getTickFrequency() < 1.0)
    {
        if (_com.read(buff, 1) > 0)
            {
            rx_str = rx_str + buff[0];
            }
    }
    size_t pos = 0;
     
    while ((pos = rx_str.find(" ")) != std::string::npos)
    {
        rx_str.erase(0, pos + space.length());
    }
    result = std::stod(rx_str);
    _com.flush();
    return false;
}

bool CControl::set_data(int type, int channel, int val)
{
    std::string space = " ";
    // converting type, channel, and value int to string
    std::string typ_s = std::to_string(type);
    std::string chan_s = std::to_string(channel);
    std::string val_s = std::to_string(val);
    // TX string
    std::string tx_str = "S " + typ_s + space + chan_s + space + val_s + "\n";
    // Send TX string
    _com.write(tx_str.c_str(), tx_str.length());
    // clears acknowdledgement response
    _com.flush();
	return false;
}

bool CControl::get_analog(int type, int channel, int& result, int& perc_result)
{
    //temp variable for per_result calculation
    int res;
    //curr.get_data(type, channel, result);
    res = result;
    perc_result = (res * 100) / 1024;
    return false;
}

bool CControl::get_butt(int& result, int butt, int type)
{
    get_data(type, butt, result);
    return false;
}

