#include "stdafx.h"
#include "CSketch.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
/**
*
*@brief Draws different coloured lines on _canvas image
*
*Initializes serial comunication with msp board and sets sizes of _canvas
*takes position data from msp joystick to draw line on _canvas image
*
*@author Stephen Cyr
*
*/

using namespace cv;

CSketch::CSketch(Size dim, int port)
{
	_canvas = Mat::zeros(Size(dim), CV_8UC3);
	sketch_contr.init_com(port);
	cv::imshow("image", _canvas);
    sketch_contr.set_data(DIGITAL, RED, HIGH);
}

CSketch::~CSketch()
{
}
void CSketch::update()
{
    //int printx;
    //int printy;
    //temp variable for per_result calculation
    //do
    //{
        sketch_contr.get_data(ANALOG, 9, _y_pos);
        sketch_contr.get_data(ANALOG, 15, _x_pos);
        _y_pos = 100 - ((_y_pos * 100) / 1024);
        _x_pos = (_x_pos * 100) / 1024;
        //printx = (500 * d_x_per) / 100;
        //printy = (500 * d_y_per) / 100;
        //printf("\nX: %d  Y: %d", _x_pos, _y_pos);
    //} while (1);
    sketch_contr.get_butt(chan_col, BUTT_2);
    if (!chan_col && (((getTickCount() - butt_2) / getTickFrequency()) > 0.2))
    {
        butt_2 = getTickCount();
        change_col();
    }
    sketch_contr.get_butt(clear, BUTT_1);
    if (!clear && (((getTickCount() - butt_1) / getTickFrequency()) > 0.2))
    {
        butt_1 = getTickCount();
        _canvas = Mat::zeros(Size(500, 500), CV_8UC3);
        cv::imshow("image", _canvas);
        p1.x = 250;
        p1.y = 250;
        p2.x = 250;
        p2.y = 250;
        
    }
}
void CSketch::change_col()
{
    switch (cur_colour)
    {
    case RED:
        colour = Scalar(255, 0, 0);
        cur_colour = BLUE;
        sketch_contr.set_data(DIGITAL, BLUE, HIGH);
        sketch_contr.set_data(DIGITAL, RED, LOW);
        break;
    case BLUE:
        colour = Scalar(0, 255, 0);
        cur_colour = GREEN;
        sketch_contr.set_data(DIGITAL, GREEN, HIGH);
        sketch_contr.set_data(DIGITAL, BLUE, LOW);
        break;
    case GREEN:
        colour = Scalar(0, 0, 255);
        cur_colour = RED;
        sketch_contr.set_data(DIGITAL, RED, HIGH);
        sketch_contr.set_data(DIGITAL, GREEN, LOW);
        break;
    }
}
void CSketch::draw()
{
    if (_x_pos > 70)
    {
        if (p2.x > 495)
        {
            p2.x = 500;
        }
        else
        {
            p2.x += incr;
        }
    }
    else if (_x_pos < 30)
    {
        if (p2.x < 5)
        {
            p2.x = 0;
        }
        else
        {
            p2.x -= incr;
        }
    }
    if (_y_pos > 70)
    {
        if (p2.y > 495)
        {
            p2.y = 500;
        }
        else
        {
            p2.y += incr;
        }
    }
    else if (_y_pos < 30)
    {
        if (p2.y < 5)
        {
            p2.y = 0;
        }
        else
        {
            p2.y -= incr;
        }
    }
    line(_canvas, p1, p2, colour,5);
    imshow("image", _canvas);
    p1 = p2;
}
