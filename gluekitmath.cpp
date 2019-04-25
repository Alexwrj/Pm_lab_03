#include "gluekitmath.h"
#include <limits>
#include <algorithm>
#include <math.h>

GlueKitMath::GlueKitMath()
{
}

Matrix::Matrix()
{
    rowNum = 0;
    colNum = 0;
}

Matrix::Matrix(QVector<float> vect)
{
    QVector<QVector<float>> matr;
    matr.push_back(vect);
    matrix = matr;
    rowNum = 1;
    colNum = vect.size();
}

Matrix::Matrix(QVector<QVector<float>> matr)
{
    this->matrix = matr;
    rowNum = matr.size();
    colNum = matr[0].size();
}

Matrix::Matrix(int rows, int cols)
{
    matrix.resize(rows);

    for (auto &row : matrix)
    {
        row.resize(cols);
    }

    rowNum = rows;
    colNum = cols;
}

void Matrix::addRow(QVector<float> row, int index)
{
    if (row.size() != colNum)
    {
        throw std::invalid_argument("Length of new row not equals to actual matrix width.");
    }

    if (index != -1)
    {
        matrix.insert(matrix.begin() + index, row);
    }
    else
    {
        matrix.push_back(row);
    }

    rowNum++;
}

void Matrix::addCol(QVector<float> col, int index)
{
    if (col.size() != rowNum)
    {
        throw std::invalid_argument("Length of new column not equals to actual matrix height.");
    }

    if (index != -1)
    {
        for (int row = 0; row < matrix.size(); row++)
        {
            matrix[row].insert(matrix[row].begin() + index, col[row]);
        }
    }
    else
    {
        for (int row = 0; row < matrix.size(); row++)
        {
            matrix[row].push_back(col[row]);
        }
    }

    colNum++;
}

void Matrix::transp()
{
    Matrix transpMatrix = Matrix(matrix);
    Matrix tempMatrix = Matrix(matrix);

    bool isChanged = false;

    if (rowNum != colNum)
    {
        makeSquared(transpMatrix);
        makeSquared(tempMatrix);
        isChanged = true;
    }

    for (int row = 0; row < tempMatrix.height(); row++)
    {
        for (int col = 0; col < tempMatrix.width(); col++)
        {
            transpMatrix[row][col] = tempMatrix[col][row];
        }
    }

    if (isChanged)
    {
        reduceInfVectors(transpMatrix);
    }

    std::swap(colNum, rowNum);
    matrix = Matrix::fromMatrix(transpMatrix);
}

void Matrix::clear()
{
    matrix.empty();
}

void Matrix::setMatrix(QVector<QVector<float> > newMatrix)
{
    matrix = newMatrix;
}

float Matrix::det(Matrix matr)
{
    if (matr.height() != matr.width())
    {
        throw std::invalid_argument("Unable to calculate determinant of non-squared matrix.");
    }

    float deter = 0.f;

    if (matr.height() == 2 && matr.width() == 2)
    {
        deter = matr[0][0] * matr[1][1] - matr[0][1] * matr[1][0];
    }
    //zero means that we use only first row to proceed
    else
    {
        for (int j = 0; j < matr.width(); j++)
        {
            QVector<QVector<float>> rMatr;

            for (int row = 0; row < matr.height(); row++)
            {
                QVector<float> newRow;

                for (int col = 0; col < matr.width(); col++)
                {
                    if (row != 0 && col != j)
                    {
                        newRow.push_back(matr[row][col]);
                    }
                }

                if (newRow.size() != 0)
                {
                    rMatr.push_back(newRow);
                }
            }

            deter += static_cast<float>(pow(-1, j)) * matr[0][j] * Matrix::det(Matrix(rMatr));
        }
    }

    return deter;
}

Matrix Matrix::inverse(Matrix matr)
{
    if (matr.height() != matr.width())
    {
        throw std::invalid_argument("Unable to calculate reversed matrix of non-squared matrix.");
    }

    float deter = Matrix::det(matr);

    //if det = 0 return empty matrix. No exception
    if (deter == 0.f)
    {
        return Matrix();
    }

    QVector<QVector<float>> rev;
    if (matr.height() == 2 && matr.width() == 2)
    {
        rev.push_back({matr[1][1], -matr[0][1]});
        rev.push_back({-matr[1][0], matr[0][0]});

        auto inv = Matrix(rev);
        inv = inv * (1.f / Matrix::det(inv));

        return inv;
    }
    else
    {
        Matrix algCompMatr = getAlgComp(matr);
        algCompMatr.transp();
        return algCompMatr * (1.f / deter);
    }
}

int Matrix::height() const
{
    return rowNum;
}

int Matrix::width() const
{
    return colNum;
}

Matrix Matrix::operator+(Matrix otherMatrix)
{
    if (rowNum != otherMatrix.height() || colNum != otherMatrix.width())
    {
        throw std::invalid_argument("Wrong dimensions of add matricies.");
    }

    QVector<QVector<float>> sumMatrix;
    for (int row = 0; row < rowNum; row++)
    {
        QVector<float> sumRow;
        for (int col = 0; col < colNum; col++)
        {
            sumRow.push_back(this->matrix[row][col] + otherMatrix[row][col]);
        }

        sumMatrix.push_back(sumRow);
    }

    return Matrix(sumMatrix);
}

