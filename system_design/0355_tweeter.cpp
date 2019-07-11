// operator in cmp should be declared public

class Tweet {
public:
    Tweet(int tweetId, int timestamp) {
        this->tweetId = tweetId;
        this->timestamp = timestamp;
        next = nullptr;
    }
    friend class User;
    friend class Twitter;
private:
    int tweetId;
    int timestamp;
    Tweet *next;
};

class User {
public:
    User(int userId) {
        this->userId = userId;
        tweetsHead = nullptr;
        followees.insert(userId);//first follow himself
    }
    ~User(){
        Tweet* tmp = tweetsHead;
        while (tweetsHead) {
            tmp = tweetsHead->next;
            delete tweetsHead;
            tweetsHead = tmp;
        }
    }
    void post(int tweetId, int timestamp) {
        Tweet *t = new Tweet(tweetId, timestamp);
        t->next = tweetsHead;
        tweetsHead = t;
    }
    void follow(int followeeId) {
        followees.insert(followeeId);
    }
    void unfollow(int followeeId) {
        if (followees.find(followeeId) != followees.end() && followeeId != userId) {
            followees.erase(followeeId);
        }
    }
    friend class Twitter;
private:
    int userId;
    Tweet *tweetsHead;
    unordered_set<int> followees;
};



class Twitter {
public:
    /** Initialize your data structure here. */
    Twitter() {

    }
    ~Twitter() {
        for (pair<int, User*> p : userMap) {
            delete p.second;
        }
    }
    /** Compose a new tweet. */
    void postTweet(int userId, int tweetId) {
        if (userMap.find(userId) == userMap.end()) {
            User *newUser = new User(userId);
            userMap[userId] = newUser;
        }
        userMap[userId]->post(tweetId, timestamp);
        timestamp++;
    }
    //comparator used in priority_queue
    class Comparator {
    public:
        bool operator() (const Tweet* tp1, const Tweet* tp2) {
            return tp1->timestamp < tp2->timestamp;
        }
    };
    /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
    vector<int> getNewsFeed(int userId) {
        vector<int> res;
        if (userMap.find(userId) == userMap.end()) return res;
        priority_queue<Tweet*, vector<Tweet*>, Comparator> p;
        for (int u : userMap[userId]->followees) {//construct priority queue
            if (userMap[u]->tweetsHead != nullptr)
                p.push(userMap[u]->tweetsHead);
        }
        for (int i = 0; i < 10 && !p.empty(); ++i) {
            Tweet* t = p.top();
            res.push_back(t->tweetId);
            p.pop();
            if (t->next) p.push(t->next);
        }
        return res;
    }

    /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
    void follow(int followerId, int followeeId) {
        if (userMap.find(followerId) == userMap.end()) {
            User *u = new User(followerId);
            userMap[followerId] = u;
        }
        if (userMap.find(followeeId) == userMap.end()) {
            User *u = new User(followeeId);
            userMap[followeeId] = u;
        }
        userMap[followerId]->follow(followeeId);
    }

    /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
    void unfollow(int followerId, int followeeId) {
        if (userMap.find(followerId) == userMap.end() || userMap.find(followeeId) == userMap.end()) {
            return;
        }
        userMap[followerId]->unfollow(followeeId);
    }
private:
    int timestamp = 0;
    unordered_map<int, User*> userMap;
};
