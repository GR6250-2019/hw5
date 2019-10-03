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
using namespace std;
using namespace xll;

static AddIn xai_put(
	Function(XLL_DOUBLE, L"?xll_put", L"XLL.PUT")
	.Arg(XLL_DOUBLE, L"f", L"is the value of current underlying asset price.")
	.Arg(XLL_DOUBLE, L"t", L"is the value of time to maturity")
	.Arg(XLL_DOUBLE, L"k", L"is the value of strike price")
	.Arg(XLL_DOUBLE, L"sigma", L"is the standard deviation of the normal random variable. Default is 1.")
	.Category(CATEGORY)
	.FunctionHelp(L"Return the value of the put option.")
	.Documentation(
		L"This function computes the put option value"
		L"using the standard normal density "
		MATH_(L"e" SUP_(minus_ L"z" sup2_ L"/2") L"/" radic_ L"2" pi_)
	)
);

double WINAPI xll_put(double f, double t, double k, double sigma = 1)
{
#pragma XLLEXPORT
	/*if (sigma == 0) {
		sigma = 1;
	}*/

	return fms::black::put(f, t, k, sigma);
}

#ifdef _DEBUG

test test_put([] {
	ensure(xll_put(100, 0.25, 100, 0.2) == 3.988);
});

#endif

static AddIn xai_call(
	Function(XLL_DOUBLE, L"?xll_call", L"XLL.CALL")
	.Arg(XLL_DOUBLE, L"f", L"is the value of current underlying asset price.")
	.Arg(XLL_DOUBLE, L"t", L"is the value of time to maturity")
	.Arg(XLL_DOUBLE, L"k", L"is the value of strike price")
	.Arg(XLL_DOUBLE, L"sigma", L"is the standard deviation of the normal random variable. Default is 1.")
	.Category(CATEGORY)
	.FunctionHelp(L"Return the value of the call option.")
	.Documentation(
		L"This function computes the call option value"
		L"using the standard normal density "
		MATH_(L"e" SUP_(minus_ L"z" sup2_ L"/2") L"/" radic_ L"2" pi_)
	)
);

double WINAPI xll_call(double f, double t, double k, double sigma = 1)
{
#pragma XLLEXPORT
	/*if (sigma == 0) {
		sigma = 1;
	}*/

	return fms::black::call(f, t, k, sigma);
}


#ifdef _DEBUG

test test_call([] {
	ensure(xll_call(100, 0.25, 100, 0.2) == 3.988);
});

#endif
