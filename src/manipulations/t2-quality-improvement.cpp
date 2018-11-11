#include <iostream>
#include <vector>
#include <algorithm>
#include "../../lib/CImg.templ"
#include "t0-other.h"
#include "t2-quality-improvement.h"
#include "t2-histogram.h"

using namespace std;
using namespace cimg_library;

void applyExponentialPDF(CImg<int> &original, CImg<int> &edited, char *gm, Histogram &histogram){
    float gmin = atof(gm);
    for (int c = 0; c < original.spectrum(); c++) {

        float alpha = 0.014; //set custom alpha, different than parameter

        int* improvedColors = new int[256];
        for (int m = 0; m < 256; m++) { //apply histogram modification
            cout << "m: " << m << " " << gmin - 1.0/alpha * log(1.0 - (1.0/(original.width()*original.height())) * histogram.cumulative[c][m]) << endl;

            improvedColors[m] = gmin - 1.0/alpha *
                    log(1.0 - (1.0/(original.width()*original.height())) * histogram.cumulative[c][m]);
            improvedColors[m] = normalized(improvedColors[m]);
        }

        for (int x = 0; x < original.width(); x++) { //apply to image
            for (int y = 0; y < original.height(); y++) {
                edited(x, y, 0, c) = improvedColors[original(x, y, 0, c)];
            }
        }
    }

    Histogram newHistogram = Histogram(edited);
    //newHistogram.displayUniformValues(0);
    ((*histogram.getUniformHistogramGraph(0, false)).append(*newHistogram.getUniformHistogramGraph(0, false), 'x', 1)).display("HISTOGRAM", false); //show difference in histogram
    histogram.getUniformHistogramGraph(0, false)->save("original_histogram.png");
    newHistogram.getUniformHistogramGraph(0, false)->save("edited_histogram.png");
}

void applyLaplacianFilter(CImg<int> &original, CImg<int> &edited, char* m, Histogram &histogram){
    float maskNumber = atoi(m);

    int filterMask1[3][3] = {-1, -1, -1, -1, 8, -1, -1, -1, -1};
    int filterMask2[3][3] = {0, -1, 0, -1, 4, -1, 0, -1, 0};
    int filterMask3[3][3] = {1, -2, 1, -2, 4, -2, 1, -2, 1};

    int filterMask[3][3];
    if(maskNumber == 1) {copy(&filterMask1[0][0], &filterMask1[0][0]+9, &filterMask[0][0]);}
    else if(maskNumber == 2){copy(&filterMask2[0][0], &filterMask2[0][0]+9, &filterMask[0][0]);}
    else if(maskNumber == 3){copy(&filterMask3[0][0], &filterMask3[0][0]+9, &filterMask[0][0]);}
    else {cout << "Wrong mask value. \nType --help to view information about available commands." << endl; exit(0);}

    for (int x = 1; x < original.width() - 1; x++)
    {
        for (int y = 1; y < original.height() - 1; y++)
        {
            for (int c = 0; c < original.spectrum(); c++)
            {
                int p = 0;
                int q = 0;
                int pixelValue = 0;

                for (int i = x - 1; i < x + 2; i++)
                {
                    p = 0;
                    for (int j = y - 1; j < y + 2; j++)
                    {
                        pixelValue += original(i, j, 0, c) * filterMask[p][q];
                        p++;
                    }
                    q++;
                }
                edited(x, y, 0, c) = normalized(pixelValue);
            }
        }
    }
}

void applyLaplacianFilterOptimised(CImg<int> &original, CImg<int> &edited, Histogram &histogram){
    for (int x = 1; x < original.width() - 1; x++)
    {
        for (int y = 1; y < original.height() - 1; y++)
        {
            for (int c = 0; c < original.spectrum(); c++)
                {
                int pixelValue = 0;
                for (int i = x - 1; i < x + 2; i++)
                {
                    pixelValue += -original(i, y - 1, 0, c) -original(i, y, 0, c) -original(i, y + 1, 0, c);
                }
                pixelValue += 9*original(x, y, 0, c);

                edited(x, y, 0, c) = normalized(pixelValue);
            }
        }
    }
}

void applyLaplacianFilterOptimised2(CImg<int> &original, CImg<int> &edited, Histogram &histogram){
    for (int x = 1; x < original.width() - 1; x++)
    {
        for (int y = 1; y < original.height() - 1; y++)
        {
            for (int c = 0; c < original.spectrum(); c++)
            {
                edited(x, y, 0, c) = normalized(
                        -original(x-1, y - 1, 0, c) -original(x-1, y, 0, c) -original(x-1, y + 1, 0, c)
                        -original(x, y - 1, 0, c) -8*original(x, y, 0, c) -original(x, y + 1, 0, c)
                        -original(x+1, y - 1, 0, c) -original(x+1, y, 0, c) -original(x+1, y + 1, 0, c)
                );
            }
        }
    }
}

void applyRobertsOperatorFilter(CImg<int> &original, CImg<int> &edited, Histogram &histogram){
    for (int x = 1; x < original.width() - 1; x++)
    {
        for (int y = 1; y < original.height() - 1; y++)
        {
            for (int c = 0; c < original.spectrum(); c++)
            {
               edited(x, y, 0, c) = abs(original(x, y, 0, c) - original(x + 1, y + 1, 0, c)) + abs(original(x, y + 1, 0, c) - original(x + 1, y, 0, c));
            }
        }
    }
}