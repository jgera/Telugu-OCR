#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>

#ifndef DATA_DIMENSION
#define DATA_DIMENSION 128
#endif

using namespace std;
#define MAINFILE "resource/TeluguMainStrokes.txt"
#define BASEFILE "resource/TeluguBaselineStrokes.txt"
#define BOTFILE "resource/TeluguBottomStrokes.txt"
#define TOPFILE "resource/TeluguTopStrokesV1.txt"
#define MAIN 0
#define BASELINE 1
#define BOTTOM 2
#define TOP 3
#define MAINCNT 149
#define BASECNT 20
#define BOTCNT 41
#define TOPCNT 27
#define LARGEVAL 999
#define DIMPRECLASS 70
#define POS 1
#define NEG 0
#define PI 3.14159265

//#define TRUE 1
//#define FALSE 0
#define ERROR_VALUE -999

#define SVM_PRECLASS FALSE

#define SMOOTH_WINDOW_SIZE 11
#define SMOOTH_SIGMA 1.5

template <class T>
class Matrix
{
 public:
  int nrows, ncols;
  T **array;

  /* Constructors */
  Matrix ();
  Matrix(const Matrix<T>& mat);
  ~Matrix();
  Matrix(vector<T>& ,vector<T>&);
  Matrix(T a[][2],int len);
  Matrix (int nrows, int ncols);
  Matrix (int nrows, int ncols, T element);
  Matrix (int nrows, int ncols, char rand);

  /* Operator Overloading */
  Matrix<T> operator+ (const Matrix<T>& m1);
  Matrix<T> operator- (const Matrix<T>& m1);
  Matrix<T> operator* (const Matrix<T>& m1);
  Matrix<T> operator* (T element);
  Matrix<T> operator/ (const Matrix<T>& m1);
  Matrix<T> operator/ (T element);

  void operator=(Matrix<T> mat);

  T& operator() (int i);
  T& operator() (int i,char col);
  T& operator() (int i, int j);
  Matrix<T> ScalarMult (const Matrix<T>& m1);

  double Norm();

  /* Size */
  Matrix<int> Size();

  /* Set the row and column */
  void SetRowCol (int row, int col);

  /* Get Elements from the user */
  void GetElements ();
  void GetElements (int row, int col);

  /* Display the data */
  void Display();

  /* Get is the FindElement function */
  Matrix<T> Get (int i, int j, int hvflag);
  Matrix<T> Get (int i, int j, int l, int m);
  T Get (int row, int col);
  Matrix<T> Get(Matrix<T>& indices);

  /* Set does the replace operations */
  void Set (int i, int j, int hvflag, Matrix<T>& m1);
  void Set (int i, int j, int l, int m, Matrix<T>& m1);
  void Set (int row, int col, T element);
  void Set (Matrix<T>& indices, Matrix<T>& m1);

  /* Insert */
  void Insert (int index, int hvflag, Matrix<T>& m1);
  /* Append */
  void Append ( Matrix<T>& m1, int hvflag);
  void RowAppend (T a[], int nacols);
  /* Delete */
  void Delete (int index, int hvflag);
  void Delete (int i, int j, int hvflag);

  /* Find Index returns 2D indices*/
  /* flag is >, < or = */
  Matrix<int> FindIndex (T element, char flag);

  /* Maximum Minimum Values */
  T Max ();
  T Max (Matrix& m1);
  T Max (int index, int hvflag);

  T Max (int index, int hvflag, Matrix& m1);

  Matrix<T> nMax (int n);
  Matrix<T> nMax (int n, Matrix& m1);
  Matrix<T> nMax (int n, int index, int hvflag);
  Matrix<T> nMax (int n, int index, int hvflag, Matrix& m1);
  T Min ();
  T Min (Matrix& m1);
  T Min (int index, int hvflag);
  T Min (int index, int hvflag, Matrix& m1);
  Matrix<T> nMin (int n);
  Matrix<T> nMin (int n, Matrix& m1);
  Matrix<T> nMin (int n, int index, int hvflag);
  Matrix<T> nMin (int n, int index, int hvflag, Matrix& m1);


  /* Other Functions */
  T Sum ();
  T Sum (int index, int hvflag);
  Matrix Sum (int hvflag); // Returns all the row/col wise sum in an array
  T Mean ();
  T Mean (int index, int hvflag);
  Matrix<T> Mean (int hvflag); // Returns all the row/col wise mean in an array
  Matrix<T> Transpose();

  //File operations
  void WriteToFile(const char* filename);
  void WriteToFile(ofstream& ofs);
  void ReadFromFile(const char* filename);
  void ReadFromFile(ifstream& ifs);
  void WriteStrkCoordsToFile(const char* filename);

  /* Error handling functions */
  void MakeNull();
  int IsNull();
  int ValidIndex (int i);
  int ValidIndex (int i, int j);
  int ValidIndex (int i, int start, int end);
  int IsValidHVFlag (int hvflag);
  //int IsValidADFlag(int adflag);

  void Copy(const Matrix<T>& m);
  void CopyTo(Matrix<T>& m);

  /* Sorts entire matrix */
  void Swap(int index1, int index2, int hvflag);
  Matrix<T> Sort (int adflag, int index, int hvflag);
  void MSort (Matrix<T>& result, Matrix<T>& temp, int left, int right, int index, int adflag, int hvflag);
  void Merge (Matrix<T>& result, Matrix<T>& temp, int lPos, int rPos, int rightEnd, int index, int adflag, int hvflag);

  void Load (char* fileName);

};

/*Constructors*/
/******************************************************************************
 * Name          : Matrix - default constructor
 * Syntax        : Matrix()
 * Description   : Default constructor task is to intialize the objects of its
                   class
 * Arguments     : Nothing
 * Returns       : Nothing
 * Exceptions    : Nil
 * Bugs          : Nil
 *****************************************************************************/

template <class T>
Matrix<T>::Matrix ()
{
  array=NULL;
  nrows=ncols=0;
}

template <class T>
Matrix<T>::~Matrix ()
{
  if(array!=NULL)
    {
      for(int i=0;i<nrows;i++)
            delete [] array[i];
      delete [] array;
    }
}

template <class T>
Matrix<T>::Matrix(const Matrix<T>& m1)
{
    int i,j;
    nrows=m1.nrows;
    ncols=m1.ncols;
    array=new T*[nrows];/*creates nrows */
    for(i=0;i<nrows;i++)
        array[i]=new T[ncols];/*creates ncols*/
    for(i=0;i<nrows;i++)
        for(j=0;j<ncols;j++)
            array[i][j]=m1.array[i][j];
}

template <class T>
Matrix<T>::Matrix (vector<T>& xp,vector<T>& yp)
{
    int i;
    if(!xp.empty() && !yp.empty())
    {
        nrows=xp.size();
        ncols=2;
        array=new T*[nrows];
        for(i=0;i<nrows;i++)
            array[i]=new T[ncols];
        for(i=0;i<nrows;i++)
        {
            array[i][0]=xp[i];
            array[i][1]=yp[i];
        }
    }
}

template <class T>
void Matrix<T>::operator=(Matrix<T> m1)
{
    int i,j;
    if(array!=NULL)
    {
        for(int i=0;i<nrows;i++)
            delete [] array[i];
        delete [] array;
    }
    nrows=m1.nrows;
    ncols=m1.ncols;
    array=new T*[nrows];/*creates nrows */
    for(i=0;i<nrows;i++)
        array[i]=new T[ncols];/*creates ncols*/
    for(i=0;i<nrows;i++)
        for(j=0;j<ncols;j++)
            array[i][j]=m1.array[i][j];
}

/*parameterized constructors */
/******************************************************************************
 * Name          : Matrix - parameterized constructor
 * Syntax        : Matrix (int ,int )
 * Description   : Parameterized constructor allows to intialize the various
                   data elements with different values,when objects are created
 * Arguments     : nr - number of rows, nc - number of columns
 * Returns       : Nothing
 * Exceptions    : Nil
 * Bugs          : Nil
 *****************************************************************************/
template <class T>
Matrix<T>::Matrix (int nr,int nc)
{
    int i,j;
    nrows=nr;
    ncols=nc;
    array=new T*[nrows];/*creates nrows */
    for(i=0;i<nrows;i++)
        array[i]=new T[ncols];/*creates ncols*/
    for(i=0;i<nrows;i++)
        for(j=0;j<ncols;j++)
            array[i][j]=0;
}

/******************************************************************************
 * Name          : Matrix - parameterized constructor
 * Syntax        : Matrix (int , int ,T)
 * Description   : Parameterized constructor allows to intialize the various                      data elements with different values,when objects are created
 * Arguments     : nr - number of rows ,nc - number of columns,element
 * Returns       : Nothing
 * Exceptions    : Nil
 * Bugs          : Nil
 *****************************************************************************/
template <class T>
Matrix<T>::Matrix (int nr,int nc,T element)
{
    int i,j;
    nrows=nr;
    ncols=nc;
    array=new T*[nrows];
    for(i=0;i<nrows;i++)
        array[i]=new T[ncols];
    for(i=0;i<nrows;i++)
        for(j=0;j<ncols;j++)
            array[i][j]=element;
}

/******************************************************************************
 * Name          : Matrix - parameterized constructors
 * Syntax        : Matrix (int ,int ,char)
 * Description   : Parameterized constructor  allows to intialize the various
                   data elements with different values,when objects are created
 * Arguments     : nr - number of rows,nc - number of columns,rand
 * Returns       : Nothing
 * Exceptions    : Nil
 * Bugs          : Nil
 *****************************************************************************/
template <class T>
Matrix<T>::Matrix (int nr, int nc,char rand)
{
    int i,j;
    nrows=nr;
    ncols=nc;
    array=new T*[nrows];
    for(i=0;i<nrows;i++)
        array[i]=new T[ncols];
    for(i=0;i<nrows;i++)
        for(j=0;j<ncols;j++)
            array[i][j]=rand;

}

/*operator Overloading*/
/******************************************************************************
 * Name          : operator+ - overloading binary arithmetic '+' operator
 * Syntax        : operator+ (Matrix )
 * Description   : To perform matrix addition
 * Arguments     : m1 - Matrix object
 * Returns       : temp - Matrix object
 * Exceptions    : Nil
 * Bugs          : Nil
 *****************************************************************************/
