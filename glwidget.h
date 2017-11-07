#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
//#include <QOpenGLFunctions>
#include <QtGui/QOpenGLFunctions_4_1_Core>
#include <QtOpenGLExtensions/QOpenGLExtensions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include<glm\glm.hpp>
#include<glm\gtc\matrix_transform.hpp>
#include "Model.h"
#include "Shader.h"
#include "Camera.h"
#include "TextureLoader.h"

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)
#define  CAMERA_FOV 20.0f

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_1_Core
{
	Q_OBJECT

public:
	GLWidget(QWidget *parent = 0);
	~GLWidget();

	QSize minimumSizeHint() const override;
	QSize sizeHint() const override;

	void load_preset(string path);
	void init_textures();

public slots:

	void cleanup();
	void nextCurrIndex();
	void preCurrIndex();
signals:
	

protected:
	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int width, int height) override;
	//处理鼠标事件
	void mousePressEvent(QMouseEvent *event) override;//按下
	void mouseReleaseEvent(QMouseEvent *event) override;//松开
	void mouseMoveEvent(QMouseEvent *event) override;//按下移动
	void wheelEvent(QWheelEvent *event) override;//滚轮

	void print_mat4(glm::mat4 m);


private:
	const float PI = 3.1415926536f;

	Model sphere;
	TextureLoader textureLoader;
	Shader mainShader;
	Camera camera;
	Camera * current_camera = &camera;
	glm::mat4 model, model_inverse_transepose;

	string material[6] = { "gold","grass","plastic","rusted_iron","wood","rock" };
	int curr_material_index = 3;
	const int width = 800, height = 600;
	const string sphere_model = "media/sphere.obj";

	GLuint albedoTex, normalTex, roughnessTex, aoTex, metallicTex;
	// lights
	// ------
	glm::vec3 lightPositions[3] = {
		glm::vec3(0.0f, 0.0f, 10.0f),
		glm::vec3(1.0f,2.0f,6.0f),
		glm::vec3(3.0f, 5.0f, 8.0f)
	};
	glm::vec3 lightColors[3] = {
		glm::vec3(150.0f, 150.0f, 150.0f),
		glm::vec3(150.0f, 150.0f, 150.0f),
		glm::vec3(150.0f, 150.0f, 150.0f)
	};
};

#endif
