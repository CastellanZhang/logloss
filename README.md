# logloss
计算分类器结果的logloss，具体公式见：https://www.kaggle.com/wiki/LogarithmicLoss

使用方法：<br>
cat predictFile | ./logloss class_num

输入文件predictFile每一行的格式：<br>
label score_1 score_2 ... score_k

即label后面按顺序跟k个类别的预测分数，label必须是1到k。

注意：程序中没有对k个分数做归一，必须自行保证预测分数是归一的。
