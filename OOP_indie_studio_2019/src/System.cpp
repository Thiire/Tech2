/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** System
*/

#include "../include/System/System.hpp"

System::System()
{
    this->_stock.push_back(Storage(Cmp::Type::MESH));
    this->_stock.push_back(Storage(Cmp::Type::STAT));
    this->_stock.push_back(Storage(Cmp::Type::TIMER));
    this->_stock.push_back(Storage(Cmp::Type::CUBE));

    for (size_t idx = 0; idx < 4; idx++) {
        this->_direction.push_back({-1, -1, -1});
        this->_way.push_back({-1, -1, -1});
    }
    this->event = new Event();
    this->_newGame = true;
    this->createWindow();
    this->_window->getCursorControl()->setVisible(true);
    this->menu = new Menu(this->_window);
    this->game = new Game(this->_window);
    this->sound = new Sound();
    this->_state = 0;
    this->_idCounter = 0;
    if (this->_window == 0) {
        std::cerr << "Before" << std::endl;
        exit (84);
    }
    this->_death = false;
    this->_window->setWindowCaption((wchar_t *)"Bomberman");
}

System::~System()
{
    this->_entities.clear();
    this->_stock.clear();
    if (this->menu)
        delete (this->menu);
    if (this->game)
        delete (this->game);
    if (this->event)
        delete (this->event);
}

void System::start()
{
    this->sound->playMusic();
    this->createMap();
    while (this->_window->run()) {
        if (this->event->IsButtonDown(Evt::GUI_ID_QUIT_BUTTON) && this->_state == 0) {
            std::cout << "quit" << std::endl;
            break;
        } else if (this->event->IsKeyDown(irr::KEY_KEY_B)) {
            this->_death = !this->_death;
            std::cout << "{ Damage " << (this->_death ? "Activated }" : "Disabled }") << std::endl;
            this->event->releaseKey(irr::KEY_KEY_B);
        } else if (this->event->IsButtonDown(Evt::GUI_ID_LAUNCH_BUTTON) && this->_state == 4) {
            this->initBot(this->menu->getBot());
            this->_state = 1;
            this->_newGame = true;
            this->_window->getCursorControl()->setVisible(false);
        } else if (this->event->IsButtonDown(Evt::GUI_ID_PLAY_BUTTON) && this->_state == 0) {
            this->_state = 4;
        } else if (this->event->IsKeyDown(irr::KEY_ESCAPE) && this->_state == 1) {
            this->_state = 3;  this->_window->getCursorControl()->setVisible(true);
        } else if (this->event->IsButtonDown(Evt::GUI_ID_OPTION_BUTTON) && this->_state == 0) {
            this->_state = 2;
        } else if (this->event->IsButtonDown(Evt::GUI_ID_RESUME_BUTTON) && this->_state == 3) {
            this->_state = 1;
            this->_window->getCursorControl()->setVisible(false);
        } else if (this->event->IsButtonDown(Evt::GUI_ID_PAUSE_QUIT_BUTTON) && this->_state == 3) {
            this->_state = 0;
            this->_window->getCursorControl()->setVisible(true);
        } else if ((this->event->IsKeyDown(irr::KEY_ESCAPE) || this->event->IsButtonDown(Evt::GUI_ID_OPTION_QUIT_BUTTON)) && this->_state == 2) {
            this->_state = 0;
        } else if (this->event->IsButtonDown(Evt::GUI_ID_MAP_BUTTON)) {
            this->switchMap();
        }
        if (this->event->IsKeyDown(irr::KEY_SPACE)) {
            this->dropBomb(Ett::PLAYER);
            this->event->releaseKey(irr::KEY_SPACE);
        }
        if (this->event->IsButtonDown(Evt::GUI_ID_PLAYER1_BUTTON) && this->_state == 4) {
            this->menu->SwapBot(0);
        } else if (this->event->IsButtonDown(Evt::GUI_ID_PLAYER2_BUTTON) && this->_state == 4) {
            this->menu->SwapBot(1);
        } else if (this->event->IsButtonDown(Evt::GUI_ID_PLAYER3_BUTTON) && this->_state == 4) {
            this->menu->SwapBot(2);
        } else if (this->event->IsButtonDown(Evt::GUI_ID_PLAYER4_BUTTON) && this->_state == 4) {
            this->menu->SwapBot(3);
        }
        if (this->event->IsKeyDown(irr::KEY_RETURN)) {
            this->dropBomb(Ett::PLAYER2);
            this->event->releaseKey(irr::KEY_RETURN);
        }
        if (this->event->IsKeyDown(irr::KEY_KEY_A)) {
            this->game->rotateCamera(-0.01);
        } else if (this->event->IsKeyDown(irr::KEY_KEY_E)) {
            this->game->rotateCamera(0.01);
        } else if (this->event->IsButtonDown(Evt::GUI_ID_SAVE_BUTTON)) {
            this->saveMap();
        } else if (this->event->IsButtonDown(Evt::GUI_ID_LOAD_BUTTON)) {
            this->loadMap();
        }
        this->menu->SwitchMenu(this->_state);
        this->game->displayGame(this->_state);
        if (this->_state == 1) {
            explosionTimer();
            if (this->_newGame == true) {
                this->setCollisions();
            }
            this->playerMovements();
            this->launchIA();
            this->checkVictory();
        }
        detectPowerUp();
    }
    this->_window->drop();
}

void System::createWindow()
{
    irr::SIrrlichtCreationParameters params;
    params.DriverType = irr::video::E_DRIVER_TYPE::EDT_OPENGL;
    params.WindowSize = irr::core::dimension2d<irr::u32>(1920, 1080);
    params.EventReceiver = this->event;
    params.Vsync = true;
    params.Fullscreen = true;
    this->_window = irr::createDeviceEx(params);
    if (!this->_window)
        exit(84);
    this->_window->setWindowCaption(L"Bomberman");
}

void System::initBot(std::vector<bool> type)
{
    int number = 0;

    for (size_t idy = 0; idy < this->_entities.size(); idy++) {
        if (this->_entities[idy].getType() == Ett::Type::PLAYER || this->_entities[idy].getType() == Ett::Type::PLAYER2) {
            this->_entities[idy].setType(Ett::Type::BOT);
        }
    }
    for (size_t idx = 0; idx < type.size(); idx++) {
        if (type[idx]) {
            int size = 0;
            for (size_t idy = 0; idy < this->_entities.size(); idy++) {
                if (this->_entities[idy].getType() == Ett::Type::BOT) {
                    if (size == idx && number == 0) {
                        this->_entities[idy].setType(Ett::Type::PLAYER);
                        number++;
                        break;
                    } else if (size == idx) {
                        this->_entities[idy].setType(Ett::Type::PLAYER2);
                        number++;
                        break;
                    }
                    size++;
                } else if (this->_entities[idy].getType() == Ett::Type::PLAYER) {
                    size++;
                }
            }
        }
    }
}

void System::supComponent(size_t id)
{
    for (size_t idx = 0; idx < this->_stock.size(); idx++) {
        this->_stock[idx].supComponent(id);
    }
}

Component *System::getComponent(Cmp::Type type, size_t id)
{
    for (size_t idx = 0; idx < this->_stock.size(); idx++) {
        if (this->_stock[idx].getType() == type) {
            return (this->_stock[idx].getComponent(id));
        }
    }
}

template<typename T>
std::vector<T *> System::getComponents(Cmp::Type type, int size...)
{
    va_list args;
    Component * tmp;
    std::vector<T *> components;
    std::vector<Ett::Type> types;
    int index = 0;

    va_start(args, size);
    for (size_t idx = 0; idx < size; idx++) {
        types.push_back((Ett::Type)va_arg(args, int));
    }
    for (size_t idx = 0; idx < this->_stock.size(); idx++) {
        if (this->_stock[idx].getType() == type)
            index = idx;
    }
    for (size_t idx = 0; idx < this->_entities.size(); idx++) {
        if (std::find(types.begin(), types.end(), this->_entities[idx].getType()) != types.end()) {
            tmp = this->_stock[index].getComponent(this->_entities[idx].getID());
            if (tmp != NULL)
                components.push_back(dynamic_cast<T *>(tmp));
        }
    }
    va_end(args);
    return components;
}

