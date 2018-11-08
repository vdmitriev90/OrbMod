#include"Integrate.h"
#include"Global.h"
#include"constant.h"

#include<time.h>

#define IS_IOUT 1
#define IS_DEBUG 0

using namespace std;

namespace OrbMod
{
    ivar::ivar()
    { };

    ivar::~ivar()
    { };

    //
    void ivar::stepDs(double ds, double S, vector<double> &X, vector<double> &Y)
    {
        double dt = abs(ds / S);
        for (int k = 0; k < N; k++)
            P[k] = 0.0;
        for (int j = K - 1; j >= 0; j--)
            for (int k = 0; k < N; k++)
                P[k] = dt * (B[j][k] + P[k]);
        for (int k = 0; k < N; k++)
            Y[k] = X[k] + ds * (F0[k] + P[k]);
    };
    //
    void ivar::endOfStep(double t0, double H, vector<double> &X, vector<double> &Y)
    {
        for (int k = 0; k < N; k++)
            P[k] = 0.0;

        for (int j = K - 1; j >= 0; j--)
            for (int k = 0; k < N; k++)
                P[k] = B[j][k] + P[k];

        for (int k = 0; k < N; k++)
            X[k] = X[k] + H * (F0[k] + P[k]);
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Everchart integrator for first-order differential qeuation (FODE)
    //implemented according to  http://scharmn.narod.ru/AVD/Gauss_15.pdf 
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    int ivar::Gauss_FODE(vector<double> &X, double to, double &te_, double &step, int NOR, int NI, int &NS, int &NBS)
    {
        K = NOR / 2;
        this->te = te_;

        this->err = Global::eps;
        if (!Global::IsAutoStep)
            this->err = 0;

        this->B = vector<vector<double>>(K, vector<double>(N));
        this->BL = vector<vector<double>>(K, vector<double>(N));

        //Y = vector<double>(N);
        F = vector<double>(N);
        F0 = vector<double>(N);
        P = vector<double>(N);
        XK = vector<double>(N);
        //Yo = vector<double>(N);

        vector<vector<double>>	_S(K, vector<double>(K));
        vector<vector<double>> C(K + 1, vector<double>(K + 1)), D(K + 1, vector<double>(K + 1)), E(K + 1, vector<double>(K + 1));
        vector<vector<double>>A(K, vector<double>(N));
        vector<double> Spacing(K + 1), dX(N), Y(N), Yo(N);

#if IS_IOUT
        FILE *foInteg; fopen_s(&foInteg,"integrator.out", "w");
#endif
#if IS_DEBUG
        fodbg = fopen("debug.out", "w");
#endif

        const int IPS0 = 100;
        bool  INC = true, CNV;
        clock_t start = clock();
        //Input parameters
        int NST = 0;
        int IPS = IPS0;
        int it = 0;

#pragma region Preliminary calculation

        Spacing[0] = 0.0;
        int L = K * (NOR - K - 1);
        for (int i = 1; i <= K; i++)
            Spacing[i] = consts::spacing[i + L - 1];

        // 1/(Taui-Tauj)
        for (int i = 1; i <= K; i++)
            for (int j = 1; j <= i - 1; j++)
                _S[i - 1][j - 1] = 1.0 / (Spacing[i] - Spacing[j]);

        // Cij Dij
        C[0][0] = 1.0;
        D[0][0] = 1.0;

        for (int j = 1; j <= K; j++)
            for (int i = j; i <= K; i++)
            {
                C[i][j] = C[i - 1][j - 1] - Spacing[i - 1] * C[i - 1][j];
                D[i][j] = D[i - 1][j - 1] + Spacing[j] * D[i - 1][j];
            }
        // eij
        for (int j = 0; j <= K; j++)
            E[j][0] = 1.0;

        for (int i = 1; i <= K; i++)
            for (int j = 1; j <= i; j++)
                E[i][j] = E[i - 1][j - 1] + E[i - 1][j];

        //normalization
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

        //direction 
        double DIR = (te - to) / abs(to - te);
        Global::Discr *= DIR;
        double H_ = abs(step);
        vs = err != 0;
        CNV = NI <= 0;
        double t = to;
        double B_ = 0;
        IPS = IPS0;

#pragma endregion

        //метка 3
        M3: double H = H_ * DIR;
            double R = 1.0;
            ls = false;
            for (int k = 0; k < N; k++)
            {
                XK[k] = 0.0;
                for (int i = 0; i < K; i++)
                    B[i][k] = 0.0;
            }


            //Ќачальное значение шага
#pragma region Ќачальное значение шага
            if (H_ == 0)
            {
                if (!vs) throw invalid_argument("Zero Constant Step!");
                ///////////////////////////////////////
                force(to, X, F0);
                H_ = EPS;
                B_ = 0.0;
                while (B_ == 0)
                {
                    H_ = H_ * 10.0;
                    H = H_ * DIR;
                    for (int j = 0; j < N; j++)
                        Y[j] = X[j] + H * F0[j];
                    if (abs(te - to) <= H_)
                        goto M1;
                    ///////////////////////////////
                    force(to + H, Y, F);

                    for (int j = 0; j < N; j++)
                    {
                        double d = (F[j] - F0[j]);
                        B_ = B_ + d * d;
                    }
                }
                H_ = sqrt(2.0*err*H_ / sqrt(B_));
                H = H_ * DIR;
            }
#pragma endregion
#if IS_DEBUG
            fprintf(fodbg, "%f %f \n", err, vs);
#endif
            //if (Init(H_, dir, R, to, X, Y, B_))return 1;


            //Start of integration
#pragma region Start of integration
            M1 :
               if (abs(te - t) <= H_)
               {
                   step = H_;
                   H = te - t;
                   H_ = abs(H);
                   R = R * H_ / step;
                   ls = true;
               }
               if (NS <= 1)
               {
                   for (int i = 0; i < K; i++)
                       for (int j = 0; j < N; j++)
                           BL[i][j] = B[i][j];
               }
#pragma endregion

#if IS_IOUT
               fprintf(foInteg, "%19.12e\t%12.8f\t%d\n", t, H, it);
#endif // DEBUG



#pragma region A+dA
               //не трогай!
               double q = 1.0;
               for (int l = 0; l < K; l++)
               {
                   for (int i = 0; i < N; i++)
                       P[i] = 0.0;

                   for (int m = l; m < K; m++)
                       for (int i = 0; i < N; i++)
                           P[i] = P[i] + E[m + 1][l + 1] * B[m][i];
                   q = q * R;
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

#pragma region Corrector
               //<Iterations on step>
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
                       s = Spacing[i + 1];
                       for (k = 0; k < N; k++)
                           P[k] = 0.0;
                       for (j = K - 1; j >= 0; j--)
                           for (k = 0; k < N; k++)
                               P[k] = s * (B[j][k] + P[k]);

                       for (k = 0; k < N; k++)
                           Y[k] = X[k] + H * s*(F0[k] + P[k]);

                       ////////////////////////////////////////
                       //#pragma omp atomic
                       t_ = t + H * s;
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

                   //<Convergence check and exit>
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
               //если не сошлись итерации
               if ((it > IPS0) && (!CNV) && (NS != 0)) NBS++;
#pragma endregion

#pragma region ѕроверка величины шага
               if (vs)
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
                       INC = (!ls) && INC;
                       if (INC && (R > RMX) || (R < RMN))
                       {
                           NST++;
                           if ((NST > 100) && (R > RMX)) goto M4;
                           H_ = H_ * R; goto M3;
                           //if (Init(H_, dir, R, to, X, Y, B_))return 1;
                       }
                   }
                   //metka4
               M4:	if (R > RMX) R = RMX;
               }
#pragma endregion

               if (Inter(t, H, X, Yo)) ls = true;

               // Solution on step
               endOfStep(t, H, X, Yo);

               t = t + H;
               H = H * R;
               step = H_ = abs(H);
               NS++;

               if (CNV)
                   IPS = IPS0;
               else
                   IPS = NI;

               if (ls)
               {
                   te = t;
#if IS_IOUT
                   fclose(foInteg);
#endif
#if IS_DEBUG
                   fclose(fodbg);
#endif

                   return 0;
               }
               goto M1;
    };

