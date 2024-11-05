#include <iostream>
#include <opencv2/opencv.hpp>
#include <immintrin.h> // Header for SIMD (AVX)
#include "avx_mathfun.h" // for 256log and 256exp function

cv::Mat convertSDRtoHDR(const cv::Mat& frame)
{
    cv::Mat hdrFrame;

    frame.convertTo(hdrFrame, CV_32F, 1.0 / 255.0); // Normalization to 0-1

    float gamma = 2.2f; // Gamma corection factor

    int numPixels = hdrFrame.rows * hdrFrame.cols * hdrFrame.channels();

    float* pixelPtr = reinterpret_cast<float*>(hdrFrame.data);

    __m256 gammaVec = _mm256_set1_ps(gamma);
    for (int i = 0; i < numPixels; i += 8) {
        __m256 pixelVec = _mm256_load_ps(&pixelPtr[i]);
        pixelVec = _mm256_max_ps(pixelVec, _mm256_set1_ps(1e-8f)); // Avoiding log(0)
        __m256 logVec = log256_ps(pixelVec);
        __m256 mulVec = _mm256_mul_ps(gammaVec, logVec);
        __m256 resultVec = exp256_ps(mulVec);
        _mm256_storeu_ps(&pixelPtr[i], resultVec);
    }

    // Factor for Brightness range scaling for HDR
    float hdrScale = 1.5f;
    // Scaling
    cv::multiply(hdrFrame, hdrScale, hdrFrame);

    // Limiting pixel values ​​to 0-1 (to avoid excessive brightness)
    cv::threshold(hdrFrame, hdrFrame, 1.0, 1.0, cv::THRESH_TRUNC);

    cv::Mat hdrFrame8U;
    hdrFrame.convertTo(hdrFrame8U, CV_8U, 255); 

    return hdrFrame8U;
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