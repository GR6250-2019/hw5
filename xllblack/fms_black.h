// fms_black.h - Black model
#pragma once
#include "fms_normal.h"

namespace fms::black {

	//!!! Black put and call code goes here.
	// Black-Scholes Call Price

	double BLACK_CALL(double f, double sigma, double k, double t )
	{
		double r = 0;
		double d1 = (log(f / k) + t * (r + 0.5 * sigma * sigma)) / (sigma * sqrt(t));
		double call = f * fms::normal::cdf(d1) - exp(-r * t) * k * fms::normal::cdf(d1 - sigma * sqrt(t));
		return call;
	}

	double BLACK_PUT(double f, double sigma, double k, double t )
	{
		double r = 0;
		double d1 = (log(f / k) + t * (r + 0.5 * sigma * sigma)) / (sigma * sqrt(t));
		double put = exp(-r * t) * k * fms::normal::cdf(sigma * sqrt(t) - d1) - f * fms::normal::cdf(-d1);
		return put;
	}
	//!!! Use the functions in fms_normal.h

} // fms::black



