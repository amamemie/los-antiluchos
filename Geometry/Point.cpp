struct point
{
	int x, y;
	point() {}
	point(int x, int y): x(x), y(y) {}
	point operator -(point p) {return point(x - p.x, y - p.y);}
	point operator +(point p) {return point(x + p.x, y + p.y);}
	int sq() const{return x * x + y * y;}
	double abs() const {return sqrt(sq());}
	int operator ^(point p) {return x * p.y - y * p.x;}
  	int operator *(point p) {return x * p.x + y * p.y;}
  	point operator *(int a) {return point(x * a, y * a);}
	bool operator <(const point& p) const {return x == p.x ? y < p.y : x < p.x;}
	int left(point a, point b) {
        return ((b - a) ^ (*this - a)); // 0, -, +
    }
};
ostream& operator<<(ostream& os, const point& p) {
    return os << "(" << p.x << "," << p.y << ")\n";
}
 
 
void polarSort(vector<point>& v) {
  sort(v.begin(), v.end(), [] (point a, point b) {
    const point origin{0, 0};
    bool ba = a < origin, bb = b < origin;
    if (ba != bb) { return ba < bb; }
    return (a^b) > 0;
  });
}
