/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Cube
*/

#ifndef CUBE_HPP_
#define CUBE_HPP_

#include "Component.hpp"

class Cube : public Component {
    public:
        Cube(double x, double y, double z, irr::scene::ISceneManager *smgr, irr::video::ITexture *texture);
        ~Cube();
        irr::scene::IMeshSceneNode *getNode() const;
        irr::core::vector3df &getCoords();
        irr::scene::ITriangleSelector *getTriangleSelector() const;
        void setCoords(float x, float y, float z);

    protected:
    private:
        irr::core::vector3df _coords;
        irr::scene::IMeshSceneNode *_node;
        irr::scene::ISceneManager *_smgr;
        irr::scene::ITriangleSelector* _selector;
};

#endif /* !MESH_HPP_ */
