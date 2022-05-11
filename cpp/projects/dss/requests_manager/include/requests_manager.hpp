/*****************************************************************************
Title: requests_manager - Infinity Labs R&D 
Group: RD91
Description: requests_manager API
******************************************************************************/

#ifndef ILRD_RD91_ATTEMPTS_MANAGER_HPP
#define ILRD_RD91_ATTEMPTS_MANAGER_HPP

#include <boost/shared_ptr.hpp> // boost::shared_ptr
#include <sys/types.h> // u_int64_t
#include <boost/tuple/tuple.hpp> // boost::tuple
#include <iostream>
#include "boost/tuple/tuple_comparison.hpp" // added for compiling

#include "requests_api.hpp" // RequestHandler
#include "handleton.hpp" // Handleton
#include "actions_api.hpp" // Action, Callback
#include "data_repository.hpp" // DataRepository::StorageType
#include "kamikaze.hpp" // Kamikaze

namespace ilrd
{

class RequestsManager
{
public:
    void Write(boost::shared_ptr<RequestHandler> request);
    void Read(boost::shared_ptr<RequestHandler> request);

private:
    enum RequestType {WRITE, READ};

    class WriteCallbackHandler : public CallbackHandler
    {
    public:
        WriteCallbackHandler(u_int64_t from_, DataRepository::StorageType st_);
        void operator()(bool status);

    private:
        static const RequestType s_rt;
        u_int64_t m_from;
        DataRepository::StorageType m_st;
    };
    
    class ReadCallbackHandler : public CallbackHandler
    {
    public:
        ReadCallbackHandler(u_int64_t from_, DataRepository::StorageType st_);
        void operator()(bool status);

    private:
        static const RequestType s_rt;
        u_int64_t m_from;
        DataRepository::StorageType m_st;
    };

    class WriteAction : public Action
    {
    public:
        WriteAction(
            boost::shared_ptr<char[]> buf_, 
            u_int64_t from_, 
            DataRepository::StorageType st_
        );
        
        void operator()();

    private:
        boost::shared_ptr<char[]> m_buf;
        u_int64_t m_from;
        DataRepository::StorageType m_st;
    };

    class ReadAction : public Action
    {
    public:
        ReadAction(
            boost::shared_ptr<char[]> buf_, 
            u_int64_t from_, 
            DataRepository::StorageType st_
        );
        void operator()();

    private:
        boost::shared_ptr<char[]> m_buf;
        u_int64_t m_from;
        DataRepository::StorageType m_st;
    };

    typedef std::pair<u_int64_t, RequestType> RequestKey_t;
    typedef boost::tuple<u_int64_t, RequestType, DataRepository::StorageType> SubrequestKey_t;

    static const std::size_t s_startDelay;
    static const std::size_t s_rescheduleDelay;
    static const std::size_t s_attemptsLimit;

    std::map<RequestKey_t, boost::shared_ptr<RequestHandler> > m_requestsMap;
    std::map<SubrequestKey_t, std::size_t> m_attemptsMap;

    friend class Handleton<RequestsManager>;
    RequestsManager();

    static std::size_t GetRescheduleDelay();
    static std::size_t GetAttemptsLimit();

    void Register(
        boost::shared_ptr<RequestHandler> request,
        u_int64_t from, const RequestsManager::RequestType &rt
    );

    template<class ActionT>
    void HandleRequest(
        u_int64_t from, const RequestsManager::RequestType &rt
    );

    template<class ActionT>
    void CreateKamikaze(
        const RequestKey_t &key, 
        const DataRepository::StorageType &st, 
        const std::size_t &delay
    );

    boost::shared_ptr<RequestArgs> GetArgs(
        boost::shared_ptr<RequestHandler> request
    );
    boost::shared_ptr<RequestArgs> GetArgs(const RequestKey_t &key);

    template<class ActionT>
    void Callback(
        u_int64_t from, 
        const RequestType &rt, 
        const DataRepository::StorageType &st, 
        bool status
    );

    void HandleSuccess(
        u_int64_t from, 
        const RequestType &rt, 
        const DataRepository::StorageType &st, 
        bool status
    );

    template<class ActionT>
    void HandleFailure(
        u_int64_t from, 
        const RequestType &rt, 
        const DataRepository::StorageType &st, 
        bool status
    );

    void EraseRequest(const RequestKey_t &key);
    void EraseSubrequest(const SubrequestKey_t &key);

    bool SubrequestExists(const SubrequestKey_t &key);

    void IncrementAttempts(const SubrequestKey_t &key);
    bool ReachedAttemptsLimit(const SubrequestKey_t &key);

    void Reply(const RequestKey_t &key, bool status);
};

#include "requests_manager_impl.hpp" // template implementations

}

#endif // ILRD_RD91_ATTEMPTS_MANAGER_HPP
