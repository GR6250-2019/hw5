# Homework 5

1. Create a spreadsheet called `normal_inv.xlsx` to find out when `NORMAL.INV` starts failing.  

Duplicate the function `fms::normal::inv` in the file `fms_normal.h`:

- Choose a cell for input `x`. Start with `x` equal to 0.
- Choose a cell for for the output, `p`, of function `NORMSDIST(x)`
- Using `p` as input, duplicate the code for the initial guess on line 40 of `fms_normal.h`. Call this `x0`.
- In the cell to the right of the initial guess enter the formula for `XLL.NORMAL.CDF(x0) - p`
- In the cell to the right of this enter the formula for `XLL.NORMAL.PDF(x0)`
- Below the cell for `x0` enter the formula for the Newton-Raphson next guess. Call this `x1`.
- Copy and paste the cells for the cdf and pdf directly below in the same row as `x1`.
- Copy and paste the row of three cells you just enter as needed until you see convergence.

Find the value for `x` > 0 such that the root finding algorithm converges but `x + 0.1` does not converge. Submit your spreadsheet with that value.

2. Search for !!! in the project and follow the directions.
