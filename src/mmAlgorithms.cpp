#include <cstring>
#include <fstream>
#include <iostream>

#include <time.h>
#include <random>
#include <cilk/cilk.h>
#include <chrono>
#include <ctime>
#include <papi.h>

using namespace std;

void mDelete(int *m)
{
	if (m != NULL)
	{
		delete[] m;
	}
}

void mmIKJ1(int *mZ, int row0, int col0, int *mX, int row1, int col1, int *mY,
			int row2, int col2, int n, int size)
{

	cilk_for(int i = 0; i < n; ++i)
	{
		for (int k = 0; k < n; ++k)
		{
			for (int j = 0; j < n; ++j)
			{
				mZ[(i + row0) * size + col0 + j] += mX[(row1 + i) * size + col1 + k] * mY[(row2 + k) * size + col2 + j];
			}
		}
	}
}

void mmIKJ2(int *mZ, int row0, int col0, int *mX, int row1, int col1, int *mY,
			int row2, int col2, int n, int size)
{

	for (int i = 0; i < n; ++i)
	{
		cilk_for(int k = 0; k < n; ++k)
		{
			for (int j = 0; j < n; ++j)
			{
				mZ[(i + row0) * size + col0 + j] += mX[(row1 + i) * size + col1 + k] * mY[(row2 + k) * size + col2 + j];
			}
		}
	}
}

void mmIKJ3(int *mZ, int row0, int col0, int *mX, int row1, int col1, int *mY,
			int row2, int col2, int n, int size)
{

	for (int i = 0; i < n; ++i)
	{
		for (int k = 0; k < n; ++k)
		{
			cilk_for(int j = 0; j < n; ++j)
			{
				mZ[(i + row0) * size + col0 + j] += mX[(row1 + i) * size + col1 + k] * mY[(row2 + k) * size + col2 + j];
			}
		}
	}
}

void mmIKJ4(int *mZ, int row0, int col0, int *mX, int row1, int col1, int *mY,
			int row2, int col2, int n, int size)
{

	cilk_for(int i = 0; i < n; ++i)
	{
		cilk_for(int k = 0; k < n; ++k)
		{
			for (int j = 0; j < n; ++j)
			{
				mZ[(i + row0) * size + col0 + j] += mX[(row1 + i) * size + col1 + k] * mY[(row2 + k) * size + col2 + j];
			}
		}
	}
}

void mmIKJ5(int *mZ, int row0, int col0, int *mX, int row1, int col1, int *mY,
			int row2, int col2, int n, int size)
{

	cilk_for(int i = 0; i < n; ++i)
	{
		for (int k = 0; k < n; ++k)
		{
			cilk_for(int j = 0; j < n; ++j)
			{
				mZ[(i + row0) * size + col0 + j] += mX[(row1 + i) * size + col1 + k] * mY[(row2 + k) * size + col2 + j];
			}
		}
	}
}

void mmIKJ6(int *mZ, int row0, int col0, int *mX, int row1, int col1, int *mY,
			int row2, int col2, int n, int size)
{

	for (int i = 0; i < n; ++i)
	{
		cilk_for(int k = 0; k < n; ++k)
		{
			cilk_for(int j = 0; j < n; ++j)
			{
				mZ[(i + row0) * size + col0 + j] += mX[(row1 + i) * size + col1 + k] * mY[(row2 + k) * size + col2 + j];
			}
		}
	}
}

void mmIKJ7(int *mZ, int row0, int col0, int *mX, int row1, int col1, int *mY,
			int row2, int col2, int n, int size)
{

	cilk_for(int i = 0; i < n; ++i)
	{
		cilk_for(int k = 0; k < n; ++k)
		{
			cilk_for(int j = 0; j < n; ++j)
			{
				mZ[(i + row0) * size + col0 + j] += mX[(row1 + i) * size + col1 + k] * mY[(row2 + k) * size + col2 + j];
			}
		}
	}
}

void mmKIJ1(int *mZ, int row0, int col0, int *mX, int row1, int col1, int *mY,
			int row2, int col2, int n, int size)
{

	cilk_for(int k = 0; k < n; ++k)
	{
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				mZ[i * n + j] += mX[(row1 + i) * size + col1 + k] * mY[(row2 + k) * size + col2 + j];
			}
		}
	}
}

void mmKIJ2(int *mZ, int row0, int col0, int *mX, int row1, int col1, int *mY,
			int row2, int col2, int n, int size)
{

	for (int k = 0; k < n; ++k)
	{
		cilk_for(int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				mZ[i * n + j] += mX[(row1 + i) * size + col1 + k] * mY[(row2 + k) * size + col2 + j];
			}
		}
	}
}

