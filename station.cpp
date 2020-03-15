#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

typedef struct {
	int x, y, z;		
} Vector;

double inner_product(const Vector& v1, const Vector& v2) {
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

double norm(const Vector& v) {
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

bool is_abtuse(const Vector& v1, const Vector& v2) {
	// cos��Ÿ�� ����� ����, 0���ϸ� �����̰ų� �а��̴�.
	double costheta = inner_product(v1,v2) / (norm(v1)*norm(v2));
	
	if(costheta > 0.0)
		return false;
	else
		return true;
}

double which_case(const Vector& A, const Vector& B, const Vector& P) {
	Vector AtoP, AtoB, BtoP, BtoA;
	
	AtoP.x = P.x - A.x;
	AtoP.y = P.y - A.y;
	AtoP.z = P.z - A.z;
	
	AtoB.x = B.x - A.x;
	AtoB.y = B.y - A.y;
	AtoB.z = B.z - A.z;
	
	BtoP.x = P.x - B.x;
	BtoP.y = P.y - B.y;
	BtoP.z = P.z - B.z;
	
	BtoA.x = A.x - B.x;
	BtoA.y = A.y - B.y;
	BtoA.z = A.z - B.z;
	
	if( is_abtuse(AtoP, AtoB) ) { // AP�� AB�� �а��̰ų� �����̸�, 
		// ||AP||�� ���� ª�� ���̴�.
		return norm(AtoP);
	}
	else { // AP�� AB�� �����̰�, 
		if( is_abtuse(BtoP, BtoA) ) { // BP�� BA�� �а��̰ų� �����̸�, 
			// ||BP||�� ���� ª�� ���̴�.
			return norm(BtoP);
		}
		else { // AP, AB ���̰��� BP, BA ���̰� �� �� �����̶��, 
			// ���� ���� ������ ������ ���� ª�� ���� ã�´�.
			double costheta = inner_product(AtoP,AtoB) / (norm(AtoP)*norm(AtoB));
			double m = costheta * norm(AtoP);
			return sqrt(norm(AtoP)*norm(AtoP) - m*m);
		}
	}
}

int main(void) {
	ifstream ifs("station.inp");
	ofstream ofs("station.out");
	Vector A, B, P;
	
	ifs >> A.x >> A.y >> A.z;
	ifs >> B.x >> B.y >> B.z;
	ifs >> P.x >> P.y >> P.z;
	
	int result = (int)ceil(which_case(A, B, P));
	
	ofs << result;
	
	ifs.close();
	ofs.close();
	
	return 0;
}