template <class T>
Matrix<T> Matrix<T>::operator+ (const Matrix<T>& m1)
{
    int i,j;
    if(nrows==m1.nrows && ncols==m1.ncols)
    {
        Matrix<T> temp(nrows,ncols);
        for(i=0;i<nrows;i++)
            for(j=0;j<ncols;j++)
                temp.array[i][j]=array[i][j]+m1.array[i][j];
        return(temp);
    }
    else
    {
        cout << "\nError:Matrix order not equal";
        Matrix<T> temp(0,0);
        return(temp);
    }

}

/******************************************************************************
 * Name          : operator-  - overloading binary arithmetic '-' operator
 * Syntax        : operator- (Matrix )
 * Description   : To perform matrix subtraction
 * Arguments     : m1 - Matrix object
 * Returns       : temp - Matrix object
 * Exceptions    : Nil
 * Bugs          : Nil
 *****************************************************************************/
template <class T>
Matrix<T> Matrix<T>::operator- (const Matrix<T>& m1)
{
    int i,j;
    if(nrows==m1.nrows && ncols==m1.ncols)
    {
        Matrix<T> temp(nrows,ncols);
        for(i=0;i<nrows;i++)
            for(j=0;j<ncols;j++)
                temp.array[i][j]=array[i][j]-m1.array[i][j];
        return(temp);
    }
    else
    {
        cout << "\nError:Matrix order not equal";
        Matrix<T> temp(0,0);
        return(temp);
    }
}

/******************************************************************************
 * Name          : operator* - overloading binary arithmetic '*' operator
 * Syntax        : operator* (Matrix )
 * Description   : To perform matrix multiplication
 * Arguments     : m1 - Matrix object
 * Returns       : temp - Matrix object
 * Exceptions    : Nil
 * Bugs          : Nil
 *****************************************************************************/
template <class T>
Matrix<T> Matrix<T>::operator* (const Matrix<T>& m1)
{
    int i,j,k;
    if(nrows==m1.ncols)
    {
        Matrix<T> temp(nrows,m1.ncols);
        for(k=0;k<nrows;k++)
            for(i=0;i<nrows;i++)
                for(j=0;j<ncols;j++)
                    temp.array[k][i]+=array[k][j]*m1.array[j][i];
        return(temp);
    }
    else
    {
        cout << "\nError:Matrix order not equal";
        Matrix<T> temp(0,0);
        return(temp);
    }
}

/******************************************************************************
 * Name          : ScalarMult - Scalar multplication
 * Syntax        : ScalarMult (Matrix )
 * Description   : To perform scalar multiplication of matrix
 * Arguments     : m1 - Matrix object
 * Returns       : temp - Matrix object
 * Exceptions    : Nil
 * Bugs          : Nil
 *****************************************************************************/
template <class T>
Matrix<T> Matrix<T>::ScalarMult (const Matrix<T>& m1)
{
    int i,j;
    if(nrows==m1.nrows && ncols==m1.ncols)
    {
        Matrix<T> temp(nrows,ncols);
        for(i=0;i<nrows;i++)
            for(j=0;j<ncols;j++)
                temp.array[i][j]=array[i][j]*m1.array[i][j];
        return(temp);
    }
    else
    {
        cout << "\nError:Matrix order not equal";
        Matrix<T> temp(0,0);
        return(temp);
    }

}

/******************************************************************************
 * Name          : operator* - overloading binary arithmetic '*' operator
 * Syntax        : operator* (T )
 * Description   : To multiply all elements of matrix by passed element
 * Arguments     : element
 * Returns       : temp - Matrix object
 * Exceptions    : Nil
 * Bugs          : Nil
 *****************************************************************************/
template <class T>
Matrix<T> Matrix<T>::operator* (T element)
{
    int i,j;
    Matrix<T> temp(nrows,ncols);
    for(i=0;i<nrows;i++)
        for(j=0;j<ncols;j++)
            temp.array[i][j]=array[i][j]*element;
    return(temp);

}
/******************************************************************************
 * Name          : operator/ - overloading binary arithmetic '/' operator
 * Syntax        : operator/ (Matrix )
 * Description   : To perform matrix divsion
 * Arguments     : m1 - Matrix object
 * Returns       : temp - Matrix object
 * Exceptions    : Nil
 * Bugs          : Nil
 *****************************************************************************/
template <class T>
Matrix<T> Matrix<T>::operator/ (const Matrix<T>& m1)
{
    int i,j;
    if(nrows==m1.nrows && ncols==m1.ncols)
    {
        Matrix<T> temp(nrows,ncols);
        for(i=0;i<nrows;i++)
            for(j=0;j<ncols;j++)
                temp.array[i][j]=array[i][j]/m1.array[i][j];
        return(temp);
    }
    else
    {
        cout << "\nError:Matrix order not equal";
        Matrix<T> temp(0,0);
        return(temp);
    }
}
/******************************************************************************
 * Name          : operator/ - overloading binary arithmetic '/' operator
 * Syntax        : operator/ (T )
 * Description   : To divide all elements of matrix by passed element
 * Arguments     : element
 * Returns       : temp - Matrix object
 * Exceptions    : Nil
 * Bugs          : Nil
 *****************************************************************************/
template <class T>
Matrix<T> Matrix<T>::operator/ (T element)
{
    int i,j;
    Matrix<T> temp(nrows,ncols);
    for(i=0;i<nrows;i++)
        for(j=0;j<ncols;j++)
            temp.array[i][j]=array[i][j]/element;
    return(temp);
}

/******************************************************************************
 * Name          : operator()
 * Syntax        : operator() (int )
 * Description   : Element coresponding to the i th  positon is returned
 * Arguments     : i - positon of element
 * Returns       : element of type T
 * Exceptions    : Nil
 * Bugs          : Nil
 *****************************************************************************/
template <class T>
T& Matrix<T>::operator()(int i)
{
    int cv=i,rv=0;

    while(cv>ncols)
    {
        rv++;
        cv=cv-ncols;
    }
    return(array[rv][cv-1]);


}
/******************************************************************************
 * Name          : operator()
 * Syntax        : operator() (int ,int )
 * Description   : Element corressponding to the row and column position is
                   returned
 * Arguments     : i - row position ,j - column position
 * Returns       : element of type T
 * Exceptions    : Nil
 * Bugs          : Nil
 *****************************************************************************/
template <class T>
T& Matrix<T>::operator()(int i,int j)
{
  return(array[i-1][j-1]);
}

/*size*/
/******************************************************************************
 * Name          : Size - size of matrix
 * Syntax        : size()
 * Description   : To determine the size of matrix i.e number of rows and number                   of columns
 * Arguments     : Nothing
 * Returns       : temp - Matrix object
 * Exceptions    : Nil
 * Bugs          : Nil
 *****************************************************************************/
 template <class T>
 Matrix<int> Matrix<T>::Size()
{
  Matrix<int> temp(1,2);

  temp.operator()(1,1) = nrows;
  temp.operator()(1,2) = ncols;

  return(temp);
}

/*Set the row and columns*/
/******************************************************************************
 * Name          : SetRowCol - intialize rows and columns
 * Syntax        : SetRowCol(int ,int )
 * Description   : To intilaize set of rows and columns of the matrix
 * Arguments     : row - row size,col - column size
 * Returns       : Nothing
 * Exceptions    : Nil
 * Bugs          : Nil
 *****************************************************************************/
template <class T>
void Matrix<T>::SetRowCol (int row ,int col)
{
    int i,j;
    if(array!=NULL)
    {
        for(int i=0;i<nrows;i++)
            delete [] array[i];
        delete [] array;
    }
    nrows=row;
    ncols=col;
    array=new T*[nrows];
    for(i=0;i<nrows;i++)
        array[i]=new T[ncols];
    for(i=0;i<nrows;i++)
        for(j=0;j<ncols;j++)
            array[i][j]=0;
}

/*Get Elements from the user*/
/******************************************************************************
 * Name          : GetElements
 * Syntax        : GetElements()
 * Description   : Gets elements from the user
 * Arguments     : Nothing
 * Returns       : Nothing
 * Exceptions    : Nil
 * Bugs          : Nil
 *****************************************************************************/
template <class T>
void Matrix<T>::GetElements()
{
    int i,j;
    for(i=0;i<nrows;i++)
        for(j=0;j<ncols;j++)
        {
            array[i][j]=(i+1)*(j+1);
        }
}
/******************************************************************************
 * Name          : GetElements
 * Syntax        : GetElements(int ,int)
 * Description   : To get the row size and column size to construct user                           specified matrix and entering the elements
 * Arguments     : row - row size, col - column size
 * Returns       : Nothing
 * Exceptions    : Nil
 * Bugs          : Nil
 *****************************************************************************/
template <class T>
void Matrix<T>::GetElements (int row ,int col)
{
    int i,j,rvalue,cvalue,sr,sc,error;
    cout << "\nEnter the elements :";
    for(i=0;i<row;i++)
        for(j=0;j<col;j++)
            cin >> array[i][j];
}
/*Display*/
/******************************************************************************
 * Name          : Display
 * Syntax        : Display()
 * Description   : To display the elements of matrix
 * Arguments     : Nothing
 * Returns       : Nothing
 * Exceptions    : Nil
 * Bugs          : Nil
 *****************************************************************************/
template <class T>
void Matrix<T>::Display()
{
    int i,j;
    if(IsNull())
    {
        cout<<"Matrix contains Nothing\n";
        return;
    }
    cout << "\nElements of the array : \n";
    cout<<"Rows :"<<nrows<<"\t Cols :"<<ncols<<"\n";
    for(i=1;i<=nrows;i++)
    {
        for(j=1;j<=ncols;j++)
        {
            cout <<"\t"<< this->operator()(i,j)<<"\t";
        }
        cout << "\n ";
    }
    cout <<"\n";
}
/******************************************************************************
Name        - Get
Syntax      - Matrix Get(int, int, int)
Description - This is used to extract the elements from the current Matrix
 object into another Matrix object.
Arguments   - start ->Integer, indicates the starting row/column
              end   ->Integer, indicates the ending row/column
              hvflag->Integer, indicates whether the operation is done on rows
                      or columns
Returns     - Matrix object
Exceptions  - Nil
Bugs        - Nil
******************************************************************************/

