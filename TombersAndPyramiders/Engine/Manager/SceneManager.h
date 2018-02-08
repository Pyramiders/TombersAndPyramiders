#include <stack>
#include "Scene.h"

class SceneManager {
private:
    std::stack<Scene*> m_scenes;
    void initializeScene();
    static SceneManager* s_instance;
    SceneManager();

public:
    static SceneManager* getInstance();

    //Pushing a scene pause the top of the stack, call OnStart on the parameterized scene, and push it to the stack.
    void pushScene(Scene *scene);

    //Calling this will call OnEnd on top scene, remove it, and call OnResume for the scene underneath.
    bool popScene();

    //Update the current scene on the stack.
    bool updateScene(int ticks);
    
    //Gets reference to current scene.
    Scene* getCurrentScene();
    
    //Has at least one scene.
    bool hasScene();

};