bool System::hasComponent(Cmp::Type type, size_t id)
{
    for (size_t idx = 0; idx < this->_stock.size(); idx++) {
        if (this->_stock[idx].getType() == type) {
            return (this->_stock[idx].hasComponent(id));
        }
    }
    return false;
}

irr::EKEY_CODE System::keyPress()
{
    if (this->event->IsKeyDown(irr::KEY_KEY_A))
        return irr::KEY_KEY_A;
    if (this->event->IsKeyDown(irr::KEY_KEY_E))
        return irr::KEY_KEY_E;
    if (this->event->IsKeyDown(irr::KEY_ESCAPE))
        return irr::KEY_ESCAPE;
    if (this->event->IsKeyDown(irr::KEY_KEY_Z))
        return irr::KEY_KEY_Z;
    if (this->event->IsKeyDown(irr::KEY_KEY_Q))
        return irr::KEY_KEY_Q;
    if (this->event->IsKeyDown(irr::KEY_KEY_S))
        return irr::KEY_KEY_S;
    if (this->event->IsKeyDown(irr::KEY_KEY_D))
        return irr::KEY_KEY_D;
    if (this->event->IsKeyDown(irr::KEY_LEFT))
        return irr::KEY_LEFT;
    if (this->event->IsKeyDown(irr::KEY_RIGHT))
        return irr::KEY_RIGHT;
    if (this->event->IsKeyDown(irr::KEY_UP))
        return irr::KEY_UP;
    if (this->event->IsKeyDown(irr::KEY_DOWN))
        return irr::KEY_DOWN;
    if (this->event->IsKeyDown(irr::KEY_SPACE))
        return irr::KEY_SPACE;
    if (this->event->IsKeyDown(irr::KEY_RETURN))
        return irr::KEY_RETURN;
    return irr::KEY_KANJI;
}

template<typename ...Args>
size_t System::addPlayer(Args ...args)
{
    std::tuple<Args...> tmp(args...);

    this->_entities.push_back(Entity(this->_idCounter, Ett::PLAYER));
    for (size_t idx = 0; idx < this->_stock.size(); idx++)
        if (this->_stock[idx].getType() == Cmp::MESH)
            this->_stock[idx].addMesh(this->_idCounter, std::get<0>(tmp), std::get<1>(tmp), std::get<2>(tmp), std::get<3>(tmp), std::get<4>(tmp), irr::core::vector3df{50.0f, 50.0f, 50.0f});
    for (size_t idx = 0; idx < this->_stock.size(); idx++)
        if (this->_stock[idx].getType() == Cmp::STAT)
            this->_stock[idx].addStat(this->_idCounter, std::get<5>(tmp), std::get<6>(tmp));
    this->_idCounter++;
    return this->_idCounter;
}

template<typename ...Args>
size_t System::addPlayer2(Args ...args)
{
    std::tuple<Args...> tmp(args...);

    this->_entities.push_back(Entity(this->_idCounter, Ett::PLAYER2));
    for (size_t idx = 0; idx < this->_stock.size(); idx++)
        if (this->_stock[idx].getType() == Cmp::MESH)
            this->_stock[idx].addMesh(this->_idCounter, std::get<0>(tmp), std::get<1>(tmp), std::get<2>(tmp), std::get<3>(tmp), std::get<4>(tmp), irr::core::vector3df{50.0f, 50.0f, 50.0f});
    for (size_t idx = 0; idx < this->_stock.size(); idx++)
        if (this->_stock[idx].getType() == Cmp::STAT)
            this->_stock[idx].addStat(this->_idCounter, std::get<5>(tmp), std::get<6>(tmp));
    this->_idCounter++;
    return this->_idCounter;
}

template<typename ...Args>
size_t System::addBot(Args ...args)
{
    std::tuple<Args...> tmp(args...);

    this->_entities.push_back(Entity(this->_idCounter, Ett::BOT));
    for (size_t idx = 0; idx < this->_stock.size(); idx++)
        if (this->_stock[idx].getType() == Cmp::MESH)
            this->_stock[idx].addMesh(this->_idCounter, std::get<0>(tmp), std::get<1>(tmp), std::get<2>(tmp), std::get<3>(tmp), std::get<4>(tmp), irr::core::vector3df{50.0f, 50.0f, 50.0f}, std::get<5>(tmp), std::get<6>(tmp), std::get<7>(tmp), std::get<8>(tmp), std::get<9>(tmp));
    for (size_t idx = 0; idx < this->_stock.size(); idx++)
        if (this->_stock[idx].getType() == Cmp::STAT)
            this->_stock[idx].addStat(this->_idCounter, std::get<10>(tmp), std::get<11>(tmp));
    this->_idCounter++;
    return this->_idCounter;
}

template<typename ...Args>
size_t System::addBox(Args ...args)
{
    std::tuple<Args...> tmp(args...);

    this->_entities.push_back(Entity(this->_idCounter, Ett::BOX));
    for (size_t idx = 0; idx < this->_stock.size(); idx++)
        if (this->_stock[idx].getType() == Cmp::MESH)
            this->_stock[idx].addMesh(this->_idCounter, std::get<0>(tmp), std::get<1>(tmp), std::get<2>(tmp), std::get<3>(tmp), std::get<4>(tmp));
    this->_idCounter++;
    return this->_idCounter;
}

template<typename ...Args>
size_t System::addRamp(Args ...args)
{
    std::tuple<Args...> tmp(args...);

    this->_entities.push_back(Entity(this->_idCounter, Ett::RAMP));
    for (size_t idx = 0; idx < this->_stock.size(); idx++)
        if (this->_stock[idx].getType() == Cmp::MESH)
            this->_stock[idx].addMesh(this->_idCounter, std::get<0>(tmp), std::get<1>(tmp), std::get<2>(tmp), std::get<3>(tmp), std::get<4>(tmp), irr::core::vector3df{100.0f, 100.0f, 100.0f}, std::get<5>(tmp), std::get<6>(tmp), std::get<7>(tmp));
    this->_idCounter++;
    return this->_idCounter;
}

template<typename ...Args>
size_t System::addPowerUp(Args ...args)
{
    std::tuple<Args...> tmp(args...);
    int rand = std::rand() % 2;

    this->_entities.push_back(Entity(this->_idCounter, Ett::POWERUP));
    for (size_t idx = 0; idx < this->_stock.size(); idx++)
        if (this->_stock[idx].getType() == Cmp::MESH)
            this->_stock[idx].addMesh(this->_idCounter, std::get<0>(tmp), std::get<1>(tmp), std::get<2>(tmp), std::get<3>(tmp), std::get<4>(tmp), irr::core::vector3df{100.0f, 100.0f, 100.0f}, 0.0, 0.0, 0.0, true);
    for (size_t idx = 0; idx < this->_stock.size(); idx++)
        if (this->_stock[idx].getType() == Cmp::STAT) {
            if (rand == 1) {
                this->_stock[idx].addStat(this->_idCounter, 1, 0);
            } else {
                this->_stock[idx].addStat(this->_idCounter, 0, 0.25);
            }
        }
    this->_idCounter++;
    return this->_idCounter;
}

