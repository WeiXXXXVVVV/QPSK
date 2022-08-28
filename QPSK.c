#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

float rand49()
{  /*rand_max=7FFF (32767) */
	static int Num=0;
    double number;
    int    i;
    i=rand();
    number=(double)(i)/((unsigned) (RAND_MAX+1));
    Num++;
    if (Num >=RAND_MAX){
		time_t t;
		t=time(NULL);
//		srand((unsigned)(t%RAND_MAX));
        Num=0;
    }
    return (float)number;
}

double normal()
{
	static int iset=0;
    static double qset;
    double vx,vy,r,temp;
    if (iset==0)//noise=normal*deviate
    {
	    do
        {
		    vx=2.0*rand49()-1.0;
            vy=2.0*rand49()-1.0;
            r =vx*vx+vy*vy;
        }while (r >=1.0 || r==0);
        temp=sqrt(-2.0*log(r)/r);
        qset=vy*temp;
        iset=1;
        return (vx*temp);
    }
    else
    {
   	    iset=0;
        return qset;
    }
}
int main(int argc, char *argv[]) {
	srand(time(NULL));
	int i,j,k,snr_dB;
double x1,x2,y1,y2,err=0.0,tx=0,ber;
	

    


	for(snr_dB=0;snr_dB<13;snr_dB++)
	{
		double snr=pow(10,snr_dB*0.1);
	    double N0=1/snr;
		while(err<=100)
		{
		tx+=2;
		x1=rand()%2;
		x2=rand()%2;
		if(x1==0)
		{
		x1=-1;
		}
		if(x2==0)
		{
		x2=-1;
		}
		y1=x1+sqrt(0.5*N0)*normal();
		y2=x2+sqrt(0.5*N0)*normal();
		if(y1<=0)
		{
		y1=-1;
		}
		if(y1>0)
		{
		y1=1;
		}
		
		if(y2<=0)
		{
		y2=-1;
		}
		if(y2>0)
		{
		y2=1;
		}
		
		if((y1!=x1)||(y2!=x2))
		{
		err++;
		}
		ber=err/tx;
		}
        
	
    
printf("SNR %d  dB  ¿ù»~²v %e  ¶Ç°e%f  bits\n ",snr_dB,ber,tx);
	err=0;
		tx=0;
}
	
	return 0;
}
