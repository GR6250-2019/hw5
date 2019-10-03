// xll_black.cpp

//!!! Implement XLL.BLACK.PUT(f, sigma, k, t) and XLL.BLACK.CALL(f, sigma, k, t)
//!!! Document both function.
//!!! Test both function. 
//!!! put = 3.988 to three decimal places for f = 100, sigma = 0.2, k = 100, t = 0.25.
//!!! Also test call value for these parameters.


#include "xll_black.h"
#include "fms_black.h"

using namespace fms::black;
using namespace xll;
static AddInX xai_black_call(
	FunctionX(XLL_DOUBLE, L"?xll_black_call", L"XLL.BLACK_CALL")
	.Arg(XLL_DOUBLE, L"f", L"is the price of stock.")
	.Arg(XLL_DOUBLE, L"sigma", L"is the yearly volatility.")
	.Arg(XLL_DOUBLE, L"k", L"the strike price.")
	.Arg(XLL_DOUBLE, L"t", L"is years to maturity.")
	.Category(L"XLL")
	.FunctionHelp(L"Computes the call of an option.")
	.Documentation(LR"(Using the BLACK-SCHOLE Model to calculate the call of an option)")

	); 
double WINAPI xll_black_call(double f, double sigma, double k, double t)
{
#pragma XLLEXPORT
	return fms::black::black_call(f,sigma,k,t);
}

static AddInX xai_black_put(
	FunctionX(XLL_DOUBLE, L"?xll_black_put", L"XLL.BLACK_PUT")
	.Arg(XLL_DOUBLE, L"f", L"is the price of stock.")
	.Arg(XLL_DOUBLE, L"sigma", L"is the yearly volatility.")
	.Arg(XLL_DOUBLE, L"k", L"the strike price.")
	.Arg(XLL_DOUBLE, L"t", L"is years to maturity.")
	.Category(L"XLL")
	.FunctionHelp(L"Computes the put of an option .")
	.Documentation(LR"(Using the BLACK-SCHOLE Model to calculate the put of an option)")

);
double WINAPI xll_black_put(double f, double sigma, double k, double t)
{
#pragma XLLEXPORT
	return fms::black::black_put(f, sigma, k, t);
}

#ifdef _DEBUG

xll::test test_xll_black_put_value([]() {
	double presult;
	presult = xll_black_put(100, 0.2, 100, 0.25) - 3.988;

	ensure(presult < 1e-3);
	});

#endif // _DEBUG
#ifdef _DEBUG

xll::test test_xll_black_call_value([]() {
	double presult;
	presult = xll_black_call(100, 0.2, 100, 0.25)-3.988;
	ensure(presult <1e-3);
	});
#endif//_DEBUG

