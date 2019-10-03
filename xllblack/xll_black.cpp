// xll_black.cpp
#include "fms_normal.h"
#include "fms_black.h"
#include "xll_black.h"


using namespace fms::black;
using namespace fms::normal;
using namespace xll;


static AddIn xai_BLACKPUT(
	Function(XLL_FP, L"?xll_blackput", L"BLACKPUT")
	.Arg(XLL_DOUBLE, L"f", L"is the value of an instrument at option expiration.")
	.Arg(XLL_DOUBLE, L"sigma", L"is the volatility.")
	.Arg(XLL_DOUBLE, L"k", L"is the strike price.")
	.Arg(XLL_DOUBLE, L"t", L"is the time to maturity.")
	.Category(L"BLACK")
	.FunctionHelp(L"Return the price of put option.")
	.Documentation(LR"(
		Computes the value of put option, and stores a double value in a location that's specified in a parameter.
	)")
);

_FP12* WINAPI xll_blackput(double f, double sigma, double k, double t)
{
#pragma XLLEXPORT
	static xll::FP12 result(1, 1);

	try {

		double put = blackput(f, sigma, k, t);

		result[0] = put;
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0; // shows as #NUM! in Excel
	}

	return result.get();
}

static AddIn xai_BLACKCALL(
	Function(XLL_FP, L"?xll_blackcall", L"BLACKCALL")
	.Arg(XLL_DOUBLE, L"f", L"is the value of an instrument at option expiration.")
	.Arg(XLL_DOUBLE, L"sigma", L"is the volatility.")
	.Arg(XLL_DOUBLE, L"k", L"is the strike price.")
	.Arg(XLL_DOUBLE, L"t", L"is the time to maturity.")
	.Category(L"BLACK")
	.FunctionHelp(L"Return the price of call option.")
	.Documentation(LR"(
		Computes the value of call option, and stores a double value in a location that's specified in a parameter.
	)")
);
_FP12* WINAPI xll_blackcall(double f, double sigma, double k, double t)
{
#pragma XLLEXPORT

	static xll::FP12 result(1, 1);

	try {

		double call = blackcall(f, sigma, k, t);

		result[0] = call;
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0; // shows as #NUM! in Excel
	}

	return result.get();
}

#if _DEBUG


xll::test test_xll_blackput([]() {
	_FP12* presult;
	double f = 100;
	double sigma = 0.2;
	double k = 100;
	double t = 0.25;
	presult = xll_blackput(f, sigma, k, t);
	ensure(presult->array[0] == 3.988);
	});

#endif // _DEBUG

