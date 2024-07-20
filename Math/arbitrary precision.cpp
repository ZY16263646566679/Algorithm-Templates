// 高精度
#include <bits/stdc++.h>
using namespace std;

class Int {
public:
    // constructor
    Int(long long = 0);
    Int(const string&);
    Int(const char* str) { *this = string(str); }

    // assignment operators
    Int& operator=(long long num) { return *this = Int(num); }
    Int& operator=(const string& str) { return *this = Int(str); }
    Int& operator=(const char* str) { return *this = Int(str); }

    // relatiional operators 
    bool operator<(const Int& obj) const { return cmp(obj) < 0; }
    bool operator>(const Int& obj) const { return cmp(obj) > 0; }
    bool operator<=(const Int& obj) const { return cmp(obj) <= 0; }
    bool operator>=(const Int& obj) const { return cmp(obj) >= 0; }
    bool operator==(const Int& obj) const { return cmp(obj) == 0; }
    bool operator!=(const Int& obj) const { return cmp(obj) != 0; }

    // arithmetic operators
    Int operator+() const { return *this; }
    Int operator-() const { return Int(-sign_, val_); }
    Int operator+(const Int&) const;
    Int operator-(const Int&) const;
    Int operator*(const Int&) const;
    Int operator/(const Int&) const;
    Int operator%(const Int&) const;

    // compound assignment operators
    Int& operator+=(const Int& obj) { return *this = *this + obj; }
    Int& operator-=(const Int& obj) { return *this = *this - obj; }
    Int& operator*=(const Int& obj) { return *this = *this * obj; }
    Int& operator/=(const Int& obj) { return *this = *this / obj; }
    Int& operator%=(const Int& obj) { return *this = *this % obj; }

    // increment and decrement operators
    Int& operator++() { return *this += 1; }
    Int& operator--() { return *this -= 1; }
    Int operator++(int);
    Int operator--(int);

    // input and output
    friend istream &operator>>(istream &, Int&);
    friend ostream &operator<<(ostream &, const Int&);

protected:
    enum div_type { division, remainder };
    enum cmp_type { with_sign, without_sign };
    static const int base_ = (int)1e4;
    static const int width_ = 4;
    Int(int s, const vector<int>& v) : sign_(s), val_(v) {}
    int cmp(const Int&, cmp_type = with_sign) const;
    Int& delZero();
    Int& add(const Int&);
    Int& sub(const Int&);
    Int& mul(const Int&, const Int&);
    Int& div(Int&, Int, div_type = division);

private:
    int sign_;
    vector<int> val_;
};

Int::Int(long long num) : sign_(0) {
    if (num < 0) sign_ = -1, num = -num;
    else if (num > 0) sign_ = 1;
    do {
        val_.push_back(num % base_);
        num /= base_;
    } while (num);
}

Int::Int(const string &str) {
    sign_ = str[0] == '-' ? -1 : 1;
    int be = str[0] == '-' ? 1 : 0, en = str.size();
    while ((en -= width_) >= be) {
        stringstream ss(str.substr(en, width_));
        int temp;
        ss >> temp;
        val_.push_back(temp);
    }
    if ((en += width_) > be) {
        stringstream ss(str.substr(be, en - be));
        int temp;
        ss >> temp;
        val_.push_back(temp);
    }
    delZero();
}

Int Int::operator+(const Int& obj) const {
    if (sign_ * obj.sign_ == 1) {
        Int temp;
        return cmp(obj, without_sign) >= 0 ? (temp = *this).add(obj) : (temp = obj).add(*this);
    }
    else if (sign_ * obj.sign_ == -1) return *this - -obj;
    else return sign_ == 0 ? obj : *this;
}

Int Int::operator-(const Int& obj) const {
    if (sign_ * obj.sign_ == 1) {
        Int temp;
        return cmp(obj, without_sign) >= 0 ? (temp = *this).sub(obj) : (temp = -obj).sub(*this);
    }
    else if (sign_ * obj.sign_ == -1) return *this + -obj;
    else return sign_ == 0 ? -obj : *this;
}

inline Int Int::operator*(const Int& obj) const {
    Int temp;
    return (temp.sign_ = sign_ * obj.sign_) == 0 ? temp : temp.mul(*this, obj);
}

inline Int Int::operator/(const Int& obj) const {
    Int temp, mod = *this;
    return cmp(obj, without_sign) < 0 || (temp.sign_ = sign_ * obj.sign_) == 0 ? temp : temp.div(mod, obj);
}

inline Int Int::operator%(const Int& obj) const {
    Int temp, mod = *this;
    return cmp(obj, without_sign) < 0 || (temp.sign_ = sign_) == 0 ? mod : temp.div(mod, obj, remainder);
}

