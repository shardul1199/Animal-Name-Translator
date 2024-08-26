
//#include "stdafx.h"
#include <stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
//#include<conio.h>
//#include<stdio.h>

/*#include "LBG.h"
#include "HMM.h"
#include "universe.h"*/
//#include "testing.h"

//#include<limits.h>


//#include<conio.h>
//#include<string.h>

#define M 32
#define N 5
#define T 160
#define p 12  //no. of columns of codebook
#define delta 0.0001
#define epsilon 0.03
#define fsize 320
#define pie 3.14159265
#define frame_size 80

long double tokhura_distance(long double test[], long double code_book[]) // finds the tokhura distance between given reference data and given test data
{
	long double dist=0;
	 long double w[]={1.0, 3.0, 7.0, 13.0, 19.0, 22.0, 25.0, 33.0, 42.0, 50.0, 56.0, 61.0}; //w[] array will contain tokhura weights of the 12 cepstral coefficients
    int j;

	for(j=0;j<p;j++)
	 {
		dist+=w[j]*(test[j]-code_book[j])*(test[j]-code_book[j]); // applying tokhura distance formula
	 }

	 return dist; // returning tokhura distance between given reference data and test data
}


long double absolute(long double x) //returns the absolute of the long double variable
{
    return x>=0?x:-x;
}


void K_Means(FILE* fp,long double codebook[][p],int k,int lines)  // applying k means on the given codebook, here k is no. of codebook rows and M is no of universe file vectors
{
   // printf("\n\nk:%d \n",k);
   int m=0,i,j=0;
   long double x;

   long double distortion=0,prev_distortion=0;
   m=0;

  do
  { 
    m++; // m is this while loop counter
    prev_distortion=distortion;
     distortion=0;

    int cluster_size[M]; // contains the size of each clusters in the universe and there will be 8 total clusters
    long double dummy_codebook[M][p];  //this matrix will initially contain the centroid of each clusters
    for(i=0;i<k;i++)
    {
        cluster_size[i]=0; //initializing the cluster size
     for(j=0;j<p;j++)
       dummy_codebook[i][j]=0; 
    }
 
   fseek(fp,0,SEEK_SET); // setting the file pointer to file's start position
    for(i=0;i<lines;i++)
    {
            int itr1,index,itr2;

            long double universe_row[p]; // this array will collect the vectors from universe file one by one
           
           for(itr2=0;itr2<p;itr2++)
         {
           fscanf(fp,"%Lf",&x); //reading the values from universe file
          
           if(itr2!=p-1)
             fgetc(fp);   //ignoring the ','
             universe_row[itr2]=x; 
         }
           
        
            long double min_dist=2147483647;
            for(itr1=0;itr1<k;itr1++)
            {
               long double dist=tokhura_distance(universe_row,codebook[itr1]);  //calculating the tokhura distance between the given codebook vector and the given universe file row
               if(min_dist>dist)
                 {
                   min_dist=dist;
                   index=itr1;  // index will contain the index (in the codebook) of centroid of the cluster of the current universe row
                 }
            }
            cluster_size[index]++;
           distortion+=min_dist; // fisrt summing sum all the distortions of the universe rows from the centroid
           
        for(itr2=0;itr2<p;itr2++)
          {
            dummy_codebook[index][itr2]+=universe_row[itr2]; //summing up all the universe file rows belonging to the same clusters
          }
    }

     for(i=0;i<k;i++)
     {
      for(j=0;j<p;j++)
       {
         codebook[i][j]=dummy_codebook[i][j]/cluster_size[i]; //storing the centroid values in the codebook matrix
        }
     }
    distortion/=lines;  //calculating the current average distortion 

  }while(m==1 || absolute(distortion-prev_distortion)>delta);
}


void LBG(FILE* fp, long double codebook[][p])   // applying the LBG algo on given universe file
{
    long double x, sum[p]={0};
     int count=0,lines=0,i,j;

   fseek(fp,0,SEEK_SET);
   while(fscanf(fp,"%Lf",&x)==1) //reading the values from the universe file
   {
     sum[count]+=x;  //summing up all the elements belonging to same column in the universe file
     count++;
     if(count==12)
     {
        lines++;
        count=0;
     }

	 else
       fgetc(fp);
   }

   long double avg[p];
   for(i=0;i<p;i++)
   {
     avg[i]=sum[i]/lines;
     codebook[0][i]=avg[i]; //initializing the codebook matrix with one element
   }

   long double copy[32][p];
   int k=1;
   do  //splitting of the codebook happens here
   {
      for(i=0;i<k;i++)
      {
        for(j=0;j<p;j++)
        {
            copy[i][j]=codebook[i][j];
        }
      }

      for(i=0;i<k;i++)
      {
        for(j=0;j<p;j++)
        {
            codebook[2*i][j]=copy[i][j]*(1-epsilon);
            codebook[2*i+1][j]=copy[i][j]*(1+epsilon);
        }
      }
      k=k*2;

      fseek(fp,0,SEEK_SET);
      K_Means(fp,codebook,k,lines);  //appying the k means algo on given codebook

	  printf("codebook size: %d\n",k);
	  for(i=0;i<k;i++)
		{
			for(j=0;j<p;j++)
				printf("%Lf ",codebook[i][j]);
			printf("\n");
	    }
	  printf("\n\n");

   }while(k<32); //k contain current codebook size
}


