// 3D EngineView.cpp : implementation of the CMy3DEngineView class
//

#include "stdafx.h"
#include "3DEngine.h"

#include "3DEngineDoc.h"
#include "3DEngineView.h"

#include "math.h"

#include "mmsystem.h"
#include "wingdi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMy3DEngineView

IMPLEMENT_DYNCREATE(CMy3DEngineView, CFormView)

BEGIN_MESSAGE_MAP(CMy3DEngineView, CFormView)
	//{{AFX_MSG_MAP(CMy3DEngineView)
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy3DEngineView construction/destruction

CMy3DEngineView::CMy3DEngineView()
	: CFormView(CMy3DEngineView::IDD)
{
	//{{AFX_DATA_INIT(CMy3DEngineView)
	//}}AFX_DATA_INIT
	// TODO: add construction code here

	joyon=false;
	LButtonDown=false;

	KeyUp=false;
	KeyDown=false;
	KeyLeft=false;
	KeyRight=false;

	KeyB=false;

	PlayerIndex=0;

	m_Cut=0;

	stimer=0;
}

CMy3DEngineView::~CMy3DEngineView()
{
	Bitmap.DeleteObject();
	tempdc.DeleteDC();
}

void CMy3DEngineView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMy3DEngineView)
	//}}AFX_DATA_MAP
}

BOOL CMy3DEngineView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CMy3DEngineView::OnInitialUpdate()
{	
	CFormView::OnInitialUpdate();
	ResizeParentToFit();

	//CRect rect;
	//m_Joystick.GetWindowRect(&rect);

	//m_Joystick.ScreenToClient(&rect);

	//LeftBorder=rect.Width()*1.5;
	LeftBorder=0;
	
	CMy3DEngineDoc* doc=GetDocument();
	CDC* dc=GetDC();

	Bitmap.DeleteObject();
	Bitmap.CreateCompatibleBitmap(dc,1,1);
	tempdc.DeleteDC();
	tempdc.CreateCompatibleDC(dc);
	tempdc.SelectObject(Bitmap);
	ReleaseDC(dc);
}

/////////////////////////////////////////////////////////////////////////////
// CMy3DEngineView printing