template <class T>
Matrix<T> Matrix<T>::Get (int start, int end, int hvflag)
{
    int i,j,sr,sc,error;
    Matrix<T> retObj;
    error=0;
    if(!IsValidHVFlag(hvflag))
    {
        error=1;
        cout<<"hvflag should be either 1 or 2\n";
    }
    if(hvflag==1)
    {
        if(!ValidIndex(start,1,nrows) || !ValidIndex(end,1,nrows))
        {
              error=1;
              cout<<"Row numbers should be positive and less than the Number of rows in the Matrix\n";
        }
        if(start>end)
        {
              error=1;
              cout<<"Starting row should be less than Ending row\n";
        }
        if(error)
        {
            retObj.MakeNull();
            return(retObj);
        }
        retObj.SetRowCol(end-start+1,ncols);
        for(i=0,sr=start;i<(end-start+1);i++,sr++)
            for(j=0;j<ncols;j++)
                retObj.array[i][j]=array[sr-1][j];
        return(retObj);
    }
    else if(hvflag==2)
    {
        if(!ValidIndex(start,1,ncols) || !ValidIndex(end,1,ncols))
        {
            error=1;
            cout<<"Column numbers should be positive and less than No. of columns in the Matrix\n";
        }
        if(start>end)
        {
            error=1;
            cout<<"Starting column should be less than Ending column\n";
        }
        if(error)
        {
            Matrix<T> retObj;
            retObj.MakeNull();
            return(retObj);
        }
        retObj.SetRowCol(nrows,end-start+1);
        for(i=0;i<nrows;i++)
            for(j=0,sc=start;j<(end-start+1);j++,sc++)
                retObj.array[i][j]=array[i][sc-1];
    }
    return(retObj);
}

/******************************************************************************
Name        - Get
Syntax      - Matrix Get(int, int, int, int)
Description - This is used to extract the elements from the current Matrix
 object into another Matrix object.
Arguments   - startrow ->Integer, indicates the starting row
              endrow   ->Integer, indicates the ending row
              startcol ->Integer, indicates the starting column
              endcol   ->Integer, indicates the ending column
Returns     - Matrix object
Exceptions  - Nil
Bugs        - Nil
******************************************************************************/
template <class T>
Matrix<T> Matrix<T>::Get (int startrow, int endrow, int startcol, int endcol)
{
    int i,j,sr,sc,error;
    error=0;
    if(!ValidIndex(startrow,1,nrows) || !ValidIndex(endrow,1,nrows))
    {
        cout<<"Row numbers should be positive and less than the Number of rows in the Matrix\n";
        error=1;
    }
    if(startrow>endrow)
    {
        cout<<"Starting row should be less than Ending row\n";
        error=1;
    }
    if(startcol>endcol)
    {
        cout<<"Starting column should be less than Ending column\n";
        error=1;
    }
    if(!ValidIndex(startcol,1,ncols) || !ValidIndex(endcol,1,ncols))
    {
        cout<<"Column numbers should be positive and less than the Number of Columns in the Matrix\n";
        error=1;
    }
    if(error)
    {
        Matrix<T> retObj;
        retObj.MakeNull();
        return(retObj);
    }
    Matrix<T> retObj(endrow-startrow+1,endcol-startcol+1);
    for(i=0,sr=startrow;i<(endrow-startrow+1);i++,sr++)
        for(j=0,sc=startcol;j<=(endcol-startcol+1);j++,sc++)
            retObj.array[i][j]=array[sr-1][sc-1];
    return(retObj);
}
/******************************************************************************
Name        - Get
Syntax      - T Get(int, int)
Description - This is used to extract one element from the current Matrix
Arguments   - row ->Integer, row of the element
              col ->Integer, column of the element
Returns     - the element of type T (template class type)
Exceptions  - Nil
Bugs        - Nil
******************************************************************************/
template <class T>
T Matrix<T>::Get (int row, int col)
{
  if(!ValidIndex(row,col))
  {
    cout<<"Position should be positive and within order of the Matrix\n";
    return(ERROR_VALUE);
  }
  T retElem=array[row-1][col-1];
  return(retElem);
}
/******************************************************************************
Name        - Get
Syntax      - Matrix Get(Matrix)
Description - This is used to extract the elements from the current Matrix
 object into another Matrix object.
Arguments   - m1 ->Matrix object, contains the indices of the element which are
                   going to be extracted
Returns     - Matrix object, containing the extracted elements
Exceptions  - Nil
Bugs        - Nil
******************************************************************************/
template <class T>
Matrix<T> Matrix<T>::Get(Matrix<T>& m1)
{
    int i;
    if(m1.ncols!=1)
    {
        Matrix<T> retObj;retObj.MakeNull();
        cout<<"Index matrix should be a column vector\n";
        return(retObj);
    }
    if(m1.IsNull())
    {
        cout<<"Argument Matrix contains nothing\n";
        return(m1);
    }
    Matrix<T> retObj(m1.nrows,1);
    for(i=1;i<=m1.nrows;i++)
    {
        if(ValidIndex(m1(i,1)))
            retObj.array[i-1][0]=operator()(m1(i,1));
        else
        {
            Matrix<T> retObj;retObj.MakeNull();
            cout<<"Index matrix contains invalid index\n";
            return(retObj);
        }
    }
    return(retObj);
}
/******************************************************************************
Name        - Set
Syntax      - void Set(int, int, int, Matrix)
Description - This is used to set the elements into the current Matrix
 object from another Matrix object.
Arguments   - start ->Integer, indicates the starting row/column
              end   ->Integer, indicates the ending row/column
              hvflag->Integer, indicates whether the operation is going to be
                      done on rows or columns
              m1    ->Matrix object, containg the elements
Returns     - Nothing
Exceptions  - Nil
Bugs        - Nil
******************************************************************************/
template <class T>
void Matrix<T>::Set (int start, int end, int hvflag, Matrix<T>& m1)
{
    int i,j,sr,sc;
    if(m1.IsNull())
    {
        cout<<"Argument Matrix contains nothing\n";
        return;
    }
    if(IsNull())
    {
        cout<<"Current Matrix contains nothing\n";
        return;
    }
    if(!IsValidHVFlag(hvflag))
    {
        cout<<"hvflag should be either 1 or 2\n";
        return;
    }
    if(hvflag==1)
    {
        if(!ValidIndex(start,1,nrows) || !ValidIndex(end,1,nrows))
        {
            cout<<"Row numbers should be positive and less than the Number of rows in the Matrix\n";
            return;
        }
        if(start>end)
        {
            cout<<"Starting row should be less than Ending row\n";
            return;
        }
        if(ncols!=m1.ncols)
        {
            cout<<"Number of columns in the current matrix and argument matrix should be equal\n";
            return;
        }
        for(i=0,sr=start;i<m1.nrows;i++,sr++)
            for(j=0;j<m1.ncols;j++)
                array[sr-1][j]=m1.array[i][j];
    }
    else if(hvflag==2)
    {
        if(!ValidIndex(start,1,ncols) || !ValidIndex(end,1,ncols))
        {
            cout<<"Column numbers should be positive and less than No. of columns in the Matrix\n";
            return;
        }
        if(start>end)
        {
            cout<<"Starting column should be less than Ending column\n";
            return;
        }
        if(nrows!=m1.nrows)
        {
            cout<<"Number of rows in the current matrix and argument matrix should be equal\n";
            return;
        }
        for(i=0;i<nrows;i++)
        {
            for(j=0,sc=start;j<m1.ncols;j++,sc++)
                array[i][sc-1]=m1.array[i][j];
        }
    }
}
/******************************************************************************
Name        - Set
Syntax      - void Set(int, int, int, int, Matrix)
Description - This is used to set the elements into the current Matrix
 object from another Matrix object.
Arguments   - startrow ->Integer, indicates the starting row
              endrow   ->Integer, indicates the ending row
              startcol ->Integer, indicates the starting column
              endcol   ->Integer, indicates the ending column
              m1       ->Matrix object, containing the elements
Returns     - Nothing
Exceptions  - Nil
Bugs        - Nil
******************************************************************************/
template <class T>
void Matrix<T>::Set(int startrow, int endrow, int startcol, int endcol, Matrix<T>& m1)
{
    int i,j,sr,sc;
    if(m1.IsNull())
    {
        cout<<"Argument Matrix contains nothing\n";
        return;
    }
    if(IsNull())
    {
        cout<<"Current Matrix contains nothing\n";
        return;
    }
    if(!ValidIndex(startrow,1,nrows) || !ValidIndex(endrow,1,nrows))
    {
        cout<<"Row numbers should be positive and less than the Number of rows in the Matrix\n";
        return;
    }
    if(startrow>endrow)
    {
        cout<<"Starting row should be less than Ending row\n";
        return;
    }
    if(startcol>endcol)
    {
        cout<<"Starting column should be less than Ending column\n";
        return;
    }
    if(!ValidIndex(startcol,1,ncols) || !ValidIndex(endcol,1,ncols))
    {
        cout<<"Column numbers should be positive and less than the Number of Columns in the Matrix\n";
        return;
    }
    if(m1.nrows!=(endrow-startrow+1) || m1.ncols!=(endcol-startcol+1))
    {
        cout<<"Argument matrix does not fit into the specified size\n";
        return;
    }
    for(i=0,sr=startrow;i<m1.nrows;i++,sr++)
        for(j=0,sc=startcol;j<m1.ncols;j++,sc++)
            array[sr-1][sc-1]=m1.array[i][j];
}
/******************************************************************************
Name        - Set
Syntax      - void Set(int, int, T)
Description - This is used to set one elements into the current Matrix object
 at a particular position.
Arguments   - row    ->Integer, indicates the row of the element
              col    ->Integer, indicates the column of the element
              element->the element value of type T(template class type)
Returns     - Nothing
Exceptions  - Nil
Bugs        - Nil
******************************************************************************/
template <class T>
void Matrix<T>::Set (int row, int col, T element)
{
    if(!ValidIndex(row,col))
    {
        cout<<"Position should be positive and within order of the Matrix\n";
        return;
    }
    if(IsNull())
    {
        cout<<"Current Matrix contains nothing\n";
        return;
    }
    array[row-1][col-1]=element;
    return;
}
/******************************************************************************
Name        - Set
Syntax      - void Set(Matrix, Matrix)
Description - This is used to set the elements of the Matrix object m1 at the
 indices specified in Matrix object indis.
Arguments   - indis ->Matrix object, containing the indices
              m1    ->Matrix object, containing the elements
Returns     - Nothing
Exceptions  - Nil
Bugs        - Nil
******************************************************************************/
template <class T>
void Matrix<T>::Set (Matrix<T>& indis, Matrix<T>& m1)
{
    int i,j,rvalue,cvalue,sr,sc,error;
    if(IsNull())
    {
        cout<<"Current Matrix contains nothing\n";
        return;
    }
    if(m1.ncols!=1)
    {
        cout<<"Value matrix should be a column vector\n";
        return;
    }
    if(indis.ncols!=1)
    {
        cout<<"Index matrix should be a column vector\n";
        return;
    }
    if(indis.IsNull() || m1.IsNull())
    {
        cout<<"Argument objects should not be NULL\n";
        return;
    }
    if(indis.nrows!=m1.nrows)
    {
        cout<<"The rows of the argument matrices should be same\n";
        return;
    }
    for(i=1;i<=indis.nrows;i++)
    {
        if(ValidIndex(indis(i,1)))
        {
            cvalue=indis(i,1)%ncols;
            rvalue=indis(i,1)/ncols;
            *(*(array+(rvalue-1))+(cvalue-1))=m1(i,1);
        }
        else
        {
            cout<<"Index matrix contains invalid index\n";
            return;
        }
    }
    return;
}

