//package com.company;
// Always comment out package when submitting.

import java.io.*;
import java.util.*;

// J juicy
public class juicy_zihan {
    public static class Task {

        public class DisjointUnion {
            int[] arr;
            DisjointUnion(int n) {
                arr = new int[n];
                Arrays.fill(arr, -1);
            }
            int find(int a) {
                return arr[a] == -1 ? a : (arr[a] = find(arr[a]));
            }
            boolean union(int a, int b) {
                int ra = find(a), rb = find(b);
                if (ra == rb) return false;
                arr[ra] = rb;
                return true;
            }
        }

        public class Edge {
            int u;
            int v;
            int h;
            int e;
            double realVal;

            public Edge(int u, int v, int h, int e) {
                this.u = u;
                this.v = v;
                this.h = h;
                this.e = e;
            }

            public void setRatio(double ratio) {
                realVal = h - ratio * e;
            }
        }

        public void solve(Scanner sc, PrintWriter pw) throws IOException {
            int a = sc.nextInt();
            int b = sc.nextInt();
            int m = sc.nextInt();
            List<Edge> edges = new ArrayList<>();
            for (int i = 0; i < m; i++) {
                int u = sc.nextInt() - 1;
                int v = sc.nextInt() - 1;
                int h = sc.nextInt();
                int e = sc.nextInt();
                edges.add(new Edge(u, v, h, e));
            }
            double lo = 0.0, hi = 1e9;
            while (lo < hi - 1e-9) {
                double mid = (lo + hi) / 2;
                for (Edge e: edges) {
                    e.setRatio(mid);
                }
                edges.sort(new Comparator<Edge>() {
                    @Override
                    public int compare(Edge o1, Edge o2) {
                        return Double.compare(o2.realVal, o1.realVal);
                    }
                });
                double bestVal = -9e18;
                for (int i = 0; i < 1 << a; i++) {
                    Set<Integer> forbid = new HashSet<>();
                    for (int j = 0; j < a; j++) {
                        if (((1 << j) & i) != 0) forbid.add(j);
                    }
                    int needEdges = a - forbid.size() + b;
                    double totalVal = 0.0;
                    DisjointUnion djs = new DisjointUnion(a + b + 1);
                    for (Edge e : edges) {
                        if (forbid.contains(e.u) || forbid.contains(e.v)) continue;
                        if (djs.union(e.u, e.v)) {
                            totalVal += e.realVal;
                            needEdges--;
                            if (needEdges == 0) break;
                        }
                    }
                    if (needEdges == 0) {
                        bestVal = Math.max(totalVal, bestVal);
                    }
                }
                if (bestVal >= 0) {
                    lo = mid;
                } else {
                    hi = mid;
                }
            }
            pw.printf("%.6f\n", (lo + hi) / 2);
        }
    }

    // template, actual code is in class Task.
    static long TIME_START, TIME_END;

    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
//        Scanner sc = new Scanner(new FileInputStream("Test.in"));
        PrintWriter pw = new PrintWriter(new BufferedOutputStream(System.out));
//        PrintWriter pw = new PrintWriter(new FileOutputStream("Test.out"));
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