void CodeBook(char* foldername)
{
	char file[100];
	sprintf(file,"%s/universe.csv",foldername);

	FILE* fp=fopen(file,"r");
	if(fp==NULL)
	 {
		 printf("sorry\n%s",file);
		 return;
	 }

	long double codebook[M][p];
	 printf("\nLBG starting:\n");
	LBG(fp,codebook);

	int i,j;
	sprintf(file,"%s/codebook.csv",foldername);
	FILE* fpw=fopen(file,"w");
   for(i=0;i<M;i++) // storing the yield codebook in codebook.csv file
   {
    for(j=0;j<p;j++)
     {
        if(j!=p-1)
          fprintf(fpw,"%0.32e,",codebook[i][j]);
          else
             fprintf(fpw,"%0.32e\n",codebook[i][j]); 
     }
   }
     fclose(fpw);
}







































//===========================================================================




/*void DC_shift(long double*, long double);
void normalize(long double* , int);
 void hamming_window(long double[]);
void auto_correlation( long double*,long double[]);
void durbin_algo(long double[], long double[]);
void cepstral_coeff(long double[], long double[]);
void raised_sine_window(long double[]);
int absolute(int);
void build_universe(FILE*,FILE*);
 void universe(FILE*);*/


  int absolute(int data)
  {
     return data>=0?data:-data;
  }

 long double ste(int* arr, long long i)  //calculating short term energy on the given frame using the formula E=1/N*sum(s[i]) i=0..N-1
 {
       long long int j=i;
       long double E=0;
       
	   for(j=i;j<i+frame_size;j++)
	   {
	   	   E+=arr[j]*arr[j];
	   }	
		   
		   E=E*1.0/frame_size;
		  // printf("\nE:%Lf  sum:%Lf\n\n",E,sum);

		   return E;
 }


 long double threshold_ste()
 {
	 /*long long i;
	 long double threshold=0;
	 for(i=file_size-2*frame_size;i>=file_size-5*frame_size;i-=frame_size)
		  threshold+=ste(sample,i);

	 threshold/=4;
	// printf("threshold:%Lf \n",threshold);
	 return 13*threshold;*/

	 /*FILE* fp=fopen("testdata/noise.txt","r");
	 int x, arr[4000];

	 long long counter=0;
	 while(fscanf(fp,"%d",&x)==1 && counter<4000)
		  arr[counter++]=x;
	 fclose(fp);

	 long long i;
	 long double threshold=0;
	 for(i=0;i<counter-frame_size;i+=frame_size)
		 {
			 long double energy=ste(arr,i);
			 if(threshold<energy)
				 threshold=energy;
	     }

	  fp=fopen("testdata/threshold.txt","w");
	  fprintf(fp,"%Lf",threshold);
	  fclose(fp);*/

	 long double threshold;
	   FILE* fp=fopen("testdata/threshold.txt","r");
	  fscanf(fp,"%Lf",&threshold);
	  fclose(fp);

	   return threshold*1.5;
 }

  int start_end(char* str, char* str2)
 {
	 long long itr1;
	 long double DCShift=0;
   long long file_size=0,bar=0;   //modified
	 int x;

	  FILE* fp=fopen(str,"r");
	  if(fp==NULL)
		  return 0;

	 while(fscanf(fp,"%d",&x)==1)
	 {
		 file_size++;
		 if(file_size<=150)
             DCShift+=x;
	 }
	 fclose(fp);

	 file_size-=bar;
	 DCShift/=150;

	 int* sample=(int*)malloc(file_size*sizeof(int));
	 fp=fopen(str,"r");

	 long double max_sample=0;
	 long long max_sample_index=0;
	 for(itr1=0;itr1<file_size+bar;itr1++)
		 {
			 fscanf(fp,"%d",&x);

		  if(itr1>=bar)
		  {
			  long long itr2=itr1-bar;
			  sample[itr2]=x;
			  //printf("%Lf: %ld \n",sample[itr2],itr2);

			 if(max_sample<absolute(sample[itr2]))
		    {
			 max_sample=absolute(sample[itr2]);
			 max_sample_index=itr2;
		    }
		  }
	    }
	  fclose(fp);


	 long double threshold=threshold_ste();
     //printf("threshold:%Lf \n",threshold);

	 long long start=0,end=0;
	 for(itr1=0;itr1<=file_size-15*frame_size;itr1+=frame_size)
	 {
		 int i,check=0;
		 for(i=0;i<15;i++)
			{
				if(ste(sample,itr1+i*frame_size)<=threshold)
                 {
					 check=1;
					 break;
				  }
		     }

		       if(check==0)
			   {
				 start=itr1;
				 break;
			   }
	 }

	    
	for(itr1=file_size-frame_size;itr1>=15*frame_size;itr1-=frame_size)
	{
		 int i,check=0;
		 for(i=0;i<15;i++)
			{
				if(ste(sample,itr1-i*frame_size)<=threshold)
                 {
					 check=1;
					 break;
				  }
		     }

		       if(check==0)
			   {
				 end=itr1;
				 break;
			   }
	}

	   
		// end=start+90*frame_size;
	     /*end+=5*frame_size;
		 start-=2*frame_size;*/

		 if(end>start+160*frame_size)
			  end=start+70*frame_size;


		 /*printf("%s\nstart:%ld\n",str,start);
		 printf("end:%ld \n",end);
		 printf("file_size:%ld\n\n",file_size);*/

		 if((end-start)<20*frame_size)
		   {
			   printf("can't crop this file\n");
			   return 0;
	       }

		 FILE* fpw=fopen(str2,"w");
		 for(itr1=start;itr1<=end;itr1++)
		 {
			 fprintf(fpw,"%d\n",sample[itr1]);
		 }

	     /*for(itr1=0;itr1<file_size;itr1++)
		 {
			 if(itr1>=start && itr1<=end)
				 fprintf(fpw,"%d\n",sample[itr1]);

			 else
				 fprintf(fpw,"0\n");
		 }
		 fclose(fpw);*/

		 return 1;
 }




