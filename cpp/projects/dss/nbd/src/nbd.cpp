/*****************************************************************************
Title: client_buse - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: client_buse
******************************************************************************/

#define _POSIX_C_SOURCE (200809L)

#include <errno.h> // errno
#include <linux/nbd.h> // nbd flags
#include <signal.h> // sigfillset, sigemptyset, sigaddset, sigprocmask, sigaction
#include <string.h> // strerror
#include <sys/ioctl.h> // ioctl
#include <sys/socket.h> // socketpair
#include <unistd.h> // open, close, fork
#include <exception> // std::runtime_error
#include <stdlib.h> // atoi

#include "nbd.hpp" // api
#include "framework.hpp" // Framework
#include "handleton.hpp" // Handleton
#include "input_proxy.hpp" // InputProxyBase
#include "nbd_proxy.hpp" // NBDProxy
#include "helper.hpp" // ThrowIfBad
#include "runtime_config.hpp" // RuntimeConfig
#include "reactor.hpp" // Reactor::READ

namespace ilrd
{

static int g_nbdDevToDisconnect = -1;
static void DisconnectNBD(int signal)
{
    (void)signal;
    if (g_nbdDevToDisconnect != -1) 
    {
        int status = ioctl(g_nbdDevToDisconnect, NBD_DISCONNECT);
        ThrowIfBad<std::runtime_error>(-1 == status, strerror(errno));
        g_nbdDevToDisconnect = -1;
    }
}

static std::string GetNBDFile()
{
    Handleton<RuntimeConfig> config;
    return config->GetValue(NBD_FILE);
}

static std::size_t GetNBDSize()
{
    Handleton<RuntimeConfig> config;
    return atoi(config->GetValue(NBD_SIZE).c_str());
}

void __attribute__((constructor)) NBD(void)
{
    int sp[2];

    int status = socketpair(AF_UNIX, SOCK_STREAM, 0, sp);
    ThrowIfBad<std::runtime_error>(-1 == status, strerror(errno));

    Handleton<RuntimeConfig> config;
    int nbd = open(GetNBDFile().c_str(), O_RDWR);
    ThrowIfBad<std::runtime_error>(-1 == nbd, strerror(errno));

    status = ioctl(nbd, NBD_SET_SIZE, GetNBDSize());
    ThrowIfBad<std::runtime_error>(-1 == status, strerror(errno));

    status = ioctl(nbd, NBD_CLEAR_SOCK);
    ThrowIfBad<std::runtime_error>(-1 == status, strerror(errno));

    pid_t pid = fork();
    ThrowIfBad<std::runtime_error>(-1 == pid, strerror(errno));

    if (pid == 0) 
    {
        sigset_t sigset;

        status = sigfillset(&sigset);
        ThrowIfBad<std::runtime_error>(-1 == status, strerror(errno));

        status = sigprocmask(SIG_SETMASK, &sigset, NULL);
        ThrowIfBad<std::runtime_error>(-1 == status, strerror(errno));

        status = close(sp[0]);
        ThrowIfBad<std::runtime_error>(-1 == status, strerror(errno));

        status = ioctl(nbd, NBD_SET_SOCK, sp[1]);
        ThrowIfBad<std::runtime_error>(-1 == status, strerror(errno));

#if defined NBD_SET_FLAGS
        int flags = 0;
#if defined NBD_FLAG_SEND_TRIM
        flags |= NBD_FLAG_SEND_TRIM;
#endif
#if defined NBD_FLAG_SEND_FLUSH
        flags |= NBD_FLAG_SEND_FLUSH;
#endif
        status = ioctl(nbd, NBD_SET_FLAGS, flags);
        ThrowIfBad<std::runtime_error>(0 != flags && -1 == status, strerror(errno));
#endif

        status = ioctl(nbd, NBD_DO_IT);
        ThrowIfBad<std::runtime_error>(-1 == status, strerror(errno));

        status = ioctl(nbd, NBD_CLEAR_QUE);
        ThrowIfBad<std::runtime_error>(-1 == status, strerror(errno));

        status = ioctl(nbd, NBD_CLEAR_SOCK);
        ThrowIfBad<std::runtime_error>(-1 == status, strerror(errno));

        exit(0);
    }

    g_nbdDevToDisconnect = nbd;
    struct sigaction act;
    struct sigaction oact;
    act.sa_handler = DisconnectNBD;
    act.sa_flags = SA_RESTART;

    status = sigemptyset(&act.sa_mask);
    ThrowIfBad<std::runtime_error>(-1 == status, strerror(errno));

    status = sigaddset(&act.sa_mask, SIGINT);
    ThrowIfBad<std::runtime_error>(-1 == status, strerror(errno));

    status = sigaddset(&act.sa_mask, SIGTERM);
    ThrowIfBad<std::runtime_error>(-1 == status, strerror(errno));

    status = sigaction(SIGINT, &act, &oact);
    ThrowIfBad<std::runtime_error>(-1 == status, strerror(errno));

    status = sigaction(SIGTERM, &act, &oact);
    ThrowIfBad<std::runtime_error>(-1 == status, strerror(errno));

    status = close(sp[1]);
    ThrowIfBad<std::runtime_error>(-1 == status, strerror(errno));

    boost::shared_ptr<InputProxy> inputProxy(new NBDProxy(sp[0]));

    Handleton<Framework> framework;
    framework->Register(inputProxy, Reactor::READ, sp[0]);
}

}

/*****************************************************************************/
