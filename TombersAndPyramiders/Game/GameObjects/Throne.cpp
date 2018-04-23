#include "Throne.h"
#include "GameManager.h"
#include "SpawnManager.h"
#include "Light.h"
#include "PositionBasedPopup.h"
#include "InputManager.h"
#include "SpinningEffect.h"
#include "PhysicsManager.h"
#include "NetworkingManager.h"
#include "Camera.h"
#include "SceneManager.h"
#include "MainMenuScene.h"
#include "MessageManager.h"
#include "CharacterController.h"
#include "Sender.h"

Throne::Throne() : ComplexSprite(createSpriteInfo(), 0, 0)
{
    m_activated = false;
    m_counter = 0;
    m_brightness = 10.0f;
    auto light = addComponent<Light>(this);
    getTransform()->setScale(5.0f);
    light->setSize(m_brightness);
    light->setColor(150, 100, 100);
    
}

std::shared_ptr<ComplexSpriteInfo> Throne::createSpriteInfo()
{
    auto spriteInfo = std::make_shared<ComplexSpriteInfo>();
	spriteInfo->addSprite("throneIdle.png", "Idle", 1, 1);
    spriteInfo->addAnimation("Idle", "idle", 0, 0);
    spriteInfo->addSprite("throneActive.png", "Active", 6, 1);
    spriteInfo->addAnimation("Active", "active", 0, 0);
    return spriteInfo;
}

Throne::~Throne()
{
    
}

void Throne::trigger()
{
    changeSpriteSheet("Active");
    m_activated = true;
    m_popupActive = false;
    auto character = SpawnManager::getInstance()->getActivePlayer();
    character->getComponent<Light>()->setSize(8.0f)->setColor(255, 0, 0);
    GameManager::getInstance()->createGameObject<SpinningEffect>(false)->getTransform()->setPosition(getTransform()->getX(), getTransform()->getY());
    getTransform()->setZ(1000);
    character->getTransform()->setZ(1001);
    character->getComponent<CharacterController>()->m_audioSource->playSFX(SFX_THRONE);
	character->getComponent<Sender>()->sendEndGame();
}

void Throne::onStart() 
{
    changeSpriteSheet("Idle");
}

void Throne::onUpdate(int ticks)
{
    updateFrames(ticks);
    auto character = SpawnManager::getInstance()->getActivePlayer();
	if (character != nullptr) 
	{
		auto distance = getTransform()->getDistance(character->getTransform());
        if (!m_activated) 
        {
            if (distance < 4.0f && !m_popupActive)
            {
                m_popupActive = true;
                GameManager::getInstance()->createGameObject<PositionBasedPopup>(false, getTransform()->getX(), getTransform()->getY(), 4.0f, character, "popupPickup.png");
                //Create Popup to destroy when this & player are 4> distance apart
                
            }
            if (distance < 5.5f) {
                if (InputManager::getInstance()->onKeyPressed(SDLK_z))
                {
                    trigger();
                }
            }
        }

        if (distance > 4.0f) {
            m_popupActive = false;
        }
		
    }
    if (m_activated) {
        m_counter += (float)ticks / 100.0f;
        if (m_counter <= 16.0f / 100.0f * 150)
        {
            m_brightness += sin(m_counter);
            if (m_brightness < 16) {
                m_brightness += 0.05f;
            }
        } else {
            if (m_brightness > 0) {
                m_brightness -= 0.1f;
                if (m_brightness <= 3) {
                    character->getComponent<Light>()->setSize(m_brightness);
                }
                if (m_brightness <= 0) {
                    PhysicsManager::getInstance()->purge();
                    SpriteRendererManager::getInstance()->purge();
                    NetworkingManager::getInstance()->hardReset();
                    Camera::getActiveCamera()->setActiveCamera(GameManager::getInstance()->createGameObject<Camera>(true));
                    SceneManager::getInstance()->pushScene(new MainMenuScene());
                }
            }
        }
        
        getComponent<Light>()->setSize(m_brightness);
        std::cout << m_brightness << std::endl;
        character->getTransform()->setPosition(getTransform()->getX(), getTransform()->getY());
        character->changeAnimation("IdleDown");
        character->getTransform()->setRotation(90.0f);
    }
}