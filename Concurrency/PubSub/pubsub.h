#include  <functional> // for std::function
#include <vector>
#include <map>
#include <utility> 

using namespace std;

//class Subscriber;
//enum class Event {RED, GREEN, BLUE, ORANGE};

template <typename Event>
class PubSubService {
public:
template <typename Subscriber>
void registerObserver(const Event&& event, Subscriber&& subscriber ){
    subscribers_[event].push_back(std::forward<Subscriber>(subscriber));

}

void notify(const Event& event) const {
    for(auto const& subs : subscribers_.at(event)){
        subs();
    }
}

private:
  std::map<Event, std::vector<std::function<void()>>> subscribers_;
};