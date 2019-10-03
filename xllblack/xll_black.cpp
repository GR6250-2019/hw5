// xll_black.cpp


//!!! Implement XLL.BLACK.PUT(f, sigma, k, t) and XLL.BLACK.CALL(f, sigma, k, t)

#include"xll_black.h"
#include "fms_black.h"
#ifndef CATEGORY
#define CATEGORY "Float"
#endif
using namespace fms::black;
using namespace xll;

static AddInX xai_black_call(

	FunctionX(XLL_DOUBLE, L"?xll_black_call", L"XLL.BLACK.CALL")
	.Arg(XLL_DOUBLE, L"f", L"is stock price")
	.Arg(XLL_DOUBLE, L"sigma", L"is volatility")
	.Arg(XLL_DOUBLE, L"k", L"is strike price")
	.Arg(XLL_DOUBLE, L"t", L"is years to maturity")
	.Category(CATEGORY)
	.FunctionHelp(L"Computes the value of call option")
	.Documentation(LR"(Calculate the value of call option)")

);
double WINAPI

xll_black_call(double f, double sigma, double k, double t)

{
#pragma XLLEXPORT

	return fms::black::BLACK_CALL(f, sigma, k, t);
}

static AddInX xai_black_put(

	FunctionX(XLL_DOUBLE, L"?xll_black_put", L"XLL.BLACK.PUT")
	.Arg(XLL_DOUBLE, L"f", L"is stock price")
	.Arg(XLL_DOUBLE, L"sigma", L"is volatility")
	.Arg(XLL_DOUBLE, L"k", L"is strike price")
	.Arg(XLL_DOUBLE, L"t", L"is years to maturity")
	.Category(CATEGORY)
	.FunctionHelp(L"Computes the value of put option")
	.Documentation(LR"(Calculate the value of put option)")

);
double WINAPI

xll_black_put(double f, double sigma, double k, double t)

{
#pragma XLLEXPORT

	return fms::black::BLACK_PUT(f, sigma, k, t);
}


#if _DEBUG
xll::test test1_xll_black_call([]() {

	double presult;
	double f = 120;
	double sigma = 0.2;
	double k = 120;
	double t = 1;
	presult = fms::black::BLACK_CALL(f, sigma, k, t);
	ensure(presult = 9.559);

	});
#endif // _DEBUG

#if _DEBUG
xll::test test1_xll_black_put([]() {

	double presult;
	double f = 120;
	double sigma = 0.2;
	double k = 120;
	double t = 1;
	presult = fms::black::BLACK_PUT(f, sigma, k, t);
	ensure(presult = 9.559);

	});


#endif // _DEBUG

#if _DEBUG
xll::test test_xll_black_call([]() {

	double presult;
	double f = 100;
	double sigma = 0.2;
	double k = 100;
	double t = 0.25;
	presult = fms::black::BLACK_CALL(f, sigma, k, t);
	ensure(presult = 3.988);

	});
#endif // _DEBUG

#if _DEBUG
xll::test test_xll_black_put([]() {

	double presult;
	double f = 100;
	double sigma = 0.2;
	double k = 100;
	double t = 0.25;
	presult = fms::black::BLACK_PUT(f, sigma, k, t);
	ensure(presult = 3.988);

	});


#endif // _DEBUG



//!!! Implement XLL.BLACK.PUT(f, sigma, k, t) and XLL.BLACK.CALL(f, sigma, k, t)
//!!! Document both function.
//!!! Test both function. 
//!!! put = 3.988 to three decimal places for f = 100, sigma = 0.2, k = 100, t = 0.25.
//!!! Also test call value for these parameters.


