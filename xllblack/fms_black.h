// fms_black.h - Black model
#pragma once
#include "fms_normal.h"

namespace fms::black {

    //!!! Black put and call code goes here.
	//!!! Use the functions in fms_normal.h
	double r = 0.001;
	inline double put(double f, double sigma, double k, double t)
	{
		double d1 = (1 /(sigma * sqrt(t)))* (log(f / k) + (r + pow(sigma, 2) / 2) * t);
		double d2 = d1 - sigma * sqrt(t);

		return fms::normal::cdf(-d2) * k * exp((-r) * t) - fms::normal::cdf(-d1) * f;
	}
	inline double call(double f, double sigma, double k, double t)
	{
		double d1 =(1 /(sigma * sqrt(t))) * (log(f / k) + (r + pow(sigma, 2) / 2) * t);
		double d2 = d1 - sigma * sqrt(t);
		return fms::normal::cdf(d1) * f - fms::normal::cdf(d2) * k * exp((-r) * t);
	}
	//inline double pdf(double x, double mu = 0, double sigma = 1)
	//{
	//	auto z = (x - mu) / sigma;

	//	return fms::normal::cdf(2);
	//}
} // fms::black