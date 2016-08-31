#include "stdafx.h"
#include "Matrix.h"
#include "AlgLib\src\linalg.h"

using namespace alglib;
namespace Algebra
{
#pragma region Constructors
	Matrix::Matrix()
	{
		initDim(0, 0);
		for (int j = 0; j < this->size; ++j)
			this->M[j] = 0;
	}
	//
	void Matrix::initDim(const int &n, const int & m)
	{
		this->n = n;
		this->m = m;
		this->size = n*m;
		this->M = new double[this->size];
	}
	//
	//void Matrix::init()
	//{
	//	
	//
	//	for (int j = 0; j < this->size; ++j)
	//		this->M[j] = 0;
	//}
	//
	Matrix::Matrix(const int & N, const int & M)
	{
		initDim(N, M);
		for (int j = 0; j < this->size; ++j)
			this->M[j] = 0;
	}
	//
	Matrix::Matrix(const double *Arr, int N, int M)
	{
		initDim(N, M);
		for (int i = 0; i < size; ++i)
			this->M[i] = Arr[i];
	}
	//
	Matrix::Matrix(const alglib::real_2d_array &rArr)
	{
		initDim(rArr.rows(), rArr.cols());

		for (int i = 0; i < this->n; ++i)
			for (int j = 0; j < this->m; ++j)
				this->M[i*this->m + j] = rArr(i, j);
	}
	//
	Matrix::Matrix(const vector<double> &Vec, int N, int M, int offset)
	{
		initDim(N, M);

		if (this->size > Vec.size() + offset)
			throw invalid_argument("Invalid input data in Matrix constructor: input vector<double> is too short");
		for (int i = 0; i < size; ++i) this->M[i] = Vec[i];
	}
	//
	Matrix::Matrix(const vector<double> &Vec)
	{
		int N = Vec.size();
		initDim(N, 1);
		for (int i = 0; i < N; ++i)this->M[i] = Vec[i];
	}
	//
	Matrix::Matrix(triple Vec)
	{
		initDim(3, 1);

		for (int i = 0; i < 3; ++i)
			this->M[i] = Vec[i];
	}
	//copy-constuctor
	Matrix::Matrix(const Matrix & other)
	{
		this->n = other.n;
		this->m = other.m;
		this->size = other.size;
		this->M = new double[size];
		memcpy(this->M, other.M, sizeof(double)*size);

		//for (int i = 0; i < size; ++i)
		//	this->M[i] = other.M[i];
	}
#pragma endregion Constructors
	//
	Matrix::~Matrix()
	{
		delete[] M;
	}

#pragma region CopyTo
	//
	void Matrix::ToOneDimArr(double *&vec) const
	{
		vec = new double[size];
		for (int j = 0; j < this->size; ++j) vec[j] = this->M[j];
	}
#pragma endregion CopyTo

#pragma region Operators

