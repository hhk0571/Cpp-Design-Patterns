
class House {
public:
    void init(){ // 不能用构造函数, 因为C++构造函数是静态绑定, 无法调用子类的虚函数.
        this->BuildPart1();

        for (int i = 0; i < 4; i++){
            this->BuildPart2();
        }

        bool flag = this->BuildPart3();

        if(flag){
            this->BuildPart4();
        }

        this->BuildPart5();
    }
    virtual ~House(){}
protected:
	virtual void BuildPart1()=0;
    virtual void BuildPart2()=0;
    virtual void BuildPart3()=0;
    virtual void BuildPart4()=0;
    virtual void BuildPart5()=0;

};

//这里用的是 template method 模式
class StoneHouse: public House {
protected:
	virtual void BuildPart1(){ ... }
    virtual void BuildPart2(){ ... }
    virtual void BuildPart3(){ ... }
    virtual void BuildPart4(){ ... }
    virtual void BuildPart5(){ ... }
};

int main(int argc, char const *argv[])
{
    House *pHouse = new StoneHouse();
    pHouse->init();
    return 0;
}
