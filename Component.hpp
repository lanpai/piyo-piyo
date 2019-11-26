#pragma once

#include <string>

namespace piyo {
    class Engine;

    enum class ComponentType {
        DEFAULT,
        WINDOW
    };

    class Component {
        friend Engine;

        public:
            Component(const std::string& name, ComponentType type) : _name(name), _type(type) {};
            virtual ~Component() {};

            void SetParent(Engine *parent) { this->_parent = parent; };

            const std::string& ToString() const { return this->_name; };
            ComponentType GetType() const { return this->_type; };

        protected:
            virtual void OnInit() {};
            virtual void OnPreUpdate() {};
            virtual void OnPostUpdate() {};
            virtual void OnPreDraw() {};
            virtual void OnPostDraw() {};

            std::string _name = "Component";
            ComponentType _type = ComponentType::DEFAULT;

        private:
            Engine *_parent;
    };
}
