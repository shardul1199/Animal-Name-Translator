#include <stdio.h>
#include<math.h>
//#include<conio.h>
//#include<string.h>

#define M 32
#define N 5
#define T 160
#define p 12
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