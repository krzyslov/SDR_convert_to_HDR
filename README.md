# SDR to HDR Conversion

This project demonstrates the conversion of Standard Dynamic Range (SDR) video to High Dynamic Range (HDR) using C++ with OpenCV and SIMD AVX optimization. The process includes tone mapping, color space transformation to Rec. 2020, gamma correction, and SIMD AVX optimization to achieve high performance and improved visual quality.

## Features

- **Color Space Conversion to Rec. 2020**: Converts the color space from Rec. 709 (used in SDR) to Rec. 2020, a wider color space standard for HDR, allowing for more vivid and realistic colors.
- **Gamma Correction with SIMD AVX**: Implements gamma correction using SIMD AVX instructions for efficient parallel processing of pixels. This approach speeds up the gamma correction step by processing multiple pixels simultaneously, enhancing performance especially on large video frames.
- **16-Bit Depth Support**: Scales the output to 16-bit depth, preserving more detail in bright and dark regions of the video.

## Installation

1. **Install OpenCV**: Make sure OpenCV is installed and configured in your environment.
2. **Clone this repository**:
   ```bash
   git clone https://github.com/krzyslov/SDR_convert_to_HDR.git
   cd SDR_convert_to_HDR
   mkdir build
   cd build
   cmake ..
   make
   ```
3. **Usage**: Run the compiled executable:
   ```bash
   ./SDR_to_HDR_converter
   ```
   Remember that your `SDR_sample_footage.mp4` file needs to be in the same directory as the executable.

## Code Overview

- **`convertSDRtoHDR`**: Main function for converting SDR frames to HDR. This function performs gamma correction, tone mapping, and scaling to HDR brightness levels.
- **`convertToRec2020`**: Converts the color space from Rec. 709 (SDR) to Rec. 2020 (HDR).
- **SIMD AVX Optimization**: Uses SIMD AVX instructions for parallel processing of pixel data during gamma correction, significantly improving performance on supported hardware.
- **`mathfun.h` Library**: Utilizes the `mathfun.h` library ([available here](https://github.com/reyoung/avx_mathfun)) for SIMD-optimized logarithmic and exponential functions, enabling efficient `log` and `exp` calculations as part of the HDR transformation.

## Dependencies

- **OpenCV**: Required for image processing and tone mapping functions. Install it via package manager or build from source.
- **CMake**: Used to build the project.
