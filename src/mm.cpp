#include <cstdlib>
#include <cilk/cilk.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
#include "mmAlgorithms.h"
#include <cilk/cilk_api.h>
#include <math.h>

int main(int argc, const char *argv[])
{
	int n;
	int base;
	if (argc >= 2)
	{
		n = atoi(argv[1]);
		cout << "input matrix size:	" << argv[1] << endl;
	}
	else
	{
		cout << "size of input matrix has to be specified" << endl;
		return 0;
	}

	if (argc >= 3)
	{
		base = atoi(argv[2]);
		cout << "recursion base size:	" << argv[2] << endl;
	}
	else
	{
		cout << "size of recusion base matrix has to be specified" << endl;
		return 0;
	}

	if (argc >= 4)
		__cilkrts_set_param("nworkers", argv[3]);
	cout << "workers: " << __cilkrts_get_nworkers() << endl;


	int *mX;
	int *mY;

	//	readFromFile(&mX, &mY, &n);

	// int DEBUG = 0;
	// if (DEBUG == 1)
	// {
	// 	printM(mX, n, n);
	// 	printM(mY, n, n);
	// }

	//	srand(0);

	int DEBUG2 = 1;
	if (argc >= 5)
		DEBUG2 = atoi(argv[4]);





	if (DEBUG2 == 1)
	{

		mX = new int[n * n];
		mY = new int[n * n];

		init(mX, n, n);
		init(mY, n, n);

		// int type = 1;
		// if (argv[5] != NULL)
		// 	type = atoi(argv[5]);

		// if (type == 1)
		// bm(&mmIJK, mX, 0, 0, mY, 0, 0, n, n, "mmIJK");
		// // if (type == 2)
		// bm(&mmIKJ, mX, 0, 0, mY, 0, 0, n, n, "mmIKJ");
		// // if (type == 3)
		// bm(&mmJIK, mX, 0, 0, mY, 0, 0, n, n, "mmJIK");
		// // if (type == 4)
		// bm(&mmJKI, mX, 0, 0, mY, 0, 0, n, n, "mmJKI");
		// // if (type == 5)
		// bm(&mmKIJ, mX, 0, 0, mY, 0, 0, n, n, "mmKIJ");
		// // if (type == 6)
		// bm(&mmKJI, mX, 0, 0, mY, 0, 0, n, n, "mmKJI");

		// bm2(&mmRec, mX, 0, 0, mY, 0, 0, n, n, base, "mmRec");
		bm(&mmKIJ4, mX, 0, 0, mY, 0, 0, n, n, "mmKIJ4");
		bm2(&mmParRec, mX, 0, 0, mY, 0, 0, n, n, base, "mmParRec");
	}

	if (DEBUG2 == 2)
	{
		for (int k = 5; k < 14; k++)
		{
			// cout << "k:	" << k << endl;
			n = (int)pow((int)2, (int)k);
			mX = new int[n * n];
			mY = new int[n * n];

			init(mX, n, n);
			init(mY, n, n);
			// bm(&mmIKJ, mX, 0, 0, mY, 0, 0, n, n, "mmIKJ");
			bm2(&mmParRec, mX, 0, 0, mY, 0, 0, n, n, base, "mmParRec");
			// int type = 1;
			// if (argc >= 6)
			// 	type = atoi(argv[5]);
			// if (type == 1)
			// 	bm(&mmIKJ1, mX, 0, 0, mY, 0, 0, n, n, "mmIKJ1");
			// if (type == 2)
			// 	bm(&mmIKJ2, mX, 0, 0, mY, 0, 0, n, n, "mmIKJ2");
			// if (type == 3)
			// 	bm(&mmIKJ3, mX, 0, 0, mY, 0, 0, n, n, "mmIKJ3");
			// if (type == 4)
			// 	bm(&mmIKJ4, mX, 0, 0, mY, 0, 0, n, n, "mmIKJ4");
			// if (type == 5)
			// 	bm(&mmIKJ5, mX, 0, 0, mY, 0, 0, n, n, "mmIKJ5");
			// if (type == 6)
			// 	bm(&mmIKJ6, mX, 0, 0, mY, 0, 0, n, n, "mmIKJ6");
			// if (type == 7)
			// 	bm(&mmIKJ7, mX, 0, 0, mY, 0, 0, n, n, "mmIKJ7");

			// // bm(&mmKIJ, mX, 0, 0, mY, 0, 0, n, n, "mmKIJ");
			// if (type == 8)
			// 	bm(&mmKIJ1, mX, 0, 0, mY, 0, 0, n, n, "mmKIJ1");
			// if (type == 9)
			// 	bm(&mmKIJ2, mX, 0, 0, mY, 0, 0, n, n, "mmKIJ2");
			// if (type == 10)
			// 	bm(&mmKIJ3, mX, 0, 0, mY, 0, 0, n, n, "mmKIJ3");
			// if (type == 11)
				// bm(&mmKIJ4, mX, 0, 0, mY, 0, 0, n, n, "mmKIJ4");
			// if (type == 12)
			// 	bm(&mmKIJ5, mX, 0, 0, mY, 0, 0, n, n, "mmKIJ5");
			// if (type == 13)
			// 	bm(&mmKIJ6, mX, 0, 0, mY, 0, 0, n, n, "mmKIJ6");
			// if (type == 14)
			// 	bm(&mmKIJ7, mX, 0, 0, mY, 0, 0, n, n, "mmKIJ7");
		}
	}

	mDelete(mX);
	mDelete(mY);
	mX = NULL;
	mY = NULL;

	// cout << "end_______" << endl;

	return 0;
}
