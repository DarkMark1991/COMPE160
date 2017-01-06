## COMPE160 - Lab 6 part 2 - Numerical Analysis Algorithm 

### Method:
The chosen method is Riemann sum algorithm, specifically the midpoint variant.
The algorithm provides a way to approximate the area under the curve of a function, i.e. a definite integral. This is achieved by breaking the interval down into multiple subintervals and calculating the sum of areas of rectangles whose base is the subinterval, and height is the result of the function at the midpoint of the subinterval.
So, to calculate definite integral of f(x) on interval a, b we break it into N parts {x1, x2 … xN} where x1=a & xN=b and calculate:

![alt text](http://i.imgur.com/cnHvDqC.png "∫abf(x)dx ~ limN→∞ ∑i=1N f(xi-1/2+xi/2)(xi−xi-1)")

The greater the number N the better the approximation. Generally taking the limit of the sum where N→∞ yields the best result, however, as computer’s resources are limited we will set stopping criteria:
1.	If maximum number of iterations (30000) is reached the program will stop and display the result.
2.	If the sum converges, i.e. the (sum – previous sum) < Ɛ, where Ɛ is a small enough number the execution will stop. Ɛ=10-6

### Function:
The function to be evaluated is polynomial derived from the last 6 digits of my Red ID number, which is 819817616, so:

![alt text](http://i.imgur.com/WWr1RJK.png "f(x) = 8x^5 + x^4 + 7x^3 + 6x^2 + x + 6")

This function has local extrema at the given points:

![alt text](http://i.imgur.com/yn3ZUHD.png "min: x ~= -0.101293, max: x ~= -0.371789")

### Pseudocode: 
BEGIN MAIN
	FOR EACH test interval 
RIEMANN_CYCLE(f, interval, epsilon, maxIteration);
PRINT N, elapsed time, interval, sum, integral, error;
END MAIN

BEGIN RIEMANN_CYCLE(f, interval, epsilon, maxIteration)
	WHILE N++ < maxIteration
		prevSum = sum;
		sum = RIEMANN(f, interval, N);
		if(-epsilon < sum-prevSum < epsilon) break;
	RETURN sum, N;
END RIEMANN_CYCLE

BEGIN RIEMANN(f, interval, N)
	delta = intervalEnd-intervalStart/N;
	FOR each subInterval in interval
		sum += delta * f(midPoint);
	RETURN sum;
END RIEMANN
