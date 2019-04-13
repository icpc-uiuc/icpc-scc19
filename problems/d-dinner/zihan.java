//package com.company;
// Always comment out package when submitting.

import java.io.*;
import java.math.BigInteger;
import java.util.*;

public class Main {
    public static class Task {

        public static class Point implements Comparable<Point> {
            int x, y;
            int idx;
            boolean inPivot;

            public Point(int x, int y) {
                this.x = x;
                this.y = y;
            }

            public Point copy() {
                return new Point(this.x, this.y);
            }

            public void pivot(Point pivot) {
                if (inPivot) throw new RuntimeException();
                inPivot = true;
                x -= pivot.x;
                y -= pivot.y;
            }

            public void unpivot(Point pivot) {
                if (!inPivot) throw new RuntimeException();
                inPivot = false;
                x += pivot.x;
                y += pivot.y;
            }

            @Override
            public int compareTo(Point o) {
                int z1 = x == 0 && y == 0 ? 1 : 0;
                int z2 = o.x == 0 && o.y == 0 ? 1 : 0;
                if (z2 - z1 != 0) return z2 - z1;
                boolean up1 = y > 0 || (y == 0 && x >= 0);
                boolean up2 = o.y > 0 || (o.y == 0 && o.x >= 0);
                if (up1 != up2) return up1 ? -1 : 1;
                return Long.compare((long) x * o.y, (long) y * o.x);
            }

            @Override
            public String toString() {
                return this.x + " " + this.y;
            }


        }

        int mod = 1_000_000_007;
        public int add(int a, int b) {
            int c = a + b;
            if (c < 0) return c + mod;
            if (c >= mod) return c - mod;
            return c;
        }

        public int findPointWithIdx(Point[] points, int idx) {
            int found = -1;
            for (int i = 0; i < points.length; i++) {
                if (points[i].idx == idx) {
                    if (found != -1) throw new RuntimeException();
                    found = i;
                }
            }
            if (found == -1) throw new RuntimeException();
            return found;

        }

        public boolean isClockWise(Point a, Point b, Point c) { // return angle abc is clockwise or not
            int abX = b.x - a.x;
            int abY = b.y - a.y;
            int bcX = c.x - b.x;
            int bcY = c.y - b.y;
            return (long) abX * bcY < (long) abY * bcX;
        }

        public int solveForSet(Point[] points) {
            int n = points.length;
            if (n <= 2) return 0;
            for (int i = n - 1; i >= 0; i--) { // pivot itself last
                points[i].pivot(points[0]);
                points[i].inPivot = false; // this does not count..
            }
            Arrays.sort(points);
            if (points[0].x != 0 || points[0].y != 0) {
                throw new RuntimeException();
            }
            for (int i = 0; i < n; i++) {
                points[i].idx = i;
            }
            int[][] dp = new int[n][n]; // i, j using side i->j, j -> 0, # of convex polygons
            int sum = 0;
            for (int i = 1; i < n; i++) { // all points with 0 < idx < i are calculated
                Point pivot = points[i].copy();
                for (int j = 0; j < n; j++) {
                    points[j].pivot(pivot);
                }
                Arrays.sort(points);
                int originalStartIdx = findPointWithIdx(points, 0);
                int firstClockWiseIdx = -1;
                for (int shift = 0; shift < n - 1; shift++) {
                    int j = (originalStartIdx + shift);
                    if (j >= n) j -= n - 1;
                    if (isClockWise(points[originalStartIdx], points[0], points[j])) {
                        if (shift == 1) {
                            if (i != 1) {
                                throw new RuntimeException();
                            }
                        }
                        firstClockWiseIdx = j;
                        break;
                    }
                }
                if (firstClockWiseIdx == -1) {
                    if (i != n - 1) {
                        throw new RuntimeException();
                    }
                    break;
                }
                int beforeIdx = originalStartIdx + 1;
                if (beforeIdx >= n) beforeIdx -= n - 1;
                int afterIdx = firstClockWiseIdx;
                int sumBefore = 0;
                while ( afterIdx != originalStartIdx ) {
                    while ( beforeIdx != firstClockWiseIdx && isClockWise(points[beforeIdx], points[0], points[afterIdx]) ) {
                        sumBefore = add(sumBefore, dp[points[beforeIdx].idx][points[0].idx]);
                        beforeIdx += 1;
                        if (beforeIdx >= n) beforeIdx -= n - 1;
                    }
                    dp[points[0].idx][points[afterIdx].idx] = add(add(dp[points[0].idx][points[afterIdx].idx], sumBefore), 1);
                    sum = add(sum, dp[points[0].idx][points[afterIdx].idx]);
                    afterIdx += 1;
                    if (afterIdx >= n) afterIdx -= n - 1;
                }

                for (int j = 0; j < n; j++) {
                    points[j].unpivot(pivot);
                }
                Arrays.sort(points, new Comparator<Point>() {
                    @Override
                    public int compare(Point p1, Point p2) {
                        return p1.idx - p2.idx;
                    }
                });
            }
            return sum;
        }

