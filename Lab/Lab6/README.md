# Lab 6 - COMP 2160
**Recursive Fibonacci**
n | run time 
10 | 0.00
16 | 0.00
24 | 0.00
30 | 0.00
36 | 0.09
40 | 0.66
42 | 1.74

**Cached Fibonacci**
n  | run time
10 | 0.00
16 | 0.00
24 | 0.00
30 | 0.00
36 | 0.00
40 | 0.00
42 | 0.00
5000 | 0.00

**Explaination** 
If we calculate fibinacci by recursion without caching, the complexity is O(2^n) (T(n) = T(n-1) + T(n-2)). For small number, the runtime is not increasing significant (from n = 10 to n = 36). However, once the n gets larger, the time would increase very fast. n=40 is 0.66 but n=42 is 1.74s. 
Another expanaition is the wasting for re-calculating same value many times. Take n = 42 as example, to calculate n = 42 we need to calculate n = 41 then n = 40. Without caching we need to calculate n=40 at least twice. One is for calculating n = 42 and the other one is for calculating n = 42. Then for lower n, the more repeated calculation we need to do. 
That's the reason why caching makes the problem much much faster. It eliminated all the repeat of calculations. Instead of calculating hundreds or even thousands time of n=3, we only need to calculate 1 times only. The complexity, then, become linear O(n). 

Optimal cached size: personally I used dynamic size based on the number given by user. Becaues the program runs only one time, there is no need to create any number larger than the one user query. So just use the number users give to create the size of the cache. My cache has a size of n + 1 which means it includes the fib from n = 0 to n = (n+1)-1= n. 
If the program becomes run one time with many query, I would use static size so the user can query in a given range. 

**Notes**
- In the screenshot I use $alias time2 /usr/bin/time so I dont need to repeat the whole command. Im just being lazy :)
- I applied my caching technique to solve from bottom up (0->n) instead of top down (n->0). I think this way is more efficient and less bug-prone than other way. 

