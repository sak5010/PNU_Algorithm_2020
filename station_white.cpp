#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

vector<double> A(3);
vector<double> B(3);
vector<double> P(3);
const double epsilon = 0.0001;
double ans = 1e9;

void input(ifstream& ifs) {
	for(int i=0; i<3; ++i)
		ifs >> A[i];
	for(int i=0; i<3; ++i)
		ifs >> B[i];
	for(int i=0; i<3; ++i)
		ifs >> P[i];
}

double calc(const vector<double>& p1, const vector<double>& p2) {
	double ret = 0;
	for(int i=0; i<3; ++i) {
		ret += (p1[i] - p2[i]) * (p1[i] - p2[i]);
	}
	return ret;
}

double mdist(double lt, double rt) {
	double mt = (lt+rt)/2.0;
	
	vector<double> M(3);
	for(int i=0; i<3; ++i)
		M[i] = mt*B[i] + (1-mt)*A[i];
	ans = min(ans, calc(M, P));
	
	double tolt = mt - epsilon;
	double tort = mt + epsilon;
	
	if(tort > rt)
		return ans;
	for(int i=0; i<3; ++i)
		M[i] = tolt*B[i] + (1-tolt)*A[i];
	double toltcal = calc(M, P);
	ans = min(ans, toltcal);
	
	for(int i=0; i<3; ++i)
		M[i] = tort*B[i] + (1-tort)*A[i];
	double tortcal = calc(M, P);
	ans = min(ans, tortcal);
	
	if(toltcal > tortcal)
		ans = mdist(mt, rt);
	else
		ans = mdist(lt, mt);
		
	return ans;
}

int main(void) {
	ifstream ifs("station.inp");
	ofstream ofs("station.out");
	input(ifs);
	int result = ceil(sqrt(mdist(0.0, 1.0)));
	ofs << result;
	ifs.close();
	ofs.close();
	return 0;
}
