#ifndef _matrixclass
#define _matrixclass

class Matrix2D {
	private: 
		int rows, cols;
		int ** data;
    public:
		Matrix2D(int r, int c);
		int GetIndex(int i, int j);
		void SetIndex(int i, int j, int val);
};

Matrix2D::Matrix2D(int r, int c)
{
    rows=r;
	cols=c;
	data = new int* [r]; 

	for (int i = 0; i<rows; i++) 
		data[i] = new int[cols];
		
}

int Matrix2D::GetIndex(int i, int j)
{
    return data[i][j];
}

void Matrix2D::SetIndex(int i, int j, int value)
{
    data[i][j] = value;
}

#endif