void mmKIJ3(int *mZ, int row0, int col0, int *mX, int row1, int col1, int *mY,
			int row2, int col2, int n, int size)
{

	for (int k = 0; k < n; ++k)
	{
		for (int i = 0; i < n; ++i)
		{
			cilk_for(int j = 0; j < n; ++j)
			{
				mZ[i * n + j] += mX[(row1 + i) * size + col1 + k] * mY[(row2 + k) * size + col2 + j];
			}
		}
	}
}

void mmKIJ4(int *mZ, int row0, int col0, int *mX, int row1, int col1, int *mY,
			int row2, int col2, int n, int size)
{

	cilk_for(int k = 0; k < n; ++k)
	{
		cilk_for(int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				mZ[i * n + j] += mX[(row1 + i) * size + col1 + k] * mY[(row2 + k) * size + col2 + j];
			}
		}
	}
}

void mmKIJ5(int *mZ, int row0, int col0, int *mX, int row1, int col1, int *mY,
			int row2, int col2, int n, int size)
{

	for (int k = 0; k < n; ++k)
	{
		cilk_for(int i = 0; i < n; ++i)
		{
			cilk_for(int j = 0; j < n; ++j)
			{
				mZ[i * n + j] += mX[(row1 + i) * size + col1 + k] * mY[(row2 + k) * size + col2 + j];
			}
		}
	}
}

void mmKIJ6(int *mZ, int row0, int col0, int *mX, int row1, int col1, int *mY,
			int row2, int col2, int n, int size)
{

	cilk_for(int k = 0; k < n; ++k)
	{
		for (int i = 0; i < n; ++i)
		{
			cilk_for(int j = 0; j < n; ++j)
			{
				mZ[i * n + j] += mX[(row1 + i) * size + col1 + k] * mY[(row2 + k) * size + col2 + j];
			}
		}
	}
}

void mmKIJ7(int *mZ, int row0, int col0, int *mX, int row1, int col1, int *mY,
			int row2, int col2, int n, int size)
{

	cilk_for(int k = 0; k < n; ++k)
	{
		cilk_for(int i = 0; i < n; ++i)
		{
			cilk_for(int j = 0; j < n; ++j)
			{
				mZ[i * n + j] += mX[(row1 + i) * size + col1 + k] * mY[(row2 + k) * size + col2 + j];
			}
		}
	}
}

void mmIJK(int *mZ, int row0, int col0, int *mX, int row1, int col1, int *mY,
		   int row2, int col2, int n, int size)
{

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			for (int k = 0; k < n; ++k)
			{
				mZ[i * n + j] += mX[(row1 + i) * size + col1 + k] * mY[(row2 + k) * size + col2 + j];
			}
		}
	}
}

void mmIKJ(int *mZ, int row0, int col0, int *mX, int row1, int col1, int *mY,
		   int row2, int col2, int n, int size)
{

	for (int i = 0; i < n; ++i)
	{
		for (int k = 0; k < n; ++k)
		{
			for (int j = 0; j < n; ++j)
			{
				mZ[(i + row0) * size + col0 + j] += mX[(row1 + i) * size + col1 + k] * mY[(row2 + k) * size + col2 + j];
			}
		}
	}
}

void mmJIK(int *mZ, int row0, int col0, int *mX, int row1, int col1, int *mY,
		   int row2, int col2, int n, int size)
{

	for (int j = 0; j < n; ++j)
	{
		for (int i = 0; i < n; ++i)
		{
			for (int k = 0; k < n; ++k)
			{
				mZ[i * n + j] += mX[(row1 + i) * size + col1 + k] * mY[(row2 + k) * size + col2 + j];
			}
		}
	}
}

void mmJKI(int *mZ, int row0, int col0, int *mX, int row1, int col1, int *mY,
		   int row2, int col2, int n, int size)
{

	for (int j = 0; j < n; ++j)
	{
		for (int k = 0; k < n; ++k)
		{
			for (int i = 0; i < n; ++i)
			{
				mZ[i * n + j] += mX[(row1 + i) * size + col1 + k] * mY[(row2 + k) * size + col2 + j];
			}
		}
	}
}

void mmKIJ(int *mZ, int row0, int col0, int *mX, int row1, int col1, int *mY,
		   int row2, int col2, int n, int size)
{

	for (int k = 0; k < n; ++k)
	{
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				mZ[i * n + j] += mX[(row1 + i) * size + col1 + k] * mY[(row2 + k) * size + col2 + j];
			}
		}
	}
}

void mmKJI(int *mZ, int row0, int col0, int *mX, int row1, int col1, int *mY,
		   int row2, int col2, int n, int size)
{

	for (int k = 0; k < n; ++k)
	{
		for (int j = 0; j < n; ++j)
		{
			for (int i = 0; i < n; ++i)
			{
				mZ[i * n + j] += mX[(row1 + i) * size + col1 + k] * mY[(row2 + k) * size + col2 + j];
			}
		}
	}
}

