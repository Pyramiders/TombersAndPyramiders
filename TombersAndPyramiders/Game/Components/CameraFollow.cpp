#include "CameraFollow.h"
#include "Transform.h"
#include "GameObject.h"

//The constructor that passes GameObject into the parent/Component classes constructor
CameraFollow::CameraFollow(GameObject* gameObject) : Component(gameObject)
{
	std::cout << "CompontentTemplate Constructor Invoked" << std::endl;
}

//The destructor called when this component is deleted. Do any cleanup here
CameraFollow::~CameraFollow()
{
	std::cout << "ComponentTempalte Destructor Invoked. Time To Cleanup" << std::endl;
}

void CameraFollow::onUpdate(int ticks)
{
	if (m_toFollow)
	{
		Transform toGoTransform = *(*m_toFollow).getTransform();
		Transform* ourTransform = this->getGameObject()->getTransform();
		float newX = lerp(0.15f, ourTransform->getX(), toGoTransform.getX());
		if (fabs(newX - ourTransform->getX()) < 0.005f)
		{
			newX = toGoTransform.getX();
		}
		ourTransform->setX(newX);

		float newY = lerp(0.15f, ourTransform->getY(), toGoTransform.getY());
		if (fabs(newY - ourTransform->getY()) < 0.005f)
		{
			newY = toGoTransform.getY();
		}
		ourTransform->setY(newY);
	}
}


void CameraFollow::setToFollow(std::shared_ptr<GameObject> toFollow)
{
	m_toFollow = toFollow;
}

//TODO: Extract this out into the vector class. Really, lerping is a vector thing but transform doesent use vector and I'm using transforms.
//Maybe Vector should have an instance method to lerp itself, then a static method to lerp x/y points, and we would use hte static method here.
//(The instance method would just call the static one)
float CameraFollow::lerp(float t, float a, float b)
{
	return (1 - t)*a + t*b;
}