// 3D EngineView.h : interface of the CMy3DEngineView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_3DENGINEVIEW_H__7039CD6E_DB84_11D5_8358_00A024E92462__INCLUDED_)
#define AFX_3DENGINEVIEW_H__7039CD6E_DB84_11D5_8358_00A024E92462__INCLUDED_

#include "World.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "windows.h"
#include "mmsystem.h"

class CMy3DEngineView : public CFormView
{
protected: // create from serialization only
	CMy3DEngineView();
	DECLARE_DYNCREATE(CMy3DEngineView)

public:
	//{{AFX_DATA(CMy3DEngineView)
	enum { IDD = IDD_MY3DENGINE_FORM };
	//}}AFX_DATA

// Attributes
public:
	CMy3DEngineDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy3DEngineView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
public:
	int stimer;
	void Shoot();
	bool KeyB;
	bool KeyMinus;
	bool KeyPlus;
	bool KeySpace;
	int m_Cut;
	int PlayerIndex;
	bool KeyUp;
	bool KeyDown;
	bool KeyLeft;
	bool KeyRight;
	
	double LeftBorder;
	bool RButtonDown;
	CPoint MouseStart;
	bool LButtonDown;
	CDC tempdc;
	CBitmap Bitmap;
	void GetInput();
	bool joyon;
	JOYCAPS JoyCap;
	
	void Joystick();
	void ReleasedcaptureCut(NMHDR* pNMHDR, LRESULT* pResult);

	CWorld World;
	virtual ~CMy3DEngineView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMy3DEngineView)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in 3D EngineView.cpp
inline CMy3DEngineDoc* CMy3DEngineView::GetDocument()
   { return (CMy3DEngineDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3DENGINEVIEW_H__7039CD6E_DB84_11D5_8358_00A024E92462__INCLUDED_)
