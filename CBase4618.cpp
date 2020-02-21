#include "stdafx.h"
#include "CBase4618.h"
#include <chrono>
#include <thread>
#include "CPong.h"

CBase4618::CBase4618()
{
}

CBase4618::~CBase4618()
{
}

void CBase4618::run()
{
	int _esc;
	do
	{
		auto end_time = std::chrono::system_clock::now() + std::chrono::milliseconds(33);
		update();
		draw();
		_esc = cv::waitKey(10);
		std::this_thread::sleep_until(end_time);
	} while (_esc != 113);
}