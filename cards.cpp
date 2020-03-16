#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

int main(void) {
	ifstream ifs("cards.inp");
	int N, n;
	ifs >> N;
	int totalSum, missingSum, totalSquareSum, missingSquareSum, sum, squareSum;
	totalSum = 0, missingSum = 0, totalSquareSum = 0, missingSquareSum = 0;
	for(int i=0; i<N-2; ++i) {
		ifs >> n;
		missingSum += n;
		missingSquareSum += n*n;
	}
	totalSum = N*(N+1)/2;
	totalSquareSum = N*(N+1)*(2*N+1)/6;
	sum = totalSum - missingSum; // a + b
	squareSum = totalSquareSum - missingSquareSum; // a^2 + b^2
	int a, b, ab;
	ab = (sum*sum - squareSum)/2;
	for(int i=1; i<=sum/2; ++i) {
		if(ab == i*(sum-i)) {
			a = i;
			b = sum-i;
		}
	}
	ofstream ofs("cards.out");
	ofs << a << endl;
	ofs << b << endl;
	
	ifs.close();
	ofs.close();
		
	return 0;
}
