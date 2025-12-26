项目背景: 
具体工作: 
    模式链接生成: 使用三重Few-Shot Examples召回算法: 基于表名称的 Jaccard 相似度; 基于关键词匹配的相似度; 基于文本语义的相似度
    sql语句语句生成: 基于“自然语言关键词”到“SQL 关键字”的映射
    目标问题包含的关键词,寻找样本 SQL 中包含的特征,权重,解释
"""每个"", ""每种"", ""各"", ""不同""",GROUP BY,High,涉及分组聚合
"""平均""",AVG(),Med,涉及数学计算
"""总共"", ""一共""",SUM(),Med,涉及数学计算
"""最大"", ""最高"", ""最多""",ORDER BY ... DESC + LIMIT 1 / MAX(),High,涉及排序或极值
"""前 3 名"", ""前 5 个""",LIMIT,High,涉及截断
"""大于"", ""小于"", ""不等于""",WHERE ... > / < / !=,Low,基础筛选（大部分都有）
"""第 X 高"", ""排名""","Window Function (RANK, ROW_NUMBER)",Critical,涉及高级窗口函数
"""和"", ""以及"" (连接名词)","OR, IN",Med,逻辑连接
    策略：如果目标问题里有“每个（Group By暗示）”和“前3名（Limit暗示）”，那么在 15 条样本中，同时拥有 GROUP BY 和 LIMIT 子句的样本得分最高，哪怕它是查完全不同的表。
    在 Schema Linking（模式链接） 阶段，由于主要任务是**“找准列”和“理清业务逻辑”**，你的召回（Retrieval）规则必须高度依赖 表名（Tables） 和 业务关键词（Keywords）。由于你已经知道每一条待测问题的 table_list（这是已知条件），这是你最大的优势。建议采用 “表重合度为主，语义相似度为辅” 的混合打分策略。核心召回规则逻辑我们将为 15 条已知的 Example 计算对当前 Target Question 的得分，取 Top 3。$$Score = (W_1 \times S_{Table}) + (W_2 \times S_{Logic}) + (W_3 \times S_{Text})$$1. 表重合度得分 ($S_{Table}$) —— 权重 60%原理：Schema Linking 最怕选错表。如果 Example 用了 dws_login，而 Target 也要查 dws_login，那么这个 Example 里对 dt, userid 的处理方式极具参考价值。算法：Jaccard 相似度。$$S_{Table} = \frac{|Tables_{Target} \cap Tables_{Example}|}{|Tables_{Target} \cup Tables_{Example}|}$$2. 逻辑特征匹配得分 ($S_{Logic}$) —— 权重 30%原理：针对那些复杂的“派生指标”（LTV、留存、流失、排名）。如果是计算“留存”，必须找一个计算过“留存”的 Example，哪怕表名不同。算法：关键词硬匹配。特征词库：retention: ["留存", "次留", "三留", "7留", "回流"]rank: ["排名", "前x", "最高", "最低", "top"]ltv: ["ltv", "生命周期价值", "arpu", "付费率"]time_calc: ["近30天", "连续", "累计", "同时"]string_op: ["分割", "截取", "包含", "匹配"] (针对 knowledge 里的复杂逻辑)3. 文本语义相似度 ($S_{Text}$) —— 权重 10%原理：作为兜底。当表都对不上，也没有特殊逻辑时，找字面意思相近的。算法：TF-IDF 余弦相似度 或 简单的字面重叠率。


挑战：数据量太小->生成数据
    数据生成的策略:...
    数据集的制作可以参考bird的文章
权衡pass@9和tempreture

we are welcome to any findings during experiments about interaction with database values. For example, we find that GPT4-32k even fails to consider the tied results in a joined tables correctly.
我们欢迎您在实验过程中分享任何关于数据库值交互的发现。例如，我们发现 GPT4-32k 甚至无法正确处理连接表中的并列结果。
In the dev_1388, the predicted SQL of GPT4-32k is:
在 dev_1388 中，GPT4-32k 的预测 SQL 为：

Question: Which students manage to generate the highest income. State his/her name along with the income source.
SELECT T1.first_name, T1.last_name, T2.source  
FROM member AS T1  
INNER JOIN income AS T2 ON T1.member_id = T2.link_to_member  
WHERE T2.amount = (  
    SELECT MAX(amount)  
    FROM income  
)  
ORDER BY T2.amount DESC
it leads to a NULL result set since MAX(amount) is 3000 in the orignal table income. However, the ground-truth SQL should consider the MAX(amount) in the joined table pertaining to tables member and income. Therefore, the largest amount is only 50, and the ground-truth SQL should be:
由于原始表 income 中 MAX(amount) 为 3000 因此会导致 NULL 结果集。然而，正确的 SQL 语句应该考虑连接表 member 和 income 中 MAX(amount) 值。因此，最大金额仅为 50 ，正确的 SQL 语句应该是：

SELECT T1.first_name, T1.last_name, T2.source
FROM member AS T1
INNER JOIN income AS T2
ON T1.member_id = T2.link_to_member
WHERE T2.amount = (
    SELECT MAX(T4.amount)
    FROM member AS T3
    INNER JOIN income AS T4
    ON T3.member_id = T4.link_to_member
    )
We hypothesize that GPT-4 is pre-trained based on semantic parsing framework, losing the enough attention on values. This may also be marked as the initial challenge in achieving Artificial General Intelligence (AGI) for real-world text-to-SQL applications.
我们推测，GPT-4 是基于语义解析框架进行预训练的，因此对数值的关注度不足。这或许也是实现面向实际文本到 SQL 应用的通用人工智能（AGI）所面临的首要挑战。

分析为什么复杂流程不如直接推理
分析为什么微调小模型不如大模型

误解数据库内容（Misunderstanding Database Content，占40.8%）：当ChatGPT无法回忆起正确的数据库结构（例如，rtype不属于satscores表）或生成假的schema项（例如，lap_records没有出现在formula_1数据库中）时，尤其是当数据库非常大时，就会发生这种情况。在这种情况下，如何使模型真正理解数据库结构和内容仍然是LLMs中的一个痛点话题。-->如何解决这个问题

为什么选择bird?
因为bird特别关注大型数据库内容