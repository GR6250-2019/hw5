// xll_black.cpp // COMPUTES THE PUT OR CALL OPTION PRICE OF A EUROPEAN OPTION

//!!! Implement XLL.BLACK.PUT(f, sigma, k, t) and XLL.BLACK.CALL(f, sigma, k, t)
//!!! Document both function.
//!!! Test both function. 
//!!! put = 3.988 to three decimal places for f = 100, sigma = 0.2, k = 100, t = 0.25.
//!!! Also test call value for these parameters.

#include "fms_black.h" // include the correct header file (which also include the fms_normal.h file)
#include "../xll12/xll/xll.h"
#include "../xll12/xll/shfb/entities.h"

#ifndef CATEGORY
#define CATEGORY L"XLL"
#endif

using namespace xll; // groups our xll name entities

// CALL OPTION PRICING FUNCTION

static AddIn xai_black_call(
	Function(XLL_DOUBLE, L"?xll_black_call", L"XLL.BLACK.CALL")
	.Arg(XLL_DOUBLE, L"f", L"is the forward price.") // f is the forward price
	.Arg(XLL_DOUBLE, L"sigma", L"is theunderlying volatility.") // sigma is the underlying volatility, a standard deviation of log returns
	.Arg(XLL_DOUBLE, L"k", L"is the strike price.") // k is the strike price
	.Arg(XLL_DOUBLE, L"t", L"is the time to maturity.") // is the time to maturity, in years
	.Category(CATEGORY)
	.FunctionHelp(L"Return the price of the call option.")
	.Documentation(
		L"This function computes the price of a European style call option"
	)
);

double WINAPI xll_black_call(double f, double sigma, double k, double t) // define function for computing the put option price
{
#pragma XLLEXPORT

	double price = std::numeric_limits<double>::quiet_NaN(); // initiate the price option storage as nan

	try {
		price = fms::black::call(f, sigma, k, t); // calculate the price of the put option
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0; // shows as #NUM! in Excel
	}

	return price; // return the price of the put option
}

#ifdef _DEBUG

test test_black_call([] {
	double call_test = round(xll_black_call(100, 0.2, 100, 0.25) * 1000) / 1000; // set precision to 3 decimals
	ensure(call_test == 3.988); // Ensure that the computed price of the call option is the expected value given the known data
	});

#endif

// PUT OPTION PRICING FUNCTION

static AddIn xai_black_put(
	Function(XLL_DOUBLE, L"?xll_black_put", L"XLL.BLACK.PUT")
	.Arg(XLL_DOUBLE, L"f", L"is the forward price.") // f is the forward price
	.Arg(XLL_DOUBLE, L"sigma", L"is theunderlying volatility.") // sigma is the underlying volatility, a standard deviation of log returns
	.Arg(XLL_DOUBLE, L"k", L"is the strike price.") // k is the strike price
	.Arg(XLL_DOUBLE, L"t", L"is the time to maturity.") // is the time to maturity, in years
	.Category(CATEGORY)
	.FunctionHelp(L"Return the price of the put option.")
	.Documentation(
		L"This function computes the price of a European style put option"
	)
);

double WINAPI xll_black_put(double f, double sigma, double k, double t) // define function for computing the put option price
{
#pragma XLLEXPORT
	
	double price = std::numeric_limits<double>::quiet_NaN(); // initiate the price option storage as nan

	try {
		price = fms::black::put(f, sigma, k, t); // calculate the price of the put option
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0; // shows as #NUM! in Excel
	}

	return price; // return the price of the put option
}

#ifdef _DEBUG

test test_black_put([] {
	double put_test = round(xll_black_put(100, 0.2, 100, 0.25) * 1000) / 1000; // set precision to 3 decimals
	ensure(put_test == 3.988); // Ensure that the computed price of the call option is the expected value given the known data
	});

#endif

