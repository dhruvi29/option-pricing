# option-pricing

### C++ Build Proceess 
> https://stackoverflow.com/questions/6264249/how-does-the-compilation-linking-process-work
> https://www.youtube.com/watch?v=JsIJBh2OKhM


### Project evolution 
#### Version 1: Using no arbitrage
``` g++ ./include/binomial.h main.cpp binomial.cpp ```
1. s1u = s0 * u; s1d = s0 * d
2. c1u = max(0, s1u - x) || p1u = max(0, x - s1u) // X = Strike Price
3. Portfolio of shares and an option -> v = h * S - c
4. A portfolio, such that its value remains same in case of a upmove or a down move i.e. v1u = v1d
5. Hence, equating v1u = v1d, we derive value of h -> hedge ratio. (Number of shares to but for writing each call)
6. Calculate v1, calc p.v. of v1 tp get v0
7. Again v0 = h * s0 - c0; from this, derive c0 & hence the value of call option
8. Similarly get the value of put option

#### Version 2: Using risk neutral probabilities 
``` g++ ./include/binomial.h main.cpp binomial.cpp ```
1. step 1 and step 2 -> same as above
2. Risk netral probability of upmove = (1 + Rf - d) / (u - d). 
3. Expected future payoff = probability-weighted value of upmove and downmove
4. Present value of xpected future payoff -> Required value of call / put

> gives exact same results as version 1
> Version 1 & 2 donot have multilevels and does not account number of days to expiry - We discount it by one year. Hence, it gives us value of an option that expires one year from now while calculating only one branch / level (i.e. not multi-level)

#### Version 3: Multilevel - Include days to expiry + Recursive solution

``` g++ ./include/binomial2.h main.cpp binomial2.cpp ```

#### Version 4: Multilevel - Memoised

#### Version 5: Multilevel - Bottom up DP

> Version 3,4,5 are in binomial2. They take into consideration the days to expiration while having equal number of branches as to number of days & daily compunding / discounting.