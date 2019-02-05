#ifndef MM_ALGORITHMS_H
#define MM_ALGORITHMS_H

using namespace std;

void mDelete(int* m);

void mmIJK(int*mZ, int row0, int col0, int* mX, int row1, int col1, int* mY,
		int row2, int col2, int n, int size);
void mmIKJ(int*mZ, int row0, int col0, int* mX, int row1, int col1, int* mY,
		int row2, int col2, int n, int size);

void mmJIK(int*mZ, int row0, int col0, int* mX, int row1, int col1, int* mY,
		int row2, int col2, int n, int size);

void mmJKI(int*mZ, int row0, int col0, int* mX, int row1, int col1, int* mY,
		int row2, int col2, int n, int size);

void mmKIJ(int*mZ, int row0, int col0, int* mX, int row1, int col1, int* mY,
		int row2, int col2, int n, int size);
void mmKJI(int*mZ, int row0, int col0, int* mX, int row1, int col1, int* mY,
		int row2, int col2, int n, int size);

void mAdd(int* mX, int* mY, int n);

void mmRec(int*mZ, int row0, int col0, int* mX, int row1, int col1, int* mY,
		int row2, int col2, int n, int size, int base);

void mmParRec(int*mZ, int row0, int col0, int* mX, int row1, int col1, int* mY,
		int row2, int col2, int n, int size, int base);

void printM(int* m, int row, int col);

void init(int* m, int row, int col);
void readFromFile(int** mX, int** mY, int* num);
void bm(void (*func)(int*, int, int, int*, int, int, int*, int, int, int, int),
		int* mX, int row1, int col1, int* mY, int row2, int col2, int n,
		int size, string name);
void bm2(
		void (*func)(int*, int, int, int*, int, int, int*, int, int, int, int,
				int), int* mX, int row1, int col1, int* mY, int row2, int col2,
		int n, int size, int base, string name);

void mmIKJ1(int*mZ, int row0, int col0, int* mX, int row1, int col1, int* mY,
		int row2, int col2, int n, int size);

void mmIKJ2(int*mZ, int row0, int col0, int* mX, int row1, int col1, int* mY,
		int row2, int col2, int n, int size);

void mmIKJ3(int*mZ, int row0, int col0, int* mX, int row1, int col1, int* mY,
		int row2, int col2, int n, int size);

void mmIKJ4(int*mZ, int row0, int col0, int* mX, int row1, int col1, int* mY,
		int row2, int col2, int n, int size);

void mmIKJ5(int*mZ, int row0, int col0, int* mX, int row1, int col1, int* mY,
		int row2, int col2, int n, int size);

void mmIKJ6(int*mZ, int row0, int col0, int* mX, int row1, int col1, int* mY,
		int row2, int col2, int n, int size);

void mmIKJ7(int*mZ, int row0, int col0, int* mX, int row1, int col1, int* mY,
		int row2, int col2, int n, int size);

void mmKIJ1(int* mZ, int row0, int col0, int* mX, int row1, int col1, int* mY,
		int row2, int col2, int n, int size);

void mmKIJ2(int* mZ, int row0, int col0, int* mX, int row1, int col1, int* mY,
		int row2, int col2, int n, int size);

void mmKIJ3(int* mZ, int row0, int col0, int* mX, int row1, int col1, int* mY,
		int row2, int col2, int n, int size);

void mmKIJ4(int* mZ, int row0, int col0, int* mX, int row1, int col1, int* mY,
		int row2, int col2, int n, int size);

void mmKIJ5(int* mZ, int row0, int col0, int* mX, int row1, int col1, int* mY,
		int row2, int col2, int n, int size);

void mmKIJ6(int* mZ, int row0, int col0, int* mX, int row1, int col1, int* mY,
		int row2, int col2, int n, int size);

void mmKIJ7(int* mZ, int row0, int col0, int* mX, int row1, int col1, int* mY,
		int row2, int col2, int n, int size);

#endif