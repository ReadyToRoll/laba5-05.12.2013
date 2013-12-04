#include <iostream>
#include <vector>

using namespace std;

template <class Templ>
class SharedPtr
{
private:
    Templ* ptr;
    int* count;
    void deleteData()
    {
        if (--*count == 0)
        {
            delete count;
            delete ptr;
        }
    }
public:
    SharedPtr():ptr(0), count(new int(0)){}
    explicit SharedPtr(Templ* p=0): ptr(p), count(new int(1)) {}
    SharedPtr(const SharedPtr<Templ>& p) throw(): ptr(p.ptr), count(p.count){++*count;}
    ~SharedPtr()
    {
        deleteData();
    }
    Templ& operator*(){return *ptr;}
    Templ* operator->(){return ptr;}
    SharedPtr<Templ>& operator= (const SharedPtr<Templ>& p) throw()
    {
        if(this!=&p)
        {
            deleteData();
            ptr=p.ptr;
            count=p.count;
            ++*count;
        }
        return *this;
    }
};

class Transporter
{
private:
    double cost;
    int speed;
public:
    double getCost()
    {
        return cost;
    }
    int getSpeed()
    {
        return speed;
    }
    void show()
    {
        cout<<"Cost: "<<cost<<endl<<"Speed: "<<speed<<endl;
    }
    Transporter(double a,int b):cost(a),speed(b) {}
    /*~Transporter()
       {
           cost=NULL;
           speed=NULL;
       }*/
};

class Airplane:public Transporter
{
public:
    Airplane(double a, int b):Transporter(a,b) {}
    //  ~Airplane():Transporter(){}
    int check_distance_airplane(int a)
    {
        if(a>500)
            return 1;
        else
        {
            if(a>200)
            {
                return 0;
            }
            else
                return -1;
        }
        return -1;
    }
};

class Bus:public Transporter
{
public:
    Bus(double a, int b):Transporter(a,b) {}
    //  ~Bus():Transporter(){}
    int check_time_bus(int a)
    {
        int temp=a,i;
        for(i=0; temp>12; i++)
            temp=temp-12;
        a=12*i;
        return a;
    }
};

class Train:public Transporter
{
public:
    Train(double a, int b):Transporter(a,b) {}
    //  ~Train():Transporter(){}
};

class destErr:public exception
{
    /* ... */
};
class nonIntVar:public exception
{
    /* ... */
};


int setDestination()
{

    int w=-1;
    cout<<"set your destination:"<<endl;
    cout<<" 1 - Minsk"<<endl;
    cout<<" 2 - Brest"<<endl;
    cout<<" 3 - Gomel"<<endl;
    cout<<" 4 - Mogilev"<<endl;
    cout<<" 5 - Valencia"<<endl;
    cout<<" 6 - Bari"<<endl<<endl;
    cin>>w;
    if(!cin)
        throw nonIntVar();
    if(w<1||w>6)
        throw destErr();
    else
        return w;
}