BOOL CMy3DEngineView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMy3DEngineView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMy3DEngineView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMy3DEngineView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
	OnUpdate(NULL,NULL,NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CMy3DEngineView diagnostics

#ifdef _DEBUG
void CMy3DEngineView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMy3DEngineView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMy3DEngineDoc* CMy3DEngineView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy3DEngineDoc)));
	return (CMy3DEngineDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMy3DEngineView message handlers

#define STEREO 0

void CMy3DEngineView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{

	CMy3DEngineDoc* doc=GetDocument();
	
	CDC* dc=GetDC();
	
	UpdateData();
	doc->world.wall=(double)m_Cut/1.5+1;
	
#if STEREO
	doc->world.cx-=5;
	doc->world.dc=&tempdc;
	doc->world.Draw();

	dc->BitBlt( 0,0,doc->world.vw,doc->world.vh,&tempdc,0,0,SRCCOPY);

	doc->world.cx+=10;
	doc->world.dc=&tempdc;
	doc->world.Draw();

	dc->BitBlt( doc->world.vw+1,0,doc->world.vw,doc->world.vh,&tempdc,0,0,SRCCOPY);

	doc->world.cx-=5;
#else
	doc->world.dc=&tempdc;
	doc->world.Draw();

	dc->BitBlt(LeftBorder,0,doc->world.vw,doc->world.vh,&tempdc,0,0,SRCCOPY);
#endif

	ReleaseDC(dc);
}

void CMy3DEngineView::OnDraw(CDC* pDC) 
{
	OnUpdate(NULL,NULL,NULL);	
	
}

void CMy3DEngineView::OnTimer(UINT nIDEvent)
{
	CMy3DEngineDoc* doc=GetDocument();

	switch(nIDEvent)
	{
	case 0:
		GetInput();
	
		/*doc->world.Groups[0].t++;
		if(doc->world.Groups[0].t==360)
			doc->world.Groups[0].t=0;

		doc->world.Groups[0].a+=2;
		if(doc->world.Groups[0].a==360)
			doc->world.Groups[0].a=0;

		doc->world.Groups[0].p+=3;
		if(doc->world.Groups[0].p==360)
			doc->world.Groups[0].p=0;

		doc->world.Groups[1].t++;
		if(doc->world.Groups[1].t==360)
			doc->world.Groups[1].t=0;

		doc->world.Groups[1].a+=2;
		if(doc->world.Groups[1].a==360)
			doc->world.Groups[1].a=0;

		doc->world.Groups[1].p+=3;
		if(doc->world.Groups[1].p==360)
			doc->world.Groups[1].p=0;

		doc->world.Groups[2].t++;
		if(doc->world.Groups[2].t==360)
			doc->world.Groups[2].t=0;

		doc->world.Groups[2].a+=2;
		if(doc->world.Groups[2].a==360)
			doc->world.Groups[2].a=0;

		doc->world.Groups[2].p+=3;
		if(doc->world.Groups[2].p==360)
			doc->world.Groups[2].p=0;*/

		//OnUpdate(NULL,NULL,NULL);

		break;
	case 1:
		return;
		CDC* dc=GetDC();
		
		char* b;
		b=new char[256];
		b=itoa(doc->world.DrawCount,b,10);
		dc->TextOut(410,5,b);
		doc->world.DrawCount=0;
		delete[]b;

		ReleaseDC(dc);
	}
	
	OnUpdate(NULL,NULL,NULL);
	
	
	CFormView::OnTimer(nIDEvent);
	
}

#define JOYSTICK 0

void CMy3DEngineView::Joystick() 
{
	joyon=!joyon;
	
#if JOYSTICK
	if(joyon)
	{
		SetTimer(1,1000,NULL);
		joySetCapture(m_hWnd,JOYSTICKID1, 200, TRUE);
		joySetThreshold(JOYSTICKID1,1);
		joyGetDevCaps(JOYSTICKID1,&JoyCap,sizeof(JOYCAPS));
	}
#endif
	
	while(joyon)
	{
		OnTimer(0);
		GetInput();
		

		MSG msg;

		// Process existing messages in the application's message queue.
		// When the queue is empty, do clean up and return.
		while (::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE))
		{
			if (!AfxGetThread()->PumpMessage())
				return;
		}
	}
	
#if JOYSTICK
	joyReleaseCapture(JOYSTICKID1);
#endif

	KillTimer(1);
}

