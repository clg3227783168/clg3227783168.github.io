---
title: "解决 Marp 中文 PDF 导出问题"
date: 2025-09-15
tags: ["Marp", "Hugo", "字体"]
categories: ["技术教程"]
---

## 问题描述

使用 Marp for VS Code 将 Markdown 转换为 PDF 时，中文字体无法正常显示。

## 解决方法

安装 `noto-cjk` 字体库。

```bash
sudo apt-get install fonts-noto-cjk
```

以下为2025-11-09修改
本质上是机器中无中文字体
使用fc-list查看全部字体
使用fc-list :lang=zh查看中文字体
下载中文字体到字体目录/usr/share/fonts/
mkfontscale && mkfontdir && fc-cache刷新缓存