#include "DrawShape.h"
#define PI 3.141592653
DWORD WINAPI DrawCir(LPVOID dataCir)
{
	int i;
	DataCir *info = (DataCir *)dataCir;
	HDC hdc = info->cdc;
	int x = info->x;
	int y = info->y;
	int R = info->R;

	for(i=0;i<=1440;i++)
	{
		//SetPixel(hdc,x+R*cos(2*PI*i/1440),x+R*sin(2*PI*i/1440),RGB(0,0,0));
		Ellipse(hdc,x+R*cos(2*PI*i/1440)-1,x+R*sin(2*PI*i/1440)-1,x+R*cos(2*PI*i/1440)+1,x+R*sin(2*PI*i/1440)+1);
		Sleep(10);
	}
	return 0;
}
DWORD WINAPI DrawRec(LPVOID dataR)
{
	int i,j;
	DataRec *info = (DataRec *)dataR;
	HDC hdc = info->hdc;
	int Lx = info->lx;
	int Ly = info->ly;
	int Rx = info->rx;
	int Ry = info->ry;
	int width = Rx-Lx;
	int height = Ry-Ly;
	int X0 = Lx+width/2;
	int Y0 = Ly+height/2;
	//画右边线
/*	for(i=Ly;i<=Ry;i++)
	{
		SetPixel(hdc,Rx,i,RGB(255,0,0));
		Sleep(10);
	}
	//画下面线
	for(i=Rx;i>=Lx;i--)
	{
		SetPixel(hdc,i,Ry,RGB(255,0,0));
		Sleep(10);
	}
	//画左边的线
	for(i=Ry;i>=Ly;i--)
	{
		SetPixel(hdc,Lx,i,RGB(255,0,0));
		Sleep(10);
	}
	//画上面的线
	for(i=Lx;i<=Rx;i++)
	{
		SetPixel(hdc,i,Ly,RGB(255,0,0));
		Sleep(10);
	}*/
	//画右边线
	for(i=0;i<360;i++)
	{
		//SetPixel(hdc,Lx+width,Y0-width*tan(PI/4-i*PI/720)/2,RGB(255,0,0));
		Ellipse(hdc,Lx+width-1,Y0-width*tan(PI/4-i*PI/720)/2-1,Lx+width+1,Y0-width*tan(PI/4-i*PI/720)/2+1);
		Sleep(10);
	}
	//画下边线
	for(i=0;i<360;i++)
	{
		//SetPixel(hdc,X0+height*tan(PI/4-i*PI/720)/2,Ly+height,RGB(255,0,0));
		Ellipse(hdc,X0+height*tan(PI/4-i*PI/720)/2-1,Ly+height-1,X0+height*tan(PI/4-i*PI/720)/2+1,Ly+height+1);
		Sleep(10);
	}
	//画左边线
	for(i=0;i<360;i++)
	{
		//SetPixel(hdc,Lx,Y0+width*tan(PI/4-i*PI/720)/2,RGB(255,0,0));
		Ellipse(hdc,Lx-1,Y0+width*tan(PI/4-i*PI/720)/2-1,Lx+1,Y0+width*tan(PI/4-i*PI/720)/2+1);
		Sleep(10);
	}
	//画上面的线
	for(i=0;i<360;i++)
	{
		//SetPixel(hdc,X0-width*tan(PI/4-i*PI/720)/2,Ly,RGB(255,0,0));
		Ellipse(hdc,X0-width*tan(PI/4-i*PI/720)/2-1,Ly-1,X0-width*tan(PI/4-i*PI/720)/2+1,Ly+1);
		Sleep(10);
	}

	return 0;
}