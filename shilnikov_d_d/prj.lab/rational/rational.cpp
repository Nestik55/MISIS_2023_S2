#include "include/rational/rational.hpp"
#include <stdexcept>
#include <iostream>
#include <sstream>

Rational::Rational(const int32_t num) noexcept {
	num_ = num;
	den_ = 1;
}

Rational::Rational(const int32_t num, const int32_t denom) {
//	std::cout << "konstr: " << num << " " << denom << std::endl;
	if (denom == 0) {
        throw std::invalid_argument("Div by zero!");
	}

	num_ = num;
	den_ = denom;
	
	normalize();
}

void Rational::normalize() noexcept {
//	std::cout << "norm1: " << *this << std::endl;
	int32_t signNum = (num_ < 0? -1: 1);
	int32_t signDenom = (den_ < 0? -1: 1);

	num_ = num_*signNum;
	den_ = den_*signDenom;
	
	int32_t a = num_;
	int32_t b = den_;
	
	while (b) {
		a %= b;
		std::swap(a, b);
	}
//	std::cout << "norm2: " << *this << std::endl;
	num_ /= a;
	den_ /= a;
//	std::cout << "norm3: " << *this << std::endl;
	if (signNum*signDenom == -1) {
		num_ = -num_;
	}

}


bool Rational::operator==(const Rational& r) const noexcept {
	return this->num_ == r.num_ && this->den_ == r.den_;
}

bool Rational::operator!=(const Rational& r) const noexcept {
	return this->num_ != r.num_ || this->den_ != r.den_;
}

bool Rational::operator>(const Rational& r) const noexcept {
	return this->num_*r.den_ > this->den_*r.num_;
}

bool Rational::operator<(const Rational& r) const noexcept {
	return this->num_*r.den_ < this->den_*r.num_;
}

bool Rational::operator>=(const Rational& r) const noexcept {
	return this->num_*r.den_ >= this->den_*r.num_;
}

bool Rational::operator<=(const Rational& r) const noexcept {
	return this->num_*r.den_ <= this->den_*r.num_;
}

Rational Rational::operator-() const noexcept {
	return Rational(-num_, den_);
}

Rational::operator bool() const noexcept {
	return num_ != 0;
}

Rational& Rational::operator*=(const Rational& rhs) noexcept {
	this->num_*= rhs.num_;
	this->den_*= rhs.den_;
//	std::cout << "this: " << *this << std::endl;
	normalize();
//	std::cout << "this2*: " << *this << std::endl;
	return *this;
}

Rational& Rational::operator+=(const Rational& rhs) noexcept {
	this->num_ = this->num_*rhs.den_ + this->den_*rhs.num_;
	this->den_ = this->den_*rhs.den_;
	
	normalize();
//	std::cout << "this: " << *this << std::endl;
	return *this;
}

Rational& Rational::operator-=(const Rational& rhs) noexcept {
	this->num_ = this->num_*rhs.den_ - this->den_*rhs.num_;
	this->den_ = this->den_*rhs.den_;
	
	normalize();
	return *this;
}

Rational& Rational::operator/=(const Rational& rhs) {
	if (!rhs) {
		throw std::invalid_argument("Div by zero!");
	}
	
	this->num_ = this->num_*rhs.den_;
	this->den_ = this->den_*rhs.num_;
	
	normalize();
	return *this;
}


std::istream& Rational::read_from(std::istream& istrm) noexcept {
	char c;
	int dd, nn;
	istrm >> nn >> std::noskipws >> c >> dd >> std::skipws;
	
	if (istrm.good() || istrm.eof()) {
		if (c == delim() && dd > 0) {
			*this = Rational(nn, dd);
		} else {
			istrm.setstate(std::ios_base::failbit);
		}
	}
	
	
	
	return istrm;
}

std::ostream& Rational::write_to(std::ostream& ostrm) const noexcept {
    ostrm << num() << delim() << denom();
  	return ostrm;
}


std::istream &operator>>(std::istream& istrm, Rational& rhs) noexcept {
    return rhs.read_from(istrm);
}

std::ostream &operator<<(std::ostream& ostrm, const Rational& rhs) noexcept {
    rhs.write_to(ostrm);
    return ostrm;
}

