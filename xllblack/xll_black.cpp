// xll_black.cpp
#include "fms_black.h"
#include "xll_black.h"

using namespace xll;
using namespace fms::black;

#ifdef _DEBUG
test test_moneyness([]() {
	double f = 100;
	double sigma = 0.2;
	double k = 100;
	double t = 0.25;

	double z = moneyness(f, sigma*sqrt(t), k);
	ensure(z == (0.2 * 0.2 * 0.25 / 2) / (0.2 * sqrt(0.25)));
	
	double p = put(f, sigma, k, t);
	ensure(fabs(p - 3.987) < 0.001);

	double c = call(f, sigma, k, t);
	ensure(fabs(c - 3.987) < 0.001);

	});
#endif // _DEBUG

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

static AddIn xai_black_call(
    Function(XLL_DOUBLE, L"?xll_black_call", L"XLL.BLACK.CALL")
    .Arg(XLL_DOUBLE, L"f", L"is the forward.", L"100")
    .Arg(XLL_DOUBLE, L"sigma", L"is the volatility.", L"0.2")
    .Arg(XLL_DOUBLE, L"k", L"is the strike.", L"100")
    .Arg(XLL_DOUBLE, L"t", L"is the time in years to expiration.", L"0.25")
    .Category(L"XLL")
    .FunctionHelp(L"Return Black call value.")
);
double WINAPI xll_black_call(double f, double sigma, double k, double t)
{
#pragma XLLEXPORT
    double result = std::numeric_limits<double>::quiet_NaN();

    try {
        result = call(f, sigma, k, t);
    }
    catch (const std::exception & ex) {
        XLL_ERROR(ex.what());
    }

    return result;
}

test test_delta([]() {

    double f = 100;
    double sigma = .2;
    double k = 100;
    double t = 0.25;

    double p = put(f, sigma, k, t);

    for (double h : {.01, .001, .0001, 0.00001, .000001}) {
        double dp = put_delta(f, sigma, k, t);
        double p_ = put(f + h, sigma, k, t);
        double _p = put(f - h, sigma, k, t);
        double dp_ = (p_ - _p) / (2 * h);
        double gamma = (p_ - 2 * p + _p) / (h * h);
        //double a, b;
        //a = dp - dp_;
        //b = gamma * h * h / 2;
        ensure(fabs(dp - dp_) <= gamma*h*h/2);
    }

    });

test test_vega([]() {
    //!!! Implement a test for vega

	// Set test values
	double f = 100;
	double sigma = .2;
	double k = 100;
	double t = 0.25;

	// Test value of put value with respect to sigma
	double p = put(f, sigma, k, t); // calculate the fms::black::put value of test values

	for (double h : {.01, .001, .0001, 0.00001, .000001}) { // test increments
		double dp = vega(f, sigma, k, t); // calculate derivitive of put value with respect to sigma (vega on put)
		double p_ = put(f, sigma + h, k, t); // calculate put with small increase (h) in sigma
		double _p = put(f, sigma - h, k, t); // calculate put with small decrease (h) in sigma
		double dp_ = (p_ - _p) / (2 * h); // calculate slope from above
		double gamma = (p_ - 2 * p + _p) / (h * h); // threshold
		ensure(fabs(dp - dp_) <= gamma * h * h / 2); // ensure small difference between vega dp and calculated dp
	}

	// Test value of call value with respect to sigma
	double c = call(f, sigma, k, t); // calculate the fms::black::put value of test values

	for (double h : {.01, .001, .0001, 0.00001, .000001}) { // test increments
		double dc = vega(f, sigma, k, t); // calculate derivitive of put value with respect to sigma (vega on put)
		double c_ = call(f, sigma + h, k, t); // calculate call with small increase (h) in sigma
		double _c = call(f, sigma - h, k, t); // calculate call with small decrease (h) in sigma
		double dc_ = (c_ - _c) / (2 * h); // calculate slope from above
		double gamma = (c_ - 2 * c + _c) / (h * h); // threshold
		ensure(fabs(dc - dc_) <= gamma * h * h / 2); // ensure small difference between vega dc and calculated dc
	}

    });

//!!! Implement XLL.BLACK.PUT.IMPLIED(f, p, k, t) where p is the put value.

static AddIn xai_black_put_implied_volatility(
	Function(XLL_DOUBLE, L"?xll_black_put_implied_volatility", L"XLL.BLACK.PUT.IMPLIED")
	.Arg(XLL_DOUBLE, L"f", L"is the forward.")
	.Arg(XLL_DOUBLE, L"p", L"is the put value.")
	.Arg(XLL_DOUBLE, L"k", L"is the strike.")
	.Arg(XLL_DOUBLE, L"t", L"is the time in years to expiration.")
	.Category(L"XLL")
	.FunctionHelp(L"Return implied put volatility (sigma).")
);
double WINAPI xll_black_put_implied_volatility(double f, double p, double k, double t)
{
#pragma XLLEXPORT
	double result = std::numeric_limits<double>::quiet_NaN();

	try {
		result = put_implied_volatility(f, p, k, t);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return result;
}

