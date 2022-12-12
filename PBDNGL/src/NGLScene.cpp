#include <QMouseEvent>
#include <QGuiApplication>

#include "NGLScene.h"
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include<ngl/ShaderLib.h>
#include<ngl/Util.h>
#include <iostream>
#include <ngl/Random.h>

NGLScene::NGLScene()
{
  // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
  setTitle("Blank NGL");
}


NGLScene::~NGLScene()
{
  std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
}



void NGLScene::resizeGL(int _w , int _h)
{
  m_win.width  = static_cast<int>( _w * devicePixelRatio() );
  m_win.height = static_cast<int>( _h * devicePixelRatio() );
}

const std::string_view ParticleShader="ParticleShader";
//give this shader a name

void NGLScene::initializeGL()
{
  // we must call that first before any other GL commands to load and link the
  // gl commands from the lib, if that is not done program will crash
  ngl::NGLInit::initialize();
  glClearColor(0.7f, 0.7f, 0.7f, 1.0f);			   // Grey Background
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
  // enable multisampling for smoother drawing
  glEnable(GL_MULTISAMPLE);
  m_generator=std::make_unique<Generator>(6);
  startTimer(10);

  //the basic color and shader
  ngl::ShaderLib::use(ngl::nglColourShader);

  m_view=ngl::lookAt({12,12,12},{0,0,0},{0,1,0});
  m_project=ngl::perspective(45.0f,1.0f,0.01f,50.0f);
  //useShader
  ngl::ShaderLib::loadShader(ParticleShader,"shaders/ParticleVertex.glsl","shaders/ParticleFragment.glsl");
  ngl::ShaderLib::use(ParticleShader);
  ngl::ShaderLib::setUniform("MVP",m_project*m_view);
  //ngl::ShaderLib::setUniform("Colour",1.0f,0.0f,0.0f,1.0f);
  glPointSize(5);//easy to see the particle
}

void NGLScene::timerEvent(QTimerEvent *_event)
{
  m_generator->update();
  update();
}

void NGLScene::paintGL()
{
  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0,0,m_win.width,m_win.height);

  auto rotX=ngl::Mat4::rotateX(m_win.spinXFace);
  auto rotY=ngl::Mat4::rotateY(m_win.spinXFace);
  m_mouseGlobalTX=rotX*rotY;
  m_mouseGlobalTX.m_m[3][0]=m_modelPos.m_x;
  m_mouseGlobalTX.m_m[3][1]=m_modelPos.m_y;
  m_mouseGlobalTX.m_m[3][2]=m_modelPos.m_z;

  ngl::ShaderLib::setUniform("MVP",m_project*m_view*m_mouseGlobalTX);
  m_generator->render();
}

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::keyPressEvent(QKeyEvent *_event)
{
  // this method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch (_event->key())
  {
  // escape key to quite
  case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS); break;
  case Qt::Key_Space :
      m_win.spinXFace=0;
      m_win.spinYFace=0;
      m_modelPos.set(ngl::Vec3::zero());

  break;
  default : break;
  }
  // finally update the GLWindow and re-draw

    update();
}
