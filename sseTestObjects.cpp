#include "sseTestObjects.hpp"

objAirplane::objAirplane()
{

}

void objAirplane::DrawObject(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader)
{
    static float airplane[9][3] = {
        { 0.0f,  0.5f, -4.5f},
        { 3.0f,  0.5f, -4.5f},
        { 3.0f,  0.5f, -3.5f},
        { 0.0f,  0.5f,  0.5f},
        { 0.0f,  0.5f,  3.25f},
        { 0.0f, -0.5f,  5.5f},
        {-3.0f,  0.5f, -3.5f},
        {-3.0f,  0.5f, -4.5f},
        { 0.0f, -0.5f, -4.5f}
    };

    glColor3f(1.00, 0.19, 0.69); /* violet: r=1, g=.19, b=.69 */

    glBegin(GL_LINE_LOOP);
        glVertex3fv(airplane[6]);
        glVertex3fv(airplane[7]);
        glVertex3fv(airplane[1]);
        glVertex3fv(airplane[2]);
        glVertex3fv(airplane[4]);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex3fv(airplane[0]);
        glVertex3fv(airplane[4]);
        glVertex3fv(airplane[5]);
        glVertex3fv(airplane[8]);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex3fv(airplane[6]);
        glVertex3fv(airplane[3]);
        glVertex3fv(airplane[2]);
    glEnd();

    return;
}

objTriangle::objTriangle()
{

}

void objTriangle::DrawObject(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader)
{
	gluLookAt(0, 0, 6,     0, 0, 0,     0, 1, 0);
	//eyeX, eyeY, eyeZ
    //Specifies the position of the eye point.
	//centerX, centerY, centerZ
    //Specifies the position of the reference point.
    //upX, upY, upZ
    //Specifies the direction of the up vector.

    glBegin (GL_TRIANGLES);
    glVertex3f(0, 1, 0);
    glVertex3f(-1, 0, 0);
	glVertex3f(1, 0, 0);
    glEnd();
}
	
obj3DGrid::obj3DGrid()
{
	
}

void obj3DGrid::PreProcess(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader) {

}

void obj3DGrid::DrawObject(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader)
{
    for(float i = -200; i <= 200; i += 1)
    {
		glColor3ub(0, 255, 0);

        glBegin(GL_LINES);

        glVertex3f(-200, 0, i);
        glVertex3f(200, 0, i);
        glVertex3f(i, 0, -200);
        glVertex3f(i, 0, 200);

        glEnd();
    }
}

objPolygon::objPolygon()
{
	
}

void objPolygon::DrawObject(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader)
{
	glColor3f(1.0,1.0,1.0);
	gluLookAt(0, 0, 2,     .5, .5, 0,     0, 1, 0);
	glBegin(GL_POLYGON);
	glVertex3f(0.25, 0.25, 0.0);
	glVertex3f(0.75,0.25,0.0);
	glVertex3f(0.75,0.75,0.0);
	glVertex3f(0.25,0.75,0.0);
	glEnd();
}

objIcosahedron::objIcosahedron()
{
	
}

void objIcosahedron::DrawObject(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader)
{
	float X=.525731112119133606;
	float Z=.850650808352039932;

	static GLfloat vdata[12][3] = {
		{-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},    
		{0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},    
		{Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0} 
	};

	static GLuint tindices[20][3] = { 
		{0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},    
		{8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},    
		{7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6}, 
		{6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11} };

	int i;

	gluLookAt(0, 0, 2,     .5, .5, 0,     0, 1, 0);

	glBegin(GL_TRIANGLES);    
	for (i = 0; i < 20; i++) {    
		//glColor3f(1.0,1.0,1.0);
		glVertex3fv(&vdata[tindices[i][0]][0]); 
		glVertex3fv(&vdata[tindices[i][1]][0]); 
		glVertex3fv(&vdata[tindices[i][2]][0]); 
	}
	glEnd();
}

objCube::objCube()
{
	
}
	
void objCube::DrawObject(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader)
{
   glColor3f (1.0, 1.0, 1.0);
   //glLoadIdentity ();             /* clear the matrix */
           /* viewing transformation  */
   //glScalef (1.0, 2.0, 1.0);      /* modeling transformation */ 
   glutWireCube (3.0);
}

objSphere::objSphere()
{

}

void objSphere::DrawObject(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader)
{
   glColor3f (1.0, 1.0, 1.0);

   glutWireSphere(1.0, 20, 16);
}


objSolarSystem::objSolarSystem()
{
	m_year=0;
	m_day=0;
	AcceptEvents();
}

void objSolarSystem::DrawObject(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader)
{
   static int iCurrentTick=SDL_GetTicks();
   static int iNextyAnim=iCurrentTick+50;
   static int iNextdAnim=iCurrentTick+50;

   glClear (GL_COLOR_BUFFER_BIT);
   glColor3f (1.0, 1.0, 1.0);

   //if (m_pEventMappings->m_bEventUp) m_day = (m_day - 10) % 360;
   //if (m_pEventMappings->m_bEventDown) m_year = (m_year + 5) % 360;

   if (iCurrentTick>iNextyAnim)
   {
	   m_year = (m_year + 5) % 360;
       iNextyAnim=iCurrentTick+60;
   }

   if (iCurrentTick>iNextdAnim)
   {
		m_day = (m_day - 10) % 360;
		iNextdAnim=iCurrentTick+20;
   }

   iCurrentTick=SDL_GetTicks();
   glPushMatrix();
   glutWireSphere(1, 20, 16);   /* draw sun */
   glRotatef ((GLfloat) m_year, 0.0, 10.0, 0.0);
   glTranslatef (2.0, 0.0, 0.0);
   glRotatef ((GLfloat) m_day, 0.0, 10.0, 0.0);
   glutWireSphere(0.2, 10, 8);    /* draw smaller planet */
   glPopMatrix();
}
