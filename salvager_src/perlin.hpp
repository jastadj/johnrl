#ifndef PERLIN_H
#define PERLIN_H

#include <cstdlib>
#include <vector>
#include <cmath>

inline double findnoise2(double x,double y);
inline double interpolate(double a,double b,double x);

double noise(double x,double y);

std::vector< std::vector<int> > genHeightMapV(int w,int h,int sx, int sy, double zoom,double p, int o);

#endif // PERLIN_H
