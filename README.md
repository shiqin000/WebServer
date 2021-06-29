# A C++ Web Server

## 简介

这是一个采用 C++ 11 编写的简易 Web 服务器，支持解析 GET 方法，可处理静态资源。

当前版本：version 0.1

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

- 遵循单一职责原则编写代码
