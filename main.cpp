#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    cv::VideoCapture reader("SDR_sample_footage.mp4");
    if (!reader.isOpened()) {
        std::cerr << "Cannot load video!" << std::endl;
        return -1;
    }

    cv::Mat SDR_frame;
    while(true){

        bool isSuccess = reader.read(SDR_frame);
        if (!isSuccess) {
            break;
        } else {
        cv::imshow("SDR FRAME", SDR_frame);
        }

        if (cv::waitKey(10) == 27) { // Press ESC to quit
            break;
        }
    }

    reader.release();
    cv::destroyAllWindows();

    return 0;
}