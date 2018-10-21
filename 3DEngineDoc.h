// 3D EngineDoc.h : interface of the CMy3DEngineDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_3DENGINEDOC_H__7039CD6C_DB84_11D5_8358_00A024E92462__INCLUDED_)
#define AFX_3DENGINEDOC_H__7039CD6C_DB84_11D5_8358_00A024E92462__INCLUDED_

#include "World.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMy3DEngineDoc : public CDocument
{
protected: // create from serialization only
	CMy3DEngineDoc();
	DECLARE_DYNCREATE(CMy3DEngineDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy3DEngineDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	void LoadShapes();
	void LoadTank();
	CWorld world;
	virtual ~CMy3DEngineDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMy3DEngineDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3DENGINEDOC_H__7039CD6C_DB84_11D5_8358_00A024E92462__INCLUDED_)
