#include<bits/stdc++.h>
using namespace std;


class csr_matrix{
public:
	int row,col;
	vector<int> row_ptr;
	vector<int> col_indices;
	vector<int> val;
    void print(vector<int> arr){
     for(int i=0;i<arr.size();i++){
         cout<<arr[i]<<" ";
     }
     cout<<"\n";
    }
	csr_matrix(vector<vector<int>> v){
    
    
	int m=v.size();
	int n=v[0].size();
    
	vector<int> vals;
	vector<int> column_indices;
	vector<int> row_ptrs;
    int c=0;
    row_ptrs.push_back(c);
	for (int i = 0; i < m; i++) { 
        for (int j = 0; j < n; j++) { 
            if (v[i][j] != 0) { 
                vals.push_back(v[i][j]); 
                column_indices.push_back(j); 
                c++; 
            } 
        } 
        row_ptrs.push_back(c); 
    }
    //row_ptrs.push_back(c+1); 
    cout<<"row ptrs:"<<endl;
    print(row_ptrs);
    cout<<"values"<<endl;
    print(vals);
    cout<<"column indices"<<endl;
    print(column_indices);
	row_ptr=row_ptrs;
	val=vals;
	col_indices=column_indices;
    cout<<"-----------"<<endl;
}

};

void csr_matmat_pass1(int n_row,int n_col,vector<int> Ap,vector<int> Aj,vector<int> Bp,vector<int> Bj,vector<int>& Cp)
{
    cout<<"pass1 "<<endl;
    std::vector<int> mask(n_col, -1);
    Cp[0] = 0;

    int nnz = 0;
    for(int i = 0; i < n_row; i++){
    	int row_nnz = 0;
        for(int jj = Ap[i]; jj < Ap[i+1]; jj++){
            int j = Aj[jj];
            for(int kk = Bp[j]; kk < Bp[j+1]; kk++){
                int k = Bj[kk];
                if(mask[k] != i){
                    mask[k] = i;
                    row_nnz++;
                }
            }
        }

        int next_nnz = nnz + row_nnz;
        nnz = next_nnz;
        Cp[i+1] = nnz;
    }
}


void csr_matmat_pass2(int n_row,int n_col,vector<int> Ap,vector<int> Aj,vector<int> Ax,vector<int> Bp,vector<int> Bj,vector<int> Bx,vector<int>& Cp,vector<int>& Cj,vector<int>& Cx){
    cout<<"pass2 "<<endl;
    std::vector<int> next(n_col,-1);
    std::vector<int> sums(n_col, 0);

    int nnz = 0;

    Cp[0] = 0;
    cout<<"p1"<<endl;
    for(int i = 0; i < n_row; i++){
        int head   = -2;
        int length =  0;

        int jj_start = Ap[i];
        int jj_end   = Ap[i+1];
        for(int jj = jj_start; jj < jj_end; jj++){
          
            int j = Aj[jj];
            int v = Ax[jj];
            int kk_start = Bp[j];
            int kk_end   = Bp[j+1];
            for(int kk = kk_start; kk < kk_end; kk++){
                int k = Bj[kk];
                sums[k] += v*Bx[kk];

                if(next[k] == -1){
                    next[k] = head;
                    head  = k;
                    length++;
                }
            }
        }

        for(int jj = 0; jj < length; jj++){
            if(sums[head] != 0){
                Cj[nnz] = head;
                Cx[nnz] = sums[head];
                nnz++;
            }

            int temp = head;
            head = next[head];
            next[temp] = -1;
            sums[temp] =  0;
        }
        Cp[i+1] = nnz;
    }
}
 void print(vector<int> arr){
     for(int i=0;i<arr.size();i++){
         cout<<arr[i]<<" ";
     }
     cout<<"\n";
    }
int main(){
	
	int m,n;
	m=3,n=3;
	vector<std::vector<int>> mat1(m,vector<int>(n,0));
	vector<std::vector<int>> mat2(m,vector<int>(n,0));
	vector<std::vector<int>> test_mat(m+1,vector<int>(n+1,0));
    vector<std::vector<int>> test_mat1(m+1,vector<int>(n+3,0));
	/*assigning arrays for product of C=A*B*/
	vector<int> Cx(n*n,0);
	vector<int> Cp(n+1,0);
	vector<int> Cj(n,0);

    test_mat={{0,0,0,0},{5,8,0,0},{0,0,3,0},{0,6,0,0}};
    test_mat1={{10,20,0,0,0,0},{0,30,0,40,0,0},{0,0,50,60,70,0},{0,0,0,0,0,80}};
	mat1={{0,0,1},{2,3,0},{5,0,0}};
	mat2={{0,0,1},{0,2,0},{0,0,3}};
    csr_matrix obj0(test_mat);
    csr_matrix onj3(test_mat1);
	csr_matrix obj1(mat1);
	csr_matrix obj2(mat2);
	csr_matmat_pass1(m,n,obj1.row_ptr,obj1.col_indices,obj2.row_ptr,obj2.col_indices,Cp);
	csr_matmat_pass2(m,n,obj1.row_ptr,obj1.col_indices,obj1.val,obj2.row_ptr,obj2.col_indices,
    obj2.val,Cp,Cj,Cx);



    cout<<"vals in product:"<<endl;
    print(Cx);
    cout<<"row ptrs:"<<endl;
    print(Cp);
    cout<<"columns:"<<endl;
    print(Cj);

	return 0;
}