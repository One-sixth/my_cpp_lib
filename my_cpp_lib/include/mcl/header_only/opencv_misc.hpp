/*
* opencv�����
*/

#pragma once
#include <opencv2/opencv.hpp>


// ��� cv::Mat ��ռ�ֽ���
inline static
size_t get_cv_im_mem_size(const cv::Mat& m)
{
	return m.rows * m.cols * m.elemSize() * m.elemSize1();
}
