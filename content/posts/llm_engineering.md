---
title: 大模型工程的思考
---

实现sql生成：可以使用函数调用，agent，multiagnet，tool，RAG... 到底如何选择？

RAG在没有证据时可以返回标准化的回退结果

学习langchain源码中的prompt写法

20min 1.7B

>> 简历新增
数据集构造
微调
部署
agent
    使用GO-UT-Bench数据集微调Qwen3-1.7B
    使用xxx部署微调后的模型

max_length与效果

调试prompt