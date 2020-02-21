////////////////////////////////////////////////////////////////
// ELEX 4618 Template project for BCIT
// Created Oct 5, 2016 by Craig Hennessey
// Last updated March 23, 2017
////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include <string>
#include <iostream>
#include <thread>

#include "Client.h"
#include "Server.h"
#include "Serial.h" // Must include Windows.h after Winsock2.h, so Serial must include after Client/Server
#include "CControl.h"
#include "CPong.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <stdio.h>  

// OpenCV Include
#include "opencv.hpp"

// OpenCV Library
#pragma comment(lib,".\\opencv\\lib\\opencv_world310d.lib")

#include "CSketch.h"

//CControl curr;


void process_msg()
{
  MSG msg;
  while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
  {
    ::TranslateMessage(&msg);
    ::DispatchMessage(&msg);
  }
}

////////////////////////////////////////////////////////////////
// Serial Communication
////////////////////////////////////////////////////////////////
void test_com()
{
  // Comport class
  Serial com;
  com.open("COM5");

  // TX and RX strings
  std::string tx_str = "G 1 9\n";
  std::string rx_str;

  // temporary storage
  char buff[2];
  do
  {
    // Send TX string
		com.write(tx_str.c_str(), tx_str.length());
    Sleep(10); // wait for ADC conversion, etc. May not be needed?
  
    rx_str = "";
    // start timeout count
    double start_time = cv::getTickCount();

    buff[0] = 0;
		// Read 1 byte and if an End Of Line then exit loop
    // Timeout after 1 second, if debugging step by step this will cause you to exit the loop
    while (buff[0] != '\n' && (cv::getTickCount() - start_time) / cv::getTickFrequency() < 1.0)
    {
      if (com.read(buff, 1) > 0)
      {
        rx_str = rx_str + buff[0];
      }
    }

    printf ("\nRX: %s", rx_str.c_str());
    
  } 
  while (1);
}

////////////////////////////////////////////////////////////////
// Display Image on screen
////////////////////////////////////////////////////////////////
void do_image()
{
  cv::Mat im;

  im = cv::imread("BCIT.jpg");

  srand(time(0));

  for (int i = 0; i < 500; i++)
  {
    float radius = 50 * rand() / RAND_MAX;
    cv::Point center = cv::Point(im.size().width*rand() / RAND_MAX, im.size().height*rand() / RAND_MAX);
    
    cv::circle(im, center, radius, cv::Scalar(200, 200, 200), 1, cv::LINE_AA);
    
    im.at<char>(i,i) = 255;
    
    cv::imshow("Image", im);
    cv::waitKey(1);
  }
}

////////////////////////////////////////////////////////////////
// Display Video on screen
////////////////////////////////////////////////////////////////
void do_video()
{
  cv::VideoCapture vid;

  vid.open(0);

  if (vid.isOpened() == TRUE)
  {
    do
    {
      cv::Mat frame, edges;
      vid >> frame;
      if (frame.empty() == false)
      {
        cv::cvtColor(frame, edges, cv::COLOR_BGR2GRAY);
        cv::GaussianBlur(edges, edges, cv::Size(7, 7), 1.5, 1.5);
        cv::Canny(edges, edges, 0, 30, 3);
        cv::imshow("edges", edges);
      }
    }
    while (cv::waitKey(10) != ' ');
  }      
}		
    

////////////////////////////////////////////////////////////////
// Demo client server communication
////////////////////////////////////////////////////////////////
Server serv;

// Start TCP server
void serverfunc()
{
  serv.start(4618);
}

// Send image to TCP server
void serverimagefunc()
{
  cv::VideoCapture vid;

  vid.open(0);

  if (vid.isOpened() == TRUE)
  {
    do
    {
      cv::Mat frame;
      vid >> frame;
      serv.set_txim(frame);
    }
    while (cv::waitKey(10) != ' ');
  }
}

void clientserver()
{
  std::string str;
  cv::Mat im;

  // Start server
  std::thread t1(&serverfunc);
  t1.detach();

  // Start image send to server
  std::thread t2(&serverimagefunc);
  t2.detach();

  // Wait until server starts up (webcam is slow)
  Sleep(2000);

  // connect
  Client client(4618, "127.0.0.1");

  // Wait until server starts up (webcam is slow)
  Sleep(500);

  client.tx_str("cmd");
  do
  {
    client.rx_str(str);
    if (str.length() > 0)
    {
      std::cout << "\nClient Rx: " << str;
    }
  } while (str.length() == 0);

  int count = 0;
  while (1)
  {
    client.tx_str("im");

    if (client.rx_im(im) == TRUE)
    {
      if (im.empty() == false)
      {
        count++;
        std::cout << "\nImage received: " << count;
        cv::imshow("rx", im);
        cv::waitKey(100);
      }
    }
  }
}
bool get_analog(int type, int channel, int& result, int& perc_result)
{
    //temp variable for per_result calculation
    int res;
    //curr.get_data(type, channel, result);
    res = result;
    perc_result = (res * 100) / 1024;
    return false;
}

void analog_test()
{
    //curr.init_com(5);
    while (1)
    {
        int x_per;
        int x_value;
        int y_value;
        int y_per;
        get_analog(ANALOG, 9, x_value, x_per);
        get_analog(ANALOG, 15, y_value, y_per);
        std::string x_str = std::to_string(x_value);
        std::string y_str = std::to_string(y_value);
        std::string x_per_str = std::to_string(x_per);
        std::string y_per_str = std::to_string(y_per);
        std::cout << "ANALOG TEST: CH9 = " + x_str + " (" + x_per_str + "%) CH15 = " + y_str + " (" + y_per_str + "%)" << std::endl;
    }
}

void print_menu()
{
	std::cout << "\n***********************************";
	std::cout << "\n* ELEX4618 Template Project";
	std::cout << "\n***********************************";
	std::cout << "\n(1) Test serial COM communication";
	std::cout << "\n(2) Show image manipulation";
	std::cout << "\n(3) Show video manipulation";
	std::cout << "\n(4) Test client/server communication";
	std::cout << "\n(0) Exit";
	std::cout << "\nCMD> ";
}

int main(int argc, char* argv[])
{
  
	int cmd = -1;
	//do
	//{
		print_menu();
		std::cin >> cmd;
		switch (cmd)
		{
		case 1: test_com(); break;
		case 2: do_image(); break;
		case 3: do_video(); break;
		case 4: clientserver(); break;
        case 5:
           // CSketch test;
            //test.run(); 
            break;
        case 6: 
            srand(time(NULL));
            CPong game;
            game.start
            ();
            break;
		}
	//} while (cmd != 0);
}
