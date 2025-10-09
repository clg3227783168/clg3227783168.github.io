---
title: gopack
---

项目如何实现不依赖Docker?
使用 Google 的 go-containerregistry 库中的 crane工具来直接处理容器镜像，而不需要 Docker daemon。包括加载基础镜像，创建自定义层，保存镜像到本地tar文件。

如何实现静态分析？
使用语法树