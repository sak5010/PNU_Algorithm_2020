#include <bits/stdc++.h>
using namespace std;

// epsilon
const double GAP = 0.0001;

vector <double> A(3);
vector <double> B(3);
vector <double> P(3);
double ans = 1e9;

double calc(const vector <double>& P1, const vector <double>& P2) {
	double ret = 0;
	for(int i=0; i<3; ++i)
		ret += (P1[i] - P2[i]) * (P1[i] - P2[i]);
	return ret;
}

double search(double tl, double tr) { // t_left, t_right
	double t = (tl+tr)/2.0;
	vector <double> tt(3);
	
	double totl = t - GAP;
	double totr = t + GAP;
	
	for(int i=0; i<3; ++i)
		tt[i] = t*A[i] + (1-t)*B[i];
	ans = min(ans, calc(P, tt));
	
	if(tl + GAP >= tr)
		return ans;
	
	for(int i=0; i<3; ++i)
		tt[i] = totl*A[i] + (1-totl)*B[i];
	double tlans = calc(P, tt);
	ans = min(ans, tlans);
	
	for(int i=0; i<3; ++i)
		tt[i] = totr*A[i] + (1-totr)*B[i];
	double trans = calc(P, tt);
	ans = min(ans, trans);
	
	if(tlans > trans)
		ans = min(ans, search(t, tr));
	else
		ans = min(ans, search(tl, t));
		
	return ans;
}

int main(void) {
	ifstream in("station.inp");
	ofstream out("station.out");
	for(int i=0; i<3; ++i)
		in >> A[i];
	for(int i=0; i<3; ++i)
		in >> B[i];
	for(int i=0; i<3; ++i)
		in >> P[i];
	out << ceil(sqrt(search(0,1)));
	in.close();
	out.close();
	return 0;
}