template<typename ...Args>
size_t System::addWall(Args ...args)
{
    std::tuple<Args...> tmp(args...);

    this->_entities.push_back(Entity(this->_idCounter, Ett::WALL));
    for (size_t idx = 0; idx < this->_stock.size(); idx++)
        if (this->_stock[idx].getType() == Cmp::MESH)
            this->_stock[idx].addMesh(this->_idCounter, std::get<0>(tmp), std::get<1>(tmp), std::get<2>(tmp), std::get<3>(tmp), std::get<4>(tmp));
    this->_idCounter++;
    return this->_idCounter;
}

template<typename ...Args>
size_t System::addPillar(Args ...args)
{
    std::tuple<Args...> tmp(args...);

    this->_entities.push_back(Entity(this->_idCounter, Ett::PILLAR));
    for (size_t idx = 0; idx < this->_stock.size(); idx++)
        if (this->_stock[idx].getType() == Cmp::MESH)
            this->_stock[idx].addMesh(this->_idCounter, std::get<0>(tmp), std::get<1>(tmp), std::get<2>(tmp), std::get<3>(tmp), std::get<4>(tmp));
    this->_idCounter++;
    return this->_idCounter;
}

template<typename ...Args>
size_t System::addGround(Args ...args)
{
    std::tuple<Args...> tmp(args...);

    this->_entities.push_back(Entity(this->_idCounter, Ett::GROUND));
    for (size_t idx = 0; idx < this->_stock.size(); idx++)
        if (this->_stock[idx].getType() == Cmp::CUBE)
            this->_stock[idx].addCube(this->_idCounter, std::get<0>(tmp), std::get<1>(tmp), std::get<2>(tmp), std::get<3>(tmp), std::get<4>(tmp));
    this->_idCounter++;
    return this->_idCounter;
}

template<typename ...Args>
size_t System::addBomb(Args ...args)
{
    std::tuple<Args...> tmp(args...);

    this->_entities.push_back(Entity(this->_idCounter, Ett::BOMB));
    for (size_t idx = 0; idx < this->_stock.size(); idx++)
        if (this->_stock[idx].getType() == Cmp::MESH)
            this->_stock[idx].addMesh(this->_idCounter, std::get<0>(tmp), std::get<1>(tmp), std::get<2>(tmp), std::get<3>(tmp), std::get<4>(tmp));
    for (size_t idx = 0; idx < this->_stock.size(); idx++)
        if (this->_stock[idx].getType() == Cmp::STAT)
            this->_stock[idx].addStat(this->_idCounter, std::get<5>(tmp), std::get<6>(tmp));
    for (size_t idx = 0; idx < this->_stock.size(); idx++)
        if (this->_stock[idx].getType() == Cmp::TIMER)
            this->_stock[idx].addTimer(this->_idCounter);
    this->_idCounter++;
    return this->_idCounter;
}

void System::setCollisions()
{
    std::vector<Mesh *> players = this->getComponents<Mesh>(Cmp::Type::MESH, 3, Ett::Type::PLAYER, Ett::Type::PLAYER2, Ett::Type::BOT);
    std::vector<Mesh *> components = this->getComponents<Mesh>(Cmp::Type::MESH, 4, Ett::Type::BOX, Ett::Type::WALL, Ett::Type::RAMP, Ett::Type::PILLAR);
    std::vector<Cube *> floor = this->getComponents<Cube>(Cmp::Type::CUBE, 1, Ett::Type::GROUND);

    for (size_t idx = 0; idx < players.size(); idx++) {
        players[idx]->createTriangleSelector(this->game->getSceneManager());
        for (size_t idy = 0; idy < floor.size(); idy++)
            players[idx]->pushTriangleSelector(floor[idy]->getTriangleSelector());
        for (size_t idy = 0; idy < components.size(); idy++)
            players[idx]->pushTriangleSelector(components[idy]->getTriangleSelector());
        players[idx]->createCollisionResponse(this->game->getSceneManager());
    }
    this->_newGame = false;
}

void System::playerMovements()
{
    size_t playerId = -1;
    size_t secPlayerId = -1;
    Mesh *playerMesh = nullptr;
    Mesh *secPlayerMesh = nullptr;
    Component *tmp = nullptr;
    Stat *stat = nullptr;
    Stat *stat2 = nullptr;
    irr::core::vector3df coords = {0, 0, 0};

    for (size_t idx = 0; idx < this->_entities.size(); idx++) {
        if (this->_entities[idx].getType() == Ett::PLAYER)
            playerId = this->_entities[idx].getID();
        else if (this->_entities[idx].getType() == Ett::PLAYER2)
            secPlayerId = this->_entities[idx].getID();
    }
    if (playerId == -1)
        return;
    tmp = this->getComponent(Cmp::MESH, playerId);
    if (tmp != NULL) {
        playerMesh = dynamic_cast<Mesh *>(tmp);
        stat = dynamic_cast<Stat *>(this->getComponent(Cmp::STAT, getId(Cmp::MESH, playerMesh)));
    } else
        return;
    tmp = this->getComponent(Cmp::MESH, secPlayerId);
    if (tmp != NULL) {
        secPlayerMesh = dynamic_cast<Mesh *>(tmp);
        stat2 = dynamic_cast<Stat *>(this->getComponent(Cmp::STAT, getId(Cmp::MESH, secPlayerMesh)));
    }
    coords = playerMesh->getNode()->getPosition();
    switch (this->keyPress())
    {
        case irr::KEY_KEY_Z:
            playerMesh->setCoords(coords.X, coords.Y, coords.Z + (2 * stat->getSpeed()));
            playerMesh->getNode()->setRotation(irr::core::vector3df{0, 0, 0});
            break;
        case irr::KEY_KEY_S:
            playerMesh->setCoords(coords.X, coords.Y, coords.Z - (2 * stat->getSpeed()));
            playerMesh->getNode()->setRotation(irr::core::vector3df{0, 180, 0});
            break;
        case irr::KEY_KEY_Q:
            playerMesh->setCoords(coords.X - (2 * stat->getSpeed()), coords.Y, coords.Z);
            playerMesh->getNode()->setRotation(irr::core::vector3df{0, 270, 0});
            break;
        case irr::KEY_KEY_D:
            playerMesh->setCoords(coords.X + (2 * stat->getSpeed()), coords.Y, coords.Z);
            playerMesh->getNode()->setRotation(irr::core::vector3df{0, 90, 0});
            break;
        default:
            break;
    }
    if (secPlayerMesh) {
        coords = secPlayerMesh->getNode()->getPosition();
        switch (this->keyPress())
        {
            case irr::KEY_UP:
                secPlayerMesh->setCoords(coords.X, coords.Y, coords.Z + (2 * stat2->getSpeed()));
                secPlayerMesh->getNode()->setRotation(irr::core::vector3df{0, 0, 0});
                break;
            case irr::KEY_DOWN:
                secPlayerMesh->setCoords(coords.X, coords.Y, coords.Z - (2 * stat2->getSpeed()));
                secPlayerMesh->getNode()->setRotation(irr::core::vector3df{0, 180, 0});
                break;
            case irr::KEY_LEFT:
                secPlayerMesh->setCoords(coords.X - (2 * stat2->getSpeed()), coords.Y, coords.Z);
                secPlayerMesh->getNode()->setRotation(irr::core::vector3df{0, 270, 0});
                break;
            case irr::KEY_RIGHT:
                secPlayerMesh->setCoords(coords.X + (2 * stat2->getSpeed()), coords.Y, coords.Z);
                secPlayerMesh->getNode()->setRotation(irr::core::vector3df{0, 90, 0});
                break;
            default:
                break;
        }
    }
}

