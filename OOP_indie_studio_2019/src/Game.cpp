/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Game
*/

#include "Game.hpp"

Game::Game(irr::IrrlichtDevice *win)
{
    this->_window = win;

    _sceneMngr = _window->getSceneManager()->createNewSceneManager(false);
    _camera = _sceneMngr->addCameraSceneNodeFPS(0, 100.0f, 0.5f);
    _driver = _window->getVideoDriver();

    _camera->setInputReceiverEnabled(false);
    _camera->setFarValue(5000000.0f);

    rotation = 4.712;
    
    _floor = _sceneMngr->addTerrainSceneNode(
        "./Assets/Texture/floor.bmp",
        0,
        1,
        irr::core::vector3df(-2000.f, -4.f, -500.f),     // position
        irr::core::vector3df(0.f, 0.f, 0.f),     // rotation
        irr::core::vector3df(4.f, 4.4f, 2.f),  // scale
        irr::video::SColor (255, 255, 255, 255),
        5,
        irr::scene::ETPS_17,
        4);
    _floor->setMaterialTexture(0, _driver->getTexture("./Assets/Texture/planch.jpg"));
    _floor->scaleTexture(1.0f, 0.5f);
    _floor->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);
  
    _sceneMngr->setShadowColor(irr::video::SColor(255,0,0,0));
    _skydome = _sceneMngr->addSkyDomeSceneNode(_driver->getTexture("./Assets/Texture/hdri.png"),16,8,1.0f,2.0f);
    _driver->setTextureCreationFlag(irr::video::ETCF_ALWAYS_32_BIT, true);
}

Game::~Game()
{

}

irr::scene::ISceneManager *Game::getSceneManager() const 
{
    return this->_sceneMngr;
}

irr::video::IVideoDriver *Game::getVideoDriver() const
{
    return this->_driver;
}

void Game::rotateCamera(float rot)
{
    this->rotation += rot;
    this->rotation = (this->rotation < 0) ? 6.25 : this->rotation;
    this->rotation = (this->rotation > 6.25) ? 0 : this->rotation;
}

void Game::fixCamera(int x_start, int y_start, int x, int y)
{
    int max = (x > y) ? x : y;

    this->high = 1500 + (max * 50);
    _camera->setPosition(irr::core::vector3df(x_start - 50 + ((x) * 100) / 2, this->high ,y_start));
    _camera->setTarget(irr::core::vector3df(x_start - 50 + ((x) * 100) / 2, 1000 ,y_start - 50 + (y * 100) / 2));
    this->_centerCamera = irr::core::vector3df(x_start - 50 + ((x) * 100) / 2, 1000 ,y_start - 50 + (y * 100) / 2);
    this->size = (y * 100) / 2 - 50;
    this->rotation = 4.712;
}

void Game::explosionParticle(float x, float y, float z)
{
    this->_particles.push_back(std::tuple<irr::scene::IParticleSystemSceneNode *,
    irr::scene::IParticleEmitter *, std::chrono::system_clock::time_point>
    (0, 0, std::chrono::system_clock::now()));

    std::get<irr::scene::IParticleSystemSceneNode *>(this->_particles.back()) =
    _sceneMngr->addParticleSystemSceneNode(false, 0, -1, irr::core::vector3df{x, y, z},
    irr::core::vector3df{0, 0, 0}, irr::core::vector3df{3,3,3});

    std::get<irr::scene::IParticleEmitter *>(this->_particles.back()) = std::get<irr::scene::IParticleSystemSceneNode *>(this->_particles.back())->createBoxEmitter(
    irr::core::aabbox3d<irr::f32>(-7,0,-7,7,1,7),
    irr::core::vector3df(0.0f,0.06f,0.0f),80,100,
    irr::video::SColor(0,255,25,13),
    irr::video::SColor(0,255,255,255),800,2000,0,
    irr::core::dimension2df(15.f,15.f),
    irr::core::dimension2df(25.f,25.f));

    std::get<irr::scene::IParticleSystemSceneNode *>(this->_particles.back())->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    std::get<irr::scene::IParticleSystemSceneNode *>(this->_particles.back())->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
    std::get<irr::scene::IParticleSystemSceneNode *>(this->_particles.back())->setMaterialTexture(0, _driver->getTexture("./Assets/Texture/fireball.bmp"));
    std::get<irr::scene::IParticleSystemSceneNode *>(this->_particles.back())->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);

    std::get<irr::scene::IParticleSystemSceneNode *>(this->_particles.back())->setEmitter(std::get<irr::scene::IParticleEmitter *>(this->_particles.back()));
}

void Game::displayGame(int state)
{
    _driver->beginScene(true, true, 0);
    auto end = std::chrono::system_clock::now();
    for (size_t i = 0; i < this->_particles.size(); i += 1) {
        if (double(std::chrono::duration_cast<std::chrono::seconds>(end - std::get<std::chrono::system_clock::time_point>(this->_particles[i])).count()) >= 1) {
            std::get<irr::scene::IParticleSystemSceneNode *>(this->_particles[i])->setEmitter(0);
            _sceneMngr->addToDeletionQueue(std::get<irr::scene::IParticleSystemSceneNode *>(this->_particles[i]));
            delete std::get<irr::scene::IParticleEmitter *>(this->_particles[i]);
            this->_particles.erase(this->_particles.begin() + i);
            i--;
        }
    }
    // std::cout << "-------------------------------------------" << std::endl; 
    // std::cout << "POS X => " <<  _camera->getPosition().X << std::endl;
    // std::cout << "POS Y => " << _camera->getPosition().Y << std::endl;
    // std::cout << "POS Z => " << _camera->getPosition().Z << std::endl;
    // std::cout << "-------------------------------------------" << std::endl; 
    // std::cout << "TAR X => " << _camera->getTarget().X << std::endl;
    // std::cout << "TAR Y => " << _camera->getTarget().Y << std::endl;
    // std::cout << "TAR Z => " << _camera->getTarget().Z << std::endl;

    _sceneMngr->drawAll();
    if (state == 1) {
        this->rotation = 4.712;
    }
    if (state != 1) {
        this->rotation = (this->rotation > 6.25) ? 0 : this->rotation + 0.005;
        _camera->setPosition(irr::core::vector3df(this->_centerCamera.X + (this->size * cos(this->rotation)), this->high, this->_centerCamera.Z + (this->size * sin(this->rotation))));
        this->_window->getGUIEnvironment()->drawAll();
    } else {
        _camera->setPosition(irr::core::vector3df(this->_centerCamera.X + (this->size * cos(this->rotation)), this->high, this->_centerCamera.Z + (this->size * sin(this->rotation))));
    }
    _driver->endScene();
}
