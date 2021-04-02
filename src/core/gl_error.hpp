#ifndef JUST_SOME_GRAPHICS_SRC_GL_ERROR_HPP
#define JUST_SOME_GRAPHICS_SRC_GL_ERROR_HPP

// Ask Opengl for errors:
// Result is printed on the standard output
// usage :
//      GLCheckError(__FILE__,__LINE__);
void GLCheckError(const char *file, unsigned int line);

#endif
