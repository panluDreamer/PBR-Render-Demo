#include "OpenGLFunctions.h"
bool OpenGLFunctions::initializeOpenGLFunctions()
{
	Log::msg("initialize openGL functions");
	if (!BaseOpenGLFunctions::initializeOpenGLFunctions())
	{
		Log::msg("Unable to initialize OpenGLFunctions");
		return false;
	}

	if (!mGL_textureStorage.initializeOpenGLFunctions())
	{
		Log::msg("Unable to load required OpenGL extensions for OpenGLFunctions");
		return false;
	}

	return true;
}
