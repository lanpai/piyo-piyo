#pragma once

#include <string>

namespace piyo {
    class Engine;

    enum class ComponentType {
        USER,
        WINDOW,
        INPUT
    };

    class Component {
        friend Engine;

        public:
            Component(const std::string& name, ComponentType type = ComponentType::USER)
                : _name(name)
                , _type(type) {};

            void SetParent(Engine *parent, unsigned int id);

            const std::string& ToString() const { return this->_name; };
            unsigned int GetID() const { return this->_id; };
            ComponentType GetType() const { return this->_type; };

        protected:
            virtual void OnInit() {};
            virtual void OnDestroy() {};
            virtual void OnPreUpdate() {};
            virtual void OnPostUpdate() {};
            virtual void OnPreDraw() {};
            virtual void OnPostDraw() {};

            std::string _name;
            ComponentType _type;

            Engine *_parent;
            unsigned int _id;
    };
}
