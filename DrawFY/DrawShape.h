#include <math.h>
#include <windows.h>

DWORD WINAPI DrawCir(LPVOID dataCir);
DWORD WINAPI DrawRec(LPVOID dataRec);
struct DataCir{
	HDC cdc;
	int x;
	int y;
	int R;
};
struct DataRec{
	HDC hdc;
	int lx;
	int ly;
	int rx;
	int ry;
};