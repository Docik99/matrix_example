#include <iostream>

class matrix_t {
private:
    float ** elements_;
    std::size_t rows_;
    std::size_t collumns_;
public:
    matrix_t();
    matrix_t( matrix_t const & other );
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
