//package com.company;
// Always comment out package when submitting.

import java.io.*;
import java.util.*;

// D diameter
public class diameter_zihan {
    public static class Task {

        public void solve(Scanner sc, PrintWriter pw) throws IOException {
            int n = sc.nextInt();
            int k = sc.nextInt();
            int[][] crucial = new int[2 * k][2];
            for (int i = 0; i < k; i++) {
                int m = sc.nextInt();
                int[][] points = new int[m][2];
                for (int j = 0; j < m; j++) {
                    for (int l = 0; l < 2; l++) {
                        points[j][l] = sc.nextInt();
                    }
                }
                Arrays.sort(points, new Comparator<int[]>() {
                    @Override
                    public int compare(int[] o1, int[] o2) {
                        if (o1[0] == o2[0]) {
                            return Integer.compare(o1[1], o2[1]);
                        }
                        return Integer.compare(o1[0], o2[0]);
                    }
                });
                crucial[i << 1] = points[0];
                crucial[i << 1 | 1] = points[m - 1];
            }
            long maxDist = -1;
            for (int i = 0; i < 2 * k; i++) {
                for (int j = i + 1; j < 2 * k; j++) {
                    long sum = 0;
                    for (int l = 0; l < 2; l++) {
                        int diff = crucial[i][l] - crucial[j][l];
                        sum += (long) diff * diff;
                    }
                    maxDist = Math.max(maxDist, sum);
                }
            }
            pw.println(maxDist);
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