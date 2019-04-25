#ifndef GLUEKITMATH_H
#define GLUEKITMATH_H

#include <QVector>

class Matrix
{
public:
    Matrix();
    Matrix(QVector<float>vect);
    Matrix(QVector<QVector<float>>matr);
    Matrix(int rows, int cols);

    void addRow(QVector<float>row, int index = -1);
    void addCol(QVector<float>col, int index = -1);
    void transp();
    void clear();
    void setMatrix(QVector<QVector<float>> newMatrix);

    int height() const;
    int width() const;

    Matrix operator+(Matrix otherMatrix);
    Matrix operator*(Matrix otherMatrix);
    Matrix operator*(QVector<float> vector);
    Matrix operator*(float value);
    bool operator==(Matrix otherMatrix);
    QVector<float> &operator[](int index);

    static QVector<QVector<float>> fromMatrix(Matrix otherMatrix);
    static float det(Matrix matr);
    static Matrix inverse(Matrix matr);

private:
    int rowNum;
    int colNum;

    void incrRowNum();
    void incrColNum();

    void makeSquared(Matrix &matr);
    void reduceInfVectors(Matrix &matr);
    static Matrix getAlgComp(Matrix matr);

    QVector<QVector<float>> matrix;
};

class GlueKitMath
{
public:
    GlueKitMath();
};

struct ComplexNumber
{
    float real;
    float imag;

    ComplexNumber();
    ComplexNumber(float real, float imag);
    ComplexNumber operator+(ComplexNumber otherNumber);
    ComplexNumber operator*(ComplexNumber otherNumber);
    void operator+=(ComplexNumber otherNumber);
    ComplexNumber operator-(ComplexNumber otherNumber);
    ComplexNumber operator+(float otherNumber);
    ComplexNumber operator-(float otherNumber);
    ComplexNumber operator*(float otherNumber);
    ComplexNumber operator/(float otherNumber);
};

#endif // GLUEKITMATH_H
