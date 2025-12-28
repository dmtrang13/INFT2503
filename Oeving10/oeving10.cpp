#include "imgui-SFML.h"
#include "imgui.h"

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>

#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

#include <glm/glm.hpp>

#include <bullet/btBulletDynamicsCommon.h>

#include <chrono>

#include <iostream>

using namespace std;

constexpr float RAD2DEG = 57.29577951308232f;
static void drawSolidCube(float size) {
  const float s = size * 0.5f;
  glBegin(GL_QUADS);
  // +X
  glNormal3f(1,0,0);  glVertex3f(+s,-s,-s); glVertex3f(+s,-s,+s); glVertex3f(+s,+s,+s); glVertex3f(+s,+s,-s);
  // -X
  glNormal3f(-1,0,0); glVertex3f(-s,-s,+s); glVertex3f(-s,-s,-s); glVertex3f(-s,+s,-s); glVertex3f(-s,+s,+s);
  // +Y
  glNormal3f(0,1,0);  glVertex3f(-s,+s,-s); glVertex3f(+s,+s,-s); glVertex3f(+s,+s,+s); glVertex3f(-s,+s,+s);
  // -Y
  glNormal3f(0,-1,0); glVertex3f(-s,-s,+s); glVertex3f(+s,-s,+s); glVertex3f(+s,-s,-s); glVertex3f(-s,-s,-s);
  // +Z
  glNormal3f(0,0,1);  glVertex3f(+s,-s,+s); glVertex3f(-s,-s,+s); glVertex3f(-s,+s,+s); glVertex3f(+s,+s,+s);
  // -Z
  glNormal3f(0,0,-1); glVertex3f(-s,-s,-s); glVertex3f(+s,-s,-s); glVertex3f(+s,+s,-s); glVertex3f(-s,+s,-s);
  glEnd();
}

static void wake(btRigidBody& b) {
  b.activate(true);
  b.forceActivationState(ACTIVE_TAG);
}


class Ground {
  btStaticPlaneShape shape;
  btDefaultMotionState motion_state;

public:
  btRigidBody body;

  Ground() : shape(btVector3(0.0, 1.0, 0.0), 0.0), body(0.0, &motion_state, &shape) {
    body.setRollingFriction(0.1);
    body.setRestitution(0.8);
  }

  void draw() {
    auto position = body.getCenterOfMassPosition();

    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(0.0, 1.0, 0.0);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(position.x() - 5.0, position.y(), position.z() + 5.0);
    glVertex3f(position.x() - 5.0, position.y(), position.z() - 5.0);
    glVertex3f(position.x() + 5.0, position.y(), position.z() + 5.0);
    glVertex3f(position.x() + 5.0, position.y(), position.z() - 5.0);
    glEnd();
  }
};

class Sphere {
  btSphereShape shape;
  btDefaultMotionState motion_state;

public:
  btRigidBody body;

  Sphere() : shape(btScalar(0.1)), body(1.0, &motion_state, &shape) {
    auto mass = 1.0 / body.getInvMass();

    btVector3 inertia;
    shape.calculateLocalInertia(mass, inertia);

    body.setMassProps(mass, inertia);
    body.setRollingFriction(0.2);
    body.setRestitution(0.8);
  }

  void draw() {
    glPushMatrix();
    auto position = body.getCenterOfMassPosition();
    glTranslatef(position.x(), position.y(), position.z());
    glColor3f(0.0, 0.0, 1.0);
    auto quadric = gluNewQuadric();
    gluSphere(quadric, shape.getRadius(), 32, 32);
    gluDeleteQuadric(quadric);
    glPopMatrix();
  }
};

class Cube {
  btBoxShape shape;
  btDefaultMotionState motion_state;

public:
  btRigidBody body;

  Cube() : shape({0.1, 0.1, 0.1}), body(1.0, &motion_state, &shape) {
    auto mass = 1.0 / body.getInvMass();

    btVector3 inertia;
    shape.calculateLocalInertia(mass, inertia);

    body.setMassProps(mass, inertia);
    body.setFriction(0.5);
    body.setRollingFriction(0.1);
    body.setRestitution(0.2);
  }

