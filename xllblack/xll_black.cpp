// xll_black.cpp

//!!! Implement XLL.BLACK.PUT(f, sigma, k, t) and XLL.BLACK.CALL(f, sigma, k, t)
//!!! Document both function.
//!!! Test both function. 
//!!! put = 3.988 to three decimal places for f = 100, sigma = 0.2, k = 100, t = 0.25.
//!!! Also test call value for these parameters.
#include "../xll12/xll/xll.h"
#include "../xll12/xll/shfb/entities.h"
#include "fms_normal.h"
#ifndef CATEGORY
#define CATEGORY L"XLL"
#endif
using namespace xll;
static AddIn xai_black_put(
	Function(XLL_DOUBLE, L"?xll_black_put", L"XLL.BLACK.PUT")
	.Arg(XLL_DOUBLE, L"f", L"is the current forward price.")
	.Arg(XLL_DOUBLE, L"sigma", L"is the volatility.")
	.Arg(XLL_DOUBLE, L"k", L"is the strike.")
	.Arg(XLL_DOUBLE, L"t", L"is the time to maturity in years.")
	.Category(CATEGORY)
	.FunctionHelp(L"Return the value of the Black Scholes formula for put price.")
	.Documentation(
		L"This function computes the black scholes put price"

	)
);
double WINAPI xll_black_put(double f, double sigma, double k, double t)
{
#pragma XLLEXPORT
	double d1 = (log(f / k) + sigma * sigma * 0.5 * t) / (sigma * sqrt(t));
	double d2 = (log(f / k) - sigma * sigma * 0.5 * t) / (sigma * sqrt(t));
	std::function<double(double)> F = [](double x) {return fms::normal::cdf(x, 0, 1); };
	return k * F(-d2) - f * F(-d1);
}

static AddIn xai_black_call(
	Function(XLL_DOUBLE, L"?xll_black_call", L"XLL.BLACK.CALL")
	.Arg(XLL_DOUBLE, L"f", L"is the current forward price.")
	.Arg(XLL_DOUBLE, L"sigma", L"is the volatility.")
	.Arg(XLL_DOUBLE, L"k", L"is the strike.")
	.Arg(XLL_DOUBLE, L"t", L"is the time to maturity in years.")
	.Category(CATEGORY)
	.FunctionHelp(L"Return the value of the Black Scholes formula for call price.")
	.Documentation(
		L"This function computes the black scholes call price"

	)
);
double WINAPI xll_black_call(double f, double sigma, double k, double t)
{
#pragma XLLEXPORT
	double d1 = (log(f / k) + sigma * sigma * 0.5 * t) / (sigma * sqrt(t));
	double d2 = (log(f / k) - sigma * sigma * 0.5 * t) / (sigma * sqrt(t));
	std::function<double(double)> F = [](double x) {return fms::normal::cdf(x, 0, 1); };
	return f * F(d1) - k * F(d2);
}

#ifdef _DEBUG

test test_black_put([] {
	ensure(abs(xll_black_put(100, 0.2, 100, 0.25) - 3.988) < 0.001);
});

#endif