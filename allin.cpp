#include <bits/stdc++.h>
using namespace std;

vector<int> price;
vector< pair<int, int> > p;
int profit=0;

int Minimum(int low, int high, int* MIN) {
	int temp, day;
	temp = price[low];
	for(int i=low; i<=high; ++i) {
		if(temp >= price[i]) {
			temp = price[i];
			*MIN = temp;
			day = i+1;
		}
	}
	return day;
}

int Maximum(int low, int high, int* MAX) {
	int temp, day;
	temp = price[low];
	for(int i=high; i>=low; --i) {
		if(temp <= price[i]) {
			temp = price[i];
			*MAX = temp;
			day = i+1;
		}
	}
	return day;
}

void compare(int low, int mid, int high) {
	int tempProfit = 0, tempSell, tempBuy, MAX, MIN;
	
	if(low <= mid)
		tempBuy = Minimum(low, mid, &MIN);
	if(mid+1 <= high)
		tempSell = Maximum(mid+1, high, &MAX);
	
	tempProfit = MAX - MIN;
	
	if(profit < tempProfit) {
		profit = tempProfit;
		p.clear();
		p.push_back(make_pair(tempBuy, tempSell));
	} else if(profit == tempProfit) {
		p.push_back(make_pair(tempBuy, tempSell));
	}
}

void mergeSort(int low, int high) {
	if(low < high) {
		int mid = (low+high)/2;
		mergeSort(low, mid);
		mergeSort(mid+1, high);
		compare(low, mid, high);
	}
}

bool cmp(const pair<int, int>& p1, const pair<int, int>& p2) {
	if(p1.first != p2.first)
		return p1.first > p2.first;
	else
		return p1.second < p2.second;
}

int main(void) {
	int N, n;
	
	ifstream ifs("allin.inp");
	ifs >> N;
	for(int i=0; i<N; ++i) {
		ifs >> n;
		price.push_back(n);
	}
	ifs.close();
	
	mergeSort(0, N-1);
	sort(p.begin(), p.end(), cmp);
	
	ofstream ofs("allin.out");
	ofs << p[0].first << " " << p[0].second;
	ofs.close();
	
	return 0;
}
