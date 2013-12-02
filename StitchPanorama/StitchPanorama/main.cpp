#include <iostream>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/stitching/stitcher.hpp>
#include "PragmaLibs.h"


int main(int argc, char *argv[])
{
	std::vector<cv::Mat> imgs;
	bool try_use_gpu = true;
	int i;

	for ( i = 1; i < argc; i++ ) {
		cv::Mat img = cv::imread( argv[ i ], 1 );
		if ( img.empty() ) {
			std::cerr << "can not read a image: " << argv[ i ] << std::endl;
			return -1;
		}
		imgs.push_back( img );
	}

	cv::Mat result;
	cv::Stitcher stitcher = cv::Stitcher::createDefault( try_use_gpu );
	cv::Stitcher::Status status = stitcher.stitch(imgs, result);
	if ( status != cv::Stitcher::OK ) {
		std::cerr << "can not make a panorama" << std::endl;
		return -2;
	}

#ifdef _WIN32
	cv::namedWindow( "panorama", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO );
	cv::imshow( "panorama", result );
	cv::waitKey(0);
#endif
	cv::imwrite( "ret-panorama.jpg", result );

	return 0;
}
