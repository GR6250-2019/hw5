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

        return f*normal::pdf(d1)*sqrt(t);
    }

    // Value of sigma for a put having value p.
    template<class F, class P, class K, class T>
    inline auto put_implied_volatility(F f, P p, K k, T t)
    {
        //!!! Put in appropriate checks, including bounds for p.
		ensure(t > 0);
		ensure(p <= k);
		ensure(p >= k - f);

		//initial guess s0
		double s0 = (M_SQRT2PI/sqrt(t))*(p/f);
		double p_ = put(f, s0, k, t);

		//use Newton-Raphson
		//x = x0 - y0/f'(x0) where y0 = f(x0)
		//function = put(f,s,k,t) - p = 0
		while (fabs(p_ - p) > 1e-3) {
			double deri = vega(f, s0, k, t);
			s0 = s0 - (p_ - p) / deri;
			p_ = put(f, s0, k, t);
		}

        return s0; // !!!implement using Newton-Raphson 
    }

} // fms::black