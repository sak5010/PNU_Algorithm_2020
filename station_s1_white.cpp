#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

struct Point {
    double x, y, z;
};

double dist(const Point& d1, const Point& d2) {
    return sqrt(pow(d2.x - d1.x, 2) + pow(d2.y - d1.y, 2) + pow(d2.z - d1.z, 2));
}

int mdist(const Point& a, const Point& b, const Point& p) {
    Point s;
    s.x = (a.x + b.x) / 2.0;
    s.y = (a.y + b.y) / 2.0;
    s.z = (a.z + b.z) / 2.0;

    int dap, dbp;
    dap = ceil(dist(a, p));
    dbp = ceil(dist(b, p));

    if(dap == dbp) {
        int dsp = ceil(dist(s, p));
        return dsp;
    }
    else if(dap > dbp) {
        return mdist(s, b, p);
    }
    else {
        return mdist(a, s, p);
    }
}

int main(void) {
    ifstream in("station.inp");

    Point a, b, p;
    in >> a.x >> a.y >> a.z;
    in >> b.x >> b.y >> b.z;
    in >> p.x >> p.y >> p.z;

    ofstream out("station.out");
    out << mdist(a, b, p);

	in.close();
	out.close();
	return 0;
}
