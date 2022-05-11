/*****************************************************************************
Title: requests_manager - Infinity Labs R&D 
Group: RD91
Description: requests_manager API
******************************************************************************/

#include <boost/shared_ptr.hpp> // boost::shared_ptr
#include <sys/types.h> // u_int64_t
#include <stdlib.h> // atoi

#include "requests_manager.hpp" // api
#include "handleton.hpp" // Handleton
#include "data_repository.hpp" // DataRepository, DataRepository::StorageType
#include "actions_api.hpp" // Action::Callback, Callback
#include "runtime_config.hpp" // RuntimeConfig
#include "requests_api.hpp" // RequestHandler

#define START_DELAY 0

namespace ilrd
{

const std::size_t RequestsManager::s_startDelay = START_DELAY; 

const std::size_t RequestsManager::s_rescheduleDelay =
    RequestsManager::GetRescheduleDelay();

const std::size_t RequestsManager::s_attemptsLimit = 
    RequestsManager::GetAttemptsLimit();

RequestsManager::RequestsManager()
    : m_requestsMap(), m_attemptsMap()
{}

void RequestsManager::Write(boost::shared_ptr<RequestHandler> request)
{
    u_int64_t from = GetArgs(request)->m_from;
    RequestType rt(WRITE);
    Register(request, from, rt);
    HandleRequest<WriteAction>(from, rt);
}

void RequestsManager::Read(boost::shared_ptr<RequestHandler> request)
{
    u_int64_t from = GetArgs(request)->m_from;
    RequestType rt(READ);
    Register(request, from, rt);
    HandleRequest<ReadAction>(from, rt);
}

std::size_t RequestsManager::GetRescheduleDelay()
{
    Handleton<RuntimeConfig> config;
    return atoi(config->GetValue(RESCHEDULE_DELAY).c_str());
}

std::size_t RequestsManager::GetAttemptsLimit()
{
    Handleton<RuntimeConfig> config;
    return atoi(config->GetValue(ATTEMPTS_LIMIT).c_str());
}

void RequestsManager::Register(
    boost::shared_ptr<RequestHandler> request,
    u_int64_t from, const RequestsManager::RequestType &rt
)
{
    RequestKey_t key(from, rt);

    m_requestsMap[key] = request;

    m_attemptsMap[SubrequestKey_t(
        from, rt, DataRepository::StorageType(DataRepository::MAIN))] = 0; 
    m_attemptsMap[SubrequestKey_t(
        from, rt, DataRepository::StorageType(DataRepository::BACKUP))] = 0; 

    Handleton<DataRepository> dr;
    dr->Register(from);
}

boost::shared_ptr<RequestArgs> RequestsManager::GetArgs(
    boost::shared_ptr<RequestHandler> request
)
{
    return request->GetArgs();
}

boost::shared_ptr<RequestArgs> RequestsManager::GetArgs(const RequestKey_t &key)
{
    return m_requestsMap[key]->GetArgs();
}

void RequestsManager::HandleSuccess(
    u_int64_t from, 
    const RequestType &rt, 
    const DataRepository::StorageType &st, 
    bool status
)
{
    Handleton<RequestsManager> requestsManager;

    RequestKey_t requestKey(from, rt);
    SubrequestKey_t subrequestKey(from, rt, st);
    SubrequestKey_t otherSubrequestKey(from, rt, DataRepository::StorageType(!st));

    requestsManager->Reply(requestKey, status);

    requestsManager->EraseSubrequest(subrequestKey);

    if (!requestsManager->SubrequestExists(otherSubrequestKey))
    {
        requestsManager->EraseRequest(requestKey);
        std::cout << "handling success" << std::endl;
    }
}

void RequestsManager::EraseRequest(const RequestKey_t &key)
{
    m_requestsMap.erase(m_requestsMap.find(key));
}

void RequestsManager::EraseSubrequest(const SubrequestKey_t &key)
{
    m_attemptsMap.erase(m_attemptsMap.find(key));
}

bool RequestsManager::SubrequestExists(const SubrequestKey_t &key)
{
    return (m_attemptsMap.find(key) != m_attemptsMap.end());
}

void RequestsManager::IncrementAttempts(const SubrequestKey_t &key)
{
    ++m_attemptsMap[key];
}

bool RequestsManager::ReachedAttemptsLimit(const SubrequestKey_t &key)
{
    return (m_attemptsMap[key] >= s_attemptsLimit);
}

void RequestsManager::Reply(const RequestKey_t &key, bool status)
{
    m_requestsMap[key]->Reply(status);
}

const RequestsManager::RequestType RequestsManager::WriteCallbackHandler::s_rt(WRITE);

RequestsManager::WriteCallbackHandler::WriteCallbackHandler(
    u_int64_t from_, DataRepository::StorageType st_
)
    : m_from(from_), m_st(st_)
{}

void RequestsManager::WriteCallbackHandler::operator()(bool status)
{
    Handleton<RequestsManager> requestsManager;
    requestsManager->Callback<WriteAction>(m_from, s_rt, m_st, status);
}

const RequestsManager::RequestType RequestsManager::ReadCallbackHandler::s_rt(READ);

RequestsManager::ReadCallbackHandler::ReadCallbackHandler(
    u_int64_t from_, DataRepository::StorageType st_
)
    : m_from(from_), m_st(st_)
{}

void RequestsManager::ReadCallbackHandler::operator()(bool status)
{
    Handleton<RequestsManager> requestsManager;
    requestsManager->Callback<ReadAction>(m_from, s_rt, m_st, status);
}

RequestsManager::WriteAction::WriteAction(
    boost::shared_ptr<char[]> buf_, 
    u_int64_t from_, 
    DataRepository::StorageType st_
)
    : Action(boost::shared_ptr<CallbackHandler>(
    new WriteCallbackHandler(from_, st_))), 
    m_buf(buf_), m_from(from_), m_st(st_)
{}

void RequestsManager::WriteAction::operator()()
{
    Handleton<DataRepository> dr;
    Action::Callback(dr->Write(m_buf.get(), m_from, m_st));
}

RequestsManager::ReadAction::ReadAction(
    boost::shared_ptr<char[]> buf_, 
    u_int64_t from_, 
    DataRepository::StorageType st_
)
    : Action(boost::shared_ptr<CallbackHandler>(
    new ReadCallbackHandler(from_, st_))), 
    m_buf(buf_), m_from(from_), m_st(st_)
{}

void RequestsManager::ReadAction::operator()()
{
    Handleton<DataRepository> dr;
    Action::Callback(dr->Read(m_buf.get(), m_from, m_st));
}

}
