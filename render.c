#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef WIN32
#include <Windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


#include "ac3d.h"

Private void col_set(long matno)
{
    ACMaterial *m = ac_palette_get_material(matno);
    ACCol rgba;
    static int lastcolset = -1;

    if (lastcolset == matno)
		return;
    else
	lastcolset = matno;

    rgba = m->rgb;
    rgba.a = 1.0-m->transparency;
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (float*)&rgba);

    rgba = m->ambient;
    rgba.a = 1.0-m->transparency;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (float *)&rgba);

    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, (float *)&m->emissive);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (float *)&m->specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, (float *)&m->shininess);

    if (rgba.a < 1.0)
	    {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
		}
    else
        glDisable(GL_BLEND);

}


Private void col_set_simple(long matno)
{
    ACMaterial *m = ac_palette_get_material(matno);

    glColor3fv((float *)&m->rgb);
}




Private void render(ACObject *ob)
{
    int n, s, sr;
    int st;

    glPushMatrix();

    glTranslated(ob->loc.x, ob->loc.y, ob->loc.z);

    if (ob->texture != -1)
		{
		static int lasttextureset = -1;
		//ACImage *i = ac_get_texture(ob->texture);
		ac_get_texture(ob->texture);
 
		glEnable(GL_TEXTURE_2D);

		if (ob->texture != lasttextureset)
			{
			glBindTexture(GL_TEXTURE_2D, ob->texture);
			lasttextureset = ob->texture;
			}
		}
	else
        glDisable(GL_TEXTURE_2D);


    for (s = 0; s < ob->num_surf; s++)
		{
		ACSurface *surf = &ob->surfaces[s];

		glNormal3fv((GLfloat *)&surf->normal);

		if (surf->flags & SURFACE_TWOSIDED)
			glDisable(GL_CULL_FACE);
		else
			glEnable(GL_CULL_FACE);

		st = surf->flags & 0xf;
		if (st == SURFACE_TYPE_CLOSEDLINE)
			{
			glDisable(GL_LIGHTING);

			glBegin(GL_LINE_LOOP);
			col_set_simple(surf->mat);
			}
		else
		if (st == SURFACE_TYPE_LINE)
			{
			glDisable(GL_LIGHTING);

			glBegin(GL_LINE_STRIP);
			col_set_simple(surf->mat);
			}
		else
			{
			glEnable(GL_LIGHTING);
			col_set(surf->mat); 
			if (surf->num_vertref == 3)
				glBegin(GL_TRIANGLE_STRIP);
			else
				glBegin(GL_POLYGON);
			}


		for (sr = 0; sr < surf->num_vertref; sr++)
			{
			ACVertex *v = &ob->vertices[surf->vertref[sr]];

			if (ob->texture > -1)
				{
				float tu = surf->uvs[sr].u;
				float tv = surf->uvs[sr].v;

				float tx = ob->texture_offset_x + tu * ob->texture_repeat_x;
				float ty = ob->texture_offset_y + tv * ob->texture_repeat_y;

				glTexCoord2f(tx, ty);
				}

			if (surf->flags & SURFACE_SHADED)
				glNormal3fv((GLfloat *)&v->normal);

			glVertex3fv((GLfloat *)v);
			}

		glEnd();
    }


    if (ob->num_kids)
	for (n = 0; n < ob->num_kids; n++)
	    render(ob->kids[n]); 

    glPopMatrix();
}


Prototype void ac_prepare_render()
{
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    glDisable( GL_COLOR_MATERIAL );

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}



Prototype void ac_render_object(ACObject *ob)
{
    render(ob);

}


Prototype int ac_display_list_render_object(ACObject *ob)
{
    GLuint  list;

    list = glGenLists(1);

    glNewList(list,GL_COMPILE);

    ac_render_object(ob);
    glEndList();
    return(list);

}


Prototype int ac_load_and_render_ac3d(char *fname)
{
    GLuint  list;
    ACObject *ob = ac_load_ac3d(fname);

    if (ob)
		{
		list = ac_display_list_render_object(ob);
		return((int)list);
		}
	else
		return(-1);

}



Prototype int ac_load_texture(char *name)
{
    int id = ac_load_rgb_image(name);

    if (id > -1)
    {
	ACImage *i = ac_get_texture(id);

	glBindTexture(GL_TEXTURE_2D, id);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 
			  i->depth, i->width, i->height,
			  (i->depth==1)?GL_LUMINANCE:
			  (i->depth==2)?GL_LUMINANCE_ALPHA:
			  (i->depth==3)?GL_RGB:
			  GL_RGBA,
			  GL_UNSIGNED_BYTE,
			  i->data);
    }
    return(id);
}
