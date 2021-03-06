#pragma once
#include "Serial.h"
#include "opencv.hpp"

/**
*
*@brief Communicates through serail port
*
*Initializes serial communication and has methods to read and write data to com port
*
*@author Stephen Cyr
*
*/
enum { DIGITAL = 0, ANALOG, SERVO };
constexpr auto BUTT_1 = 33;
constexpr auto BUTT_2 = 32;

class CControl 
{
private:
    /** @brief Serial object used for serial communication with com port
    */
    Serial _com;
    double last_push = cv::getTickCount();

public:
    /** @brief CControl constructor
    *
    * @param none
    * @return nothing
    */
    CControl();
    /** @brief CControl destructor
    *
    * @param none
    * @return nothing
    */
    ~CControl();
    /** @brief initalizes serial communication with specified com port
    *
    * @param integer specifying com port
    * @return nothing
    */
    void init_com(int comport);
    /** @brief sends a request for a type of data at a pin, and reads return data at com port
    *
    * @param int specifying data type, int specifying what channel, and memory address of int to store response
    * @return bool expression
    */
    bool get_data(int type, int channel, int& result);
    /** @brief sends a signal to be outputed on a specified channel
    *
    * @param int specifying data type, int specifying channel, and int specifying value for pin
    * @return booling expression
    */
    bool set_data(int type, int channel, int val); 
    /** @brief Calls get_data function and returns data and analog data and percent
    *
    * @param int specifying data type, int specifying channel, memory address for data, and memory address for percent
    * @return booling expresion
    */
    bool get_analog(int, int, int&, int&);
    bool get_butt(int&, int, int = 0);
};