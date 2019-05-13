#ifndef __TIMED_COUNTER__
#define __TIMED_COUNTER__

#include <QTimer>
#include <QObject>

namespace HDC{
    class TimedCounter : public QObject {

        Q_OBJECT
    public:
        enum class CounterState{
            quieto,
            andante
        };

        TimedCounter(QObject* parent = 0);
        ~TimedCounter(){
            if (ptimer){
                delete ptimer;
                ptimer = nullptr;
            }
        }
    //if andante: changing freq or period will take effect after the next tick
    //if quieto:  changing freq or period will take effect when state is andante   
    void setfrequency_hz(float hz);
    void setperiod(int ms);


    void start(int start_value = 0); //quieto: starts counting with established freq / period, counter is set to start_value 
                                     //(quieto->andante) andante:no effect
    void pause(); //andante: pauses the counter andante->quieto 
                  //quieto: noeffect
    void unpause(); //quieto:starts the counter andante->quieto 
                  //andante: noeffect
    void stop(); //andante::stops the count and set it to 0
                //quieto: no effect
    void restart(); //set the counter to 0 (on next tick). Won't affect state.
    void setcountervalue(int countervalue); //set the counter to countervalue (on next tick).

    signals:
    void counter_ticked(int);//cnt+1
    void counter_wrapped(); //0x7ffffffff + 1
private:
    
    TimedCounter::CounterState m_counter_state{CounterState::quieto};
    int m_period_ms{1000};
    void tick();
    QTimer* ptimer{nullptr};
    int m_counter{0};


};


}

#endif