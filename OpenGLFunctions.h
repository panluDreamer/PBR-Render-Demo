#ifndef OPENGLFUNCTIONS_H
#define OPENGLFUNCTIONS_H
#include <QObject>
#include <QtGui/QOpenGLFunctions_4_1_Core>
#include <QtOpenGLExtensions/QOpenGLExtensions>
#include"Log.h"
using BaseOpenGLFunctions = QOpenGLFunctions_4_1_Core;
class OpenGLFunctions : public BaseOpenGLFunctions
{
	Q_OBJECT

public:
	bool initializeOpenGLFunctions() override;

	void glTexStorage1D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width)
	{
		mGL_textureStorage.glTexStorage1D(target, levels, internalformat, width);
	}

	void glTexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
	{
		mGL_textureStorage.glTexStorage2D(target, levels, internalformat, width, height);
	}

	void glTexStorage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth)
	{
		mGL_textureStorage.glTexStorage3D(target, levels, internalformat, width, height, depth);
	}

private:
	QOpenGLExtension_ARB_texture_storage mGL_textureStorage;

};



#endif