inline Int Int::operator++(int) {
    Int temp = *this;
    ++*this;
    return temp;
}

inline Int Int::operator--(int) {
    Int temp = *this;
    --*this;
    return temp;
}

inline istream& operator>>(istream &in, Int& obj) {
    string str;
    if (in >> str) obj = str;
    return in;
}

ostream& operator<<(ostream &out, const Int& obj) {
    if (obj.sign_ == -1) cout << '-';
    out << obj.val_.back();
    for (int i = obj.val_.size() - 2; i >= 0; i--)
        out << setw(Int::width_) << setfill('0') << obj.val_[i];
    return out;
}

int Int::cmp(const Int& obj, cmp_type typ) const {
    if (typ == with_sign && sign_ != obj.sign_)
        return sign_ - obj.sign_;
    int sign = typ == with_sign ? sign_ : 1;
    if (val_.size() != obj.val_.size())
        return sign * (val_.size() - obj.val_.size());
    for (int i = val_.size() - 1; i >= 0; i--)
        if (val_[i] != obj.val_[i])
            return sign * (val_[i] - obj.val_[i]);
    return 0;
}

inline Int& Int::delZero() {
    while(val_.back() == 0 && val_.size() > 1)
        val_.pop_back();
    if (val_.back() == 0) sign_ = 0;
    return *this;
}

Int& Int::add(const Int& obj) {
    int ts = val_.size(), os = obj.val_.size();
    for (int i = 0; i < os; i++)
        val_[i] += obj.val_[i];
    val_.push_back(0);
    for (int i = 0; i < ts; i++)
        if (val_[i] >= base_) val_[i] -= base_, ++val_[i + 1];
    return delZero();
}

Int& Int::sub(const Int& obj) {
    int pos = obj.val_.size();
    for (int i = 0; i < pos; i++)
        if ((val_[i] -= obj.val_[i]) < 0)
            val_[i] += base_, --val_[i + 1];
    while (val_[pos] < 0)
        val_[pos] += base_, --val_[++pos];
    return delZero();
}

Int& Int::mul(const Int& a, const Int& b) {
    int as = a.val_.size(), bs = b.val_.size();
    val_.resize(as + bs);
    for (int i = 0; i < as; i++)
        for (int j = 0; j < bs; j++) {
            int x = i + j;
            val_[x] += a.val_[i] * b.val_[j];
            val_[x + 1] += val_[x] / base_;
            val_[x] %= base_;
        }
    return delZero();   
}

Int& Int::div(Int& a, Int b, div_type typ) {
    int move = a.val_.size() - b.val_.size();
    val_.resize(move + 1);
    b.val_.insert(b.val_.begin(), move, 0);
    for (int i = move; i >= 0; i--) {
        int left = 0, right = base_;
        while (left + 1 < right) {
            int mid = (left + right) >> 1;
            if (a.cmp(b * Int(mid), without_sign) >= 0) left = mid;
            else right = mid;
        }
        val_[i] = left;
        a.sub(b * Int(left));
        b.val_.erase(b.val_.begin());
    }
    return typ == division ? delZero() : a;
}

// faster
using u32 = unsigned int;
using ll = long long;
using ull = unsigned long long;
using comp = complex<double>;

struct ffter {
    vector<comp> w{1.0};
    void init(int l) {
        int old = w.size();
        if (l <= (old << 1))
            return;
        int t = __lg(l - 1);
        l = 1 << t, w[0] = 1.0, w.resize(l);
        for (int i = 1; i < l; i <<= 1)
            w[i] = polar(1.0, acos(-1.0) / (i << 1));
        for (int i = 1; i < l; i++)
            w[i] = w[i & (i - 1)] * w[i & -i];
    }
    void dif(comp *f, int L) {
        for (int l = L >> 1, r = L; l; l >>= 1, r >>= 1) {
            for (comp *k = f; k != f + l; k++) {
                comp x = *k, y = k[l];
                *k = x + y, k[l] = x - y;
            }
            for (comp *j = f + r, *o = w.data() + 1; j != f + L; j += r, o++)
                for (comp *k = j; k != j + l; k++) {
                    comp x = *k, y = k[l] * (*o);
                    *k = x + y, k[l] = x - y;
                }
        }
    }
    void dit(comp *f, int L) {
        for (int l = 1, r = 2; l < L; l <<= 1, r <<= 1) {
            for (comp *k = f; k != f + l; k++) {
                comp x = *k, y = k[l];
                *k = x + y, k[l] = x - y;
            }
            for (comp *j = f + r, *o = w.data() + 1; j != f + L; j += r, o++)
                for (comp *k = j; k != j + l; k++) {
                    comp x = *k, y = k[l];
                    *k = x + y, k[l] = (x - y) * conj(*o);
                }
        }
    }
    void fconv(comp *F, comp *G, int lm) {
        init(lm), dif(F, lm), dif(G, lm);
        double fx = 1.0 / lm, fx2 = 0.25 * fx;
        F[0] = {F[0].real() * G[0].real() + F[0].imag() * G[0].imag(), F[0].real() * G[0].imag() + F[0].imag() * G[0].real()};
        F[0] *= fx, F[1] *= G[1] * fx;
        for (int k = 2, m = 3; k < lm; k <<= 1, m <<= 1)
            for (int i = k, j = i + k - 1; i < m; ++i, j--) {
                comp oi = F[i] + conj(F[j]), hi = F[i] - conj(F[j]);
                comp Oi = G[i] + conj(G[j]), Hi = G[i] - conj(G[j]);
                comp r0 = oi * Oi - hi * Hi * ((i & 1) ? -w[i >> 1] : w[i >> 1]), r1 = Oi * hi + oi * Hi;
                F[i] = (r0 + r1) * fx2, F[j] = conj(r0 - r1) * fx2;
            }
        dit(F, lm);
    }
} FFT;

