// 3D EngineView.cpp : implementation of the CMy3DEngineView class
//

#include "stdafx.h"
#include "3DEngine.h"

#include "3DEngineDoc.h"
#include "3DEngineView.h"

#include "math.h"

#include "mmsystem.h"

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
	ON_BN_CLICKED(IDC_UP, OnUp)
	ON_BN_CLICKED(IDC_RIGHT, OnRight)
	ON_BN_CLICKED(IDC_DOWN, OnDown)
	ON_BN_CLICKED(IDC_LEFT, OnLeft)
	ON_BN_CLICKED(IDC_UP2, OnUp2)
	ON_BN_CLICKED(IDC_RIGHT2, OnRight2)
	ON_BN_CLICKED(IDC_DOWN2, OnDown2)
	ON_BN_CLICKED(IDC_LEFT2, OnLeft2)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_JOYSTICK, OnJoystick)
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

	COLORREF color;
	color=RGB(255,0,0);
	RedPen.CreatePen(0,1,color);
	color=RGB(127,127,255);
	BluePen.CreatePen(0,1,color);
	PolygonCount=0;
}

CMy3DEngineView::~CMy3DEngineView()
{
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

void CMy3DEngineView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CMy3DEngineDoc* doc=GetDocument();

	if(doc->world.ca<0)
		doc->world.ca+=360;
	else if(doc->world.ca>=360)
		doc->world.ca-=360;

	World=doc->world;

	dc=GetDC();

	dc->Rectangle(0,0,World.vw,World.vh);

	//for(int counter=0;counter<1;counter++)
	//{
		/*COLORREF color;
		if(counter==0)
		{
			World.cx-=.4;
			dc->SelectObject(&RedPen);
		}
		else
		{
			World.cx+=.8;
			dc->SelectObject(&BluePen);
		}*/
	
	if(PolygonCount>0)
		delete[]Polygons;
	PolygonCount=0;
	CLine l;
	CPolygon pg;
	double a,t,p,d;

	for(int x=0;x<World.GroupCount;x++)
	{	
		if(World.Groups[x].Visible)
		{
			for(int y=0;y<World.Groups[x].LineCount;y++)
			{	
				l=World.Groups[x].Lines[y];

				if(l.y1!=0 || l.z1!=0)
				{
					d=sqrt(pow(l.y1,2)+pow(l.z1,2));
					t=GetA(l.y1,l.z1);
					t+=World.Groups[x].t;
					if(t<0)
						t+=360;
					if(t>=360)
						t-=360;
					l.y1=GetX(t,d);
					l.z1=GetY(t,d);
				}

				if(l.y2!=0 || l.z2!=0)
				{
					d=sqrt(pow(l.y2,2)+pow(l.z2,2));
					t=GetA(l.y2,l.z2);
					t+=World.Groups[x].t;
					if(t<0)
						t+=360;
					if(t>=360)
						t-=360;
					l.y2=GetX(t,d);
					l.z2=GetY(t,d);
				}

				if(l.x1!=0 || l.z1!=0)
				{
					d=sqrt(pow(l.x1,2)+pow(l.z1,2));
					p=GetA(l.x1,l.z1);
					p+=World.Groups[x].p;
					if(p<0)
						a+=360;
					if(p>=360)
						p-=360;
					l.x1=GetX(p,d);
					l.z1=GetY(p,d);
				}

				if(l.x2!=0 || l.z2!=0)
				{
					d=sqrt(pow(l.x2,2)+pow(l.z2,2));
					p=GetA(l.x2,l.z2);
					p+=World.Groups[x].p;
					if(p<0)
						p+=360;
					if(p>=360)
						p-=360;
					l.x2=GetX(p,d);
					l.z2=GetY(p,d);
				}

				if(l.x1!=0 || l.y1!=0)
				{
					d=sqrt(pow(l.x1,2)+pow(l.y1,2));
					a=GetA(l.x1,l.y1);
					a+=World.Groups[x].a;
					if(a<0)
						a+=360;
					if(a>=360)
						a-=360;
					l.x1=GetX(a,d);
					l.y1=GetY(a,d);
				}

				if(l.x2!=0 || l.y2!=0)
				{
					d=sqrt(pow(l.x2,2)+pow(l.y2,2));
					a=GetA(l.x2,l.y2);
					a+=World.Groups[x].a;
					if(a<0)
						a+=360;
					if(a>=360)
						a-=360;
					l.x2=GetX(a,d);
					l.y2=GetY(a,d);
				}

				l.x1+=World.Groups[x].x;
				l.y1+=World.Groups[x].y;
				l.z1+=World.Groups[x].z;
				l.x2+=World.Groups[x].x;
				l.y2+=World.Groups[x].y;
				l.z2+=World.Groups[x].z;
				DrawLine(l);
			}

			for(y=0;y<World.Groups[x].PolygonCount;y++)
			{	
				pg=World.Groups[x].Polygons[y];

				for(int z=0;z<World.Groups[x].Polygons[y].PointCount;z++)
				{
					if(pg.y[z]!=0 || pg.z[z]!=0)
					{
						d=sqrt(pow(pg.y[z],2)+pow(pg.z[z],2));
						t=GetA(pg.y[z],pg.z[z]);
						t+=World.Groups[x].t;
						if(t<0)
							t+=360;
						if(t>=360)
							t-=360;
						pg.y[z]=GetX(t,d);
						pg.z[z]=GetY(t,d);
					}

					if(pg.x[z]!=0 || pg.z[z]!=0)
					{
						d=sqrt(pow(pg.x[z],2)+pow(pg.z[z],2));
						p=GetA(pg.x[z],pg.z[z]);
						p+=World.Groups[x].p;
						if(p<0)
							a+=360;
						if(p>=360)
							p-=360;
						pg.x[z]=GetX(p,d);
						pg.z[z]=GetY(p,d);
					}

					if(pg.x[z]!=0 || pg.y[z]!=0)
					{
						d=sqrt(pow(pg.x[z],2)+pow(pg.y[z],2));
						a=GetA(pg.x[z],pg.y[z]);
						a+=World.Groups[x].a;
						if(a<0)
							a+=360;
						if(a>=360)
							a-=360;
						pg.x[z]=GetX(a,d);
						pg.y[z]=GetY(a,d);
					}

					pg.x[z]+=World.Groups[x].x;
					pg.y[z]+=World.Groups[x].y;
					pg.z[z]+=World.Groups[x].z;
				}
				AddPolygon(&pg);
			}
		}
	}
	DrawPolygons();
}