int main()
{
    int distance,w,ch;
    int minskBrest=354, minskGomel=298, minskMogilev=198, minskValencia=3279 ,minskBari=2645, minskMinsk=0;
    int brestBrest=0, brestGomel=639, brestMogilev=600, brestValencia=2953 ,brestBari=2288, brestMinsk=354;
    int gomelBrest=639, gomelGomel=0, gomelMogilev=175, gomelValencia=3537 ,gomelBari=2872, gomelMinsk=298;
    int mogilevBrest=600, mogilevGomel=175, mogilevMogilev=0, mogilevValencia=3461 ,mogilevBari=2828, mogilevMinsk=198;
    int valenciaBrest=2953, valenciaGomel=3537, valenciaMogilev=3461, valenciaValencia=0 ,valenciaBari=2145, valenciaMinsk=3279;
    int bariBrest=2288, bariGomel=2872, bariMogilev=2828, bariValencia=2145 ,bariBari=0, bariMinsk=2645;
    double resultTimeAir, resultTimeBus, resultTimeTrain;
    double resultCostAir, resultCostBus, resultCostTrain;

    SharedPtr<Airplane> minskAir(new Airplane(0.5,750));
    SharedPtr<Bus> minskBus (new Bus(0.2,110));
    SharedPtr<Train> minskTrain (new Train(0.3,90));

    SharedPtr<Airplane> valenciaAir (new Airplane(0.4,750));
    SharedPtr<Bus> valenciaBus (new Bus(0.5,110));
    SharedPtr<Train> valenciaTrain (new Train(0.3,90));

    SharedPtr<Airplane> brestAir (new Airplane(0,750));
    SharedPtr<Bus> brestBus (new Bus(0.2,110));
    SharedPtr<Train> brestTrain (new Train(0.3,90));

    SharedPtr<Airplane> gomelAir (new Airplane(0,750));
    SharedPtr<Bus> gomelBus (new Bus(0.2,110));
    SharedPtr<Train> gomelTrain (new Train(0.3,90));

    SharedPtr<Airplane> mogilevAir (new Airplane(0,750));
    SharedPtr<Bus> mogilevBus (new Bus(0.2,110));
    SharedPtr<Train> mogilevTrain (new Train(0.3,90));

    SharedPtr<Airplane> bariAir (new Airplane(0.4,750));
    SharedPtr<Bus> bariBus (new Bus(0.5,110));
    SharedPtr<Train> bariTrain (new Train(0.4,90));

    vector <Airplane> air;
    air.push_back(*minskAir);
    air.push_back(*brestAir);
    air.push_back(*gomelAir);
    air.push_back(*mogilevAir);
    air.push_back(*valenciaAir);
    air.push_back(*bariAir);

    cout<<"Container #1: "<<endl;
    vector<Airplane>::iterator cur;
    for (cur=air.begin(); cur<air.end(); cur++)
        cur->show();
    cout<<endl<<endl;

    vector <Bus> bus;
    bus.push_back(*minskBus);
    bus.push_back(*brestBus);
    bus.push_back(*gomelBus);
    bus.push_back(*mogilevBus);
    bus.push_back(*valenciaBus);
    bus.push_back(*bariBus);

    cout<<"Container #2: "<<endl;
    vector<Bus>::iterator cur1;
    for (cur1=bus.begin(); cur1<bus.end(); cur1++)
        cur1->show();
    cout<<endl<<endl;

    vector <Train> train;
    train.push_back(*minskTrain);
    train.push_back(*brestTrain);
    train.push_back(*gomelTrain);
    train.push_back(*mogilevTrain);
    train.push_back(*valenciaTrain);
    train.push_back(*bariTrain);

    cout<<"Container #3: "<<endl;
    vector<Train>::iterator cur2;
    for (cur2=train.begin(); cur2<train.end(); cur2++)
        cur2->show();
    cout<<endl<<endl;
    do
    {
        cout<<"set your location:"<<endl;
        cout<<" 1 - Minsk"<<endl;
        cout<<" 2 - Brest"<<endl;
        cout<<" 3 - Gomel"<<endl;
        cout<<" 4 - Mogilev"<<endl;
        cout<<" 5 - Valencia"<<endl;
        cout<<" 6 - Bari"<<endl<<endl;
        cin>>w;
        if(!cin)
            throw nonIntVar();
        switch(w)
        {
        case 1:
            ch=setDestination();
            if(ch==1)
                distance=minskMinsk;
            if(ch==2)
                distance=minskBrest;
            if(ch==3)
                distance=minskGomel;
            if(ch==4)
                distance=minskMogilev;
            if(ch==5)
                distance=minskValencia;
            if(ch==6)
                distance=minskBari;
            w=31;
            break;
        case 2:
        {
            ch=setDestination();
            if(ch==1)
                distance=brestMinsk;
            if(ch==2)
                distance=brestBrest;
            if(ch==3)
                distance=brestGomel;
            if(ch==4)
                distance=brestMogilev;
            if(ch==5)
                distance=brestValencia;
            if(ch==6)
                distance=brestBari;
            w=32;
            break;
        }
        case 3:
        {
            ch=setDestination();
            if(ch==1)
                distance=gomelMinsk;
            if(ch==2)
                distance=gomelBrest;
            if(ch==3)
                distance=gomelGomel;
            if(ch==4)
                distance=gomelMogilev;
            if(ch==5)
                distance=gomelValencia;
            if(ch==6)
                distance=gomelBari;
            w=33;
            break;
        }
        case 4:
        {
            ch=setDestination();
            if(ch==1)
                distance=mogilevMinsk;
            if(ch==2)
                distance=mogilevBrest;
            if(ch==3)
                distance=mogilevGomel;
            if(ch==4)
                distance=mogilevMogilev;
            if(ch==5)
                distance=mogilevValencia;
            if(ch==6)
                distance=mogilevBari;
            w=34;
            break;
        }
        case 5:
        {
            ch=setDestination();
            if(ch==1)
                distance=valenciaMinsk;
            if(ch==2)
                distance=valenciaBrest;
            if(ch==3)
                distance=valenciaGomel;
            if(ch==4)
                distance=valenciaMogilev;
            if(ch==5)
                distance=valenciaValencia;
            if(ch==6)
                distance=valenciaBari;
            w=35;
            break;
        }
        case 6:
        {
            ch=setDestination();
            if(ch==1)
                distance=bariMinsk;
            if(ch==2)
                distance=bariBrest;
            if(ch==3)
                distance=bariGomel;
            if(ch==4)
                distance=bariMogilev;
            if(ch==5)
                distance=bariValencia;
            if(ch==6)
                distance=bariBari;
            w=36;
            break;
        }
        }
    }
    while(w<30);

    if(air[ch-1].check_distance_airplane(distance)==1)
        resultTimeAir=distance/air[ch-1].getSpeed();
    else if(air[ch-1].check_distance_airplane(distance)==-1)
        resultTimeAir=-1;
    if(ch>=2&&ch<=4)
        resultCostAir=0;
    else if(air[ch-1].check_distance_airplane(distance)==0)
        resultCostAir=distance*air[ch-1].getCost()*1.5;
    else
        resultCostAir=distance*air[ch-1].getCost();
    resultTimeBus=distance/bus[ch-1].getSpeed()+bus[ch-1].check_time_bus(distance/bus[ch-1].getSpeed());
    resultCostBus=distance*bus[ch-1].getCost();
    resultTimeTrain=distance/train[ch-1].getSpeed();
    resultCostTrain=distance*train[ch-1].getCost();

    cout<<"Table for "<<distance<<" km(s):"<<endl;
    if(resultCostAir!=0)
        cout<<"Air:   "<<resultTimeAir<<"hrs  "<<resultCostAir<<"$"<<endl;
    else
        cout<<"Air:   "<<"no possible"<<endl;
    cout<<"Bus:   "<<resultTimeBus<<"hrs  "<<resultCostBus<<"$"<<endl;
    cout<<"Train: "<<resultTimeTrain<<"hrs  "<<resultCostTrain<<"$"<<endl;
    return 0;
}
