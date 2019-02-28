import sys
import numpy as np


def get_banded(mat1):
	m=mat1.shape[0]
	n=mat1.shape[1]
	print('rows',m)
	print('columns',n)
	q=0
	for i in range(m):
		if mat1[0][i]!=0:
			q+=1

	p=0
	for i in range(m):
		if mat1[i][0]!=0:
			p+=1
	p-=1
	q-=1
	band=p+q+1
	print('bandwidth:',band)
	print('p',p)
	print('q',q)

	band_mat1=np.zeros((band,n))

	for i in range(m):
		for j in range(n):
			if mat1[i][j]!=0:
				band_mat1[i-j+q][j]=mat1[i][j]

	return p,q,band_mat1


def banded_matrix_multiply(band_mat1,q1,band_mat2,q2,n):

	result=np.zeros((n,n))
	band=band_mat1.shape[0]
	for i in range(n):
		for j in range(n):
			for k in range(n):
				if i-k+q1>=0 and i-k+q1<band and k-j+q2>=0 and k-j+q2<band:
					result[i][j] += band_mat1[i-k+q1][k] * band_mat2[k-j+q2][j]

	return result



m=3
n=3

test_mat=np.array([[11, 12, 13, 0, 0, 0],[21, 22, 23 ,24, 0 ,0],[0, 32, 33, 34 ,35, 0],[0, 0 ,43, 44, 45, 46],[0, 0, 0 ,54 ,55 ,56],[0 ,0 ,0 ,0 ,65, 66]])
p,q,band_test_mat=get_banded(test_mat)

for i in range(p+q+1):
	for j in range(6):
		print(int(band_test_mat[i][j]),end=" ")
	print("\n")


mat1=np.array([[1,2,0],[0,3,4],[0,0,5]])
mat2=np.array([[6,0,0],[9,7,0],[0,10,8]])

p1,q1,mat1_band=get_banded(mat1)
p2,q2,mat2_band=get_banded(mat2)


for i in range(p1+q1+1):
	for j in range(n):
		print(int(mat1_band[i][j]),end=" ")
	print("\n")
print("-------")
for i in range(p2+q2+1):
	for j in range(n):
		print(int(mat2_band[i][j]),end=" ")
	print("\n")

product=banded_matrix_multiply(mat1_band,q1,mat2_band,q2,n)

for i in range(n):
	for j in range(n):
		print(product[i][j],end=" ")
	print(" ")