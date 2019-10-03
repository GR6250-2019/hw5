// fms_black.h - Black model
#pragma once
#include "fms_normal.h"

namespace fms::black {
 	// calculate put function.
 	inline double put(double f, double sigma, double k, double t)
 	{
 		if (k * f < 0 || t < 0) {
 			throw std::domain_error("fms::black::put parameter k,f,t must be positive!");
 		}
 		else
 		{
 			double d2 = -(log(k / f) + sigma * sigma * t / 2) / sigma / sqrt(t);
 			double d1 = d2 + sigma * sqrt(t);

     //!!! Black put and call code goes here.
     //!!! Use the functions in fms_normal.h
 			return k * fms::normal::cdf(-d2) - f * fms::normal::cdf(-d1);
 		}
 	}
 	// calculate put function.
 	inline double call(double f, double sigma, double k, double t)
 	{
 		if (k * f < 0 || t < 0) {
 			throw std::domain_error("fms::black::call parameter k,f,t must be positive!");
 		}
 		else
 		{
 			double d2 = -(log(k / f) + sigma * sigma * t / 2) / sigma / sqrt(t);
 			double d1 = d2 + sigma * sqrt(t);

 			return f * fms::normal::cdf(d1) - k * fms::normal::cdf(d2);
 		}
 	}
 } // fms::black 
