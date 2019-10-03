// fms_black.h - Black model
#pragma once
#include "fms_normal.h"

namespace fms::black {

    //!!! Black put and call code goes here.
    //!!! Use the functions in fms_normal.h

	//d2 Calculator
	inline double d2(double f, double sigma, double k, double t)
	{
		return -(pow(sigma, 2) * t / 2 + log(k / f)) / (sigma * sqrt(t));
	}

	//d1 Calculator
	inline double d1(double f, double sigma, double k, double t)
	{
		return d2(f, sigma, k, t) + sigma * sqrt(t);
	}

	//Put Calculator
	inline double put(double f, double sigma, double k, double t)
	{
		double ProbCOM = fms::normal::cdf(-d1(f, sigma, k, t));
		double Prob = fms::normal::cdf(-d2(f, sigma, k, t));

		return k * Prob - f * exp((pow(sigma, 2) - pow(sigma, 2)) / 2 * t) * ProbCOM;
	}

	//Call Calculator
	inline double call(double f, double sigma, double k, double t)
	{
		double ProbCOM = fms::normal::cdf(-d1(f, sigma, k, t));
		double Prob = fms::normal::cdf(-d2(f, sigma, k, t));

		return f * exp((pow(sigma, 2) - pow(sigma, 2)) / 2 * t) * (1 - ProbCOM) - k * (1 - Prob);
	}

} // fms::black