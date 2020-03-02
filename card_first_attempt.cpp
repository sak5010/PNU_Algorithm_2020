#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

int main(void) {
	ifstream ifs("cards.inp");
	int N, n;
	ifs >> N;
	int totalSum, missingSum, totalMul, missingMul, Sum, Mul;
	totalSum = 0, missingSum = 0, totalMul = 1, missingMul = 1;
	for(int i=0; i<N-2; ++i) {
		ifs >> n;
		missingSum += n;
		missingMul *= n;
	}
	for(int i=1; i<=N; ++i) {
		totalSum += i;
		totalMul *= i;
	}
	Sum = totalSum - missingSum;
	Mul = totalMul / missingMul;
	int a, b;
	for(int i=1; i<=Sum/2; ++i) {
		if(Mul == i*(Sum-i)) {
			a = i;
			b = Sum-i;
		}
	}
	ofstream ofs("cards.out");
	ofs << a << endl;
	ofs << b << endl;
		
	return 0;
}
