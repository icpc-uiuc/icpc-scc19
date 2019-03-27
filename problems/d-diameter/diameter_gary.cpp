// Geometry

#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>
#include <deque>

using namespace std;

double EPS = 1e-8;
double PI = acos(-1.0);

bool equal (double x, double y) { return fabs(x - y) < EPS; }
int sign (double x) {
	if (equal(x, 0.0)) return 0;
	return x > 0.0 ? 1 : -1;
}

struct Point {
	double x, y;

	Point (double x, double y) : x(x), y(y) {}

	friend bool operator== (Point p, Point q) { return equal(p.x, q.x) && equal(p.y, q.y); }
	friend Point operator+ (Point p, Point q) { return Point(p.x + q.x, p.y + q.y); }
	friend Point operator- (Point p, Point q) { return Point(p.x - q.x, p.y - q.y); }
	friend Point operator* (Point p, double k) { return Point(p.x * k, p.y * k); }
	friend Point operator/ (Point p, double k) { return p * (1.0 / k); }

	static double arg (Point p) { return atan2(p.y, p.x); }
	static double norm (Point p) { return sqrt(p.x * p.x + p.y * p.y); }
	static double dot (Point p, Point q) { return p.x * q.x + p.y * q.y; }
	static double cross (Point p, Point q) { return p.x * q.y - q.x * p.y; }
	static double dist (Point p, Point q) { return norm(p - q); }
	static double det (Point p, Point q, Point r) { return cross(q-p, r-p); }
	static Point rotate (Point p, double theta) {
		return Point(p.x * cos(theta) - p.y * sin(theta), p.x * sin(theta) + p.y * cos(theta));
	}

	/* triangle */
	static Point mass_center (Point p1, Point p2, Point p3) {
		return (p1 + p2 + p3) / 3.0;
	}
	static Point outer_center (Point p1, Point p2, Point p3) {
		double a1 = p2.x - p1.x, b1 = p2.y - p1.y, c1 = (a1*a1+b1*b1) / 2.0;
		double a2 = p3.x - p1.x, b2 = p3.y - p1.y, c2 = (a2*a2+b2*b2) / 2.0;
		double d = a1 * b2 - a2 * b1;
		double x = p1.x + (c1*b2 - c2*b1) / d;
		double y = p1.y + (a1*c2 - a2*c1) / d;
		return Point(x, y);
	}
	static Point outer_center (Point p1, Point p2) {
		return (p1 + p2) / 2.0;
	}
	static Point ortho_center (Point p1, Point p2, Point p3) {
		return mass_center(p1, p2, p3) * 3.0 - outer_center(p1, p2, p3) * 2.0;
	}
	static Point inner_center (Point p1, Point p2, Point p3) {
		double a = dist(p2, p3);
		double b = dist(p3, p1);
		double c = dist(p1, p2);
		return (p1 * a + p2 * b + p3 * c) / (a + b + c);
	}
	/* triangle */

	// divide and conquer: O(nlogn)
	// tested on HDU 1007
	static pair<double,pair<Point,Point>> closest_pair (vector<Point> ps) {
		int n = ps.size();
		vector<int> rank(n);
		for (int i = 0; i < n; i++) rank[i] = i;
		sort(rank.begin(), rank.end(), [&ps](int i, int j) -> bool { return ps[i].x < ps[j].x; });
		return closest_pair(ps, rank, 0, n);
	}
	static pair<double,pair<Point,Point>> closest_pair (vector<Point> &ps, vector<int> &rank, int l, int r) {
		auto ans_cmp = [](pair<double,pair<Point,Point>> i, pair<double,pair<Point,Point>> j) -> bool { return i.first < j.first; };
		if (r - l < 20) {
			pair<double,pair<Point,Point>> ans = {0x7fffffff, {Point(0,0), Point(0,0)}};
			for (int i = l; i < r; i++) {
				for (int j = i+1; j < r; j++) {
					if (ans.first > dist(ps[rank[i]], ps[rank[j]])) {
						ans = {dist(ps[rank[i]], ps[rank[j]]), {ps[rank[i]], ps[rank[j]]}};
					}
				}
			}
			return ans;
		}
		int mid = (l + r) / 2;
		auto ans = min(closest_pair(ps, rank, l, mid), closest_pair(ps, rank, mid, r), ans_cmp);
		int tl; for (tl = l; ps[rank[tl]].x < ps[rank[mid]].x - ans.first; tl++);
		int tr; for (tr = r-1; ps[rank[tr]].x > ps[rank[mid]].x + ans.first; tr--);
		sort(rank.begin()+tl, rank.begin()+tr, [&ps](int i, int j) -> bool { return ps[i].y < ps[j].y; });
		for (int i = tl; i < tr; i++) {
			for (int j = i+1; j < min(tr, i+6); j++) {
				if (ans.first > dist(ps[rank[i]], ps[rank[j]])) {
					ans = {dist(ps[rank[i]], ps[rank[j]]), {ps[rank[i]], ps[rank[j]]}};
				}
			}
		}
		sort(rank.begin()+tl, rank.begin()+tr, [&ps](int i, int j) -> bool { return ps[i].x < ps[j].x; });
		return ans;
	}

