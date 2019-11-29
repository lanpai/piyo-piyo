#include "Component.hpp"

#include "Engine.hpp"

namespace piyo {
    void Component::SetParent(Engine *parent, unsigned int id) {
        this->_parent = parent;
        this->_id = id;
    }
}
