import sys
import numpy as np

def get_lu(mat,n):
	og_mat=mat
	for k in range(n):
		mat[k+1:n,k]= mat[k+1:n,k]/mat[k,k]
		for i in range(k+1,n):
			for j in  range(k+1,n):
				mat[i][j]=( mat[i][j])-(mat[i][k]*mat[k][j])
	return mat


def forward_substitution(mat,b,n):
	
	y=np.zeros(b.shape[0])
	y[0]=b[0]/mat[0][0]

	for i in range(1,n):
		t=b[i]
		for j in range(i):
			t=t-mat[i][j]*y[j]
		y[i]=t/mat[i][i]

	return y

def backward_substituion(mat,b,n):
	
	x=np.zeros(b.shape[0])

	x[-1] = 1. / mat[-1, -1] * b[-1]
	for i in range(n-2, -1, -1):
		x[i] = 1. / mat[i, i] * (b[i] - np.sum(mat[i, i+1:] * x[i+1:]))
	return x

def lu_solve(L_mat,U_mat,b,n):
	y=forward_substitution(L_mat,b,n)

	print('y for backward backward_substituion',y)

	ans=backward_substituion(U_mat,y,n)

	print('Final answer:')
	print(ans)
	c=original_mat.dot(ans)
	c=c-b
	print('difference between solutions:')
	print(np.linalg.norm(c))




n=3
mat=np.array([[7,-2,1],[14,-7,-3],[-7, 11, 18]])
#mat=np.array([[1,2,3],[2,3,10],[-3,-6, -8]],dtype='f')
hess=np.array([[1,4,2,3],[3,4,1,7],[0,2,3,4],[0,0,1,3]],dtype='f')

original_mat=np.copy(mat)

#b=np.array([12,17,5])
b=np.array([4,-5,10],dtype='f')
# getting LU decomposition
lu_mat=get_lu(mat,n)
L_mat=np.zeros((n,n))
U_mat=np.zeros((n,n))

for i in range(n):
	for j in range(n):
		if i==j:
			L_mat[i][j]=1
		elif i>j:
			L_mat[i][j]=lu_mat[i][j]

for i in range(n):
	for j in range(n):
		if i<=j:
			U_mat[i][j]=lu_mat[i][j]

print('lower matrix:\n',L_mat)
print('upper matrix:\n',U_mat)

lu_solve(L_mat,U_mat,b,n)
	

'''
hes_lu=get_lu(hess,4)

print("LU:\n",hes_lu)



result=np.zeros((4,4))
	
for i in range(4):
	for j in range(4):
		for k in range(4):
			result[i][j] += L_mat[i][k] * U_mat[k][j]

print('checked LU result:\n',result)
'''