	//assignment operator
	Matrix & Matrix::operator = (const Matrix & other)
	{
		if (this != &other) // self-assignment protection
		{
			this->n = other.n;
			this->m = other.m;
			this->size = other.size;

			delete[] M;
			this->M = new double[size];
			memcpy(this->M, other.M, sizeof(double)*size);
			/*for (size_t i = 0; i < size; ++i)
				this->M[i] = other.M[i];*/
		}
		return *this;
	}
	//set-get indexer
	double & Matrix:: operator ()(int i, int j) 
	{
		if (this->size >= (i + 1)*(j + 1))
			return this->M[i*this->m + j];
		else throw out_of_range("Matrix: Index is out of range.");
	}
	//get-only indexer
	const double & Matrix:: operator ()(int i, int j) const
	{
		if (this->size >= (i + 1)*(j + 1))
			return this->M[i*this->m + j];
		else throw out_of_range("Matrix: Index is out of range.");
	}
	//
	//set indexer
	double & Matrix:: at(int i, int j)
	{
		if (this->size >= (i + 1)*(j + 1))
			return this->M[i*this->m + j];
		else throw out_of_range("Matrix: Index is out of range.");
	}
	//get indexer
	const double & Matrix::at(int i, int j) const
	{
		if (this->size >= (i + 1)*(j + 1))
			return this->M[i*this->m + j];
		else throw out_of_range("Matrix: Index is out of range.");
	}
	//
	Matrix operator + (const Matrix &left, const  Matrix &right)
	{
		if (left.n != right.n && left.m != right.m)
			throw invalid_argument("Non-conformable matrices in Matrix operation.");
		Matrix res = Matrix(left.n, left.m);
		for (int j = 0; j < left.size; ++j) res.M[j] = left.M[j] + right.M[j];
		return res;
	}
	//
	Matrix operator-(const Matrix & left, const Matrix & right)
	{
		if (left.n != right.n || left.m != right.m)
			throw invalid_argument("Non-conformable matrices in Matrix operation.");
		Matrix res = Matrix(left.n, left.m);
		for (int j = 0; j < left.size; ++j) res.M[j] = left.M[j] - right.M[j];
		return res;
	}
	//
	Matrix operator*(const double & left, const  Matrix & right)
	{
		Matrix res = Matrix(right.n, right.m);
		for (int j = 0; j < right.size; ++j) res.M[j] = left * right.M[j];
		return res;
	}
	//
	triple operator *(const Matrix &left, const triple &right)
	{
		if (left.n != 3 && left.m != 3)
			throw invalid_argument("Non-conformable matrices in Matrix operation.");

		triple res = triple();
		for (int i = 0; i < 3; ++i)
		{
			double S = .0;
			for (int k = 0; k < 3; k++) S += left(i, k) * right[k];
			res[i] = S;
		}
		return res;
	}
	//
	Matrix operator/(const Matrix & left, const double & right)
	{
		Matrix res = Matrix(left.n, left.m);
		for (int j = 0; j < left.size; ++j) res.M[j] = left.M[j] / right;
		return res;
	}
	//
	Matrix operator*(const Matrix & left, const double & right)
	{
		Matrix res = Matrix(left.n, left.m);
		for (int j = 0; j < left.size; ++j) res.M[j] = right * left.M[j];
		return res;
	}
	//
	Matrix operator*(const Matrix & a, const Matrix & b)
	{
		int aRows = a.n;
		int aCols = a.m;
		int bRows = b.n;
		int bCols = b.m;
		if (aCols != bRows)
			throw invalid_argument("Matrix: Non-conformable matrices in Matrix Product");

		Matrix res = Matrix(aRows, bCols);
		for (int i = 0; i < aRows; ++i)
			for (int j = 0; j < bCols; ++j)
				for (int k = 0; k < aCols; ++k)
					res(i, j) += a(i, k) * b(k, j);
		return res;
	}
	//
	void Matrix::operator+=(const Matrix & right)
	{
		if (this->n != right.n || this->m != right.m)
			throw invalid_argument("Non-conformable matrices in Matrix operation.");
		for (size_t i = 0; i < this->size; ++i)
		{
			this->M[i] += right.M[i];
		}
	}
	//
	void Matrix::operator-=(const Matrix & right)
	{
		if (this->n != right.n || this->m != right.m)
			throw invalid_argument("Non-conformable matrices in Matrix operation.");
		for (size_t i = 0; i < this->size; ++i)
		{
			this->M[i] -= right.M[i];
		}
	}
	//
	void Matrix::operator*=(const double & right)
	{
		for (size_t i = 0; i < this->size; ++i)
		{
			this->M[i] *= right;
		}
	}
	//
	void Matrix::operator/=(const double & right)
	{
		for (size_t i = 0; i < this->size; ++i)
		{
			this->M[i] /= right;
		}
	}
#pragma endregion

