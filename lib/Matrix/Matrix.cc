#include "Matrix.h"
#include <cassert>

Matrix::Matrix() {
  size_x_ = 0;
  size_y_ = 0;

  arr_ = nullptr;
  // uzycie takiego sposobu pomaga zaoszczedzic alokacji
  // wymaganych do utworzenia wskaznika na tablice dwuwymiarowa
  // poprawia uklad danych W pamieci dodatkowo pozwala porownywac x kopiowac
  // tabele o wiele szybciej
  // arr_ = new double[size_x_ * size_y_];
}

Matrix::Matrix(std::initializer_list<std::initializer_list<double>> init_list) {

  // std::initializer_list to obiekt zdefiniowany W STL sluzacy do implementacji
  // list inicjalizacyjnych przechowuje iterator po kolejnych elementach W
  // zwiazku z tym zeby stworzyc Matrix potrzebujemy zagniezdzonych list po
  // jednej dla kazdego wiersza

  // ustalamy rozmiary na podstawie odpowiednich list
  size_y_ = init_list.size();
  size_x_ = init_list.begin()->size();

  // sprawdzamy czy kazdy wiersz ma ta sama dlugosc jak nie wyrzucamy wyjatek
  for (auto i : init_list) {
    if (i.size() != size_x_) {
      throw std::out_of_range("Initializer list need to be the same lenght");
    }
  }

  // alokuje pamiec na podstawie rozmiarow
  arr_ = new double[init_list.size() * init_list.begin()->size()];

  // wypelniam ja elementami list inicjalizacyjncyh
  unsigned i = 0;
  for (auto outer : init_list) {
    for (double inside : outer) {
      // linter pokazuje ostrzerzenie o mozliwym wyjsciu poza zakres tablicy ale
      // chyba nie powinno sie nigdy zdarzyc
      arr_[i++] = inside;
    }
  }
}

// From: https://www.geeksforgeeks.org/c-program-multiply-two-matrices/
// ***
Matrix Matrix::Multiply(const Matrix &other) const {
  unsigned m1 = this->SizeY();
  unsigned m2 = this->SizeX();
  unsigned n1 = other.SizeY();
  unsigned n2 = other.SizeX();

  unsigned x, i, j;
  Matrix result = RowsXCols(m1, n2);
  for (i = 0; i < m1; i++) {
    for (j = 0; j < n2; j++) {
      result(i, j) = 0;
      for (x = 0; x < m2; x++) {
        result(j, i) += this->At(x, i) * other.At(j, x);
      }
    }
  }
  return result;
}

Matrix::Matrix(const Matrix &other) {
  this->size_x_ = other.size_x_;
  this->size_y_ = other.size_y_;
  arr_ = new double[Size()];
  memcpy(arr_, other.arr_, sizeof(double) * size_x_ * size_y_);
}

Matrix::Matrix(unsigned size_x, unsigned size_y) {
  size_x_ = size_x;
  size_y_ = size_y;
  arr_ = new double[size_x_ * size_y_];
  memset(arr_, 0, sizeof(double) * size_x * size_y);
}

unsigned Matrix::CalcAdress(unsigned x, unsigned y) const {
  // Konwertuje adres W postaci x,y na element tablicy 1 wymiarowej
  //  assert(x < this->size_x_);
  //  assert(y < this->size_y_);
  unsigned addr = y * this->size_x_ + x;
  //  assert(addr < size_x_ * size_y_);
  return addr;
}

void Matrix::Set(unsigned x, unsigned y, double value) {
#ifdef CHECK_BOUNDS
  if (x >= size_x_ || y >= size_y_)
    throw std::out_of_range("You are trying to acces element out of bounds");
#endif// CHECK_BOUNDS
  arr_[CalcAdress(x, y)] = value;
}

double Matrix::At(unsigned x, unsigned y) const {
// Jako ze sprawdzanie czy adres nie wychodzi poza zakresy tabel zuzywa duzo
// zasobow (akumulje sie wiele wywolan tej funckji po 2 porownaniach W kazdym)
// ustawiamy je jako dodatkowa func domyslnie wylaczana
#ifdef CHECK_BOUNDS
  if (x >= size_x_ || y >= size_y_)
    throw std::out_of_range("You are trying to acces element out of bounds");
#endif// CHECK_BOUNDS
  return arr_[CalcAdress(x, y)];
}

