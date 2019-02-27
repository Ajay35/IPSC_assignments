import sys
import numpy as np

def get_csr_matrix(mat1):

	m=mat1.shape[0]
	n=mat1.shape[1]
	vals=[]
	columns=[]
	row_ptrs=[]
	c=0
	row_ptrs.append(c)
	for i in range(m):
		for j in range(n):
			if mat1[i][j] != 0:
				
				columns.append(j)
				vals.append(mat1[i][j])
				c+=1
		row_ptrs.append(c)
	return row_ptrs,columns,vals

def build_from_crs(row_ptrs,columns,vals,m,n):

	mat=np.zeros((m,n))
	index=0
	for i in range(1,len(row_ptrs)):
		nz=row_ptrs[i]-row_ptrs[i-1]

		for j in range(nz):
			mat[i-1][columns[index]]=vals[index]
			index+=1

	for i in range(m):
		for j in range(n):
			print(int(mat[i][j]),end=" ")
		print("\n")





m1=int(input('Enter first matrix rows:'))
n1=int(input('Enter first matrix columns:'))

#mat1=np.zeros((m1,n1));
mat1=np.array([[1,0,0,2,0],[3,4,0,5,0],[6,0,7,8,9],[0,0,10,11,0],[0,0,0,0,12]])
#mat1=np.array([[0,0,0,0],[5,8,0,0],[0,0,3,0],[0,6,0,0]])

for i in range(5):
	for j in range(5):
		print(mat1[i][j],end=" ")
	print("\n")

row_ptrs,columns,vals=get_csr_matrix(mat1)
print(vals)
print(columns)
print(row_ptrs)
print("\n\n")

build_from_crs(row_ptrs,columns,vals,5,5)