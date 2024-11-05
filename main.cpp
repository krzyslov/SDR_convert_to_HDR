#include <iostream>
#include <opencv2/opencv.hpp>


// convert function template
cv::Mat convertSDRtoHDR(const cv::Mat& frame)
{
    return frame;
}

int main()
{
    cv::VideoCapture reader("SDR_sample_footage.mp4");
    if (!reader.isOpened()) {
        std::cerr << "Cannot load video!" << std::endl;
        return -1;
    }

    // Get template frame data so I can create a HDR frame template
    int frameWidth = static_cast<int>(reader.get(cv::CAP_PROP_FRAME_WIDTH));
    int frameHeight = static_cast<int>(reader.get(cv::CAP_PROP_FRAME_HEIGHT));
    int fps = static_cast<int>(reader.get(cv::CAP_PROP_FPS));

    cv::VideoWriter writer("hdr_video.mp4", cv::VideoWriter::fourcc('m', 'p', '4', 'v'), fps, cv::Size(frameWidth, frameHeight));
    if (!writer.isOpened()) {
        std::cerr << "Cannot open file needed to save the video!" << std::endl;
        return -1;
    }


    cv::Mat SDR_frame;
    while(true){

        bool isSuccess = reader.read(SDR_frame);
        if (!isSuccess) {
            break;
        }

        cv::Mat HDR_frame = convertSDRtoHDR(SDR_frame);
        cv::imshow("SDR FRAME", SDR_frame);
        cv::imshow("HDR_Frame", HDR_frame);
        

        if (cv::waitKey(10) == 27) { // Press ESC to quit
            break;
        }
    }

    reader.release();
    cv::destroyAllWindows();

    return 0;
}