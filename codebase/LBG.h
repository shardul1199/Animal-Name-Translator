#include<stdio.h>
//#include<limits.h>

#define p 12  //no. of columns of codebook
#define delta 0.0001
#define epsilon 0.03
#define M 32

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