#include <bits/stdc++.h>
using namespace std;

struct BigInt {
    int len;
    bool sign;       // 符号位
    string digits;   // 存储大数的字符串
    
    BigInt() : sign(true) {}
    
    BigInt(int n) {
        if (n < 0) sign = false, n = -n;
        else sign = true;
        while (n) {
            digits += n % 10 + '0';
            n /= 10;
        }
        reverse(digits.begin(), digits.end());
        len = digits.length();
    }
    
    BigInt(string str) {
        len = str.length();
        if (str[0] == '-') sign = false, str.erase(0, 1);
        else sign = true;
        reverse(str.begin(), str.end());
        digits = str;
        trim();
    }
    
    void trim() { while (digits.size() > 1 && digits.back() == '0') digits.pop_back(); }
    
    char operator[](int index) { return digits[digits.length() - index - 1]; } // 0：最低位
    
    BigInt operator-() const { BigInt r = *this; r.sign = !sign; return r; }
    
    BigInt operator+(const BigInt& rhs) const {
        if (sign ^ rhs.sign) return *this - (-rhs);
        BigInt sum;
        sum.digits.resize(max(digits.size(), rhs.digits.size()) + 1);
        for (int i = 0, carry = 0; i < sum.digits.size(); i++) {
            int s = carry;
            if (i < digits.size()) s += digits[i] - '0';
            if (i < rhs.digits.size()) s += rhs.digits[i] - '0';
            sum.digits[i] = s % 10 + '0';
            carry = s / 10;
        }
        sum.trim();
        sum.sign = sign;
        return sum;
    }

    BigInt operator-(const BigInt& rhs) const {
        if (sign ^ rhs.sign) return *this + (-rhs);
        if (abs() < rhs.abs()) return -(rhs - *this);
        BigInt diff;
        diff.digits.resize(digits.size());
        for (int i = 0, borrow = 0; i < digits.size(); i++) {
            int d = borrow;
            d += digits[i] - '0' - (i < rhs.digits.size() ? rhs.digits[i] - '0' : 0);
            if (d < 0) d += 10, borrow = -1;
            else borrow = 0;
            diff.digits[i] = d + '0';
        }
        diff.trim();
        diff.sign = *this >= rhs;
        return diff;
    }

    BigInt operator*(const BigInt& rhs) const {
        BigInt prod;
        prod.digits.resize(digits.size() + rhs.digits.size() + 1, '0');
        prod.sign = sign == rhs.sign;
        for (int i = 0; i < digits.size(); i++) {
            int carry = 0;
            for (int j = 0; j < rhs.digits.size(); j++) {
                int s = carry + (digits[i] - '0') * (rhs.digits[j] - '0') + prod.digits[i + j] - '0';
                carry = s / 10;
                prod.digits[i + j] = s % 10 + '0';
            }
            prod.digits[i + rhs.digits.size()] += carry;
        }
        prod.trim();
        return prod;
    }

    bool operator<(const BigInt& rhs) const {
        if (sign != rhs.sign) return !sign;
        if (digits.size() != rhs.digits.size())
            return (digits.size() < rhs.digits.size()) ^ !sign;
        for (int i = digits.size()-1; i >= 0; i--)
            if (digits[i] != rhs.digits[i])
                return (digits[i] < rhs.digits[i]) ^ !sign;
        return false;
    }

    bool operator>(const BigInt& rhs) const { return rhs < *this; }
    
    bool operator<=(const BigInt& rhs) const { return !(rhs < *this); }
    
    bool operator>=(const BigInt& rhs) const { return !(*this < rhs); }
    
    bool operator==(const BigInt& rhs) const { return sign == rhs.sign && digits == rhs.digits; }
    
    bool operator!=(const BigInt& rhs) const { return !(*this == rhs); }

    BigInt abs() const {
        BigInt r = *this;
        r.sign = true;
        return r;
    }

    explicit operator bool() const { return digits.size() > 1 || digits[0] != '0'; }

    friend istream& operator>>(istream& in, BigInt& num) {
        string str;
        if (in >> str) num = BigInt(str);
        return in;
    }

    friend ostream& operator<<(ostream& out, const BigInt& num) {
        if (!num.sign) out << '-';
        for (int i = num.digits.size() - 1; i >= 0; i--)
            out << num.digits[i];
        return out;
    }
};