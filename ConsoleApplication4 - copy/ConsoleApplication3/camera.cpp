#include <opencv2/opencv.hpp>  
#include <iostream>
#include <time.h> 
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <stdlib.h> 
#include "cxcore.h"
#include "cv.h"
#include "highgui.h"
#include <time.h> 
#include <string>
#include <io.h>
#include <direct.h>

// 这几个依赖库文件必须要添加，
// 因为这些是OpenCV所使用的第三方库  
#pragma comment( lib, "IlmImf.lib")
#pragma comment( lib, "libjasper.lib")
#pragma comment( lib, "libjpeg.lib")
#pragma comment( lib, "libpng.lib")
#pragma comment( lib, "libtiff.lib")
#pragma comment( lib, "zlib.lib")

#pragma comment( lib, "opencv_calib3d2410.lib" )
#pragma comment( lib, "opencv_contrib2410.lib" )
#pragma comment( lib, "opencv_core2410.lib" )
#pragma comment( lib, "opencv_features2d2410.lib" )
#pragma comment( lib, "opencv_flann2410.lib" )
#pragma comment( lib, "opencv_gpu2410.lib" )
#pragma comment( lib, "opencv_highgui2410.lib" )
#pragma comment( lib, "opencv_imgproc2410.lib" )
#pragma comment( lib, "opencv_legacy2410.lib" )
#pragma comment( lib, "opencv_ml2410.lib" )
#pragma comment( lib, "opencv_nonfree2410.lib" )
#pragma comment( lib, "opencv_objdetect2410.lib" )
#pragma comment( lib, "opencv_ocl2410.lib" )
#pragma comment( lib, "opencv_photo2410.lib" )
#pragma comment( lib, "opencv_stitching2410.lib" )
#pragma comment( lib, "opencv_superres2410.lib" )
#pragma comment( lib, "opencv_ts2410.lib" )
#pragma comment( lib, "opencv_video2410.lib" )
#pragma comment( lib, "opencv_videostab2410.lib" )

#pragma comment(lib,"User32.lib")
#pragma comment( lib, "vfw32.lib" )  
#pragma comment( lib, "comctl32.lib" ) 

using namespace std;
using namespace cv;



using namespace cv;

void main()
{

	IplImage *img = NULL;
	IplImage *imgChannel[4] = { 0, 0, 0, 0 };
	IplImage *imgColor[4] = { 0, 0, 0, 0 };
	//int cm;
	//std::cin>>cm;
	CvCapture* pCapture = cvCreateCameraCapture(1);
	CvSize size = cvSize(1280, 720);
	cvSetCaptureProperty(pCapture, CV_CAP_PROP_FRAME_WIDTH, size.width);
	cvSetCaptureProperty(pCapture, CV_CAP_PROP_FRAME_HEIGHT, size.height);
	time_t t;

	char outImageName[40];
	cvNamedWindow("vedio", 1);
	cvNamedWindow("channel Blue", 1);
	cvNamedWindow("channel Green", 1);
	cvNamedWindow("channel Red", 1);
	while (1)
	{
		img = cvQueryFrame(pCapture);
		if (!img) break;

		cvShowImage("vedio", img);
		for (int i = 0; i < img->nChannels; i++)
		{
			imgChannel[i] = cvCreateImage(cvGetSize(img), img->depth, 1);
			imgColor[i] = cvCreateImage(cvGetSize(img), img->depth, 3);
			cvZero(imgColor[i]);
		}
		cvSplit(img, imgChannel[0], imgChannel[1], imgChannel[2], imgChannel[3]);
		cvMerge(imgChannel[0], NULL, NULL, NULL, imgColor[0]);
		cvMerge(NULL, imgChannel[1], NULL, NULL, imgColor[1]);
		cvMerge(NULL, NULL, imgChannel[2], NULL, imgColor[2]);


		char c = cvWaitKey(100);
		if (c == 27)  break;
		else if (c == 114)
		{
			t = time(0);

			sprintf(outImageName, "redcap%d.jpg", t);
			cvSaveImage(outImageName, imgColor[2]);
			printf(" imagesave success！\n");
		}
		else if (c == 98)
		{
			t = time(0);

			sprintf(outImageName, "bluecap%d.jpg", t);
			cvSaveImage(outImageName, imgColor[0]);
			printf(" imagesave success！\n");
		}
		else if (c == 103)
		{
			t = time(0);

			sprintf(outImageName, "greencap%d.jpg", t);
			cvSaveImage(outImageName, imgColor[1]);
			printf(" imagesave success！\n");
		}
		else if (c == 111)
		{
			t = time(0);
			cout << "ejadea" << endl;
			sprintf(outImageName, "origincap%d.jpg", t);
			cvSaveImage(outImageName, img);
			printf(" imagesave success！\n");
		}

		cvShowImage("channel Blue", imgColor[0]);
		cvShowImage("channel Green", imgColor[1]);
		cvShowImage("channel Red", imgColor[2]);
		cvReleaseImage(&imgColor[0]);
		cvReleaseImage(&imgColor[1]);
		cvReleaseImage(&imgColor[2]);
		cvReleaseImage(&imgChannel[0]);
		cvReleaseImage(&imgChannel[1]);
		cvReleaseImage(&imgChannel[2]);


	}

	cvReleaseImage(&img);
	cvReleaseImage(&imgColor[0]);
	cvReleaseImage(&imgColor[1]);
	cvReleaseImage(&imgColor[2]);
	cvReleaseImage(&imgChannel[0]);
	cvReleaseImage(&imgChannel[1]);
	cvReleaseImage(&imgChannel[2]);

	cvDestroyWindow("video");
	cvDestroyWindow("channel Blue");
	cvDestroyWindow("channel Green");
	cvDestroyWindow("channel Red");
}
