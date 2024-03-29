#ifndef MORPHOLOGICAL_OPERATIONS
#define MORPHOLOGICAL_OPERATIONS

#include <vector>
#include "lib/CImg.templ"


using namespace std;
using namespace cimg_library;


struct Point{
    Point(int x, int y);
    int x, y;
};

struct MorphMask{
    vector<Point> hit;
    vector<Point> miss;
};

MorphMask getNormalMask(int number);
MorphMask getHMTMask(int number);

CImg<int>& applyUnion(CImg<int> &image1, CImg<int> &image2);
CImg<int>& applyIntersection(CImg<int> &image1, CImg<int> &image2);
CImg<int>& applyDifference(CImg<int> &image1, CImg<int> &image2);
CImg<int>& applyComplement(CImg<int> &image1);

CImg<int>& applyErosion(CImg<int> &original, MorphMask mask);
CImg<int>& applyDilation(CImg<int> &original, MorphMask mask);
CImg<int>& applyOpening(CImg<int> &original, MorphMask mask);
CImg<int>& applyClosing(CImg<int> &original, MorphMask mask);
CImg<int>& applyHMT(CImg<int> &original, MorphMask mask);

CImg<int>& applyOuterBorder(CImg<int> &original, int maskNumber);
CImg<int>& applyInnerBorder(CImg<int> &original, int maskNumber);
CImg<int>& applyInnerOuterBorder(CImg<int> &original, int maskNumber);

CImg<int>& applyFilling(CImg<int> &original, int x, int y, int maskNumber);
CImg<int>& applyRemoving(CImg<int> &original, int x, int y, int maskNumber);


#endif //MORPHOLOGICAL_OPERATIONS
