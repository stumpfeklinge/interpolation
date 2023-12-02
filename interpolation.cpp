#include <iostream>
#include <fstream>
#include <math.h>
#include <complex>
#include <locale>
#include <cmath>
#include "GnuP.h"
1
using namespace std;
int SLAU(float** matrica_a, int n, float* massiv_b, float* x)
{
int i, j, k, r;
float c, M, s;
float max;
float** a, * b;
a = new float* [n];
for (i = 0; i < n; i++)
a[i] = new float[n];
b = new float[n];
for (i = 0; i < n; i++)
for (j = 0; j < n; j++)
a[i][j] = matrica_a[i][j];
for (i = 0; i < n; i++)
b[i] = massiv_b[i];
for (k = 0; k < n; k++)
{
max = abs(a[k][k]);
r = k;
for (i = k + 1; i < n; i++)
if (abs(a[i][k]) > max)
{
max = abs(a[i][k]);
r = i;
}
for (j = 0; j < n; j++)
{
c = a[k][j];
a[k][j] = a[r][j];
a[r][j] = c;
}
c = b[k];
b[k] = b[r];
b[r] = c;
for (i = k + 1; i < n; i++)
{
2
for (M = a[i][k] / a[k][k], j = k; j < n; j++)
a[i][j] -= M * a[k][j];
b[i] -= M * b[k];
}
}
if (abs(a[n - 1][n - 1]) == 0)
if (abs(b[n - 1]) == 0)
return -1;
else return -2;
else
{
for (i = n - 1; i >= 0; i--)
{
for (s = 0, j = i + 1; j < n; j++)
s += a[i][j] * x[j];
x[i] = (b[i] - s) / a[i][i];
}
return 0;
}
for (i = 0; i < n; i++)
delete[] a[i];
delete[] a;
delete[] b;
}
float kanon(float x, float* A)
{
return A[0] + A[1] * x + A[2] * x * x + A[3] * x * x * x + A[4] * x * x * x * x +}
float net(float x, int ny, float* X, float* Y) {
float* A;
A = new float[ny];
for (int i = 0; i < ny; i++)
A[i] = Y[i];
for (int j = 1; j < ny; j++)
{
3
for (int i = ny - 1; i > j - 1; i--)
{
A[i] = (A[i] - A[i - 1]) / (X[i] - X[i - j]);
}
}
float b;
b = A[ny - 1];
for (int i = ny - 2; i >= 0; i--)
{
b = A[i] + (x - X[i]) * b;
}
return b;
}
float lagranj(float x, int ny, float* X, float* Y) {
float sum = 0;
for (int i = 0; i < ny; ++i) {
float l = 1;
for (int j = 0; j < ny; ++j)
if (j != i)
l *= (x - X[j]) / (X[i] - X[j]);
sum += Y[i] * l;
}
return sum;
}
float LI(float x, float* X, float* Y, int ny)
{
float x0, x1, y0, y1;
for (int i = 0; i < ny - 1; i++) {
if (x >= X[i] && x <= X[i + 1]) {
x0 = X[i];
x1 = X[i + 1];
y0 = Y[i];
y1 = Y[i + 1];
4
break;
}
}
if (x0 == x1)
{
cout << "Ошибка: x0 и x1 равны, невозможно выполнить интерполяцию!" << endl;
return 0;
}
float y = y0 + (x - x0) * (y1 - y0) / (x1 - x0);
return y;
}
float cub(float* X, float* Y, int n, float point) {
float* a = new float[n];
float* b = new float[n];
float* c = new float[n];
float* d = new float[n];
float* h = new float[n - 1];
float* alpha = new float[n];
float* l = new float[n];
float* u = new float[n];
float* z = new float[n];
// Расчет разностей узловых точек
for (int i = 0; i < n - 1; i++) {
h[i] = X[i + 1] - X[i];
}
// Расчет вторых разностей узловых точек
for (int i = 1; i < n - 1; i++) {
alpha[i] = 3 * ((Y[i + 1] - Y[i]) / h[i] - (Y[i] - Y[i - 1]) / h[i - 1]);
}
// Решение трехдиагональной системы уравнений
l[0] = 1.0;
5
u[0] = 0.0;
z[0] = 0.0;
for (int i = 1; i < n - 1; i++) {
l[i] = 2 * (X[i + 1] - X[i - 1]) - h[i - 1] * u[i - 1];
u[i] = h[i] / l[i];
z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
}
l[n - 1] = 1.0;
z[n - 1] = 0.0;
c[n - 1] = 0.0;
for (int j = n - 2; j >= 0; j--) {
c[j] = z[j] - u[j] * c[j + 1];
b[j] = (Y[j + 1] - Y[j]) / h[j] - h[j] * (c[j + 1] + 2 * c[j]) / 3.0;
d[j] = (c[j + 1] - c[j]) / (3 * h[j]);
if (point >= X[j] && point <= X[j + 1]) {
double t = point - X[j];
double splineValue = Y[j] + b[j] * t + c[j] * t * t + d[j] * t * t * t;
delete[] a;
delete[] b;
delete[] c;
delete[] d;
delete[] h;
delete[] alpha;
delete[] l;
delete[] u;
delete[] z;
return splineValue;
}
}
delete[] a;
delete[] b;
delete[] c;
delete[] d;
6
delete[] h;
delete[] alpha;
delete[] l;
delete[] u;
delete[] z;
return 0.0;
}
int main()
{
setlocale(LC_ALL, "rus");
FILE* fx;
int ix, nx; float* X;
fx = fopen("x.dat", "rb");
fread(&nx, sizeof(int), 1, fx);
X = new float[nx];
fread(X, sizeof(float), nx, fx);
fclose(fx);
FILE* f;
int iy, ny; float* y;
f = fopen("y.dat", "rb");
fread(&ny, sizeof(int), 1, f);
cout << "Кол-во эксперементальных значений = " << ny << "\n";
y = new float[ny];
fread(y, sizeof(float), ny, f);
fclose(f);
FILE* ftochki;
int i, n1; float* tochki;
ftochki = fopen("tochki.dat", "rb");
fread(&n1, sizeof(int), 1, ftochki);
tochki = new float[n1];
fread(tochki, sizeof(float), n1, ftochki);
fclose(ftochki);
7
cout << "Массив значений x: ";
for (int i = 0; i < nx; i++)
{
cout << X[i] << " ";
}
cout << "" << endl;
cout << "Массив значений y: ";
for (int i = 0; i < ny; i++)
{
cout << y[i] << " ";
}
cout << "" << endl;
cout << "Массив точек для подстановки: ";
for (int i = 0; i < n1; i++)
{
cout << tochki[i] << " ";
}
cout << "" << endl;
float** C;
C = new float* [ny];
for (int i = 0; i < ny; i++)
C[i] = new float[ny];
for (int i = 0; i < ny; i++)
{
for (int j = 0; j < ny; j++)
{
C[i][j] = pow(X[i], j);
}
}
int n = 29;
float* XX;
XX = new float[n];
float asd = 0.02;
8
for (int i = 0; i < n; i++)
{
XX[i] = asd;
asd += 0.01;
}
float* x;
x = new float[ny];
SLAU(C, ny, y, x);
float* kan;
kan = new float[n];
cout << "Значение точек в каноническом полиноме: " << endl;
for (int i = 0; i < n1; i++)
{
cout << kanon(tochki[i], x) << ", ";
}
cout << "" << endl;
float* nety;
nety = new float[n];
cout << "Значение точек в полиноме Ньютона: " << endl;
for (int i = 0; i < n1; i++)
{
cout << net(tochki[i], ny, X, y) << ", ";
}
cout << "" << endl;
float* lagi;
lagi = new float[n];
cout << "Значение точек в полиноме Лагранджа: " << endl;
for (int i = 0; i < n1; i++)
{
cout << lagranj(tochki[i], ny, X, y) << ", ";
}
cout << "" << endl;
float* lin;
9
lin = new float[ny];
cout << "Значение точек в Линейной интерполяции: " << endl;
for (int i = 0; i < n1; i++)
{
cout << LI(tochki[i], X, y, ny) << ", ";
}
cout << "" << endl;
float* cubi;
cubi = new float[n];
cout << "Значение точек в Кубической интерполяции: " << endl;
for (int i = 0; i < n1; i++)
{
cout << cub(X, y, ny, tochki[i]) << ", ";
}
cout << "" << endl;
for (int i = 0; i < n; i++)
{
cubi[i] = cub(X, y, ny, XX[i]);
lagi[i] = lagranj(XX[i], ny, X, y);
nety[i] = net(XX[i], ny, X, y);
kan[i] = kanon(XX[i], x);
}
for (int i = 0; i < ny; i++)
{
lin[i] = LI(X[i], X, y, ny);
}
cout << "" << endl;
GnuP p;
p.plotArrayPar(n, XX, nety, 2, 1, 8, "Полином Ньютона");
p.plotArrayPar(n, XX, kan, 2, 1, 5, "Канонический полином");
p.plotArrayPar(n, XX, lagi, 2, 1, 2, "Полином Лагранжа");
p.plotArrayPar(ny, X, lin, 2, 1, 4, "Линейная интерполяция");
p.plotArrayPar(ny, X, y, 1, 1, 11, "Эксперементальные точки");
p.plotArrayPar(n, XX, cubi, 2, 1, 9, "Кубическая интерполяция");
10
p.plot();
}
