class Messager{
public:
    virtual void Login(string username, string password)=0;
    virtual void SendMessage(string message)=0;
    virtual void SendPicture(Image image)=0;

    virtual void PlaySound()=0;
    virtual void DrawShape()=0;
    virtual void WriteText()=0;
    virtual void Connect()=0;

    virtual ~Messager(){}
};


//平台实现

class PCMessagerBase : public Messager{
public:

    virtual void PlaySound(){
        //**********
    }
    virtual void DrawShape(){
        //**********
    }
    virtual void WriteText(){
        //**********
    }
    virtual void Connect(){
        //**********
    }
};

class MobileMessagerBase : public Messager{
public:

    virtual void PlaySound(){
        //==========
    }
    virtual void DrawShape(){
        //==========
    }
    virtual void WriteText(){
        //==========
    }
    virtual void Connect(){
        //==========
    }
};



//业务抽象

// PC端精简版
class PCMessagerLite : public PCMessagerBase {
public:

    virtual void Login(string username, string password){

        PCMessagerBase::Connect();
        //........
    }
    virtual void SendMessage(string message){

        PCMessagerBase::WriteText();
        //........
    }
    virtual void SendPicture(Image image){

        PCMessagerBase::DrawShape();
        //........
    }
};



// PC端豪华版
class PCMessagerPerfect : public PCMessagerBase {
public:

    virtual void Login(string username, string password){

        PCMessagerBase::PlaySound();
        //********
        PCMessagerBase::Connect();
        //........
    }
    virtual void SendMessage(string message){

        PCMessagerBase::PlaySound();
        //********
        PCMessagerBase::WriteText();
        //........
    }
    virtual void SendPicture(Image image){

        PCMessagerBase::PlaySound();
        //********
        PCMessagerBase::DrawShape();
        //........
    }
};


// 移动端精简版
class MobileMessagerLite : public MobileMessagerBase {
public:

    virtual void Login(string username, string password){

        MobileMessagerBase::Connect();
        //........
    }
    virtual void SendMessage(string message){

        MobileMessagerBase::WriteText();
        //........
    }
    virtual void SendPicture(Image image){

        MobileMessagerBase::DrawShape();
        //........
    }
};


// 移动端豪华版
class MobileMessagerPerfect : public MobileMessagerBase {
public:

    virtual void Login(string username, string password){

        MobileMessagerBase::PlaySound();
        //********
        MobileMessagerBase::Connect();
        //........
    }
    virtual void SendMessage(string message){

        MobileMessagerBase::PlaySound();
        //********
        MobileMessagerBase::WriteText();
        //........
    }
    virtual void SendPicture(Image image){

        MobileMessagerBase::PlaySound();
        //********
        MobileMessagerBase::DrawShape();
        //........
    }
};


void Process(){
        //编译时装配
        Messager *m =
            new MobileMessagerPerfect();
}


