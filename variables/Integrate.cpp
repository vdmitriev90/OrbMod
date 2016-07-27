#include"stdafx.h"
#include"Integrate.h"

#define ISDEBUG 1

using namespace std;
namespace OrbMod
{
	ivar::ivar()
	{
	};
	ivar::~ivar()
	{
	};
	//
	void ivar::stepDs(double ds, double S, vector<double> &X, vector< vector<double>> &B, vector<double> &F0, vector<double> &P, vector<double> &Y)
	{
		double dt = abs(ds / S);
		for (int k = 0; k < N; k++)
			P[k] = 0.0;
		for (int j = K - 1; j >= 0; j--)
			for (int k = 0; k < N; k++)
				P[k] = dt*(B[j][k] + P[k]);
		for (int k = 0; k < N; k++)
			Y[k] = X[k] + ds*(F0[k] + P[k]);
	};
	//
	void ivar::endOfStep(double t0, double H, vector<double> &X, vector<double> &Y, vector<double> &F0, vector<double> &P, vector<vector<double>> &B)
	{
		for (int k = 0; k < N; k++)
			P[k] = 0.0;

		for (int j = K - 1; j >= 0; j--)
			for (int k = 0; k < N; k++)
				P[k] = B[j][k] + P[k];

		for (int k = 0; k < N; k++)
			X[k] = X[k] + H*(F0[k] + P[k]);
	}
	//
	void ivar::FODE(vector<double> &X, double to, double &te_, double &step, int NOR, int NI, int &NS, int &NBS)
	{
		K = NOR / 2;
		this->te = te_;

		double err = Global::eps;
		if (!Global::IsAutoStep)
			err = 0;

		vector<vector<double>>	_S(K, vector<double>(K));
		vector<vector<double>> A(K, vector<double>(N)), B(K, vector<double>(N)), BL(K, vector<double>(N));
		vector<vector<double>> C(K + 1, vector<double>(K + 1)), D(K + 1, vector<double>(K + 1)), E(K + 1, vector<double>(K + 1));
		vector<double>  Y(N), F(N), F0(N), P(N), XK(N), Yo(N);
		vector<double> SPC(K + 1);

#ifdef ISDEBUG
		FILE *fodbg = fopen("debug.out", "w");
#endif

		const double EPS = 1e-15;
		const double SGM = 3.16;
		const int IPS0 = 100;
		bool  LS, VS, INC = true, CNV;
		clock_t start = clock();
		//Input parameters
		int NST = 0;
		int IPS = IPS0;
		int it = 0;
		vector<double> dX(N);

#pragma region Предварительные вычисления

		SPC[0] = 0.0;
		int L = K*(NOR - K - 1);
		for (int i = 1; i <= K; i++)
			SPC[i] = spacing[i + L - 1];

		// 1/(Taui-Tauj)
		for (int i = 1; i <= K; i++)
			for (int j = 1; j <= i - 1; j++)
				_S[i - 1][j - 1] = 1.0 / (SPC[i] - SPC[j]);

		// Cij Dij
		C[0][0] = 1.0;
		D[0][0] = 1.0;

		for (int j = 1; j <= K; j++)
			for (int i = j; i <= K; i++)
			{
				C[i][j] = C[i - 1][j - 1] - SPC[i - 1] * C[i - 1][j];
				D[i][j] = D[i - 1][j - 1] + SPC[j] * D[i - 1][j];
			}
		// eij
		for (int j = 0; j <= K; j++)
			E[j][0] = 1.0;

		for (int i = 1; i <= K; i++)
			for (int j = 1; j <= i; j++)
				E[i][j] = E[i - 1][j - 1] + E[i - 1][j];

		//Нормализация
		for (int i = 1; i <= K; i++)
		{
			double cf = i + 1;
			for (int j = 0; j <= K; j++)
			{
				C[j][i] /= cf;
				D[i][j] *= cf;
				E[i][j] *= cf;
			}
		}

		//sigma
		double DEG = 1.0 / (K + 1);
		double RMX = pow(SGM, DEG);
		double RMN = 1.0 / RMX;

		//Направление интегрирования
		double DIR = (te - to) / abs(to - te);
		Global::Discr *= DIR;
		double H_ = abs(step);
		VS = err != 0;
		CNV = NI <= 0;
		double t = to;
		double B_ = 0;
		IPS = IPS0;
		//метка 3
	M3: double H = H_*DIR;
		double R = 1.0;
		LS = false;
		for (int k = 0; k < N; k++)
		{
			XK[k] = 0.0;
			for (int i = 0; i < K; i++)
				B[i][k] = 0.0;
		}

#pragma endregion

		//Начальное значение шага
#pragma region Начальное значение шага
		if (H_ == 0)
		{
			if (!VS)throw("Zero Constant Step!");
			///////////////////////////////////////
			force(to, X, F0);
			H_ = EPS;
			B_ = 0.0;
			while (B_ == 0)
			{
				H_ = H_*10.0;
				H = H_*DIR;
				for (int j = 0; j < N; j++)
					Y[j] = X[j] + H*F0[j];
				if (abs(te - to) <= H_)
					goto M1;
				///////////////////////////////
				force(to + H, Y, F);

				for (int j = 0; j < N; j++)
				{
					double d = (F[j] - F0[j]);
					B_ = B_ + d*d;
				}
			}
			H_ = sqrt(2.0*err*H_ / sqrt(B_));
			H = H_*DIR;
		}

#pragma endregion

		//Начало процесса интегрирования
#pragma region Начало интегрирования
		M1 :
		   if (abs(te - t) <= H_)
		   {
			   step = H_;
			   H = te - t;
			   H_ = abs(H);
			   R = R*H_ / step;
			   LS = true;
		   }
		   if (NS <= 1)
		   {
			   for (int i = 0; i < K; i++)
				   for (int j = 0; j < N; j++)
					   BL[i][j] = B[i][j];
		   }
#pragma endregion

#ifdef ISDEBUG
		   fprintf(fodbg, "%19.12e\t%12.8f\t%d\n", t, H, it);
#endif // DEBUG

		   double q = 1.0;

#pragma region A+dA
		   for (int l = 0; l < K; l++)
		   {
			   for (int i = 0; i < N; i++)
				   P[i] = 0.0;

			   for (int m = l; m < K; m++)
				   for (int i = 0; i < N; i++)
					   P[i] = P[i] + E[m + 1][l + 1] * B[m][i];
			   q = q*R;
			   for (int i = 0; i < N; i++)
			   {
				   B[l][i] = B[l][i] - BL[l][i];

				   BL[l][i] = P[i] * q / (l + 2);
				   B[l][i] = BL[l][i] + B[l][i];
			   }
		   }
		   //</A+dA>  
#pragma endregion

#pragma region Alpha
		   for (int l = 0; l < K; l++)
		   {
			   for (int i = 0; i < N; i++)
				   P[i] = 0.0;

			   for (int m = l; m < K; m++)
				   for (int i = 0; i < N; i++)
					   P[i] = P[i] + D[m + 1][l + 1] * B[m][i];

			   for (int i = 0; i < N; i++)
				   A[l][i] = P[i];
		   }
#pragma endregion

		   force(t, X, F0);

#pragma region Корректор
		   //<Итерационный процесс на шаге>
		   for (it = 1; it < IPS; it++)
		   {
			   double s, t_;
			   int j, k;
			   //#pragma omp parallel for\
   			//firstprivate (P,H,B,F,Y,A) \
   			//private (s,t_,j,k) \
   			//lastprivate(A)

			   for (int i = 0; i < K; i++)
			   {
				   s = SPC[i + 1];
				   for (k = 0; k < N; k++)
					   P[k] = 0.0;
				   for (j = K - 1; j >= 0; j--)
					   for (k = 0; k < N; k++)
						   P[k] = s*(B[j][k] + P[k]);

				   for (k = 0; k < N; k++)
					   Y[k] = X[k] + H*s*(F0[k] + P[k]);

				   ////////////////////////////////////////
					//#pragma omp atomic
				   t_ = t + H*s;
				   force(t_, Y, F);

				   for (k = 0; k < N; k++)
					   P[k] = (F[k] - F0[k]) / s;

				   for (j = 0; j < i; j++)
					   for (k = 0; k < N; k++)
						   P[k] = (P[k] - A[j][k])*_S[i][j];

				   for (j = 0; j <= i; j++)
					   for (k = 0; k < N; k++)
						   B[j][k] = B[j][k] + C[i + 1][j + 1] * (P[k] - A[i][k]);

				   for (k = 0; k < N; k++)
					   A[i][k] = P[k];
			   }

			   //<выход из итераций если сошлись>
			   for (int k = 0; k < N; k++)
				   dX[k] = Y[k] - XK[k];
			   bool b = true;
			   for (int k = 0; k < N; k++)
				   if (!(abs(dX[k]) <= abs(EPS*Y[k])))
					   b = false;

			   for (int k = 0; k < N; k++)
				   XK[k] = Y[k];

			   if (b == true) break;
		   }
#pragma endregion

		   if ((it > IPS0) && (!CNV) && (NS != 0)) NBS++;

#pragma region Проверка величины шага
		   if (VS)
		   {
			   B_ = 0.0;
			   for (int k = 0; k < N; k++)
			   {
				   double b2 = B[K - 1][k] * B[K - 1][k];
				   B_ = B_ + b2;
			   }

			   if (B_ != 0)
				   R = pow((err / sqrt(B_) / H_), DEG);
			   else
				   R = RMX;
			   if (NS == 0)
			   {
				   INC = (!LS) && INC;
				   if (INC && (R > RMX) || (R < RMN))
				   {
					   NST++;
					   if ((NST > 100) && (R > RMX)) goto M4;
					   H_ = H_*R; goto M3;
				   }
			   }
			   //metka4
		   M4:	if (R > RMX) R = RMX;
		   }
#pragma endregion

		   if (Inter(t, H, X, Yo, F0, P, B)) LS = true;

		   // Решение на шаге
		   endOfStep(t, H, X, Yo, F0, P, B);

		   t = t + H;
		   H = H*R;
		   H_ = abs(H);
		   NS++;

		   if (CNV)
			   IPS = IPS0;
		   else
			   IPS = NI;

		   if (LS)
		   {
			   te = t;
#ifdef ISDEBUG
			   fclose(fodbg);
#endif
			   return;
		   }
		   goto M1;
	};
}