/*                                                                                                                                                                  
** EPITECH PROJECT, 2020                                                                                                                                            
** OOP_indie_studio_2019                                                                                                                                            
** File description:                                                                                                                                                
** Mesh                                                                                                                                                             
*/

#ifndef MESH_HPP_
#define MESH_HPP_

#include "Component.hpp"

class Mesh : public Component {
    public:
        Mesh(double x, double y, double z, const char *path, irr::scene::ISceneManager *smgr, double rotx = 0.0, double roty = 0.0, double rotz = 0.0, bool rotate = false, const char *texture = NULL, irr::core::vector3df scale = irr::core::vector3df{100.0f, 100.0f, 100.0f});
        ~Mesh();
        irr::scene::IAnimatedMeshSceneNode *getNode() const;
        irr::scene::IAnimatedMesh *getMesh() const;
        irr::core::vector3df &getCoords();
        irr::scene::ITriangleSelector *getTriangleSelector() const;
        irr::scene::IMetaTriangleSelector *getTriangleSelectors() const;
        void createCollisionResponse(irr::scene::ISceneManager *smgr);
        void createTriangleSelector(irr::scene::ISceneManager *smgr);
        void pushTriangleSelector(irr::scene::ITriangleSelector *selector);
        void removeTriangleSelector(irr::scene::ITriangleSelector *selector);
        void toggleMeshPosition();
        void setCoords(float x, float y, float z);

    protected:
    private:
        irr::core::vector3df _coords;
        irr::scene::IAnimatedMeshSceneNode *_node;
        irr::scene::IAnimatedMesh *_mesh;
        irr::scene::ISceneManager *_smgr;
        irr::scene::ITriangleSelector* _selector;
        irr::scene::IMetaTriangleSelector* _selectors;
        irr::scene::ISceneNodeAnimator* _animator;
};

#endif /* !MESH_HPP_ */

