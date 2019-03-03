#include<bits/stdc++.h>
using namespace std;
const int MAX=100;

class coo_matrix{ 

public:
	int row, col,len;
	int mat_info[MAX][3]; 
      
coo_matrix(int r,int c){  
   row = r; 
   col = c; 
   len = 0; 
} 
void insert(int r, int c, int val){ 
    if (r > row || c > col) { 
        cout<<"Wrong entry"<<endl; 
    } 

    else { 
        mat_info[len][0] = r;
        mat_info[len][1] = c;
        mat_info[len][2] = val;
        len++; 
    } 
} 
  
void add(coo_matrix b){ 

    if (row != b.row || col != b.col) { 
        cout<<"Matrices can't be added"<<endl; 
    } 

    else { 

        int apos = 0, bpos = 0; 
        coo_matrix result(row,col);; 
        while (apos < len && bpos < b.len) { 
            if (mat_info[apos][0] > b.mat_info[bpos][0] || (mat_info[apos][0] == b.mat_info[bpos][0] &&  mat_info[apos][1] > b.mat_info[bpos][1])){ 
               result.insert(b.mat_info[bpos][0],b.mat_info[bpos][1],b.mat_info[bpos][2]); 
               bpos++; 
            } 

	
            else if (mat_info[apos][0] < b.mat_info[bpos][0] || (mat_info[apos][0] == b.mat_info[bpos][0] && mat_info[apos][1] < b.mat_info[bpos][1])){ 

                result.insert(mat_info[apos][0],mat_info[apos][1],mat_info[apos][2]); 
                apos++; 
            } 

            else{ 
                int addedval = mat_info[apos][2] + b.mat_info[bpos][2]; 

                if (addedval != 0) 
                    result.insert(mat_info[apos][0],mat_info[apos][1],addedval);
                apos++; 
                bpos++; 
            } 
        } 

        
        while (apos < len) 
            result.insert(mat_info[apos][0],mat_info[apos][1],mat_info[apos++][2]); 

        while (bpos < b.len) 
            result.insert(b.mat_info[bpos][0],b.mat_info[bpos][1],b.mat_info[bpos++][2]); 

        result.print(); 
    } 
} 
  
    coo_matrix transpose(){ 
  
        coo_matrix result(col, row); 
        result.len = len; 
        int count[col + 1]; 

        for (int i = 1; i <= col; i++) 
            count[i] = 0; 
  
        for (int i = 0; i < len; i++) 
            count[mat_info[i][1]]++; 
  
        int index[col + 1]; 
  
        
        index[1] = 0;
        for (int i = 2; i <= col; i++)
            index[i] = index[i - 1] + count[i - 1]; 
  
        for (int i = 0; i < len; i++) { 
  
            int rpos = index[mat_info[i][1]]++; 
            result.mat_info[rpos][0] = mat_info[i][1];
            result.mat_info[rpos][1] = mat_info[i][0];
            result.mat_info[rpos][2] = mat_info[i][2]; 
        } 
        return result; 
    } 
  
     void multiply(coo_matrix b){ 
  
        if (col != b.row) { 
  
            cout<<"Invalid dimensions"<<endl; 
            return; 
        } 
  
        
        
        b = b.transpose(); 
        int apos, bpos; 
  
       	coo_matrix result(row, b.row); 
  
        for (apos = 0; apos < len;) { 

            int r = mat_info[apos][0]; 

            for (bpos = 0; bpos < b.len;) { 
               int c = b.mat_info[bpos][0]; 
  
          	    int tempa = apos; 
                int tempb = bpos; 
  
                int sum = 0; 
  
              while (tempa < len && mat_info[tempa][0] == r 
                       && tempb < b.len && b.mat_info[tempb][0] == c) { 
  
                    if (mat_info[tempa][1] < b.mat_info[tempb][1]) 
  
          
                        tempa++; 
  
                    else if (mat_info[tempa][1] > b.mat_info[tempb][1]) 
  
                        tempb++; 
                    else
  
                        sum += mat_info[tempa++][2] * b.mat_info[tempb++][2]; 
                } 
  
                
                if (sum != 0) 
                    result.insert(r, c, sum); 
  
                while (bpos < b.len && b.mat_info[bpos][0] == c) 
  
                    bpos++; 
            } 
  
            while (apos < len && mat_info[apos][0] == r) 
  
                apos++; 
        } 
  
        result.print(); 
    } 
  
    void print(){ 
        cout<<"Dimension: " <<row << "x " << col<<endl; 
        cout<<"COO Matrix: \nRow Column Value"<<endl; 
  
        for (int i = 0; i < len; i++) { 
  
            cout<<mat_info[i][0] << " "<< mat_info[i][1] << " " << mat_info[i][2]<<endl;
            cout<<endl; 
        } 
    }     
}; 
  
int main(){ 
  
        coo_matrix a(4, 4); 
        coo_matrix b(4, 4); 
  
        a.insert(1, 2, 10); 
        a.insert(1, 4, 12); 
        a.insert(3, 3, 5); 
        a.insert(4, 1, 15); 
        a.insert(4, 2, 12); 
        b.insert(1, 3, 8); 
        b.insert(2, 4, 23); 
        b.insert(3, 3, 9); 
        b.insert(4, 1, 20); 
        b.insert(4, 2, 25); 
  
         
        cout<<"Addition: "<<endl; 
        a.add(b); 
        cout<<"Multiplication: "<<endl; 
        a.multiply(b); 
        cout<<"Transpose: "<<endl; 
        coo_matrix atranspose = a.transpose(); 
        atranspose.print();
        return 0; 
    }