  void draw() {
  glPushMatrix();
  auto position = body.getCenterOfMassPosition();
  glTranslatef(position.x(), position.y(), position.z());

  auto q = body.getOrientation();
  btVector3 axis = q.getAxis(); // already normalised
  glRotatef(q.getAngle() * RAD2DEG, axis.x(), axis.y(), axis.z());
  glColor3f(1.0, 0.0, 0.0);
  //glutSolidCube(0.2);
  drawSolidCube(0.2f);
  glPopMatrix();
  }
};

class World {
  btDefaultCollisionConfiguration collision_configuration;
  btCollisionDispatcher dispatcher;
  btDbvtBroadphase broadphase;
  btSequentialImpulseConstraintSolver solver;

public:
  btDiscreteDynamicsWorld dynamics;

  Ground ground;
  Sphere ground_sphere, falling_sphere;
  std::vector<Cube> cubes;
  
  btTransform ground_t0{};
  btTransform ground_sphere_t0{};
  btTransform falling_sphere_t0{};
  array<btTransform, 6> cubes_t0{};
  bool aiming = false;

  World() : dispatcher(&collision_configuration),
            dynamics(&dispatcher, &broadphase, &solver, &collision_configuration),
            cubes(6) {
    dynamics.setGravity(btVector3(0, -10.0, 0));

    // Add objects to the physics engine
    dynamics.addRigidBody(&ground.body);
    dynamics.addRigidBody(&ground_sphere.body);
    dynamics.addRigidBody(&falling_sphere.body);
    for (auto &cube : cubes)
      dynamics.addRigidBody(&cube.body);

    btTransform transform;

    // Position ground
    transform.setIdentity();
    transform.setOrigin(btVector3(0.0, 0.0, 0.0));
    ground.body.setCenterOfMassTransform(transform);
    ground_t0 = transform;

    // Position spheres
    transform.setOrigin(btVector3(1.0, 0.1, 0.0));
    ground_sphere.body.setCenterOfMassTransform(transform);
    ground_sphere_t0 = transform;

    transform.setOrigin(btVector3(0.9, 3.0, 0.0));
    falling_sphere.body.setCenterOfMassTransform(transform);
    falling_sphere_t0 = transform;

    // Position cubes
    transform.setOrigin(btVector3(-1.0, 0.1, -0.2));
    cubes[0].body.setCenterOfMassTransform(transform);
    cubes_t0[0] = transform;

    transform.setOrigin(btVector3(-1.0, 0.1, 0.0));
    cubes[1].body.setCenterOfMassTransform(transform);
    cubes_t0[1] = transform;

    transform.setOrigin(btVector3(-1.0, 0.1, 0.2));
    cubes[2].body.setCenterOfMassTransform(transform);
    cubes_t0[2] = transform;

    transform.setOrigin(btVector3(-1.0, 0.3, -0.1));
    cubes[3].body.setCenterOfMassTransform(transform);
    cubes_t0[3] = transform;

    transform.setOrigin(btVector3(-1.0, 0.3, 0.1));
    cubes[4].body.setCenterOfMassTransform(transform);
    cubes_t0[4] = transform;

    transform.setOrigin(btVector3(-1.0, 0.5, 0.0));
    cubes[5].body.setCenterOfMassTransform(transform);
    cubes_t0[5] = transform;
  }

  void draw() {
    ground.draw();
    ground_sphere.draw();
    falling_sphere.draw();
    for (auto &cube : cubes)
      cube.draw();
  }

  void beginAim() {
    if(!aiming) {
      dynamics.removeRigidBody(&falling_sphere.body);
      clearBodyVel(falling_sphere.body);
      aiming = true;
    }
  }

  void setAimPosition(float x, float y) {
    btTransform t; 
    t.setIdentity();
    t.setOrigin(btVector3(x, y, 0.0f)); 
    falling_sphere.body.setCenterOfMassTransform(t);
    clearBodyVel(falling_sphere.body);
    wake(falling_sphere.body);
  }

  void drop() {
    if(aiming) {
      clearBodyVel(falling_sphere.body);
      dynamics.addRigidBody(&falling_sphere.body);
      wake(falling_sphere.body);
      aiming = false;
    }
  }

