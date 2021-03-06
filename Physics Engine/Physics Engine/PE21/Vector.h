#ifndef _VECTOR_H
#define _VECTOR_H

#include <math.h>

template <typename T> class Vector2
    {
    public:
        // Data
        T x, y;

        // Constructors

        Vector2 ():
            x (0),
            y (0)
            { }
        Vector2 (T X, T Y):
            x (X),
            y (Y)
            { }
        Vector2 (double alpha):
            x (cos (alpha)),
            y (sin (alpha))
            { }

        // Getters
        double length () const
            {
            return T (sqrt (this->x * this->x +
                            this->y * this->y));
            }
        
        Vector2 <T> mod () const
            { 
            if (this->length ())
                { 
                double k = 1.0 / this->length ();

                return Vector2 <T> (this->x * k,
                                    this->y * k);
                }

            return Vector2 <T> (0, 0);
            }

        // Operators

        // Plus
        Vector2 <T> operator + (const Vector2 <T> &right) const
            {
            return Vector2 <T> (this->x + right.x,
                                this->y + right.y);
            }
        Vector2 <T> operator + () const
            {
            return *this;
            }
        Vector2 <T> operator += (const Vector2 &right)
            {
            return Vector2 <T> (this->x = this->x + right.x,
                                this->y = this->y + right.y);
            }
        
        // Minus
        Vector2 <T> operator - (const Vector2 <T> &right) const
            {
            return Vector2 <T> (this->x - right.x,
                                this->y - right.y);
            }
        Vector2 <T> operator - () const
            {
            return Vector2 <T> (-this->x, -this->y);
            }
        Vector2 <T> operator -= (const Vector2 <T> &right)
            {
            return Vector2 <T> (this->x = this->x - right.x,
                                this->y = this->y - right.y);
            }

        // Vector multiplication
        T operator ^ (const Vector2 <T> &right) const
            {
            return this->x*right.y - this->y*right.x;
            }
        // Scalar multiplication
        T operator * (const Vector2 <T> &right) const
            {
            return (T)(this->x * right.x + this->y * right.y);
            }
        Vector2 <T> operator * (const T &factor) const
            {
            return Vector2 <T> (this->x*factor, 
                                this->y*factor);
            }
        Vector2 <T> operator *= (const T &factor) 
            {
            return Vector2 <T> (this->x = this->x * factor,
                                this->y = this->y * factor);
            }

        // Scalar division
        Vector2 <T> operator / (const T &factor) const
            {
            if (factor)
                return Vector2 <T> (this->x / factor,
                                    this->y / factor);
            else
                return Vector2 <T> (NAN, NAN);
            }
        Vector2 <T> operator /= (const T &factor) 
            {
            if (factor)
                return Vector2 <T> (this->x = this->x / factor,
                                    this->y = this->y / factor);
            else
                return Vector2 <T> (0, 0);
            }

        // Comparators
        const bool operator == (const Vector2 <T> &right) const
            {
            return ((this->x == right.x) && (this->y == right.y));
            }
        const bool operator != (const Vector2 <T> &right) const
            {
            return !(*this == right);
            }
        const bool operator < (Vector2 <T> &right) const
            {
            return (this->length () < right.length ());
            }
        const bool operator <= (Vector2 <T> &right) const
            {
            return (this->length () <= right.length ());
            }
        const bool operator > (Vector2 <T> &right) const
            {
            return (this->length () > right.length ());
            }
        const bool operator >= (Vector2 <T> &right) const
            {
            return (this->length () >= right.length ());
            }
        
        // Logical operators
        const bool operator ! () const
            {
            return ! ((bool) *this);
            }
        const bool operator && (Vector2 <T> &right) const
            {
            return (((bool) *this) && ((bool)right));
            }
        const bool operator || (Vector2 <T> &right) const
            {
            return (((bool) *this) || ((bool)right));
            }
        
        //operator T () const;

        
        #ifdef SFML_VECTOR2_HPP
        
        sf::Vector2f toSf ()
            {
            return sf::Vector2f (x, y);
            }

        #endif // SFML_VECTOR2_HPP

    };

typedef Vector2 <int> Vectori;
typedef Vector2 <float> Vectorf;
typedef Vector2 <double> Vectord;

#endif // !_VECTOR_H


