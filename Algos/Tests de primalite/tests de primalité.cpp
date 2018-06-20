// Tests de primalité.cpp : définit le point d'entrée pour l'application console.
//

#include <stdlib.h>     /* srand, rand */
#include <iostream>
#include <math.h>       /* sqrt */
#include <stdio.h>
#include <ctime>
#include <iostream>
#include <fstream>

struct Jacobi
{
	bool sign;		// true = positive 
	unsigned int m, n;
};

template <typename T>
T fast_pow(T base, T exp, T modulus) {
	base %= modulus;
	T result = 1;
	while (exp > 0) {
		if (exp & 1) result = (result * base) % modulus;
		base = (base * base) % modulus;
		exp >>= 1;
	}
	return result;
}


bool Miller_Rabin_aux(unsigned int n, unsigned int k, unsigned int m) {
	unsigned int a = 1 + rand() % (n - 1);
	long long int b = fast_pow((long long int) a, (long long int) m, (long long int)n);
	if (b == 1)
		return true;

	b %= n;

	for (unsigned int i = 0; i < k; i++)
	{
		if (b == n - 1)
			return true;
		b = (b * b) % n;
	}
	return false;
}

/*


#n impair
def Miller_Rabin(n, nbTests = 100) :
k = 0
m = n - 1
while m & 1 == 0 :
m = m >> 1
k += 1
# n - 1 = 2 ^ k*m

for i in range(nbTests) :
a = randint(1, n - 1)
if not Miller_Rabin_aux(n, a, k, m) :
return False
return True
*/

bool Miller_Rabin(unsigned int n, unsigned int nbTests = 100) {
	unsigned int k = 0;
	unsigned int m = n - 1;

	while (m % 2 == 0)
	{
		m = m >> 1;
		k++;
	}
	// n - 1 = 2 ^ k*m

	for (unsigned int i = 0; i < nbTests; i++)
	{
		if (!Miller_Rabin_aux(n, k, m))
			return false;
	}
	return true;
}

bool is_prime_impair(unsigned int n) {

	unsigned sqrtn = floor(sqrt(n));

	if (n < 2)
		return false;

	for (int i = 3; i <= sqrtn; i += 2)
	{
		if (n % i == 0)
			return false;
	}
	return true;
}


bool J_getPowTwoVal(unsigned int n)
{
	if (n % 8 == (unsigned int)3 || n % 8 == (unsigned int)5)
		return false;	// -1

	return true;		// 1
}

void J_switchVal(Jacobi& j)
{
	if (j.m % 4 == (unsigned int)3 && j.n % 4 == (unsigned int)3)
		j.sign = !j.sign;
	unsigned int n = j.n;
	j.n = j.m;
	j.m = n;
}


void J_reducePowTwo(Jacobi& j)
{
	unsigned int k = 0;
	while (!(j.m & 1))
	{
		j.m = j.m >> 1;
		k++;
	}

	if (k % 2 == (unsigned int)1)
		j.sign = j.sign == J_getPowTwoVal(j.n);	// sign = sign * J_getPow...
}

void J_mod(Jacobi& j)
{
	j.m = j.m % j.n;
}

int calculate_Jacobi(unsigned int m, unsigned int n)
{
	Jacobi j;
	j.sign = true;
	j.m = m;
	j.n = n;

	while (j.m > (unsigned int)1)
	{
		if (j.m > j.n)
		{
			J_mod(j);
		}
		else
		{
			if (j.m % 2 == (unsigned int)0)
				J_reducePowTwo(j);
			else
				J_switchVal(j);
		}
	}
    
	if (j.sign)
		return (int)(j.m);
	return -(int)(j.m);
}

bool Solovay_Strassen_aux(unsigned int n, unsigned int a)
{
	int x = calculate_Jacobi(a, n);
	if (x == 0)
		return false;

	int long long y = fast_pow((int long long)(a), (int long long)((n - 1) / 2), (int long long)(n));

	return (((int long long)x - y) % n) == 0;
}

bool Solovay_Strassen(unsigned int n, unsigned int nbTests = 100)
{
	for (unsigned int i = 0; i < nbTests; i++)
	{
		if (!Solovay_Strassen_aux(n, 1 + rand() % (n - 1)))
			return false;
	}
	return true;
}

int main()
{
	printf(Miller_Rabin(709097) ? "true" : "false");
	std::clock_t start;

	std::ofstream myfile;
	myfile.open("tests.txt");
	myfile << "In ms. 1: naive, 2:solovay strassen; 3: miller rabin\n";

	unsigned int nb = 1e10;
	unsigned int ptNb = 10000;
	unsigned int step = nb / ptNb;

	unsigned int i1 = 0, i2 = 0, i3 = 0;

	for (unsigned int k = 3; k < nb; k+= step)
	{
		printf("%i \% \n", (int)(100 * (float)k / (float)nb));

		start = std::clock();
		for (unsigned int i = k; i < k + step; i += 2)
		{
			if (is_prime_impair(i))
				i1++;
		}
		// Average of times
		myfile << (std::clock() - start)/((double)(CLOCKS_PER_SEC / 1000)) << "\n";

		start = std::clock();
		for (unsigned int i = k; i < k + step; i += 2)
		{
			if (Solovay_Strassen(i))
				i2++;
		}
		// Average of times
		myfile << (std::clock() - start) / ((double)(CLOCKS_PER_SEC / 1000)) << "\n";

		start = std::clock();
		for (unsigned int i = k; i < k + step; i += 2)
		{
			if (Miller_Rabin(i))
				i3++;
		}
		// Average of times
		myfile << (std::clock() - start) / ((double)(CLOCKS_PER_SEC / 1000)) << "\n";


		myfile << "\n";
		myfile << i1 << " " << i2 << " " << i3 << "\n";

	}

	myfile.close();

}
