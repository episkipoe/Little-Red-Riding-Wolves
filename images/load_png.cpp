#include <GL/glut.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <stdio.h>
#include <png.h>
#include <iostream>
#include <exception>
#include <string>
#include <map>
#include "textures.h"

using namespace std;

struct Image {
	unsigned long width;
	unsigned long height;
	GLubyte *data;
	bool hasAlpha;
};

map<string,GLuint> name_to_texture;
GLuint get_texture(string name) {
	return name_to_texture[name];
}

/*
 * http://blog.nobel-joergensen.com/2010/11/07/loading-a-png-as-texture-in-opengl-using-libpng/
*/

bool loadPngImage(const char *name, Image & image) {
    png_structp png_ptr;
    png_infop info_ptr;
    unsigned int sig_read = 0;
    FILE *fp;

    if ((fp = fopen(name, "rb")) == NULL)
        return false;

    /* Create and initialize the png_struct
     * with the desired error handler
     * functions.  If you want to use the
     * default stderr and longjump method,
     * you can supply NULL for the last
     * three parameters.  We also supply the
     * the compiler header file version, so
     * that we know if the application
     * was compiled with a compatible version
     * of the library.  REQUIRED
     */
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
            NULL, NULL, NULL);

    if (png_ptr == NULL) {
        fclose(fp);
        return false;
    }

    /* Allocate/initialize the memory
     * for image information.  REQUIRED. */
    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL) {
        fclose(fp);
        png_destroy_read_struct(&png_ptr, png_infopp_NULL, png_infopp_NULL);
        return false;
    }

    /* Set error handling if you are
     * using the setjmp/longjmp method
     * (this is the normal method of
     * doing things with libpng).
     * REQUIRED unless you  set up
     * your own error handlers in
     * the png_create_read_struct()
     * earlier.
     */
    if (setjmp(png_jmpbuf(png_ptr))) {
        /* Free all of the memory associated
         * with the png_ptr and info_ptr */
        png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);
        fclose(fp);
        /* If we get here, we had a
         * problem reading the file */
        return false;
    }

    /* Set up the output control if
     * you are using standard C streams */
    png_init_io(png_ptr, fp);

    /* If we have already
     * read some of the signature */
    png_set_sig_bytes(png_ptr, sig_read);

    /*
     * If you have enough memory to read
     * in the entire image at once, and
     * you need to specify only
     * transforms that can be controlled
     * with one of the PNG_TRANSFORM_*
     * bits (this presently excludes
     * dithering, filling, setting
     * background, and doing gamma
     * adjustment), then you can read the
     * entire image (including pixels)
     * into the info structure with this
     * call
     *
     * PNG_TRANSFORM_STRIP_16 |
     * PNG_TRANSFORM_PACKING  forces 8 bit
     * PNG_TRANSFORM_EXPAND forces to
     *  expand a palette into RGB
     */
    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, png_voidp_NULL);

    image.width = info_ptr->width;
    image.height = info_ptr->height;
    switch (info_ptr->color_type) {
        case PNG_COLOR_TYPE_RGBA:
            image.hasAlpha = true;
            break;
        case PNG_COLOR_TYPE_RGB:
            image.hasAlpha = false;
            break;
        default:
            cout << "Color type " << info_ptr->color_type << " not supported" << endl;
            png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
            fclose(fp);
            return false;
    }
    unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
    image.data = (unsigned char*) malloc(row_bytes * image.height);

    png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);

    for (size_t i = 0; i < image.height; i++) {
        // note that png is ordered top to
        // bottom, but OpenGL expect it bottom to top
        // so the order or swapped
        memcpy(image.data+(row_bytes * (image.height-1-i)), row_pointers[i], row_bytes);
    }

    /* Clean up after the read,
     * and free any memory allocated */
    png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);

    /* Close the file */
    fclose(fp);

    /* That's it */
    return true;
}

GLuint loadTexture(const string & file_name) {
	GLuint handle;
	Image image;
	if(!loadPngImage(file_name.c_str(), image)) {
		cout << "Failed to load " <<file_name<<endl;	
		return 0;
	}
	glGenTextures(1, &handle);
	glBindTexture(GL_TEXTURE_2D, handle);

	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, image.hasAlpha ? 4 : 3, image.width, image.height, 
		0, image.hasAlpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, image.data);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	return handle;
}

void loadImages() {
	name_to_texture["tree"] = loadTexture("images/tree01.png");
}

void draw_texture(std::string name, Point location, float size) {
	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, get_texture(name) );
	glPushMatrix();
		glTranslatef(location.x, location.y, 0);
		glScalef(size, size, size);
		glBegin( GL_QUADS );
			glTexCoord2d(0.0,0.0); glVertex2d(0.0,0.0);
			glTexCoord2d(1.0,0.0); glVertex2d(1.0,0.0);
			glTexCoord2d(1.0,1.0); glVertex2d(1.0,1.0);
			glTexCoord2d(0.0,1.0); glVertex2d(0.0,1.0);
		glEnd();
	glPopMatrix();
	glDisable( GL_TEXTURE_2D );
}