void System::explosionTimer()
{
    std::vector<Timer *> bombsTimer = this->getComponents<Timer>(Cmp::Type::TIMER, 1, Ett::Type::BOMB);
    Mesh *bombMesh = nullptr;
    Stat *bombStat = nullptr;

    for (size_t a = 0; a < bombsTimer.size(); a += 1) {
        if (bombsTimer[a]->getEllapsedTime() >= 2000.0) {
            bombMesh = dynamic_cast<Mesh *>(this->getComponent(Cmp::MESH, getId(Cmp::TIMER, bombsTimer[a])));
            bombStat = dynamic_cast<Stat *>(this->getComponent(Cmp::STAT, getId(Cmp::TIMER, bombsTimer[a])));
            this->updateExplosion(bombMesh->getCoords(), bombStat);
            supEntity(getId(Cmp::MESH, bombMesh));
        }
    }
    bombsTimer.clear();
}

bool System::checkCollision(irr::scene::IAnimatedMeshSceneNode *node1, irr::scene::IAnimatedMeshSceneNode *node2)
{
    return node1->getTransformedBoundingBox().intersectsWithBox(node2->getTransformedBoundingBox());
}

void System::fillMap(std::vector<std::string> &map)
{
    std::ifstream file("./Assets/Map/0.map");
    std::string str;

    while (std::getline(file, str))
        map.push_back(str);
}

irr::core::vector3df System::getCenterPos(irr::core::vector3df coords)
{
    irr::core::vector3df pos = {0, coords.Y, 0};
    int arrZ = coords.Z;
    int arrX = coords.X;

    arrZ %= 100;
    arrX %= 100;
    if (arrZ >= 50)
        pos.Z = (coords.Z - arrZ) + 100;
    else
        pos.Z = (coords.Z - arrZ);
    if (arrX < 50)
        pos.X = (coords.X + (50 -arrX));
    else
        pos.X = (coords.X - (arrX - 50));

    return pos;
}

size_t System::getId(Cmp::Type type, Component *cmp)
{
    for (size_t idx = 0; idx < this->_stock.size(); idx++) {
        if (type == this->_stock[idx].getType()) {
            return this->_stock[idx].getId(cmp);
        }
    }
    return -1;
}

Ett::Type System::getType(size_t id)
{
    for (size_t idx = 0; idx < this->_entities.size(); idx++) {
        if (this->_entities[idx].getID() == id) {
            return this->_entities[idx].getType();
        }
    }
    return Ett::UNDEFINED;
}

void System::detectPowerUp()
{
    std::vector<Mesh *> players = this->getComponents<Mesh>(Cmp::Type::MESH, 3, Ett::Type::PLAYER, Ett::BOT, Ett::PLAYER2);
    std::vector<Mesh *> powersUp = this->getComponents<Mesh>(Cmp::Type::MESH, 2, Ett::Type::POWERUP);


    for (size_t idx = 0; idx < players.size(); idx += 1) {
        for (size_t idy = 0; idy < powersUp.size(); idy += 1) {
            if (this->getCenterPos(players[idx]->getCoords()).X > powersUp[idy]->getCoords().X - 3 && this->getCenterPos(players[idx]->getCoords()).X < powersUp[idy]->getCoords().X + 3 && this->getCenterPos(players[idx]->getCoords()).Z > powersUp[idy]->getCoords().Z - 3 && this->getCenterPos(players[idx]->getCoords()).Z < powersUp[idy]->getCoords().Z + 3) {
                dynamic_cast<Stat *>(this->getComponent(Cmp::STAT, getId(Cmp::MESH, players[idx])))->addStat(dynamic_cast<Stat *>(this->getComponent(Cmp::STAT, getId(Cmp::MESH, powersUp[idy]))));
                supEntity(getId(Cmp::MESH, powersUp[idy]));
                break;
            }
        }
    }
    players.clear();
    powersUp.clear();
}

Ett::Type System::canDestroy(irr::core::vector3df pos)
{
    std::vector<Mesh *> meshes = this->_death ? this->getComponents<Mesh>(Cmp::Type::MESH, 5, Ett::Type::BOX, Ett::Type::BOMB, Ett::Type::PLAYER, Ett::Type::PLAYER2) : this->getComponents<Mesh>(Cmp::Type::MESH, 2, Ett::Type::BOX, Ett::Type::BOMB);
    // std::vector<Mesh *> meshes = this->getComponents<Mesh>(Cmp::Type::MESH, 5, Ett::Type::BOX, Ett::Type::BOMB, Ett::Type::PLAYER, Ett::Type::PLAYER2);
    std::vector<Mesh *> colli = this->getComponents<Mesh>(Cmp::Type::MESH, 3, Ett::Type::PLAYER, Ett::Type::PLAYER2, Ett::Type::BOT);
    Ett::Type tmp = Ett::UNDEFINED;

    for (size_t idx = 0; idx < meshes.size(); idx++) {
        irr::core::vector3df posTmp = meshes[idx]->getNode()->getPosition();
        if (getCenterPos(posTmp).X > pos.X - 9 && getCenterPos(posTmp).X < pos.X + 9 && getCenterPos(posTmp).Z > pos.Z - 9 && getCenterPos(posTmp).Z < pos.Z + 9) {
            tmp = this->getType(this->getId(Cmp::MESH, meshes[idx]));
            if (tmp != Ett::BOMB) {
                for (size_t idy = 0; idy < colli.size(); idy++) {
                    colli[idy]->removeTriangleSelector(meshes[idx]->getNode()->getTriangleSelector());
                    colli[idy]->createCollisionResponse(this->game->getSceneManager());
                }
                supEntity(getId(Cmp::MESH, meshes[idx]));
            } else if (tmp == Ett::BOMB) {
                dynamic_cast<Timer *>(this->getComponent(Cmp::TIMER, getId(Cmp::MESH, meshes[idx])))->setTime(std::chrono::system_clock::time_point(std::chrono::high_resolution_clock::now() - std::chrono::seconds(2)));
            }
            return tmp;
        }
    }
    if (this->_death ) {
        std::vector<Mesh *> bots = this->getComponents<Mesh>(Cmp::Type::MESH, 1, Ett::Type::BOT);
        for (size_t idx = 0; idx < bots.size(); idx++) {
            irr::core::vector3df posTmp = bots[idx]->getNode()->getAbsolutePosition();
            if (getCenterPos(posTmp).X > pos.X - 9 && getCenterPos(posTmp).X < pos.X + 9 && getCenterPos(posTmp).Z > pos.Z - 9 && getCenterPos(posTmp).Z < pos.Z + 9) {
                for (size_t idy = 0; idy < colli.size(); idy++) {
                    colli[idy]->removeTriangleSelector(bots[idx]->getNode()->getTriangleSelector());
                    colli[idy]->createCollisionResponse(this->game->getSceneManager());
                }
                this->_direction.erase(this->_direction.begin() + idx);
                this->_way.erase(this->_way.begin() + idx);
                supEntity(getId(Cmp::MESH, bots[idx]));
                return Ett::BOT;
            }
        }
    }
    return Ett::UNDEFINED;
}

bool System::canDrop(size_t id, irr::core::vector3df pos)
{
    std::vector<Mesh *> meshes = this->getComponents<Mesh>(Cmp::Type::MESH, 4, Ett::Type::BOX, Ett::Type::BOMB, Ett::Type::WALL, Ett::Type::PILLAR);
    for (size_t idx = 0; idx < meshes.size(); idx++) {
        if (idx != id) {
            if (meshes[idx]->getCoords().X > pos.X - 2 && meshes[idx]->getCoords().X < pos.X + 2 && meshes[idx]->getCoords().Z > pos.Z - 2 && meshes[idx]->getCoords().Z < pos.Z + 2) {
                return false;
            }
        }
    }
    return true;
}

