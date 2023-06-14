//
// Created by isaac on 6/2/2023.
//

#ifndef CJ2ENGINE_CJ2MATH_H
#define CJ2ENGINE_CJ2MATH_H

#include <cmath>
#include <cassert>
#include <iostream>

namespace cj2math {

    template<int n> struct Vector {
        double data[n] = {0};
        double& operator[](const int i)       { assert(i>=0 && i<n); return data[i]; }
        double  operator[](const int i) const { assert(i>=0 && i<n); return data[i]; }
        double norm2() const { return *this * *this; }
        double norm()  const { return std::sqrt(norm2()); }
    };

    template<int n> double operator*(const Vector<n>& lhs, const Vector<n>& rhs) {
        double ret = 0;
        for (int i=n; i--; ret+=lhs[i]*rhs[i]);
        return ret;
    }

    template<int n> Vector<n> operator+(const Vector<n>& lhs, const Vector<n>& rhs) {
        Vector<n> ret = lhs;
        for (int i=n; i--; ret[i]+=rhs[i]);
        return ret;
    }

    template<int n> Vector<n> operator-(const Vector<n>& lhs, const Vector<n>& rhs) {
        Vector<n> ret = lhs;
        for (int i=n; i--; ret[i]-=rhs[i]);
        return ret;
    }

    template<int n> Vector<n> operator*(const double& rhs, const Vector<n> &lhs) {
        Vector<n> ret = lhs;
        for (int i=n; i--; ret[i]*=rhs);
        return ret;
    }

    template<int n> Vector<n> operator*(const Vector<n>& lhs, const double& rhs) {
        Vector<n> ret = lhs;
        for (int i=n; i--; ret[i]*=rhs);
        return ret;
    }

    template<int n> Vector<n> operator/(const Vector<n>& lhs, const double& rhs) {
        Vector<n> ret = lhs;
        for (int i=n; i--; ret[i]/=rhs);
        return ret;
    }

    template<int n1,int n2> Vector<n1> embed(const Vector<n2> &v, double fill=1) {
        Vector<n1> ret;
        for (int i=n1; i--; ret[i]=(i<n2?v[i]:fill));
        return ret;
    }

    template<int n1,int n2> Vector<n1> proj(const Vector<n2> &v) {
        Vector<n1> ret;
        for (int i=n1; i--; ret[i]=v[i]);
        return ret;
    }

    template<int n> std::ostream& operator<<(std::ostream& out, const Vector<n>& v) {
        for (int i=0; i<n; i++) out << v[i] << " ";
        return out;
    }

    template<> struct Vector<2> {
        double x = 0, y = 0;
        double& operator[](const int i)       { assert(i>=0 && i<2); return i ? y : x; }
        double  operator[](const int i) const { assert(i>=0 && i<2); return i ? y : x; }
        double norm2() const { return *this * *this; }
        double norm()  const { return std::sqrt(norm2()); }
        Vector<2> normalized() { return (*this) / norm(); }
    };

    template<> struct Vector<3> {
        double x = 0, y = 0, z = 0;
        double& operator[](const int i)       { assert(i>=0 && i<3); return i ? (1==i ? y : z) : x; }
        double  operator[](const int i) const { assert(i>=0 && i<3); return i ? (1==i ? y : z) : x; }
        double norm2() const { return *this * *this; }
        double norm()  const { return std::sqrt(norm2()); }
        Vector<3> normalized() { return (*this) / norm(); }
    };

    typedef Vector<2> Vector2D;
    typedef Vector<3> Vector3D;
    typedef Vector<4> Vector4D;
    Vector3D cross(const Vector3D &v1, const Vector3D &v2);

    template<int n> struct dt;

