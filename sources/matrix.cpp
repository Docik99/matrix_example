#include <iostream>
#include "matrix.hpp"
using namespace std;

int ** Create_Matrix(int stroki,int stolbi){
    int **New_Matrix = new int *[stroki];
    for (int i=0;i<stroki;i++){
        New_Matrix[i]=new int [stolbi];
    }
    return New_Matrix;
}
matrix_t::matrix_t()
{
    stroki=0;
    stolbi=0;
    data = Create_Matrix(stroki, stolbi);
}
matrix_t::matrix_t(int in_stroki,int in_stolbi){
    stroki=in_stroki;
    stolbi=in_stolbi;
    data = Create_Matrix(stroki, stolbi);
}

matrix_t::matrix_t( matrix_t const & object )
{
    stroki=object.stroki;
    stolbi=object.stolbi;
    data=Create_Matrix(stroki, stolbi);
    for ( int i = 0; i < stroki; ++i){
        for ( int j = 0; j < stolbi; ++j){
            data[i][j] = object.data[i][j];
        }
    }
}

matrix_t & matrix_t::operator =( matrix_t const & other )
{
    if (&other == this) return *this;
    for (int i=0; i<stroki; i++){ //Сначала освобождаем память ,потом узнаем размер ,потом выделяем память.
        delete[] data[i];
    }
    delete[] data;
    stroki=other.stroki;
    stolbi=other.stolbi;
    this->data = Create_Matrix(stroki, stolbi);
    for ( int i = 0; i < stroki; ++i){
        for ( int j = 0; j < stolbi; ++j){
            data [i][j] = other.data[i][j];
        }
    }
    //        cout<<"operator ="<<'\n';
    return *this;
}

matrix_t::~matrix_t()
{
    for (int i=0; i<stroki; i++){
        delete[] data[i];
    }
    delete[] data;
    cout<<'\n';
    
}

unsigned int matrix_t::rows() const
{
    return stroki;
}

    unsigned int matrix_t::collumns() const
{
    return stolbi;
}

matrix_t matrix_t::operator +( matrix_t const & other ) const
{
    matrix_t result(stroki,stolbi);
    for (int i = 0; i< stroki; i++) {
        for (int j = 0 ; j< stolbi; j++) {
            result.data[i][j]=data[i][j]+other.data [i][j];
        }
    }
    return result;
}

matrix_t matrix_t::operator -( matrix_t const & other ) const
{
    matrix_t result(stroki,stolbi);
    for (int i = 0; i< stroki; i++) {
        for (int j = 0 ; j< stolbi; j++) {
            result.data[i][j]=data[i][j]-other.data [i][j];
        }
    }
    return result;
}

matrix_t matrix_t::operator *( matrix_t const & other ) const
{
    matrix_t result(stroki,other.stolbi);
    for (int i = 0; i<stroki; i++) {
        for (int j = 0; j<other.stolbi; j++) {
            result.data[i][j] = 0;
            for (int h = 0; h<stolbi; h++) {
                result.data[i][j] += data[i][h]*other.data[h][j];
            }
        }
    }
    return result;
}

matrix_t & matrix_t::operator -=( matrix_t const & other )
{
    stroki=other.stroki;
    stolbi=other.stolbi;
    for (int i = 0; i< stroki; i++) {
        for (int j = 0 ; j< stolbi; j++) {
            data[i][j]=data[i][j]-other.data [i][j];
        }
    }
    return *this;
}

matrix_t & matrix_t::operator +=( matrix_t const & other )
{
    stroki=other.stroki;
    stolbi=other.stolbi;
    for (int i = 0; i< stroki; i++) {
        for (int j = 0 ; j< stolbi; j++) {
            data[i][j]=data[i][j]+other.data [i][j];
        }
    }
    return *this;
}

matrix_t & matrix_t::operator *=( matrix_t const & other )
{
    matrix_t copy(*this);
    matrix_t copy2(other);
    for (int i = 0; i<stroki; i++) {
        for (int j = 0; j<other.stolbi; j++) {
            data[i][j] = 0;
            for (int h = 0; h<stolbi; h++) {
                data[i][j] += copy.data[i][h]*copy2.data[h][j];
            }
        }
    }
    this->stolbi = other.stolbi;
    return *this;
}
istream & matrix_t::read( istream & stream )
{
    unsigned int stroki2 ;
    unsigned int stolbi2 ;
    char symbol ;
    
    bool success = true;
    if( stream >> stroki2 && stream >> symbol && symbol == ',' && stream >> stolbi2 ) {
        int ** elements = new int *[ stroki2 ];
        for( unsigned int i = 0; success && i < stroki2; ++i ) {
            elements[ i ] = new int [ stolbi2 ];
            for( unsigned int j = 0; j < stolbi2; ++j ) {
                if( !( stream >> elements[ i ][ j ] ) ) {
                    success = false;
                    break;
                }
            }
        }
        
        if( success ) {
            for( unsigned int i = 0; i < stroki; ++i ) {
                delete [] data[ i ];
            }
            delete [] data;
            
            stroki = stroki2;
            stolbi = stolbi2;
            data = elements;
        }
        else {
            for( unsigned int i = 0; i < stroki2 ; ++i ) {
                delete [] elements[ i ];
            }
            delete [] elements;
        }
    }
    else {
        success = false;
    }
    
    if( !success ) {
        stream.setstate( ios_base::failbit );
        //            cout<<"ERROR"<<'\n';
    }
    return stream;
}

ostream & matrix_t::write( ostream & stream ) const
{
    
    stream << stroki << ", " << stolbi;
    for( unsigned int i = 0; i < stroki; ++i ) {
        stream <<'\n';
        for( unsigned int j = 0; j < stolbi; ++j ) {
            stream << data[ i ][ j ];
            if( j != stroki - 1 ) {
                stream <<' ';
            }
        }
    }
    
    return stream;
}