void System::dropBomb(Ett::Type controller, size_t botID)
{
    size_t playerId = -1;
    Stat *stats = nullptr;
    Mesh *player = nullptr;
    irr::core::vector3df pos;

    if (controller != Ett::BOT) {
        for (size_t idx = 0; idx < this->_entities.size(); idx++) {
            if (this->_entities[idx].getType() == controller)
                playerId = this->_entities[idx].getID();
        }
        if (playerId == -1)
            return;
    } else {
        playerId = botID;
    }
    player = dynamic_cast<Mesh *>(this->getComponent(Cmp::MESH, playerId));
    stats = dynamic_cast<Stat *>(this->getComponent(Cmp::STAT, playerId));
    if (!player || !stats)
        return;
    pos = getCenterPos(player->getNode()->getAbsolutePosition());
    if (canDrop(playerId, pos)) {
        this->addBomb(pos.X, pos.Y, pos.Z, "./Assets/Mesh/Bomb.obj", this->game->getSceneManager(),
        stats->getPower(), stats->getSpeed());
    }
}

void System::setParticle(irr::core::vector3df pos, int &state)
{
    if (!state)
        return;

    std::vector<Mesh *> meshes = this->getComponents<Mesh>(Cmp::Type::MESH, 8, Ett::Type::BOX, Ett::Type::WALL, Ett::Type::BOMB, Ett::Type::RAMP, Ett::PLAYER2, Ett::PLAYER, Ett::BOT, Ett::Type::PILLAR);
    for (size_t idx = 0; idx < meshes.size(); idx++) {
        irr::core::vector3df posTmp = meshes[idx]->getNode()->getAbsolutePosition();
        if (getCenterPos(posTmp).X > pos.X - 3 && getCenterPos(posTmp).X < pos.X + 3 && getCenterPos(posTmp).Z > pos.Z - 3 && getCenterPos(posTmp).Z < pos.Z + 3) {
            
            if (canDestroy(pos) == Ett::BOX) {
                this->game->explosionParticle(pos.X, pos.Y, pos.Z);
                if ((rand() % 5) == 1)
                    addPowerUp(pos.X, pos.Y, pos.Z, "./Assets/Mesh/powerUp.obj", this->game->getSceneManager());
            }
            state = 0;
            return;
        }
    }
    this->game->explosionParticle(pos.X, pos.Y, pos.Z);
}

void System::checkVictory()
{
    int check = 0;

    for (size_t i = 0; i < this->_entities.size(); i += 1) {
        if (this->_entities[i].getType() == Ett::PLAYER || this->_entities[i].getType() == Ett::BOT || this->_entities[i].getType() == Ett::PLAYER2)
            check += 1;
    }

    if (check <= 1) {
        this->_state = 0;
        this->_window->getCursorControl()->setVisible(true);
        this->switchMap();
    }
}

