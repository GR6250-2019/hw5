// fms_black.h - Black model
#pragma once
#include "fms_normal.h"

namespace fms::black {

    //!!! Black put and call code goes here.
    //!!! Use the functions in fms_normal.h

	// Call option price computation
	// C(S_0,t) = S_0 * N(d_1) - K * N(d_2)
	// The price of the call option is simply the return [S_0 * N(d_1)] minus the cost [K * N(d_2)]
	// Where the return = stock price * probability function
	// And the cost = strike price * discount to present value * probability function
	// N(d_1) is a probability that is 0 if the stock is below the strike price but is some probability representing the stock's value if its above strike price, simply area under the normal distribution up to a z-score (z = x - u / sigma) 
	// Where d_1 = ln(f/k) + (sigma/2)*t / (sqrt(sigma)*sqrt(t))
	// N(d_2) is the probability the future price will be above the strike price on expiration date
	// Where d_2 = d_1 - (sqrt(sigma)*sqrt(t))

	inline double call(double f, double sigma, double k, double t) // "inline" inserts the body of the function in every place that the function is called, rather than generating code to clal the function in the one place it is defined
	{
		auto d1 = (log(f / k) + ((pow(sigma, 2) / 2) * t)) / (sigma * sqrt(t));
		auto d2 = d1 - (sigma * sqrt(t));
		auto return_value = f * fms::normal::cdf(d1);
		auto cost_value = k * fms::normal::cdf(d2);
		auto call_option_value = return_value - cost_value;

		return  call_option_value;
	}

	// Put option price computation
	// P(S_0,t) = K * N(-d_2) - S_0 * N(-d_1)
	inline double put(double f, double sigma, double k, double t) // "inline" inserts the body of the function in every place that the function is called, rather than generating code to clal the function in the one place it is defined
	{
		auto d1 = (log(f / k) + ((pow(sigma, 2) / 2) * t)) / (sigma * sqrt(t));
		auto d2 = d1 - (sigma * sqrt(t));
		auto cost_value = k * fms::normal::cdf(-d2);
		auto return_value = f * fms::normal::cdf(-d1);
		auto put_option_value = cost_value - return_value;

		return put_option_value;
	}

} // fms::black