Matrix Matrix::operator*(Matrix otherMatrix)
{
    if (colNum != otherMatrix.height())
    {
        throw std::invalid_argument("Wrong dimensions of multypliyng matricies.");
    }

    QVector<QVector<float>> newVectMatrix;

    for (int row = 0; row < rowNum; row++)
    {
        QVector<float> newRow;
        for (int col = 0; col < otherMatrix.width(); col++)
        {
            float newElement = 0.f;
            for (int i = 0; i < colNum; i++)
            {
                newElement += matrix[row][i] * otherMatrix[i][col];
            }

            newRow.push_back(newElement);
        }

        newVectMatrix.push_back(newRow);
    }

    return Matrix(newVectMatrix);
}

Matrix Matrix::operator*(QVector<float> vector)
{
    auto vec = Matrix(vector);
    vec.transp();

    return Matrix(matrix) * vec;
}

Matrix Matrix::operator*(float value)
{
    QVector<QVector<float>> newMatrix = matrix;

    for (auto &vect : newMatrix)
    {
        for (auto &el : vect)
        {
            el *= value;
        }
    }

    return Matrix(newMatrix);
}

bool Matrix::operator==(Matrix otherMatrix)
{
    return this->matrix == Matrix::fromMatrix(otherMatrix);
}

QVector<QVector<float>> Matrix::fromMatrix(Matrix otherMatrix)
{
    QVector<QVector<float>> out;

    for (int row = 0; row < otherMatrix.height(); row++)
    {
        out.push_back(otherMatrix[row]);
    }

    return out;
}

QVector<float> &Matrix::operator[](int index)
{
    return this->matrix[index];
}

void Matrix::incrRowNum()
{
    rowNum++;
}

void Matrix::incrColNum()
{
    colNum++;
}

void Matrix::makeSquared(Matrix &matr)
{
    float inf = std::numeric_limits<float>::infinity();

    while (matr.width() > matr.height())
    {
        QVector<float> zeroVector(colNum, inf);
        matr.addRow(zeroVector);
    }

    while (matr.height() > matr.width())
    {
        QVector<float> zeroVector(rowNum, inf);
        matr.addCol(zeroVector);
    }
}

void Matrix::reduceInfVectors(Matrix &matr)
{
    auto vectMatr = Matrix::fromMatrix(matr);
    float inf = std::numeric_limits<float>::infinity();

    //reduce inf rows
    for (int i = vectMatr.size() - 1; i >= 0 ; i--)
    {
        if (vectMatr[i][0] == inf)
        {
            vectMatr.erase(vectMatr.begin() + i);
        }
    }

    //reduce inf columns
    for (auto &vect : vectMatr)
    {
        vect.erase(std::remove(vect.begin(), vect.end(), inf), vect.end());
    }

    matr = vectMatr;
}

Matrix Matrix::getAlgComp(Matrix matr)
{
    QVector<QVector<float>> minorMatrix;

    for (int i = 0; i < matr.height(); i++)
    {
        QVector<float> minorRow;

        for (int j = 0; j < matr.width(); j++)
        {
            minorRow.empty();
            QVector<QVector<float>> rMatr;

            for (int row = 0; row < matr.height(); row++)
            {
                QVector<float> newRow;

                for (int col = 0; col < matr.width(); col++)
                {
                    if (row != i && col != j)
                    {
                        newRow.push_back(matr[row][col]);
                    }
                }

                if (newRow.size() != 0)
                {
                    rMatr.push_back(newRow);
                }
            }

            minorRow.push_back(static_cast<float>(pow(-1, i + j)) * det(rMatr));
        }

        minorMatrix.push_back(minorRow);
    }

    return Matrix(minorMatrix);
}


ComplexNumber::ComplexNumber()
{
    real = 0.f;
    imag = 0.f;
}

ComplexNumber::ComplexNumber(float real, float imag)
{
    this->real = real;
    this->imag = imag;
}

ComplexNumber ComplexNumber::operator+(ComplexNumber otherNumber)
{
    return ComplexNumber(this->real + otherNumber.real, this->imag + otherNumber.imag);
}

ComplexNumber ComplexNumber::operator*(ComplexNumber otherNumber)
{
    return ComplexNumber(this->real * otherNumber.real - this->imag * otherNumber.imag,
                         this->real * otherNumber.imag + this->imag * otherNumber.real);
}

void ComplexNumber::operator+=(ComplexNumber otherNumber)
{
    this->real += otherNumber.real;
    this->imag += otherNumber.imag;
}

ComplexNumber ComplexNumber::operator-(ComplexNumber otherNumber)
{
    return ComplexNumber(this->real - otherNumber.real, this->imag - otherNumber.imag);
}

ComplexNumber ComplexNumber::operator+(float otherNumber)
{
    return ComplexNumber(this->real + otherNumber, this->imag);
}

ComplexNumber ComplexNumber::operator-(float otherNumber)
{
    return ComplexNumber(this->real - otherNumber, this->imag);
}

ComplexNumber ComplexNumber::operator*(float otherNumber)
{
    return ComplexNumber(this->real * otherNumber, this->imag * otherNumber);
}

ComplexNumber ComplexNumber::operator/(float otherNumber)
{
    return ComplexNumber(this->real / otherNumber, this->imag / otherNumber);
}
