#https://www.cfm.brown.edu/people/dobrush/am33/python/?/p3/pade.html

#Henri Eugène Padé.
#A Padé approximant is the "best" approximation of a function by a rational function of given order -- under this technique, the approximant's power series agrees with the power series of the function it is approximating. The technique was developed around 1890 by the French mathematician Henri Padé (1863--1953), but goes back to the German mathematician Georg Frobenius (1849--1917) who introduced the idea and investigated the features of rational approximations of power series. Henri Eugène Padé, while preparing his doctorate under Charles Hermite, he introduced what is now known as the Padé approximant.

'''
A mathematical definition of the Padé approximant and examples: 

To implement the Padé approximant, here is a simple implementation in Python using the sympy library:
'''

import sympy as sp

def pade_approximant(f, x, m, n):
    # Get the Maclaurin series of the function up to order m + n
    series = sp.series(f, x, 0, m + n + 1).removeO()

    # Split the series into the numerator and the denominator
    num_series = series.as_ordered_terms()[:m + 1]
    den_series = series.as_ordered_terms()[m + 1:]

    # Define the coefficients for the numerator and denominator
    a = sp.symbols('a0:{}'.format(m + 1))
    b = sp.symbols('b1:{}'.format(n + 1))

    # Construct the numerator and denominator
    num = sum(a[i]*x**i for i in range(m + 1))
    den = 1 + sum(b[i]*x**(i + 1) for i in range(n))

    # Solve for the coefficients
    coeff_eqs = []
    for i in range(m + 1):
        coeff_eqs.append(num_series[i] - num.as_ordered_terms()[i])
    for i in range(n):
        coeff_eqs.append(den_series[i] - den.as_ordered_terms()[i + 1])

    coeff_soln = sp.solve(coeff_eqs, a + b)

    # Substitute the coefficients back into the numerator and denominator
    num = num.subs(coeff_soln)
    den = den.subs(coeff_soln)

    return num / den

'''
This function approximates the input function 'f' around 'x = 0' using the Padé approximant of order [m/n].

This is a simple implementation and may not work for all functions or orders, and doesn't take into account issues like numerical stability. Furthermore, calculating higher order derivatives and solving systems of linear equations can be computationally intensive, so this function may be slow for large 'm' and 'n'. We would need a more sophisticated algorithm for a production-quality implementation.
'''

#Example: Consider Padé approximants for cosine functions

\begin{align*} r_2 (x) &= \dfrac{1 - \frac{5}{12}\, x^2}{1 + \frac{1}{12}\, x^2} , \\ r_4 (x) &= \dfrac{1 - \frac{115}{252}\,x^2 + \frac{313}{15120}\,x^4}{1+ \frac{11}{252}\,x^2 + \frac{13}{15120}\,x^4} , \\ r_8 (x) &= \dfrac{1-\frac{260735}{545628}\,x^2 + \frac{4375409}{141863280}\,x^4 - \frac{7696415}{13108167072}\,x^6 + \frac{80737373}{23594700729600}\, x^8}{1 + \frac{12079}{545628}\, x^2 + \frac{34709}{141863280}\,x^4 + \frac{109247}{65540835360}\, x^6 + \frac{11321}{1814976979200}\, x^8} . \end{align*}
