/*******************************************************************************
Title: kamikaze - Infinity Labs R&D 
Group: OL91
Description: kamikaze API
*******************************************************************************/

#ifndef ILRD_RD91_KAMIKAZE_HPP
#define ILRD_RD91_KAMIKAZE_HPP

#include <boost/shared_ptr.hpp> // boost::shared_ptr

#include "actions_api.hpp" // Action
#include "scheduler.hpp" // SchedulerTask

namespace ilrd
{

class Kamikaze
{
public:
    Kamikaze(boost::shared_ptr<Action> action_, std::size_t delay);

private:
    class Task : public Scheduler::Task
    {
    public:
        Task(Kamikaze &k_);
        void Execute();

    private:
        Kamikaze &m_k;
    };

    boost::shared_ptr<Action> m_action;

    void PerformAction();
};

} // end of namespace ilrd

#endif // ILRD_RD91_KAMIKAZE_HPP
