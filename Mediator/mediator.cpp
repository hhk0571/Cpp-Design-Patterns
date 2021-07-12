#include <iostream>
#include <memory>
#include <type_traits>
#include <vector>

using namespace std;

/*
租客(Tenant)想要通过房屋中介（Agency）租房，需要去中介处了解房东（Landlord）的信息（姓名，价格，地址和联系方式）；
房东们（Landlord）需要在中介处注册自己的房源，同时也可以从中介处了解租客（Tenant）的信息（姓名）。

$ cd "d:\HHK\Ref_Book\01_设计模式\CPP设计模式\Cpp-Design-Patterns\Mediator" && g++ -g -Wall -std=c++17 -fexec-charset=GBK mediator.cpp -o mediator  && ./mediator
租客'张三'询问房东信息
房东姓名: 刘备, 房租: 1350, 地址: 成都市双流区, 电话: 1351025
房东姓名: 关羽, 房租: 1500, 地址: 成都市武侯区, 电话: 1378390
房东姓名: 张飞, 房租: 1000, 地址: 成都市龙泉驿, 电话: 1881166


房东'刘备'查看租客信息:
租客姓名: 张三
租客姓名: 李四
租客姓名: 王五
租客姓名: 赵六


*/

enum class PersonType : uint8_t
{
    NOT_DEFINED,
    LANDLORD,
    TENANT
};

template<typename E>
constexpr auto
toUType(E enumerator) noexcept
{
    return static_cast<std::underlying_type_t<E>>(enumerator);
}

class Mediator;

class Colleague : public std::enable_shared_from_this<Colleague>
{
  public:
    Colleague(string name = "N.N.")
      : m_name{ name }
    {}
    ~Colleague() = default;
    void setMediator(shared_ptr<Mediator> mediator) { m_mediator = mediator; }
    shared_ptr<Mediator> getMediator() { return m_mediator; }
    PersonType getPersonType() { return m_personType; }

    virtual void ask() = 0;
    virtual void answer() = 0;

  protected:
    string m_name;
    shared_ptr<Mediator> m_mediator{ nullptr };
    PersonType m_personType;
};

class Mediator : public std::enable_shared_from_this<Mediator>
{
  public:
    Mediator() = default;
    ~Mediator() = default;
    virtual void doAction(shared_ptr<Colleague>) = 0;
    virtual void registerMethod(shared_ptr<Colleague>) = 0;
};

class Agency : public Mediator
{
  public:
    Agency() {}
    ~Agency() {}

    void registerMethod(shared_ptr<Colleague> colleague) override
    {
        switch (colleague->getPersonType()) {
            case PersonType::LANDLORD:
                landlords.push_back(colleague);
                colleague->setMediator(shared_from_this());
                break;
            case PersonType::TENANT:
                tenants.push_back(colleague);
                colleague->setMediator(shared_from_this());
                break;
            default:
                cout << __FUNCTION__ << ":wrong person type: "
                     << toUType(colleague->getPersonType()) << endl;
        }
    }

    void doAction(shared_ptr<Colleague> colleague) override
    {
        switch (colleague->getPersonType()) {
            case PersonType::LANDLORD:
                for (const auto& elem : tenants) {
                    elem->answer();
                }
                break;
            case PersonType::TENANT:
                for (const auto& elem : landlords) {
                    elem->answer();
                }
                break;
            default:
                cout << __FUNCTION__ << ":wrong person type: "
                     << toUType(colleague->getPersonType()) << endl;
        }
    }

  private:
    vector<shared_ptr<Colleague>> landlords;
    vector<shared_ptr<Colleague>> tenants;
};

class Landlord : public Colleague
{
  public:
    Landlord(string name = "N.N.",
             int price = 0,
             string address = "none",
             string phone = "none")
      : Colleague(name)
      , m_price{ price }
      , m_address{ address }
      , m_phone{ phone }
    {
        m_personType = PersonType::LANDLORD;
    }

    ~Landlord() {}

    virtual void ask()
    {
        cout << "房东'" << m_name << "'查看租客信息:" << endl;
        m_mediator->doAction(shared_from_this());
    }

    virtual void answer() override
    {
        cout << "房东姓名: " << m_name << ", 房租: " << m_price
             << ", 地址: " << m_address << ", 电话: " << m_phone << endl;
    }

  private:
    int m_price;
    string m_address;
    string m_phone;
};

class Tenant : public Colleague
{
  public:
    Tenant(string name = "N.N.")
      : Colleague(name)
    {
        m_personType = PersonType::TENANT;
    }

    ~Tenant() {}

    virtual void ask() override
    {
        cout << "租客'" << m_name << "'询问房东信息\n";
        m_mediator->doAction(shared_from_this());
    }

    virtual void answer() { cout << "租客姓名: " << m_name << endl; }
};

int main(int argc, char const* argv[])
{
    // 创建中介
    shared_ptr<Mediator> mediator = make_shared<Agency>();

    // 创建房东
    shared_ptr<Colleague> landlord1 = make_shared<Landlord>("刘备", 1350, "成都市双流区", "1351025");
    shared_ptr<Colleague> landlord2 = make_shared<Landlord>("关羽", 1500, "成都市武侯区", "1378390");
    shared_ptr<Colleague> landlord3 = make_shared<Landlord>("张飞", 1000, "成都市龙泉驿", "1881166");

    // 房东在中介登记房源信息
    mediator->registerMethod(landlord1);
    mediator->registerMethod(landlord2);
    mediator->registerMethod(landlord3);

    // 创建租客
    shared_ptr<Colleague> tenant1 = make_shared<Tenant>("张三");
    shared_ptr<Colleague> tenant2 = make_shared<Tenant>("李四");
    shared_ptr<Colleague> tenant3 = make_shared<Tenant>("王五");
    shared_ptr<Colleague> tenant4 = make_shared<Tenant>("赵六");

    // 租客在中介登记求租信息
    mediator->registerMethod(tenant1);
    mediator->registerMethod(tenant2);
    mediator->registerMethod(tenant3);
    mediator->registerMethod(tenant4);

    tenant1->ask();
    cout << "\n\n";
    landlord1->ask();

    return 0;
}
