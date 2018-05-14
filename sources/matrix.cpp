#include "matrix.hpp"
using namespace std;

float ** create_matr (int rows_,int collumns_){
    float ** new_matr = new float * [rows_];
    for (int i = 0; i < rows_; i++){
        new_matr[i] = new float [collumns_];
        for (int j = 0; j < collumns_; j++)
            new_matr[i][j] = 0;
    }
    return new_matr;
}

matrix_t::matrix_t() {
    rows_ = 0;
    collumns_ = 0;
    elements_ = create_matr(rows_, collumns_);
}

matrix_t::matrix_t( matrix_t const & other ) {
    elements_ = create_matr(other.rows_, other.collumns_);
    for (int i = 0; i < other.rows_; i++)
        for (int j = 0; j < other.collumns_; j++)
            elements_[i][j] = other.elements_[i][j];
    rows_ = other.rows_;
    collumns_ = other.collumns_;
}

matrix_t & matrix_t::operator =( matrix_t const & other ) {
    if (this != &other) {
        for (unsigned int i = 0; i < rows_; ++i)
            delete[] elements_[i];
        delete[] elements_;
        rows_ = other.rows_;
        collumns_ = other.collumns_;
        elements_ = create_matr(rows_, collumns_);
        for (int i = 0; i < other.rows_; i++)
            for (int j = 0; j < other.collumns_; j++)
                elements_[i][j] = other.elements_[i][j];
    }
    return *this;
}

matrix_t::~matrix_t() {
    for (unsigned int i = 0; i < rows_; ++i) {
        delete[] elements_[i];
    }
    delete[] elements_;
}

unsigned int matrix_t::rows()  const {
    return rows_;
}

unsigned int matrix_t::collumns() const {
    return collumns_;
}

matrix_t matrix_t::operator +( matrix_t const & other ) const {
    matrix_t result;
    for (unsigned int i = 0; i < rows_; i++)
        for (unsigned int j = 0; j < collumns_; j++)
            result.elements_[i][j] = elements_[i][j] + other.elements_[i][j];
    return result;
}

matrix_t matrix_t::operator -( matrix_t const & other ) const {
    matrix_t result;
    for (unsigned int i = 0; i < rows_; i++)
        for (unsigned int j = 0; j < collumns_; j++)
            result.elements_[i][j] = elements_[i][j] - other.elements_[i][j];
    return result;
}

matrix_t matrix_t::operator *( matrix_t const & other ) const {
    matrix_t result;
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < other.collumns_; j++) {
            result.elements_[i][j] = 0;
            for (int f = 0; f < collumns_; f++)
                result.elements_[i][j] += elements_[i][f] * other.elements_[f][j];
        }
    }
    result.rows_ = rows_;
    result.collumns_ = other.collumns_;
    return result;
}

matrix_t & matrix_t::operator -=( matrix_t const & other ) {
    rows_ = other.rows_;
    collumns_ = other.collumns_;
    for (unsigned int i = 0; i < rows_; i++)
        for (unsigned int j = 0; j < collumns_; j++)
            elements_[i][j] -= other.elements_[i][j];
    return *this;
}

matrix_t & matrix_t::operator +=( matrix_t const & other ) {
    rows_ = other.rows_;
    collumns_ = other.collumns_;
    for (unsigned int i = 0; i < rows_; i++)
        for (unsigned int j = 0; j < collumns_; j++)
            elements_[i][j] += other.elements_[i][j];
    return *this;
}

matrix_t & matrix_t::operator *=( matrix_t const & other ) {
    matrix_t copy(*this);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < other.collumns_; j++) {
            elements_[i][j] = 0;
            for (int f = 0; f < collumns_; f++)
                elements_[i][j] += elements_[i][f] * other.elements_[f][j];
        }
    }
    collumns_ = other.collumns_;
    return *this;
}

istream & matrix_t::read( std::istream & stream ) {
    size_t rows;
    size_t collumns;
    char symbol;

    bool success = true;
    if( stream >> rows && stream >> symbol && symbol == ',' && stream >> collumns ) {
        float ** elements = new float *[ rows ];
        for( std::size_t i = 0; success && i < rows; ++i ) {
            elements[ i ] = new float[ collumns ];
            for( std::size_t j = 0; j < collumns; ++j ) {
                if( !( stream >> elements[ i ][ j ] ) ) {
                    success = false;
                    break;
                }
            }
        }

        if( success ) {
            for( std::size_t i = 0; i < rows_; ++i ) {
                delete [] elements_[ i ];
            }
            delete [] elements_;

            rows_ = rows;
            collumns_ = collumns;
            elements_ = elements;
        }
        else {
            for( std::size_t i = 0; i < rows; ++i ) {
                delete [] elements[ i ];
            }
            delete [] elements;
        }
    }
    else {
        success = false;
    }

    if( !success ) {
        stream.setstate( std::ios_base::failbit );
    }

    return stream;
}

ostream & matrix_t::write( std::ostream & stream ) const {
    stream << rows_ << ", " << collumns_;
    for( std::size_t i = 0; i < rows_; ++i ) {
        stream << '\n';
        for( std::size_t j = 0; j < collumns_; ++j ) {
            stream << elements_[ i ][ j ];
            if( j != rows_ - 1 ) {
                stream << ' ';
            }
        }
    }

    return stream;
}
