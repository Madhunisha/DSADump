#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <list>

using namespace std;
struct Event {
    int occurrences, businessId;
    string eventType;

    Event (string et, int occ, int bizId) {
        eventType = et;
        occurrences = occ;

        businessId = bizId;
    }
};
unordered_map<string,pair<int,int>> avgs;
// split: receives a char delimiter; returns a vector of strings
vector<string> split(const string& work, char delim=' ') {
    vector<string> flds;

    string buf = "";
    int i = 0;
    while (i < work.length()) {
        if (work[i] != delim)
            buf += work[i];
        else {
            flds.push_back(buf);
            buf = "";
        }
        i++;
    }
    if (!buf.empty())
        flds.push_back(buf);
    return flds;
}

//COMPLETE ME
vector<int> findActiveBusinesses(const vector<Event>& eventTypes) {
    unordered_map<int,vector<pair<string,int>>> biz;
    unordered_map<string,pair<float,int>> evAvg;
    vector<int> result;
    for(auto const& val : eventTypes) {
        if(val.occurrences > 0) {
            biz[val.businessId].emplace_back(val.eventType, val.occurrences);
            evAvg[val.eventType].first+=val.occurrences;
            evAvg[val.eventType].second++;
        }
    }
    for(auto &val : evAvg) {
        val.second.first/=val.second.second;
    }
    for(auto const& val : biz) {
        if(val.second.size() < 2) continue;
        int cnt = 0;
        for(auto const& ev : val.second) {
            if(ev.second >= evAvg[ev.first].first)
                cnt++;
            if(cnt >= 2) {
                result.push_back(val.first);
                break;
            }
        }
    }
    return result;
}


int main() {
    string input;
    vector<Event> eventTypes;

    /*while(getline(cin, input)) {

        vector<string> fields = split(input);
        eventTypes.push_back(Event(fields[0], stoi(fields[1]), stoi(fields[2])));
    }*/
    eventTypes.push_back(Event("ads", 6, 1));
    eventTypes.push_back(Event("views", 2, 2));
    eventTypes.push_back(Event("photos", 4, 3));
    eventTypes.push_back(Event("photos", 4, 2));
    eventTypes.push_back(Event("photos", 5, 1));
    eventTypes.push_back(Event("ads", 20, 4));
    eventTypes.push_back(Event("photos", 3, 4));
    eventTypes.push_back(Event("views", 2, 3));

    vector<int> activeBusinesses = findActiveBusinesses(eventTypes);
    for (int bizId : activeBusinesses){
        cout << bizId << endl;
    }

    return 0;
}