void CMy3DEngineView::GetInput()
{
	//return;
	
#if JOYSTICK
	JOYINFO info;

	joyGetPos(JOYSTICKID1, &info);
	
	double xval=info.wXpos;
	double xmax=JoyCap.wXmax;
	double xmin=JoyCap.wXmin;
	double xper=((xval-xmin)/(xmax-xmin)*2.0)-1.0;

	double yval=info.wYpos;
	double ymax=JoyCap.wYmax;
	double ymin=JoyCap.wYmin;
	double yper=((yval-ymin)/(ymax-ymin)*2.0)-1.0;

	double zval=info.wZpos;
	double zmax=JoyCap.wZmax;
	double zmin=JoyCap.wZmin;
	double zper=-(((zval-zmin)/(zmax-zmin)*2.0)-1.0);

	bool Button2=info.wButtons & JOY_BUTTON2;
	bool Button1=info.wButtons & JOY_BUTTON1;
#else
	double xper=0;
	if(KeyLeft)
		xper--;
	if(KeyRight)
		xper++;
	double yper=0;
	if(KeyUp)
		yper--;
	if(KeyDown)
		yper++;
	static double zper=0;
	if(KeyPlus)
		zper+=.05;
	if(KeyMinus)
		zper-=.05;

	bool Button2=KeySpace;
	bool Button1=KeyB;
#endif

	CMy3DEngineDoc* doc=GetDocument();

	doc->world.Groups[PlayerIndex].a-=xper*.50;
	doc->world.ct=-zper*45;
	//doc->world.ct+=yper*.20;
	double dx,dy,ds,da;
	//if(yper>=0)
		da=doc->world.Groups[PlayerIndex].a/180*3.14159;
	//else
	//	da=3.14159-(doc->world.Groups[PlayerIndex].a/180*3.14159);
	ds=-yper/3;
	dx=cos(da);
	dy=sin(da);
	dx*=ds;
	dy*=ds;

	if(Button2 && doc->world.Groups[PlayerIndex].z<=0)
	{
		doc->world.Groups[PlayerIndex].fz+=.2;
	}
	//doc->world.Groups[PlayerIndex].fz-=.001;
	/*if(doc->world.Groups[PlayerIndex].z<0)
	{
		doc->world.Groups[PlayerIndex].z=0;
		doc->world.Groups[PlayerIndex].fz=0;
	}*/
	//doc->world.Groups[PlayerIndex].z+=doc->world.Groups[PlayerIndex].dz;

	doc->world.Groups[PlayerIndex].x+=dx;
	doc->world.Groups[PlayerIndex].y+=dy;

	doc->world.ca=doc->world.Groups[PlayerIndex].a;
	dx=-cos(doc->world.ca/180*3.14159)*50*cos(doc->world.ct/180*3.14159);
	dy=-sin(doc->world.ca/180*3.14159)*50*cos(doc->world.ct/180*3.14159);
	doc->world.cx=doc->world.Groups[PlayerIndex].x+dx;
	doc->world.cy=doc->world.Groups[PlayerIndex].y+dy;

	dy=sin(doc->world.ct/180*3.14159)*50;
	doc->world.cz=-dy+doc->world.Groups[PlayerIndex].z;
	
	/*if((doc->world.ca>90 && doc->world.ca<180) || doc->world.ca>270)
	{
		doc->world.cx-=dx;
		doc->world.cy-=dy;
	}
	else if(doc->world.ca>180 && doc->world.ca<270)
	{
		doc->world.cx-=dx;
		doc->world.cy-=dy;
	}
	else
	{
		doc->world.cx+=dx;
		doc->world.cy+=dy;
	}*/

	/*doc->world.dc->Rectangle(0,410,50,460);
	doc->world.dc->MoveTo(0,435);
	doc->world.dc->LineTo(50,435);
	doc->world.dc->MoveTo(25,410);
	doc->world.dc->LineTo(25,460);
	doc->world.dc->Rectangle(25+xper*25-2,435+yper*25-2,25+xper*25+2,435+yper*25+2);
	doc->world.dc->Rectangle(60,410,80,460);
	doc->world.dc->Rectangle(60,435,80,435+zper*-25.0);*/

	if(Button1)
		Shoot();
	stimer++;

	doc->world.Physics();
	UpdateData(FALSE);
}

void CMy3DEngineView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CMy3DEngineDoc* doc=GetDocument();

	static drag=0;

	if(!drag)
		MouseStart=point;

	int dx=point.x-MouseStart.x;
	int dy=point.y-MouseStart.y;
	
	if(nFlags & MK_LBUTTON)
	{
		doc->world.ca-=point.x-MouseStart.x;
		doc->world.ct-=point.y-MouseStart.y;
	}
	else if(nFlags & MK_RBUTTON)
	{
		double dx,dy,ds;
		
		dx=cos(doc->world.ca/180*3.14159);
		dy=sin(doc->world.ca/180*3.14159);
		ds=MouseStart.y-point.y;
		dx*=ds;
		dy*=ds;
		doc->world.cx+=dx;
		doc->world.cy+=dy;

		dx=cos((doc->world.ca-90)/180*3.14159);
		dy=sin((doc->world.ca-90)/180*3.14159);
		ds=point.x-MouseStart.x;
		dx*=ds;
		doc->world.cx+=dx;
		dy*=ds;
		doc->world.cy+=dy;
	}
	else if(nFlags & MK_MBUTTON)
	{
		UpdateData();
		m_Cut-=dy;
		UpdateData(FALSE);
		doc->world.wall=(double)m_Cut/10.0;
		//OnReleasedcaptureCut(NULL,NULL);
	}
	else if(nFlags & MK_CONTROL)
	{
		doc->world.Groups[0].t+=dx;
		if(doc->world.Groups[0].t==360)
			doc->world.Groups[0].t=0;

		doc->world.Groups[0].a+=2*dx;
		if(doc->world.Groups[0].a==360)
			doc->world.Groups[0].a=0;

		doc->world.Groups[0].p+=3*dx;
		if(doc->world.Groups[0].p==360)
			doc->world.Groups[0].p=0;

		doc->world.Groups[1].t+=dx;
		if(doc->world.Groups[1].t==360)
			doc->world.Groups[1].t=0;

		doc->world.Groups[1].a+=2*dx;
		if(doc->world.Groups[1].a==360)
			doc->world.Groups[1].a=0;

		doc->world.Groups[1].p+=3*dx;
		if(doc->world.Groups[1].p==360)
			doc->world.Groups[1].p=0;

		doc->world.Groups[2].t+=dx;
		if(doc->world.Groups[2].t==360)
			doc->world.Groups[2].t=0;

		doc->world.Groups[2].a+=2*dx;
		if(doc->world.Groups[2].a==360)
			doc->world.Groups[2].a=0;

		doc->world.Groups[2].p+=3*dx;
		if(doc->world.Groups[2].p==360)
			doc->world.Groups[2].p=0;
	}
	else if(nFlags & MK_SHIFT)
	{
		for(int x=0;x<doc->world.GroupCount;x++)
		{
			doc->world.Groups[x].a+=dx;
			doc->world.Groups[x].t+=dy;
		}
	}

	if(nFlags)
	{
		MouseStart=point;
		OnUpdate(NULL,NULL,NULL);
	}

	drag=nFlags;
	
	CFormView::OnMouseMove(nFlags, point);
}

