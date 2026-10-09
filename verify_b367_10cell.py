import numpy as np
rule=71880
B=np.array([(rule>>i)&1 for i in range(9)]);S=np.array([(rule>>(9+i))&1 for i in range(9)])
pat=["..O.","OOO.","O.OO","OO..","..O."]
N=80;g=np.zeros((N,N),np.uint8)
for y,r in enumerate(pat):
    for x,c in enumerate(r):
        if c=='O':g[N//2+y,N//2+x]=1
for t in range(1,81):
    n=sum(np.roll(np.roll(g,dy,0),dx,1) for dy in(-1,0,1) for dx in(-1,0,1) if dy or dx)
    g=np.where(g==1,S[n],B[n]).astype(np.uint8)
    if t%16==0:
        ys,xs=np.nonzero(g);print(t,int(g.sum()),round(ys.mean()-N//2,2),round(xs.mean()-N//2,2))
