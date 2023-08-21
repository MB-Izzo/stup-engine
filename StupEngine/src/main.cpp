#include "Application.h"
#include "Engine/Core/Input.h"
#include "Engine/Core/KeyCodes.h"
#include "Engine/Core/Layer.h"
#include "Engine/GameObjects/Components/Component.h"
#include "Engine/GameObjects/Components/Rigidbody.h"
#include "Engine/GameObjects/Components/Sprite.h"
#include "Engine/GameObjects/GameObject.h"
#include "Engine/GameObjects/Scene.h"
#include "Engine/Renderer/Framebuffer.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Renderer/Shader.h"
#include "glad/glad.h"
#include "stuppch.h"
#include <GLFW/glfw3.h>
#include <memory>

// #include "Renderer/VertexBuffer.h"
// void framebuffer_size_callback(GLFWwindow *window, int width, int height);
// void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 640;
const unsigned int SCR_HEIGHT = 640;

// Camera camera(glm::vec3(1.0f, 0.0f, 0.0f));
bool firstMouse = true;
float lastX = 400.0f, lastY = 300.0f;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

class Player : public Stup::GameObject {
  public:
    Player() : GameObject()
    {
        m_cSprite = std::make_unique<Stup::Sprite>(
            "/home/mathieu/personal/opengl/stup_engine/StupEngine/assets/"
            "nooon.png",
            32, 32, GetTransform());
        m_cRigidbody = std::make_unique<Stup::Rigidbody>(GetTransform());
        m_cRigidbody->SetVelocity(glm::vec2(0, 0));
        GetTransform().SetPosition(glm::vec2(32, 32));
    }

    ~Player() = default;

    void Update(float dt) override
    {
        if (Stup::Input::IsKeyPressed(Stup::Key::D)) {
            m_cRigidbody->SetVelocity(4, m_cRigidbody->GetVelocity().y);
        }
        else if (Stup::Input::IsKeyPressed(Stup::Key::A)) {
            m_cRigidbody->SetVelocity(-4, m_cRigidbody->GetVelocity().y);
        }
        else if (Stup::Input::IsKeyPressed(Stup::Key::W)) {
            m_cRigidbody->SetVelocity(m_cRigidbody->GetVelocity().x, 4);
        }
        else if (Stup::Input::IsKeyPressed(Stup::Key::S)) {
            m_cRigidbody->SetVelocity(m_cRigidbody->GetVelocity().x, -4);
        }
        else {
            m_cRigidbody->SetVelocity(glm::vec2(0, 0));
        }

        m_cSprite->Update(dt);
        m_cRigidbody->Update(dt);
    }

    Stup::Sprite &GetSpriteComponent() { return *m_cSprite; }
    Stup::Rigidbody &GetRigidbody() { return *m_cRigidbody; }

  private:
    std::unique_ptr<Stup::Sprite> m_cSprite;
    std::unique_ptr<Stup::Rigidbody> m_cRigidbody;
};

class TestLayer : public Stup::Layer {
  public:
    void OnAttach() override
    {
        std::cout << "Test Layer Attached" << std::endl;
        Stup::Renderer::shared_instance().SetViewport(0, 0, 640, 640);
        Stup::Renderer::shared_instance().Init();

        scene.AddGameObject(player);
        scene.AddGameObject(enemy);
        enemy->GetTransform().SetPosition(glm::vec2(0, 0));
    }

    void OnDetach() override {}

    void OnUpdate(float dt) override
    {
        Stup::Renderer &renderer = Stup::Renderer::shared_instance();

        renderer.SetViewport(0, 0, 64, 64);
        fb.Bind();

        renderer.SetClearColor(glm::vec4(0, 1, 0, 1));
        renderer.Clear();

        scene.Update(dt);

        fb.Blit();
        // render scene here bro
    }

    void OnEvent(Stup::Event &e) override
    {
        //        std::cout << "received event" << std::endl;
    }

  private:
    std::shared_ptr<Player> player = std::make_shared<Player>();
    std::shared_ptr<Player> enemy = std::make_shared<Player>();
    //    std::shared_ptr<Stup::Shader> shader =
    //    std::make_shared<Stup::Shader>("/home/mathieu/personal/opengl/stup_engine/StupEngine/assets/basicShader.vs",
    //    "/home/mathieu/personal/opengl/stup_engine/StupEngine/assets/basicShader.fs");
    //    Stup::Sprite sprite =
    //    Stup::Sprite("/home/mathieu/personal/opengl/stup_engine/StupEngine/assets/nooon.png",
    //    shader, 32, 32);
    Stup::Framebuffer fb;

    Stup::Scene scene;
    //   std::shared_ptr<Stup::GameObject> go =
    //   std::make_shared<Stup::GameObject>();
    //  std::shared_ptr<Stup::Sprite> sprite =
    //  std::make_shared<Stup::Sprite>(Stup::Sprite("/home/mathieu/personal/opengl/stup_engine/StupEngine/assets/nooon.png",
    //  shader, 32, 32));
};

int main()
{
    Stup::Application app;
    app.PushLayer(new TestLayer());

    // app = Stup::Application();
    app.Run();
    return 1;
    // glfw: initialize and configure
    // ------------------------------
    /*
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(640, 640, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 640, 640);

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);

        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
    */
}

// process all input: query GLFW whether relevant keys are pressed/released this
// frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
/*void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = static_cast<float>(52.5f * deltaTime);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
//        camera.ProcessKeyboard(FORWARD, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
//        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
//        camera.ProcessKeyboard(LEFT, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
//        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
//
---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width
    // and height will be significantly larger than specified on retina
    // displays.
    glViewport(0, 0, width, height);
}
*/
