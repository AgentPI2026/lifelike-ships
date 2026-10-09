// Glider finder for Life-like rules: random soups -> isolated components -> check translated recurrence.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#define G 96
static uint64_t s[2]={88172645463325252ULL,1442695040888963407ULL};
static uint64_t rnd(){uint64_t a=s[0],b=s[1];s[0]=b;a^=a<<23;s[1]=a^b^(a>>17)^(b>>26);return s[1]+b;}
typedef unsigned char grid[G][G];
static int rule;
static void step(grid in,grid out){
  for(int y=0;y<G;y++)for(int x=0;x<G;x++){int k=0;
    for(int dy=-1;dy<=1;dy++)for(int dx=-1;dx<=1;dx++)if(dy||dx){int yy=y+dy,xx=x+dx;if(yy>=0&&yy<G&&xx>=0&&xx<G)k+=in[yy][xx];}
    out[y][x]=in[y][x]?(rule>>(9+k))&1:(rule>>k)&1;}}
static int bbox(grid g,int*x0,int*y0,int*x1,int*y1,int*cnt){*x0=G;*y0=G;*x1=-1;*y1=-1;*cnt=0;
  for(int y=0;y<G;y++)for(int x=0;x<G;x++)if(g[y][x]){(*cnt)++;if(x<*x0)*x0=x;if(x>*x1)*x1=x;if(y<*y0)*y0=y;if(y>*y1)*y1=y;}
  return *cnt>0;}
static int same_shift(grid a,grid b,int*dx,int*dy){ // is b a translate of a?
  int ax0,ay0,ax1,ay1,ac,bx0,by0,bx1,by1,bc;
  if(!bbox(a,&ax0,&ay0,&ax1,&ay1,&ac)||!bbox(b,&bx0,&by0,&bx1,&by1,&bc))return 0;
  if(ac!=bc||ax1-ax0!=bx1-bx0||ay1-ay0!=by1-by0)return 0;
  for(int y=ay0;y<=ay1;y++)for(int x=ax0;x<=ax1;x++)if(a[y][x]!=b[y-ay0+by0][x-ax0+bx0])return 0;
  *dx=bx0-ax0;*dy=by0-ay0;return 1;}
static grid A,B,C,P,Q,L; static int lab[G][G];
static void flood(int y,int x,int id){ // components with radius-2 linkage
  int st[G*G][2],sp=0;st[sp][0]=y;st[sp][1]=x;sp++;lab[y][x]=id;
  while(sp){sp--;int cy=st[sp][0],cx=st[sp][1];
    for(int dy=-2;dy<=2;dy++)for(int dx=-2;dx<=2;dx++){int yy=cy+dy,xx=cx+dx;
      if(yy>=0&&yy<G&&xx>=0&&xx<G&&A[yy][xx]&&!lab[yy][xx]){lab[yy][xx]=id;st[sp][0]=yy;st[sp][1]=xx;sp++;}}}}
int main(int argc,char**argv){
  rule=atoi(argv[1]);int soups=atoi(argv[2]);s[0]^=atoi(argv[3])*7919;
  int found=0; static char seen[64][64][4]; // not used for dedup precisely
  char keys[200][64];int nk=0;
  for(int sp=0;sp<soups;sp++){
    memset(A,0,sizeof A);
    int sz=12+rnd()%12;
    for(int y=0;y<sz;y++)for(int x=0;x<sz;x++)A[G/2-sz/2+y][G/2-sz/2+x]=(rnd()%100)<(30+rnd()%30);
    for(int t=0;t<150;t++){step(A,B);memcpy(A,B,sizeof A);}
    memset(lab,0,sizeof lab);int nl=0;
    for(int y=0;y<G;y++)for(int x=0;x<G;x++)if(A[y][x]&&!lab[y][x])flood(y,x,++nl);
    for(int l=1;l<=nl&&l<30;l++){
      memset(P,0,sizeof P);int c=0,x0=G,y0=G,x1=-1,y1=-1;
      for(int y=0;y<G;y++)for(int x=0;x<G;x++)if(lab[y][x]==l){c++;if(x<x0)x0=x;if(x>x1)x1=x;if(y<y0)y0=y;if(y>y1)y1=y;}
      if(c<3||x1-x0>20||y1-y0>20)continue;
      for(int y=y0;y<=y1;y++)for(int x=x0;x<=x1;x++)if(lab[y][x]==l)P[G/2-10+y-y0][G/2-10+x-x0]=1;
      memcpy(Q,P,sizeof Q);
      for(int t=1;t<=40;t++){
        step(Q,C);memcpy(Q,C,sizeof Q);
        int dx,dy;
        // touching border => escaped / too big
        int bx0,by0,bx1,by1,bc;if(!bbox(Q,&bx0,&by0,&bx1,&by1,&bc)||bx0<3||by0<3||bx1>G-4||by1>G-4)break;
        if(same_shift(P,Q,&dx,&dy)){
          if(dx||dy){char k[64];snprintf(k,64,"p%d d(%d,%d) n%d",t,dx,dy,c);
            int dup=0;for(int i=0;i<nk;i++)if(!strcmp(keys[i],k))dup=1;
            if(!dup&&nk<200){strcpy(keys[nk++],k);found++;
              printf("rule %d GLIDER %s\n",rule,k);
              for(int y=G/2-10;y<=G/2-10+(y1-y0);y++){for(int x=G/2-10;x<=G/2-10+(x1-x0);x++)putchar(P[y][x]?'O':'.');putchar('\n');}
            }}
          break;}
      }
    }
  }
  fprintf(stderr,"rule %d: %d distinct glider signatures\n",rule,found);
}