void CMy3DEngineView::DrawLine(CLine Line)
{
	double x1,y1,x2,y2,dx,dy,dz,dt,a,t;

	dx=Line.x1-World.cx;
	dy=Line.y1-World.cy;
	dz=Line.z1-World.cz;
	dt=sqrt(pow(dx,2)+pow(dy,2));

	a=GetA(dx,dy);
	t=GetA(dt,dz);
	//a=atan(dy/dx)/3.14159*180;
	//t=atan(dz/dt)/3.14159*180;

	//if(dx<0)
	//	a+=180;
	//else if(dx>0 && dy<0)
	//	a+=360;

	//if(dt<0)
	//	t+=180;
	//else if(dt>0 && dz<0)
	//	t+=360;

	if(World.ca<90 && a>270)
		a-=360;
	else if(World.ca>270 && a<90)
		a+=360;
	if(World.ct<90 && t>270)
		t-=360;
	else if(World.ct>270 && a<90)
		t+=360;

	//if(dy>0 && dx==0)
	//	a=90;
	//else if(dy<0 && dx==0)
	//	a=270;

	x1=World.vw-((a-(World.ca-(World.cw/2)))/World.cw*World.vw);
	y1=World.vh-((t-(World.ct-(World.ch/2)))/World.ch*World.vh);

	dx=Line.x2-World.cx;
	dy=Line.y2-World.cy;
	dz=Line.z2-World.cz;
	dt=sqrt(pow(dx,2)+pow(dy,2));

	a=GetA(dx,dy);
	t=GetA(dt,dz);
	//a=atan(dy/dx)/3.14159*180;
	//t=atan(dz/dt)/3.14159*180;

	//if(dx<0)
	//	a+=180;
	//else if(dx>0 && dy<0)
	//	a+=360;

	//if(dt<0)
	//	t+=180;
	//else if(dt>0 && dz<0)
	//	t+=360;

	if(World.ca<90 && a>270)
		a-=360;
	else if(World.ca>270 && a<90)
		a+=360;
	if(World.ct<90 && t>270)
		t-=360;
	else if(World.ct>270 && a<90)
		t+=360;

	//if(dy>0 && dx==0)
	//	a=90;
	//else if(dy<0 && dx==0)
	//	a=270;

	x2=World.vw-((a-(World.ca-(World.cw/2)))/World.cw*World.vw);
	y2=World.vh-((t-(World.ct-(World.ch/2)))/World.ch*World.vh);

	dc->MoveTo(x1,y1);
	dc->LineTo(x2,y2);
}

