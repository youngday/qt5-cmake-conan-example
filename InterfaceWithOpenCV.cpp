#include <iostream>
#include <numeric>
#include <array>

#include "NumCpp.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "xtensor/xarray.hpp"
#include "xtensor/xio.hpp"
#include "xtensor/xview.hpp"
#include <xtensor/xmanipulation.hpp>
#include <xtensor/xtensor.hpp>



#include "xtensor/xbuilder.hpp"
#include "xtensor/xcomplex.hpp"
#include "xtensor/xrandom.hpp"
#include "xtensor-blas/xblas.hpp"
#include "xtensor-blas/xlapack.hpp"
#include "xtensor-blas/xlinalg.hpp"

#include "main.h"
#include "Logger.h"
using namespace std;
extern Logger logger;
extern  stringstream logout;
constexpr nc::uint32 NUM_ROWS = 512;
constexpr nc::uint32 NUM_COLS = 512;

using namespace std;

int numcpp_test()
{


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

//   // display the OpenCV Mat
//   cv::namedWindow("Display window",
//                   cv::WINDOW_AUTOSIZE); // Create a window for display.
//   cv::imshow("Display window",
//              cvArray); // Show our image inside it.
//                        // cv::waitKey(0); // Wait for a keystroke in the window

  // tranpose the Mat with OpenCV
  auto transposedCvArray = cv::Mat(cvArray.cols, cvArray.rows, CV_8SC1);
  cv::transpose(cvArray, transposedCvArray);

//   // display the transposed Mat
//   cv::namedWindow("Display window",
//                   cv::WINDOW_AUTOSIZE); // Create a window for display.
//   cv::imshow("Display window",
//              transposedCvArray); // Show our image inside it.
//                                  // cv::waitKey(0); // Wait for a keystroke in
//                                  // the window

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
    logger.debug(logout.str());
  }


logout << "array testing++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.\n";
logger.debug(logout.str());

auto inTolerance = 1e-5 ;
nc::NdArray<double> B = { {1,-2,1}, {0,2,-8},{-4,5,9} };
cout<<B;
nc::NdArray<double> b = { {0,8,-9} };

cout<<b;
auto bt=nc::transpose(b);
cout<<bt;
auto x=nc::linalg::solve(B,bt);
cout<<x;
auto check=nc::dot(B,x);
cout<<check;


//auto y=nc::allclose(dot(a, x), b);
logout.str("");
logout <<"x=\n" <<x;
logger.debug(logout.str());
 
//  logout.str("");
// logout <<"y=\n" <<y;
// logger.debug(logout.str());

//  logout.str("");
// logout <<"check=\n" <<check;
// logger.debug(logout.str());




xt::xarray<double> xtB{ {1,-2,1}, {0,2,-8},{-4,5,9} };
cout<<"xtB"<<"\n";
cout<<xtB<<"\n";

xt::xarray<double> xtb({ {0,8,-9} });
cout<<"xtb"<<"\n";

//auto xtbt = xt::transpose(xtb, {1,0});
auto xtbt = xt::transpose(xtb);
cout<<"xtbt"<<"\n";
cout<<xtbt<<"\n";
auto xtx=xt::linalg::solve(xtB,xtbt);
cout<<"xtx"<<"\n";
cout<<xtx<<"\n";
auto xtcheck=xt::linalg::dot(xtB,xtx);
cout<<"xtcheck"<<"\n";
cout<<xtcheck<<"\n";



logout.str("");
logout <<"\n" <<xtx;
logger.debug(logout.str());

xt::xtensor<double, 2> xtt({{1.01, 2.0e+0, 3.0}, {2.0, 5.0, 7.0}, {2.0, 5.0, 7.0}});
logout.str("");
logout <<"\n" <<xtt;
logger.debug(logout.str());

  cout << "end." << endl;

  return 0;
}
