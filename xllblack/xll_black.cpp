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

//Black Scholes Put
static AddIn xai_black_put(
	Function(XLL_DOUBLE, L"?xll_black_put", L"XLL.BLACK.PUT")
	.Arg(XLL_HANDLE, L"f", L"is the price.")
	.Arg(XLL_DOUBLE, L"sigma", L"is the volatility.")
	.Arg(XLL_DOUBLE, L"k", L"is the strike price.")
	.Arg(XLL_DOUBLE, L"t", L"is the time until expiration.")
	.Category(CATEGORY)
	.FunctionHelp(L"Returns the price of the specified put option.")
	.Documentation(
		L"This function computes the price of the specified put option "
		L"using the Black-Scholes pricing model "
		L"E[max(k-F,0)"
	)
);
double WINAPI xll_black_put(double f, double sigma, double k, double t)
{
#pragma XLLEXPORT
	
	return fms::black::put(f, sigma, k, t);
}

//Black Scholes Call
static AddIn xai_black_call(
	Function(XLL_DOUBLE, L"?xll_black_call", L"XLL.BLACK.CALL")
	.Arg(XLL_HANDLE, L"f", L"is the price.")
	.Arg(XLL_DOUBLE, L"sigma", L"is the volatility.")
	.Arg(XLL_DOUBLE, L"k", L"is the strike price.")
	.Arg(XLL_DOUBLE, L"t", L"is the time until expiration.")
	.Category(CATEGORY)
	.FunctionHelp(L"Returns the price of the specified call option.")
	.Documentation(
		L"This function computes the price of the specified call option "
		L"using the Black-Scholes pricing model "
		L"E[max(F-k,0)]"
	)
);
double WINAPI xll_black_call(double f, double sigma, double k, double t)
{
#pragma XLLEXPORT

	return fms::black::call(f, sigma, k, t);
}