void mmRec(int *mZ, int row0, int col0, int *mX, int row1, int col1, int *mY,
		   int row2, int col2, int n, int size, int base)
{
	if (n == base)
	{
		return mmKIJ4(mZ, row0, col0, mX, row1, col1, mY, row2, col2, n, size);
	}
	else
	{
		//Z11, X11, Y11
		mmRec(mZ, row0, col0, mX, row1, col1, mY, row2, col2, n / 2, size,
			  base);
		//Z12, X11, Y12
		mmRec(mZ, row0, col0 + n / 2, mX, row1, col1, mY, row2, col2 + n / 2,
			  n / 2, size, base);
		//Z21, X21, Y11
		mmRec(mZ, row0 + n / 2, col0, mX, row1 + n / 2, col1, mY, row2, col2,
			  n / 2, size, base);
		//Z22, X21, Y12
		mmRec(mZ, row0 + n / 2, col0 + n / 2, mX, row1 + n / 2, col1, mY, row2,
			  col2 + n / 2, n / 2, size, base);

		//Z11, X12, Y21
		mmRec(mZ, row0, col0, mX, row1, col1 + n / 2, mY, row2 + n / 2, col2,
			  n / 2, size, base);
		//Z12, X12, Y22
		mmRec(mZ, row0, col0 + n / 2, mX, row1, col1 + n / 2, mY, row2 + n / 2,
			  col2 + n / 2, n / 2, size, base);
		//Z21, X22, Y21
		mmRec(mZ, row0 + n / 2, col0, mX, row1 + n / 2, col1 + n / 2, mY,
			  row2 + n / 2, col2, n / 2, size, base);
		//Z22, X22, Y22
		mmRec(mZ, row0 + n / 2, col0 + n / 2, mX, row1 + n / 2, col1 + n / 2,
			  mY, row2 + n / 2, col2 + n / 2, n / 2, size, base);
	}
}

void mmParRec(int *mZ, int row0, int col0, int *mX, int row1, int col1, int *mY,
			  int row2, int col2, int n, int size, int base)
{
	if (n == base)
	{
		return mmIKJ(mZ, row0, col0, mX, row1, col1, mY, row2, col2, n, size);
	}
	else
	{
		//Z11, X11, Y11
		cilk_spawn mmParRec(mZ, row0, col0, mX, row1, col1, mY, row2, col2, n / 2, size,
							base);
		//Z12, X11, Y12
		cilk_spawn mmParRec(mZ, row0, col0 + n / 2, mX, row1, col1, mY, row2, col2 + n / 2,
							n / 2, size, base);
		//Z21, X21, Y11
		cilk_spawn mmParRec(mZ, row0 + n / 2, col0, mX, row1 + n / 2, col1, mY, row2, col2,
							n / 2, size, base);
		//Z22, X21, Y12
		mmParRec(mZ, row0 + n / 2, col0 + n / 2, mX, row1 + n / 2, col1, mY, row2,
				 col2 + n / 2, n / 2, size, base);
		cilk_sync;
		//Z11, X12, Y21
		cilk_spawn mmParRec(mZ, row0, col0, mX, row1, col1 + n / 2, mY, row2 + n / 2, col2,
							n / 2, size, base);
		//Z12, X12, Y22
		cilk_spawn mmParRec(mZ, row0, col0 + n / 2, mX, row1, col1 + n / 2, mY, row2 + n / 2,
							col2 + n / 2, n / 2, size, base);
		//Z21, X22, Y21
		cilk_spawn mmParRec(mZ, row0 + n / 2, col0, mX, row1 + n / 2, col1 + n / 2, mY,
							row2 + n / 2, col2, n / 2, size, base);
		//Z22, X22, Y22
		mmParRec(mZ, row0 + n / 2, col0 + n / 2, mX, row1 + n / 2, col1 + n / 2,
				 mY, row2 + n / 2, col2 + n / 2, n / 2, size, base);

		cilk_sync;
	}
}

void printM(int *m, int row, int col)
{

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << m[i * col + j] << " ";
		}
		cout << endl;
	}
}

void init(int *m, int row, int col)
{
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			m[i * col + j] = rand() % 4;
		}
	}
}

void readFromFile(int **mX, int **mY, int *num)
{

	ifstream inFile;
	inFile.open("input2");
	if (!inFile)
	{
		cout << "Unable to open file";
		exit(1);
	}

	inFile >> *num;
	int n = *num;

	*mX = new int[n * n];
	*mY = new int[n * n];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			inFile >> (*mX)[i * n + j];
		}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			inFile >> (*mY)[i * n + j];
		}
	inFile.close();
}

