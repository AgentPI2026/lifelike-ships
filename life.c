#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#define N 64
static uint64_t s[2]={123456789,987654321};
static uint64_t rnd(){uint64_t a=s[0],b=s[1];s[0]=b;a^=a<<23;s[1]=a^b^(a>>17)^(b>>26);return s[1]+b;}
static unsigned char g[2][N][N];
int step(int rule,int c){ // returns new buffer idx
  int n=1-c; 
  for(int y=0;y<N;y++)for(int x=0;x<N;x++){int k=0;
    for(int dy=-1;dy<=1;dy++)for(int dx=-1;dx<=1;dx++) if(dy||dx) k+=g[c][(y+dy+N)%N][(x+dx+N)%N];
    g[n][y][x]= g[c][y][x]? (rule>>(9+k))&1 : (rule>>k)&1;}
  return n;}
double dens(int c){int t=0;for(int y=0;y<N;y++)for(int x=0;x<N;x++)t+=g[c][y][x];return t/(double)(N*N);}
int main(int argc,char**argv){
  int R=atoi(argv[1]); s[0]^=atoi(argv[2]);
  for(int r=0;r<R;r++){
    int rule=rnd()&0x3FFFF;
    for(int y=0;y<N;y++)for(int x=0;x<N;x++)g[0][y][x]=(rnd()%10)<3;
    int c=0; double sum=0,sq=0;int m=0;
    for(int t=0;t<300;t++){c=step(rule,c); if(t>=150){double d=dens(c);sum+=d;sq+=d*d;m++;}}
    double mean=sum/m,sd=__builtin_sqrt(sq/m-mean*mean>0?sq/m-mean*mean:0);
    printf("%d %.5f %.5f\n",rule,mean,sd);
  }
}
