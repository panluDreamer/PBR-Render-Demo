#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <QObject>
#include <QtGui/QOpenGLFunctions_4_1_Core>
#include <QtOpenGLExtensions/QOpenGLExtensions>
#include"Log.h"
#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"
class TextureLoader : public QObject,protected QOpenGLFunctions_4_1_Core
{
	Q_OBJECT

public:
	void init() {
		initializeOpenGLFunctions();
	}

	 GLuint CreateTexture(const char *path, bool srgb) {
		GLuint textureID;
		glGenTextures(1, &textureID);

		int width, height, nrComponents;
		stbi_set_flip_vertically_on_load(false);//设置为false，表示不翻转，实际硬盘上的存储会是上下反的
		unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
		if (data)
		{
			GLenum format;
			//cout << "component = " << nrComponents << endl;
			if (nrComponents == 1)
				format = GL_RED;
			else if (nrComponents == 3)
				format = GL_RGB;
			else if (nrComponents == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, textureID);
			if (srgb) {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, width, height, 0, format, GL_UNSIGNED_BYTE, data);//GL_SRGB_ALPHA
			}
			else {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);//GL_SRGB_ALPHA
			}

			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(data);
		}
		else
		{
			std::cout << "Texture failed to load at path: " << path << std::endl;
			stbi_image_free(data);
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		return textureID;
	}


};
#endif