/******************************************************************************
Name        - Insert
Syntax      - void Insert(int, int, Matrix)
Description - This is used to insert the Matrix object m1 into the current
 Matrix object at the specified location.
Arguments   - start ->Integer, indicates the starting row/column
              hvflag->Integer, indicates whether the operation is going to be
                      done on rows or columns
              m1    ->Matrix object, containing the elements
Returns     - Nothing
Exceptions  - Nil
Bugs        - Nil
******************************************************************************/
template <class T>
void Matrix<T>::Insert (int start, int hvflag,Matrix<T>& m1)
{
    int i,j,rvalue,cvalue;
    if(!IsValidHVFlag(hvflag))
    {
        cout<<"hvflag should be either 1 or 2\n";
        return;
    }
    if(m1.IsNull())
    {
        cout<<"Argument matrix should not be NULL\n";
        return;
    }
    if(hvflag==1)
    {
        if(!ValidIndex(start,1,nrows))
        {
            cout<<"Starting row number should be positive and less than the number of rows in the Matrix\n";
            return;
        }
        if(ncols!=m1.ncols)
        {
            cout<<"Number of columns in argument matrix is equal to the number of columns of the current matrix\n";
            return;
        }
        Matrix insObj(nrows+m1.nrows,ncols);
        for(i=0;i<(start-1);i++)
            for(j=0;j<ncols;j++)
                insObj.array[i][j]=array[i][j];
        for(i=0,rvalue=(start-1);i<m1.nrows;i++,rvalue++)
            for(j=0;j<ncols;j++)
                insObj.array[rvalue][j]=m1.array[i][j];
        for(i=(start-1),rvalue=(start-1+m1.nrows);i<nrows;i++,rvalue++)
            for(j=0;j<ncols;j++)
                insObj.array[rvalue][j]=array[i][j];
        this->Copy(insObj);
    }
    else if(hvflag==2)
    {
        if(!ValidIndex(start,1,ncols))
        {
            cout<<"Starting column number should be positive and less than the number of columns in the Matrix\n";
            return;
        }
        if(nrows!=m1.nrows)
        {
            cout<<"Number of columns in argument matrix is equal to the number of columns of the current matrix\n";
            return;
        }
        Matrix insObj(nrows,ncols+m1.ncols);
        for(i=0;i<nrows;i++)
            for(j=0;j<(start-1);j++)
              insObj.array[i][j]=array[i][j];
        for(i=0;i<nrows;i++)
            for(j=0,cvalue=(start-1);j<m1.ncols;j++,cvalue++)
              insObj.array[i][cvalue]=m1.array[i][j];
        for(i=0;i<nrows;i++)
            for(j=(start-1),cvalue=(start-1+m1.ncols);j<ncols;j++,cvalue++)
              insObj.array[i][cvalue]=array[i][j];
        this->Copy(insObj);
    }
    return;
}
/******************************************************************************
Name        - Append
Syntax      - void Insert(Matrix, int)
Description - This is used to append the Matrix object m1 into the current
 Matrix object at the end of the row/column.
Arguments   - hvflag->Integer, indicates whether the operation is going to be
                      done on rows or columns
              m1    ->Matrix object, containing the elements
Returns     - Nothing
Exceptions  - Nil
Bugs        - Nil
******************************************************************************/
template <class T>
void Matrix<T>::Append (Matrix<T>& m1, int hvflag)
{
    int i,j,rvalue,cvalue;
    if(!IsValidHVFlag(hvflag))
    {
        cout<<"hvflag should be either 1 or 2\n";
        return;
    }
    if(m1.IsNull())
    {
        cout<<"Argument Matrix should not be NULL\n";
        return;
    }
    if(nrows==0 || ncols==0 || array==NULL)
    {
        this->Copy(m1);
    }
    if(hvflag==1)
    {
    if(ncols!=m1.ncols)
    {
        cout<<"Number of columns in argument matrix is not equal to the number of columns of the current matrix\n";
        return;
    }
    Matrix insObj(nrows+m1.nrows,ncols);
    for(i=0;i<nrows;i++)
        for(j=0;j<ncols;j++)
            insObj.array[i][j]=array[i][j];
    for(i=0,rvalue=nrows;i<(m1.nrows);i++,rvalue++)
        for(j=0;j<m1.ncols;j++)
            insObj.array[rvalue][j]=m1.array[i][j];
    this->Copy(insObj);
    }
    else if(hvflag==2)
    {
        if(nrows!=m1.nrows)
        {
            cout<<"Number of columns in argument matrix is equal to the number of columns of the current matrix\n";
            return;
        }
        Matrix insObj(nrows,ncols+m1.ncols);
        for(i=0;i<nrows;i++)
            for(j=0;j<ncols;j++)
                insObj.array[i][j]=array[i][j];
        for(i=0;i<nrows;i++)
            for(j=0,cvalue=ncols;j<m1.ncols;j++,cvalue++)
                insObj.array[i][cvalue]=m1.array[i][j];
        this->Copy(insObj);
    }
    return;
}

template <class T>
void Matrix<T>::RowAppend (T a[], int nacols)
{
    int i,j;
    Matrix insObj(nrows+1,ncols);
    if (nacols!=ncols)
    {
        cerr<<"ERROR: In Matrix::RowAppend() no: of cols don't match";
        return;
    }
    for(i=0;i<nrows;i++)
        for(j=0;j<ncols;j++)
        insObj.array[i][j]=array[i][j];
    for(j=0;j<ncols;j++)
        insObj.array[nrows][j]=a[j];
    this->Copy(insObj);
}


/******************************************************************************
Name        - Delete
Syntax      - void Delete(int, int)
Description - This is used to delete a particular row/column in current
 Matrix object.
Arguments   - index    ->Integer, the row/column number
              hvflag   ->Integer, representing whether the operation is going
                         to be made in row/column
Returns     - Nothing
Exceptions  - Nil
Bugs        - Nil
******************************************************************************/
template <class T>
void Matrix<T>::Delete (int index, int hvflag)
{
    int i,j,rvalue,cvalue;
    if(!IsValidHVFlag(hvflag))
    {
        cout<<"hvflag should be either 1 or 2\n";
        return;
    }
    if(hvflag==1)
    {
        if(!ValidIndex(index,1,nrows))
        {
            cout<<"Row number should be positive and less than the number of rows in the Matrix\n";
            return;
        }
        Matrix<T> tmpObj(nrows-1,ncols);
        for(i=0,rvalue=0;i<nrows;i++)
        {
            if(i!=(index-1))
            {
                for(j=0;j<ncols;j++)
                tmpObj.array[rvalue][j]=array[i][j];
                rvalue++;
            }
        }
        this->Copy(tmpObj);
    }
    else if(hvflag==2)
    {
        if(!ValidIndex(index,1,ncols))
        {
            cout<<"Column number should be positive and less than the number of columns in the matrix\n";
            return;
        }
        Matrix<T> tmpObj(nrows,ncols-1);
        for(i=0;i<nrows;i++)
            for(j=0,cvalue=0;j<ncols;j++)
                if(j!=(index-1))
                {
                    tmpObj.array[i][cvalue]=array[i][j];
                    cvalue++;
                }
        this->Copy(tmpObj);
    }
}

/******************************************************************************
Name        - Delete
Syntax      - void Delete(int, int, int)
Description - This is used to delete a set of rows/columns in current
 Matrix object.
Arguments   - start    ->Integer, the starting row/column number
              end      ->Integer, the ending row/column number
              hvflag   ->Integer, representing whether the operation is going
                         to be made in rows/columns
Returns     - Nothing
Exceptions  - Nil
Bugs        - Nil
******************************************************************************/
template <class T>
void Matrix<T>::Delete (int start, int end, int hvflag)
{
    int i,j,rvalue,cvalue;
    if(!IsValidHVFlag(hvflag))
    {
        cout<<"hvflag should be either 1 or 2\n";
        return;
    }
    if(hvflag==1)
    {
        if(!ValidIndex(start,1,nrows) || !ValidIndex(end,1,nrows))
        {
            cout<<"Row numbers should be positive and less than the number of rows in the Matrix\n";
            return;
        }
        Matrix<T> tmpObj((nrows-(end-start+1)),ncols);
        for(i=0;i<(start-1);i++)
        for(j=0;j<ncols;j++)
        tmpObj.array[i][j]=array[i][j];
        for(i=(start-1),rvalue=end;i<(nrows-(end-start+1));i++,rvalue++)
        for(j=0;j<ncols;j++)
        tmpObj.array[i][j]=array[rvalue][j];
        this->Copy(tmpObj);
    }
    else if(hvflag==2)
    {
        if( !ValidIndex(start,1,ncols) || !ValidIndex(end,1,ncols))
        {
            cout<<"Column numbers should be positive and less than the number of columns in the Matrix\n";
            return;
        }
        Matrix<T> tmpObj(nrows,(ncols-(end-start+1)));
        for(i=0;i<nrows;i++)
            for(j=0;j<(start-1);j++)
                tmpObj.array[i][j]=array[i][j];
        for(i=0;i<nrows;i++)
            for(j=(start-1),cvalue=end;j<(ncols-(end-start+1));j++,cvalue++)
                tmpObj.array[i][j]=array[i][cvalue];
        this->Copy(tmpObj);
    }
}