void DC_shift(long double *arr, long double DC_SHIFT)  // does dc shift on the amplitudes
  {
     int i=0;
  	 //printf("%lf ",avg);
  	 
  	 for(i=0;i<fsize;i++)
  	  arr[i]-=DC_SHIFT;
  }

 void normalize(long double *arr, int max)// normalize the speech amlitude under +5000 to -5000
 {
 	int i=0;
 	for(i=0;i<fsize;i++)
 		arr[i]=(5000*arr[i])/max; // max contains the maximum absolute value of the sample data
 }


 void hamming_window(long double frame[]) //applying hamming window on the steady frame data
  {
	  long double w[fsize];

  	 int i;
  	 for(i=0;i<fsize;i++)
  	  w[i]=0.54-0.46*cos(2*pie*i*1.0/(fsize-1)); //w[] array will contain the hamming window data

  	  for(i=0;i<fsize;i++)
  	  	 frame[i]=frame[i]*w[i]; //applying hamming window

	/*  FILE* fp=fopen("word/hamming_window.txt","w"); //storing the hamming window data in a file
	  for(i=0;i<fsize;i++)
        fprintf(fp,"%0.32e\n",w[i]);
	  fclose(fp);*/
  }

void auto_correlation( long double* arr,long double R[p+1]) // calculating 12 r[] values from of the given frame
  {
     int m,i;
	 for(i=0;i<=p;i++)
	 {
		R[i]=0;
        for(m=0;m<=fsize-1-i;m++)
			R[i]+=arr[m]*arr[m+i]; 
	 }
  }

void durbin_algo(long double R[p+1], long double a[p+1]) // applies durbin's algo on the r[] values and find the LPC coefficients a[12]
{
	long double E[p+1];
	long double alpha[p+1][p+1];
	long double k[p+1];

	E[0]=R[0];
	int i=0,j=0;

	for(i=1;i<=p;i++)
	{
		k[i]=R[i];
		for(j=1;j<=i-1;j++)
		{
			k[i]-=alpha[i-1][j]*R[i-j];
		}

		k[i]/=E[i-1];
		alpha[i][i]=k[i];
		for(j=1;j<=i-1;j++)
		{
			alpha[i][j]=alpha[i-1][j]-k[i]*alpha[i-1][i-j];
		}

		E[i]=(1-k[i]*k[i])*E[i-1];
	} 

	for(i=1;i<=p;i++)
	{
		a[i]=alpha[p][i];
	}
}


