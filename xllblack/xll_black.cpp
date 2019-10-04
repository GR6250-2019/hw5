// xll_black.cpp
#include "fms_black.h"
#include "xll_black.h"

using namespace xll;
using namespace fms::black;

test test_moneyness([]() {
	double f = 100;
	double sigma = 0.2;
	double k = 100;
	double t = 0.25;

	//double z = moneyness(f, sigma, k, t);
	//ensure(z == (0.2 * 0.2 * 0.25 / 2) / (0.2 * sqrt(0.25)));
	
	double p = put(f, sigma, k, t);
	ensure(fabs(p - 3.987) < 0.001);

	double c = call(f, sigma, k, t);
	ensure(fabs(c - 3.987) < 0.001);

	});

//!!! Implement XLL.BLACK.PUT(f, sigma, k, t) and XLL.BLACK.CALL(f, sigma, k, t)

static AddIn xai_black_put(
	Function(XLL_DOUBLE, L"?xll_black_put", L"XLL.BLACK.PUT")
	.Arg(XLL_DOUBLE, L"f", L"is the forward.", L"100")
	.Arg(XLL_DOUBLE, L"sigma", L"is the volatility.", L"0.2")
	.Arg(XLL_DOUBLE, L"k", L"is the strike.", L"100")
	.Arg(XLL_DOUBLE, L"t", L"is the time in years to expiration.", L"0.25")
	.Category(L"XLL")
	.FunctionHelp(L"Return Black put value.")
);
double WINAPI xll_black_put(double f, double sigma, double k, double t)
{
#pragma XLLEXPORT
	double result = std::numeric_limits<double>::quiet_NaN();

	try {
		result = put(f, sigma, k, t);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return result;
}
