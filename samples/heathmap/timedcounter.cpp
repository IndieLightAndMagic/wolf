#include "timedcounter.h"
#include <iostream>
HDC::TimedCounter::TimedCounter(QObject* parent):QObject(parent){

    ptimer = new QTimer(this);
    connect(ptimer, &QTimer::timeout, this, &HDC::TimedCounter::tick);
}
void HDC::TimedCounter::tick(){

    m_counter++;
    emit counter_ticked(m_counter);

}
void HDC::TimedCounter::setfrequency_hz(float hz){
    
    hz = 1 / hz;
    hz *= 1000;
    m_period_ms = static_cast<int>(hz);
    if (m_counter_state == CounterState::quieto){
    
        return;
    
    } else if (m_counter_state == CounterState::andante) {



    } 
}
void HDC::TimedCounter::setperiod(int ms){

    m_period_ms = ms;

}
void HDC::TimedCounter::start(int start_value){

    if (m_counter_state == CounterState::quieto){
        
        m_counter_state = CounterState::andante;
        m_counter       = start_value;
        ptimer->start(m_period_ms);
        return;

    } else if (m_counter_state == CounterState::andante){

        return;

    }
    assert(false);

}

void HDC::TimedCounter::pause(){

    if (m_counter_state == CounterState::quieto){
        
        return;
        
    } else if (m_counter_state == CounterState::andante){
        
        m_counter_state = CounterState::quieto;
        ptimer->stop();
        return;

    }
    assert(false);

}

void HDC::TimedCounter::unpause(){
    if (m_counter_state == CounterState::quieto){
        
        ptimer->start(m_period_ms);
        m_counter_state = CounterState::andante;
    
    } else if (m_counter_state == CounterState::andante){

        ptimer->stop();

    }
}

void HDC::TimedCounter::stop(){
    if (m_counter_state == CounterState::andante){
        ptimer->stop();
        m_counter = 0;
    }
}
void HDC::TimedCounter::setcountervalue(int countervalue){
    m_counter = countervalue - 1;
}
void HDC::TimedCounter::restart(){
    setcountervalue(0);
}








