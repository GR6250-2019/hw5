// xll_black.cpp
//!!! Implement XLL.BLACK.PUT(f, sigma, k, t) and XLL.BLACK.CALL(f, sigma, k, t)
//!!! Document both function.
//!!! Test both function. 
//!!! put = 3.988 to three decimal places for f = 100, sigma = 0.2, k = 100, t = 0.25.
//!!! Also test call value for these parameters.

#include "fms_black.h"
#include "../xll12/xll/xll.h"
#include "../xll12/xll/shfb/entities.h"
#include "iostream"
#ifndef CATEGORY
#define CATEGORY L"XLL"
#endif
using namespace xll;

//put
static AddIn xai_black_put(
 	Function(XLL_DOUBLE, L"?xll_black_put", L"XLL.BLACK.PUT")
 	.Arg(XLL_DOUBLE, L"f", L"is the present value of the underlying forward.")
 	.Arg(XLL_DOUBLE, L"sigma", L"is the standard deviation of price of the forward.")
 	.Arg(XLL_DOUBLE, L"k", L"is the stike price.")
 	.Arg(XLL_DOUBLE, L"t", L"is the time to maturity.")
 	.Category(CATEGORY)
 	.FunctionHelp(L"Return the value of the put.")
 	.Documentation(
 		L"This function computes the price of the put"
 		L"using the Black and Scholes Model "
 	)
 );
 double WINAPI xll_black_put(double f, double sigma, double k, double t)
 {
 #pragma XLLEXPORT
 	return fms::black::put(f, sigma, k, t);
 }

 //call
 static AddIn xai_black_call(
 	Function(XLL_DOUBLE, L"?xll_black_call", L"XLL.BLACK.CALL")
 	.Arg(XLL_DOUBLE, L"f", L"is the present value of the underlying forward.")
 	.Arg(XLL_DOUBLE, L"sigma", L"is the standard deviation of price of the forward.")
 	.Arg(XLL_DOUBLE, L"k", L"is the stike price.")
 	.Arg(XLL_DOUBLE, L"t", L"is the time to maturity.")
 	.Category(CATEGORY)
 	.FunctionHelp(L"Return the value of the call.")
 	.Documentation(
 		L"This function computes the price of the call"
 		L"using the Black and Scholes Model "
 	)
 );
 double WINAPI xll_black_call(double f, double sigma, double k, double t)
 {
 #pragma XLLEXPORT
 	return fms::black::call(f, sigma, k, t);
 }

 #ifdef _DEBUG

 test test_black_call([] {

   	ensure(std::round(xll_black_call(100, 0.2, 100, 0.25) * 1000.0) / 1000.0 == 3.988);

 	});#endif 
