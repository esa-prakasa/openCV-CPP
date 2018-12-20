#include "opencv2/highgui/highgui.hpp"

using namespace cv;

int main(int, char**)
{
    VideoCapture cap0(0);
    if(!cap0.isOpened())
        return -1;

    Mat frame0;
    int roiSize = 200;
    int roiSizeDiv2 = floor(roiSize/2);
    Mat frame1(roiSize, roiSize, CV_8UC3);

    cap0 >> frame0;
    int midCols = floor(frame0.cols/2);
    int midRows = floor(frame0.rows/2);

    for(;;)
    {
      system ("clear");
      cap0 >> frame0;

      for(int i=0;i<2*roiSizeDiv2;i++){
          int k = i - roiSizeDiv2 + midRows;
          for (int j=0;j<2*roiSizeDiv2;j++){
              int l = j - roiSizeDiv2 + midCols;
              frame1.at<Vec3b>(i,j)[0] = frame0.at<Vec3b>(k,l)[0];
              frame1.at<Vec3b>(i,j)[1] = frame0.at<Vec3b>(k,l)[1];
              frame1.at<Vec3b>(i,j)[2] = frame0.at<Vec3b>(k,l)[2];
          }
      }

      rectangle( frame0,
                 Point(midCols - roiSizeDiv2, midRows + roiSizeDiv2),
                 Point(midCols + roiSizeDiv2, midRows - roiSizeDiv2),
                 Scalar( 0, 255, 255 ),
                 1);

      imshow("Webcam view", frame0);
      imshow("ROI view",frame1);
      if(waitKey(30) >= 0) break;
    }
    return 0;
}








//#include "/home/esa/opencv/opencv-3.0.0-alpha/modules/highgui/include/opencv2/highgui.hpp"



//using namespace std;



//#include "opencv2/core/core.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include <opencv2/features2d/features2d.hpp>
//#include <iostream>
//#include <string>
//#include <stdio.h>
//#include <math.h>
//#include <unistd.h>
//#include <stdlib.h>

//#include <math.h>
//#include <unistd.h>
//#include <stdlib.h>

//#include <iostream>
//#include <string>