/******************************************************************************
Name        - FindIndex
Syntax      - Matrix FindIndex(T, char)
Description - This is used to find the indices of the elements with respect to
 the element, satisfying the condition.
Arguments   - T     ->the element of type T(template class type)
              char  ->Character,representing the condition
Returns     - Matrix object, containg the indices
Exceptions  - Nil
Bugs        - Nil
******************************************************************************/
template <class T>
Matrix<int> Matrix<T>::FindIndex (T element, char flag)
{
  int i,j;
  if(flag!='<' && flag!='>' && flag!='=')
  {
    Matrix<int> retObj;retObj.MakeNull();
    cout<<"Flag should be either = or < or >\n";
    return(retObj);
  }
  int numeq=0,numgreat=0,numless=0,k=0;
  Matrix<int> retObj;
  for(i=0;i<nrows;i++)
    for(j=0;j<ncols;j++)
      {
        if(array[i][j]==element)
          numeq++;
        else if(array[i][j]>element)
          numgreat++;
        else
          numless++;
      }
  if(flag=='<'){
    retObj.SetRowCol(numless,2);
    for(i=0;i<nrows;i++)
      for(j=0;j<ncols;j++)
        {
        if(array[i][j]<element)
            {
              retObj(k,0)=i+1;
              retObj(k,1)=j+1;
              k++;
            }
        }
  }
  if(flag=='>'){
    retObj.SetRowCol(numgreat,2);
    for(i=0;i<nrows;i++)
      for(j=0;j<ncols;j++)
        {
          if(array[i][j]>element)
            {
              retObj(k,0)=i+1;
              retObj(k,1)=j+1;
              k++;
            }
        }
  }
  if(flag=='='){
    retObj.SetRowCol(numeq,2);
    for(i=0;i<nrows;i++)
      for(j=0;j<ncols;j++)
        {
          if(array[i][j]==element)
            {
              retObj(k,0)=i+1;
              retObj(k,1)=j+1;
              k++;
            }
        }
  }
  return(retObj);
}

/************************************************************************
        Name         : Max
        Prototype    : T Max ()
        Description  : Finds the maximum element present in the matrix class.
                       Done by simple looping
        Arguments    : NIL
        Returns      : The maximum element
        Exceptions   : NIL
        Bugs         : NIL
*************************************************************************/
template <class T>
T Matrix<T>::Max()
{
        T max;

        if (IsNull ())
                return ERROR_VALUE;

        max = array[0][0];

        for (int i = 0; i < nrows; i++)
                for (int j = 0; j < ncols; j++)
                        if (max < array[i][j])
                                max = array[i][j];

        return max;
}

/***************************************************************************
        Name         : Max
        Prototype    : T Max (Matrix m1)
        Description  : Finds the maximum element present in the matrix class.
                       Stores the index (row and column position) of the
                       maximum element in the input argument.
        Arguments    : An object of matrix class
        Returns      : The maximum element
        Exceptions   : The input argument should be initialised before passing it
                       to the function.
        Bugs         : NIL
******************************************************************************/
template <class T>
T Matrix<T>::Max(Matrix& m1)
{
        T max;
        max = array[0][0];

        if (IsNull ())
                return ERROR_VALUE;

        if (m1.IsNull ())
        {
                cout << "\n Cannot Store the index. Input argument is NULL.\n";
                max = Max();
                return max;
        }

        if (m1.ncols < 1 || m1.nrows < 2)
        {
                cout<<"\n Input matrix has lesser dimension ( less than 2 X 1)";                return ERROR_VALUE;
        }

        for (int i = 0; i < nrows; i++)
                for (int j = 0; j < ncols; j++)
                        if (max < array[i][j])
                        {
                                max = array[i][j];
                                m1 (1,1) = i+1;
                                m1 (2,1) = j+1;
                        }

        return max;
}


/*****************************************************************************
        Name         : Max
        Prototype    : T Max (int index, int hvflag)
        Description  : Finds the maximum element present in the matrix class
                       in the particular row or column given by 'index'
        Arguments    : The row/column flag and the row/column number
        Returns      : The maximum element of the row or column
        Exceptions   : NIL
        Bugs         : NIL
******************************************************************************/
template <class T>
T Matrix<T>::Max (int index, int hvflag)
{
        T max;

        if (IsNull ())
                return ERROR_VALUE;

        if ( !(IsValidHVFlag (hvflag)))
                return ERROR_VALUE;

        if (hvflag == 1)
        {
                if (ValidIndex (index, 1, nrows) != 1)
                        return ERROR_VALUE;

                index = index - 1;

                max = array [index][0];

                for ( int i = 0; i < ncols; i++)
                        if (max < array[index][i])
                                max = array[index][i];
        }
        else
        {
                if (ValidIndex (index, 1, ncols) != 1)
                        return ERROR_VALUE;

                index = index - 1;

                max = array [0][index];

                for ( int i = 0; i < nrows; i++)
                        if (max < array[i][index])
                                max = array[i][index];
        }
        return(max);
}


/*****************************************************************************
        Name         : Max
        Prototype    : T Max (int index, int hvflag, Matrix& m1)
        Description  : Finds the maximum element present in the matrix class
                       in the particular row or column given by 'index'
                       Stores the index (row and column position) of the
                       maximum element in the input argument.
        Arguments    : The row/column flag and the row/column number
                       Input matrix to store the index
        Returns      : The maximum element of the row or column
        Exceptions   : The input argument should be initialised before passing it
                       to the function.
        Bugs         : NIL
******************************************************************************/
template <class T>
T Matrix<T>::Max (int index, int hvflag, Matrix& m1)
{
        T max;

        if (IsNull ())
                return ERROR_VALUE;

        if (! (IsValidHVFlag (hvflag)))
        {
                m1.MakeNull();
                return ERROR_VALUE;
        }

        if ( m1.IsNull ())
        {
                cout << "\n Input Matrix is null";
                return ERROR_VALUE;
        }

        if (m1.ncols < 1 || m1.nrows < 2)
        {
                cout<<"\n Input matrix has lesser dimension ( less than 2 X 1)";
                return ERROR_VALUE;
        }

        if (hvflag == 1)
        {
                if (ValidIndex (index, 1, nrows) != 1)
                        return ERROR_VALUE;

                index = index - 1;

                max = array[index][0];

                for ( int i = 0; i < ncols; i++)
                        if (max < array[index][i])
                        {
                                max = array[index][i];
                                m1[1][1] = index + 1;
                                m1[2][1] = i + 1;
                        }
        }
        else
        {
                if (ValidIndex (index, 1, ncols) != 1)
                        return ERROR_VALUE;

                index = index - 1;

                max = array[0][index];

                for ( int i = 0; i < nrows; i++)
                        if (max < array[i][index])
                        {
                                max = array[i][index];
                                m1[1][1] = i + 1;
                                m1[2][1] = index + 1;
                        }
        }
}


/************************************************************************
        Name         : Min
        Prototype    : T Min ()
        Description  : Finds the minimum element present in the matrix class.
                       Done by simple looping
        Arguments    : NIL
        Returns      : The minimum element
        Exceptions   : NIL
        Bugs         : NIL
*************************************************************************/

template <class T>
T Matrix<T>::Min()
{
        T min;

        if (IsNull ())
                return ERROR_VALUE;

        min = array[0][0];

        for (int i = 0; i < nrows; i++)
                for (int j = 0; j < ncols; j++)
                        if (min > array[i][j])
                                min = array[i][j];

        return min;
}

/***************************************************************************
        Name         : Min
        Prototype    : T Min (Matrix m1)
        Description  : Finds the minimum element present in the matrix class.
                       Stores the index (row and column position) of the
                       minimum element in the input argument.
        Arguments    : An object of matrix class
        Returns      : The minimum element
        Exceptions   : The input argument should be initialised before passing it
                       to the function.
        Bugs         : NIL
******************************************************************************/
template <class T>
T Matrix<T>::Min (Matrix& m1)
{
        T min;

        if (IsNull())
        {
                cout<<"\n Current matrix is empty";
                return ERROR_VALUE;
        }

        if (m1.IsNull())
        {
                cout<<"\n Input matrix is empty";
                return ERROR_VALUE;
        }

        if (m1.ncols < 1 || m1.nrows < 2)
        {
                cout<<"\n Input matrix has lesser dimension ( less than 2 X 1)";
                return ERROR_VALUE;
        }

        min = array[0][0];

        for (int i = 0; i < nrows; i++)
                for (int j = 0; j < ncols; j++)
                        if (min > array[i][j])
                        {
                                min = array[i][j];
                                m1 (1,1) = i + 1;
                                m1 (2,1) = j + 1;
                        }

        return min;
}

/*****************************************************************************
        Name         : Min
        Prototype    : T Min (int index, int hvflag)
        Description  : Finds the minimum element present in the matrix class
                       in the particular row or column given by 'index'
        Arguments    : The row/column flag and the row/column number
        Returns      : The minimum element of the row or column
        Exceptions   : The input argument should be initialised before passing it
                       to the function.
        Bugs         : NIL
******************************************************************************/

