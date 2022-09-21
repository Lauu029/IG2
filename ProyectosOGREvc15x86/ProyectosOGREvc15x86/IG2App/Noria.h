#pragma once
#include "AspaNoria.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
class Noria
{
public:
	Noria(Ogre::SceneManager* mSM);
	~Noria() {};
protected:
	Ogre::SceneNode* feria = nullptr;
	Ogre::SceneNode* aspa = nullptr;
};

