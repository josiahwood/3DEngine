// Light.h: interface for the CLight class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LIGHT_H__003574A0_E508_11D5_8358_00A024E92462__INCLUDED_)
#define AFX_LIGHT_H__003574A0_E508_11D5_8358_00A024E92462__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLight  
{
public:
	double x,y,z;
	COLORREF color;
	double intensity;
	int VectorCount;
	double* a;
	double* t;

	CLight();
	virtual ~CLight();

};

#endif // !defined(AFX_LIGHT_H__003574A0_E508_11D5_8358_00A024E92462__INCLUDED_)
