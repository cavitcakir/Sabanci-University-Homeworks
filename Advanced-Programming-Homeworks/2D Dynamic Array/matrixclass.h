#ifndef _matrixclass
#define _matrixclass

/*
 1) Is  not  templated,
 2) Works for only integers,
 3) Does not implement default constructor,
 4) Does not implement  deep copy  constructor,
 5) Does not implement  destructor , and
 6) Lacks several other operators that the main function uses.
 
 
 
 The  definitive tasks  of the homework can be ordered like this:
 + Convert the basis class into templated version,
 + Implement the default constructor (It may set everything to minimum default.),
 + Implement the destructor (Deallocate the 2D dynamic array held within the object.),
 + Implement >> operator (We recommend you to implement this function at this stage, as
   it helps debugging other functions. You may assume that this function will only be used
   with ifstream objects, but not with cin or istringstream.),
 + Implement << operator,
 + Implement += and = operators for the class,
 + Implement the copy constructor (You will need this for + operator.  Do not make shallow copy , it will change outputs  in main and make your program fail test cases.), and
 + Finally, implement + operator which will return a new Matrix2D object.
 
 */

using namespace std;

template <class itemType>
class Matrix2D {
     friend ifstream & operator >> (ifstream & ifObject, Matrix2D<itemType> & cObject);
     friend ostream & operator << (ostream & osObject, Matrix2D<itemType> & cObject);
    friend Matrix2D<itemType> & operator + (const Matrix2D<itemType> & lhs,const Matrix2D<itemType> & rhs);
	private: 
		int rows, cols;
		itemType ** data;
    public:
		Matrix2D(const Matrix2D<itemType> & rhs);
        Matrix2D();
        ~Matrix2D();
		itemType GetIndex(int i, int j);
		void SetIndex(int i, int j, itemType val);
        Matrix2D<itemType> & operator += (const Matrix2D<itemType> & rhs);
        Matrix2D<itemType> & operator = (const Matrix2D<itemType> & rhs);
    
};



template <class itemType>
Matrix2D<itemType> & operator + (const Matrix2D<itemType> & lhs, const Matrix2D<itemType> & rhs)
{
    Matrix2D<itemType> elda = new Matrix2D<itemType>(lhs);
    
    for(int i = 0; i < lhs.rows ; i++)
    {
        for(int j = 0; j < lhs.cols ; j++)
        {
            elda.data[i][j] += rhs.data[i][j];
        }
    }
    return elda;
}


template <class itemType>
Matrix2D<itemType> & Matrix2D<itemType> :: operator = (const Matrix2D<itemType> & rhs)
{
    for(int i = 0; i < rows ; i++)
    {
        for(int j = 0; j < cols ; j++)
        {
            data[i][j] = rhs.data[i][j];
        }
        delete rhs.data[i];
    }
    delete rhs.data;
    return *this;
}
template <class itemType>
Matrix2D<itemType> & Matrix2D<itemType> :: operator += (const Matrix2D<itemType> & rhs)
{
    for(int i = 0; i < rows ; i++)
    {
        for(int j = 0; j < cols ; j++)
        {
            data[i][j] += rhs.data[i][j];
        }
    }
    return *this;
}

template <class itemType>
ostream & operator << (ostream & osObject, Matrix2D<itemType> & cObject)
{
    for (int i = 0; i < cObject.rows; i++)
    {
        for (int j = 0; j < cObject.cols; j++)
        {
            osObject << cObject.data[i][j];
        }
        cout << endl;
    }
    
    return osObject;
}

template <class itemType>
ifstream & operator >> (ifstream & ifObject, Matrix2D<itemType> & iObject)
{
    string line;
    int row = 0, col = 0;
   while(getline(ifObject, line))
   {
       stringstream ss(line);
       itemType word;
       while(ss >> word)
       {
           col++;
       }
       row++;
   }
    iObject.rows = row;
    iObject.cols = col;
    
    iObject.data = new itemType * [row];
    
    for (int i = 0; i<row; i++)
        iObject.data[i] = new itemType[col];
    
    ifObject.seekg(0);

    int i =0;
    while(getline(ifObject, line) ) //&& i <= Matrix2D<itemType>::rows)
    {
        int a =0;
        stringstream ss(line);
        itemType word;
        while(ss >> word) //&& a <= Matrix2D<itemType>::cols)
        {
            iObject.data[i][a] = word;
            a++;
        }
        i++;
    }
    return ifObject;
}

template <class itemType>
Matrix2D<itemType>::Matrix2D()
{
    rows=0;
    cols=0;
    data = NULL;
}

template <class itemType>
Matrix2D<itemType>::Matrix2D(const Matrix2D<itemType> & rhs)
{
    rows= rhs.rows;
	cols= rhs.cols;
	data = new itemType* [rhs.rows];

	for (int i = 0; i< rows; i++)
    {
       data[i] = new itemType[cols];
    }
    for(int i = 0; i < rhs.rows ; i++)
    {
        for(int j = 0; j < rhs.cols ; j++)
        {
            data[i][j] = rhs.data[i][j];
        }
    }
}



template <class itemType>
itemType Matrix2D<itemType>::GetIndex(int i, int j)
{
    return data[i][j];
}

template <class itemType>
void Matrix2D<itemType>::SetIndex(int i, int j, itemType value)
{
    data[i][j] = value;
}

template <class itemType>
Matrix2D<itemType>::~Matrix2D()
{
    for(int i = 0; i< rows; i++)
    {
        delete [] data[i];
    }
    delete[] data;
}



#endif
