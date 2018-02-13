#include "ComponentTemplate.h"

//The constructor that passes GameObject into the parent/Component classes constructor
ComponentTemplate::ComponentTemplate(GameObject* gameObject) : Component(gameObject)
{
	std::cout << "CompontentTemplate Constructor Invoked" << std::endl;
}

//The destructor called when this component is deleted. Do any cleanup here
ComponentTemplate::~ComponentTemplate()
{
	std::cout << "ComponentTemplate Destructor Invoked. Time To Clean Up" << std::endl;
}

void ComponentTemplate::exampleMethod()
{
	std::cout << "Example Method Invoked On ComponentTemplate Class" << std::endl;
}