	// farthest pair in a convex hull
	// DEBUG: maybe not good at when all points are colinear
	// tested on POJ 2187
	static pair<double,pair<Point,Point>> farthest_pair (vector<Point> &ps) {
		auto ans_cmp = [](pair<double,pair<Point,Point>> i, pair<double,pair<Point,Point>> j) -> bool { return i.first < j.first; };
		int n = ps.size();
		pair<double,pair<Point,Point>> ans = {0.0, {Point(0,0), Point(0,0)}};
		if (n == 1) return ans;
		for (int i = 0, j = 1; i < n; i++) {
			while (sign(det(ps[i], ps[(i+1)%n], ps[j]) - det(ps[i], ps[(i+1)%n], ps[(j+1)%n])) == -1) {
				j = (j+1)%n;
			}
			ans = max(ans, {dist(ps[i], ps[j]), {ps[i], ps[j]}}, ans_cmp);
			ans = max(ans, {dist(ps[(i+1)%n], ps[(j+1)%n]), {ps[(i+1)%n], ps[(j+1)%n]}}, ans_cmp);
		}
		return ans;
	}

	// Graham scan: O(nlogn); result in counter-clockwise
	// tested on POJ 2187 indirectly
	static vector<Point> convex_hull (vector<Point> &ps) {
		int n = ps.size();
		if (n < 3) return ps;
		for (int i = 1; i < n; i++) {
			if (ps[0].y > ps[i].y || (ps[0].y == ps[i].y && ps[0].x > ps[i].x)) {
				swap(ps[0], ps[i]);
			}
		}
		Point base = ps[0];
		sort(ps.begin()+1, ps.end(), [&](Point p, Point q) -> bool { return sign(det(base, p, q)) > 0 || (sign(det(base, p, q)) == 0 && dist(base, p) < dist(base, q)); });
		vector<Point> ans = {ps[0], ps[1], ps[2]};
		for (int i = 3; i < n; i++) {
			while (ans.size() >= 2 && sign(det(ans[ans.size()-1], ans[ans.size()-2], ps[i])) >= 0) ans.pop_back();
			ans.push_back(ps[i]);
		}
		return ans;
	}
};

struct Line {
	Point a, b;

	Line (Point a, Point b) : a(a), b(b) {}

	static double dist (Line l, Point p) {
		return fabs(Point::det(p, l.a, l.b) / Point::dist(l.a, l.b));
	}

	static Point proj (Line l, Point p) {
		double r = Point::dot(l.b - l.a, p - l.a) / Point::dot(l.b - l.a, l.b - l.a);
		return l.a * (1 - r) + l.b * r;
	}

	static bool on_segment (Line l, Point p) {
		return sign(Point::det(p, l.a, l.b)) == 0 && sign(Point::dot(p - l.a, p - l.b)) <= 0;
	}

	static bool parallel (Line l, Line m) {
		return sign(Point::cross(l.a - l.b, m.a - m.b)) == 0;
	}

	static Point line_x_line (Line l, Line m) {
		double s1 = Point::det(m.a, l.a, m.b);
		double s2 = Point::det(m.a, l.b, m.b);
		return (l.b * s1 - l.a * s2) / (s1 - s2);
	}

