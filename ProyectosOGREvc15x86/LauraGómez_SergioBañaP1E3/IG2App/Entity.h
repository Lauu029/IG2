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
#include <OgreTimer.h>

#include "checkML.h"

using namespace Ogre;
using namespace std;

class EntityIG : public OgreBites::InputListener {
public:
	enum MessageKind { NoriaScene, BombScene,avionDied, SimBadDied };
	//Constructora y destructora
	EntityIG(Ogre::SceneNode* node);
	~EntityIG() {}
	//Vector est?tico de listeners
	static std::vector<EntityIG*> appListeners;
	//A?adir entidad como listener al vector con push_back()
	static void addListener(EntityIG* entidad) {
		appListeners.push_back(entidad);
	};

	void sendEvent(EntityIG* entidad, MessageKind k);
	virtual void receiveEvent(EntityIG* entidad, MessageKind k) {};

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
};

class Noria : public EntityIG {

public:
	Noria(Ogre::SceneNode* noria, int numAspas);
	~Noria() {};

protected:
	virtual void receiveEvent(EntityIG* entidad, MessageKind k) override;
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

	virtual void receiveEvent(EntityIG* entidad, MessageKind k) override;
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
	virtual void frameRendered(const Ogre::FrameEvent& evt) override;

	Ogre::Entity* mBody = nullptr;
	Ogre::Entity* mHead = nullptr;

	bool mMoving = false;
	bool mRojo = false;

	AnimationState* animationState = nullptr;
};
//---------------------------------------------------------------
class Plano : public EntityIG {
public:
	Plano(Ogre::SceneNode* plan, string name);
	~Plano() {};
protected:
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
	virtual void receiveEvent(EntityIG* entidad, MessageKind k) override;

	void changeMovingWater();

	Ogre::Entity* mPlane = nullptr;

	bool mMoveWater = true;

};
//------------------------------------------------------------------
class Aspa : public EntityIG {
public:
	Aspa(Ogre::SceneNode* aspa);
	~Aspa() {};
	Ogre::SceneNode* getCilinder() { return mCilinder; };

protected:
	Ogre::SceneNode* mCilinder = nullptr;
};

class AspasNave : public EntityIG {
public:
	AspasNave(Ogre::SceneNode* aspasNave, int num_aspas);
	~AspasNave() {};
	std::vector<Aspa*> mAspas;
};

class Avion : public EntityIG {
public:
	Avion(Ogre::SceneNode* avion);
	~Avion() {};
protected:
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
	virtual void frameRendered(const Ogre::FrameEvent& evt) override;

	AspasNave* mHelice1 = nullptr;
	AspasNave* mHelice2 = nullptr;

	ParticleSystem* pSys = nullptr;
	Ogre::SceneNode* nAvion = nullptr;

	int timeExplosion = -1;
	bool death = false;

};
//----------------------------------------------------------------------------
class BrazoDron : public EntityIG {
public:
	BrazoDron(Ogre::SceneNode* brazo);
	~BrazoDron() {};

	AspasNave* getHelice() { return mHelice; }
protected:
	AspasNave* mHelice = nullptr;
};

class Dron : public EntityIG {
public:
	Dron(Ogre::SceneNode* dron, int numBrazos, bool avispa);
	~Dron() {};
	void changeBodyColor();
protected:
	virtual void frameRendered(const Ogre::FrameEvent& evt) override;

	Ogre::Entity* mCenter = nullptr;
	std::vector<BrazoDron*>mBrazos;
	Ogre::Timer* myTimer = nullptr;
	double rot;
};
class Sinbad : public EntityIG {
public:
	Sinbad(Ogre::SceneNode* _sinbad, bool dP);
	~Sinbad() {};

	void arma();
protected:
	virtual void frameRendered(const Ogre::FrameEvent& evt) override;
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
	virtual void receiveEvent(EntityIG* entidad, MessageKind k)override;


	void arma(bool setDerecha);
	void cambiaEspada();
	void dance();

	Ogre::Entity* _Sinbad = nullptr;

	AnimationState* animation_piernas = nullptr;
	AnimationState* animation_brazos = nullptr;
	AnimationState* animation_dance = nullptr;
	AnimationState* animationState = nullptr;

	Ogre::Entity* sword_left = nullptr;
	Ogre::Entity* sword_right = nullptr;
	bool swordRight = false;
	bool swordLeft = false;

	bool desplazaPlano = true;
	int sendDiedEvent;
	bool death = false;

	Ogre::Timer* t = nullptr;
};
class Bomba : public EntityIG {
public:
	Bomba(Ogre::SceneNode* _bomba);
	virtual ~Bomba() {};
private:
	AnimationState* animationState = nullptr;
	Ogre::SceneNode* bombaNode = nullptr;
	virtual void frameRendered(const Ogre::FrameEvent& evt) override;
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
	virtual void receiveEvent(EntityIG* entidad, MessageKind k)override;

	Ogre::Timer* timeBomb = nullptr;
};