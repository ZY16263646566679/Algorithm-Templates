// 矩阵
#include <bits/stdc++.h>
using namespace std;

namespace Matrix {
    const int maxn = 50; // 这里maxn不能大于718，否则会RE；
    template<typename T>
    struct matrix {
        int n;
        T mat[maxn + 1][maxn + 1];
        matrix(int n = maxn) : n(n) {
            for (int i = 0; i <= n; i++)
                memset(mat[i], 0, (n + 1) * sizeof(T));
            for (int i = 1; i <= n; i++)
                mat[i][i] = 1;
        }
        matrix(const vector<vector<T>>& mt) {
            n = mt.size();
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    mat[i][j] = mt[i - 1][j - 1];
        }
        T* operator[](int i) { return mat[i]; }
        friend ostream& operator<<(ostream& stream, const matrix& mt) {
            string res;
            res += "[\t";
            for (int i = 1; i <= mt.n; i++) {
                if (i > 1) res += "\t";
                for (int j = 1; j <= mt.n; j++) {
                    res += to_string(mt.mat[i][j]);
                    res += "\t";
                }
                if (i < mt.n) res += "\n";
            }
            res += " ]";
            stream << res;
            return stream;
        }
        matrix operator*(matrix mt) {  
            matrix res(n);
            for (int i = 1; i <= n; i++)
                res[i][i] = 0;
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    for (int k = 1; k <= n; k++)
                        res[i][j] += mat[i][k] * mt[k][j];
            return res;
        }
        T det() {
            T res = 0;
            for (int i = 1, sign = 1; i <= n; i++) {
                vector<vector<T>> temp;
                for (int j = 1; j <= n; j++) {
                    vector<T> row;
                    for (int k = 1; k <= n; k++)
                        if (k != j) row.push_back(mat[j][k]);
                    temp.push_back(row);
                }
                res += sign * mat[1][i] * matrix(temp).det();
                sign *= -1;
            }
            return res;
        }
    };
    template<typename T>
    struct unit : matrix<T> {
        int n;
        unit(int order) {
            for (int i = 1; i <= n; i++)
                matrix::mat[i][i] = 1;
        }
        bool operator==(matrix m) {
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++) {
                    if (i - j) { if (m[i][j]) return false; }
                    else if (m[i][j] != 1) return false;
                }
            return true;
        }
    };
}