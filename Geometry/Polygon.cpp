double areaTriangle(pt a, pt b, pt c) {
	return abs(cross(b-a, c-a)) / 2.0;
}

double areaPolygon(vector<pt> p) {
	double area = 0.0;
	for (int i = 0, n = p.size(); i < n; i++) {
		area += cross(p[i], p[(i+1)%n]); 
		// wrap back to 0 if i == n - 1
	}
	return abs(area) / 2.0;
}

bool above(pt a, pt p) {
	return p.y >= a.y;
}
// check if [PQ] crosses ray from A
bool crossesRay(pt a, pt p, pt q) {
	return (above(a,q) - above(a,p)) * orient(a,p,q) > 0;
}

bool inPolygon(vector<pt> p, pt a, bool strict = true) {
	int numCrossings = 0;
	for (int i = 0, n = p.size(); i < n; i++) {
		if (onSegment(p[i], p[(i+1)%n], a))
		return !strict;
		numCrossings += crossesRay(a, p[i], p[(i+1)%n]);
	}
	return numCrossings & 1; // inside if odd number of crossings
}

double angleTravelled(pt a, pt p, pt q) {
	double ampli = angle(p-a, q-a);
	if (orient(a,p,q) > 0) return ampli;
	else return -ampli;
}

double angleTravelled(pt a, pt p, pt q) {
	// remainder ensures the value is in [-pi,pi]
	return remainder(arg(q-a) - arg(p-a), 2*M_PI);
}

int windingNumber(vector<pt> p, pt a) {
	double ampli = 0;
	for (int i = 0, n = p.size(); i < n; i++)
		ampli += angleTravelled(a, p[i], p[(i+1)%n]);
	return round(ampli / (2*M_PI));
}

struct angle {
	pt d; int t = 0; // direction and number of full turns	angle t180();

	angle t360() {return {d, t+1};}
	angle t180() {return {d*(-1), t + half(d)};}

	bool operator<(angle a, angle b) {
		return make_tuple(a.t, half(a.d), 0) <
		make_tuple(b.t, half(b.d), cross(a.d,b.d));
	}
};

bool half(pt p) {
	return p.y > 0 || (p.y == 0 && p.x < 0);
}


angle moveTo(angle a, pt newD) {
	// check that segment [DD’] doesn’t go through the origin
	assert(!onSegment(a.d, newD, {0,0}));
	angle b{newD, a.t};
	if (a.t180() < b) // if b more than half a turn bigger
		b.t--; // decrease b by a full turn
	if (b.t180() < a) // if b more than half a turn smaller
		b.t++; // increase b by a full turn
	return b;
}

int windingNumber(vector<pt> p, pt a) {
	angle a{p.back()}; // start at last vertex
	for (pt d : p)
		a = moveTo(a, d); // move to first vertex, second, etc.
	return a.t;
}
