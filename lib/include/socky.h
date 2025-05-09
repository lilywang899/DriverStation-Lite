/*
 * The Driver Station Library (LibDS)
 * Copyright (c) Lily Wang, Alex Spataru and other contributors.
 * Open Source Software; you can modify and/or share it under the terms of
 * the MIT license file in the root directory of this project.
 */

#ifndef _SOCKY_MAIN_H
#define _SOCKY_MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

/* Includes */
#if defined _WIN32
#   include <winsock2.h>
#   include <ws2tcpip.h>
#else
#   include <fcntl.h>
#   include <errno.h>
#   include <netdb.h>
#   include <string.h>
#   include <unistd.h>
#   include <sys/types.h>
#   include <sys/socket.h>
#endif

/* Socket types */
#define SOCKY_TCP 0x01
#define SOCKY_UDP 0x02

/* IP family types */
#define SOCKY_IPv4 0x03
#define SOCKY_IPv6 0x04
#define SOCKY_ANY 0x05

/* Shutdown methods */
#define SOCKY_READ 0x01
#define SOCKY_WRITE 0x02

/* Set listen() backlog value */
#define SOCKY_BACKLOG 128

/* Misc functions */
extern int sockets_exit(void);
extern int sockets_init(const int exit_on_fail);
extern int set_socket_block(const int sfd, const int block);
extern struct addrinfo *get_address_info(const char *host, const char *service, int socktype, int family);

/* Socket initialization functions */
extern int create_client_udp(const int family, const int flags);
extern int create_client_tcp(const char *host, const char *port, const int family, const int flags);
extern int create_server_udp(const char *port, const int family, const int flags);
extern int create_server_tcp(const char *port, const int family, const int flags);

/* Socket closing functions */
extern int socket_close(const int sfd);
extern void socket_close_threaded(int sfd);
extern int socket_shutdown(const int sfd, const int method);

/* Special TCP functions */
extern int tcp_accept(const int sfd, char *host, const int host_len, char *service, const int service_len,
                      const int flags);

/* Re-implementation of sendto */
extern int udp_sendto(const int sfd, const char *buf, const int buf_len, const char *host, const char *service,
                      const int flags);

/* Re-implementation of recvfrom */
extern int udp_recvfrom(const int sfd, char *buf, const int buf_len, const char *host, const char *service,
                        const int flags);

#ifdef __cplusplus
}
#endif

#endif
