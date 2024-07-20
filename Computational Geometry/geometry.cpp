#include <bits/stdc++.h>
using namespace std;

// 计算几何
const long double PI = 3.1415926535897932384l;
// 点
struct Point {
    long double x, y;
    Point(long double x = 0, long double y = 0) : x(x), y(y) {}
    friend Point operator+(Point A, Point B) { return Point(A.x + B.x, A.y + B.y); }
    friend Point operator-(Point A, Point B) { return Point(A.x - B.x, A.y - B.y); }
    friend Point operator*(Point A, long double k) { return Point(A.x * k, A.y * k); }
    friend Point operator/(Point A, long double k) { return Point(A.x / k, A.y / k); }
    Point operator=(Point B) { return Point(B.x, B.y); }
    friend bool operator==(Point A, Point B) { return A.x == B.x && A.y == B.y; }
};
// 两点之间距离
double Distance(const Point& A, const Point& B) { return hypot(A.x - B.x, A.y - B.y); }
// 向量：用点坐标表示
typedef Point Vector;
// 点积
double Dot(const Vector& A, const Vector& B) { return A.x * B.x + A.y * B.y; }
// 向量的长度及其平方
double Len(const Vector& A) { return sqrt(Dot(A, A)); }
double Len2(const Vector& A) { return Dot(A, A); }
// 求向量之间夹角
double Angle(const Vector& A, const Vector& B) { return acos(Dot(A, B) / Len(A) / Len(B)); }
// 叉积
double Cross(const Vector& A, const Vector& B) { return A.x * B.y - A.y * B.x; }
// 求平行四边形面积（以A为公共点，若求三角形面积则再乘以1/2）
double Area(const Point& A, const Point& B, const Point& C) { return Cross(B - A, C - A); }
// 向量旋转（逆时针旋转rad度）
Vector Rotate(const Vector& A, double rad) { return Vector(A.x * cos(rad) - A.y * sin(rad), A.x * sin(rad) + A.y * cos(rad)); }
// 判断向量是否平行
bool Parallel(const Vector& A, const Vector& B) { return A.x * B.y - A.y * B.x == 0; }
// 直线
struct Line {
    Point p1, p2;
    long double angle;
    // 两点式：(y - y1) / (y2 - y1) = (x - x1) / (x2 - x1)
    Line(Point p1, Point p2) : p1(p1), p2(p2) {
        if (p1.x - p2.x)
            angle = atan((p2.y - p1.y) / (p2.x - p1.x));
        else angle = PI / 2;
    }
    // 点斜式：y - y0 = tan(angle)(x - x0)
    Line(Point p, long double angle) {
        p1 = p;
        if (angle == PI / 2) p2 = (p1 + Point(0, 1));
        else p2 = (p1 + Point(1, tan(angle)));
    }
    // 一般式：ax + by + c = 0
    Line(long double a, long double b, long double c) {
        if (a && b) {
            p1 = Point(0, -c / b);
            p2 = Point(1, -(c + a) / b);
            angle = atan(-a / b);
        } else if (a == 0) {
            p1 = Point(0, -c / b);
            p2 = Point(1, -c / b);
            angle = 0;
        } else {
            p1 = Point(-c / a, 0);
            p2 = Point(-c / a, 1);
            angle = PI / 2;
        }
    }
};
// 线段
typedef Line Segment;
// 点和直线的位置关系（大于零为右，小于零为左）
int Point_line_relation(const Point& p, Line v) { return Cross(p - v.p1, v.p2 - v.p1); }
// 点到直线的距离
double Dis_point_line(const Point& p, Line v) { return fabs(Cross(p - v.p1, v.p2 - v.p1) / Distance(v.p1, v.p2)); }
// 点在直线上的投影
Point Point_line_proj(const Point& p, Line v) {
    double k = Dot(v.p2 - v.p1, p - v.p1) / Len2(v.p2 - v.p1);
    return v.p1 + (v.p2 - v.p1) * k;
}
// 点关于直线的对称点
Point Point_line_symmetry(const Point& p, Line v) {
    Point q = Point_line_proj(p, v);
    return Point(2 * q.x - p.x, 2 * q.y - p.y);
}
// 点到线段的距离
double Dis_point_seg(const Point& p, Segment v) {
    if (Dot(p - v.p1, v.p2 - v.p1) < 0 || Dot(p - v.p2, v.p1 - v.p2) < 0)
        return min(Distance(p, v.p1), Distance(p, v.p2));
    return Dis_point_line(p, v);
}
// 两条直线的位置关系（-1：重合，0：平行，1：相交）
int Line_relation(Line v1, Line v2) {
    if (Cross(v1.p2 - v1.p1, v2.p2 - v2.p1) == 0)
        if (Point_line_relation(v1.p1, v2) == 0) return -1;
        else return 0;
    else return 1;
}
// 两条直线的交点
Point Cross_point(Line v1, Line v2) {
    double s1 = Cross(v1.p2 - v1.p1, v2.p1 - v1.p1), s2 = Cross(v1.p2 - v1.p1, v2.p2 - v1.p1);
    return Point(v2.p1.x * s2 - v2.p2.x * s1, v2.p1.y * s2 - v2.p2.y * s1) / (s2 - s1);
}
// 判断两个线段是否相交
bool Cross_segment(Segment v1, Segment v2) {
    double c1 = Cross(v1.p2 - v1.p1, v2.p1 - v1.p1), c2 = Cross(v1.p2 - v1.p1, v2.p2 - v1.p1);
    double d1 = Cross(v2.p2 - v2.p1, v1.p1 - v2.p1), d2 = Cross(v2.p2 - v2.p1, v1.p2 - v2.p1);
    return c1 * c2 <= 0 && d1 * d2 <= 0;
}
// 求两条线段的交点：先判断两条线段是否相交，若相交，问题转化成两条直线求交点