void System::launchIA()
{
    std::vector<Mesh *> bots = this->getComponents<Mesh>(Cmp::MESH, 1, Ett::BOT);
    std::srand(time(NULL));
    
    for (size_t i = 0; i < bots.size(); i += 1) {
        int dir = std::rand() % 4;
        irr::core::vector3df tmp = bots[i]->getNode()->getPosition();
        Stat *stat = dynamic_cast<Stat *>(this->getComponent(Cmp::STAT, getId(Cmp::MESH, bots[i])));

        if (this->_direction[i].X != -1) {
            if ((this->_direction[i].X < tmp.X - 6 || this->_direction[i].X > tmp.X + 6) && (this->_direction[i].Z < tmp.Z - 6 || this->_direction[i].Z > tmp.Z + 6)) {
                if (tmp.X > this->_way[i].X - 0.1 && tmp.X < this->_way[i].X + 0.1 && tmp.Z > this->_way[i].Z - 0.1 && tmp.Z < this->_way[i].Z + 0.1) {
                    bots[i]->setCoords(this->_direction[i].X, this->_direction[i].Y, this->_direction[i].Z);
                    continue;
                }
                if (std::abs(this->_direction[i].X - tmp.X) > std::abs(this->_direction[i].Z - tmp.Z)) {
                    if (this->_direction[i].X > tmp.X) {
                        bots[i]->setCoords(tmp.X + (1 * stat->getSpeed()), tmp.Y, tmp.Z);
                    } else {
                        bots[i]->setCoords(tmp.X - (1 * stat->getSpeed()), tmp.Y, tmp.Z);
                    }
                } else {
                    if (this->_direction[i].Z > tmp.Z) {
                        bots[i]->setCoords(tmp.X, tmp.Y, tmp.Z + (1 * stat->getSpeed()));
                    } else {
                        bots[i]->setCoords(tmp.X, tmp.Y, tmp.Z - (1 * stat->getSpeed()));
                    }
                }
                this->_way[i] = tmp;
                continue;
            }
        }
        this->_way[i] = tmp;
        if (dir == 0) {
            if (canDrop(-1, getCenterPos(irr::core::vector3df{tmp.X + 100, tmp.Y, tmp.Z}))) {
                bots[i]->setCoords(tmp.X + (1 * stat->getSpeed()), tmp.Y, tmp.Z);
                bots[i]->getNode()->setRotation(irr::core::vector3df{0, 90, 0});
                this->_direction[i] = getCenterPos(irr::core::vector3df{tmp.X + 100, tmp.Y, tmp.Z});
                if (rand() % 20 == 0)
                    dropBomb(Ett::BOT, getId(Cmp::MESH, bots[i]));
                continue;
            }
            if (canDrop(-1, getCenterPos(irr::core::vector3df{tmp.X - 100, tmp.Y, tmp.Z}))) {
                bots[i]->setCoords(tmp.X - (1 * stat->getSpeed()), tmp.Y, tmp.Z);
                bots[i]->getNode()->setRotation(irr::core::vector3df{0, 270, 0});
                this->_direction[i] = getCenterPos(irr::core::vector3df{tmp.X - 100, tmp.Y, tmp.Z});
                if (rand() % 20 == 0)
                    dropBomb(Ett::BOT, getId(Cmp::MESH, bots[i]));
                continue;
            }
            if (canDrop(-1, getCenterPos(irr::core::vector3df{tmp.X, tmp.Y, tmp.Z + 100}))) {
                bots[i]->setCoords(tmp.X, tmp.Y, tmp.Z + (1 * stat->getSpeed()));
                bots[i]->getNode()->setRotation(irr::core::vector3df{0, 0, 0});
                this->_direction[i] = getCenterPos(irr::core::vector3df{tmp.X, tmp.Y, tmp.Z + 100});
                if (rand() % 20 == 0)
                    dropBomb(Ett::BOT, getId(Cmp::MESH, bots[i]));
                continue;
            }
            if (canDrop(-1, getCenterPos(irr::core::vector3df{tmp.X, tmp.Y, tmp.Z - 100}))) {
                bots[i]->setCoords(tmp.X, tmp.Y, tmp.Z - (1 * stat->getSpeed()));
                bots[i]->getNode()->setRotation(irr::core::vector3df{0, 18, 0});
                this->_direction[i] = getCenterPos(irr::core::vector3df{tmp.X, tmp.Y, tmp.Z - 100});
                if (rand() % 20 == 0)
                    dropBomb(Ett::BOT, getId(Cmp::MESH, bots[i]));
                continue;
            }
        } else if (dir == 1) {
            if (canDrop(-1, getCenterPos(irr::core::vector3df{tmp.X - 100, tmp.Y, tmp.Z}))) {
                bots[i]->setCoords(tmp.X - (1 * stat->getSpeed()), tmp.Y, tmp.Z);
                bots[i]->getNode()->setRotation(irr::core::vector3df{0, 270, 0});
                this->_direction[i] = getCenterPos(irr::core::vector3df{tmp.X - 100, tmp.Y, tmp.Z});
                if (rand() % 20 == 0)
                    dropBomb(Ett::BOT, getId(Cmp::MESH, bots[i]));
                continue;
            }
            if (canDrop(-1, getCenterPos(irr::core::vector3df{tmp.X, tmp.Y, tmp.Z + 100}))) {
                bots[i]->setCoords(tmp.X, tmp.Y, tmp.Z + (1 * stat->getSpeed()));
                bots[i]->getNode()->setRotation(irr::core::vector3df{0, 0, 0});
                this->_direction[i] = getCenterPos(irr::core::vector3df{tmp.X, tmp.Y, tmp.Z + 100});
                if (rand() % 20 == 0)
                    dropBomb(Ett::BOT, getId(Cmp::MESH, bots[i]));
                continue;
            }
            if (canDrop(-1, getCenterPos(irr::core::vector3df{tmp.X, tmp.Y, tmp.Z - 100}))) {
                bots[i]->setCoords(tmp.X, tmp.Y, tmp.Z - (1 * stat->getSpeed()));
                bots[i]->getNode()->setRotation(irr::core::vector3df{0, 18, 0});
                this->_direction[i] = getCenterPos(irr::core::vector3df{tmp.X, tmp.Y, tmp.Z - 100});
                if (rand() % 20 == 0)
                    dropBomb(Ett::BOT, getId(Cmp::MESH, bots[i]));
                continue;
            }
            if (canDrop(-1, getCenterPos(irr::core::vector3df{tmp.X + 100, tmp.Y, tmp.Z}))) {
                bots[i]->setCoords(tmp.X + (1 * stat->getSpeed()), tmp.Y, tmp.Z);
                bots[i]->getNode()->setRotation(irr::core::vector3df{0, 90, 0});
                this->_direction[i] = getCenterPos(irr::core::vector3df{tmp.X + 100, tmp.Y, tmp.Z});
                if (rand() % 20 == 0)
                    dropBomb(Ett::BOT, getId(Cmp::MESH, bots[i]));
                continue;
            }
        } else if (dir == 2) {
            if (canDrop(-1, getCenterPos(irr::core::vector3df{tmp.X, tmp.Y, tmp.Z + 100}))) {
                bots[i]->setCoords(tmp.X, tmp.Y, tmp.Z + (1 * stat->getSpeed()));
                bots[i]->getNode()->setRotation(irr::core::vector3df{0, 0, 0});
                this->_direction[i] = getCenterPos(irr::core::vector3df{tmp.X, tmp.Y, tmp.Z + 100});
                if (rand() % 20 == 0)
                    dropBomb(Ett::BOT, getId(Cmp::MESH, bots[i]));
                continue;
            }
            if (canDrop(-1, getCenterPos(irr::core::vector3df{tmp.X, tmp.Y, tmp.Z - 100}))) {
                bots[i]->setCoords(tmp.X, tmp.Y, tmp.Z - (1 * stat->getSpeed()));
                bots[i]->getNode()->setRotation(irr::core::vector3df{0, 18, 0});
                this->_direction[i] = getCenterPos(irr::core::vector3df{tmp.X, tmp.Y, tmp.Z - 100});
                if (rand() % 20 == 0)
                    dropBomb(Ett::BOT, getId(Cmp::MESH, bots[i]));
                continue;
            }
            if (canDrop(-1, getCenterPos(irr::core::vector3df{tmp.X + 100, tmp.Y, tmp.Z}))) {
                bots[i]->setCoords(tmp.X + (1 * stat->getSpeed()), tmp.Y, tmp.Z);
                bots[i]->getNode()->setRotation(irr::core::vector3df{0, 90, 0});
                this->_direction[i] = getCenterPos(irr::core::vector3df{tmp.X + 100, tmp.Y, tmp.Z});
                if (rand() % 20 == 0)
                    dropBomb(Ett::BOT, getId(Cmp::MESH, bots[i]));
                continue;
            }
            if (canDrop(-1, getCenterPos(irr::core::vector3df{tmp.X - 100, tmp.Y, tmp.Z}))) {
                bots[i]->setCoords(tmp.X - (1 * stat->getSpeed()), tmp.Y, tmp.Z);
                bots[i]->getNode()->setRotation(irr::core::vector3df{0, 270, 0});
                this->_direction[i] = getCenterPos(irr::core::vector3df{tmp.X - 100, tmp.Y, tmp.Z});
                if (rand() % 20 == 0)
                    dropBomb(Ett::BOT, getId(Cmp::MESH, bots[i]));
                continue;
            }
        } else if (dir == 3) {
            if (canDrop(-1, getCenterPos(irr::core::vector3df{tmp.X, tmp.Y, tmp.Z - 100}))) {
                bots[i]->setCoords(tmp.X, tmp.Y, tmp.Z - (1 * stat->getSpeed()));
                bots[i]->getNode()->setRotation(irr::core::vector3df{0, 18, 0});
                this->_direction[i] = getCenterPos(irr::core::vector3df{tmp.X, tmp.Y, tmp.Z - 100});
                if (rand() % 20 == 0)
                    dropBomb(Ett::BOT, getId(Cmp::MESH, bots[i]));
                continue;
            }
            if (canDrop(-1, getCenterPos(irr::core::vector3df{tmp.X + 100, tmp.Y, tmp.Z}))) {
                bots[i]->setCoords(tmp.X + (1 * stat->getSpeed()), tmp.Y, tmp.Z);
                bots[i]->getNode()->setRotation(irr::core::vector3df{0, 90, 0});
                this->_direction[i] = getCenterPos(irr::core::vector3df{tmp.X + 100, tmp.Y, tmp.Z});
                if (rand() % 20 == 0)
                    dropBomb(Ett::BOT, getId(Cmp::MESH, bots[i]));
                continue;
            }
            if (canDrop(-1, getCenterPos(irr::core::vector3df{tmp.X - 100, tmp.Y, tmp.Z}))) {
                bots[i]->setCoords(tmp.X - (1 * stat->getSpeed()), tmp.Y, tmp.Z);
                bots[i]->getNode()->setRotation(irr::core::vector3df{0, 270, 0});
                this->_direction[i] = getCenterPos(irr::core::vector3df{tmp.X - 100, tmp.Y, tmp.Z});
                if (rand() % 20 == 0)
                    dropBomb(Ett::BOT, getId(Cmp::MESH, bots[i]));
                continue;
            }
            if (canDrop(-1, getCenterPos(irr::core::vector3df{tmp.X, tmp.Y, tmp.Z + 100}))) {
                bots[i]->setCoords(tmp.X, tmp.Y, tmp.Z + (1 * stat->getSpeed()));
                bots[i]->getNode()->setRotation(irr::core::vector3df{0, 0, 0});
                this->_direction[i] = getCenterPos(irr::core::vector3df{tmp.X, tmp.Y, tmp.Z + 100});
                if (rand() % 20 == 0)
                    dropBomb(Ett::BOT, getId(Cmp::MESH, bots[i]));
                continue;
            }
        }
    }
}

void System::supEntity(size_t id)
{
    for (size_t idx = 0; idx < this->_entities.size(); idx += 1) {
        if (this->_entities[idx].getID() == id) {
            this->_entities.erase(this->_entities.begin() + idx);
            supComponent(id);
            break;
        }
    }
}

void System::updateExplosion(irr::core::vector3df pos, Stat *stats)
{
    std::vector<int> sidesBlock(4, 1);
    int a = 1;
    int b = 1;
    int c = 1;
    int d = 1;
    this->sound->playSound();
    this->game->explosionParticle(pos.X, pos.Y, pos.Z);
    for (size_t idx = 0; idx < stats->getPower(); idx += 1) {
        setParticle(irr::core::vector3df{pos.X + ((idx + 1) * 100), pos.Y, pos.Z}, a);
        setParticle(irr::core::vector3df{pos.X - ((idx + 1) * 100), pos.Y, pos.Z}, b);
        setParticle(irr::core::vector3df{pos.X, pos.Y, pos.Z + ((idx + 1) * 100)}, c);
        setParticle(irr::core::vector3df{pos.X, pos.Y, pos.Z - ((idx + 1) * 100)}, d);
    }

    /* ----------AUZIAS------------
    for (size_t i = 0; i < 4; i += 1) {
        this->game->explosionParticle(pos.X - (stats->getPower() * 100), pos.Z - ((i + 1) * 100));
        this->game->explosionParticle(pos.X + ((i + 1) * 100), pos.Z - (stats->getPower() * 100));
        this->game->explosionParticle(pos.X + (stats->getPower() * 100), pos.Z + ((i + 1) * 100));
        this->game->explosionParticle(pos.X - ((i + 1) * 100), pos.Z + (stats->getPower() * 100));
    } */
}


