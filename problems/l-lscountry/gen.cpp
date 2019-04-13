#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <stdlib.h>
#include <time.h>

using namespace std;


int main()
{
    srand(time(NULL));

    for (int testcase = 0; testcase < 15; ++testcase) {
        cout << "Generating test " << testcase << endl;
        char filename[100];
        sprintf(filename, "%d.in", testcase);
        /*FILE* out = fopen(filename, "w");
        int n = 5000;
        vector < int > a;
        int v = 0;
        for (int i = 1; i <= n; ++i) {
            v += (rand() % 100000) + 1;
            a.push_back(v);
        }
        random_shuffle(a.begin(), a.end());
        fprintf(out, "%d\n", n);
        for (int x : a) fprintf(out, "%d ", x);
        fprintf(out, "\n");
        for (int i = 0; i < n; ++i) {
            int x = (rand() % 2) + 1;
            fprintf(out, "%d ", x);
        }
        fclose(out);*/

        char ansfilename[100];
        sprintf(ansfilename, "%d.out", testcase);
        char command[200];
        sprintf(command, "../a.out < %s > %s", filename, ansfilename);
        system(command);

        /*sprintf(ansfilename, "%d_tle.out", testcase);
        sprintf(command, "../b.out < %s > %s", filename, ansfilename);
        system(command);*/
    }
    return 0;
}
