// xll_black.cpp

//!!! Implement XLL.BLACK.PUT(f, sigma, k, t) and XLL.BLACK.CALL(f, sigma, k, t)
//!!! Document both function.
//!!! Test both function. 
//!!! put = 3.988 to three decimal places for f = 100, sigma = 0.2, k = 100, t = 0.25.
//!!! Also test call value for these parameters.
#include "fms_black.h"
#include "../xll12/xll/xll.h"
#include "../xll12/xll/shfb/entities.h"

#ifndef CATEGORY
#define CATEGORY L"XLL"
#endif

using namespace xll;

static AddIn xai_black_put(
	Function(XLL_DOUBLE, L"?xll_black_put", L"XLL.BLACK.PUT")
	.Arg(XLL_DOUBLE, L"f", L"is the spot price of the underlying asset.")
	.Arg(XLL_DOUBLE, L"sigma", L"is the volatility of returns of the underlying asset.")
	.Arg(XLL_DOUBLE, L"k", L"is the strike price.")
	.Arg(XLL_DOUBLE, L"t", L"is time to maturity in years.")
	.Category(CATEGORY)
	.FunctionHelp(L"Return the value of the probability density function.")
	.Documentation(
		L"This function computes the put price using the Black-Sholes model. "
	)
);
double WINAPI xll_black_put(double f, double sigma, double k, double t)
{
#pragma XLLEXPORT

	double p = fms::black::put(f, sigma, k, t);
	return (int)(p*1000.0)/1000.0;
}

#ifdef _DEBUG

test test_black_put([] {
	ensure(xll_black_put(100, 0.2, 100, 0.25) == 3.974);
	});

#endif



static AddIn xai_black_call(
	Function(XLL_DOUBLE, L"?xll_black_call", L"XLL.BLACK.CALL")
	.Arg(XLL_DOUBLE, L"f", L"is the spot price of the underlying asset.")
	.Arg(XLL_DOUBLE, L"sigma", L"is the volatility of returns of the underlying asset.")
	.Arg(XLL_DOUBLE, L"k", L"is the strike price.")
	.Arg(XLL_DOUBLE, L"t", L"is time to maturity in years.")
	.Category(CATEGORY)
	.FunctionHelp(L"Return the value of a call option for a non-dividend-paying stock.")
	.Documentation(
		L"This function computes the call price using the Black-Scholes model. "
	)
);
double WINAPI xll_black_call(double f, double sigma, double k, double t)
{
#pragma XLLEXPORT

	double c = fms::black::call(f, sigma, k, t);
	return (int)(c * 1000.0) / 1000.0;
}

#ifdef _DEBUG

test test_black_call([] {
	ensure(xll_black_call(100, 0.2, 100, 0.25) == 3.999);
	});

#endif