void System::createMap(std::vector<std::string> map)
{
    int x = 0;
    int i = 0;
    int max_i = 0;
    bool up = false;

    if (map.empty())
        this->fillMap(map);
    for (x = 0, i = 0; x < map.size(); x++) {
        for (i = 0; i < map[x].size(); i++) {
            if (map[x][i] == '!')
                continue;
            if ((x + i) % 2 == 0)
                this->addGround(250 + (x * 100), 1075.0, 200 + (i * 100), this->game->getSceneManager(), this->game->getVideoDriver()->getTexture("./Assets/Texture/floor1.png"));
            else
                this->addGround(250 + (x * 100), 1075.0, 200 + (i * 100), this->game->getSceneManager(), this->game->getVideoDriver()->getTexture("./Assets/Texture/floor2.png"));
            if (map[x][i] == '&') {
                if ((x + i) % 2 == 0)
                    this->addGround(250 + (x * 100), 1175.0, 200 + (i * 100), this->game->getSceneManager(), this->game->getVideoDriver()->getTexture("./Assets/Texture/floor3.png"));
                else
                    this->addGround(250 + (x * 100), 1175.0, 200 + (i * 100), this->game->getSceneManager(), this->game->getVideoDriver()->getTexture("./Assets/Texture/floor4.png"));
            } else if (map[x][i] == '*') {
                this->addWall(250 + (x * 100), 1175.0, 200.0 + (i * 100), "./Assets/Mesh/Wall.obj", this->game->getSceneManager());
            } else if (map[x][i] == '+') {
                this->addPillar(250 + (x * 100), 1175.0, 200.0 + (i * 100), "./Assets/Mesh/Pillar.obj", this->game->getSceneManager());
            } else if (map[x][i] == 'x') {
                this->addBox(250 + (x * 100), 1175.0, 200.0 + (i * 100), "./Assets/Mesh/Box2.obj", this->game->getSceneManager());
            } else if (map[x][i] == 'p') {
                this->addBot(250 + (x * 100), 1200.0, 200.0 + (i * 100), "./Assets/Mesh/bomberman.obj", this->game->getSceneManager(), 0.0, 0.0, 0.0, false, "./Assets/Texture/Bomberman_Blue.png", 1, 1);
            } else if (map[x][i] == 'm') {
                this->addBot(250 + (x * 100), 1200.0, 200.0 + (i * 100), "./Assets/Mesh/bomberman.obj", this->game->getSceneManager(), 0.0, 0.0, 0.0, false, "./Assets/Texture/Bomberman_Red.png", 1, 1);
            } else if (map[x][i] == 'c') {
                this->addBot(250 + (x * 100), 1200.0, 200.0 + (i * 100), "./Assets/Mesh/bomberman.obj", this->game->getSceneManager(), 0.0, 0.0, 0.0, false, "./Assets/Texture/Bomberman_White.png", 1, 1);
            } else if (map[x][i] == 'b') {
                this->addBot(250 + (x * 100), 1200.0, 200.0 + (i * 100), "./Assets/Mesh/bomberman.obj", this->game->getSceneManager(), 0.0, 0.0, 0.0, false, "./Assets/Texture/Bomberman_Yellow.png", 1, 1);
            } else if (map[x][i] == '#') {
                this->addWall(250 + (x * 100), 1275.0, 200.0 + (i * 100), "./Assets/Mesh/Wall.obj", this->game->getSceneManager());
                up = true;
            } else if (map[x][i] == 'X') {
                this->addBox(250 + (x * 100), 1275.0, 200.0 + (i * 100), "./Assets/Mesh/Box2.obj", this->game->getSceneManager());
                up = true;
            } else if (map[x][i] == '-') {
                this->addPillar(250 + (x * 100), 1275.0, 200.0 + (i * 100), "./Assets/Mesh/Pillar.obj", this->game->getSceneManager());
                up = true;
            } else if (map[x][i] == '<') {
                this->addRamp(250 + (x * 100), 1175.0, 200.0 + (i * 100), "./Assets/Mesh/Ramp.obj", this->game->getSceneManager(), 0.0, 0.0, 0.0);
            } else if (map[x][i] == '>') {
                this->addRamp(250 + (x * 100), 1175.0, 200.0 + (i * 100), "./Assets/Mesh/Ramp.obj", this->game->getSceneManager(), 0.0, 180.0, 0.0);
            } else if (map[x][i] == '/') {
                this->addRamp(250 + (x * 100), 1175.0, 200.0 + (i * 100), "./Assets/Mesh/Ramp.obj", this->game->getSceneManager(), 0.0, 90, 0.0);
            } else if (map[x][i] == '\\') {
                this->addRamp(250 + (x * 100), 1175.0, 200.0 + (i * 100), "./Assets/Mesh/Ramp.obj", this->game->getSceneManager(), 0.0, 270.0, 0.0);
            } else if (map[x][i] == 'B') {
                this->addBot(250 + (x * 100), 1300.0, 200.0 + (i * 100), "./Assets/Mesh/bomberman.obj", this->game->getSceneManager(), 0.0, 0.0, 0.0, false, "./Assets/Texture/Bomberman_Jordan.png", 1, 1);
                up = true;
            } else if (map[x][i] == 'C') {
                this->addBot(250 + (x * 100), 1300.0, 200.0 + (i * 100), "./Assets/Mesh/bomberman.obj", this->game->getSceneManager(), 0.0, 0.0, 0.0, false, "./Assets/Texture/Bomberman_Jordan.png", 1, 1);
                up = true;
            } else if (map[x][i] == 'P') {
                this->addBot(250 + (x * 100), 1300.0, 200.0 + (i * 100), "./Assets/Mesh/bomberman.obj", this->game->getSceneManager(), 0.0, 0.0, 0.0, false, "./Assets/Texture/Bomberman_Jordan.png", 1, 1);
                up = true;
            } else if (map[x][i] == 'M') {
                this->addBot(250 + (x * 100), 1300.0, 200.0 + (i * 100), "./Assets/Mesh/bomberman.obj", this->game->getSceneManager(), 0.0, 0.0, 0.0, false, "./Assets/Texture/Bomberman_Jordan.png", 1, 1);
                up = true;
            }
            if (up) {
                if ((x + i) % 2 == 0)
                    this->addGround(250 + (x * 100), 1175.0, 200 + (i * 100), this->game->getSceneManager(), this->game->getVideoDriver()->getTexture("./Assets/Texture/floor3.png"));
                else
                    this->addGround(250 + (x * 100), 1175.0, 200 + (i * 100), this->game->getSceneManager(), this->game->getVideoDriver()->getTexture("./Assets/Texture/floor4.png"));
                up = false;
            }
        }
        max_i = (i > max_i) ? i : max_i;
    }
    // irr::video::ITexture* normalMap = this->game->getVideoDriver()->getTexture("./Assets/Texture/PowerUp.png");
    // irr::scene::IAnimatedMeshSceneNode* gun =this->game->getSceneManager()->addAnimatedMeshSceneNode(this->game->getSceneManager()->getMesh("./Assets/Mesh/powerUp.b3d"));
             
    // ((irr::scene::ISkinnedMesh*)gun)->convertMeshToTangents();   //ne pas oublier de convertir le mesh
    //                                                         //afin de pouvoir utiliser les fonctions ci-dessous
    // gun->setJointMode(irr::scene::EJUOR_CONTROL);
    // gun->setMaterialTexture(0, this->game->getVideoDriver()->getTexture("./Assets/Texture/PowerUp.png"));
    // gun->setMaterialTexture(1, normalMap);
    // gun->getMaterial(0).SpecularColor.set(0,0,0,0);
    // gun->setMaterialType(irr::video::EMT_NORMAL_MAP_SOLID);
    // gun->setScale(irr::core::vector3df(100.f, 100.f, 100.f));
    // gun->setPosition(irr::core::vector3df(350,1175,300));
    this->game->fixCamera(250, 200, x, max_i);
}

