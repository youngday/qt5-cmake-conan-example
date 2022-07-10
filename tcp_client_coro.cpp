#include <iostream>
#include <cstdlib>
#include <string>

#include "main.h"
#include "Logger.h"

#include "co/all.h"

using namespace std;

enum
{
  max_length = 1024
};

extern Logger logger;
extern stringstream logout;
//----------------------------------------------------------------------

bool use_ssl = false;
std::unique_ptr<tcp::Client> proto;

co::Pool pool(
    []()
    { return (void *)new tcp::Client(*proto); },
    [](void *p)
    { delete (tcp::Client *)p; });

void client_fun()
{
  co::PoolGuard<tcp::Client> c(pool);

  if (!c->connect(3000))
  {
    LOG << "connect failed: " << c->strerror();
    return;
  }

  char buf[8] = {0};

  while (true)
  {
    LOG << "client send ping";
    int r = c->send("ping", 4);
    if (r == 4)
    {
      logout.str("");
      logout << "send ok, num:" << r << "\n";
      logger.debug(logout.str());
    }

    if (r <= 0)
    {
      LOG << "client send error: " << c->strerror();
      break;
    }

    // r = c->recv(buf, 8);
    r = c->recv(buf, 100);
    logout.str("");
    logout << "received , num:" << r << "buf:" << buf << "\n";
    logger.debug(logout.str());

    if (r < 0)
    {
      LOG << "client recv error: " << c->strerror();
      break;
    }
    else if (r == 0)
    {
      LOG << "server close the connection";
      break;
    }
    else
    {
      LOG << "client recv " << fastring(buf, r) << '\n';
      co::sleep(3000);
    }
  }
}

int tcp_client_coro()
{
  logout.str("");
  logout << "tcp client start ."
         << "\n";
  logger.debug(logout.str());

  proto.reset(new tcp::Client("127.0.0.1", 8888, use_ssl));

  for (int i = 0; i < 8; ++i)
  {
    go(client_fun);
    logout.str("");
    logout << "tcp client fun ." << i << "\n";
    logger.debug(logout.str());
  }
  return 0;
}
