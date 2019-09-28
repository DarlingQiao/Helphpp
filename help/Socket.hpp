#pragma once

#include <system_error>
#include <string>
#include <memory>


#ifdef _MSC_VER
#pragma comment(lib, "Ws2_32.lib")

#include <windows.h>
#endif

namespace net {

	//Address families协议域
	enum class AddressFamily : int{
		af_inet = AF_INET,
	};

	//socket类型
	enum class SocketTypes : int {
		stream = 1,
		dgam = 2,
		raw = 3,
		rem = 4,
		seqpacket = 5
	};

	//指定协议
	enum class SocketProtocol : int {
		//#define IPPROTO_IP              0               /* dummy for IP */
		//#define IPPROTO_ICMP            1               /* control message protocol */
		//#define IPPROTO_IGMP            2               /* group management protocol */
		//#define IPPROTO_GGP             3               /* gateway^2 (deprecated) */
		//#define IPPROTO_TCP             6               /* tcp */
		//#define IPPROTO_PUP             12              /* pup */
		//#define IPPROTO_UDP             17              /* user datagram protocol */
		//#define IPPROTO_IDP             22              /* xns idp */
		//#define IPPROTO_ND              77              /* UNOFFICIAL net disk proto */

		//#define IPPROTO_RAW             255             /* raw IP packet */
		//#define IPPROTO_MAX             256
	};

	class Socket {
	protected:
		int socket_;
		std::string ip_;
		std::size_t port_;
		int af_;
		int type_;
		int protocol_;
    sockaddr sockaddr_;
	public:
		Socket() : socket_(-1), ip_(""), port_(0) {
		};

		Socket(const std::string& ip, const std::size_t& port, int af, int type, int protocol)
			: socket_(-1), ip_(ip), port_(port), af_(af), type_(type), protocol_(protocol) {
      memset(&socket_, 0, sizeof(socket_));
		}
    Socket(const Socket*) = delete;
    Socket(const Socket&) = delete;
    Socket(const Socket&&) = delete;
    Socket &operator=(const Socket&&) = delete;
    Socket &operator=(const Socket&) = delete;
    Socket &operator=(const Socket*) = delete;
 

		virtual ~Socket() { //父类虚析构函数
		}

    virtual std::error_code Create(std::error_code& ec) = 0;
		virtual std::error_code Control(long cmd, unsigned long* argp, std::error_code& ec) = 0;//int ioctlsocket( int s, long cmd, u_long * argp);
		virtual std::error_code Write(const char* p, const std::size_t& size, std::size_t &len, std::error_code& ec) = 0;
		virtual std::error_code Read(char* p, const std::size_t& size, std::size_t& len, std::error_code& ec) = 0;
		virtual std::error_code Close(std::error_code& ec) = 0;
    virtual std::error_code Connect(std::error_code& ec) = 0;
    virtual std::error_code Accept(int *len, std::error_code& ec) = 0;
    virtual std::error_code Listen(int szie, std::error_code& ec) = 0;
    virtual std::error_code Bind(std::error_code& ec) = 0;

    void SetIp(const std::string& ip) {
      ip_ = ip;
    }

    void SetPort(const std::size_t& port) {
      port_ = port;
    }
	protected:
    virtual std::error_code Init(std::error_code& ec) = 0;
    virtual void Destroy() = 0;
	private:

	};


	class SocketWin : public Socket {
	public:
    using Socket::Socket;

    virtual ~SocketWin() {
      Destroy();
    }

    std::error_code Create(std::error_code& ec) override {
      ec.clear();
      if (Init(ec)) {
        return ec;
      }
      socket_ = (int)socket(af_, type_, protocol_);//socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
      if (socket_ <= SOCKET_ERROR) {
        return ec = std::error_code(WSAGetLastError(), std::system_category());
      }
      return ec;
    }

		std::error_code Control(long cmd, unsigned long* argp, std::error_code& ec) override {
      *argp = 0;
      ec.clear();
			if (ioctlsocket(socket_, cmd, argp) != NO_ERROR) {
				return ec = std::error_code(GetLastError(),std::system_category());
			}
			return ec;
		}

		std::error_code Write(const char* p, const std::size_t& size, std::size_t &len, std::error_code& ec) override {
      len = 0;
      ec.clear();
      len = send(socket_,p,size,0);
      if (SOCKET_ERROR == len) {
        return ec = std::error_code(WSAGetLastError(),std::system_category());
      }
      return ec;
		}

		std::error_code Read(char* p, const std::size_t& size, std::size_t& len, std::error_code& ec) override {
      ec.clear();
      len = recv(socket_, p, size, 0);
      if (SOCKET_ERROR == len) {
        return ec = std::error_code(WSAGetLastError(), std::system_category());
      }
      return ec;
		}

		std::error_code Close(std::error_code& ec) override {\
      ec.clear();
			if (socket_ > SOCKET_ERROR && closesocket(socket_) != NO_ERROR) {
        return ec = std::error_code(WSAGetLastError(), std::system_category());
			}
			socket_ = SOCKET_ERROR;
      return ec;
		}