	static bool two_segments_intersect (Line l, Line m) {
		double dla = Point::det(l.b, m.a, m.b);
		double dlb = Point::det(l.a, m.a, m.b);
		double dma = Point::det(m.b, l.a, l.b);
		double dmb = Point::det(m.a, l.a, l.b);
		if (sign(dla * dlb) == -1 && sign(dma * dmb) == -1) return true;
		if (sign(dla) == 0 && on_segment(m, l.b)) return true;
		if (sign(dlb) == 0 && on_segment(m, l.a)) return true;
		if (sign(dma) == 0 && on_segment(l, m.b)) return true;
		if (sign(dmb) == 0 && on_segment(l, m.a)) return true;
		return false;
	}

	static bool any_segments_intersect (vector<Line> ls) {
		vector<pair<Point,pair<int,int>>> items;
		for (int i = 0; i < ls.size(); i++) {
			Line &l = ls[i];
			if (l.a.x > l.b.x) swap(l.a, l.b);
			items.push_back({l.a, {0, i}});
			items.push_back({l.b, {1, i}});
		}
		sort(items.begin(), items.end(), [](pair<Point,pair<int,int>> a, pair<Point,pair<int,int>> b) -> bool {
			if (sign(a.first.x - b.first.x) == -1) return true;
			if (sign(a.first.x - b.first.x) == 1) return false;
			if (a.second.first < b.second.first) return true;
			if (a.second.first > b.second.first) return false;
			return a.first.y < b.first.y;
		});
		auto cmp = [&](int i, int j) -> bool { return ls[i].a.y < ls[j].a.y; };
		set<int,decltype(cmp)> s(cmp);
		for (auto &item : items) {
			if (item.second.first == 0) {
				auto it = s.insert(item.second.second).first;
				int id = *it;
				int prev_id = (it == s.begin()) ? -1 : *(prev(it));
				int next_id = (next(it) == s.end()) ? -1 : *(next(it));
				if (prev_id != -1 && two_segments_intersect(ls[id], ls[prev_id])) return true;
				if (next_id != -1 && two_segments_intersect(ls[id], ls[next_id])) return true;
			} else {
				auto it = s.find(item.second.second);
				int id = *it;
				int prev_id = (it == s.begin()) ? -1 : *(prev(it));
				int next_id = (next(it) == s.end()) ? -1 : *(next(it));
				if (prev_id != -1 && next_id != -1 && two_segments_intersect(ls[prev_id], ls[next_id])) return true;
				s.erase(it);
			}
		}
		return false;
	}
};

struct HalfPlane {
	Point s, t;  // half plane on the left of ray from p to q
	HalfPlane (Point s, Point t) : s(s), t(t) {}

	double eval (Point p) {
		double a, b, c;  // ax+by+c<=0
		a = t.y - s.y;
		b = s.x - t.x;
		c = Point::cross(t, s);
		return p.x * a + p.y * b + c;
	}

	static Point halfplane_x_line (HalfPlane hp, Line l) {
		Point p = l.a, q = l.b;
		double vp = hp.eval(p), vq = hp.eval(q);
		double x = (vq * p.x - vp * q.x) / (vq - vp);
		double y = (vq * p.y - vp * q.y) / (vq - vp);
		return Point(x, y);
	}

	static vector<Point> halfplanes_x (vector<HalfPlane> hps) {
		sort(hps.begin(), hps.end(), [](HalfPlane a, HalfPlane b) -> bool {
			int sgn = sign(Point::arg(a.t - a.s) - Point::arg(b.t - b.s));
			return sgn == 0 ? (sign(b.eval(a.s)) == -1) : (sgn < 0);
		});
		deque<HalfPlane> q {hps[0]};
		deque<Point> ans;
		for (int i = 1; i < hps.size(); i++) {
			if (sign(Point::arg(hps[i].t - hps[i].s) - Point::arg(hps[i-1].t - hps[i-1].s)) == 0) continue;
			while (ans.size() > 0 && sign(hps[i].eval(ans.back())) == 1) { ans.pop_back(); q.pop_back(); }
			while (ans.size() > 0 && sign(hps[i].eval(ans.front())) == 1) { ans.pop_front(); q.pop_front(); }
			ans.push_back(Line::line_x_line(Line(q.back().s, q.back().t), Line(hps[i].s, hps[i].t)));
			q.push_back(hps[i]);
		}
		while (ans.size() > 0 && sign(q.front().eval(ans.back())) == 1) { ans.pop_back(); q.pop_back(); }
		while (ans.size() > 0 && sign(q.back().eval(ans.front())) == 1) { ans.pop_front(); q.pop_front(); }
		ans.push_back(Line::line_x_line(Line(q.back().s, q.back().t), Line(q.front().s, q.front().t)));
		return vector<Point>(ans.begin(), ans.end());
	}
};