  void reset() {
    dynamics.removeRigidBody(&falling_sphere.body);
    aiming = true;

    ground.body.setCenterOfMassTransform(ground_t0);
    ground_sphere.body.setCenterOfMassTransform(ground_sphere_t0);
    falling_sphere.body.setCenterOfMassTransform(falling_sphere_t0);
    for(int i = 0; i < (int)cubes.size(); i++) {
      cubes[i].body.setCenterOfMassTransform(cubes_t0[i]);
    }
    clearBodyVel(ground.body);
    clearBodyVel(ground_sphere.body);
    clearBodyVel(falling_sphere.body);
    for(auto &c : cubes) clearBodyVel(c.body);
    wake(falling_sphere.body);
  }

private:
  static void clearBodyVel(btRigidBody& b) {
    b.clearForces();
    b.setLinearVelocity(btVector3(0,0,0));
    b.setAngularVelocity(btVector3(0,0,0));
    b.activate(true);
  }
};

class Application {
  sf::RenderWindow window;

  World world;

public:
  Application() : window(sf::VideoMode({800, 600}), "SFML Example") {
    window.setFramerateLimit(144);
    window.setVerticalSyncEnabled(true);

    // Various settings
    glClearColor(0.5, 0.5, 0.5, 0.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light_position[] = {-3.0, 4.0, 0.0, 1.0};
    GLfloat spot_direction[] = {1.0, -1.0, -0.5};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.0);
    glEnable(GL_COLOR_MATERIAL);

    // Setup projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    gluPerspective(45.0, 4.0 / 3.0, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);

    // ImGui settings
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    if (!ImGui::SFML::Init(window))
      throw "Failed to initialize Imgui::SFML";
  }

  void start() {
    glm::vec3 camera(0.0, 1.0, 6.0);

    float horizontal_position = -1.0f;
    float vertical_position = 2.0f;

    world.beginAim();
    world.setAimPosition(horizontal_position, vertical_position);

    sf::Clock delta_clock;

    auto last_time = std::chrono::system_clock::now();
    bool running = true;
    while (running) {
      // Handle events
      while (auto event = window.pollEvent()) {
        ImGui::SFML::ProcessEvent(window, *event);
        if (auto keyPressed = event->getIf<sf::Event::KeyPressed>()) {
          if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
            window.close();
            running = false;
          }
        } else if (event->is<sf::Event::Closed>()) {
          window.close();
          running = false;
        }
      }

      ImGui::SFML::Update(window, delta_clock.restart());

      ImGui::Begin("ImGui");
      if (ImGui::Button("Restart game")) {
        world.reset();
        horizontal_position = -1.0f;
        vertical_position = 2.0f;
        world.setAimPosition(horizontal_position, vertical_position);
      }
      if (ImGui::Button("Drop ball")) {
        world.drop();
      }

      if (ImGui::SliderFloat("Horizontal ball position", &horizontal_position, -5.0, 5.0)) {
        if(world.aiming) world.setAimPosition(horizontal_position, vertical_position);
      }

      if (ImGui::VSliderFloat("Vertical ball position", {20, 100}, &vertical_position, 0, 5.0)) {
        if(world.aiming) world.setAimPosition(horizontal_position, vertical_position);
      }
      if(ImGui::Button("Hold ball again")) {
        world.beginAim();
        world.setAimPosition(horizontal_position, vertical_position);
      }

      ImGui::End();

      // Draw
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glLoadIdentity();

      gluLookAt(camera.x, camera.y, camera.z, // Camera position in World Space
                camera.x, camera.y, 0.0,      // Camera looks towards this position
                0.0, 1.0, 0.0);               // Up

      auto time = std::chrono::system_clock::now();
      if(!world.aiming) {
        world.dynamics.stepSimulation(std::chrono::duration<float>(time - last_time).count()); 
      }
      last_time = time;

      world.draw();
      
      window.resetGLStates();
      ImGui::SFML::Render(window);


      // Swap buffer (show result)
      window.display();
    }
    ImGui::SFML::Shutdown();
  }
};

int main() {
  Application application;
  application.start();
}
