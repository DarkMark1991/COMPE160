## COMPE160 - Lab 6 part 2 - Numerical Analysis Algorithm 

### Method
The chosen method is Riemann sum algorithm, specifically the midpoint variant.
The algorithm provides a way to approximate the area under the curve of a function, i.e. a definite integral. This is achieved by breaking the interval down into multiple subintervals and calculating the sum of areas of rectangles whose base is the subinterval, and height is the result of the function at the midpoint of the subinterval.
So, to calculate definite integral of f(x) on interval a, b we break it into N parts {x1, x2 … xN} where x1=a & xN=b and calculate:

![alt text](http://i.imgur.com/cnHvDqC.png "∫abf(x)dx ~ limN→∞ ∑i=1N f(xi-1/2+xi/2)(xi−xi-1)")

 