void CMy3DEngineView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CMy3DEngineDoc* doc=GetDocument();

	if(point.x<doc->world.vw && point.y<doc->world.vh)
	{
		LButtonDown=true;
		MouseStart=point;
	}

	CFormView::OnLButtonDown(nFlags, point);
}

void CMy3DEngineView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	LButtonDown=false;
	CFormView::OnLButtonUp(nFlags, point);
}

void CMy3DEngineView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CMy3DEngineDoc* doc=GetDocument();

	if(point.x<doc->world.vw && point.y<doc->world.vh)
	{
		RButtonDown=true;
		MouseStart=point;
	}
	
	CFormView::OnRButtonDown(nFlags, point);
}

void CMy3DEngineView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	RButtonDown=false;
	
	CFormView::OnRButtonUp(nFlags, point);
}

void CMy3DEngineView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	CMy3DEngineDoc* doc=GetDocument();
	doc->world.vw=cx-LeftBorder;
	doc->world.vh=cy;

	delete[]doc->world.zbuffer;
	doc->world.zbuffer=new double[doc->world.vw*doc->world.vh];

	Bitmap.DeleteObject();
	tempdc.DeleteDC();

	CDC* dc=GetDC();
	//CMy3DEngineDoc* doc=GetDocument();
	Bitmap.CreateCompatibleBitmap(dc,doc->world.vw,doc->world.vh);
	tempdc.CreateCompatibleDC(dc);
	tempdc.SelectObject(Bitmap);

	doc->world.tbit.DeleteObject();
	doc->world.tdc.DeleteDC();
	
	doc->world.tdc.CreateCompatibleDC(dc);
	doc->world.tbit.CreateCompatibleBitmap(dc,doc->world.vw,doc->world.vh);
	doc->world.tdc.SelectObject(doc->world.tbit);

	ReleaseDC(dc);
}

void CMy3DEngineView::ReleasedcaptureCut(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData();
	
	CMy3DEngineDoc* doc=GetDocument();
	doc->world.wall=(double)m_Cut/10.0;

	OnUpdate(NULL,NULL,NULL);

	*pResult = 0;
}