    int ivar::Init(double &H_, double &dir, double &R, double &to, vector<double> X, vector<double> Y, double &B_)
    {
        H = H_ * dir;
        R = 1.0;
        ls = false;
        for (int k = 0; k < N; k++)
        {
            XK[k] = 0.0;
            for (int i = 0; i < K; i++)
                B[i][k] = 0.0;
        }

#pragma endregion
#if IS_DEBUG
        fprintf(fodbg, "2");
#endif
        //initial value of step
#pragma region Initial value of step
        if (H_ == 0)
        {
            if (!vs) return 1;
#if IS_DEBUG
            fprintf(fodbg, "3");
#endif
            ///////////////////////////////////////
            force(to, X, F0);
#if IS_DEBUG
            fprintf(fodbg, "4");
#endif
            H_ = EPS;
            B_ = 0.0;
            while (B_ == 0)
            {
                H_ = H_ * 10.0;
                H = H_ * dir;
                for (int j = 0; j < N; j++)
                    Y[j] = X[j] + H * F0[j];
                if (abs(te - to) <= H_)
                    return 0;
                ///////////////////////////////
                force(to + H, Y, F);

                for (int j = 0; j < N; j++)
                {
                    double d = (F[j] - F0[j]);
                    B_ = B_ + d * d;
                }
            }
            H_ = sqrt(2.0*err*H_ / sqrt(B_));
            H = H_ * dir;
        }
#if IS_DEBUG
        fprintf(fodbg, "5");
#endif
        return 0;
    }
}