struct Polygon {
	int n;
	vector<Point> p;  // always counter-clockwise

	Polygon (vector<Point> p) : p(p), n(p.size()) {}

	double perimeter () {
		double ans = 0;
		for (int i = 0; i < n; i++) {
			ans += Point::dist(p[i], p[(i+1)%n]);
		}
		return ans;
	}

	double area () {
		double ans = 0;
		for (int i = 1; i < n-1; i++) {
			ans += Point::det(p[0], p[i], p[i+1]) / 2.0;
		}
		return ans;
	}

	Point mass_center () {
		Point ans(0.0, 0.0);
		double a = area();
		if (sign(a) == 0) return ans;
		for (int i = 1; i < n-1; i++) {
			ans = ans + ((p[0] + p[i] + p[i+1]) / 3.0) * (Point::det(p[0], p[i], p[i+1]) / 2.0);
		}
		return ans / a;
	}

	// first is grid point inside polygon; second is grid point on edge. vertices has to be grid points
	pair<int,int> grid_point_cnt () {
		int first = 0, second = 0;
		for (int i = 0; i < n; i++) {
			second += gcd(abs((int)(p[(i+1)%n].x - p[i].x)), abs((int)(p[(i+1)%n].y - p[i].y)));
		}
		first = (int)area() + 1 - second / 2;
		return {first, second};
	}
	int gcd(int p, int q) { return q == 0 ? p : gcd(q, p%q); }

	bool is_simple_convex_polygon () {
		for (int i = 0; i < n; i++) {  // convexity
			if (sign(Point::det(p[i], p[(i+1)%n], p[(i+2)%n])) == -1) return false;
		}
		for (int i = 1; i < n-1; i++) {  // simplicity
			if (sign(Point::det(p[0], p[i], p[i+1])) == -1) return false;
		}
		return true;
	}

	// O(n)
	// returns 1 for in, 0 for on, -1 for out
	static int point_in_polygon (Polygon po, Point p0) {
		int cnt = 0;
		for (int i = 0; i < po.n; i++) {
			if (Line::on_segment(Line(po.p[i], po.p[(i+1)%po.n]), p0)) return 0;
			int k = sign(Point::det(p0, po.p[i], po.p[(i+1)%po.n]));
			int d1 = sign(po.p[i].y - p0.y);
			int d2 = sign(po.p[(i+1)%po.n].y - p0.y);
			if (k == 1 && d1 != 1 && d2 == 1) cnt++;
			if (k == -1 && d2 != 1 && d1 == 1) cnt--;
		}
		return cnt ? 1 : -1;
	}

	// O(log(n))
	// returns 1 for in, 0 for on, -1 for out
	static int point_in_convex_polygon (Polygon po, Point p0) {
		Point point = (po.p[0] + po.p[po.n/3] + po.p[2*po.n/3]) / 3.0;
		int l = 0, r = po.n;
		while (r - l > 1) {
			int mid = (l + r) / 2;
			if (sign(Point::det(point, po.p[l], po.p[mid])) == 1) {
				if (sign(Point::det(point, po.p[l], p0)) != -1 && sign(Point::det(point, po.p[mid], p0)) == -1) r = mid;
				else l = mid;
			} else {
				if (sign(Point::det(point, po.p[l], p0)) == -1 && sign(Point::det(point, po.p[mid], p0)) != -1) l = mid;
				else r = mid;
			}
		}
		r %= po.n;
		return -sign(Point::det(p0, po.p[r], po.p[l]));
	}