	//vector
	void Matrix::setFromVec(int offset, const vector<double> &V) 
	{
		if (this->size + offset > V.size()) throw invalid_argument("Can't set from vector: vector too short.");
		for (int j = 0; j < this->size; ++j) this->M[j] = V[j + offset];
	}
	//vector
	void Matrix::copyToVec(int offset, vector<double> &F) const
	{
		if (this->size + offset > F.size()) throw invalid_argument("Can't copy to vector: vector too short.");
		for (int j = 0; j < this->size; ++j) F[j + offset] = this->M[j];
	}
	//
	void Matrix::Clear()
	{
		delete[] M;
		initDim(0, 0);
	}
	//Zero
	void Matrix::Zero()
	{
		for (int j = 0; j < this->size; ++j) this->M[j] = 0.0;
	}
	//Identy
	void Matrix::Identy()
	{
		for (int i = 0; i < this->n; ++i)
			for (int j = 0; j < this->m; ++j)
			{
				if (i == j)
					this->M[i*this->m + j] = 1.0;
				else
					this->M[i*this->m + j] = 0.0;
			}
	}
	//
	Matrix  Matrix::PrimeDiag() const
	{
		int L = (this->m < this->n) ? this->m : this->n;
		Matrix res(L, 1);
		for (int i = 0; i < L; ++i)
			res(i, 0) = (*this)(i, i);
		return res;
	}
	//Trace
	double Matrix::Trace() const
	{
		int L = (this->m < this->n) ? this->m : this->n;
		double res = 0;
		for (int i = 0; i < L; ++i)
			res += (*this)(i, i);
		return res;
	}
	//Transpose
	Matrix Matrix::Transpose()
	{
		Matrix res = Matrix(this->m, this->n);
		for (int i = 0; i < this->n; ++i)
			for (int j = 0; j < this->m; ++j) res(j, i) = M[i*this->m + j];
		return res;
	}
	//Invertion
	Matrix Matrix::Inverse()
	{
		if (this->n == 0 || this->m == 0)
			throw invalid_argument("empty matrices in Matrix operation.");

		if (this->n != this->m)
			throw invalid_argument("Non-conformable matrices in Matrix operation.");
		Matrix Minv;
		int N = this->n;
		try
		{
			alglib::real_2d_array A;
			A.setcontent(n, m, this->M);
			integer_1d_array pivots;
			matinvreport rep;
			ae_int_t inf;
			alglib::rmatrixlu(A, N, N, pivots);
			alglib::rmatrixluinverse(A, pivots, N, inf, rep);
			Minv = Matrix(A);
		}
		catch (...)
		{
			throw invalid_argument("Can't compute inverse matrix.");
		}
		return  Minv;
	}
	double Matrix::SumSq() const
	{
		double res = 0;
		//for (double *val = this->M; val++; )
		//	res += *val;
		for (int i = 0; i < this->size; i++)
			res += M[i]* M[i];
		return res;
	}
	//Rotaton
	void Matrix::Rotate(Axis axis, double angle)
	{
		double _sin = sin(angle);
		double _cos = cos(angle);
		initDim(3, 3);
		switch (axis)
		{
		case Axis::X: this->M = new double[size] { 1.0,	 0.0,	0.0, 
												   0.0, _cos, -_sin, 
												   0.0, _sin,  _cos };
					  break;
		case Axis::Y: this->M = new double[size] { _cos, 0.0, _sin, 
													0.0, 1.0,  0.0,
												  -_sin, 0.0, _cos };
					  break;
		case Axis::Z: this->M = new double[size] { _cos, -_sin, 0.0,
												   _sin,  _cos, 0.0,
													0.0,   0.0, 1.0 };
					  break;
		default:
			throw out_of_range("Axis index is out of range.");
		}
	}
	//Maximum module
	double Matrix::MaxMod()
	{
		double Max = 0;
		for (int j = 0; j < this->size; ++j)
		{
			double D = abs(this->M[j]);
			if (D > Max) Max = D;
		}
		return Max;
	}
	//
	std::string Matrix::toString(char* sep, char* format, int L) const
	{
		string str = "";
		char buf[30];
		for (int i = 0; i < this->size; ++i)
		{
			std::sprintf(buf, format, this->M[i]);
			str += buf;
			str += sep;
		}
		return str;
	}
	//
	std::string Matrix::toString(char* sep, char* format, int L, int isSplitByRows) const
	{
		string str = "";
		char *buf = new char[L];
		for (int i = 0; i < this->size; ++i)
		{
			std::sprintf(buf, format, this->M[i]);
			str += buf;
			if (isSplitByRows && ((i + 1) % this->m) == 0) str += "\n";
			else str += sep;
		}
		delete[] buf; 
		return str;
	}
	//
	std::string Matrix::toString(char* sep) const
	{
		string str = "";
		for (int i = 0; i < this->size; ++i)
		{
			string buf = std::to_string(this->M[i]);
			str += buf;
			str += sep;
		}
		return str;
	}
	//
	std::string Matrix::toString() const
	{
		return this->toString("\t");
	}
	//
	bool Matrix::LeastSQRSolve(Matrix &A, Matrix &b, Matrix &X, Matrix &Q)
	{
		if (A.n < 2 || A.m < 2) return false;
		if (b.n != A.n) return false;

		Matrix qt, r;
		if (!QRdecomp(A, qt, r)) return false;
		Matrix l = qt*b;
		X = Matrix(A.m, 1);
		int i, j;
		int n = X.n;

		//Gaussian reverse
		double sum;
		for (i = n - 1; i >= 0; i--)
		{
			sum = l(i, 0);
			for (j = i + 1; j < n; ++j)
				sum -= r(i, j) * X(j, 0);
			X(i, 0) = sum / r(i, i);
		}
		Q = (A.Transpose()*A).Inverse();

		return true;
	}
	//
	bool Matrix::QRdecomp(Matrix &A, Matrix &Qt, Matrix &R)
	{
		try
		{
			int N = A.n;
			int M = A.m;
			real_2d_array a;
			a.setcontent(N, M, A.M);
			real_1d_array tau;
			real_2d_array q;

			alglib::rmatrixqr(a, N, M, tau);
			rmatrixqrunpackq(a, N, M, tau, M, q);
			Matrix Q = Matrix(q);
			Qt = Q.Transpose();
			R = Qt *A;
		}
		catch (...)
		{
			return false;
		}
		return true;
	}
	//
	Matrix Matrix::subMatrix(int n0, int nSize, int m0, int mSize) const
	{
		if (m0 < 0 || n0 < 0) throw ("negative Matrix indexes");
		if (this->n < n0 + nSize || this->m < m0 + mSize) throw ("subMatrix bounds are greater than bounds of original Matrix ");
		Matrix Out = Matrix(nSize, mSize);

		for (int i = 0; i < nSize; ++i)
			for (int j = 0; j < mSize; ++j)
			{
				int k = (n0 + i)*m + m0 + j;
				Out(i, j) = this->M[k];
			}
		return Out;
	}
	//
	void Matrix::addRows(const Matrix &newRows)
	{
		if (this->size == 0)
		{
			this->initDim(newRows.n, newRows.m);
			memcpy(this->M, newRows.M, sizeof(double)*this->size);
			return;
		}
		//
		if (this->m != newRows.m) throw("Can't merge two matricis with the different columns number");

		int newSize = this->size + newRows.size;
		double *newM = new double[newSize];

		memcpy(newM, this->M, sizeof(double)*this->size);
		memcpy(newM + size, newRows.M, sizeof(double)*newRows.size);
		delete[] this->M;

		this->M = new double[newSize];
		memcpy(this->M, newM, sizeof(double)*newSize);
		delete[] newM;

		this->n += newRows.n;
		this->size = newSize;
	}
}
