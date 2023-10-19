#include <iostream>
#include <iomanip>
#include <boost/multiprecision/mpfr.hpp>
#include <cmath>


using namespace std;
using bigfloat = boost::multiprecision::mpfr_float_500;
const bigfloat pi("3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844609550582231725359408128481117450284102701938521105559644622948954930381964428810975665933446128475648233786783165271201909145648566923460348610454326648213393607260249141273724587006606315588174881520920962829254091715364367892590360011330530548820466521384146951941511609433057270365759591953092186117381932611793105");
const bigfloat pi_half = pi/2.0;
const bigfloat pi2 = pi*2;
const bigfloat sqrt_error("1e-9");


bigfloat my_abs(const bigfloat a)
{
    return (a >= 0.0L) ? a : -a;
}

bigfloat my_sqrt(const bigfloat a)
{
    bigfloat res = 1;
    while(my_abs(res*res - a) > sqrt_error)
    {
        res = (res + a/res)/2.0;
    }
    return res;
}

//для увеличения области работоспособности, используется unsigned long long
//и знак хранится в отдельной переменной
//для избежания переполнения, программа крашится если аргумент больше максимума улонг лонга
/*bigfloat my_floor(bigfloat x)
{
    int sign = (x >= 0.0L) ? 1 :-1;
    //assuming that x is not very big
    if(x > ULONG_LONG_MAX)
        std::exit(1);
    return (bigfloat)(unsigned long long)my_abs(x)*sign;
}*/

//общая функция как для синуса, так для косинуса
bigfloat normalize_angle(const bigfloat& x)
{
    if(x>2*pi)
        return x - floor(x/(2*pi))*(2*pi);
    else if(x < 0.0)
        return x + (my_abs(floor(x/(2*pi))) + 1)*(2*pi);
    else return x;
}

bigfloat sin_tailor(bigfloat);

bigfloat cos_tailor(bigfloat x)
{
    x = normalize_angle(x);
    if(x > pi_half && x <= pi)
        return -sin_tailor(x-pi_half);
    if(x > pi && x <= pi + pi_half)
        return -cos_tailor(x - pi);
    if(x > pi + pi_half && x <= pi2)
        return sin_tailor(x - pi - pi_half);

    bigfloat sum = 0.0;
    bigfloat term = 1.0;
    bigfloat divisor = 0.0;
    do {
        sum += term;
        divisor+=2;
        term *= -x*x/(divisor*(divisor-1));
    } while (my_abs(term) >= sqrt_error);
    return sum;
}


bigfloat sin_tailor(bigfloat x)
{
    x = normalize_angle(x);
    if(x > pi_half && x <= pi)
        return cos_tailor(x-pi_half);
    if(x > pi && x <= pi + pi_half)
        return -sin_tailor(x - pi);
    if(x > pi + pi_half && x <= pi2)
        return -cos_tailor(x - pi - pi_half);

    //теперь x меньше pi на 2
    bigfloat cos_x = cos_tailor(x);
    return my_sqrt(1 - cos_x*cos_x);
}

int main()
{
    string s;
    std::cin >> s;
    bigfloat inp(s);
    std::cout << std::setprecision(10) << cos_tailor(inp) << '\n';
}