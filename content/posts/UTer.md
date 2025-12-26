---
title: UTer 项目实现日志
---

2025.12.6
遇到了pip install库下载太慢的问题，直接从源网站下载之后离线安装
学习ZeRO-3


H800 跑 40k 的唯一出路：序列并行 (Sequence Parallelism)
如果你非要跑 40k 甚至 100k 的超长上下文，你不能只依靠 DeepSpeed ZeRO-3，你必须引入 序列并行 (Sequence Parallelism) 技术。

目前主流的方案有：

DeepSpeed Ulysses (尤利西斯)：专门针对长文本优化，把 Attention 计算切分到多张卡上。

Ring Attention：环状注意力机制，显存占用极

Flash Attention 2 + Gradient Checkpointing + DeepSpeed ZeRO-3 计算这些技术怎么体现在显存和计算速度上的
