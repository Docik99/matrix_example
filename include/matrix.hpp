#include <iostream>

class matrix_t {
private:
    int ** data;
    unsigned int stroki;
    unsigned int stolbi;
public:
    matrix_t();
    matrix_t(int in_stroki,int in_stolbi);
    matrix_t( matrix_t const & object );
    matrix_t & operator =( matrix_t const & other );
    ~matrix_t();
    
    unsigned int rows() const;
    unsigned int collumns() const;
    
    matrix_t operator +( matrix_t const & other ) const;
    matrix_t operator -( matrix_t const & other ) const;
    matrix_t operator *( matrix_t const & other ) const;
    
    matrix_t & operator -=( matrix_t const & other );
    matrix_t & operator +=( matrix_t const & other );
    matrix_t & operator *=( matrix_t const & other );
    
    std::istream & read( std::istream & stream );
    std::ostream & write( std::ostream  & stream ) const;
};