void cepstral_coeff(long double a[p+1], long double c[p+1]) //finds the cepstral coeffs from the LPC coefficients c[12]
{
	int m=0,k=0;
	for(m=1;m<=p;m++)
	{
		c[m]=a[m];
		for(k=1;k<=m-1;k++)
		{
			c[m]+=(k*1.0/m)*c[k]*a[m-k];  //c[i]=a[i]+sum((k/m)*c[k]*a[m-k])  where m=1....p and k=1...m-1
		}
		//printf("%lf ",c[m]);
	}
}

void raised_sine_window(long double c[]) // applies raised sine window on the given cepstral coefficients
{
	int m=0;
	long double w[p+1];
   for(m=1;m<=p;m++)
   {
	 w[m]=1+p/2*sin(pie*m*1.0/p);  //w[] array contains the raised sine window coeffs
	 c[m]*=w[m];
   }


}


void build_universe(FILE* fp, FILE* fpw, FILE* fp3)
{
    int sample_max=0,x,sample_count=0;
	long double DC_SHIFT=0;
    while(fscanf(fp,"%d",&x)==1)
      {
		 if(sample_max<absolute(x))
          sample_max=absolute(x);
      
	    if(sample_count++<100)
		  DC_SHIFT+=x;
	  }
	  DC_SHIFT/=100;


	  int frame_count=(sample_count-fsize)/80+1;
	  frame_count=frame_count<T?frame_count:T;
	  fprintf(fp3,"%d",frame_count);


    fseek(fp,0,SEEK_SET);
    int itr1,itr2,i,j;
    long double frame[fsize];
	long double frame_duplicate[fsize];
  
 for(itr1=1;itr1<=frame_count;itr1++)
 {
    if(itr1==1)
    for(itr2=1;itr2<=fsize;itr2++)
    {
       fscanf(fp,"%d",&x);
       frame_duplicate[itr2-1]=x;
    }

    else 
      {
         for(i=0;i<240;i++)
            frame_duplicate[i]=frame_duplicate[i+80];

           for(i=fsize-80;i<fsize;i++)
           {
             fscanf(fp,"%d",&x);
             frame_duplicate[i]=x;
           }
      }

	  for(i=0;i<fsize;i++)
		  frame[i]=frame_duplicate[i];

      DC_shift(frame,DC_SHIFT);
      normalize(frame,sample_max); 

     long double R[p+1];
     hamming_window(frame);
     auto_correlation(frame,R);

    long double a[p+1];
    durbin_algo(R,a);

    long double c[p+1];
    cepstral_coeff(a,c);
    raised_sine_window(c);
    
    for(i=1;i<=p;i++)
     {
		if(i!=p)
		 fprintf(fpw,"%0.32e,",c[i]);
		else
          fprintf(fpw,"%0.32e\n",c[i]);
	 }
   }

}


 void universe(char* foldername)  //creates universe.csv containing cepstral coefficients file from training data
 {
	 int num_words, num_utterances;
	  char file[100];

	  sprintf(file,"%s/num_words.txt",foldername);
	  FILE* fp=fopen(file,"r");
	  if(fp==NULL)
	 {
		 printf("sorry\n%s",file);
		 return;
	 }
	  fscanf(fp,"%d",&num_words);
	  fclose(fp);

	  sprintf(file,"%s/num_utterances.txt",foldername);
	  fp=fopen(file,"r");
	  if(fp==NULL)
	 {
		 printf("sorry\n%s",file);
		 return;
	 }
	  fscanf(fp,"%d",&num_utterances);
	  fclose(fp);

	   char universe[100];
	  sprintf(universe,"%s/universe.csv",foldername);
	  FILE* fpw=fopen(universe,"w");

	 int itr1,itr2;

	for(itr1=1;itr1<=num_words;itr1++)
	{
		printf("training set %d: \n",itr1);

		for(itr2=1;itr2<=num_utterances;itr2++)
			{
				char str[40];
				sprintf(str,"%s/%d/%d_%d.txt",foldername,itr1,itr1,itr2);
				start_end(str,str);

				fp=fopen(str,"r");
               if(fp==NULL)
			   {
                  printf("%s",str);
				 // getch();
				  return;
			   }


				char str_frames[40];
				sprintf(str_frames,"%s/frames/%d/%d_%d.txt",foldername,itr1,itr1,itr2);
				FILE* fp3=fopen(str_frames,"w");
			      if(fp3==NULL)
	            {
	        	printf("frames\n");
		        //getch();
				return;
	            }

                build_universe(fp,fpw,fp3);
				fclose(fp);
				fclose(fp3);
		    }
	}
 }