        public int calc(Point[] points) {
            Arrays.sort(points, new Comparator<Point>() {
                @Override
                public int compare(Point p1, Point p2) {
                    return p1.x - p2.x;
                }
            });
            int sol = 0;
            for (int i = 0; i < points.length; i++) {
                Point[] activePointSet = new Point[points.length - i];
                for (int j = i; j < points.length; j++) {
                    activePointSet[j - i] = points[j].copy();
                }
                sol = add(sol, solveForSet(activePointSet));
            }
            return sol;
        }

        public static boolean onSameLine(Point a, Point b, Point c) {
            int abX = b.x - a.x;
            int abY = b.y - a.y;
            int bcX = c.x - b.x;
            int bcY = c.y - b.y;
            return (long) abX * bcY == (long) abY * bcX;
        }

        public static class TestCase {
            int MAX_ABS = 1000000;
            Random rnd = new Random();
            public TestCase() {

            }
            public int randomInt() {
                int x = rnd.nextInt(MAX_ABS * 2 + 1);
                return x - MAX_ABS;
            }
            public Point[] randomPoints(int n) {
                Point[] points = new Point[n];
                for (int i = 0; i < n; i++) {
                    points[i] = new Point(randomInt(), randomInt());
                }
                return points;
            }
            public Point[] convexHull(Point[] points) {
                Arrays.sort(points, (a, b) -> Integer.compare(a.x, b.x) != 0 ? Integer.compare(a.x, b.x) : Integer.compare(a.y, b.y));
                int n = points.length;
                Point[] hull = new Point[n * 2];
                int cnt = 0;
                for (int i = 0; i < 2 * n; i++) {
                    int j = i < n ? i : 2 * n - 1 - i;
                    while (cnt >= 2 && removeMiddle(hull[cnt - 2], hull[cnt - 1], points[j]))
                        --cnt;
                    hull[cnt++] = points[j];
                }
                return Arrays.copyOf(hull, cnt - 1);
            }

            boolean removeMiddle(Point a, Point b, Point c) {
                long cross = (long) (a.x - b.x) * (c.y - b.y) - (long) (a.y - b.y) * (c.x - b.x);
                long dot = (long) (a.x - b.x) * (c.x - b.x) + (long) (a.y - b.y) * (c.y - b.y);
                return cross < 0 || cross == 0 && dot <= 0; // cross == 0 && dot <= 0 removes(b) a -> b -> c on a same line
            }

            public Point[] convexPointsWithRandom(int n) {
                int SIZE = 100 * n;
                for (int tries = 0; tries < 5; tries++) {
                    Point[] points = generateRandomConvexPolygon(SIZE);
                    Point[] convex = convexHull(points);
                    for (int i = 0; i < convex.length; i++) {
                        int x = rnd.nextInt(convex.length - i) + i;
                        Point t = convex[x];
                        convex[x] = convex[i];
                        convex[i] = t;
                    }
                    if (convex.length >= n) {
                        return Arrays.copyOf(convex, n);
                    }
                }
                throw new RuntimeException("Too many tries..");
            }

