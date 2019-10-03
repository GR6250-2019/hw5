// fms_black.h - Black model
#pragma once
#include "fms_normal.h"

namespace fms::black {

    //!!! Black put and call code goes here.
    //!!! Use the functions in fms_normal.h

	inline double put(double f, double sigma,double k,double t)
	{
		double d2 = -(log(k / f) + pow(sigma, 2) * t / 2) / (sigma * sqrt(t));
		double d1 = d2 + sigma * sqrt(t);
		double P = fms::normal::cdf(-d2);
		double P_star = fms::normal::cdf(-d1);
		double EXPF = f * exp((pow(sigma, 2) - pow(sigma, 2)) * t / 2);

		return k * P - EXPF * P_star;
	}
	inline double call(double f, double sigma, double k, double t)
	{
		double d2 = -(log(k / f) + pow(sigma, 2) * t / 2) / (sigma * sqrt(t));
		double d1 = d2 + sigma * sqrt(t);
		double P = fms::normal::cdf(-d2);
		double P_star = fms::normal::cdf(-d1);
		double EXPF = f * exp((pow(sigma, 2) - pow(sigma, 2)) * t / 2);

		return EXPF * (1-P_star)-k*(1-P);
	}

} // fms::black