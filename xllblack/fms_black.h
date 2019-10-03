// fms_black.h - Black model
#pragma once
#include "fms_normal.h"

namespace fms::black {

    // Use cdf from fms_normal.

	inline double cdf(double x, double mu = 0, double sigma = 1)
	{
		auto z = (x - mu) / sigma;

		return (1 + erf(z / M_SQRT2)) / 2;
	}

	// Black put and call code goes here.

	inline double blackput(double f, double sigma, double k, double t) 
	{
		
		double d1 = ( log ( f / k ) + ( ( pow(sigma, 2) / 2 ) * t ) ) / ( sigma * pow(t, 0.5) );
		double d2 = d1 - (sigma * pow(t, 0.5) );

		double put = cdf( -d2 ) * k - cdf( -d1 ) * f;
		put = round ( put * 1000.0) / 1000.0;
		return put;
	}
	
	inline double blackcall(double f, double sigma, double k, double t)
	{
		
		double d1 = ( log ( f / k ) + ( pow(sigma, 2) / 2 ) * t ) / ( sigma * pow(t, 0.5) );
		double d2 = d1 - (sigma * pow(t, 0.5));
		
		double call = cdf( d1 ) * f - cdf (d2) * k ;
		call = round(call * 1000.0) / 1000.0;
		return call;
	
	}
	
} // fms::black