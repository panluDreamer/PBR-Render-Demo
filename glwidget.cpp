#include "glwidget.h"
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <math.h>
#include"Log.h"
GLWidget::GLWidget(QWidget *parent)
	: QOpenGLWidget(parent)
{
		QSurfaceFormat fmt = format();
		fmt.setAlphaBufferSize(8);
		setFormat(fmt);
}

GLWidget::~GLWidget()
{
	cleanup();
}

QSize GLWidget::minimumSizeHint() const
{
	return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
	return QSize(width, height);
}

static void qNormalizeAngle(int &angle)
{
	while (angle < 0)
		angle += 360 * 16;
	while (angle > 360 * 16)
		angle -= 360 * 16;
}
void GLWidget::load_preset(std::string path)
{
	std::ifstream fs(path);
	fs >> camera;
	camera.build();
	cout << "initialize camera..." << endl;
	fs.close();
}
void GLWidget::init_textures() {
	glDeleteTextures(1, &albedoTex);
	glDeleteTextures(1, &normalTex);
	glDeleteTextures(1, &aoTex);
	glDeleteTextures(1, &metallicTex);
	glDeleteTextures(1, &roughnessTex);
	string albedoTex_path = "media/resource/pbr/" + material[curr_material_index] + "/albedo.png";
	string normalTex_path = "media/resource/pbr/" + material[curr_material_index] + "/normal.png";
	string roughnessTex_path = "media/resource/pbr/" + material[curr_material_index] + "/roughness.png";
	string aoTex_path = "media/resource/pbr/" + material[curr_material_index] + "/ao.png";
	string metallicTex_path = "media/resource/pbr/" + material[curr_material_index] + "/metallic.png";
	albedoTex = textureLoader.CreateTexture(albedoTex_path.c_str(), true);
	normalTex = textureLoader.CreateTexture(normalTex_path.c_str(), false);
	aoTex = textureLoader.CreateTexture(aoTex_path.c_str(), false);
	metallicTex = textureLoader.CreateTexture(metallicTex_path.c_str(), false);
	roughnessTex = textureLoader.CreateTexture(roughnessTex_path.c_str(), false);
}
//slots
void GLWidget::cleanup(){
}
void GLWidget::nextCurrIndex() {

	curr_material_index = (curr_material_index + 1) % 6;
	init_textures();
	//Log::msg("curr_material_index = " + to_string(curr_material_index));
	//update GLWidget
	update();
}
void GLWidget::preCurrIndex() {
	if (curr_material_index >= 1) {
		curr_material_index--;
	}
	else {//=0
		curr_material_index = 5;
	}
	init_textures();
	//Log::msg("curr_material_index = " + to_string(curr_material_index));
}
void GLWidget::print_mat4(glm::mat4 m) {
	cout << "--------------------------" << endl;
	for (int i = 0; i < 4;i++) {
		for (int j = 0; j < 4;j++) {
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
	cout << "--------------------------" << endl;
}
void GLWidget::initializeGL()
{
	// In this example the widget's corresponding top-level window can change
	// several times during the widget's lifetime. Whenever this happens, the
	// QOpenGLWidget's associated context is destroyed and a new one is created.
	// Therefore we have to be prepared to clean up the resources on the
	// aboutToBeDestroyed() signal, instead of the destructor. The emission of
	// the signal will be followed by an invocation of initializeGL() where we
	// can recreate all resources.
	//connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &GLWidget::cleanup);
	//Log::msg("initializeGL function");
	initializeOpenGLFunctions();
	//init OpenGL functions in class TextureLoader
	textureLoader.init();
	//init model
	sphere.init(sphere_model, true, true, true);
	Log::msg("load model completed");
	//init textures
	//Log::msg("before init textures");
	init_textures();
	//Log::msg("after init textures");
	//init camera
	load_preset("media/preset/preset.txt");
	camera.setDistanceVelocity(0.0f);
	camera.setPanVelocity(vec2(0.0, 0.0));
	camera.setAngularVelocity(vec2(0, 0));
	camera.setProjection(CAMERA_FOV * PI / 180.0f, (float)width / height, 0.1f, 100.0f);
	camera.setViewportSize(vec2(width, height));

	mainShader.init("shader/main.vert", "shader/main.frag");
	model = glm::scale(mat4(1.0f), vec3(0.5f, 0.5f, 0.5f)) * glm::translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f));
	model_inverse_transepose = glm::transpose(glm::inverse(model));
	Log::msg("render begin");
}


