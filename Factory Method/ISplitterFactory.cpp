
//产品抽象类
class ISplitter{
public:
    virtual void split()=0;
    virtual ~ISplitter(){}
};


//产品工厂基类
class SplitterFactory{
public:
    virtual ISplitter* CreateSplitter()=0;
    virtual ~SplitterFactory(){}
};