            private Point[] generateRandomConvexPolygon(int n) {
                // Generate two lists of random X and Y coordinates
                List<Integer> xPool = new ArrayList<>(n);
                List<Integer> yPool = new ArrayList<>(n);

                for (int i = 0; i < n; i++) {
                    xPool.add(randomInt());
                    yPool.add(randomInt());
                }

                // Sort them
                Collections.sort(xPool);
                Collections.sort(yPool);

                // Isolate the extreme points
                int minX = xPool.get(0);
                int maxX = xPool.get(n - 1);
                int minY = yPool.get(0);
                int maxY = yPool.get(n - 1);

                // Divide the interior points into two chains & Extract the vector components
                List<Integer> xVec = new ArrayList<>(n);
                List<Integer> yVec = new ArrayList<>(n);

                int lastTop = minX, lastBot = minX;

                for (int i = 1; i < n - 1; i++) {
                    int x = xPool.get(i);

                    if (rnd.nextBoolean()) {
                        xVec.add(x - lastTop);
                        lastTop = x;
                    } else {
                        xVec.add(lastBot - x);
                        lastBot = x;
                    }
                }

                xVec.add(maxX - lastTop);
                xVec.add(lastBot - maxX);

                int lastLeft = minY, lastRight = minY;

                for (int i = 1; i < n - 1; i++) {
                    int y = yPool.get(i);

                    if (rnd.nextBoolean()) {
                        yVec.add(y - lastLeft);
                        lastLeft = y;
                    } else {
                        yVec.add(lastRight - y);
                        lastRight = y;
                    }
                }

                yVec.add(maxY - lastLeft);
                yVec.add(lastRight - maxY);

                // Randomly pair up the X- and Y-components
                Collections.shuffle(yVec);

                // Combine the paired up components into vectors
                List<Point> vec = new ArrayList<>(n);

                for (int i = 0; i < n; i++) {
                    vec.add(new Point(xVec.get(i), yVec.get(i)));
                }

                // Sort the vectors by angle
                Collections.sort(vec, Comparator.comparingDouble(v -> Math.atan2(v.y, v.x)));

                // Lay them end-to-end
                int x = 0, y = 0;
                int minPolygonX = 0;
                int minPolygonY = 0;
                List<Point> points = new ArrayList<>(n);

                for (int i = 0; i < n; i++) {
                    points.add(new Point(x, y));

                    x += vec.get(i).x;
                    y += vec.get(i).y;

                    minPolygonX = Math.min(minPolygonX, x);
                    minPolygonY = Math.min(minPolygonY, y);
                }

                // Move the polygon to the original min and max coordinates
                int xShift = minX - minPolygonX;
                int yShift = minY - minPolygonY;
                Point[] ret = new Point[points.size()];
                for (int i = 0; i < n; i++) {
                    Point p = points.get(i);
                    ret[i] = new Point(p.x + xShift, p.y + yShift);
                }

                return ret;
            }

            public int[][] generateRandomTestCase(int n, boolean convex) {
                for (int tries = 0; tries < 5; tries++) {
                    int SIZE = n * 2;
                    Point[] points = convex ? convexPointsWithRandom(SIZE): randomPoints(SIZE);
                    boolean[] bad = new boolean[SIZE];
                    for (int i = 0; i < SIZE; i++) {
                        for (int j = i + 1; j < SIZE; j++) {
                            if (points[i].x == points[j].x || points[i].y == points[j].y) {
                                bad[j] = true;
                            }
                        }
                    }
                    for (int i = 0; i < SIZE; i++) {
                        for (int j = i + 1; j < SIZE; j++) {
                            for (int k = j + 1; k < SIZE; k++) {
                                if (onSameLine(points[i], points[j], points[k])) {
                                    bad[k] = true;
                                }
                            }
                        }
                    }
                    int countBad = 0;
                    for (int i = 0; i < SIZE; i++) {
                        if (bad[i]) countBad++;
                    }
                    if (SIZE - countBad >= n) {
                        int[][] ret = new int[n][2];
                        int idx = 0;
                        for (int i = 0; i < SIZE; i++) {
                            if (!bad[i]) {
                                ret[idx][0] = points[i].x;
                                ret[idx++][1] = points[i].y;
                            }
                            if (idx == n) break;
                        }
                        return ret;
                    }
                }
                throw new RuntimeException("Too many tries..");
            }
        }