void CMy3DEngineView::OnDraw(CDC* pDC) 
{
	OnUpdate(NULL,NULL,NULL);	
	
}

void CMy3DEngineView::OnUp() 
{	
	GetDocument()->world.cy++;
	OnUpdate(NULL,NULL,NULL);
	
}

void CMy3DEngineView::OnRight() 
{
	GetDocument()->world.cx++;
	OnUpdate(NULL,NULL,NULL);
	
}

void CMy3DEngineView::OnDown() 
{
	GetDocument()->world.cy--;
	OnUpdate(NULL,NULL,NULL);
	
}

void CMy3DEngineView::OnLeft() 
{
	GetDocument()->world.cx--;
	OnUpdate(NULL,NULL,NULL);
	
}

void CMy3DEngineView::OnUp2() 
{
	GetDocument()->world.ct++;
	OnUpdate(NULL,NULL,NULL);
	
}

void CMy3DEngineView::OnRight2() 
{
	GetDocument()->world.ca--;
	OnUpdate(NULL,NULL,NULL);
	
}

void CMy3DEngineView::OnDown2() 
{
	GetDocument()->world.ct--;
	OnUpdate(NULL,NULL,NULL);
	
}

void CMy3DEngineView::OnLeft2()
{
	GetDocument()->world.ca++;
	OnUpdate(NULL,NULL,NULL);
	
}

void CMy3DEngineView::OnTimer(UINT nIDEvent)
{
	CMy3DEngineDoc* doc=GetDocument();

	doc->world.Groups[0].t++;
	if(doc->world.Groups[0].t>=360)
		doc->world.Groups[0].t-=360;

	doc->world.Groups[0].a+=2;
	if(doc->world.Groups[0].a>=360)
		doc->world.Groups[0].a-=360;

	doc->world.Groups[0].p+=3;
	if(doc->world.Groups[0].p>=360)
		doc->world.Groups[0].p-=360;

	OnUpdate(NULL,NULL,NULL);

	/*JOYINFO info;

	joyGetPos(JOYSTICKID1, &info);
	
	double xval=info.wXpos;
	double xmax=JoyCap.wXmax;
	double xmin=JoyCap.wXmin;
	double xmid=(xmax-xmin)/double(2);
	double xlen=xmax-xmid;
	double xscale=xlen/double(6);
	double xscaled=(xval-xmid)/xscale;

	double yval=info.wYpos;
	double ymax=JoyCap.wYmax;
	double ymin=JoyCap.wYmin;
	double ymid=(ymax-ymin)/double(2);
	double ylen=ymax-ymid;
	double yscale=ylen/double(6);
	double yscaled=(yval-ymid)/yscale;

	if(fabs(xscaled)<1)
		xscaled=0;
	else
		xscaled--;
	if(fabs(yscaled)<1)
		yscaled=0;
	else
		yscaled--;

	yscaled=-yscaled;

	CMy3DEngineDoc* doc=GetDocument();

	doc->world.ca-=xscaled;
	doc->world.ca=fmod(doc->world.ca,360);
	double dx,dy,ds;
	dx=1;
	dy=tan(doc->world.ca/180*3.14159);
	ds=sqrt(pow(dx,2)+pow(dy,2))/yscaled;
	dx/=ds;
	dy/=ds;
	
	if((doc->world.ca>90 && doc->world.ca<180) || doc->world.ca>270)
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
	}

	OnUpdate(NULL,NULL,NULL);
	
	CFormView::OnTimer(nIDEvent);
	*/
}

void CMy3DEngineView::OnJoystick() 
{
	SetTimer(0,50,NULL);
	/*static bool joyon=false;

	if(!joyon)
	{
		joySetCapture(m_hWnd,JOYSTICKID1, 200, TRUE);
		joySetThreshold(JOYSTICKID1,1);
		joyGetDevCaps(JOYSTICKID1,&JoyCap,sizeof(JOYCAPS));

		SetTimer(0,200,NULL);
	}
	else
	{
		KillTimer(0);
		joyReleaseCapture(JOYSTICKID1);
	}

	joyon=!joyon;*/
	
}

