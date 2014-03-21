#include "mapping.h"

double rt_map(double minIn, double maxIn, double minOut, double maxOut, double input)
{
    if(input < minIn || input > maxIn)
        printf("[WARNING] Input %f out of given input range [%f,%f]\n",input,minIn,maxIn);
    double R = (input - minIn)/(maxIn-minIn); 
    return R * (maxOut-minOut) + minOut;
}
