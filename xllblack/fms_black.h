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
		auto s = sigma * sqrt(t);
		auto d2 = -moneyness(f, s, k);
		auto d1 = d2 + s;

		return k * normal::cdf(-d2) - f * normal::cdf(-d1);
	}

	template<class F, class S, class K, class T>
	inline auto call(F f, S sigma, K k, T t)
	{
		auto s = sigma * sqrt(t);
		auto d2 = moneyness(f, s, k);
		auto d1 = d2 + s;

		return f * normal::cdf(d1) - k * normal::cdf(d2);
	}
} // fms::black