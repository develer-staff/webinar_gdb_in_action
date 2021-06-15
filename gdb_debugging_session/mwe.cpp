#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

/**
    Find at which point inside the interval (0, <input value>] the integral
    of the supplied polynomial reaches a minimum.
*/


struct CurvePoint;

struct PolynomialComputation {
    CurvePoint *_parent;

    PolynomialComputation(CurvePoint *parent): _parent(parent) { }

    double compute() const;
};

struct CurvePoint {
    std::vector<double> _coefficients;
    double _value_x;
    double _value_integral;
    PolynomialComputation _computer;

    CurvePoint(double x, std::vector<double> coeff):
        _value_x(x),
        _value_integral(0.0),
        _coefficients(coeff),
        _computer(this) {}

    CurvePoint(const CurvePoint &old):
        _coefficients(old._coefficients),
        _value_x(old._value_x),
        _value_integral(old._value_integral),
        _computer(old._computer) {
        this->_computer._parent = this;
    }
    
    /** the forgotten operator...
    CurvePoint & operator=(const CurvePoint &old) {
        this->_coefficients = old._coefficients;
        this->_value_x = old._value_x;
        this->_value_integral = old._value_integral;
        this->_computer = old._computer;
        this->_computer._parent = this;
        return *this;
    }
    */

    int degree() const { return this->_coefficients.size(); }
    double coeffAt(int i) const { return this->_coefficients[i]; }
    double y() const { return this->_computer.compute(); };
    double x() const { return this->_value_x; };
    double integral() const { return this->_value_integral; }
    std::string asCoord() const { 
        return "(" + std::to_string(this->x()) + ", " + 
                     std::to_string(this->y()) + ")"; }
};

double PolynomialComputation::compute() const {
    // using Horner's method
    double res = this->_parent->coeffAt(0);
    for(int i=1; i<this->_parent->degree(); i++) {
        res = res*this->_parent->_value_x + this->_parent->coeffAt(i);
    }
    return res;
}

void print_polynomial(const std::vector<double> coeff) {
    std::cout << "input polynomial: ";
    for (int i=0, n=coeff.size(); i<n; i++) { 
        std::cout << coeff[i] << "x^" << (n-i-1) << " ";
    }
    std::cout << std::endl;
}

void print_results(const CurvePoint &min, const CurvePoint &max) {
    std::cout << "Min integral value " << min.integral() << " at " << min.asCoord() << std::endl;
    std::cout << "Max integral value " << max.integral() << " at " << max.asCoord() << std::endl;
}

int main(int argc, char **argv) {

    // parse input
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " MAX_X COEFF_A [COEFF_B .. [COEFF_N]]" << std::endl;
        exit(1);
    }
    int max_x = std::atoi(argv[1]);
    if (max_x < 2) max_x = 2;
    std::vector<double> coeff;
    for(int i=2; i<argc; i++) coeff.push_back(std::atof(argv[i]));
    print_polynomial(coeff);

    // create points
    std::vector<CurvePoint> interval;
    interval.reserve(max_x);
    for (int i=0; i<max_x; i++) {
        interval.push_back(CurvePoint(double(i), coeff));
    }

    // approximate integral using x-axis quantization of 1 unit
    double accumulator = 0.0;
    for (int i=0, n=interval.size(); i<n; i++) {
        interval[i]._value_integral = accumulator;
        accumulator += 1.0 * interval[i].y();
        //std::cout << interval[i].asCoord() << " -> " << interval[i].integral() << "\n";
    }

    // sort based on the just-computed integral value...
    // just exclude x==0 since it will always be 0 becuase the integral is
    // empty by definition.
    auto sort_on_integral = [](const CurvePoint &a, const CurvePoint &b) {
        return a.integral() < b.integral();
    };
    std::sort(interval.begin()+1, interval.end(), sort_on_integral); 

    // find and print result
    CurvePoint &min = interval[1];
    CurvePoint &max = interval.back();
    print_results(min, max);

    return 0;
}

