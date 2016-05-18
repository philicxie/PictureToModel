// C++ 标准库
#include <iostream>
#include <string>
using namespace std;

// OpenCV 库
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

// PCL 库
//#include <pcl/io/pcd_io.h>
//#include <pcl/point_types.h>

using namespace cv;

int main( int argc, char **argv)
{
	Mat image;
	image = imread( argv[1], 1 );
    	return 0;
}
