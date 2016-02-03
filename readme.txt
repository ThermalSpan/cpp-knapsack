Knapsack
=======

To folder includes my knapsack instance solver and some testing utilities. Run make and the executables will be
put in the bin folder.

To use, run the executable called knapsack with the test case as an argument. As a default it will use
a dynamic programming based algorithm. Run "./knapsack -h" for more information.

My findings suggest that when the n * c are both reasonable values, dynamic programming is both faster and more consistant. 
However, when n * c grows in magnitude, or when c is very large and n is relativley small, branch and bound is better. 

In general, data sets with a strong, or approximatley strong correlation are much "harder" than completley uncorrelated
data sets. This is reflected in a higher node count with the branch and bound algorithm. 

I tried, unsuccessfully so far, to implement a more competent algorithm based on Pissingers's "minknap" algorithm. This
is based on the observation that generaly an optimal solution to the 0-1 knapsack problem will share a large portion of
its decision vector with the "greedy" solution. My findings confirm this. 
