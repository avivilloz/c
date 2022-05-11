/*****************************************************************************
Title: kamikaze - Infinity Labs R&D 
Group: OL91
Description: kamikaze API
******************************************************************************/

#include <boost/shared_ptr.hpp> // boost::shared_ptr<>

#include "kamikaze.hpp" // api 
#include "handleton.hpp" // Handleton
#include "scheduler.hpp" // Scheduler, SchedulerTask
#include "actions_api.hpp" // Action

namespace ilrd
{

Kamikaze::Task::Task(Kamikaze &k_) 
   : m_k(k_)
{}

void Kamikaze::Task::Execute()
{
   m_k.PerformAction();
}

Kamikaze::Kamikaze(boost::shared_ptr<Action> action_, std::size_t delay)
    : m_action(action_)
{
   boost::shared_ptr<Scheduler::Task> task(
      new Task(*this));

   Handleton<Scheduler> scheduler;
   scheduler->AddTask(task, delay);
}

void Kamikaze::PerformAction()
{
   (*m_action)();
   delete this;
}

}

/*****************************************************************************/
