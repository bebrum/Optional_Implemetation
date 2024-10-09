#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include<istream>

using namespace std;
template<class T>
class optional
{
private:
    T* val;
public:
    optional() : val(nullptr) {}
    optional(const T& v) : val(new T(v)) {}
    ~optional() { val = nullptr; delete val; };
    T value()
    {
        return *val;
    }
    T* operator ->() {
        return val;
    }
    T& operator *() {
        return *val;
    }
    optional& operator = (optional v2)
    {
        std::swap(val, v2.val);
        return *this;
    }
};

class User{
private:
    string login;
    string firstName;
    optional<string> familyName;
    optional<string> patronName;
public:
    string getlogin()
    {
        return login;
    }
    User(string l, string fn, optional<string> fm, optional<string> pat) {
        login = l;
        firstName = fn;
        familyName = fm;
        patronName = pat;
    }
};

class UserBase {

private:
    
    vector<User> users;
    
    UserBase() {};
public:
    static UserBase* base;
    
    UserBase(UserBase& other) = delete;
    static UserBase* GetInstance();
    vector<User> getUsers()
    {
        return users;
    }
    User find(int id)
    {
        return users[id];
    }
    void Create(User item)
    {
        users.push_back(item);
    }
    void Delete(int id)
    {
        users.erase(users.begin() + id);;
    }
    void update(User item)
    {
        for (User u : users)
        {
            if (u.getlogin() == item.getlogin())
                u = item;
        }
    }
    void save()
    {
        return;
    }

};

UserBase* UserBase::base = nullptr;;

UserBase* UserBase::GetInstance()
{
   
    if (base == nullptr) {
        base = new UserBase;
    }
    return base;
}

class IRepository
{
    virtual vector<User> getUsers() = 0;
    virtual User GetUser(int id) = 0;
   virtual void Create(User item) = 0;
   virtual void Update(User item)=0;
   virtual void Delete(int id)=0;
   virtual void Save()=0;
};


class Repository : IRepository
{
private:
    UserBase* base = UserBase::GetInstance();
public:

    vector<User> getUsers() override
    {
        return base->getUsers();
    }

    User GetUser(int id) override
    {
        return base->find(id);
    }
    void Create(User item) override
    {
        base->Create(item);
    }
    void Update(User item) override
    {
        base->update(item);
    }
    void Delete(int id) override
    {
        base->Delete(id);
    }

    void Save() override { return; };
};

int main()
{
    optional<std::string> o;
    std::string s = "some string";
    optional<std::string> oo(s);
    o = oo;
    s.~basic_string();
    o.~optional();
    std::cout << *oo;


    UserBase* singleton = UserBase::GetInstance();
    User us("user1", "user1", optional<string>(string("user1")), optional<string>(string("userov1")));
    User nextUs("user2", "user2", optional<string>(string("user2")), optional<string>(string("userov2")));
    Repository u;
    u.Create(us);
    Repository v;
    v.Create(nextUs);
    vector<User> users = singleton->getUsers();
    u.Delete(0);
    u.GetUser(0);
    
}