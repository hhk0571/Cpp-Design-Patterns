
class House{
    //....
};

class HouseBuilder { //构建过程单独提取成一个抽象类
public:
    House* GetResult(){
        return pHouse;
    }
    virtual ~HouseBuilder(){}
protected:

    House* pHouse;
	virtual void BuildPart1()=0;
    virtual void BuildPart2()=0;
    virtual void BuildPart3()=0;
    virtual void BuildPart4()=0;
    virtual void BuildPart5()=0;

};

class StoneHouse: public House{

};

class StoneHouseBuilder: public HouseBuilder{ //具体构建类
protected:

    virtual void BuildPart1(){
        //pHouse->Part1 = ...;
    }
    virtual void BuildPart2(){

    }
    virtual void BuildPart3(){

    }
    virtual void BuildPart4(){

    }
    virtual void BuildPart5(){

    }

};

class HouseDirector{ //稳定
public:
    HouseBuilder* pHouseBuilder; // has-a reference

    HouseDirector(HouseBuilder* pHouseBuilder){ // 依赖注入
        this->pHouseBuilder=pHouseBuilder;
    }

    House* Construct(){
        pHouseBuilder->BuildPart1();

        for (int i = 0; i < 4; i++){
            pHouseBuilder->BuildPart2();
        }

        bool flag=pHouseBuilder->BuildPart3();

        if(flag){
            pHouseBuilder->BuildPart4();
        }

        pHouseBuilder->BuildPart5();

        return pHouseBuilder->GetResult();
    }
};






