#ifndef OTHER
#define OTHER

#include "../../lib/CImg.templ"

using namespace std;
using namespace cimg_library;

void applyBilinearInterpolation(CImg<int> &edited);

void displayProgress(int x, int max);

bool fileExists(char* name);

void displayHelp();

#endif //OTHER


