#ifndef FILTERS
#define FILTERS

#include "../../lib/CImg.templ"
#include "t2-histogram.h"

using namespace std;
using namespace cimg_library;

CImg<int>& applyExponentialPDF(CImg<int> &original, int Gmin, Histogram &histogram);
CImg<int>& applyLaplacianFilter(CImg<int> &original, int maskNumber, Histogram &histogram);
CImg<int>& applyLaplacianFilterOptimised(CImg<int> &original, Histogram &histogram);
CImg<int>& applyRobertsOperatorFilter(CImg<int> &original, Histogram &histogram);

#endif //FILTERS
