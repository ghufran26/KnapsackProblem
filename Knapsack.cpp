/*                                           
                                               BS Semester Project
                                              KnapSack Problem using
                                            Branch and Bound Algorithm
   
   Purpose                           :   Pick Miximum Gain with Fixed capacity Knapsack
                                           
   Formula to Calculate UpperBound   :   ub = v[i] +( W - w)*(v[i+1]/w[i+1])
   
   Author: Ghufran Khan

*/
#include<iostream>
#include<conio.h>
#include <stdlib.h>
using namespace::std;
/*
     The Purpose of This Function is to Find which Live Node has Maximum UpperBound of
*/
int Max(float Knapsack[][5],int end_index)
{
    int   i=-1;
    int   k=0;
    int   ind;
    float max;
    do
    {
       max = Knapsack[++i][k+2];             
      ind = i;   
    }while(Knapsack[i][k+3]!=1);
    int indexA=ind;
    for(int j=ind+1;j<=end_index;j++)
    {
       if(Knapsack[j][k+3]==1)
       {
          if(max<=Knapsack[j][k+2])
          {
             max    = Knapsack[j][k+2];
             indexA = j;                       
          }
       }        
    }
    return  indexA;   
}
/*  This is Main Function */
main()
{
   float Weight[20],Value[20];
   float Divid[20],Knapsack[30][5];
   for(int h=0;h<20;h++)
   {
      Divid[h]=0;  //Array is use for franctional result of v/w
   }
   Weight[0]=0;
   Value[0]=0;
   int item;
   Divid[0]=0.00;
   /* user input */ 
   cout<<"Enter the Total Number of item : ";
   cin>>item;
   float W;
   cout<<" Enter the Max Weight ";
   cin>>W;
   for(int i=1;i<=item;i++)
   {
       cout<<"Enter  the Weight : ";
       cin>>Weight[i];  
       cout<<"Enter  the Value : ";
       cin>>Value[i]; 
       Divid[i] =  Value[i] / Weight[i];   
   }
   
   
   /* user input End */
  
  
   /*      Do Array in Descending order according to Benifit  */   
   for(int i=1;i<=item;i++)
   {
           for(int j=1;j<=item;j++)
           {
              if(Value[i]>Value[j])
              {
                 float temp1    = Value[i]; 
                 float temp2    = Weight[i]; 
                 float temp3    = Divid[i]; 
                 Value[i]     = Value[j];  
                 Weight[i]    = Weight[j];  
                 Divid[i] = Divid[j];
                 Value[j]     = temp1;
                 Weight[j]    = temp2;
                 Divid[j] = temp3;    
              }        
           }        
   }
   for(int i=1;i<=item;i++)
   {
       cout<<" item No : "<<i<<endl;
       cout<<endl;
       cout<<"               Weight            : "<<Weight[i]<<endl;  
       cout<<endl;
       cout<<"               Value             : "<<Value[i]<<endl;
       cout<<endl;
       cout<<"               Fractional Result : "<<Divid[i]<<endl;  
       cout<<endl;
       cout<<endl;
   } 
   /*     do Successively table in Descending order according to Benifit  */
                            
                            
                            /*            ....                  */
                            /*             ..                  */
                            /*     State Space Tree Start     */
                            /*            ....               */
                            /*             ..               */
   
   int rowk=0,colnk=0;
   Knapsack[rowk][colnk]=0;   /* First Node Value  */
   Knapsack[rowk][colnk+1]=0; /* First Node Weight */
   Knapsack[rowk][colnk+2]= Value[0]+(W-Weight[0])*(Divid[1]); /* First Node Upper Bound */
   Knapsack[rowk][colnk+3]=1; /* First Node represent as a Live Node */
   Knapsack[rowk][colnk+4]=0; /*     Put  Level of First Node           */
   int index;
   while(Divid[(int)(Knapsack[Max(Knapsack,rowk)][colnk+4]+1)]!=0)
   {
        index=Max(Knapsack,rowk); /* Find which Live Node has Maximum UpperBound  */
        
        
       /*  
          Current Node that has Maximum Upper Bound
          After Exploring his Child this Node has represent as a Dead Node
      */
      Knapsack[index][colnk+3]=0; 
      
      Knapsack[++rowk][colnk] = Knapsack[index][colnk]; /* Current Node Exclode child Value  */
      Knapsack[rowk][colnk+1] = Knapsack[index][colnk+1]; /* Current Node Exclode  child Weight  */
      float a=Knapsack[index][colnk+4]+2.00; 
      int g=(int)a;
      float b=Knapsack[index][colnk+1];
      float c; 
      c=Divid[g];
      float d =(W-b)*c; 
      Knapsack[rowk][colnk+2] = Knapsack[index][colnk]+d; /* Current Node Exclode  child UpperBound  */
      
      Knapsack[rowk][colnk+3] =  1.00; /* Current Node Exclode child represent as a Live Node  */
      Knapsack[rowk][colnk+4] =  Knapsack[index][colnk+4]+1; /* Current Node Exclode child Level  */
      if((Knapsack[index][colnk+1]+Weight[(int)Knapsack[index][colnk+4]+1])<=W)
      {
         float a=Knapsack[index][colnk+4]+1.00;
         int g=(int)a;                                                                      
         Knapsack[++rowk][colnk] = Knapsack[index][colnk]+Value[g]; /* Current Node Include child Value  */
         float b=Knapsack[index][colnk+4]+1.00;
         int c=(int)b;
         Knapsack[rowk][colnk+1] = Knapsack[index][colnk+1]+Weight[c];/* Current Node Include child Weight  */
         float d=Knapsack[index][colnk+4]+2.00;
         int e=(int)d;
         Knapsack[rowk][colnk+2] = (Knapsack[rowk][colnk])+(W-Knapsack[rowk][colnk+1])*(Divid[e]); /* Current Node  Include child UpperBound  */
         Knapsack[rowk][colnk+3] =  1;                              /* Current Node Include child  represent as a Live Node  */
         Knapsack[rowk][colnk+4] =  Knapsack[index][colnk+4]+1;     /* Current Node Include child Level  */                                                               
      }                   
   }
                             /*                    ....                                      */
                            /*                      ..                                       */
                            /*     State Space Tree End AND Find Maximum Benifit             */
                            /*                     ....                                      */
                            /*                      ..                                       */
   
   cout<<endl;
    cout<<endl;
   int pick_item[10],count=0;
    int in=Max(Knapsack,rowk);
                                        /* Show Maximum Benifit*/
       cout<<endl;
       cout<<endl;
       cout<<endl;
       cout<<endl;
       cout<<endl;
       cout<<"                Maximum Capacity             : "<<  W                     <<endl;
       cout<<endl;
       cout<<"                Maximum Bnenifit             : "<<  Knapsack[in][colnk]   <<endl;
       cout<<endl;
       cout<<"                 Weight                      : "<<  Knapsack[in][colnk+1] <<endl;
       cout<<endl;
       cout<<"                Maximum Upper Bound          : "<<  Knapsack[in][colnk+2] <<endl;
       cout<<endl;
       cout<<endl;
       cout<<endl;
                                      
    /*                         Procedure to Find Optimal Solution Which items Carry to achive Maximum Benifit                                */
    int Cur_index=in;   
    int g=(int)Knapsack[Cur_index][colnk+4];
    g--;
    int indexA,indexB;
    int picitem=0;
    
    while(g>=0)
    {
       int indexA=Cur_index;
       
       while(Knapsack[Cur_index][colnk+4]!=g)
       {
          Cur_index--;                            
       }
       while(Knapsack[indexA][colnk+1]!=Knapsack[Cur_index][colnk+1] && Weight[g+1]+Knapsack[Cur_index][colnk+1]!=Knapsack[indexA][colnk+1])
       {
              Cur_index--;         
       }
       if(Knapsack[Cur_index][colnk+1]!=Knapsack[indexA][colnk+1])
       {
          item=(int)Knapsack[indexA][colnk+4];
          pick_item[count++]=item;  
          g--;                                            
       }
       else
       {
            g--;  
       }
    } 
    /*                              End Optimal Solution Procedure                 */
    cout<<endl;
    cout<<endl;
    /*  Print item that pick to achive Maximum Benifit  */
    for(int i=count-1;i>=0;i--)
    {
          cout<<"                    pick item : "<<pick_item[i]<<endl;            
    }
   
                             /*                    ....                                      */
                            /*                      ..  
                                                End Program                                  */
                            /*                    Thanks                                     */
                            /*                     ....                                      */
                            /*                      ..                                       */
   getch();  
}

