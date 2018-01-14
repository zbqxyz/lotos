#ifndef _REQUEST_H__
#define _REQUEST_H__

#include "buffer.h"
#include "connection.h"
#include "misc.h"

#define MAX_HEADERS (20)
#define MAX_ELEMENT_SIZE (2048)

/* basic http method */
typedef enum {
  HTTP_DELETE,
  HTTP_GET,
  HTTP_HEAD,
  HTTP_POST,
  HTTP_PUT,
} http_method;

typedef struct {
  unsigned short http_major;
  unsigned short http_minor;
} http_version;

typedef struct {
  http_method method;
  http_version version;
  bool keep_alive;
  int num_headers;

  char query_string[MAX_ELEMENT_SIZE];
  char request_path[MAX_ELEMENT_SIZE];
  char request_url[MAX_ELEMENT_SIZE];
  char headers[MAX_HEADERS][2][MAX_ELEMENT_SIZE];

  connection_t *c; /* parent connection */
  buffer_t *b;     /* requset buffer */
} request_t;

#endif

/* status code */
#define HTTP_STATUS_MAP(GEN)                                                   \
  GEN(100, CONTINUE, Continue)                                                 \
  GEN(101, SWITCHING_PROTOCOLS, Switching Protocols)                           \
  GEN(102, PROCESSING, Processing)                                             \
  GEN(200, OK, OK)                                                             \
  GEN(201, CREATED, Created)                                                   \
  GEN(202, ACCEPTED, Accepted)                                                 \
  GEN(203, NON_AUTHORITATIVE_INFORMATION, Non - Authoritative Information)     \
  GEN(204, NO_CONTENT, No Content)                                             \
  GEN(205, RESET_CONTENT, Reset Content)                                       \
  GEN(206, PARTIAL_CONTENT, Partial Content)                                   \
  GEN(207, MULTI_STATUS, Multi - Status)                                       \
  GEN(208, ALREADY_REPORTED, Already Reported)                                 \
  GEN(226, IM_USED, IM Used)                                                   \
  GEN(300, MULTIPLE_CHOICES, Multiple Choices)                                 \
  GEN(301, MOVED_PERMANENTLY, Moved Permanently)                               \
  GEN(302, FOUND, Found)                                                       \
  GEN(303, SEE_OTHER, See Other)                                               \
  GEN(304, NOT_MODIFIED, Not Modified)                                         \
  GEN(305, USE_PROXY, Use Proxy)                                               \
  GEN(307, TEMPORARY_REDIRECT, Temporary Redirect)                             \
  GEN(308, PERMANENT_REDIRECT, Permanent Redirect)                             \
  GEN(400, BAD_REQUEST, Bad Request)                                           \
  GEN(401, UNAUTHORIZED, Unauthorized)                                         \
  GEN(402, PAYMENT_REQUIRED, Payment Required)                                 \
  GEN(403, FORBIDDEN, Forbidden)                                               \
  GEN(404, NOT_FOUND, Not Found)                                               \
  GEN(405, METHOD_NOT_ALLOWED, Method Not Allowed)                             \
  GEN(406, NOT_ACCEPTABLE, Not Acceptable)                                     \
  GEN(407, PROXY_AUTHENTICATION_REQUIRED, Proxy Authentication Required)       \
  GEN(408, REQUEST_TIMEOUT, Request Timeout)                                   \
  GEN(409, CONFLICT, Conflict)                                                 \
  GEN(410, GONE, Gone)                                                         \
  GEN(411, LENGTH_REQUIRED, Length Required)                                   \
  GEN(412, PRECONDITION_FAILED, Precondition Failed)                           \
  GEN(413, PAYLOAD_TOO_LARGE, Payload Too Large)                               \
  GEN(414, URI_TOO_LONG, URI Too Long)                                         \
  GEN(415, UNSUPPORTED_MEDIA_TYPE, Unsupported Media Type)                     \
  GEN(416, RANGE_NOT_SATISFIABLE, Range Not Satisfiable)                       \
  GEN(417, EXPECTATION_FAILED, Expectation Failed)                             \
  GEN(421, MISDIRECTED_REQUEST, Misdirected Request)                           \
  GEN(422, UNPROCESSABLE_ENTITY, Unprocessable Entity)                         \
  GEN(423, LOCKED, Locked)                                                     \
  GEN(424, FAILED_DEPENDENCY, Failed Dependency)                               \
  GEN(426, UPGRADE_REQUIRED, Upgrade Required)                                 \
  GEN(428, PRECONDITION_REQUIRED, Precondition Required)                       \
  GEN(429, TOO_MANY_REQUESTS, Too Many Requests)                               \
  GEN(431, REQUEST_HEADER_FIELDS_TOO_LARGE, Request Header Fields Too Large)   \
  GEN(451, UNAVAILABLE_FOR_LEGAL_REASONS, Unavailable For Legal Reasons)       \
  GEN(500, INTERNAL_SERVER_ERROR, Internal Server Error)                       \
  GEN(501, NOT_IMPLEMENTED, Not Implemented)                                   \
  GEN(502, BAD_GATEWAY, Bad Gateway)                                           \
  GEN(503, SERVICE_UNAVAILABLE, Service Unavailable)                           \
  GEN(504, GATEWAY_TIMEOUT, Gateway Timeout)                                   \
  GEN(505, HTTP_VERSION_NOT_SUPPORTED, HTTP Version Not Supported)             \
  GEN(506, VARIANT_ALSO_NEGOTIATES, Variant Also Negotiates)                   \
  GEN(507, INSUFFICIENT_STORAGE, Insufficient Storage)                         \
  GEN(508, LOOP_DETECTED, Loop Detected)                                       \
  GEN(510, NOT_EXTENDED, Not Extended)                                         \
  GEN(511, NETWORK_AUTHENTICATION_REQUIRED, Network Authentication Required)

typedef enum {
#define GEN(num, name, string) HTTP_STATUS_##name = num,
  HTTP_STATUS_MAP(GEN)
#undef GEN
} http_status;