void Matrix::Print(const std::string &name) const {
  auto old = std::cout.precision(3);
  std::clog << name << "\nDims: (x: " << this->size_x_ << " @ "
            << "y:" << this->size_y_ << ")" << std::endl;
  for (unsigned y = 0; y < size_y_; y++) {
    for (unsigned x = 0; x < size_x_; x++) {
      std::clog << this->At(x, y) << "\t";
    }
    std::clog << "\n";
  }

  std::clog << "\n";
  std::cout.precision(old);
}

bool Matrix::FastCompare(const Matrix &other) {

  // memcmp - to funkcja W standardzie C porownujaca dwa bloki pamieci zwraca 0
  // (int) jezeli sa takie same lub pierwszy bajt ktorym sie roznia (>0 jezeli
  // wiekszy W pierwszym bloku) W zwiazku z tym nasz wynik explicitly rzucamy na
  // bool x odwracamy jego wartosc (0(bool) == false)
  return !(bool) memcmp(other.arr_, this->arr_,
                        sizeof(double) * size_x_ * size_y_);
}

bool Matrix::operator==(const Matrix &other) const {

  // jezeli maja ten sam adres tzn ze sa tym samym obiektem - moge zwrocic
  // wczesniej
  if (this == &other) {
    return true;
  }

  // jezeli rozmiary nie sa takie same to nie beda rowne - moge zwrocic
  // wczesniej
  if (other.size_x_ != this->size_x_) {
    return false;
  }
  if (other.size_y_ != this->size_y_) {
    return false;
  }

  // jezeli ktorykolwiek element nie jest rowny nie sa rowne
  for (unsigned i = 0; i < size_x_ * size_y_; i++) {
    if (this->arr_[i] != other.arr_[i]) {
      return false;
    }
  }
  return true;
}

// analoginczie jak W operatorze == tylko wartosci sa zanegowane
bool Matrix::operator!=(const Matrix &other) const {

  if (this == &other) {
    return false;
  }

  if (other.SizeX() != this->SizeX()) {
    return true;
  }

  if (other.SizeY() != this->SizeY()) {
    return true;
  }

  for (unsigned i = 0; i < Size(); i++) {
    if (this->arr_[i] != other.arr_[i]) return true;
  }
  return true;
}

Matrix &Matrix::operator=(const Matrix &other) {
  // Sprawdzamy czy nie probujemy przypisac macierzy samej do siebie
  if (&other == this) {
    return *this;
  }
  size_x_ = other.size_x_;
  size_y_ = other.size_y_;

  this->arr_ = new double[Size()];
  // memcpy - funkcja W standardzie C sluzaca do kopiowania bloku pamieci
  //(jej implementacja ma zlozonosc znaczaco lepsza niz O(n) jaka osiagneli
  // bysmy kopiujac element po elemencie)
  memcpy(arr_, other.arr_, sizeof(double) * size_x_ * size_y_);
  return *this;
}

#define CHECK_DIMENTIONS

Matrix Matrix::operator*(const Matrix &other) const {
  // Sytuacja jak W przpadku sprawdzania zakresow tablicy

// TODO: i dont know if that is correct
#ifdef CHECK_DIMENTIONS
  if (this->size_x_ != other.size_y_) {
    throw wrong_size_exception_;
  }   // throw custom exception if wrong sizes
#endif// CHECK_DIMENTIONS
  return this->Multiply(other);
}

Matrix Matrix::operator+(const Matrix &other) const {
#ifdef CHECK_DIMENTIONS
  if (this->size_x_ != other.size_x_
      || this->size_y_ != other.size_y_) {
    throw wrong_size_exception_;
  }   // throw custom exception if wrong sizes
#endif// CHECK_DIMENTIONS
  Matrix result(size_x_, size_y_);
  for (unsigned i = 0; i < Size(); i++) {
    result.arr_[i] = this->arr_[i] + other.arr_[i];
  }
  return result;
}

