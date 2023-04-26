#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <stdio.h>
using namespace std;

vector<int> koord_vect(vector<int>& a, vector<int>& b)
{
	vector<int> koord(a.size());
	for (int i = 0; i < a.size(); i++)
	{
		koord[i] = b[i] - a[i];
	}
	return koord;
}

double vect_proiz(double x1, double y1, double x2, double y2)
{
	return x1 * y2 - y1 * x2;
}

int Merge(int arr[], int aux[], int low, int mid, int high)
{
	int k = low, i = low, j = mid + 1;
	int inversionCount = 0;

	while (i <= mid && j <= high)
	{
		if (arr[i] <= arr[j]) {
			aux[k++] = arr[i++];
		}
		else {
			aux[k++] = arr[j++];
			inversionCount += (mid - i + 1);
		}
	}
	while (i <= mid) {
		aux[k++] = arr[i++];
	}

	for (int i = low; i <= high; i++) {
		arr[i] = aux[i];
	}
	return inversionCount;
}

int MergeSort(int arr[], int aux[], int low, int high)
{
	if (high <= low) {
		return 0;
	}
	int mid = (low + ((high - low) >> 1));
	int inversionCount = 0;
	inversionCount += MergeSort(arr, aux, low, mid);
	inversionCount += MergeSort(arr, aux, mid + 1, high);
	inversionCount += Merge(arr, aux, low, mid, high);
	return inversionCount;
}

int main()
{
	int kol_ver;
	cin >> kol_ver;
	const int N = kol_ver;
	vector<vector<int>> ver;
	ver.resize(kol_ver);
	vector<int> number;
	int fact = 1;
	for (int i = 0; i < kol_ver; i++)
	{
		int x, y, z;
		cin >> x >> y >> z;

		ver[i].resize(3);
		ver[i][0] = x;
		ver[i][1] = y;
		ver[i][2] = z;

		number.push_back(i + 1);
		//fact *= (i+1);
	}

	int j = 0, k = 0;
	int iter = 0;
	bool param1 = true, param2 = true, param3 = true;
	do
	{
		vector<vector<bool>> znak(kol_ver);
		for (int i = 0; i < kol_ver; i++)
		{
			if (i == kol_ver - 2)
			{
				j = i + 1;
				k = 0;
			}
			else if (i == kol_ver - 1)
			{
				j = 0;
				k = j + 1;
			}
			else
			{
				j = i + 1;
				k = j + 1;
			}

			vector<int> koord1 = koord_vect(ver[i], ver[j]);
			vector<int> koord2 = koord_vect(ver[j], ver[k]);

			znak[i].resize(3);

			double vect = vect_proiz(koord1[1], koord1[2], koord2[1], koord2[2]);
			if (vect >= 0) znak[i][0] = true;
			else  znak[i][0] = false;
			if (i>0 && znak[i-1][0] != znak[i][0]) param1 = false;
			//cout << vect << "\t";

			vect = vect_proiz(koord1[2], koord1[0], koord2[2], koord2[0]);
			if (vect >= 0) znak[i][1] = true;
			else  znak[i][1] = false;
			if (i > 0 && znak[i - 1][1] != znak[i][1]) param2 = false;
			//cout << vect << "\t";

			vect = vect_proiz(koord1[0], koord1[1], koord2[0], koord2[1]);
			if (vect >= 0) znak[i][2] = true;
			else  znak[i][2] = false;
			if (i > 0 && znak[i - 1][2] != znak[i][2]) param3 = false;
			//cout << vect << endl;
		}

		if (!param1 && !param2 && !param3) break;
		else {
			bool inv = true;
			do
			{
				next_permutation(number.begin(), number.end());
				vector<int>buf1 = number;
				vector<int>buf2 = number;

				int* arr = new int[N];
				int* aux = new int[N];
				for (int l = 0; l < N; l++)
				{
					arr[l] = number[l];
					aux[l] = number[l];
				}
				int kol_inv=MergeSort(arr, aux, 0, kol_ver-1);
				if (kol_inv % 2 == 0 && kol_inv!=0) inv = false;
				delete[] arr;
				delete[] aux;
			} while (inv);

			vector<vector<int>> buf_koord;
			buf_koord.resize(ver.size());
			for (int j = 0; j < ver.size(); j++)
			{
				buf_koord[j].resize(3);
				buf_koord[j][0] = ver[number[j] - 1][0];
				buf_koord[j][1] = ver[number[j] - 1][1];
				buf_koord[j][2] = ver[number[j] - 1][2];
			}
			ver = buf_koord;
			buf_koord.clear();

			param1 = true;
			param2 = true;
			param3 = true;
			break;
		}
		iter++;
		//cout << endl;
	} while (param1 && param2 && param3);
	for (int i = 0; i < number.size(); i++)
	{
		cout << number[i] << " ";
	}
	return 0;
}
