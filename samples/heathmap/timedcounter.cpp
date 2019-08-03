#include "timedcounter.h"
#include <iostream>
QQE::TimedCounter::TimedCounter(QObject* parent):QObject(parent){

    ptimer = new QTimer(this);
    connect(ptimer, &QTimer::timeout, this, &QQE::TimedCounter::tick);
}
void QQE::TimedCounter::tick(){

    m_counter++;
    emit counter_ticked(m_counter);

}
void QQE::TimedCounter::setfrequency_hz(float hz){
    
    hz = 1 / hz;
    hz *= 1000;
    m_period_ms = static_cast<int>(hz);
    if (m_counter_state == CounterState::quieto){
    
        return;
    
    } else if (m_counter_state == CounterState::andante) {



    } 
}
void QQE::TimedCounter::setperiod(int ms){

    m_period_ms = ms;

}
void QQE::TimedCounter::start(int start_value){

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

void QQE::TimedCounter::pause(){

    if (m_counter_state == CounterState::quieto){
        
        return;
        
    } else if (m_counter_state == CounterState::andante){
        
        m_counter_state = CounterState::quieto;
        ptimer->stop();
        return;

    }
    assert(false);

}

void QQE::TimedCounter::unpause(){
    if (m_counter_state == CounterState::quieto){
        
        ptimer->start(m_period_ms);
        m_counter_state = CounterState::andante;
    
    } else if (m_counter_state == CounterState::andante){

        ptimer->stop();

    }
}

void QQE::TimedCounter::stop(){
    if (m_counter_state == CounterState::andante){
        ptimer->stop();
        m_counter = 0;
    }
}
void QQE::TimedCounter::setcountervalue(int countervalue){
    m_counter = countervalue - 1;
}
void QQE::TimedCounter::restart(){
    setcountervalue(0);
}