void bm(void (*func)(int *, int, int, int *, int, int, int *, int, int, int, int),
		int *mX, int row1, int col1, int *mY, int row2, int col2, int n,
		int size, string name)
{
	int PAPI = 1;

	// cout << "size:" << n << endl;
	int *mZ = new int[n * n];
	memset(mZ, 0, sizeof(int) * n * n);

	auto start = std::chrono::system_clock::now();
	time_t startTime = time(NULL);

	int retval, EventSet = PAPI_NULL;
	long_long values[6] = {0};

	if (PAPI == 1)
	{
		/* Initialize the PAPI library */
		retval = PAPI_library_init(PAPI_VER_CURRENT);

		if (retval != PAPI_VER_CURRENT)
		{
			fprintf(stderr, "PAPI library init error!\n");
			// exit(1);
		}

		if (PAPI_create_eventset(&EventSet) != PAPI_OK)
			cout << "error_create" << endl;

		cout << "add L1 cache" << endl;
		if (PAPI_add_event(EventSet, PAPI_L1_TCM) != PAPI_OK)
			cout << "error_add1" << endl;

		cout << "add L2 cache" << endl;
		if (PAPI_add_event(EventSet, PAPI_L2_TCM) != PAPI_OK)
			cout << "error_add2" << endl;

		cout << "add L3 cache" << endl;
		if (PAPI_add_event(EventSet, PAPI_L3_TCM) != PAPI_OK)
			cout << "error_add3" << endl;

		if (PAPI_start(EventSet) != PAPI_OK)
			cout << "start_error" << endl;
	}

	func(mZ, 0, 0, mX, row1, col1, mY, row2, col2, n, size);
	//	printM(mZ, n, n);

	if (PAPI == 1)
	{
		if (PAPI_read(EventSet, values) != PAPI_OK)
			cout << "read error" << endl;

		printf("%lld %lld %lld %lld %lld %lld\n", values[0], values[1], values[2], values[3], values[4], values[5]);

		if (PAPI_stop(EventSet, values) != PAPI_OK)
			cout << "stop error" << endl;
	}

	time_t stopTime = time(NULL);
	long elapsed = stopTime - startTime;
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	// cout << "time interval of " << name << " : " << elapsed << "s "
	// 	 << "or chrono sec: " << elapsed_seconds.count() << " s " << endl;
	cout << elapsed_seconds.count() << endl;

	mDelete(mZ);

	// cout<<"________________"<<endl<<endl;
}

void bm2(
	void (*func)(int *, int, int, int *, int, int, int *, int, int, int, int,
				 int),
	int *mX, int row1, int col1, int *mY, int row2, int col2,
	int n, int size, int base, string name)
{

	cout << "size:" << n << endl;
	cout << "base :" << base << endl;
	int *mZ = new int[n * n];
	memset(mZ, 0, sizeof(int) * n * n);


	int retval, EventSet = PAPI_NULL;
	long_long values[6] = {0};

	int PAPI =1;
	if (PAPI == 1)
	{
		/* Initialize the PAPI library */
		retval = PAPI_library_init(PAPI_VER_CURRENT);

		if (retval != PAPI_VER_CURRENT)
		{
			fprintf(stderr, "PAPI library init error!\n");
			// exit(1);
		}

		if (PAPI_create_eventset(&EventSet) != PAPI_OK)
			cout << "error_create" << endl;

		cout << "add L1 cache" << endl;
		if (PAPI_add_event(EventSet, PAPI_L1_TCM) != PAPI_OK)
			cout << "error_add1" << endl;

		cout << "add L2 cache" << endl;
		if (PAPI_add_event(EventSet, PAPI_L2_TCM) != PAPI_OK)
			cout << "error_add2" << endl;

		cout << "add L3 cache" << endl;
		if (PAPI_add_event(EventSet, PAPI_L3_TCM) != PAPI_OK)
			cout << "error_add3" << endl;

		if (PAPI_start(EventSet) != PAPI_OK)
			cout << "start_error" << endl;
	}

	auto start = std::chrono::system_clock::now();
	time_t startTime = time(NULL);
	func(mZ, 0, 0, mX, row1, col1, mY, row2, col2, n, size, base);
	//	printM(mZ, n, n);
	time_t stopTime = time(NULL);
	long elapsed = stopTime - startTime;
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	// cout << elapsed_seconds.count() << endl;
	cout << "time interval of " << name << " : " << elapsed_seconds.count() << " s " << endl
		 << endl;

	if (PAPI == 1)
	{
		if (PAPI_read(EventSet, values) != PAPI_OK)
			cout << "read error" << endl;

		printf("%lld %lld %lld %lld %lld %lld\n", values[0], values[1], values[2], values[3], values[4], values[5]);

		if (PAPI_stop(EventSet, values) != PAPI_OK)
			cout << "stop error" << endl;
	}

	mDelete(mZ);

	// cout<<"________________"<<endl<<endl;
}
