import sys
import numpy as np

def coordinate_storage_format(mat1):

	m=mat1.shape[0]
	n=mat1.shape[1]
	vals=[]
	columns_indices=[]
	rows_indices=[]
	
	for i in range(m):
		for j in range(n):
			if  mat1[i][j] != 0:
				rows_indices.append(i)
				columns_indices.append(j)
				vals.append(mat1[i][j])

	return rows_indices,columns_indices,vals

def build_from_coo(rows_indices,columns_indices,vals,m,n):
	
	mat=np.zeros((m,n))

	for i in range(len(rows_indices)):
		mat[rows_indices[i]][columns_indices[i]]=vals[i]


	for i in range(m):
		for j in range(n):
			print(int(mat[i][j]),end=" ")
		print("\n")

'''
m1=int(input('Enter first matrix rows:'))
n1=int(input('Enter first matrix columns:'))

for i in range(m1):
	for j in range(n1):
		mat1[i][j]=random.randrange(0, 1000) 
'''
#mat1=np.array([[1,0,0,2,0],[3,4,0,5,0],[6,0,7,8,9],[0,0,10,11,0],[0,0,0,0,12]])
mat1=np.array([[1 4 7],[2 5 8],[3, 6, 10])


row_indices,col_indices,vals=coordinate_storage_format(mat1)
print('row indices',row_indices)
print('column indices',col_indices)
print('values',vals)
print("\n\n")
print('Build matrix from coordinate storage format')
build_from_coo(row_indices,col_indices,vals,5,5)