//============================================================================
//#include "universe.h"


long double tokhura_distance2(long double test[], long double code_book[]) // finds the tokhura distance between given reference data and given test data
{
	long double dist=0;
	 long double w[]={1.0, 3.0, 7.0, 13.0, 19.0, 22.0, 25.0, 33.0, 42.0, 50.0, 56.0, 61.0}; //w[] array will contain tokhura weights of the 12 cepstral coefficients
    int j;

	for(j=0;j<p;j++)
	 {
		dist+=w[j]*(test[j]-code_book[j])*(test[j]-code_book[j]); // applying tokhura distance formula
	 }

	 return dist; // returning tokhura distance between given reference data and test data
}

void finding_observation_sequence(FILE* fp, long double codebook[][p], char* str, int frame_count)   //find observation sequence  of the training data
 {
	 long double cepstral[p];
	 int i,t,j;

	 FILE* fpw=fopen(str,"w");

	 for(t=0;t<frame_count;t++)
    {
	  for(i=0;i<p;i++)
	  {
		 fscanf(fp,"%Lf",&cepstral[i]);
		 if(i!=p-1)
			 fgetc(fp);
	  }

	  int index;
	  long double min_dist=INT_MAX;
	  for(j=0;j<M;j++)
	  {
		  long double dist=tokhura_distance2(cepstral,codebook[j]);
		  //long double dist=0;
		  if(min_dist>dist)
		  {
			  min_dist=dist;
			  index=j;
		  }
	   }
	  fprintf(fpw,"%d\n",index+1);
    }

	 fclose(fpw);
 }


 void row_read(FILE* fp, long double arr[], int n)  // reading one row from the file 
{
    int i;
    for(i=0;i<n;i++)
     fscanf(fp,"%Lf",&arr[i]);
}

 void row_print(FILE* fpw, long double arr[], int n)  //printing one row in the given file 
{
     int i;
    for(i=0;i<n;i++)
     fprintf(fpw,"%0.32e ",arr[i]);
     fprintf(fpw,"\n");
}

  long double forward_procedure(long double alpha[T][N], long double pi[N], long double a[N][N], long double b[N][M], int o[T], int frame_count) 
  {
    int t,i,j;

    for(i=0;i<=N-1;i++)
      alpha[0][i]=pi[i]*b[i][o[0]-1];

   for(t=0;t<(frame_count-1);t++)
   {
    for(j=0;j<N;j++)
    {
      long double sum=0;
      for(i=0;i<N;i++)
       sum+=alpha[t][i]*a[i][j];
     
      alpha[t+1][j]=sum*b[j][o[t+1]-1];
    }
   }
    
    long double prob_o_lamda=0;
   for(i=0;i<N;i++)
   {
      prob_o_lamda+=alpha[frame_count-1][i];
   }

    return prob_o_lamda;
  }


 void backward_procedure(long double beta[T][N], long double pi[N], long double a[N][N], long double b[N][M], int o[T], int frame_count)
  {
     //initialization of beta matrix
	  int t,i,j;
	  for(i=0;i<N;i++)
		  beta[frame_count-1][i]=1;

	  for(t=frame_count-2;t>=0;t--)
	  {
		  for(i=0;i<N;i++)
		  {
			  beta[t][i]=0;
			  for(j=0;j<N;j++)
				  beta[t][i]+=a[i][j]*b[j][o[t+1]-1]*beta[t+1][j];
		  }
	  }
  }
  
  void calculation_gamma(long double alpha[T][N], long double beta[T][N], long double gamma[T][N], int frame_count)
  {
	  int t,i,j;
	long double prob_o_lamda=0;
	
	for(t=0;t<frame_count;t++)
    {
	   prob_o_lamda=0;
	for(j=0;j<N;j++)
       prob_o_lamda+=alpha[t][j]* beta[t][j];

	 for(i=0;i<N;i++)
		 gamma[t][i]=(alpha[t][i]*beta[t][i])/prob_o_lamda;
    }
  }


  long double viterbi(long double a[N][N],long double b[N][M], long double pi[N],int o[T], int frame_count)
  {
      int psi[T][N];
      int i, j, t;
      long double delt[T][N];

      for(i=0;i<N;i++)
      {
        delt[0][i]=pi[i]*b[i][o[0]-1];
       // psi[0][i]=0;
      }

      for(t=1;t<frame_count;t++)
      {
        for(j=0;j<N;j++)
        {
           int index;
           long double max=0;

           for(i=0;i<N;i++)
           {
             if(max < delt[t-1][i] * a[i][j])
               {
                max=delt[t-1][i] * a[i][j];
                index=i;
               }
           }

           delt[t][j]=max*b[j][o[t]-1];
          // psi[t][j]=index;
        }
      }


        long double p_star=INT_MIN;
       for(i=0;i<N;i++)
       {
          if(p_star < delt[frame_count-1][i])
           {
            p_star= delt[frame_count-1][i];
            // q[T-1]=i;
           }
       }

	 
     /*  for(t=T-2;t>=0;t--)
	   {
		   printf("q[%d]=%d \n",t+1,q[t+1]);
       q[t]=psi[t+1][q[t+1]];
	   }*/

       return p_star;
  }


   void re_estimation(long double pi[N], long double a[N][N], long double b[N][M], int o[T], long double alpha[T][N], long double beta[T][N], long double gamma[T][N], int frame_count)
   {
	   long double zai[T][N][N];
	   int t,i,j,k;

	   long double prob_o_lamda=0;

	   for(t=0;t<frame_count-1;t++)
	   {
		   prob_o_lamda=0;
		   for(i=0;i<N;i++)
		   {
			   for(j=0;j<N;j++)
			   {
				   prob_o_lamda+=alpha[t][i]*a[i][j]*b[j][o[t+1]-1]*beta[t+1][j];
			   }
		   }

		   for(i=0;i<N;i++)
		   {
			   for(j=0;j<N;j++)
			   {
				   zai[t][i][j]=(alpha[t][i]*a[i][j]*b[j][o[t+1]-1]*beta[t+1][j])/prob_o_lamda;
			   }
		   }
	   }


	   /*for(i=0;i<N;i++)
	     pi[i]=gamma[0][i];*/

	   for(i=0;i<N;i++)
	   {
		   for(j=0;j<N;j++)
		   {
			   long double sum_gamma=0,sum_zai=0;
			   for(t=0;t<=frame_count-2;t++)
			   {
				   sum_gamma+=gamma[t][i];
				   sum_zai+=zai[t][i][j];
			   }

			   a[i][j]=sum_zai/sum_gamma;
		   }
	   }

	   for(j=0;j<N;j++)
	   {
		   for(k=0;k<M;k++)
		   {
			   long double sum1=0, sum2=0;
			   for(t=0;t<frame_count;t++)
			   {
				   if(o[t]==k+1)
					   sum1+=gamma[t][j];

				   sum2+=gamma[t][j];
			   }
			   b[j][k]=sum1/sum2;
		   }
	   }

	    for(j=0;j<N;j++)
	   {
		   int max_index=0;
		   long double sum=0;
		   for(k=0;k<M;k++)
		   {
			   if(b[j][max_index]<b[j][k])
                  max_index=j;

			   if(b[j][k]==0)
				   b[j][k]=1e-30;

			   sum+=b[j][k];
		   }

		   b[j][max_index]+=(1-sum);
	  }

	}


  /* long double absolute(long double x)
   {
	   return x>=0?x:-x;
   }*/





 void HMM(char* foldername)
{
	printf("\n\nstrarting HMM:\n");

	int words,utterances;
	char file[100];
	sprintf(file,"%s/num_words.txt",foldername);
	FILE* fpf=fopen(file,"r");
	if(fpf==NULL)
	{
		printf("%s\n",file);
		return;
	}
	fscanf(fpf,"%d",&words);
	fclose(fpf);

	sprintf(file,"%s/num_utterances.txt",foldername);
    fpf=fopen(file,"r");
	if(fpf==NULL)
	{
		printf("%s\n",file);
		return;
	}
	fscanf(fpf,"%d",&utterances);
	fclose(fpf);


	long double pi[N]={1,0,0,0,0};
	long double initial_A[N][N]={{0.8,0.2,0,0,0},{0,0.8,0.2,0,0},{0,0,0.8,0.2,0},{0,0,0,0.8,0.2},{0,0,0,0,1}};
    long double initial_B[N][M];

	int i, j;
	for(i=0;i<N;i++)
		for(j=0;j<M;j++)
			initial_B[i][j]=1/(1.0*M);

    int o[T]; 
    long double alpha[T][N], beta[T][N], gamma[T][N];

	FILE* fpw;
	int itr1,itr2;

	for(itr1=1;itr1<=words;itr1++) 
  {
	  long double converged_A[N][N];
	  long double converged_B[N][M];

		 long double sum_starP=0;
	 int train_itr, train_count=3;

  for(train_itr=1;train_itr<=train_count;train_itr++)
 {
	  	long double sum_A[N][N];
	long double sum_B[N][M];
	  for(i=0;i<N;i++)
		for(j=0;j<N;j++)
			  sum_A[i][j]=0;
	  for(i=0;i<N;i++)
		for(j=0;j<M;j++)
			sum_B[i][j]=0;


    for(itr2=1;itr2<=utterances;itr2++) 
   {
	  printf("iteration-%d %d %d\n",itr1,train_itr,itr2);

	  long double a[N][N],b[N][M];
	  if(train_itr==1)
	  {
		  for(i=0;i<N;i++)
		    for(j=0;j<N;j++)
				a[i][j]=initial_A[i][j];

	    for(i=0;i<N;i++)
		 for(j=0;j<M;j++)
			b[i][j]=initial_B[i][j];
	  }

	  else
	  {
		  for(i=0;i<N;i++)
		    for(j=0;j<N;j++)
			   a[i][j]=converged_A[i][j];

	    for(i=0;i<N;i++)
		  for(j=0;j<M;j++)
			b[i][j]=converged_B[i][j];
	  }

	int frame_count=0;
	char str2[100];
	sprintf(str2,"%s/frames/%d/%d_%d.txt",foldername,itr1,itr1,itr2);
	FILE* fp2=fopen(str2,"r");
	if(fp2==NULL)
	{
		printf("sorry\n%s\n",str2);
		//getch();
		return;
	}
	fscanf(fp2,"%d",&frame_count);
	fclose(fp2);

	char str[100];
	 sprintf(str,"%s/observation/%d/%d_%d.txt",foldername,itr1,itr1,itr2);
	FILE* fp=fopen(str,"r");
	if(fp==NULL)
	{
		printf("sorry\n%s\n",str);
		//getch();
		return;
	}
   for(i=0;i<frame_count;i++)
         fscanf(fp,"%d",&o[i]);
    fclose(fp);


	for(i=0;i<frame_count;i++)
    for(j=0;j<N;j++)
      alpha[i][j]=0;

	long double star_p=0;
	 long double old_p;
   long double prob_o_lamda;
   int count=0;
	do{
		old_p=star_p;

	 prob_o_lamda=forward_procedure(alpha,pi,a,b,o,frame_count);
	backward_procedure(beta,pi, a, b,o,frame_count);

	calculation_gamma(alpha, beta, gamma,frame_count);

	//int psi[T][N];
   //long double delt[T][N];
    star_p=viterbi(a, b, pi, o, frame_count);

    re_estimation(pi,a,b,o,alpha,beta,gamma,frame_count);
    
	count++;
	//printf("count=%d\n",count);
	}while(count<30  && (count==1 || star_p/old_p>1e-6) ); 
	
	sum_starP+=star_p;

	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
		{	
			sum_A[i][j]+=a[i][j];
            //printf("a[%d][%d]:%0.32e\n",i,j,a[i][j]);
		}
	//printf("\n\n");
	for(i=0;i<N;i++)
		for(j=0;j<M;j++)
			{
				sum_B[i][j]+=b[i][j];
				//printf("b[%d][%d]:%0.32e\n",i,j,b[i][j]);	
		     }
  }

   for(i=0;i<N;i++)
		     for(j=0;j<N;j++)
				converged_A[i][j]=sum_A[i][j]/25;
    
	    for(i=0;i<N;i++)
		   for(j=0;j<M;j++)
				converged_B[i][j]=sum_B[i][j]/25;

 } 
    printf("training %d: average p*=%0.32e\n",itr1,sum_starP/(train_count*utterances)); 


	 char output[100];
	  sprintf(output,"%s/output/output_%d_A.txt",foldername,itr1);
	 FILE* fpw=fopen(output,"w");
	 printf("A matrix:\n");
	 for(i=0;i<N;i++)
		{
			for(j=0;j<N;j++)
		   {
			fprintf(fpw,"%0.32e\n",converged_A[i][j]);
			printf("%0.32e ",converged_A[i][j]);
			}
           printf("\n");
	    }
	 fclose(fpw);

	  sprintf(output,"%s/output/output_%d_B.txt",foldername,itr1);
	  fpw=fopen(output,"w");
	 printf("\nB matrix:\n");
	  for(i=0;i<N;i++)
		{
			for(j=0;j<M;j++)
		   {
			fprintf(fpw,"%0.32e\n",converged_B[i][j]);
			printf("%0.32e ",converged_B[i][j]);
			}
           printf("\n");
	    }
	       printf("\n\n\n");
 }

}
//===========================================================================
 void copy_files(char* target, char* source)
 {
			  FILE* fp1=fopen(source,"r");
			   if(fp1==NULL)
	          {
		        printf("sorry\n%s\n",source);
		        return;
	          }

			  FILE* fp2=fopen(target,"w");
			   if(fp2==NULL)
	          {
		       printf("sorry\n%s\n",target);
		       return;
	          }

			  char x;
			  while(!feof(fp1))
			  {
				  x=getc(fp1);
				  putc(x,fp2);
			  }
			  fclose(fp1);
			  fclose(fp2);
 }

  void live_train(char* foldername)
 {
	 char file[100];
	 int x;
	     char copy[100][40];
		 FILE* LM=fopen("live_models/ListOfModels.txt","r"); 
		 fscanf(LM,"%d",&x);
		 x++;
		 sprintf(copy[0],"%d\n",x);

		 int counter=1;
		 while(fscanf(LM,"%s",file)==1)
		 {
			 printf("%s\n",file);
			 sprintf(copy[counter++],"%s\n",file);
		 }
		 sprintf(copy[counter++],"%s\n",foldername);
		 fclose(LM);

		 LM=fopen("live_models/ListOfModels.txt","w"); 
		 int i;
		 for(i=0;i<counter;i++) 
			 fprintf(LM,"%s\n",copy[i]);
		 fclose(LM);



	 char target[100];
	 sprintf(target,"live_models/%s/noise.txt",foldername);
	 copy_files(target,"testdata/noise.txt");
	 sprintf(target,"live_models/%s/threshold.txt",foldername);
	 copy_files(target,"testdata/threshold.txt");


	 char command[100];

	  sprintf(file,"live_models/%s/num_words.txt",foldername);
	 FILE* fp=fopen(file,"r");
	 if(fp==NULL)
	 {
		 printf("sorry\n%s",file);
		 return;
	 }
	 int words;
	 fscanf(fp,"%d",&words);
	 fclose(fp);


	  sprintf(file,"live_models/%s/num_utterances.txt",foldername);
	 fp=fopen(file,"r");
	 if(fp==NULL)
	 {
		 printf("sorry\n%s",file);
		 return;
	 }

	 int utterances;
	 fscanf(fp,"%d",&utterances);
	 fclose(fp);

	 sprintf(command,"mkdir live_models\\%s\\frames",foldername);
	 system(command);

	 sprintf(command,"mkdir live_models\\%s\\observations",foldername);
	 system(command);

	 sprintf(command,"mkdir live_models\\%s\\output",foldername);
	 system(command);


	 //int i;
	 for(i=1;i<=words;i++)
	 {
         sprintf(command,"mkdir live_models\\%s\\frames\\%d",foldername,i);
		 system(command);

		 sprintf(command,"mkdir live_models\\%s\\observations\\%d",foldername,i);
		 system(command);

		 sprintf(command,"mkdir live_models\\%s\\output\\%d",foldername,i);
		 system(command);
	 }

	 

	 char folder[100];
   sprintf(folder,"live_models/%s",foldername);
   //universe(folder);
   CodeBook(folder);




   long double codebook[M][p];
	   int j;
	   sprintf(file,"%s/codebook.csv",folder);
	  fp=fopen(file,"r");
	  if(fp==NULL)
	  {
		  printf("%s\n",file);
		  return;
	  }
	 for(i=0;i<M;i++)
	 {
		 for(j=0;j<p;j++)
		 {
		 fscanf(fp,"%Lf",&codebook[i][j]);
		 if(i!=p-1)
			 fgetc(fp);
		 }
	 }
	 fclose(fp);


	 sprintf(file,"%s/universe.csv",folder);
	 fp=fopen(file,"r");
	  if(fp==NULL)
	  {
		  printf("%s\n",file);
		  return;
	  }
   int itr1,itr2;
    for(itr1=1;itr1<=words;itr1++)
   {
	  for(itr2=1;itr2<=utterances;itr2++)
	 {	
		char str[100];
		int frame_count;
	   sprintf(str,"%s/frames/%d/%d_%d.txt",folder,itr1,itr1,itr2);
	   FILE* fp2=fopen(str,"r");
	   fscanf(fp2,"%d",&frame_count);
	   fclose(fp2);

	     char str2[100];
	      sprintf(str2,"%s/observation/%d/%d_%d.txt",folder,itr1,itr1,itr2);
		   printf("%s %d\n",str2,frame_count);
	  finding_observation_sequence(fp,codebook,str2,frame_count);
	 }
   }


	HMM(folder);


	//test("input/6/test_data_8.txt",folder);
 }

 /* int _tmain(int argc, _TCHAR* argv[])
  {
	  
	  //live_train("mayukh");
	  //getch();
	  return 0;
  }
*/
