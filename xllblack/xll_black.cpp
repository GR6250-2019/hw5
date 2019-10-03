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
	.Arg(XLL_DOUBLE, L"f", L" price of the underlying asset.")
	.Arg(XLL_DOUBLE, L"sigma", L" volatility of the underlying asset. ")
	.Arg(XLL_DOUBLE, L"k", L" strike price of the option.")
	.Arg(XLL_DOUBLE, L"t", L" is the time to expiration.")
	.Category(CATEGORY)
	.FunctionHelp(L"Return the price of a put option.")
	.Documentation(
		L"This function computes the price of call option "
		L"using the price and volatility of the underlying asset, the time to expiration, the strike price of the option. "
		L"Call price= E[max(f-k,0)]."
	)
);
double WINAPI xll_black_put(double x, double sigma, double k, double t)
{
#pragma XLLEXPORT
	

	return fms::black::put(x, sigma, k, t);
}

static AddIn xai_black_call(
	Function(XLL_DOUBLE, L"?xll_black_call", L"XLL.BLACK.CALL")
	.Arg(XLL_DOUBLE, L"f", L" price of the underlying asset.")
	.Arg(XLL_DOUBLE, L"sigma", L" volatility of the underlying asset. Default is 0.")
	.Arg(XLL_DOUBLE, L"k", L" strike price of the option.")
	.Arg(XLL_DOUBLE, L"t", L" is the time to expiration.")
	.Category(CATEGORY)
	.FunctionHelp(L"Return the price of a call option.")
	.Documentation(
		L"This function computes the price of call option "
		L"using the price and volatility of the underlying asset, the time to expiration, the strike price of the option.  "
		L"Put price= E[max(k-f,0)]."
	)
);
double WINAPI xll_black_call(double x, double sigma, double k, double t)
{
#pragma XLLEXPORT


	return fms::black::call(x, sigma, k, t);
}

