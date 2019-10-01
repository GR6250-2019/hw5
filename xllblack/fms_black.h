// fms_black.h - Black model
#pragma once
#include "fms_normal.h"

namespace fms::black {
	namespace {
		double computeD1(double f, double sigma, double k, double t) {
			double num = log(f / k) + (t * sigma * sigma / 2);
			double denom = sigma * sqrt(t);
			return num / denom;
		}

		double computeD2(double f, double sigma, double k, double t) {
			double d1 = computeD1(f, sigma, k, t);
			return d1 - (sigma * sqrt(t));
		}
	}

	inline double put(double f, double sigma, double k, double t) {
		double d1 = computeD1(f, sigma, k, t);
		double d2 = computeD2(f, sigma, k, t);
		return (k * fms::normal::cdf(-d2)) - (f * fms::normal::cdf(-d1));
	}

	inline double call(double f, double sigma, double k, double t) {
		double d1 = computeD1(f, sigma, k, t);
		double d2 = computeD2(f, sigma, k, t);
		return (f * fms::normal::cdf(d1)) - (k * fms::normal::cdf(d2));
	}
} // fms::black