    template<int nrows,int ncols> struct Matrix {
        Vector<ncols> rows[nrows] = {{}};

        Vector<ncols>& operator[] (const int idx)       { assert(idx >= 0 && idx < nrows); return rows[idx]; }
        const Vector<ncols>& operator[] (const int idx) const { assert(idx >= 0 && idx < nrows); return rows[idx]; }

        Vector<nrows> col(const int idx) const {
            assert(idx>=0 && idx<ncols);
            Vector<nrows> ret;
            for (int i=nrows; i--; ret[i]=rows[i][idx]);
            return ret;
        }

        void set_col(const int idx, const Vector<nrows> &v) {
            assert(idx>=0 && idx<ncols);
            for (int i=nrows; i--; rows[i][idx]=v[i]);
        }

        static Matrix<nrows,ncols> identity() {
            Matrix<nrows,ncols> ret;
            for (int i=nrows; i--; )
                for (int j=ncols;j--; ret[i][j]=(i==j));
            return ret;
        }

        double det() const {
            return dt<ncols>::det(*this);
        }

        Matrix<nrows - 1, ncols - 1> get_minor(const int row, const int col) const {
            Matrix<nrows - 1, ncols - 1> ret;
            for (int i=nrows-1; i--; )
                for (int j=ncols-1;j--; ret[i][j]=rows[i<row?i:i+1][j<col?j:j+1]);
            return ret;
        }

        double cofactor(const int row, const int col) const {
            return get_minor(row,col).det()*((row+col)%2 ? -1 : 1);
        }

        Matrix<nrows,ncols> adjugate() const {
            Matrix<nrows,ncols> ret;
            for (int i=nrows; i--; )
                for (int j=ncols; j--; ret[i][j]=cofactor(i,j));
            return ret;
        }

        Matrix<nrows,ncols> invert_transpose() const {
            Matrix<nrows,ncols> ret = adjugate();
            return ret/(ret[0]*rows[0]);
        }

        Matrix<nrows,ncols> invert() const {
            return invert_transpose().transpose();
        }

        Matrix<ncols,nrows> transpose() const {
            Matrix<ncols,nrows> ret;
            for (int i=ncols; i--; ret[i]=this->col(i));
            return ret;
        }
    };

    template<int nrows,int ncols> Vector<nrows> operator*(const Matrix<nrows,ncols>& lhs, const Vector<ncols>& rhs) {
        Vector<nrows> ret;
        for (int i=nrows; i--; ret[i]=lhs[i]*rhs);
        return ret;
    }

    template<int R1,int C1,int C2>Matrix<R1,C2> operator*(const Matrix<R1,C1>& lhs, const Matrix<C1,C2>& rhs) {
        Matrix<R1,C2> result;
        for (int i=R1; i--; )
            for (int j=C2; j--; result[i][j]=lhs[i]*rhs.col(j));
        return result;
    }

    template<int nrows,int ncols>Matrix<nrows,ncols> operator*(const Matrix<nrows,ncols>& lhs, const double& val) {
        Matrix<nrows,ncols> result;
        for (int i=nrows; i--; result[i] = lhs[i]*val);
        return result;
    }

    template<int nrows,int ncols>Matrix<nrows,ncols> operator/(const Matrix<nrows,ncols>& lhs, const double& val) {
        Matrix<nrows,ncols> result;
        for (int i=nrows; i--; result[i] = lhs[i]/val);
        return result;
    }

    template<int nrows,int ncols>Matrix<nrows,ncols> operator+(const Matrix<nrows,ncols>& lhs, const Matrix<nrows,ncols>& rhs) {
        Matrix<nrows,ncols> result;
        for (int i=nrows; i--; )
            for (int j=ncols; j--; result[i][j]=lhs[i][j]+rhs[i][j]);
        return result;
    }

    template<int nrows,int ncols>Matrix<nrows,ncols> operator-(const Matrix<nrows,ncols>& lhs, const Matrix<nrows,ncols>& rhs) {
        Matrix<nrows,ncols> result;
        for (int i=nrows; i--; )
            for (int j=ncols; j--; result[i][j]=lhs[i][j]-rhs[i][j]);
        return result;
    }

    template<int nrows,int ncols> std::ostream& operator<<(std::ostream& out, const Matrix<nrows,ncols>& m) {
        for (int i=0; i<nrows; i++) out << m[i] << std::endl;
        return out;
    }

    template<int n> struct dt {
        static double det(const Matrix<n,n>& src) {
            double ret = 0;
            for (int i=n; i--; ret += src[0][i]*src.cofactor(0,i));
            return ret;
        }
    };

    template<> struct dt<1> {
        static double det(const Matrix<1,1>& src) {
            return src[0][0];
        }
    };
}

#endif //CJ2ENGINE_CJ2MATH_H
