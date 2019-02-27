import sys
import randoimport numpy as np

def matrix_multiply(mat1,mat2):

	if mat1.shape[1] != mat2.shape[0]:
		print('n1 and m2 are not equal ,multiplication not possible')
		return None

	result=np.zeros((m1,n2))
	
	for i in range(mat1.shape[0]):
		for j in range(mat2.shape[1]):
			for k in range(mat2.shape[0]):
				result[i][j] += mat1[i][k] * mat2[k][j]
	return result


m1=int(input('Enter first matrix rows:'))
n1=int(input('Enter first matrix columns:'))

mat1=np.zeros((m1,n1));

m2=int(input('Enter second matrix rows:'))
n2=int(input('Enter second matrix columns:'))

mat2=np.zeros((m2,n2))

for i in range(m1):
	for j in range(n1):
		mat1[i][j]=random.randrange(0, 1000) 

for i in range(m2):
	for j in range(n2):
		mat2[i][j]=random.randrange(0, 1000) 

res=matrix_multiply(mat1,mat2)

print(res)