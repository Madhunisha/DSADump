// Checkout - https://github.com/Pseudomanifold/Events/blob/master/Demo.cc


#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <list>
#include <thread>
#include <chrono>

using namespace std;

class Event {
private:
    string eventId;
    void* parameter;
public:
    Event(string id, void* param = 0) {
        eventId = id;
        parameter = param;
    }
    ~Event() {}
    string getId() {return eventId;}
    void* getParam() {return parameter;}
};

class Observer {
private:
public:
    Observer() {}
    virtual ~Observer() {}
    virtual void handleEvent(Event* event)  = 0;
};

class EventSystem {
private:
    unordered_map<string, unordered_set<Observer*> > database;
    std::list<Event> currentEvents;
    EventSystem() {}
    //~EventSystem();
    //EventSystem(const EventSystem& rhs) {}
    //EventSystem& operator=(const EventSystem& rhs) {}
public:
    ~EventSystem() { this->Shutdown(); }

    static EventSystem* Instance() {
        static EventSystem instance;
        return &instance;
    }

    void dispatchEvent(Event* event) {
        auto observers = database[event->getId()];
        for(auto const& o : observers ) {
            o->handleEvent(event);
        }
    }
    void registerObserver(string event, Observer* obs) {
        database[event].insert(obs);
    }
    void unregisterObserver(Event* event, Observer* obs) {
        database[event->getId()].erase(obs);
    }
    //void unregisterObserver(Observer* obs);
    void sendEvent(string eventId, void* data) {
        Event newEvent(eventId, data);
        currentEvents.push_back(newEvent);
    }

    void ProcessEvents() {
        while(currentEvents.size()) {
            dispatchEvent(&currentEvents.front());
            currentEvents.pop_front();
            
        }
    }
    void Shutdown() {
        database.clear();
        currentEvents.clear();
    }
};

// Sample Observer
class Gordon : public Observer {
private:
    bool resting;
public:
    Gordon() {
        resting = false;
    }
    ~Gordon() {}
    bool Resting() const { return resting; }
    // Listeners must implement the HandleEvent(Event*) method
    void handleEvent(Event* event) {
        if (event != nullptr) {
        // Bank Robbery?
        if (event->getId() == "BANK_ROBBERY") {
            cout << "Parameter is " << (int)(size_t)event->getParam();
            cout << ". Police capture the robbers.\n";
        }
        // Joker is free?
        else if (event->getId() == "JOKER_FREE") {
            cout << "The Joker has escaped!Parameter is " << (int)(size_t)event->getParam();
            cout << ". Gordon lights the Bat Signal\n";
            EventSystem::Instance()->sendEvent("BAT_SIGNAL", (void*)3);
        }
        // Joker was captured?
        else if (event->getId() == "JOKER_CAPTURED") {
            cout << "Gordon shows up and takes the Joker into custody. Parameter is " << (int)(size_t)event->getParam() << '\n';
            resting = true;
        }
    }
    }
};

class Batman : public Observer {
private:
    bool resting;
public:
    Batman() {
        resting  = false;
    }
    ~Batman() {}
    bool Resting() const { return resting; }
    // Listeners must implement the HandleEvent(Event*) method
    void handleEvent(Event* event) {
        if (event != nullptr) {
        // The Bat Signal
        if (event->getId() == "BAT_SIGNAL") {
            cout << "Batman sees the Bat Signal. Parameter is " << (int)(size_t)event->getParam();
            cout << ". Batman captures the Joker\n";
            EventSystem::Instance()->sendEvent("JOKER_CAPTURED", (void*)4);
            resting = true;
        }
    }
    }
};

int main() {
    Gordon gordon;
    Batman batman;
    cout << "Starting!"<<endl;
    EventSystem::Instance()->registerObserver("BAT_SIGNAL", &batman);
    EventSystem::Instance()->registerObserver("JOKER_FREE", &gordon);
    EventSystem::Instance()->registerObserver("JOKER_CAPTURED", &gordon);
    EventSystem::Instance()->registerObserver("BANK_ROBBERY", &gordon);


    // Start this story with 2 events, Joker escapes, and the bank gets robbed
    EventSystem::Instance()->sendEvent("BANK_ROBBERY", (void*)1);
    EventSystem::Instance()->sendEvent("JOKER_FREE", (void*)2);
    //EventSystem::Instance()->ProcessEvents();
    // While batman and gordon are still out there fighting
    while (!batman.Resting() && !gordon.Resting()) {
        // Update and handle your events
        EventSystem::Instance()->ProcessEvents();
    }

    return 0;
}



