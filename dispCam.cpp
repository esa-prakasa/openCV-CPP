//This code is used to access the video frame from webcam. 

#include "opencv2/highgui/highgui.hpp"

using namespace cv;

int main(int, char**)
{
    VideoCapture cap0(0);
    if(!cap0.isOpened())
        return -1;

    Mat frame0;

    for(;;)
    {
      system ("clear");
      cap0 >> frame0;
      imshow("Webcam view", frame0);
      if(waitKey(30) >= 0) break;
    }
    return 0;
}


