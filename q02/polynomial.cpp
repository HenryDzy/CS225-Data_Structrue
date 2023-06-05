#include <iostream>
#include "polynomial.h"

using namespace std;

// Default constructor
// constructs a first-order polynomial with all coefficients set to 1.
Polynomial::Polynomial(){
    a_ = new float[2];
    a_[0] = 1;
    a_[1] = 1;
}
// One-parameter constructor
// constructs a polynomial of user-supplied order with all coefficients set to 1.
Polynomial::Polynomial(int order){
    a_ = new float[order+1];
    for (int i = 0; i<=order; i++){
        a_[i] = 1;
    }
}
// helper function to copy - IMPLEMENT ME
void Polynomial::copy_(const Polynomial &p) {
    order_ = p.order_;
    for(unsigned int i = 0; i<=order_; i++){
        a_[i] = p.a_[i];
    }

}

// helper function to destroy - IMPLEMENT ME
void Polynomial::destroy_() {
    delete []a_;
    a_ = nullptr;
}

// Copy constructor - must use copy_() function
// constructs a new polynomial that is a copy of an existing polynomial
Polynomial::Polynomial(const Polynomial &p){
    copy_(p);
}
// Destructor - must use destroy_() function
// destroys a polynomial object
Polynomial::~Polynomial(){
    destroy_();
}
// Assignment operator - must use copy_() function
// assigns rhs Polynomial object to 'this' Polynomial object
Polynomial& Polynomial::operator=(const Polynomial& rhs_poly){
    copy_(rhs_poly);
    return *this;
}
// getPolyOrder
// returns the polynomial order
int Polynomial::getPolyOrder(){
    return order_;
}
// getCoeff
// returns the coefficient of the x^i term in polynomial
// note: If the object does not contain a term with power i (e.g., 
//       i>order_), a coefficient value of zero is returned.
float Polynomial::getCoeff(unsigned int i){
    if(i>order_){
        return 0;
    }
    else{
        return a_[i];
    }
}
// setCoeff
// If i <= order_, set a term, value*x^i, in a polynomial
void Polynomial::setCoeff(unsigned int i, float eff){
    if(i<=order_){
        a_[i] = eff;
    }
}
// addition operator
// adds two polynomials together and returns a new polynomial 
Polynomial& Polynomial::operator+(const Polynomial& other_poly){
    
    if(other_poly.order_ >= order_){
        int big_order = other_poly.order_;
        int small_order = order_;
        Polynomial* new_poly = new Polynomial(big_order);
        for(int i = 0; i<=small_order; i++){
            new_poly->a_[i] = a_[i]+other_poly.a_[i];
        }
        for(int u=small_order+1; u<=big_order;u++){
            new_poly->a_[u] = other_poly.a_[u];
        }
        return *new_poly;
    }
    else{
        int small_order = other_poly.order_;
        int big_order = order_;
        Polynomial* new_poly = new Polynomial(big_order);
        for(int i = 0; i<=small_order; i++){
            new_poly->a_[i] = a_[i]+other_poly.a_[i];
        }
        for(int u=small_order+1; u<=big_order;u++){
            new_poly->a_[u] = a_[u];
        }  
        return *new_poly;      
    }
}

// insertion operator for output
// note: This function has been provided for you -- DO NOT CHANGE IT!
ostream & operator << (ostream &out, const Polynomial& p)
{
    bool printed = false;

    for (int i = p.order_; i >= 0; i--)
    {
        float c = p.a_[i];

        if (c != 0.0)
        {
            if (printed) out << " + ";
            printed = true;
            out << c << "*X^" << i;
        }
    }

    return out;
}
