#include<bits/stdc++.h>
typedef long double ld;
using namespace std;

ld binpow (ld a, int n)
{
	if (n == 0)
		return 1;
	if (n % 2 == 1)
		return (binpow (a, n-1) * a);
	else
    {
		int b = (binpow (a, n/2));
		return (b * b);
	}
}

class Polynom
{
public:
    int n;
    ld *coeff;
    Polynom();
    Polynom(int d, ld *mass);
    Polynom(int d);
    ld Coef(int i);
    ld Value(ld x);
    ~Polynom();
    Polynom(const Polynom &);       //копирование
    int getn();                     //степень полинома
    Polynom operator+(const Polynom &);
    Polynom operator-(const Polynom &);
    Polynom operator*(const Polynom &);
    Polynom operator=(const Polynom &);
    friend ostream &operator << (ostream &s, const Polynom &c);
    friend istream &operator >> (istream &s, Polynom &c);

};

Polynom::Polynom()
{
    n = 0;
    coeff = new ld[1];
    coeff[0] = 0;
}

Polynom::~Polynom()
{
    delete[]coeff;
}

Polynom::Polynom(int d)
{
    n = d;
    coeff = new ld[n + 1];
    for (int i = 0; i <= n; i++)
        coeff[i] = 0;
}

Polynom::Polynom(int d, ld *mass)
{
    n = d;
    coeff = new ld[n + 1];
    for (int i = 0; i <= n; i++)
        coeff[i] = mass[i];
}

Polynom::Polynom(const Polynom &f)
{
    n = f.n;
    coeff = new ld[n + 1];
    for (int i = 0; i <= n; i++)
        coeff[i] = f.coeff[i];
}
int Polynom::getn()
{
    return n;
}
ld Polynom::Coef(int i)
{
    if (i <= n)
        return coeff[i];
    else
        return 0.0;
}

ld Polynom::Value(ld x)
{
    ld Sum = coeff[0];
    for(int i = 1; i <= n; i++)
        Sum += binpow(x,i) * coeff[i];
    return Sum;
}

Polynom Polynom::operator-(const Polynom &t)
{
    if (n > t.n)
    {
        Polynom Z(n, coeff);
        for (int i = 0; i <= t.n; i++)
            Z.coeff[i] -= t.coeff[i];
        return Z;
    }
    else
    {
        Polynom Z(t.n, t.coeff);
        for (int i = 0; i <= n; i++)
            Z.coeff[i] =coeff[i] - Z.coeff[i];
        for (int i = n + 1; i <= t.n; i++)
            Z.coeff[i] = Z.coeff[i] * (-1);
        return Z;
    }
}
Polynom Polynom::operator+(const Polynom &t)
{
    int i;
    if (n >= t.n)
    {
        Polynom Z(n, coeff);
        for (i = 0; i <= t.n; i++)
            Z.coeff[i] += t.coeff[i];
        return Z;
    }
    else
    {
        Polynom Z(t.n, t.coeff);
        for (i = 0; i <= n; i++)
            Z.coeff[i] += coeff[i];
        return Z;
    }
}
Polynom Polynom::operator*(const Polynom &t)
{
    Polynom Z(n + t.n);
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= t.n; j++)
            Z.coeff[i + j] += coeff[i]*t.coeff[j];
    return Z;
}
Polynom Polynom::operator = (const Polynom &t)
{
    if(this!=&t)
    {
        delete[] coeff;
        n = t.n;
        coeff = new ld[n + 1];
        for (int i = 0; i <= n; i++)
            coeff[i] = t.coeff[i];
    }
    return *this;
}
istream &operator >> (istream &s, Polynom &c)
{
    for (int i = 0; i <= c.n; i++)
        s >> c.coeff[i];
    return s;
}
ostream &operator << (ostream &s, const Polynom &c)
{
    int N = 0, f = -1;
    for (int i = 0; i <= c.n; i++)
        if (c.coeff[i] != 0)
        {
            if(f < 0)
                f = i;
            N++;
        }
    if (N != 0)
    {
        if (f == 0)
            s << c.coeff[f];
        else
            s << c.coeff[f] << " * x^" << f << " ";
        for (int i = f+1; i <= c.n; i++)
        {
            if (c.coeff[i] < 0)
                if(c.coeff[i] != -1)
                    s << c.coeff[i] << " * x^" << i << " ";
                else
                    s << "- " << "x^" << i;
            if(c.coeff[i] > 0)
            {
                if (c.coeff[i] != 0)
                    if(c.coeff[i] != 1)
                        s << "+ " << c.coeff[i] << " * x^" << i << " ";
                    else
                        s<< "+ " << "x^" << i << " ";
            }
        }
        s << '\n';
    }
    else
        s << 0;
    return s;
}


int main()
{
    setlocale(LC_ALL, "Russian");
    int n, m, i;
    ld x;
    cout << "Введите степени многочленов p(x) и q(x):" << '\n';
    cin >> n >> m;
    Polynom A(n), B(m);
    cout << "Введите коэфициенты полинома p(x):" << '\n';
    cin >> A;
    cout << "Введите коэфициенты полинома q(x):" << '\n';
    cin >> B;
    cout << setw(17) << "Многочлен p(x):" << setw(5) << A << '\n';
    cout << setw(17) << "Многочлен q(x):" << setw(5) << B << '\n';
    cout << setw(17) << "Сложение p(x) + q(x):" << setw(5) << (A + B) << '\n';
    cout << setw(17) << "Вычитание p(x) - q(x):" << setw(5) << (A - B) << '\n';
    cout << setw(17) << "умножение p(x) * q(x):" << setw(5) << (A * B)<< '\n';
    cout << "Введите точку:" << '\n';
    cin >> x;
    cout << setw(17) << "Значение p(x) в точке:" << setw(5) << A.Value(x) << '\n';
    cout << setw(17) << "Значение q(x) в точке:" << setw(5) << B.Value(x) << '\n';
    //cin >> i;
    //cout << A.Coef(i) << endl;

    //system("pause");
}
