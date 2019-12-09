#pragma once

namespace piyo {
    class Engine;

    class Scene {
        friend Engine;

        public:
            virtual void OnInit() {};
            virtual void OnDestroy() {};
            virtual void OnUpdate() {};
            virtual void OnDraw() {};

        protected:
            Engine *_parent;
    };
}
