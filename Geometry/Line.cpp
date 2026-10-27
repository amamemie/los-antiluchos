typedef double T;

struct line {
	pt v; T c;
	// From direction vector v and offset c
	line(pt v, T c) : v(v), c(c) {}
	// From equation ax+by=c
	line(T a, T b, T c) : v({b,-a}), c(c) {}
	// From points P and Q
	line(pt p, pt q) : v(q-p), c(cross(v,p)) {}
	// Will be defined later:
	// - these work with T = int
	T side(pt p);
	double dist(pt p);
	line perpThrough(pt p);
	bool cmpProj(pt p, pt q);
	line translate(pt t);
	// - these require T = double
	void shiftLeft(double dist);
	pt proj(pt p);
	pt refl(pt p);
}

T side(pt p) {return cross(v,p)-c;}

double dist(pt p) {return abs(side(p)) / abs(v);}

double sqDist(pt p) {return side(p)*side(p) / (double)sq(v);}

line translate(pt t) {return {v, c + cross(v,t)};}

line shiftLeft(double dist) {return {v, c + dist*abs(v)};}

bool inter(line l1, line l2, pt &out) {
	T d = cross(l1.v, l2.v);
	if (d == 0) return false;
	out = (l2.v*l1.c - l1.v*l2.c) / d; // requires floating-point
	coordinates
	return true;
}

pt proj(pt p) {return p - perp(v)*side(p)/sq(v);}

pt refl(pt p) {return p - perp(v)*2*side(p)/sq(v);}

line bisector(line l1, line l2, bool interior) {
	assert(cross(l1.v, l2.v) != 0); // l1 and l2 cannot be parallel!
	double sign = interior ? 1 : -1;
	return {l2.v/abs(l2.v) + l1.v/abs(l1.v) * sign,
	l2.c/abs(l2.v) + l1.c/abs(l1.v) * sign};
}
