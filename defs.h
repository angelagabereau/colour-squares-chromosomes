//**********************************************************************
//	Structures etc.
//**********************************************************************

class acolor
{

	public:
		GLdouble r, g, b, a;
		acolor(GLdouble rr, GLdouble gg, GLdouble bb)
		{
			r = rr; g = gg; b = bb; a = 1.0;
		}
};

//*********************************************************************************
//	General OpenGL Definitions.
//*********************************************************************************

void glVertex(GLint x, GLint y)			{ glVertex2i(x,y); }
void glVertex(GLdouble x, GLdouble y)	{ glVertex2f(x,y); }

void glColor(GLdouble r, GLdouble g, GLdouble b)	{ glColor3f(r,g,b); }
void glColor(acolor c) { glColor3f (c.r, c.g, c.b); }

void glRect(GLint x1, GLint y1, GLint x2,GLint y2)	{ glRecti(x1,y1,x2,y2); }


//**********************************************************************
//	Random function.
//**********************************************************************

#define random(n) (rand()%n)