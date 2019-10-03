// fms_black.h - Black model
#pragma once
#include "fms_normal.h"

namespace fms::black {

    //!!! Black put and call code goes here.
    //!!! Use the functions in fms_normal.h
	
	 double black_call(double f, double sigma, double k, double t)

	{
		double d = (log(f / k) + t * (0.5 * sigma * sigma)) / (sigma * sqrt(t));
		double call = f * fms::normal::cdf(d) - k * fms::normal::cdf(d - sigma * sqrt(t));
			return call;

	}
	double black_put(double f, double sigma, double k, double t)
	{
		double d = (log(f / k) + t * (0.5 * sigma * sigma)) / (sigma * sqrt(t));
		double put = k * fms::normal::cdf(sigma * sqrt(t)-d)- f * fms::normal::cdf(-d);
		return put;
	}
} // fms::black