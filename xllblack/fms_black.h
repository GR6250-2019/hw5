// fms_black.h - Black model
#pragma once
#include "fms_normal.h"

namespace fms::black {

	//!!! Black put and call code goes here.
	inline double put(double f, double t, double k, double sigma = 1) {

		if (k < 0 || t < 0 || f < 0) {
			throw std::domain_error("fms::black::put argument (k,t,f) must be positive");
		}
		double d2 = -1 * (((pow(sigma, 2) * t) / 2) + log(k / f)) / (sigma * sqrt(t));
		double d1 = d2 + sigma * sqrt(t);

		return k * fms::normal::cdf(-1 * d2) - f * fms::normal::cdf(-1 * d1);
	};

	inline double call(double f, double t, double k, double sigma = 1) {

		if (k < 0 || t < 0 || f < 0) {
			throw std::domain_error("fms::black::put argument (k,t,f) must be positive");
		}

		double d2 = -1 * (((pow(sigma, 2) * t) / 2) + log(k / f)) / (sigma * sqrt(t));
		double d1 = d2 + sigma * sqrt(t);

		return f * fms::normal::cdf(d1) - k * fms::normal::cdf(d2);
	};
	//!!! Use the functions in fms_normal.h
} // fms::black