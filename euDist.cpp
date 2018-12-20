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


    // merah: RGB = 128  87  97
    // hijau: RGB = 109 139  92
    // biru:  RGB =  77 130 154

    float pattern[3][5];
    float distVal[5];
    String colourNm [5];

    pattern[0][0] =  97; pattern[0][1] = 87; pattern[0][2] =  128;
    pattern[1][0] =  92; pattern[1][1] = 139; pattern[1][2] = 109;
    pattern[2][0] = 154; pattern[2][1] = 130; pattern[2][2] =  77;

    colourNm[0] = "Merah";
    colourNm[1] = "Hijau";
    colourNm[2] = "Biru";



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

          distVal[0] = (pattern[0][0] - Bavg)*(pattern[0][0] - Bavg) + (pattern[0][1] - Gavg)*(pattern[0][1] - Gavg) + (pattern[0][2] - Ravg)*(pattern[0][2] - Ravg);
          distVal[1] = (pattern[1][0] - Bavg)*(pattern[1][0] - Bavg) + (pattern[1][1] - Gavg)*(pattern[1][1] - Gavg) + (pattern[1][2] - Ravg)*(pattern[1][2] - Ravg);
          distVal[2] = (pattern[2][0] - Bavg)*(pattern[2][0] - Bavg) + (pattern[2][1] - Gavg)*(pattern[2][1] - Gavg) + (pattern[2][2] - Ravg)*(pattern[2][2] - Ravg);


          float distMin = 1e5;
          int selctI;
          for (int i=0; i<3; i++){
              if (distVal[i]<distMin){
                      distMin = distVal[i];
                      selctI = i;
              }
          }
          printf ("       %s \n", colourNm[selctI].c_str());

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






