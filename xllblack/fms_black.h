// fms_black.h - Black model
#pragma once
#include "..//xll12/xll/ensure.h"
#include "fms_normal.h"

namespace fms::black {

	// F = f exp(sigma B_t - sigma^2 t/2) is the Black model.
	// F <= k if and only if B_t/sqrt(t) <= (sigma^2 t/2 + log (k/f))/sigma sqrt(t)
	template<class F, class S, class K>
	inline auto moneyness(F f, S s, K k)
	{
		ensure(f > 0);
		ensure(s > 0);
		ensure(k > 0);

		return (s * s / 2 + log(k / f)) / s;
	}
    
	template<class F, class S, class K, class T>
	inline auto put(F f, S sigma, K k, T t)
	{
        ensure(sigma > 0);
        ensure(t > 0);

        auto s = sigma * sqrt(t);
		auto d2 = -moneyness(f, s, k);
		auto d1 = d2 + s;

		return k * normal::cdf(-d2) - f * normal::cdf(-d1);
	}

	template<class F, class S, class K, class T>
	inline auto call(F f, S sigma, K k, T t)
	{
        ensure(sigma > 0);
        ensure(t > 0);
        
        auto s = sigma * sqrt(t);
		auto d2 = -moneyness(f, s, k);
		auto d1 = d2 + s;

		return f * normal::cdf(d1) - k * normal::cdf(d2);
	}

    // Derivative of put value with respect to f.
    template<class F, class S, class K, class T>
    inline auto put_delta(F f, S sigma, K k, T t)
    {
        ensure(sigma > 0);
        ensure(t > 0);
        
        auto s = sigma * sqrt(t);
        auto d2 = -moneyness(f, s, k);
        auto d1 = d2 + s;

        return -normal::cdf(-d1);
    }

    // Derivative of a put or call value with respect to sigma.
    template<class F, class S, class K, class T>
    inline auto vega(F f, S sigma, K k, T t)
    {
        ensure(sigma > 0);
        ensure(t > 0);
        
        auto s = sigma * sqrt(t);
        auto d2 = -moneyness(f, s, k);
        auto d1 = d2 + s;

        return f*normal::pdf(d1)*t;
    }

    // Value of sigma for a put having value p.
    template<class F, class P, class K, class T>
    inline auto put_implied_volatility(F f, P p, K k, T t)
    {
		ensure(p > 0);
		ensure(t > 0);
		ensure(f > 0);
		ensure(k > 0);

		auto sigma_initial = 0.1;
		auto y0 = put(f, sigma_initial, k, t) - p;
		auto y_0 = vega(f, sigma_initial, k, t) ;
		auto x_1 = sigma_initial - y0 / y_0;
		auto count = 0;
		while (put(f, x_1, k, t) != 0) {
			count = count + 1;
			y0 = put(f, x_1, k, t) - p;
			y_0 = vega(f, x_1, k, t) ;
			x_1 = x_1 - y0 / y_0;
			if (count > 99999) {
				//when there is no convergernce over this amout of iteration
				//return error value
				x_1 = -1;
				return x_1;
			}
		}
        return x_1; // !!!implement using Newton-Raphson 
    }

} // fms::black