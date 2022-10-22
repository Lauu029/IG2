#pragma once

#include "IG2ApplicationContext.h"
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreMeshManager.h>
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>
#include <OgreBillboardSet.h>
#include <OgreParticleSystem.h>
#include <OgreMovablePlane.h>
#include <OgreTextureManager.h>
#include <OgreHardwarePixelBuffer.h>
#include <OgreRenderTexture.h>
#include <OgreSubEntity.h>
#include <OgreTechnique.h>

using namespace Ogre;
using namespace std;

class EntityIG : public OgreBites::InputListener {
public:
	//Constructora y destructora
	EntityIG(Ogre::SceneNode* node);
	~EntityIG() {}
	//Vector estático de listeners
	static std::vector<EntityIG*> appListeners;
	//Añadir entidad como listener al vector con push_back()
	static void addListener(EntityIG* entidad) {
		appListeners.push_back(entidad);
	};

	void sendEvent(EntityIG* entidad);
	virtual void receiveEvent(EntityIG* entidad) {};

	;
	SceneNode* getSceneNode() { return mNode; }

protected:
	Ogre::SceneNode* mNode = nullptr;
	Ogre::SceneManager* mSM = nullptr;

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) { return false; };
	virtual void frameRendered(const Ogre::FrameEvent& evt) {};
};
//--------------------------------------------------------------
class AspaNoria : public EntityIG {
public:
	AspaNoria(Ogre::SceneNode* aspaNoria);
	~AspaNoria() {};

	SceneNode* getBase() { return Base; }
protected:
	Ogre::SceneNode* Base = nullptr;
	Ogre::SceneNode* Lateral1 = nullptr;
	Ogre::SceneNode* Lateral2 = nullptr;
};

class Noria : public EntityIG {

public:
	Noria(Ogre::SceneNode* noria, int numAspas);
	~Noria() {};


protected:
	virtual void receiveEvent(EntityIG* entidad) override;
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
	virtual void frameRendered(const Ogre::FrameEvent& evt) override;

	int numAspas;
	std::vector<AspaNoria*> aspasNoria;

	bool moving = true;
};

//---------------------------------------------------------------
class Munieco : public EntityIG {
public:
	Munieco(Ogre::SceneNode* mun);
	~Munieco() {};

protected:

	virtual void receiveEvent(EntityIG* entidad) override;
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
	virtual void frameRendered(const Ogre::FrameEvent& evt) override;

	Ogre::SceneNode* head = nullptr;
	Ogre::SceneNode* body = nullptr;
	Ogre::SceneNode* nose = nullptr;
	Ogre::SceneNode* bellyButton = nullptr;

	bool moving = false;
	bool rojo = false;
};
//---------------------------------------------------------------
class Plano : public EntityIG {
public:
	Plano(Ogre::SceneNode* plan);
	~Plano() {};
protected:
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
	void changeMovingWater();
	bool moveWater = true;

};
//------------------------------------------------------------------
class Aspa : public EntityIG {
public:
	Aspa(Ogre::SceneNode* aspa);
	~Aspa() {};
	Ogre::SceneNode* getCilindro() { return cilindro; };

protected:
	Ogre::SceneNode* tablero = nullptr;
	Ogre::SceneNode* cilindro = nullptr;

};

class AspasNave : public EntityIG {
public:
	AspasNave(Ogre::SceneNode* aspasNave, int num_aspas);
	~AspasNave() {};
	std::vector<Aspa*> aspas;
protected:
	Ogre::SceneNode* centro = nullptr;
};

class Avion : public EntityIG {
public:
	Avion(Ogre::SceneNode* avion);
	~Avion() {};
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
protected:
	Ogre::SceneNode* ala1 = nullptr;
	Ogre::SceneNode* ala2 = nullptr;
	Ogre::SceneNode* helice1 = nullptr;
	Ogre::SceneNode* helice2 = nullptr;
	Ogre::SceneNode* morro = nullptr;
	Ogre::SceneNode* piloto = nullptr;
};

class BrazoDron : public EntityIG {
public:
	BrazoDron(Ogre::SceneNode* brazo);
	~BrazoDron() {};
protected:
	Ogre::SceneNode* esfera = nullptr;
	Ogre::SceneNode* cilindro = nullptr;
	Ogre::SceneNode* aspaDron = nullptr;
};
class Dron : public EntityIG {
public:
	Dron(Ogre::SceneNode* dron, int numBrazos, bool avispa);
	~Dron() {};
protected:
	Ogre::SceneNode* centro = nullptr;
	Ogre::SceneNode* aspaPrincipal = nullptr;
	std::vector<BrazoDron*>brazos;
};

