#ifndef MACIERZ_H
#define MACIERZ_H

#include <algorithm>
#include <cstring>
#include <exception>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <random>
#include <cfloat>

/*
        Autor: Mateusz Kojro
        Opis: Klasa implementujaca Matrix dowolnych rozmiarow, obsulgujaca
   nastepujace dzialania: Utworzono: 26.10.2020 Zmiany: 26.10 - podstawowy
   szkielet x implementacja dodawania x odejmowania 28.10 - podstawowa
   implementacjia mnozenia, porownywania x kopiowania 04.11 - poprawiam api
   (@operator()) 05.11 - optymyalizacja 06.11 - dodaje komentarze 08.11 - dodaje
   liste inicjalizacyjna
*/

class Matrix {
public:
  Matrix();
  Matrix(std::initializer_list<std::initializer_list<double>> init);
  Matrix(const Matrix &other);
  Matrix(unsigned size_x, unsigned size_y);
  ~Matrix();

  double At(unsigned x, unsigned y);

  void Set(unsigned x, unsigned y, double value);
  void Print();
  bool FastCompare(const Matrix &other);
  void ApplyFunction(double (*func)(double));

  unsigned SizeX() const;
  unsigned Width() const;
  unsigned W() const;

  unsigned SizeY() const;
  unsigned Height() const;
  unsigned H() const;



  // Uzywam "const Matrix&" W celu unikniecia niepotrzebnych kopii
  Matrix &operator=(const Matrix &other);
  Matrix operator*(const Matrix &other);
  Matrix operator*(double scalar);
  Matrix operator+(const Matrix &other);
  Matrix operator-(const Matrix &other);
  bool operator==(const Matrix &other);
  bool operator!=(const Matrix &other);
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