#include <iostream>
#include <numeric>
#include <array>

#include "NumCpp.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "xtensor/xarray.hpp"
#include "xtensor/xio.hpp"
#include "xtensor/xview.hpp"
#include <xtensor/xtensor.hpp>

#include "main.h"

constexpr nc::uint32 NUM_ROWS = 512;
constexpr nc::uint32 NUM_COLS = 512;

using namespace std;

int numcpp_test()
{
  stringstream logout;
  auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  console_sink->set_level(spdlog::level::debug);
  console_sink->set_pattern("[numcpp] [%^%l%$] %v");

  auto daily_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>(
      "./log/numcpp.txt", 2, 30);
  daily_sink->set_level(spdlog::level::debug);
  spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%t] [%l] %v");

  spdlog::logger logger("numcpp", {console_sink, daily_sink});
  logger.set_level(spdlog::level::debug);
  logger.flush_on(spdlog::level::debug);
  logger.warn("this should appear in both console and file");
  logger.info(
      "this message should not appear in the console, only in the file");

  // create a ramp image with NumCpp
  constexpr auto numHalfCols = NUM_COLS / 2; // integer division
  auto ncArray = nc::NdArray<nc::uint8>(NUM_ROWS, NUM_COLS);
  for (nc::uint32 row = 0; row < ncArray.numRows(); ++row)
  {
    auto begin = ncArray.begin(row);
    std::iota(begin, begin + numHalfCols, nc::uint8{0});

    auto rbegin = ncArray.rbegin(row);
    std::iota(rbegin, rbegin + numHalfCols, nc::uint8{0});
  }
  // logout<<"ncArray"<<ncArray<<"\n";
  //  logout<<"ncArray"<<"\n";
  // logger.info(logout.str());

  // convert to OpenCV Mat
  auto cvArray =
      cv::Mat(ncArray.numRows(), ncArray.numCols(), CV_8SC1, ncArray.data());

  // display the OpenCV Mat
  cv::namedWindow("Display window",
                  cv::WINDOW_AUTOSIZE); // Create a window for display.
  cv::imshow("Display window",
             cvArray); // Show our image inside it.
                       // cv::waitKey(0); // Wait for a keystroke in the window

  // tranpose the Mat with OpenCV
  auto transposedCvArray = cv::Mat(cvArray.cols, cvArray.rows, CV_8SC1);
  cv::transpose(cvArray, transposedCvArray);

  // display the transposed Mat
  cv::namedWindow("Display window",
                  cv::WINDOW_AUTOSIZE); // Create a window for display.
  cv::imshow("Display window",
             transposedCvArray); // Show our image inside it.
                                 // cv::waitKey(0); // Wait for a keystroke in
                                 // the window

  // convert the transposed OpenCV Mat to a NumCpp array
  auto transposedNcArray = nc::NdArray<nc::uint8>(
      transposedCvArray.data, transposedCvArray.rows, transposedCvArray.cols);

  // make sure the two transposed arrays are the same
  if (nc::array_equal(transposedNcArray, ncArray.transpose()))
  {
    logout << "Arrays are equal.\n";
    //  cout<<ncArray<<"\n";
    // logout<<"ncArray"<<"\n";
    logger.info(logout.str());
  }
  else
  {
    logout << "Arrays are not equal.\n";
    logger.info(logout.str());
  }

  // construct some NumCpp arrays
  auto ncA = nc::random::randInt<int>({5, 5}, 0, 10);
  auto ncB = nc::random::randInt<int>({5, 5}, 0, 10);

  cout << "ncA:\n"
       << ncA << std::endl;
  cout << "ncB:\n"
       << ncB << std::endl;

  // add the two NumCpp arrays for a sanity check
  auto ncC = ncA + ncB;

  cout << "ncC:\n"
       << ncC << std::endl;

  xt::xarray<double> arr1{{1.0, 2.0, 3.0}, {2.0, 5.0, 7.0}, {2.0, 5.0, 7.0}};

  cout << "arr1"
       << "\n";
  cout << arr1 << "\n";

  xt::xarray<double> arr2{5.0, 6.0, 7.0};

  cout << "arr2"
       << "\n";
  cout << arr2 << "\n";

  xt::xarray<double> res = xt::view(arr1, 1) + arr2;

  cout << "res"
       << "\n";
  cout << res << "\n";

  xt::xtensor<double, 2> arr3({{1.01, 2.0e+0, 3.0}, {2.0, 5.0, 7.0}, {2.0, 5.0, 7.0}});

  // std::array<size_t, 3> shape = { 3, 2, 4 };
  // xt::xtensor<double, 3> arr3(shape);
  cout << "arr3"
       << "\n";
  cout << arr3 << "\n";

  cout << "end." << endl;

  return 0;
}
