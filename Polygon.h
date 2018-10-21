// Polygon.h: interface for the CPolygon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POLYGON_H__B98EF7C0_A532_11D5_A367_006008921FD4__INCLUDED_)
#define AFX_POLYGON_H__B98EF7C0_A532_11D5_A367_006008921FD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPolygon  
{
public:
	COLORREF color;
	int PointCount;
	double* z;
	double* y;
	double* x;
	CPolygon();
	virtual ~CPolygon();

	CPolygon& operator =(const CPolygon& aPolygon);
};

#endif // !defined(AFX_POLYGON_H__B98EF7C0_A532_11D5_A367_006008921FD4__INCLUDED_)