        public void solve(Scanner sc, PrintWriter pw) throws IOException {
            int n = sc.nextInt();
            Point[] points = new Point[n];
            Set<Integer> rangeX = new HashSet<>();
            Set<Integer> rangeY = new HashSet<>();
            for (int i = 0; i < n; i++) {
                int x = sc.nextInt();
                int y = sc.nextInt();
                if (rangeX.contains(x) || rangeY.contains(y)) throw new RuntimeException();
                rangeX.add(x);
                rangeY.add(y);
                points[i] = new Point(x, y);
            }
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    for (int k = j + 1; k < n; k++) {
                        if (onSameLine(points[i], points[j], points[k])) {
                            throw new RuntimeException();
                        }
                    }
                }
            }
            pw.println(calc(points));
        }
    }

    // template, actual code is in class Task.
    static long TIME_START, TIME_END;

    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
//        Scanner sc = new Scanner(new FileInputStream("Test.in"));
        PrintWriter pw = new PrintWriter(new BufferedOutputStream(System.out));
//        PrintWriter pw = new PrintWriter(new FileOutputStream("Test.out"));

//        createTestCases();
        Runtime runtime = Runtime.getRuntime();
        long usedMemoryBefore = runtime.totalMemory() - runtime.freeMemory();
        TIME_START = System.currentTimeMillis();
        Task t = new Task();
        t.solve(sc, pw);
        TIME_END = System.currentTimeMillis();
        long usedMemoryAfter = runtime.totalMemory() - runtime.freeMemory();
        pw.close();
//        System.err.println("Memory increased: " + (usedMemoryAfter - usedMemoryBefore) / 1000000);
//        System.err.println("Time used: " + (TIME_END - TIME_START) + ".");
    }

    static int testCase = 4;
    public static void createTestCase(int[][] points) {
        try {
            PrintWriter pw = new PrintWriter("testm/" + testCase + ".in");
            if (points.length < 3 || points.length > 100) {
                throw new RuntimeException();
            }
            pw.println(points.length);
            for (int[] point : points) {
                int x = Math.abs(point[0]);
                int y = Math.abs(point[1]);
                if (Math.abs(x) > 1_000_000 || Math.abs(y) > 1_000_000) {
                    throw new RuntimeException();
                }
                pw.println(x + " " + y);
            }
            pw.close();
            testCase += 1;
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    public static void createTestCases() {
        Task.TestCase tc = new Task.TestCase();
        for (int i = 0; i < 10; i++) {
            createTestCase(tc.generateRandomTestCase(20, false));
        }
        for (int i = 0; i < 10; i++) {
            createTestCase(tc.generateRandomTestCase(20, true));
        }
        for (int i = 0; i < 10; i++) {
            createTestCase(tc.generateRandomTestCase(100, false));
        }
        for (int i = 0; i < 7; i++) {
            createTestCase(tc.generateRandomTestCase(100, true));
        }

    }


    // Faster IO with BufferedReader wrapped with Scanner
    static class Scanner {
        StringTokenizer st;
        BufferedReader br;

        public Scanner(InputStream s) {
            br = new BufferedReader(new InputStreamReader(s));
        }

        public Scanner(FileReader s) throws FileNotFoundException {
            br = new BufferedReader(s);
        }

        public String next() throws IOException {
            while (st == null || !st.hasMoreTokens())
                st = new StringTokenizer(br.readLine());
            return st.nextToken();
        }

        public int nextInt() throws IOException {
            return Integer.parseInt(next());
        }

        public long nextLong() throws IOException {
            return Long.parseLong(next());
        }

        public String nextLine() throws IOException {
            return br.readLine();
        }

        public double nextDouble() throws IOException {
            return Double.parseDouble(next());
        }

        public boolean ready() throws IOException {
            return br.ready();
        }
    }
}