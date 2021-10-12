/*
* opencv杂项工具
*/

#pragma once
#include <opencv2/opencv.hpp>


// 获得 cv::Mat 所占字节数
inline static
size_t get_cv_im_mem_size(const cv::Mat& m)
{
	return m.rows * m.cols * m.elemSize() * m.elemSize1();
}
