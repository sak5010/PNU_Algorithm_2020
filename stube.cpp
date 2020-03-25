// (조교님 코드 참고) 
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

vector<double> A(3);
vector<double> B(3);
vector<double> C(3);
vector<double> D(3);
vector<double> P(3);
const double epsilon = 0.000001;
double ans = 1e9;

void input(ifstream& ifs) {
	for(int i=0; i<3; ++i)
		ifs >> A[i];
	for(int i=0; i<3; ++i)
		ifs >> B[i];
	for(int i=0; i<3; ++i)
		ifs >> C[i];
	for(int i=0; i<3; ++i)
		ifs >> D[i];
}

double calc(const vector<double>& p1, const vector<double>& p2) {
	double ret = 0;
	for(int i=0; i<3; ++i) {
		ret += (p1[i] - p2[i]) * (p1[i] - p2[i]);
	}
	return ret;
}

void setP(const vector<double>& M) {
	for(int i=0; i<3; ++i) {
		P[i] = M[i];
	}
}

double mdist(double lt, double rt, 
			const vector<double>& s1, const vector<double>& s2) {
	double mt = (lt+rt) / 2.0;
	
	vector<double> M(3);
	for(int i=0; i<3; ++i)
		M[i] = mt*s2[i] + (1-mt)*s1[i];
	ans = min(ans, calc(M, P));
	
	double tolt = mt - epsilon;
	double tort = mt + epsilon;
	
	if(tort > rt) {
		setP(M);
		return ans;
	}
	for(int i=0; i<3; ++i) {
		M[i] = tolt*s2[i] + (1-tolt)*s1[i];
	}
	
	double toltcal = calc(M, P);
	ans = min(ans, toltcal);
	
	for(int i=0; i<3; ++i) {
		M[i] = tort*s2[i] + (1-tort)*s1[i];
	}
	double tortcal = calc(M, P);
	ans = min(ans, tortcal);
	
	if(toltcal == tortcal) {
		return ans;
	}
	else if(toltcal > tortcal) {
		ans = mdist(mt, rt, s1, s2);
	}
	else {
		ans = mdist(lt, mt, s1, s2);
	}
	
	return ans;
}

int main(void) {
	ifstream ifs("stube.inp");
	ofstream ofs("stube.out");
	input(ifs);
	
	vector<double> M(3);
	setP(C);
	
	double prevResult = 0.0, result = 1.0;
	bool swit = true;
	const double biggerEpsilon = epsilon * 1000;
	while( !(abs(prevResult-result)<biggerEpsilon) ) {
		if(result < 0.01) {
			result = 0;
			break;
		}
		ans = 1e9;
		prevResult = result;
		if(swit) {
			result = sqrt(mdist(0.0, 1.0, A, B));
			swit = !swit;
		}
		else {
			result = sqrt(mdist(0.0, 1.0, C, D));
			swit = !swit;
		}
	}
	
/*
	result의 값이 floor(result)에 매우 가까울 경우 
	result를 floor(result)라고 바꿔야 
	올림을 했을 때 '답+1'이 나오는 것을 방지할 수 있다. 
*/ 
	if( (result-floor(result)) < biggerEpsilon ) {
		result = floor(result);
	}
	ofs << ceil(result);

	ifs.close();
	ofs.close();
	return 0;
}
