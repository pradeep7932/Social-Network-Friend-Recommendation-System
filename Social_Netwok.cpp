#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <set>

using namespace std;

class SocialNetwork {
private:
    unordered_map<int, vector<int>> adjList;

public:
    void addFriendship(int person1, int person2) {
        adjList[person1].push_back(person2);
        adjList[person2].push_back(person1);
    }

    vector<int> recommendFriends(int person) {
        unordered_map<int, int> mutualFriends;
        set<int> directFriends(adjList[person].begin(), adjList[person].end());
        directFriends.insert(person);

        for (int friendID : adjList[person]) {
            for (int friendOfFriend : adjList[friendID]) {
                if (directFriends.find(friendOfFriend) == directFriends.end()) {
                    mutualFriends[friendOfFriend]++;
                }
            }
        }

        // Sort recommendations by the number of mutual friends
        priority_queue<pair<int, int>> pq;
        for (auto &entry : mutualFriends) {
            pq.push({entry.second, entry.first});
        }

        vector<int> recommendations;
        while (!pq.empty()) {
            recommendations.push_back(pq.top().second);
            pq.pop();
        }

        return recommendations;
    }
};

int main() {
    SocialNetwork sn;
    sn.addFriendship(1, 2);
    sn.addFriendship(1, 3);
    sn.addFriendship(2, 4);
    sn.addFriendship(3, 4);
    sn.addFriendship(4, 5);

    int person = 1;
    vector<int> recommendations = sn.recommendFriends(person);

    cout << "Friend recommendations for person " << person << ": ";
    for (int rec : recommendations) {
        cout << rec << " ";
    }
    return 0;
}