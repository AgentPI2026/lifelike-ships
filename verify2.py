import numpy as np,sys
def run(rule,pat,T,N=80):
    B=np.array([(rule>>i)&1 for i in range(9)]);S=np.array([(rule>>(9+i))&1 for i in range(9)])
    g=np.zeros((N,N),np.uint8)
    for y,r in enumerate(pat):
        for x,c in enumerate(r):
            if c=='O': g[N//2+y,N//2+x]=1
    res=[]
    for t in range(1,T+1):
        n=sum(np.roll(np.roll(g,dy,0),dx,1) for dy in(-1,0,1) for dx in(-1,0,1) if dy or dx)
        g=np.where(g==1,S[n],B[n]).astype(np.uint8)
        ys,xs=np.nonzero(g); res.append((t,int(g.sum()),(round(ys.mean()-N//2,1),round(xs.mean()-N//2,1)) if len(ys) else None))
    return res
for rule,pat in [(76136,["O.O.","..O.","OOOO","..O.","O.O."]),(224008,[".O..","OO..","OOOO",".OO."]),(71880,[".O.O","O..O",".OOO","..O."])]:
    r=run(rule,pat,70); print(rule,[x for x in r if x[0]%14==0])
