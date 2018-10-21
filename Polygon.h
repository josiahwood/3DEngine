// Polygon.h: interface for the CPolygon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POLYGON_H__B98EF7C0_A532_11D5_A367_006008921FD4__INCLUDED_)
#define AFX_POLYGON_H__B98EF7C0_A532_11D5_A367_006008921FD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include <afxtempl.h>

class CPolygon  
{
public:
	bool orderignore;
	
	COLORREF color;
	COLORREF dcolor;
	int PointCount;
	double dist;
	//CArray <double,double> x;
	//CArray <double,double> y;
	//CArray <double,double> z;
	double z[10];
	double y[10];
	double x[10];

	double Nx;
	double Ny;
	double Nz;
	double Sd;

	//bool copy;

	int split;
	CPolygon();
	virtual ~CPolygon();

	CPolygon& operator =(const CPolygon& aPolygon);
};

#endif // !defined(AFX_POLYGON_H__B98EF7C0_A532_11D5_A367_006008921FD4__INCLUDED_)
