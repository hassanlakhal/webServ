# 🌐 Webserv - 42 Project

![C++](https://img.shields.io/badge/C++-project-blue?style=for-the-badge)
![42 Network](https://img.shields.io/badge/42%20School-Project-black?style=for-the-badge)
![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)

## 📚 Description

**Webserv** is a C++ web server built from scratch as part of the 42 School curriculum. The objective is to implement an HTTP/1.1-compliant server capable of handling multiple clients, serving static and dynamic content, parsing configuration files, and supporting CGI scripts.

This project focuses on **network programming**, **event-driven I/O**, **multi-client handling**, and **HTTP protocol basics** — without using any high-level web frameworks.

---

## 🧠 Project Goals

- Create a fully functional HTTP server in C++
- Handle multiple clients simultaneously (non-blocking I/O)
- Serve static files (HTML, CSS, etc.)
- Support **CGI execution** (e.g., PHP or Python scripts)
- Parse and handle multiple configuration files
- Implement basic error handling and custom error pages
- Allow multiple server blocks with virtual hosting
- Implement common HTTP features: GET, POST, DELETE

---

## 🛠️ Features

| Feature             | Status |
|---------------------|--------|
| Non-blocking sockets| ✅     |
| Config file parsing | ✅     |
| GET method          | ✅     |
| POST method         | ✅     |
| DELETE method       | ✅     |
| CGI support         | ✅     |
| Chunked transfer    | ✅     |
| Autoindex           | ✅     |
| Custom error pages  | ✅     |
| HTTP/1.1 compliance | ✅     |

---

## 🧱 Tech Stack

- **Language**: C++
- **Network API**: POSIX sockets
- **Event handling**: ` epool ` (platform-dependent)
- **OS**: Linux (Debian/Ubuntu recommended)

---


## 🚀 Getting Started

### 🔧 Prerequisites

- A Linux environment (Debian-based recommended)
- A C++ compiler (e.g., `g++`)
- Make

### 🛠️ Build the Server

```bash
make
```
---

## 🌍 Configuration Example

``` bash
server:
  listen: 2323
  host: 127.0.0.1
  root: ./www
  client_max_body_size: 1G
  server_name: server2

  location:
    - path: /
    - root:  ./www
    - upload: on
    - autoindex: on
    - listing_dir: on
    - upload_path: ./
    - methods: POST GET DELETE
    - index: index.html
    - cgi_path: .php, /usr/bin/php-cgi