void CMy3DEngineView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	char* c=new char[256];
	
	switch(nChar)
	{
	case 38:	//up
		KeyUp=true;
		break;
	case 40:	//down
		KeyDown=true;
		break;
	case 37:	//left
		KeyLeft=true;
		break;
	case 39:	//right
		KeyRight=true;
		break;
	case 32:	//space
		KeySpace=true;
		break;
	case 66:	//B
		KeyB=true;
		break;
	case 13:	//enter
		Joystick();
		break;
	case 107:	//plus
		KeyPlus=true;
		break;
	case 109:	//minus
		KeyMinus=true;
		break;
#ifdef _DEBUG
	default:
		MessageBox((CString)"Down " + itoa(nChar,c,10));
#endif
	}

	delete[]c;

	CFormView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMy3DEngineView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{	
	switch(nChar)
	{
	case 38:	//up
		KeyUp=false;
		break;
	case 40:	//down
		KeyDown=false;;
		break;
	case 37:	//left
		KeyLeft=false;
		break;
	case 39:	//right
		KeyRight=false;
		break;
	case 32:	//space
		KeySpace=false;
		break;
	case 66:	//B
		KeyB=false;
		break;
	case 107:	//plus
		KeyPlus=false;
		break;
	case 109:	//minus
		KeyMinus=false;
		break;
	}
	
	CFormView::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CMy3DEngineView::Shoot()
{
	if(stimer<10)
		return;
	
	CMy3DEngineDoc* doc=GetDocument();

	CGroup a;

	CPolygon t;

	a.Polygons.InsertAt(0,t,4);

	//a.Polygons[0].x=new double[4];
	//a.Polygons[0].y=new double[4];
	//a.Polygons[0].z=new double[4];
	a.Polygons[0].PointCount=4;
	a.Polygons[0].color=RGB(0,255,0);
	a.Polygons[0].x[0]=0;
	a.Polygons[0].y[0]=1;
	a.Polygons[0].z[0]=1;
	a.Polygons[0].x[1]=0;
	a.Polygons[0].y[1]=1;
	a.Polygons[0].z[1]=-1;
	a.Polygons[0].x[2]=-5;
	a.Polygons[0].y[2]=1;
	a.Polygons[0].z[2]=-1;
	a.Polygons[0].x[3]=-5;
	a.Polygons[0].y[3]=1;
	a.Polygons[0].z[3]=1;

	//a.Polygons[1].x=new double[4];
	//a.Polygons[1].y=new double[4];
	//a.Polygons[1].z=new double[4];
	a.Polygons[1].PointCount=4;
	a.Polygons[1].color=RGB(0,255,0);
	a.Polygons[1].x[0]=0;
	a.Polygons[1].y[0]=-1;
	a.Polygons[1].z[0]=1;
	a.Polygons[1].x[1]=0;
	a.Polygons[1].y[1]=-1;
	a.Polygons[1].z[1]=-1;
	a.Polygons[1].x[2]=-5;
	a.Polygons[1].y[2]=-1;
	a.Polygons[1].z[2]=-1;
	a.Polygons[1].x[3]=-5;
	a.Polygons[1].y[3]=-1;
	a.Polygons[1].z[3]=1;

	//a.Polygons[2].x=new double[4];
	//a.Polygons[2].y=new double[4];
	//a.Polygons[2].z=new double[4];
	a.Polygons[2].PointCount=4;
	a.Polygons[2].color=RGB(0,255,0);
	a.Polygons[2].x[0]=0;
	a.Polygons[2].y[0]=1;
	a.Polygons[2].z[0]=1;
	a.Polygons[2].x[1]=0;
	a.Polygons[2].y[1]=-1;
	a.Polygons[2].z[1]=1;
	a.Polygons[2].x[2]=-5;
	a.Polygons[2].y[2]=-1;
	a.Polygons[2].z[2]=1;
	a.Polygons[2].x[3]=-5;
	a.Polygons[2].y[3]=1;
	a.Polygons[2].z[3]=1;

	//a.Polygons[3].x=new double[4];
	//a.Polygons[3].y=new double[4];
	//a.Polygons[3].z=new double[4];
	a.Polygons[3].PointCount=4;
	a.Polygons[3].color=RGB(0,255,0);
	a.Polygons[3].x[0]=0;
	a.Polygons[3].y[0]=1;
	a.Polygons[3].z[0]=-1;
	a.Polygons[3].x[1]=0;
	a.Polygons[3].y[1]=-1;
	a.Polygons[3].z[1]=-1;
	a.Polygons[3].x[2]=-5;
	a.Polygons[3].y[2]=-1;
	a.Polygons[3].z[2]=-1;
	a.Polygons[3].x[3]=-5;
	a.Polygons[3].y[3]=1;
	a.Polygons[3].z[3]=-1;

	a.x=doc->world.Groups[0].x;
	a.y=doc->world.Groups[0].y;
	a.z=doc->world.Groups[0].z;
	a.a=doc->world.Groups[0].a;

	a.dx=cos(a.a/180*3.14159);
	a.dy=sin(a.a/180*3.14159);

	a.dexp=0;

	doc->world.AddGroup(&a);

	stimer=0;
}
