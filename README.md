# A C++ Web Server

## 简介

这是一个采用 C++ 11 编写的多线程 Web 服务器，支持解析 GET 方法，可处理静态资源。

当前版本：version 2.0

## 开发环境

- 操作系统：Ubuntu 18.04.5 LTS

- 编译器：g++ 7.5.0

- CMake: cmake 3.10.2

## 使用方式

```
cmake . && make
./WebServer <port>
```

## 核心功能与技术

- 遵循《Google 开源项目风格指南》编写程序，维护代码风格的统一

- 使用半同步/半反应堆并发编程模式

- 使用 RAII 手法封装互斥锁(mutex)、信号量(semaphore)、条件变量(condition)等线程同步机制

- 使用智能指针(shared_ptr、weak_ptr、unique_ptr)管理内存，防止内存泄漏

- 线程池使用单例模式实现
