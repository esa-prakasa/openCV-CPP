#include "opencv2/highgui/highgui.hpp"
//#include <iostream>
//#include <string>
#include <stdio.h>
//#include <math.h>
//#include <unistd.h>
//#include <stdlib.h>

//#include <math.h>
//#include <unistd.h>
//#include <stdlib.h>

//#include <iostream>
//#include <string>



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

    double secondsOld, secondsNew;
    time_t start = time(0);
    secondsOld = 0;

    for(;;)
    {

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

      double secondsNew = difftime( time(0), start);

      float Racc = 0;
      float Gacc = 0;
      float Bacc = 0;
      float Ravg, Gavg, Bavg;
      int totalPix = frame1.rows*frame1.cols;

      if ((secondsNew-secondsOld)==1){
          system ("clear");

          for (int i=0; i<frame1.rows; i++){
              for (int j=0; j<frame1.cols; j++){
                  Bacc = Bacc + frame1.at<Vec3b>(i,j)[0];
                  Gacc = Gacc + frame1.at<Vec3b>(i,j)[1];
                  Racc = Racc + frame1.at<Vec3b>(i,j)[2];
              }
          }

          Ravg = Racc/totalPix;
          Gavg = Gacc/totalPix;
          Bavg = Bacc/totalPix;

          printf("   \n");
          printf ("       %.f seconds R = %2.1f G = %2.1f B = %2.1f \n", secondsNew, Ravg, Gavg, Bavg);
          printf("   \n");
      }




      rectangle( frame0,
                 Point(midCols - roiSizeDiv2, midRows + roiSizeDiv2),
                 Point(midCols + roiSizeDiv2, midRows - roiSizeDiv2),
                 Scalar( 0, 255, 255 ),
                 1);

      imshow("Webcam view", frame0);
      imshow("ROI view",frame1);

      secondsOld = secondsNew;

      if(waitKey(30) >= 0) break;
    }
    return 0;
}