void System::switchMap()
{
    this->_idCounter = 0;
    this->_entities.clear();
    std::vector<std::string> map;
    srand(time(NULL));
    int size_x = rand() % 25;
    int size_y = rand() % 25;
    int odds = 0;
    this->_direction.clear();
    this->_way.clear();

    size_x = (size_x < 10) ? 10 : size_x;
    size_y = (size_y < 10) ? 10 : size_y;
    for (size_t idx = 0; idx < 4; idx++) {
        this->_direction.push_back({-1, -1, -1});
        this->_way.push_back({-1, -1, -1});
    }
    for (size_t idx = 0; idx < this->_stock.size(); idx++) {
        this->_stock[idx].resetStorage();
    }
    for (int idx = 0; idx < size_x; idx++) {
        map.push_back(std::string());
        if (idx == 0 || idx == size_x - 1) {
            for (int idy = 0; idy < size_y; idy++)
                map[idx].push_back('*');
        } else {
            map[idx].push_back('*');
            for (int idy = 1; idy < size_y - 1; idy++) {
                odds = rand() % 12;
                if (odds <= 6) {
                    map[idx].push_back('x');
                } else if (odds <= 8) {
                    map[idx].push_back('+');
                } else {
                    map[idx].push_back(' ');
                }
            }
            map[idx].push_back('*');
        }
    }
    map[1][1] = 'b';
    map[1][2] = ' ';
    map[2][1] = ' ';
    map[1][size_y - 2] = 'p';
    map[1][size_y - 3] = ' ';
    map[2][size_y - 2] = ' ';
    map[size_x - 2][1] = 'm';
    map[size_x - 2][2] = ' ';
    map[size_x - 3][1] = ' ';
    map[size_x - 2][size_y - 2] = 'c';
    map[size_x - 3][size_y - 2] = ' ';
    map[size_x - 2][size_y - 3] = ' ';
    this->createMap(map);
}

void System::loadMap()
{
    this->_entities.clear();
    std::ifstream file("./Assets/Map/save.map");
    std::vector<std::string> map;
    std::string str;

    for (size_t idx = 0; idx < this->_stock.size(); idx++) {
        this->_stock[idx].resetStorage();
    }
    while (std::getline(file, str))
        map.push_back(str);
    this->createMap(map);
}

void System::saveMap()
{
    std::ofstream file("./Assets/Map/save.map");
    std::vector<std::string> map;
    irr::core::vector3df pos;
    std::vector<Mesh *> meshes = this->getComponents<Mesh>(Cmp::MESH, 7, Ett::BOX, Ett::WALL, Ett::PILLAR, Ett::RAMP, Ett::PLAYER, Ett::PLAYER2, Ett::BOT);
    std::vector<Cube *> cubes = this->getComponents<Cube>(Cmp::CUBE, 1, Ett::GROUND);
    Ett::Type tmp;
    int players = 0;

    for (size_t idx = 0; idx < 100; idx++) {
        map.push_back(std::string(100, 0));
    }
    for (size_t idx = 0; idx < cubes.size(); idx++) {
        pos = getCenterPos(cubes[idx]->getNode()->getAbsolutePosition());
        pos.X = (pos.X - 250) / 100;
        pos.Z = (pos.Z - 200) / 100;
        if (pos.Y == 1075) {
            map[pos.X][pos.Z] = (map[pos.X][pos.Z] == 0) ? ' ' : map[pos.X][pos.Z];
        } else {
            map[pos.X][pos.Z] = (map[pos.X][pos.Z] == 0) ? '&' : (map[pos.X][pos.Z] == ' ') ? '&' : map[pos.X][pos.Z];
        }
    }
    for (size_t idx = 0; idx < meshes.size(); idx++) {
        pos = getCenterPos(meshes[idx]->getNode()->getAbsolutePosition());
        pos.X = (pos.X - 250) / 100;
        pos.Z = (pos.Z - 200) / 100;
        tmp = this->getType(this->getId(Cmp::MESH, meshes[idx]));
        if (pos.Y > 1173 && pos.Y < 1176) {
            switch (tmp) {
                case Ett::WALL:
                    map[pos.X][pos.Z] = '*';
                    break;
                case Ett::PILLAR:
                    map[pos.X][pos.Z] = '+';
                    break;
                case Ett::BOX:
                    map[pos.X][pos.Z] = 'x';
                    break;
                case Ett::RAMP:
                    if (meshes[idx]->getNode()->getRotation().Y == 0.0) {
                        map[pos.X][pos.Z] = '<';
                    } else if (meshes[idx]->getNode()->getRotation().Y == 90.0) {
                        map[pos.X][pos.Z] = '/';
                    } else if (meshes[idx]->getNode()->getRotation().Y == 180.0) {
                        map[pos.X][pos.Z] = '>';
                    } else if (meshes[idx]->getNode()->getRotation().Y == 270.0) {
                        map[pos.X][pos.Z] = '\\';
                    }
                    break;
                default:
                    break;
            }
            if (tmp == Ett::PLAYER || tmp == Ett::PLAYER2 || tmp == Ett::BOT) {
                switch (players) {
                    case 0:
                        map[pos.X][pos.Z] = 'p';
                        break;
                    case 1:
                        map[pos.X][pos.Z] = 'm';
                        break;
                    case 2:
                        map[pos.X][pos.Z] = 'b';
                        break;
                    case 3:
                        map[pos.X][pos.Z] = 'c';
                        break;
                    default:
                        break;
                }
                players++;
            }
        } else if (pos.Y > 1273 && pos.Y < 1276) {
            switch (tmp) {
                case Ett::GROUND:
                    map[pos.X][pos.Z] = (map[pos.X][pos.Z] == 0) ? '&' : (map[pos.X][pos.Z] == ' ') ? '&' : map[pos.X][pos.Z];
                    break;
                case Ett::WALL:
                    map[pos.X][pos.Z] = '#';
                    break;
                case Ett::PILLAR:
                    map[pos.X][pos.Z] = '-';
                    break;
                case Ett::BOX:
                    map[pos.X][pos.Z] = 'X';
                    break;
                default:
                    break;
            }
            if (tmp == Ett::PLAYER || tmp == Ett::PLAYER2 || tmp == Ett::BOT) {
                switch (players) {
                case 0:
                    map[pos.X][pos.Z] = 'P';
                    break;
                case 1:
                    map[pos.X][pos.Z] = 'M';
                    break;
                case 2:
                    map[pos.X][pos.Z] = 'B';
                    break;
                case 3:
                    map[pos.X][pos.Z] = 'C';
                    break;
                default:
                    break;
                }
                players++;
            }
        }
    }
    for (size_t idx = 0; idx < map.size(); idx++) {
        for (size_t idy = 0; map[idx].find('#', idy) != map[idx].npos || map[idx].find('*', idy) != map[idx].npos; idy++) {
            map[idx][idy] = (map[idx][idy] == 0) ? '!' : map[idx][idy];
            file << map[idx][idy];
        }
        file << std::endl;
        if (map[idx][0] == 0) {
            break;
        }
    }
    file.close();
}