template <class T>
T Matrix<T>::Min (int index, int hvflag)
{
        T min;

        if (IsNull ())
                return ERROR_VALUE;

        if ( !(IsValidHVFlag (hvflag)))
                return ERROR_VALUE;

        if (hvflag == 1)
        {
                if (ValidIndex (index, 1, nrows) != 1)
                        return ERROR_VALUE;

                index = index - 1;

                min = array [index][0];

                for ( int i = 0; i < ncols; i++)
                        if (min > array[index][i])
                                min = array[index][i];
        }
        else
        {
                if (ValidIndex (index, 1, ncols) != 1)
                        return ERROR_VALUE;

                index = index - 1;

                min = array [0][index];

                for ( int i = 0; i < nrows; i++)
                        if (min > array[i][index])
                                min = array[i][index];
        }
       // cout<<"min="<<min<<endl;
        return(min);
}

/*****************************************************************************
        Name         : Min
        Prototype    : T Min (int index, int hvflag, Matrix& m1)
        Description  : Finds the minimum element present in the matrix class
                       in the particular row or column given by 'index'
                       Stores the index (row and column position) of the
                       minimum element in the input argument.
        Arguments    : The row/column flag and the row/column number
                       Input matrix to store the index
        Returns      : The minimum element of the row or column
        Exceptions   : The input argument should be initialised before passing it
                       to the function.
        Bugs         : NIL
******************************************************************************/

template <class T>
T Matrix<T>::Min (int index, int hvflag, Matrix& m1)
{
        T min;

        if (IsNull ())
                return ERROR_VALUE;

        if (! (IsValidHVFlag (hvflag)))
        {
                MakeNull (m1);
                return ERROR_VALUE;
        }

        if ( m1.IsNull ())
        {
                cout << "\n Input Matrix is null";
                return ERROR_VALUE;
        }

        if (m1.ncols < 1 || m1.nrows < 2)
        {
                cout<<"\n Input matrix has lesser dimension ( less than 2 X 1)";
                return ERROR_VALUE;
        }

        if (hvflag == 1)
        {
                if (ValidIndex (index, 1, nrows) != 1)
                        return ERROR_VALUE;

                index = index - 1;

                min = array[index][0];

                for ( int i = 0; i < ncols; i++)
                        if (min > array[index][i])
                        {
                                min = array[index][i];
                                m1[1][1] = index + 1;
                                m1[2][1] = i + 1;
                        }
        }
        else
        {
                if (ValidIndex (index, 1, ncols) != 1)
                        return ERROR_VALUE;

                index = index - 1;

                min = array[0][index];

                for ( int i = 0; i < nrows; i++)
                        if (min > array[i][index])
                        {
                                min = array[i][index];
                                m1[1][1] = i + 1;
                                m1[2][1] = index + 1;
                        }
        }
}

/******************************************************************************
 * Name          : nMax
 * Syntax        : nMax()
 * Description   : Returns the top n maximum elements in the whole Matrix
                   object.
 * Arguments     : n, number of maximum elements which is required.
 * Returns       : Matrix object which is really a column vector contaning the
                   tot n maximum elements
 * Exceptions    : Nil
 * Bugs          : Nil
 *****************************************************************************/
template <class T>
Matrix<T> Matrix<T>::nMax (int n)
{
  if(!ValidIndex(n))
    {
      cout<<"The argument is greater than the total number of elements in the Matrix object\n";
      Matrix<T> retObj;
      retObj.MakeNull();
      return(retObj);
    }
  Matrix<T> retObj,sortObj;
  sortObj=this.Sort(1);
  retObj=this.Get(1,n,1);
  return(retObj);
}

/******************************************************************************
 * Name          : nMax
 * Syntax        : nMax()
 * Description   : Returns the top n maximum elements in the whole Matrix
                   object.
 * Arguments     : n, number of maximum elements which is required.
                   m1, to contain the indices of top n maximum elements
 * Returns       : Matrix object which is really a column vector contaning the
                   tot n maximum elements
 * Exceptions    : Nil
 * Bugs          : Nil
 *****************************************************************************/
template <class T>
Matrix<T> Matrix<T>::nMax (int n, Matrix& m1)
{
  if(!ValidIndex(n))
    {
      cout<<"The argument is greater than the total number of elements in the Matrix object\n";
      Matrix<T> retObj;retObj.MakeNull();
      return(retObj);
    }
  Matrix<T> retObj,sortObj;
  sortObj=this.Sort(1);
  retObj=this.Get(1,n,1);
  //Setting indexes
  for(int i=0;i<n;i++)
    m1.Append(this.FindIndex(retObj.array[i][0],'='),1);
  return(retObj);
}

/******************************************************************************
 * Name          : nMax
 * Syntax        : nMax()
 * Description   : Returns the top n maximum elements in the specified row or
                   column
 * Arguments     : n, number of maximum elements which is required
                   index, the column/row number
                   hvflag, indicates whether the operation is carried on row/
                           column
 * Returns       : Matrix object which is really a column vector contaning the
                   tot n maximum elements
 * Exceptions    : Nil
 * Bugs          : Nil
 *****************************************************************************/
template <class T>
Matrix<T> Matrix<T>::nMax (int n, int index, int hvflag)
{
  if(!ValidIndex(n,1,ncols))
    {
      cout<<"Vlaue of n is greater than the total number of elements in the Matrix object\n";
      Matrix<T> retObj;retObj.MakeNull();
      return(retObj);
    }
  Matrix<T> retObj,sortObj;
  sortObj=this.Sort(1,index,hvflag);
  retObj=this.Get(1,n,1);
  return(retObj);
}

/******************************************************************************
 * Name          : nMax
 * Syntax        : nMax()
 * Description   : Returns the top n maximum elements in the specified row or
                   column
 * Arguments     : n, number of maximum elements which is required
                   index, the column/row number
                   hvflag, indicates whether the operation is carried on row/
                           column
                   m1, to contain the indices of top n maximum elements
 * Returns       : Matrix object which is really a column vector contaning the
                   tot n maximum elements
 * Exceptions    : Nil
 * Bugs          : Nil
 *****************************************************************************/
template <class T>
Matrix<T> Matrix<T>::nMax (int n, int index, int hvflag, Matrix& m1)
{
  if(!ValidIndex(n,1,ncols))
    {
      cout<<"Vlaue of n is greater than the total number of elements in the Matrix object\n";
      Matrix<T> retObj;retObj.MakeNull();
      return(retObj);
    }
  Matrix<T> retObj,sortObj;
  sortObj=this.Sort(1,index,hvflag);
  retObj=this.Get(1,n,1);
  //Setting indexes
 for(int i=0;i<n;i++)
      m1.Append(this.FindIndex(retObj.array[i][0],'='),1);
  return(retObj);
}

/******************************************************************************
 * Name          : nMin
 * Syntax        : nMin()
 * Description   : Returns the top n minimum elements in the whole Matrix
                   object.
 * Arguments     : n, number of minimum elements which is required.
 * Returns       : Matrix object which is really a column vector contaning the
                   tot n minimum elements
 * Exceptions    : Nil
 * Bugs          : Nil
 *****************************************************************************/
template <class T>
Matrix<T> Matrix<T>::nMin (int n)
{
  if(!ValidIndex(n,1,ncols))
    {
      cout<<"Vlaue of n is greater than the total number of elements in the Matrix object\n";
      Matrix<T> retObj;retObj.MakeNull();
      return(retObj);
    }
  Matrix<T> retObj,sortObj;
  sortObj=this.Sort(2);
  retObj=this.Get(1,n,1);
  return(retObj);
}

/******************************************************************************
 * Name          : nMin
 * Syntax        : nMin()
 * Description   : Returns the top n minimum elements in the whole Matrix
                   object.
 * Arguments     : n, number of minimum elements which is required.
                   m1, to contain the indices of top n minimum elements
 * Returns       : Matrix object which is really a column vector contaning the
                   tot n minimum elements
 * Exceptions    : Nil
 * Bugs          : Nil
 *****************************************************************************/
template <class T>
Matrix<T> Matrix<T>::nMin (int n, Matrix& m1)
{
  if(!ValidIndex(n,1,ncols))
    {
      cout<<"Vlaue of n is greater than the total number of elements in the Matrix object\n";
      Matrix<T> retObj;retObj.MakeNull();
      return(retObj);
    }
  Matrix<T> retObj,sortObj;
  sortObj=this.Sort(2);
  retObj=this.Get(1,n,1);
  //Find Indexes
 for(int i=0;i<n;i++)
      m1.Append(this.FindIndex(retObj.array[i][0],'='),1);
  return(retObj);
}

/******************************************************************************
 * Name          : nMin
 * Syntax        : nMin()
 * Description   : Returns the top n minimum elements in the specified row or
                   column
 * Arguments     : n, number of minimum elements which is required
                   index, the column/row number
                   hvflag, indicates whether the operation is carried on row/
                           column
 * Returns       : Matrix object which is really a column vector contaning the
                   tot n minimum elements
 * Exceptions    : Nil
 * Bugs          : Nil
 *****************************************************************************/
template <class T>
Matrix<T> Matrix<T>::nMin (int n, int index, int hvflag)
{
  if(!ValidIndex(n,1,ncols))
    {
      cout<<"Vlaue of n is greater than the total number of elements in the Matrix object\n";
      Matrix<T> retObj;retObj.MakeNull();
      return(retObj);
    }
  Matrix<T> retObj,sortObj;
  sortObj=this.Sort(2,index,hvflag);
  retObj=this.Get(1,n,1);
  return(retObj);
}

/******************************************************************************
 * Name          : nMin
 * Syntax        : nMin()
 * Description   : Returns the top n minimum elements in the specified row or
                   column
 * Arguments     : n, number of minimum elements which is required
                   index, the column/row number
                   hvflag, indicates whether the operation is carried on row/
                           column
                   m1, to contain the indices of top n minimum elements
 * Returns       : Matrix object which is really a column vector contaning the
                   tot n minimum elements
 * Exceptions    : Nil
 * Bugs          : Nil
 *****************************************************************************/
