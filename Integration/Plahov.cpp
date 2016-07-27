#include "Form1.h"
#include "stdafx.h"
using namespace v_integrator;
int sumP(int N){
	int s=0;
	for(int i=0;i<=N;i++)
	{s=s+i;}
	return(s);
};

void Form1::Plahov(){

//	 clock_t start = clock();
//	const int  NOR = Global::NOR; 
//	double eps=Global::eps; 
//	double t0=Global::t0;
//	double te=Global::te; 
//	double step=Global::step;
//	Force Fs;
//	double SVi[6]; for(int i=0;i<6;i++) SVi[i] = Global::SV[i];
//
//	#pragma region pBar
//
//	double size_pb = abs(te-t0);
//	double step_pb = abs(te-t0)/1000;
//	int val_pb = 0;
//	
//	#pragma endregion
//	
//	triple X(SVi[0],SVi[1],SVi[2]),V(SVi[3],SVi[4],SVi[5]);
//	vector<double> Rado(NOR);
//
//	array<Quadruple,1>^ VAN = gcnew array<Quadruple>(NOR*NOR);
//	array<Quadruple,1>^ Q_rado = gcnew array<Quadruple>(NOR);
//
//	vector<vector<double>> InvVAN(NOR,vector<double>(NOR));
//	vector<vector<double>> Tau(NOR,vector<double>(3)), Diff(NOR,vector<double>(3)),Tau1(NOR,vector<double>(3)),dTau(NOR,vector<double>(3));
//	vector<double> h(NOR);
//	triple F;
//	vector <triple> MX (NOR), MV(NOR), MX1(NOR), MV1 (NOR), MA (NOR), DMA (NOR), MTau (NOR), MX2 (NOR), MV2 (NOR), DCor (NOR);
//	double tout=t0;
//	FILE*fosv=fopen("sv_J2000.out","w");
////	fprintf(fosv,"year month day hms(UTC) TDB(sec) interval(days) X Y Z Vx Vy Vz \n");
//
//	FILE*foel=fopen("elts_J2000.out","w");
////	fprintf(foel,"year month day hms(UTC) TDB(sec) interval(days) A E I NODE W M \n");
//
//	FILE*foSvEcl=fopen("sv_ECLIPJ2000.out","w");
//	FILE*foelEcl=fopen("elts_ECLIPJ2000.out","w");
//
//	FILE*fosvp=fopen("sv_planetIAU.out","w");
////	fprintf(fosvp,"year month day hms(UTC) TDB(sec) interval(days) X Y Z Vx Vy Vz \n");
//
//	FILE*foelp=fopen("elts_planetIAU.out","w");
////	fprintf(foelp,"year month day hms(UTC) TDB(sec) interval(days) A E I NODE W M \n");
//
//	FILE*fosvR=fopen("sv_IAUplanet.out","w");
////	fprintf(fosvR,"year month day hms(UTC) TDB(sec) interval(days) X Y Z Vx Vy Vz \n");
//
//	FILE*foelR=fopen("elts_IAUplanet.out","w");
////	fprintf(foelR,"year month day hms(UTC) TDB(sec) interval(days) A E I NODE W M \n");
//
//	FILE*foBL=fopen("BL.out","w");	
////	fprintf(foBL,"year month day hms(UTC) TDB(sec) interval(days) L B H \n");
//
//	FILE*foNEU=fopen("NEU.out","w");
////	fprintf(foNEU,"year month day hms(UTC) TDB(sec) interval(days) N E U \n");
//
//	FILE*foAZR=fopen("AZR.out","w");
////	fprintf(foAZR,"year month day hms(UTC) TDB(sec) interval(days) Azimut Z R \n");
//	FILE*fovisi=fopen("visibility.out","w");
//
//	FILE*fo3bg=fopen("3body_geodetic.out","w");
//	//Õ¿’Œ∆ƒ≈Õ»≈ ƒŒÀ√Œ“€ ¬Œ—’ŒƒﬂŸ≈√Œ ”«À¿ Õ¿ “0
//
//	double poss[6];
//	double lt1,dlt;
//	triple Zorb;
//	double Zpl[3];
//	double TimeNode = t0;
//	spkacs_c (Global::IDC, t0, "J2000", "NONE",10, poss, &lt1,&dlt);
//
//	triple Xv = triple(poss[0],poss[1],poss[2]);
//	triple Vv = triple(poss[3],poss[4],poss[5]);
//	Xv=Xv/Xv.getAbs();
//	Vv=Vv/Vv.getAbs();
//	Zorb = Xv&Vv/sin(triple::getAngle(Xv,Vv));
//
//	double Z[3] = {Zorb[0],Zorb[1],Zorb[2]};
//
//	trpos(t0,1,Global::IDC,Z,Zpl);
//	triple ZorbP = triple(Zpl);
//	triple PolP = triple(0.0,0.0,1.0);
//
//	triple Node = ZorbP&PolP;
//	Node = Node/Node.getAbs();
//
//	double NodeA = atan2(Node[1],Node[0]);
//	if(NodeA<0.0) NodeA = NodeA+2*pi;
//
//	// œÀ¿Õ≈“Œ÷≈Õ“–»◊≈— ¿ﬂ √–¿¬»“¿÷»ŒÕÕ¿ﬂ œŒ—“ŒﬂÕÕ¿ﬂ
//	double mu = Global::mu;
//
//	int ii=1;
//	int jj=0;
//
//	String^ fileName = "Radau.txt";
//	IO::StreamReader^ din = IO::File::OpenText(fileName);
//	String^ str;
//	while ((str = din->ReadLine()) != nullptr) 
//	{
//		if(ii>sumP(NOR-1) && ii<=sumP(NOR)) 
//		{   
//			Q_rado[jj] = Quadruple::FromString(str);
//			Rado[jj] = Convert::ToDouble(str);
//			jj++;
//		}
//		ii++;
//	}
//
//	for(int i=0; i<NOR; i++) h[i]=Rado[i]*step;
//	
//	for (int i=0; i<NOR; i++) 
//	{     
//		
//		for (int j=0; j<NOR; j++)
//		{
//			Quadruple st = Quadruple::FromString(Convert::ToString(j+1));
//			VAN[NOR*i+j] = Quadruple::Pow(Q_rado[i],st);
//		}
//
//	}
//	
//	cli::array<Quadruple, 1>^ BB = gcnew cli::array<Quadruple, 1>(NOR*NOR);
//
//	for(int i=0; i<NOR*NOR; i++)  BB[i]= VAN[i];
//	
//	BB = Minvers(BB, NOR);
//
//	for(int i=0; i<NOR; i++) for (int j=0; j<NOR; j++) InvVAN[i][j]=System::Convert::ToDouble(BB[NOR*i+j].ToString());
//	//ËÌÚÂ„ËÓ‚‡ÌËÂ Ì‡Á‡‰
//	if(te<t0) {step=-step; Global::Discr = -Global::Discr;}
//
//while(abs(te-t0)!=0e0)
//	{
//
//		if(abs(te-t0)<1e-12) break;
//		if(step>0)
//		{
//			if(t0+step>te) step=te-t0;
//		}
//		else
//		{
//			if(t0+step<te) step=te-t0;
//		}
//		F= Fs.force( t0, X,V);
//
//		for(int i=0; i<NOR; i++)
//		{
//			MX1[i]= MX[i] =X+V *h[i]+F*h[i]*h[i]/2.0;
//			MV1[i]= MV[i] =V+F*h[i];
//			MA[i] =Fs.force(t0+h[i],MX[i],MV1[i]);
//			DMA[i]= MA[i]-F;
//			for(int j=0; j<3; j++) Tau1[i][j] = 0.0;
//		}
//
//		int ijk = 0;
//		for(;;)
//		{
//			ijk++;
//			
//			#pragma region Mtau = InvVAN*DMA
//			
//			for(int i=0; i<NOR; i++)
//			{
//				for(int j=0; j<3; j++)
//				{
//					double S = .0;
//					for(int k=0; k<NOR; k++)S += InvVAN[i][k]*DMA[k][j];
//					Tau[i][j] = S;
//				}
//			}
//
//			#pragma endregion Mtau = InvVAN*DMA
//
//			for(int j=0; j<NOR; j++)
//			{
//				double S1[3]={.0,.0,.0};
//				double S2[3]={.0,.0,.0};
//
//				for(int k=0;k<3;k++)
//				{
//					for(int i=0; i<NOR; i++)
//					{
//						S1[k] += Tau[i][k]* pow(Rado[j],i+1)/(i+2);
//						S2[k] += Tau[i][k]* pow(Rado[j],i+1)/((i+2)*(i+3));
//						dTau[i][k]= Tau[i][k]-Tau1[i][k];
//					}
//				}
//				triple Sum1(S1);
//				triple Sum2(S2);
//			
//				MX2[j]= MX[j]+(Sum2*h[j]*h[j]);
//				MV2[j]= MV[j]+Sum1*h[j];
//				
//			}
//			double min=1000.0;
//			for(int j=0; j<NOR; j++)
//			{
//				double m = sqrt(dTau[j][0]*dTau[j][0]+dTau[j][1]*dTau[j][1]+dTau[j][2]*dTau[j][2]);
//				if(m<min) min=m;
//			}
//			
//			if (min<eps) break;
//			if(ijk>15)	break;
//			for(int j=0; j<NOR; j++) 
//			{
//				for(int i=0; i<3; i++) Tau1[j][i] =Tau[j][i];
//				MA[j] =Fs.force(t0+h[j],MX2[j],MV2[j]);
//				
//				DMA[j]= MA[j]-F;
//			}
//
//		}
//
//		double So1[3]={.0,.0,.0};
//		double So2[3]={.0,.0,.0};
//
//		for(int k=0;k<3;k++)
//		{
//			for(int i=0; i<NOR; i++)
//			{
//				So1[k] += Tau[i][k]/(i+2);
//				So2[k] += Tau[i][k]/((i+2)*(i+3));
//			}
//		}
//
//		triple Sum1(So1);
//		triple Sum2(So2);
//		if(Global::Discr!=0)
//		{				
//			while(abs(tout-t0)<abs(step))
//			{
//				double hout=tout-t0;
//				triple Xout= X+(V+(F/2.0+Sum2)*hout)*hout;
//				triple Vout= V+(F+Sum1)*hout;
//
//				write(fosv,foel,foSvEcl,foelEcl, fosvR,foelR,fosvp,foelp,foBL,foNEU,foAZR,fovisi,fo3bg,mu,tout,X,V, TimeNode, NodeA );
//				tout+=Global::Discr;
//			}
//		}
//
//		X = X+(V+(F/2.0+Sum2)*step)*step;
//		V = V+(F+Sum1)*step;
//
//		val_pb = int(((size_pb-abs(te-t0))/size_pb)*1000.0+1);
//		toolStripProgressBar1->Value = val_pb;
//
//		t0+=step;
//	
//	}
//	write(fosv,foel,foSvEcl,foelEcl, fosvR,foelR,fosvp,foelp,foBL,foNEU,foAZR,fovisi,fo3bg, mu,tout,X,V, TimeNode, NodeA );
//
//	fclose(fosv);
//	fclose(foel);
//
//	fclose(foSvEcl);
//	fclose(foelEcl);
//
//	fclose(fosvR);	
//	fclose(foelR);
//
//	fclose(fosvp);
//	fclose(foelp);
//
//	fclose(foBL);
//
//	fclose(foNEU);
//	fclose(foAZR);
//
//	fclose(fovisi);
//
//	fclose(fo3bg);
//
//	 long int Npr = Global::N_rp;
//	 dataGridView1->Rows[0]->Cells[0]->Value ="◊ËÒÎÓ Ó·‡˘ÂÌËÈ Í Ô‡‚˚Ï ˜‡ÒÚˇÏ";
//	 dataGridView1->Rows[0]->Cells[1]->Value =Convert::ToString(Npr);
//
//	 clock_t end_time = clock();
//	 double d_end_time;
//	 d_end_time = double(end_time - start) / 1000.0;
//	 toolStripStatusLabel5->Text = "sec";
//	 if (d_end_time > 99999)
//	 {
//		 d_end_time = d_end_time / 60;
//		 toolStripStatusLabel5->Text = "min";
//		 if (d_end_time > 99999)
//		 {
//			 d_end_time = d_end_time / 60;
//			 toolStripStatusLabel5->Text = "h  ";
//		 }
//	 }
//
//	 toolStripStatusLabel1->ForeColor = Color::Green;
//	 toolStripStatusLabel1->Text = "Finished";
//	 toolStripStatusLabel2->Text = d_end_time.ToString("00000");
//	 MessageBox::Show("¬Ò∏ ÌÓÏ!!!", "Information", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
};