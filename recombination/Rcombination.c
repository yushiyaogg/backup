#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define N 20
int sign[N];
int n;
int r;
int total=0;
int Input(int array[N]);
int Calculation(int array[N],int length,int index);
int Combination(int n1,int r1);
void Rcombination(int array[N],int length);
int main(){
  int array[N];
  int i=0,length=0;
  length=Input(array);
  total=Combination(n+r-1,r);
  i=Calculation(array,length,0);
  printf("the result is:%d\n",total);
  return 0;

}
int Input(int array[N]){

  int i=0,k=0,p=0;
  printf("Input R:");
  scanf("%d",&r);
  printf("Input N:");
  scanf("%d",&n);
  printf("Input array:");
  for(i=0;i<n;i++){
     scanf("%d",&p);
     if(p<=r){
        array[k]=p+1;
        k++;
     }
  array[k]='\0';
  }
  /*i=0;
  while(array[i]!='\0'){
  
    printf("%d   ",array[i]);
    i++;
  }*/
  return k;
}
int Calculation(int array[N],int length,int index){
  if(index>=length) 
       Rcombination(array,length);
  else{
    sign[index]=1;
    Calculation(array,length,index+1);
    sign[index]=0;
    Calculation(array,length,index+1);

  
  }
  return 0;
}
void Rcombination(int array[N],int length){
  int i=0,len=0,number=0;
  for(i=0;i<length;i++)
      if(sign[i]){
        number=number+array[i];
        len=len+1;
      }
  printf("number:%d\n",number);
      if(number>0){
        int t=0;
        double p=0;
       // p=pow(-1,(double)len);
        if(len%2 == 0)
            p = 1;
        else
            p = -1;
        if(r-number>0){
           t=Combination(n+r-number-1,r-number);
           
           total=total+(int)p*t;
        
        }
        else if(r-number==0)  total=total+(int)p;
      printf("total:%d\n",total);
      }
}
int Combination(int n1,int r1){
    if(r1>n1) return 0;
    else if(r1==0) return 1;
    else{
        int t=0,result=1,b=0,i=0,re=1;
    
        b=n1-r1;
        if(b<n1/2) {
         t=b;
         b=r1;
         r1=t;
        }
        for(;n1>b;n1--){
          result=result*n1;
        }
        for(i=2;i<=r1;i++) re=re*i;
        result=result/re;
        return result;
    }
}