template <class T>
Matrix<T> Matrix<T>::nMin (int n, int index, int hvflag, Matrix& m1)
{
  if(!ValidIndex(n,1,ncols))
    {
      cout<<"Vlaue of n is greater than the total number of elements in the Matrix object\n";
      Matrix<T> retObj;retObj.MakeNull();
      return(retObj);
    }
  Matrix<T> retObj,sortObj;
  sortObj=this.Sort(2,index,hvflag);
  retObj=this.Get(1,n,1);
  //Find indexes
 for(int i=0;i<n;i++)
      m1.Append(this.FindIndex(retObj.array[i][0],'='),1);
  return(retObj);
}

/******************************************************************************
Name         :sum
prototype    :T sum()
Description  :It finds the sum of all the elements in the matrix
Arguments    :It takes no arguments
Returns      :It returns a variable of template type T
Exceptions   :Nil
Bugs         :NIl
******************************************************************************/
template<class T>
T Matrix<T>:: Sum()
{
 int i,j;
 if(IsNull()==1)
   {
     cout <<"\nNull Error ,Matrix is uninitialised \n";
       return(-1);                                                    /*doubt*/
   }
 T total=0;
 for(i=0;i<nrows;i++)
   for(j=0;j<ncols;j++)
     total+=array[i][j];
 return(total);
}
/******************************************************************************
Name         :sum
prototype    :T sum(int,int)
Description  :It finds the sum of elements of a particular row/column
Arguments    :It takes 1)index which decides the address
                       2)hvflag=1=>rowwise;hvflag=2=>columnwise
Returns      :It returns a variable of template type T
Exceptions   :Nil
Bugs         :Nil
******************************************************************************/
template<class T>
T Matrix<T> :: Sum (int index,int hvflag)
{
  int i;
  if(IsNull()==1)
    {
      cout <<"\nNull Error ,Matrix is uninitialised \n";
      return(-1);                                                 /*doubt*/
    }
  if(IsValidHVFlag(hvflag)!=1)
    {
      cout <<"\nInvalid Error,flagvalue is not valid\n";
      return(-1);                                           /*doubt*/
    }
  T total=0;
  if(hvflag==1)
    {
      if(ValidIndex(index,1,nrows)!=1)
        {
          cout <<"\nInvalid Error,index value is not valid\n";
          return(-1);
        }                             /*rowsise addition*/
      else
        for(i=0;i<ncols;i++)
          total+=array[index-1][i];
    }
  if(hvflag==2)
    {
      if(ValidIndex(index,1,ncols)!=1)
        {
          cout <<"\nInvalid Error,index value is not valid\n";
          return(-1);
        }
      else
        /*columnwise addition*/
        {
          for(i=0;i<nrows;i++)
            total+=array[i][index-1];
        }
    }return(total);
}

/******************************************************************************
Name         :sum
Prototype    :Matrix sum (int)
Description  :It calculates sum of elements of each row/column seperately
Arguments    :It takes the integer  type argument hvflag which decides whether
               the operation is rowwise or columnwise
Returns      :It returns an array of sums of type class Matrix
Exceptions   :Nil
Bugs         :NIl
******************************************************************************/
template<class T>
Matrix<T> Matrix<T> ::Sum(int hvflag)
{
  int i,j;
  Matrix<T> dum(0,0),summat;
    if(IsNull()==1)
    {
      cout <<"\nNull Error ,Matrix is uninitialised \n";
        return(dum);                                              /*doubt*/
    }
  if(IsValidHVFlag(hvflag)!=1)
    {
      cout <<"\nInvalid Error,flagvalue is not valid\n";
      return(dum);                                           /*doubt*/
    }
  if(hvflag==1)
    {
      summat.SetRowCol(nrows,1);
      for(i=0;i<nrows;i++)
        for(j=0;j<ncols;j++)
          summat.array[i][0]+=array[i][j];
    }
  if(hvflag==2)
    {
      summat.SetRowCol(1,ncols);
      for(j=0;j<ncols;j++)
        for(i=0;i<nrows;i++)
          summat.array[0][j]+=array[i][j];
    }
  return summat;
}

/******************************************************************************
Name         :mean
Prototype    :T mean()
Description  :It finds the average of all the elements of the matrix
Arguments    :It takes no arguments
Returns      :It returns a variable of template type T
Exceptions   :Nil
Bugs         :Nil
******************************************************************************/
template<class T>
T Matrix<T> :: Mean()
{
  T size=nrows*ncols;
   if(size == 0)
    {
    cout <<"\nsorry,mean can't be found for matrices of zero size\n";
    return(-1);
    }
  return(Sum()/size);
}

/******************************************************************************
Name         :mean
Prototype    :T mean(int ,int)
Description  :It finds the average of a particular row/column
Arguments    :It takes 2 arguments1)index which decides the address of col/row
                                  2)hvflag=1=>rowwise;hvflag=2=>columnwsie
Returns      :It returns a variable of template type T
Exceptions   :Nil
Bugs         :Nil
******************************************************************************/
template<class T>
T Matrix<T> :: Mean(int index,int hvflag)
{
  if(IsValidHVFlag(hvflag)!=1)
    {
      cout <<"\nInvalid Error,flagvalue is not valid\n";
      return(-1);                                           /*doubt*/
    }
  if(hvflag==1)
    {
      if(ValidIndex(index,1,nrows)!=1)
        {
          cout <<"\nInvalid Error,index value is not valid\n";
          return(-1);
        }
      else
        return(Sum(index,hvflag)/ncols);
    }
  if(hvflag==2)
    {
      if(ValidIndex(index,1,ncols)!=1)
        {
          cout <<"\nInvalid Error,index value is not valid\n";
          return(-1);
        }
      else
        return(Sum(index,hvflag)/nrows);
    }
}

/******************************************************************************
Name         :mean
Prototype    :Matrix mean(int)
Description  :It calculates the mean of each row/column seperately
Arguments    :It takes the integer type argument hvflag which decides whether
              the operation is rowwise or columnwise
Returns      :It returns an array of means of type class Matrix
Exceptions   :Nil
Bugs         :NIl
******************************************************************************/
template<class T>
Matrix<T> Matrix<T> ::Mean(int hvflag)
{
  int i,j;
  Matrix<T> dum(0,0);
  Matrix<T> matr,mean;
  if(IsValidHVFlag(hvflag)!=1)
    {
      cout <<"\nInvalid Error,flagvalue is not valid\n";
      return(dum);                                           /*doubt*/
    }
  if(hvflag==1)
    {
      matr=Sum(hvflag);
      mean.SetRowCol(nrows,1);
      Matrix<T> summat(matr);
      for(i=0;i<nrows;i++)
        mean.array[i][0]=summat.array[i][0]/ncols;
    }
  if(hvflag==2)
    {
      matr=Sum(hvflag);
      mean.SetRowCol(1,ncols);
      Matrix<T> summat(matr);
      for(j=0;j<ncols;j++)
        mean.array[0][j]=summat.array[0][j]/nrows;
    }
  return(mean);
}


/******************************************************************************
Name         :transpose
Prototype    :Matrix Transpose()
Description  :it returns the tranpose ofthe current matrix
Arguments    :no arguments
Returns      :It returns a matrix of class Matrix
Exceptions   :Nil
Bugs         :Nil
******************************************************************************/
template<class T>
Matrix<T> Matrix<T> :: Transpose()
{
 int i,j;
 Matrix<T> trans(ncols,nrows);
 for(i=0;i<nrows;i++)
    for(j=0;j<ncols;j++)
      trans.array[j][i]=array[i][j];
 return(trans);
}

template <class T>
void Matrix<T>::WriteToFile(const char* filename)
{
  int i;
  ofstream outs(filename);
  outs<<nrows<<" "<<ncols<<"\n";//commented by swetha
  for(i=0;i<(nrows-1);i++)
    outs<<array[i][0]<<" "<<array[i][1]<<" ";
  outs<<array[i][0]<<" "<<array[i][1]<<"\n";
  outs.close();
}

/**********Added by swetha for SVM*************************/
template <class T>
void Matrix<T>::WriteStrkCoordsToFile(const char* filename)
{
  int i;
  ofstream outs(filename);
  outs<<nrows<<" "<<ncols - 1<<"\n";//commented by swetha
  for(i=0;i<(nrows-1);i++)
    outs<<array[i][0]<<" "<<array[i][1]<<" ";
  outs<<array[i][0]<<" "<<array[i][1]<<"\n";
  outs.close();
}
/**********Added by swetha for SVM*************************/

template <class T>
void Matrix<T>::WriteToFile(ofstream& ofs)
{
  int i;
  ofs<<nrows<<" ";
  for(i=0;i<(nrows-1);i++)
    ofs<<array[i][0]<<" "<<array[i][1]<<" ";
  ofs<<array[i][0]<<" "<<array[i][1]<<"\n";
}

template<class T>
void Matrix<T>::ReadFromFile(const char* filename)
{
  int i,j;
  ifstream ins(filename);
  ins>>nrows;
  ins>>ncols;
  array=new T*[nrows];
  for(i=0;i<nrows;i++)
    array[i]=new T[ncols];
  for(i=0;i<nrows;i++)
    for(j=0;j<ncols;j++)
      ins>>array[i][j];
  ins.close();
}

template<class T>
void Matrix<T>::ReadFromFile(ifstream& ifs)
{
  int i,j;
  ifs>>nrows;
//cout<<"nrows : "<<nrows<<"\n";
  ncols=2;
  array=new T*[nrows];
  for(i=0;i<nrows;i++)
    array[i]=new T[ncols];
  for(i=0;i<nrows;i++)
    for(j=0;j<ncols;j++)
      ifs>>array[i][j];
}

template <class T>
int Matrix<T>::ValidIndex (int i)
{
  int valid;

  valid = nrows * ncols;
  if (i > 0 && i <= valid)
    return 1;
  else
    return 0;
}

template <class T>
int Matrix<T>::ValidIndex (int i, int j)
{

  if ( i > 0 && j > 0 && i <= nrows && j <= ncols)
    return 1;
  else
    return 0;
}

template <class T>
int Matrix<T>::ValidIndex (int i, int start, int end)
{
  if ( i >= start && i <= end)
    return 1;
  else
    return 0;
}

template <class T>
int Matrix<T>::IsValidHVFlag (int hvflag)
{
  if (hvflag > 0 && hvflag < 3)
    return 1;
  else
    return 0;
}