Matrix Matrix::operator-(const Matrix &other) const {

#ifdef CHECK_DIMENTIONS
  if (this->SizeX() != other.SizeX()) {
    throw wrong_size_exception_;
  }
  if (this->SizeY() != other.SizeY()) {
    throw wrong_size_exception_;
  }   // throw custom exception if wrong sizes
#endif// CHECK_DIMENTIONS
  Matrix result(SizeX(), SizeY());
  for (unsigned i = 0; i < Size(); i++) {
    result.arr_[i] = this->arr_[i] - other.arr_[i];
  }
  return result;
}

double &Matrix::operator()(unsigned x, unsigned y) {
#ifdef CHECK_BOUNDS
  if (x >= size_x_ || y >= size_y_) {
    throw std::out_of_range("You are trying to acces element out of bounds");
  }
#endif// CHECK_BOUNDS
  return arr_[CalcAdress(x, y)];
}

// Aplikuje func na Matrix
// np.
// A.ApplyFunction([](double x) { return x * 2; });
//  Pomnozy kazdy element A przez 2
Matrix Matrix::ApplyFunction(double (*func)(double)) {
  Matrix result(*this);
  for (unsigned i = 0; i < Size(); i++) {
    result(i) = func(this->operator()(i));
  }
  return result;
}

Matrix::~Matrix() {
  delete[] arr_;
  arr_ = nullptr;
}

unsigned Matrix::SizeX() const { return size_x_; }
unsigned Matrix::SizeY() const { return size_y_; }
unsigned Matrix::Width() const { return SizeX(); }
unsigned Matrix::W() const { return SizeX(); }
unsigned Matrix::Height() const { return SizeY(); }
unsigned Matrix::H() const { return SizeY(); }
unsigned Matrix::Size() const { return SizeX() * SizeY(); }

Matrix Matrix::operator*(double scalar) const {
  Matrix result = *this;
  for (int i = 0; i < Size(); i++) {
    result(i) *= scalar;
  }

  return result;
}


/**
 * @brief      Accces elements of the matrix linearly (organised row by row)
 *
 * @param[in]  n     0 indexed element of the matrix
 *
 * @return     Reference tp n-th element
 */
double &Matrix::operator()(unsigned int n) {
#ifdef CHECK_BOUNDS
  if (n >= Size())
    throw std::out_of_range("You are trying to acces element out of bounds");
#endif// CHECK_BOUNDS
  assert(n < Size());
  return arr_[n];
}

/// Transpose matrix and return the result
///  \note Takes almost no time to do so needs to be analyzed more carefully
Matrix Matrix::Transpose() const {
  // TODO: this will be very slow if many operations are made on the transposed
  Matrix transpose = *this;

  transpose.size_x_ = this->SizeY();
  transpose.size_y_ = this->SizeX();

  for (int i = 0; i < Rows(); ++i)
    for (int j = 0; j < Cols(); ++j) {
      transpose(j, i) = this->At(i, j);
    }

  return transpose;
}

// TODO: You should be able to give the seed
void Matrix::RandomFill() {
  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution(0.0, 1.0);

  for (int i = 0; i < Size(); ++i) {
    this->operator()(i) = distribution(generator);
  }
}
unsigned Matrix::Cols() const { return Width(); }
unsigned Matrix::Rows() const { return Height(); }

Matrix Matrix::RowsXCols(unsigned int n_rows, unsigned int n_cols) {
  return {n_cols, n_rows};
}

Matrix Matrix::ColsXRows(unsigned int n_cols, unsigned int n_rows) {
  return {n_rows, n_cols};
}

Vector Matrix::ColVector(unsigned int size) {
  return {1, size};
}

/**
 * @brief      Create row vector ([[x,x,x]])
 *
 * @param[in]  size  Size of the vector
 *
 * @return     Matrix of dimesntions size, 1
 */
Vector Matrix::RowVector(unsigned int size) {
  return {size, 1};
}
