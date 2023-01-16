#include <QMouseEvent>
#include <QGuiApplication>
#include "NGLScene.h"
#include <ngl/NGLInit.h>
#include"SimulationSolver.h"
#include <ngl/VAOPrimitives.h>
#include<ngl/ShaderLib.h>
#include<ngl/Util.h>
#include <iostream>
#include <ngl/Random.h>
#include <ngl/Transformation.h>

NGLScene::NGLScene()
{
  // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
  //setTitle("Blank NGL");
    setFocus();

}


NGLScene::~NGLScene()
{
  std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
}



void NGLScene::resizeGL(int _w , int _h)
{
  m_win.width  = static_cast<int>( _w * devicePixelRatio() );
  m_win.height = static_cast<int>( _h * devicePixelRatio() );
  //m_text->setScreenSize(_w,_h);
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
 
  m_particleGenerator=std::make_unique<particleGenerator>(50);
  
  std::cout<<m_particleGenerator->get_particleInverseMass(2)<<'\n';

  //the basic color and shader
  ngl::ShaderLib::use(ngl::nglColourShader);

  m_view=ngl::lookAt({20,20,20},{0,0,0},{0,1,0});
  m_project=ngl::perspective(45.0f,1.0f,0.01f,50.0f);
  //useShader
  ngl::ShaderLib::loadShader(ParticleShader,"shaders/ParticleVertex.glsl","shaders/ParticleFragment.glsl");
  ngl::ShaderLib::use(ParticleShader);
  ngl::ShaderLib::setUniform("MVP",m_project*m_view);
  //ngl::ShaderLib::setUniform("Colour",1.0f,0.0f,0.0f,1.0f);
  glPointSize(3);//easy to see the particle
  
  //text
  //m_text=std::make_unique<ngl::Text>("fonts/FreeSans.ttf",18);
  //m_text->setColour(1.0f,1.0f,0.0f);

  //create the floor
  ngl::VAOPrimitives::createLineGrid("floor",20,20,20);
  startTimer(10);
}

void NGLScene::timerEvent(QTimerEvent *_event)
{
  //std::cout<<m_particleGenerator->get_particlePosition(2).m_y<<'\n';
  PBD(m_particleGenerator,0.99,0.05,10);
  //std::cout<<m_particleGenerator->get_particlePosition(19).m_y<<'\n';
  
  //m_particleGenerator->update();
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
  
  //draw particle
  ngl::ShaderLib::use(ParticleShader);
  ngl::Transformation tx;
  tx.setPosition(m_aimPos);
  tx.setScale(2.0f,2.0f,2.0f);
  ngl::ShaderLib::setUniform("MVP",m_project * m_view  * m_mouseGlobalTX *tx.getMatrix());
  //ngl::ShaderLib::setUniform("MVP", m_project * m_view * m_mouseGlobalTX);
  m_particleGenerator->render();

  //draw floor
  ngl::ShaderLib::use(ngl::nglColourShader);
  ngl::ShaderLib::setUniform("MVP",m_project * m_view * m_mouseGlobalTX);
  ngl::ShaderLib::setUniform("Colour",0.6f, 0.6f, 0.6f, 1.0f);
  ngl::VAOPrimitives::draw("floor");
  
  //m_text->renderText(10,680,"My Text is Here");
}

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::keyPressEvent(QKeyEvent *_event)
{
    // this method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  static int maxActive=500;
  static float spread=1.5;
  switch (_event->key())
  {
  // escape key to quite
  case Qt::Key_Escape:
    QGuiApplication::exit(EXIT_SUCCESS);
    break;
  case Qt::Key_Space:
    m_win.spinXFace = 0;
    m_win.spinYFace = 0;
    m_modelPos.set(ngl::Vec3::zero());
    break;
  case Qt::Key_1 : 
    //std::cout<<"1111"<<'\n';
    m_particleGenerator->set_particleExtForce(40,0.0f,-700.0f,500.0f);
    break;

  default : break;
  }
  // finally update the GLWindow and re-draw

    update();
}

void NGLScene::keyReleaseEvent(QKeyEvent *_event)
{
  if (_event->key() == Qt::Key_1)
  {
    //std::cout<<"1111"<<'\n';
    m_particleGenerator->set_particleExtForce(40,0.0f,700.0f,-500.0f);
  }
}