template <class T>
void Matrix<T>::MakeNull()
{
  if(array!=NULL)
    {
      for(int i=0;i<nrows;i++)
        delete [] array[i];
      delete [] array;
      array = NULL;
      nrows = ncols = 0;
    }
}

template <class T>
int Matrix<T>::IsNull()
{
  if (array == NULL || nrows == 0 || ncols == 0)
    return 1;
  else
    return 0;
}

template <class T>
void Matrix<T>::Copy(const Matrix<T>& m)
{
  int i,j;
  if(array!=NULL)
    {
      for(int i=0;i<nrows;i++)
        delete [] array[i];
      delete [] array;
    }
  nrows=m.nrows;
  ncols=m.ncols;
  array=new T*[nrows];
  for(i=0;i<nrows;i++)
    array[i]=new T[ncols];
  for(i=0;i<nrows;i++)
    for(j=0;j<ncols;j++)
      array[i][j]=m.array[i][j];
  return;
}

template <class T>
void Matrix<T>::CopyTo(Matrix<T>& m)
{
  int i,j;
  if(m.array!=NULL)
    {
      for(int i=0;i<nrows;i++)
        delete [] m.array[i];
      delete [] m.array;
    }
  m.nrows=nrows;
  m.ncols=ncols;
  m.array=new T*[nrows];
  for(i=0;i<nrows;i++)
    m.array[i]=new T[ncols];
  for(i=0;i<nrows;i++)
    for(j=0;j<ncols;j++)
      m.array[i][j]=array[i][j];
}



template<class T>
double Matrix<T>::Norm()
{
  return sqrt((this->operator()(2)*this->operator()(2) + this->operator()(1)*this->operator()(1)));

}

template<class T>
void Matrix<T>::Load (char* fileName)
{
        int nrows, ncols;
        char c;
        string s;

        ifstream fin(fileName);

        if(!fin)
        {
                cout<<"\n Error in opening the file";
                return;
        }

        nrows = 0;
        ncols = 0;

        while (!fin.eof())
        {
                fin.get(c);
                if (c == '\n')
                        break;
                if (c != ' ')
                        ncols++;
        }

        while (!fin.eof())
        {
                getline (fin, s, '\n');
                nrows++;
        }

        fin.close();

        ifstream fin1(fileName);
        if(!fin1)
        {
                cout<<"\n File caanot be opened";
                return;
        }

        Matrix<T> ans(nrows, ncols);

        for (int i=1; i<=nrows; i++)
                for(int j=1; j<=ncols; j++)
                        fin1>>ans(i, j);

        Copy(ans);
        fin1.close();
}


template <class T>
void Matrix<T>::Swap(int index1, int index2, int hvflag)
{
        if(IsValidHVFlag(hvflag)==0)
        {
                cout<<"\n HV Flag is invalid. So exiting";
                return;
        }

        if(hvflag == 1)
        {
                if (ValidIndex (index1, 0, nrows-1) != 1)
                {
                        cout<<"\n Not a valid index "<<index1<<". So exiting";
                        return;
                }

                if (ValidIndex (index2, 0, nrows-1) != 1)
                {
                        cout<<"\n Not a valid index "<<index2<<". So exiting";
                        return;
                }

                Matrix<T> temp(1,ncols);
                {
                int i;
                for (i=1; i<=ncols; i++)
                        temp(1,i) = array[index1-1][i-1];

                for (i=1; i<=ncols; i++)
                        array[index1-1][i-1] = array[index2-1][i-1];

                for (i=1; i<=ncols; i++)
                        array[index2-1][i-1] = temp(1,i);
                }
                return;
        }
        else
        {
                if (ValidIndex (index1, 0, ncols-1) != 1)
                {
                        cout<<"\n Not a valid index "<<index1<<". So exiting";
                        return;
                }

                if (ValidIndex (index2, 0, ncols-1) != 1)
                {
                        cout<<"\n Not a valid index "<<index2<<". So exiting";
                        return;
                }

                Matrix<T> temp(nrows,1);
                {
                int i;
                for (i=1; i<=nrows; i++)
                        temp(i,1) = array[i-1][index1-1];

                for (i=1; i<=nrows; i++)
                        array[i-1][index1-1] = array[i-1][index2-1];

                for (i=1; i<=nrows; i++)
                        array[i-1][index2-1] = temp(i,1);
                }
                return;
        }
}

template <class T>
Matrix<T> Matrix<T>::Sort (int adflag, int index, int hvflag)
{
        Matrix<T> result(nrows, ncols);

        if (IsValidHVFlag(adflag) != 1)
        {
                result.MakeNull();
                return result;
        }

        if (IsValidHVFlag(hvflag) !=1)
        {
                result.MakeNull();
                return result;
        }

        if ( (nrows*ncols) < 1)
        {
                cout << "\n The matrix cannot be sorted";
                result.MakeNull();
                return result;
        }

        if ( (nrows*ncols) == 1)
        {
                this->CopyTo (result);
                return result;
        }

        if (hvflag ==1)
        {
                if (ncols == 1)
                {
                       this->CopyTo (result);
                       return result;
                }
                if ( ValidIndex (index, 1, nrows) != 1)
                {
                        result.MakeNull();
                        return result;
                }

                Matrix<T> temp(nrows,ncols);
                this->CopyTo (temp);
                MSort (result, temp, 1, ncols, index, adflag, hvflag);


        }
        else
        {
                if (nrows == 1)
                {
                       this->CopyTo (result);
                       return result;
                }
                if ( ValidIndex (index, 1, ncols) != 1)
                {
                        result.MakeNull();
                        return result;
                }

                Matrix<T> temp(nrows,ncols);
                this->CopyTo (temp);

                MSort (result, temp, 1, nrows, index, adflag, hvflag);

        }
        return result;

}

template <class T>
void Matrix<T>::MSort (Matrix<T>& result, Matrix<T>& temp, int left, int right, int index, int adflag, int hvflag)
{
        int center;

        if (left < right)
        {
                center = (left + right)/2;
                MSort (result, temp, left, center, index, adflag, hvflag);
                MSort (result, temp, center+1, right, index, adflag, hvflag);
                Merge (result, temp, left, center + 1, right, index, adflag, hvflag);
        }
}

template <class T>
void Matrix<T>::Merge (Matrix<T>& result, Matrix<T>& temp, int lPos, int rPos, int rightEnd, int index, int adflag, int hvflag)
{
        int leftEnd, numElements, tempPos;

        leftEnd = rPos - 1;
        tempPos = lPos;
        numElements = rightEnd - lPos + 1;

        if (hvflag == 2)
        {
                while (lPos <= leftEnd && rPos <= rightEnd)
                {
                        if (adflag == 1) // ascending
                        {
                                if (temp(lPos,index) <= temp(rPos,index))
                                {
                                        Matrix<T> t = temp.Get(lPos, lPos, 1);
                                        result.Set (tempPos, tempPos, 1, t);
                                        tempPos++;
                                        lPos++;
                                }
                                else
                                {
                                        Matrix<T> t = temp.Get(rPos, rPos, 1);
                                        result.Set (tempPos, tempPos, 1, t);
                                        tempPos++;
                                        rPos++;
                                }
                        }
                        else
                        {
                                if (temp(lPos,index) >=temp(rPos,index))
                                {

                                        Matrix<T> t = temp.Get(lPos, lPos, 1);
                                        result.Set (tempPos, tempPos, 1, t);
                                        tempPos++;
                                        lPos++;
                                }
                                else
                                {
                                        Matrix<T> t = temp.Get(rPos, rPos, 1);
                                        result.Set (tempPos, tempPos, 1, t);
                                        tempPos++;
                                        rPos++;
                                }
                        }
                }

                while (lPos <= leftEnd)
                {
                        Matrix<T> t = temp.Get(lPos, lPos, 1);
                        result.Set (tempPos, tempPos, 1, t);
                        tempPos++;
                        lPos++;
                }

                while (rPos <= rightEnd)
                {
                        Matrix<T> t = temp.Get(rPos, rPos, 1);
                        result.Set (tempPos, tempPos, 1, t);
                        tempPos++;
                        rPos++;
                }

                lPos = rightEnd - numElements + 1;

                for (int i = lPos; i <= rightEnd; i++)
                {
                        Matrix<T> t = result.Get(i, i, 1);
                        temp.Set (i, i, 1, t);
                }
        }

        if (hvflag == 1)
        {
                while (lPos <= leftEnd && rPos <= rightEnd)
                {
                        if (adflag == 1) // ascending
                        {
                                if (temp(index,lPos) <= temp(index,rPos))
                                {
                                        Matrix<T> t = temp.Get(lPos, lPos, 2);
                                        result.Set (tempPos, tempPos, 2, t);
                                        tempPos++;
                                        lPos++;
                                }
                                else
                                {
                                        Matrix<T> t = temp.Get(rPos, rPos, 2);
                                        result.Set (tempPos, tempPos, 2, t);
                                        tempPos++;
                                        rPos++;
                                }
                        }
                        else
                        {
                                if (temp(index,lPos) >=temp(index,rPos))
                                {
                                        Matrix<T> t = temp.Get(lPos, lPos, 2);
                                        result.Set (tempPos, tempPos, 2, t);
                                        tempPos++;
                                        lPos++;
                                }
                                else
                                {
                                        Matrix<T> t = temp.Get(rPos, rPos, 2);
                                        result.Set (tempPos, tempPos, 2, t);
                                        tempPos++;
                                        rPos++;
                                }
                        }
                }

                while (lPos <= leftEnd)
                {
                        Matrix<T> t = temp.Get(lPos, lPos, 2);
                        result.Set (tempPos, tempPos, 2, t);
                        tempPos++;
                        lPos++;
                }

                while (rPos <= rightEnd)
                {
                        Matrix<T> t = temp.Get(rPos, rPos, 2);
                        result.Set (tempPos, tempPos, 2, t);
                        tempPos++;
                        rPos++;
                }

                lPos = rightEnd - numElements + 1;

                for (int i = lPos; i <= rightEnd; i++)
                {
                        Matrix<T> t = result.Get(i, i, 2);
                        temp.Set (i, i, 2, t);
                }

        }
}

#endif // MATRIX_H