void GLWidget::paintGL()
{
	//Log::msg("paintGL function");
	//elapsed time设置为0.016
	current_camera->frameMove(0.016);
	glm::vec2 velocity = current_camera->getAngularVelocity();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	mainShader.use();
	glm::mat4 projection = current_camera->getProjectionMatrix();
	mainShader.bind_mat4("projection", projection);
	glm::mat4 view = current_camera->getViewMatrix();
	mainShader.bind_mat4("view", view);
	mainShader.bind_mat4("model", model);
	mainShader.bind_mat4("ModelInverseTranspose", model_inverse_transepose);
	mainShader.bind_texture("albedoMap", albedoTex, 0, GL_TEXTURE_2D);
	mainShader.bind_texture("normalMap", normalTex, 1, GL_TEXTURE_2D);
	mainShader.bind_texture("metallicMap", metallicTex, 2, GL_TEXTURE_2D);
	mainShader.bind_texture("roughnessMap", roughnessTex, 3, GL_TEXTURE_2D);
	mainShader.bind_texture("aoMap", aoTex, 4, GL_TEXTURE_2D);
	mainShader.bind_vec3("camPos", current_camera->getEyePosition());
	for (unsigned int i = 0; i < 3; i++) {
		mainShader.bind_vec3(("lightPositions[" + std::to_string(i) + "]").c_str(), lightPositions[i]);
		mainShader.bind_vec3(("lightColors[" + std::to_string(i) + "]").c_str(), lightColors[i]);
	}
	sphere.render();
	//cout << "velocity:" << velocity.x << "," << velocity.y << endl;
	//控制拖动减速效果
	if (abs(velocity.x) > 1e-2 || abs(velocity.y) > 1e-2) {
		update();
	}
	//Log::msg("first render loop");
}

void GLWidget::resizeGL(int w, int h)
{
	//Log::msg("resizeGL function");
	if (h != 0) {
		float aspect = float(w) / h;
		camera.setProjection(CAMERA_FOV * PI / 180.0f, aspect, 0.1f, 100.0f);
		//加上这里可以保证窗口大小变化后，结果保持在窗口中间
		glViewport(0, 0, w, h);
	}
}

void GLWidget::mousePressEvent(QMouseEvent *event){
	if (event->buttons()==Qt::LeftButton) {
		//cout << "pressed:(x,y)=(" << event->x() << "," << event->y() << ")" << endl;
		current_camera->mousePos = glm::vec2(float(event->x()), float(event->y()));
		current_camera->attenuation = 4.0f;
	}
}
void GLWidget::mouseReleaseEvent(QMouseEvent *event) {

}
void GLWidget::mouseMoveEvent(QMouseEvent *event){
	glm::vec2 new_mouse_pos = glm::vec2(float(event->x()), float(event->y()));
	//cout << "move:(x,y)=(" << event->x() << "," << event->y() << ")" << endl;
	vec2 delta = current_camera->mousePos - new_mouse_pos;
	if (event->buttons()==Qt::LeftButton) {
		delta = -delta;
		current_camera->setAngularVelocity(current_camera->getAngularVelocity() - delta);
		current_camera->mousePos = new_mouse_pos;
		//更新Widget
		update();
	}
	else if (event->buttons() == Qt::RightButton) {

	}
	else if (event->buttons() == Qt::MiddleButton) {

	}
	current_camera->mousePos = new_mouse_pos;
}
void GLWidget::wheelEvent(QWheelEvent *event) {
	float sign = 1;
	if (event->delta() > 0) {//zoom in
		sign = 1;
	}
	else {//zoom out
		sign = -1;
	}
	current_camera->setDistance(current_camera->getDistance() - float(sign) / 4.0f);
	update();
}