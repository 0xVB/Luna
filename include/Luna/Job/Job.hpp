#pragma once

namespace Luna {
    class TaskScheduler;
    class Job {
        public:
            Job(const char* name) : _name(name) {};
            virtual void run(TaskScheduler* ts) = 0;

            inline const char* getName() { return _name; }
            inline void markForRemoval() { _canRemove = true; }
            inline bool isMarkedForRemoval() { return _canRemove; }
        private:
            const char* _name = nullptr;
            bool _canRemove = false;
    };
}