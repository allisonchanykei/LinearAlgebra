// Mr. Arkiletian ICTP 12
// Simultaneous linear equation assignment (2 team members)
// Solved using the STL generic vector container class 


#include <iostream>
#include <vector>
#include <map>
#include <cmath> // for pow function

using namespace std;

typedef vector <double> Dvector;
typedef vector <Dvector> Dmatrix;
typedef map <Dmatrix,double> Dmap;

// Prototypes (variable names included, but not needed)
// DO NOT change any prototypes!! NO other functions allowed.

Dmatrix GetA(); 
// gets the matrix A from the user and returns it

Dvector Getb(const int &siz); 
// gets the vector b from the user and returns it

void Display(const Dvector &xvect); 
// displays the contents of vector xvect

void Display(const Dmatrix &Amat); 
// displays the contents of matrix Amat (Note: Display function is overloaded)

Dvector Solvex(const Dmatrix &Amat, const Dvector &bvect);
// Solves for systems of linear equations in the form Ax=b using cramer's rule 

double Det(const Dmatrix &Amat, Dmap &map);
// returns the Determinant of matrix Amat using a recursive algorithm
// base case is 2x2 matrix 

Dmatrix Replace(Dmatrix Rmat, const int col, const Dvector &bvect);
// Replaces the column 'col' in Rmat with bvect and returns Rmat

Dmatrix Minor(const Dmatrix &Amat, const unsigned int col);
// Gets the Minor matrix of Amat by crossing out the first row and 
// column 'col' then returns that smaller matrix


//-------------------------------------------
int main(){

Dmatrix A;     
Dvector b,x;


A=GetA();
Display(A);
b=Getb(A.size());
x=Solvex(A,b);
Display(x);

return(0);
}
//-------------------------------------------
Dmatrix GetA(){
	Dmatrix vecvec;
	int val;
	int size;
	cin>>size;
	for (int x=0;x<size;++x){
		Dvector temp;
		for (int y=0;y<size;++y){
			cin>>val;
			temp.push_back(val);
		}
		vecvec.push_back(temp);
	}
	return vecvec;
}
Dvector Getb(const int &siz) {
	Dvector b;
	int val;
	for (int x = 0; x < siz; ++x) {
		cin >> val;
		b.push_back(val);
	}
	return b;
}
void Display(const Dvector &xvect) {
	for (unsigned int x = 0; x < xvect.size(); ++x)
		cout << xvect[x]<<endl;
}
void Display(const Dmatrix &Amat) {
	for (unsigned int x = 0; x < Amat.size(); ++x) {
		for (unsigned int y = 0; y < Amat[x].size(); ++y) {
			cout << Amat[x][y]<<" ";
		}
		cout << endl;
	}
}
Dvector Solvex(const Dmatrix &Amat, const Dvector &bvect) {
	Dvector ans;
	Dmap map;
	double a = Det(Amat,map);
	for (unsigned int x = 0; x < Amat.size(); ++x) {
		Dmatrix An = Replace(Amat, x, bvect);
		double an = Det(An,map);
		double xn = an / a;
		ans.push_back(xn);
	}
	return ans;
}
double Det(const Dmatrix &Amat,Dmap &map) {	
	if (Amat.size()==2) {
		double pb;
		pb = Amat[0][0] * Amat[1][1] - Amat[0][1] * Amat[1][0];
		return pb;
	}
	double p;
	for (unsigned int y = 0; y < Amat[0].size(); ++y) {
		if (map.find(Minor(Amat,y))== map.end()){
			p = p + pow(-1, y) * Amat[0][y] * Det(Minor(Amat,y),map);
		}
		else{
			p = p + pow(-1, y) * Amat[0][y] * map.find(Minor(Amat,y))->second;
		}		
	}
	map.insert(pair<Dmatrix,double>(Amat,p));
	return p;
}

Dmatrix Replace(Dmatrix Rmat, const int col, const Dvector &bvect) {
	for (unsigned int x = 0; x < Rmat.size(); ++x) {
		Rmat[x][col] = bvect[x];
	}
	return Rmat;
}

Dmatrix Minor(const Dmatrix &Amat, const unsigned int col) {
	Dmatrix min;
	for (unsigned int x = 1; x < Amat.size(); ++x) {
		Dvector temp;
		for (unsigned int y = 0; y < Amat.size(); ++y) {
			if (y != col)
				temp.push_back(Amat[x][y]);
		}
		min.push_back(temp);
	}
	return min;
}
