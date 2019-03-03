import numpy as np
from scipy import linalg as la
import random

def matrix_multiply(mat1,mat2):
	m1,n1=mat1.shape
	m2,n2=mat2.shape
	if mat1.shape[1] != mat2.shape[0]:
		print('n1 and m2 are not equal ,multiplication not possible')
		return None

	result=np.zeros((m1,n2))
	
	for i in range(mat1.shape[0]):
		for j in range(mat2.shape[1]):
			for k in range(mat2.shape[0]):
				result[i][j] += mat1[i][k] * mat2[k][j]
	return result
def matrix_vector(A,x):
	
	m,n=A.shape
	y=np.zeros((m,1))
	for i in range(m):
		for j in range(n):
			y[i] = y[i] + A[i] [j]*x[j]
	return y

	
	
def get_transpose(mat):

	m,n=mat.shape
	result=np.zeros((n,m))
	for i in range(m):
   		for j in range(n):
   			result[j][i] = mat[i][j]
	return result

def backward_substituion(mat,b,n):
	
	x=np.zeros(b.shape[0])
	x[-1] = 1. / mat[-1, -1] * b[-1]
	for i in range(n-2, -1, -1):
		x[i] = 1. / mat[i, i] * (b[i] - np.sum(mat[i, i+1:] * x[i+1:]))
	return x


def house(a):
    v = a / (a[0] + np.copysign(np.linalg.norm(a), a[0]))
    v[0] = 1
    H = np.eye(a.shape[0])
    H -= (2 / np.dot(v, v)) * np.dot(v[:, None], v[None, :])
    return H
 
def myqr(A):
    m, n = A.shape
    Q = np.eye(m)
    for i in range(n - (m == n)):
        H = np.eye(m)
        H[i:, i:] =house(A[i:, i])
        Q = np.dot(Q, H)
        A = np.dot(H, A)
    return Q, A
 

#A=np.array([[7,-2,1],[14,-7,-3],[-7, 11, 18]],dtype='f')
#b=np.array([4,-5,10],dtype='f')

A=np.random.rand(4,3)
b=np.random.rand(3,1)

m=A.shape[0]
n=A.shape[1]
original_mat=A
q, r = myqr(A)
print('q:\n', q.round(6))
print('r:\n', r.round(6))
print('original matrix:\n',A)
print("Checking solution:\n")
print(matrix_multiply(q,r))

## transforming q and r ot q_d and e_d by removing last row and column
q_d=q[:n,:n]
r_d=r[:n,:n]

print('new q shape',q_d.shape)
print('new r shape',r_d.shape)
# y=Q^t b
Qt=get_transpose(q_r)
y=matrix_vector(Qt,b)


#solve Rx=y by back substitution
x=backward_substituion(r,y,n)
print("ans",x)

print('Final answer:')
c=original_mat.dot(x)
c=c-b
print('difference between solutions:')
print(np.linalg.norm(c))

## using inbuilt functions
in_ans=np.linalg.solve(original_mat,b)
print('Final answer using inbuilt function:')
print(in_ans)
c=original_mat.dot(in_ans)
c=c-b
print('difference between solutions using inbuilt functions:')
print(np.linalg.norm(c))



