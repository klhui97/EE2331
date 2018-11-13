// Student name:
// Student ID  :

/*
	Submission deadline: Wed, 14 Nov 2018, 11:59 pm

	Part-1: Implement the function fib_i().

	Part-2: Implement the function findNumTargetSum(),
		   and modify the statement that calls findNumTargetSum in part_2().

	Upload your .cpp file to Canvas.
	Put down your name and student ID at the top of your file.

	10% Marks will be deducted if
	- Submission without name or ID 
	- Submission of other file types

	Late submission or submission by other means are not accepted.
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

long long fib_r(int n)  // compute Fibonacci number using recursion
{
	if (n == 0)
		return 0;

	if (n == 1)
		return 1;

	return fib_r(n-2) + fib_r(n-1);
}

long long fib_i(int n)  // compute Fibonacci number using iteration
{
	// Implement this function using for-loop or while-loop.

	if (n == 0)
		return 0;
	if (n == 1)
		return 1;

	long long fn_1 = 1, fn_2 = 0, fn;

	for (int i = 2; i <= n; i++)
	{
		fn = fn_2 + fn_1;
		fn_2 = fn_1;
		fn_1 = fn;
	}
	return fn;
}


//bool findNumTargetSum( /* parameters required by your function */ )
/*
{
	// Recursive function to find if a subset of the numbers in the input array
	// is added up to a give target value.

	// Required input parameters include 
	//	- input array of integers and the length of the array
	//	- array for storing the solution, and length of the result array passed by reference
	//	- other parameters for the control of recursion

	// The input array is sorted in ascending order. This property may help to
	// improve the computation efficiency to some exend.

	// The function returns ture if a solution is found; otherwise returns false.

}
*/

bool findNumTargetSum(const int a[], int n, int i, int targetSum, int c[], int& k)
{
	// In the current level of recursion, the program considers if a[i]
	// is included or not included in the solution.

	if (targetSum == 0) // solution found
		return true;

	if (i >= n || a[i] > targetSum) // failing case, no solution
		return false;			
	
	// option 1  : include a[i] in the solution
	c[k] = a[i];
	k += 1;
	
	if (findNumTargetSum(a, n, i+1, targetSum-a[i], c, k))
		return true;

	// option 2 (backtrack) : NOT to include a[i] in the solution
	k -= 1;
	return findNumTargetSum(a, n, i+1, targetSum, c, k);		
}

void part_1()
{
	// Observe the speed of the recursive function and the non-recursive function

	cout << "Part-1: recursion\n";

	clock_t begin, end;
	double elapsedTime;

	cout << "Compute Fibonacci number using recursion:\n";
	begin = clock();
	for (int i = 2; i < 40; i += 4)
		cout << "fib_r(" << i << ") = " << fib_r(i) << endl;
	end = clock();
	elapsedTime = (double)(end - begin)/CLOCKS_PER_SEC;
	cout << "*** Elapsed time = " << elapsedTime << " seconds\n";

	cout << "\nCompute Fibonacci number using iteration:\n";
	begin = clock();
	for (int i = 2; i < 40; i += 4)
		cout << "fib_i(" << i << ") = " << fib_i(i) << endl;
	end = clock();
	elapsedTime = (double)(end - begin)/CLOCKS_PER_SEC;
	cout << "*** Elapsed time = " << elapsedTime << " seconds\n";
}

int sum(int x[], int n)
{
	int total = 0;
	for (int i = 0; i < n; i++)
		total += x[i];

	return total;
}

void printArray(int x[], int n)
{
	for (int i = 0; i < n; i++)
	{
		if (i > 0 && i % 10 == 0)
			cout << endl;
		cout << x[i] << ", ";
	}
	cout << endl << endl;
}

void part_2()
{
	// Test data: the array is sorted in ascending order.
	int a[] = {8, 12, 20, 35, 36, 41, 55, 64, 72, 81};  
	int n = 10;

	int c[10];  // array for storing the solution
	int k = 0;  // k = number of elements in c[]

	cout << "\n-----------------------------------------------------------\n";
	cout << "Part-2: recursion and backtracking\n";

	cout << "Numbers in input list:\n";
	printArray(a, n);

	int total = sum(a, n);
	cout << "sum of the numbers in input list = " << total << endl << endl;

	bool success = false;

	for (int i = 1; i < 7; i++)  // try 6 test cases
	{
		int target = total * i / 7 + 2;
		k = 0;

		// Design a recursive function to find if a subset of numbers in
		// a[] can be added up to the given target value.
		// The solution is stored in array c[], and k is the number of elements in c[].

		// success = findNumTargetSum( /* parameters required by your recursive function */ );

		success = findNumTargetSum(a, n, 0, target, c, k);
		if (success)
		{
			cout << "Numbers in input list that add up to " << target << " :\n";
			printArray(c, k);
		}
		else
			cout << "DO NOT find subset of numbers in input list that add up to " << target << endl << endl;
	}
}

int main()
{	
	//part_1();
	part_2();

	system("pause");
	return 0;
}