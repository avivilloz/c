/*****************************************************************************
Title: requests_manager templates implementation - Infinity Labs R&D 
Group: RD91
Description: requests_manager templates implementation
******************************************************************************/

#include "requests_manager.hpp" // api

template<class ActionT>
void RequestsManager::HandleRequest(
    u_int64_t from, const RequestsManager::RequestType &rt
)
{
    RequestKey_t key(from, rt);

    CreateKamikaze<ActionT>(
        key, DataRepository::StorageType(DataRepository::MAIN), s_startDelay);
    CreateKamikaze<ActionT>(
        key, DataRepository::StorageType(DataRepository::BACKUP), s_startDelay);
}

template<class ActionT>
void RequestsManager::CreateKamikaze(
    const RequestKey_t &key, const DataRepository::StorageType &st, const std::size_t &delay
)
{
    boost::shared_ptr<RequestArgs> args(GetArgs(key));
    boost::shared_ptr<Action> action(new ActionT(args->m_buf, args->m_from, st));
    new Kamikaze(action, delay);
}

template<class ActionT>
void RequestsManager::Callback(
    u_int64_t from, 
    const RequestType &rt, 
    const DataRepository::StorageType &st, 
    bool status
)
{
    if (0 == status)
    {
        HandleSuccess(from, rt, st, status);
    }
    else
    {
        HandleFailure<ActionT>(from, rt, st, status);
    }
}

template<class ActionT>
void RequestsManager::HandleFailure(
    u_int64_t from, 
    const RequestType &rt, 
    const DataRepository::StorageType &st, 
    bool status
)
{
    Handleton<ilrd::RequestsManager> requestsManager;

    RequestKey_t requestKey(from, rt);
    SubrequestKey_t subrequestKey(from, rt, st);
    SubrequestKey_t otherSubrequestKey(from, rt, DataRepository::StorageType(!st));

    std::cout << "handling failure" << std::endl;
    if (!requestsManager->ReachedAttemptsLimit(subrequestKey))
    {
        requestsManager->CreateKamikaze<ActionT>(
            requestKey, st, s_rescheduleDelay);
        requestsManager->IncrementAttempts(subrequestKey);
    }
    else
    {
        requestsManager->EraseSubrequest(subrequestKey);

        if (!requestsManager->SubrequestExists(otherSubrequestKey))
        {
            requestsManager->Reply(requestKey, status);
            requestsManager->EraseRequest(requestKey);
        }
    }
}