	Polygon convex_polygon_x_halfplane (HalfPlane hp, Polygon po) {
		vector<Point> ps;
		for (int i = 0; i < po.n; i++) {
			if (sign(hp.eval(po.p[i])) == -1) {
				ps.push_back(po.p[i]);
			} else {
				if (sign(hp.eval(po.p[(i-1+po.n)%po.n])) == -1) {
					ps.push_back(HalfPlane::halfplane_x_line(hp, Line(po.p[i], po.p[(i-1+po.n)%po.n])));
				}
				if (sign(hp.eval(po.p[(i+1)%po.n])) == -1) {
					ps.push_back(HalfPlane::halfplane_x_line(hp, Line(po.p[i], po.p[(i+1)%po.n])));
				}
			}
		}
		return Polygon(ps);
	}

	static Polygon convex_polygon_x_convex_polygon (Polygon po1, Polygon po2) {
		vector<HalfPlane> hps;
		for (int i = 0; i < po1.n; i++) {
			hps.push_back(HalfPlane(po1.p[i], po1.p[(i+1)%po1.n]));
		}
		for (int i = 0; i < po2.n; i++) {
			hps.push_back(HalfPlane(po2.p[i], po2.p[(i+1)%po2.n]));
		}
		return Polygon(HalfPlane::halfplanes_x(hps));
	}
};

struct Circle {
	Point center;
	double radius;

	Circle (Point center, double radius) : center(center), radius(radius) {}

	static bool in_circle (Circle c, Point p) {
		return sign(Point::dist(p, c.center) - c.radius) == -1;
	}

	static Circle min_circle_cover (vector<Point> p) {
		Circle ans(p[0], 0.0);
		random_shuffle(p.begin(), p.end());
		for (int i = 1; i < p.size(); i++) if (!in_circle(ans, p[i])) {
			ans.center = p[i]; ans.radius = 0;
			for (int j = 0; j < i; j++) if (!in_circle(ans, p[j])) {
				ans.center = Point::outer_center(p[i], p[j]);
				ans.radius = Point::dist(p[j], ans.center);
				for (int k = 0; k < j; k++) if (!in_circle(ans, p[k])) {
					ans.center = Point::outer_center(p[i], p[j], p[k]);
					ans.radius = Point::dist(p[k], ans.center);
				}
			}
		}
		return ans;
	}
};

// AB AC AD BC BD CD
double simplex_volume (double l, double n, double a, double m, double b, double c) {
	double x = 4*a*a*b*b*c*c - a*a*(b*b+c*c-m*m)*(b*b+c*c-m*m) - b*b*(c*c+a*a-n*n)*(c*c+a*a-n*n);
	double y = c*c*(a*a+b*b-l*l)*(a*a+b*b-l*l) - (a*a+b*b-l*l)*(b*b+c*c-m*m)*(c*c+a*a-n*n);
	return sqrt(x-y) / 12;
}

vector<Point> vp;

int main () {
  int n, k; cin >> n >> k;
  for (int i = 0; i < k; i++) {
    int m; cin >> m;
    while (m--) {
      double x, y; cin >> x >> y;
      vp.emplace_back(x, y);
    }
  }
  bool all_colinear = true;
  for (int i = 2; i < n; i++) {
    if (sign(Point::det(vp[0], vp[1], vp[i])) != 0) all_colinear = false;
  }
  if (all_colinear) {
    sort(vp.begin(), vp.end(), [](Point &p, Point &q) -> bool {
      if (p.x < q.x) return true;
      if (p.x > q.x) return false;
      return p.y < q.y;
      });
    long long dx = (long long)vp[0].x - (long long)vp[n-1].x;
    long long dy = (long long)vp[0].y - (long long)vp[n-1].y;
    long long ans = dx * dx + dy * dy;
    cout << ans << endl;
  } else {
    auto ch = Point::convex_hull(vp);
    auto ret = Point::farthest_pair(ch);
    auto p1 = ret.second.first, p2 = ret.second.second;
    long long dx = (long long)p1.x - (long long)p2.x;
    long long dy = (long long)p1.y - (long long)p2.y;
    long long ans = dx * dx + dy * dy;
    cout << ans << endl;
  }

  return 0;
}