inline double CMy3DEngineView::GetA(double x, double y)
{
	double a=atan(y/x)/3.14159*180;

	if(x<0)
		a+=180;
	else if(x>0 && y<0)
		a+=360;

	if(y>0 && x==0)
		a=90;
	else if(y<0 && x==0)
		a=270;

	return a;
}

double CMy3DEngineView::GetX(double a, double d)
{
	double x=1,y=0,s;

	if(a==90 || a==270)
		x=0;
	else
	{
		y=tan(a/180*3.14159);

		if(a>90 && a<270)
			x=-1;

		s=sqrt(1+pow(y,2));

		x*=d;
		x/=s;
	}

	return x;
}

double CMy3DEngineView::GetY(double a, double d)
{
	double x=1,y=0,s;

	if(a==90)
		y=d;
	else if(a==270)
		y=-d;
	else
	{
		y=tan(a/180*3.14159);

		if(a<180)
			y=fabs(y);
		else
			y=-fabs(y);

		s=sqrt(1+pow(y,2));

		y*=d;
		y/=s;
	}

	return y;
}

void CMy3DEngineView::DrawPolygon(CPolygon* Polygon)
{
	double dx,dy,dz,dt,a,t;
	double* x;
	double* y;

	x=new double[Polygon->PointCount];
	y=new double[Polygon->PointCount];

	for(int c=0;c<Polygon->PointCount;c++)
	{
		dx=Polygon->x[c]-World.cx;
		dy=Polygon->y[c]-World.cy;
		dz=Polygon->z[c]-World.cz;
		dt=sqrt(pow(dx,2)+pow(dy,2));

		a=GetA(dx,dy);
		t=GetA(dt,dz);

		if(World.ca<90 && a>270)
			a-=360;
		else if(World.ca>270 && a<90)
			a+=360;
		if(World.ct<90 && t>270)
			t-=360;
		else if(World.ct>270 && a<90)
			t+=360;

		x[c]=World.vw-((a-(World.ca-(World.cw/2)))/World.cw*World.vw);
		y[c]=World.vh-((t-(World.ct-(World.ch/2)))/World.ch*World.vh);
	}

	POINT* points=new POINT[Polygon->PointCount];

	for(c=0;c<Polygon->PointCount;c++)
	{
		points[c].x=x[c];
		points[c].y=y[c];
	}

	CBrush* brush=new CBrush;
	CBrush* oldbrush;
	brush->CreateSolidBrush(Polygon->color);
	oldbrush=dc->SelectObject(brush);

	dc->Polygon(points,Polygon->PointCount);

	dc->SelectObject(oldbrush);
	delete brush;
}

void CMy3DEngineView::AddPolygon(CPolygon *Polygon)
{
	int index=0;
	double dist=0,dist2=0;
	for(int x=0;x<Polygon->PointCount;x++)
	{
		dist+=sqrt(pow(Polygon->x[x]-World.cx,2)+pow(Polygon->y[x]-World.cy,2)+pow(Polygon->z[x]-World.cz,2));
	}
	dist/=Polygon->PointCount;

	for(x=0;x<PolygonCount;x++)
	{
		dist2=0;
		for(int y=0;y<Polygons[x].PointCount;y++)
		{
			dist2+=sqrt(pow(Polygons[x].x[y]-World.cx,2)+pow(Polygons[x].y[y]-World.cy,2)+pow(Polygons[x].z[y]-World.cz,2));
		}
		dist2/=Polygons[x].PointCount;
		if(dist>dist2)
		{
			index=x;
			break;
		}
		else
			index=x+1;
	}
	
	if(PolygonCount>0)
	{
		CPolygon* tempPolygons=new CPolygon[PolygonCount];
		for(x=0;x<PolygonCount;x++)
			tempPolygons[x]=Polygons[x];

		delete[]Polygons;
		Polygons=new CPolygon[PolygonCount+1];

		for(x=0;x<index;x++)
			Polygons[x]=tempPolygons[x];

		Polygons[index]=*Polygon;

		for(x=index+1;x<PolygonCount+1;x++)
			Polygons[x]=tempPolygons[x-1];

		delete[]tempPolygons;
	}
	else
	{
		Polygons=new CPolygon[1];
		Polygons[0]=*Polygon;
	}

	PolygonCount++;
}

void CMy3DEngineView::DrawPolygons()
{
	for(int x=0;x<PolygonCount;x++)
		DrawPolygon(&Polygons[x]);
}