class BigInt {
public:
    vector<u32> digits;
    static constexpr u32 base = 1e8;
    static constexpr u32 fft_base = 1e4;
    static constexpr int bit = 8;

public:
    BigInt(ll x) { *this = x; }
    BigInt() { *this = 0; }
    int Size() const { return digits.size(); }
    BigInt &operator=(const BigInt &x) {
        digits = x.digits;
        return *this;
    }
    BigInt &operator=(ll x) {
        if (!digits.empty())
            digits.clear();
        while (x) {
            digits.push_back(x % base);
            x /= base;
        }
        if (digits.empty())
            digits.push_back(0);
        return *this;
    }
    void read_digits(string &s) {
        s = "";
        char c = getchar();
        while (!isdigit(c))
            c = getchar();
        while (isdigit(c)) {
            s += c;
            c = getchar();
        }
    }
    void input() {
        string s;
        read_digits(s), reverse(s.begin(), s.end());
        if (!digits.empty())
            digits.clear();
        digits.resize((s.size() + bit - 1) / bit);
        u32 z = 1;
        for (int i = 0; i < s.size(); i++) {
            if (i % bit == 0)
                z = 1;
            digits[i / bit] += z * (s[i] - '0'), z *= 10;
        }
    }
    string toString() const {
        static char buf[bit + 1];
        sprintf(buf, "%u", digits.back());
        string ret = buf;
        int l = ret.size(), l2 = digits.size(), p = 0;
        ret.resize(l + bit * (l2 - 1));
        for (int i = (int)l2 - 2; i >= 0; i--)
            sprintf(const_cast<char *>(ret.c_str()) + l + (p++) * bit, "%08u", digits[i]);
        return ret;
    }
    int cmp(const BigInt &x) const {
        int l = Size(), lx = x.Size();
        if (l != lx)
            return l > lx ? 1 : -1;
        for (int i = l - 1; i >= 0; i--)
            if (digits[i] != x.digits[i])
                return digits[i] > x.digits[i] ? 1 : -1;
        return 0;
    }
    bool operator<(const BigInt &x) const { return cmp(x) == -1; }
    bool operator==(const BigInt &x) const { return cmp(x) == 0; }
    bool operator>(const BigInt &x) const { return cmp(x) == 1; }
    bool operator>=(const BigInt &x) const { return !(*this < x); }
    bool operator!=(const BigInt &x) const { return !(*this == x); }
    bool operator<=(const BigInt &x) const { return !(*this > x); }
    friend BigInt operator+(const BigInt &a, const BigInt &b) { return a.Size() < b.Size() ? b.add(a) : a.add(b); }
    friend BigInt operator-(const BigInt &a, const BigInt &b) { return a.sub(b); }
    friend BigInt operator*(const BigInt &a, const BigInt &b) { return a.Size() < b.Size() ? b.mul(a) : a.mul(b); }
    friend BigInt operator/(const BigInt &a, const BigInt &b) { return a.div(b).first; }
    friend BigInt operator%(const BigInt &a, const BigInt &b) { return a.div(b).second; }
    BigInt add(const BigInt &x) const {
        BigInt r;
        r.digits.resize(Size());
        u32 c = 0;
        for (int i = 0; i < x.Size(); i++) {
            r.digits[i] = digits[i] + x.digits[i] + c, c = 0;
            if (r.digits[i] >= base)
                r.digits[i] -= base, c = 1;
        }
        for (int i = x.Size(); i < Size(); i++) {
            r.digits[i] = digits[i] + c, c = 0;
            if (r.digits[i] >= base)
                r.digits[i] -= base, c = 1;
        }
        if (c) r.digits.push_back(c);
        return r;
    }
    BigInt sub(const BigInt &x) const {
        BigInt r;
        r.digits.resize(Size());
        u32 c = 0;
        for (int i = 0; i < x.Size(); i++) {
            r.digits[i] = digits[i] - x.digits[i] - c, c = 0;
            if (r.digits[i] >= base)
                r.digits[i] += base, c = 1;
        }
        for (int i = x.Size(); i < Size(); i++) {
            r.digits[i] = digits[i] - c, c = 0;
            if (r.digits[i] >= base)
                r.digits[i] += base, c = 1;
        }
        // while (r.digits.back()==0&&r.Size()>1) r.digits.pop_back();
        return r;
    }
    BigInt mul_native(const BigInt &x) const {
        int n = Size(), m = x.Size();
        BigInt r;
        r.digits.resize(n + m);
        ull tmp = 0;
        for (int i = 0; i < n + m - 1; i++) {
            for (int j = (i >= n) ? i - n + 1 : 0; j <= min(i, m - 1); j++)
                tmp += x.digits[j] * ull(digits[i - j]);
            r.digits[i] = tmp % base, tmp /= base;
        }
        if (tmp) r.digits[n + m - 1] = tmp;
        while (r.digits.back() == 0 && r.Size() > 1)
            r.digits.pop_back();
        // cout<<1<<endl;
        return r;
    }
    BigInt mul_fft(const BigInt &x) const {
        static vector<comp> F, G;
        int n = Size(), m = x.Size();
        int u = n + m, lm = 2 << __lg(u - 1);
        F.assign(lm, 0.0), G.assign(lm, 0.0);
        for (int i = 0; i < n; i++)
            F[i] = comp(digits[i] % fft_base, digits[i] / fft_base);
        for (int i = 0; i < m; i++)
            G[i] = comp(x.digits[i] % fft_base, x.digits[i] / fft_base);
        FFT.fconv(F.data(), G.data(), lm);
        ull tmp = 0;
        BigInt r;
        r.digits.resize(u);
        for (int i = 0; i < u; i++) {
            tmp += (ll(F[i].real() + 0.5) + (ll(F[i].imag() + 0.5) * fft_base));
            r.digits[i] = tmp % base, tmp /= base;
        }
        while (r.digits.back() == 0 && r.Size() > 1)
            r.digits.pop_back();
        // cout<<2<<endl;
        return r;
    }
    BigInt mul(const BigInt &x) const {
        if (x.Size() == 0)
            return BigInt(0);
        if (x.Size() <= 16)
            return mul_native(x);
        return mul_fft(x);
    }
    ull get_val(const vector<u32> &x, int y, int z) const {
        return ull(10) * base * (y + 1 < z ? x[y + 1] : 0) + ull(10) * x[y] + (y >= 1 ? x[y - 1] : 0) / (base / 10);
    }
    void Sub(const BigInt &x, BigInt &r, int i, ll p) const {
        ll k = 0;
        for (int j = 0; j < x.Size(); j++) {
            k = k - p * x.digits[j] + r.digits[i + j];
            r.digits[i + j] = int(k % base), k /= base;
            if (r.digits[i + j] >= base)
                r.digits[i + j] += base, k--;
        }
        if (k) r.digits[i + x.Size()] += k;
    }
    pair<BigInt, BigInt> div_native(const BigInt &x) const {
        BigInt q, r = *this;
        int l = Size() - x.Size() + 1;
        q.digits.resize(l);
        for (int i = l - 1; i >= 0; i--) {
            u32 p = 0;
            while (1) {
                ull p1 = get_val(r.digits, i + x.Size() - 1, Size());
                ull p2 = get_val(x.digits, x.Size() - 1, x.Size()) + 1;
                if ((p = p1 / p2) == 0)
                    break;
                Sub(x, r, i, p);
                q.digits[i] += p;
            }
            p = 1;
            for (int j = x.Size() - 1; j >= 0; j--)
                if (r.digits[i + j] != x.digits[j]) {
                    p = r.digits[i + j] > x.digits[j];
                    break;
                }
            if (p) Sub(x, r, i, p), q.digits[i] += p;
        }
        while (q.digits.back() == 0 && q.Size() > 1)
            q.digits.pop_back();
        while (r.digits.back() == 0 && r.Size() > 1)
            r.digits.pop_back();
        return {q, r};
    }
    pair<BigInt, BigInt> div(const BigInt &x) const {
        if (*this < x) return {BigInt(0), *this};
        return div_native(x);
    }
};