#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

#define M(x) ((x)%1000000007)

struct Mem
{
    int N;//кол-во вершин
    int H;//глубина дерева
    int kol;
};

void Inital(vector<vector<unsigned int>>& CountBlack, vector<vector<unsigned int>>& CountRed, int N)
{
    /*Mem a;
    a.N=1; a.H=0; a.kol=1;
    CountBlack.push_back(a);
    CountRed.push_back(a);

    a.N=2; a.H=0; a.kol=0;
    CountBlack.push_back(a);
    CountRed.push_back(a);

    a.N=3; a.H=1; a.kol=1;
    CountBlack.push_back(a);
    a.N=3; a.H=0; a.kol=1;
    CountRed.push_back(a);

    a.N=4; a.H=0; a.kol=0;
    CountBlack.push_back(a);
    CountRed.push_back(a);*/

    /*CountBlack.resize(5);
    CountBlack[0].push_back(0);//N=0, H=0, kol=0
    CountBlack[1].push_back(1);//N=1, H=0, kol=1
    CountBlack[2].push_back(0);//N=2, H=0, kol=0
    CountBlack[3].push_back(0);//N=3, H=0, kol=0
    CountBlack[3].push_back(1);//N=3, H=1, kol=1
    CountBlack[4].push_back(0);//N=3, H=1, kol=1

    CountRed.resize(5);
    CountRed[0].push_back(0);//N=0, H=0, kol=0
    CountRed[1].push_back(0);//N=1, H=0, kol=0
    CountRed[2].push_back(0);//N=2, H=0, kol=0
    CountRed[3].push_back(1);//N=3, H=0, kol=1
    CountRed[4].push_back(0);//N=3, H=0, kol=1*/

    int Hmax = ceil(2*log2(N+1));
    CountBlack.resize(std::max(N+1, 4), vector<unsigned int>(Hmax+1, 0));
    CountRed.  resize(std::max(N+1, 4), vector<unsigned int>(Hmax+1, 0));
    CountBlack[1][0] = 1;
    CountBlack[3][1] = 1;
    CountRed[3][0] = 1;
    /*CountBlack[0].push_back(0);//N=0, H=0, kol=0
    CountBlack[1].push_back(1);//N=1, H=0, kol=1
    CountBlack[2].push_back(0);//N=2, H=0, kol=0
    CountBlack[3].push_back(0);//N=3, H=0, kol=0
    CountBlack[3].push_back(1);//N=3, H=1, kol=1

    CountRed.resize(4);
    CountRed[0].push_back(0);//N=0, H=0, kol=0
    CountRed[1].push_back(0);//N=1, H=0, kol=0
    CountRed[2].push_back(0);//N=2, H=0, kol=0
    CountRed[3].push_back(1);//N=3, H=0, kol=1*/



}

int main() {
    vector<vector<unsigned int>> CountBlack;
    vector<vector<unsigned int>> CountRed;
    int N;
    cin>>N;

    Inital(CountBlack, CountRed, N);

    for (int n = 4; n <= N; n++) {
        for (int h = 1; h <= ceil(2*log2(N+1)); h++){
            unsigned long Count_black = 0;
            for (int i = 1; i-1 <= n-i; i++) {
                unsigned long CountLeft = (CountBlack[i - 1][h - 1]) + (CountRed[i - 1][h - 1]);
                unsigned long CountRight = (CountBlack[n - i][h - 1]) + (CountRed[n - i][h - 1]);
                if (i - 1 == n - i) {
                    Count_black += M(M(CountLeft) * M(CountLeft + 1) / 2);
                } else {
                    Count_black += M(M(CountLeft) * M(CountRight));
                }
            }
            CountBlack[n][h] = M(Count_black);
            unsigned long Count_Red = 0;
            for (int i = 1; i-1 <= n-i; i++) {
                unsigned long CountLeft = (CountBlack[i-1][h]);
                unsigned long CountRight = (CountBlack[n - i][h]);

                if (i-1 == n - i)
                {
                    Count_Red += M(M(CountLeft) * M(CountLeft + 1) / 2);
                }
                else {
                    Count_Red += M(M(CountLeft) * M(CountRight));
                }
            }
            CountRed[n][h] = M(Count_Red);
        }
    }

    unsigned int kol = 0;

    for (int i = 0; i < CountBlack[N].size(); i++) {
        kol += M(CountBlack[N][i]);
        kol = M(kol);
    }

    //unsigned long long kol1 = fmod(kol, MOD);



    //cout << kol1 << endl;

    cout<<kol;

    return 0;

}
