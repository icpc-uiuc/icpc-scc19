//package com.company;
// Always comment out package when submitting.

import java.io.*;
import java.util.*;

// C construct
public class construct_zihan {
    public static class Task {

        public void solve(Scanner sc, PrintWriter pw) throws IOException {
            int n = sc.nextInt();
            int W = sc.nextInt();
            Map<Integer, Integer> items = new HashMap<>();
            for (int i = 0; i < n; i++) {
                int p = sc.nextInt();
                items.put(p, items.getOrDefault(p, 0) + 1);
            }
            int[] knapsack = new int[W + 1];
            for (Map.Entry<Integer, Integer> en: items.entrySet()) {
                int singleWeight = en.getKey();
                int count = en.getValue();
                for (int i = 1, sum = 0; sum < count; sum += i, i = Math.min(2 * i, count - sum)) {
                    int size = i * singleWeight;
                    for (int j = W - size; j >= 0; j--) {
                        knapsack[j + size] = Math.max(knapsack[j + size], knapsack[j] + size);
                    }
                }
            }
            pw.println(knapsack[W]);
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