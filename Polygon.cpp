// Polygon.cpp: implementation of the CPolygon class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "3DEngine.h"
#include "Polygon.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPolygon::CPolygon()
{
	orderignore=false;
	
	PointCount=0;
	//copy=false;
	split=false;
}

CPolygon::~CPolygon()
{
	/*if(PointCount>0 && !copy)
	{
		delete[]x;
		delete[]y;
		delete[]z;
		PointCount=0;
	}*/
}

CPolygon& CPolygon::operator =(const CPolygon& aPolygon)
{
	/*if(PointCount>0)
	{
		delete[]x;
		delete[]y;
		delete[]z;
	}
	copy=false;*/

	PointCount=aPolygon.PointCount;
	/*if(PointCount)
	{
		x=new double[PointCount];
		y=new double[PointCount];
		z=new double[PointCount];*/
		for(int a=0;a<PointCount;a++)
		{
			x[a]=aPolygon.x[a];
			y[a]=aPolygon.y[a];
			z[a]=aPolygon.z[a];
		}
	/*}*/

	//x.Copy(aPolygon.x);
	//y.Copy(aPolygon.y);
	//z.Copy(aPolygon.z);

	color=aPolygon.color;
	dcolor=aPolygon.dcolor;
	dist=aPolygon.dist;

	Nx=aPolygon.Nx;
	Ny=aPolygon.Ny;
	Nz=aPolygon.Nz;
	Sd=aPolygon.Sd;

	orderignore=aPolygon.orderignore;

	return *this;
}