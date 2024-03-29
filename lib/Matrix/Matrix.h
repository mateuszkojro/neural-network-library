#ifndef MACIERZ_H
#define MACIERZ_H

#include <algorithm>
#include <cfloat>
#include <cstring>
#include <exception>
#include <initializer_list>
#include <iostream>
#include <random>
#include <stdexcept>

/*
        Autor: Mateusz Kojro
        Opis: Klasa implementujaca Matrix dowolnych rozmiarow, obsulgujaca
   nastepujace dzialania: Utworzono: 26.10.2020 Zmiany: 26.10 - podstawowy
   szkielet x implementacja dodawania x odejmowania 28.10 - podstawowa
   implementacjia mnozenia, porownywania x kopiowania 04.11 - poprawiam api
   (@operator()) 05.11 - optymyalizacja 06.11 - dodaje komentarze 08.11 - dodaje
   liste inicjalizacyjna
*/

class Matrix;

using Vector = Matrix;

class Matrix {
public:
  Matrix();
  Matrix(std::initializer_list<std::initializer_list<double>> init);
  Matrix(const Matrix &other);
  Matrix(unsigned size_x, unsigned size_y);
  ~Matrix();

  static Matrix RowsXCols(unsigned int n_rows, unsigned int n_cols);
  static Matrix ColsXRows(unsigned int n_cols, unsigned int n_rows);

  static Vector ColVector(unsigned int size);
  static Vector RowVector(unsigned int size);

  double At(unsigned x, unsigned y) const;

  void Set(unsigned x, unsigned y, double value);
  void Print(const std::string &name="") const;
  Matrix ApplyFunction(double (*func)(double));

  unsigned SizeX() const;
  unsigned Width() const;
  bool FastCompare(const Matrix &other);
  unsigned W() const;
  unsigned Cols() const;

  unsigned SizeY() const;
  unsigned Height() const;
  unsigned H() const;
  unsigned Rows() const;

  Matrix Multiply(const Matrix& other) const;

  // Uzywam "const Matrix&" W celu unikniecia niepotrzebnych kopii
  Matrix &operator=(const Matrix &other);
  Matrix operator*(const Matrix &other) const;
  Matrix operator*(double scalar) const;
  Matrix operator+(const Matrix &other) const;
  Matrix operator-(const Matrix &other) const;
  bool operator==(const Matrix &other) const;
  bool operator!=(const Matrix &other) const;
  double &operator()(unsigned x, unsigned y);
  double &operator()(unsigned n);

  Matrix Transpose() const;

  void RandomFill();

private:
  unsigned Size() const;
  // wskaznik na tablice przechowujaca wartosci macierzy
  double *arr_;
  unsigned size_x_, size_y_;
  unsigned CalcAdress(unsigned x, unsigned y) const;

  class WrongSizeException : public std::exception {
    const char *what() const noexcept override {
      return "Matrices of those dimensions cannot be multiplied";
    }
  } wrong_size_exception_;
};
#endif // !MACIERZ_H