    std::error_code Connect(std::error_code& ec) override {
      ec.clear();
      auto name = (SOCKADDR_IN*)&sockaddr_;
      /*auto sin = static_cast<SOCKADDR_IN*>(name);*/
      name->sin_family = af_;
      auto addr = inet_addr(ip_.c_str());
      if (addr == -1) {
        WSACleanup();
        return ec = std::error_code(WSAGetLastError(), std::system_category());
      }
      name->sin_addr.S_un.S_addr = addr;
      name->sin_port = htons(port_);
      auto ret = connect(socket_, &sockaddr_, sizeof(sockaddr));
      if (ret != NO_ERROR) {
        WSACleanup();
        return ec = std::error_code(WSAGetLastError(), std::system_category());
      }
      return ec;
    };

    std::error_code Accept(int* len, std::error_code& ec) override {
      ec.clear();
      auto ret = accept(socket_, &sockaddr_, len);
      if (ret != NO_ERROR) {
        return ec = std::error_code(WSAGetLastError(), std::system_category());
      }
      return ec;
    }

    std::error_code Listen(int size, std::error_code& ec) override {
      ec.clear();
      auto ret = listen(socket_, size);
      if (ret != NO_ERROR) {
        return ec = std::error_code(WSAGetLastError(), std::system_category());
      }
      return ec;
    }

    std::error_code Bind(std::error_code& ec) override {
      ec.clear();
      auto name = (SOCKADDR_IN*)&sockaddr_;
      /*auto sin = static_cast<SOCKADDR_IN*>(name);*/
      name->sin_family = af_;
//       auto addr = inet_addr(ip_.c_str());
//       if (addr == -1) {
//         WSACleanup();
//         return ec = std::error_code(WSAGetLastError(), std::system_category());
//       }
      name->sin_addr.S_un.S_addr = htonl(INADDR_ANY);
      name->sin_port = htons(port_);
      auto ret = bind(socket_, &sockaddr_, sizeof(sockaddr_));
      if (socket_ != NO_ERROR) {
        WSACleanup();
        return ec = std::error_code(WSAGetLastError(), std::system_category());
      }
      return ec;
    }
		
	protected:
		std::error_code Init(std::error_code& ec) override {
      ec.clear();
			WSADATA wsaData;
			auto ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
			if (ret != NO_ERROR) {
				return ec = std::error_code(WSAGetLastError(), std::system_category());
			}
      //检测版本号
      if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wHighVersion) != 2) {
        WSACleanup();
        return ec = std::error_code(-1,std::system_category());
      }
			return ec;
		}

    void Destroy() override {
      std::error_code ec;
      Close(ec);
      WSACleanup();
    };

	private:

	};



  class TcpShortConnectClient {
  private:
    std::shared_ptr<SocketWin> ptr_;
  public:
    TcpShortConnectClient(const std::string& ip, std::size_t& port) {
      ptr_ = std::make_shared<SocketWin>(ip, port, AF_INET, SOCK_STREAM, IPPROTO_TCP);
    }

    virtual ~TcpShortConnectClient() {
    }

    virtual std::error_code Do(const char* buffer) {
      std::error_code ec;
      unsigned long cc = 0;
//       std::cout << t.Create(ec) << std::endl;
//       std::cout << t.Control(FIONBIO, &cc, ec) << "##" << cc << std::endl;
//       std::cout << "connect" << t.Connect(ec) << std::endl;
// 
//       char tp[1000] = { 0 };
//       std::size_t a = 0;
//       std::cout << "w " << t.Write(in.data(), in.length(), a, ec) << "## " << a << std::endl;
//       std::cout << "r " << t.Read(tp, sizeof(tp), a, ec) << "## " << a << std::endl;
//       std::cout << "c " << t.Close(ec) << "## " << a << std::endl;
    }

  };


#if 0
  class TcpWin : protected SocketWin {
  private:
    //std::unique_ptr<Socket> s_;
  public:
    TcpWin(const std::string& ip, const std::size_t& port, int af)
      : SocketWin(ip,port,af, SOCK_STREAM, IPPROTO_TCP) {
    }

    TcpWin(const std::string& ip, const std::size_t& port, int af = AF_INET)
      : SocketWin(ip, port, af, SOCK_STREAM, IPPROTO_TCP) {
    }
  };

  enum class socket_types {
    base,
    tcp,
    udp,
  };
  enum class os_types {
    win,
    linux,
  };

  class SocketFactory {
  public:
    std::unique_ptr<Socket> Create(const socket_types& t, const os_types& os) {
      if (os == os_types::win) {
        switch (t) {
        case socket_types::tcp: return std::make_unique<SocketWin>(ip, port, af, SOCK_STREAM, IPPROTO_TCP);
        default: return std::make_unique<SocketWin>();
        }
      } else {
      }
    }
  };
#endif

}