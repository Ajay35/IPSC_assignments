import sys
import numpy as np

def hes_lu(A):
	mat=A
	n=A.shape[0];
	U=np.zeros((n,n))
	v = np.zeros((n,1));
	for k in range(n-1):
		#since elements after k+1 are 0 we have to do for k+1 only
   		v[k+1]= mat[k+1][k]/mat[k][k];
   		mat[k+1,k:n] = mat[k+1,k:n] - v[k+1]*mat[k,k:n];
	U=np.triu(mat,-1)
	return v,U

A=np.array([[1,4,2,3],[3,4,1,7],[0,2,3,4],[0,0,1,3]],dtype='f')
v,u=hes_lu(A)

lower=np.identity(4)
upper=np.zeros((4,4))
# creating indentity matrix for retreiving lower matrix

i=1
j=0
ind=1
while i<4 and j<4:
	lower[i][j]+=v[ind]
	i+=1
	j+=1
	ind+=1

print('upper',u)
print('lower',lower)
print('Result LU product:')
result=np.zeros((4,4))
	
for i in range(4):
	for j in range(4):
		for k in range(4):
			result[i][j] += lower[i][k] * u[k][j]

print('checked LU result:\n',result)