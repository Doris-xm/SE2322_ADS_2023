# hw5 RBtree VS SkipList VS  AVL

### 1. 测试说明

#### 1.1数据说明

**输入数据**为0—`Size-1` 。Size取50,100,2000,5000,10000。分为顺序和乱序两种。

在”./data“ 文件夹下，一个”ran_numx.txt“中分为`insert` 和`search`两部分。

具体顺序为：

```python
Size  #输入大小
0
1
...
Size-1
Size/16 #一个搜索集合大小
...
```

**`search` 的数据集**有五组：Size/16 ; Size/8 ; Size/4 ; Size/2 ; Size

顺序的组从0开始，乱序的组用`rand()%Size` 生成。

查找的数据皆为已插入的。



#### 1.2 衡量标准

使用了`lab1` 提供的函数作为**耗时的度量**，单位为cycles

```cpp
static inline uint64_t rdtsc()
{
    uint32_t low, high;
    asm volatile ("rdtsc" : "=a" (low), "=d" (high));
    return ((uint64_t)high << 32) | low;
}
```

**旋转次数**测试中，认为左旋、右旋为一次旋转。



### 2. 实验数据

#### 2.1 insert

<center>表1 insert时间开销和旋转次数</center>

![1](E:\CppProject\dataStruct2023\hw5\1.png)

对其中的时间开销、旋转次数分别绘制了以下两张图。

![2](E:\CppProject\dataStruct2023\hw5\2.png)

* 上图展示了不同Size下，各种数据结构`insert` 操作的时间开销。

* 其中虚线为顺序插入，实线为乱序，同一种颜色为一种数据结构

* 理论上来说：顺序插入会让AVL、RB树的退化成单链表，需要更多次旋转。

* 实验结果似乎两者耗时区别不大，甚至顺序插入更好，可能的原因有：

  * 数据集较小，使得乱序顺序效率差别不大。

  * 使用`random_shuffle` 打扰数据，可能打乱的效果不好

  * 但根据下图，旋转次数确实是乱序时候少，那么可能是编译器对顺序的数组进行了未知的优化

    



![3](E:\CppProject\dataStruct2023\hw5\3.png)

- 上图展示了不同Size下，`AVL`和`RBtree` 在 `insert` 操作的旋转次数。
- 上方两条为顺序插入结果（由于太接近，重合在一起），下方为乱序
- 理论上来说：顺序插入会让AVL、RB树的退化成单链表，需要更多次旋转。而RBtree的旋转次数比Avltree更好
- 实验结果与理论吻合较好：
  - 顺序插入旋转次数明显多余乱序
  - 在乱序中，`RBtree` 明显比`AVL`旋转次数少。在顺序中由于都退化成单链表，旋转次数一样



#### 2.2 search

<center>表2 search时间消耗对比</center>

![4](E:\CppProject\dataStruct2023\hw5\4.png)

对于每个大小为`total_size` 的数据集，分别进行了：Size/16 ; Size/8 ; Size/4 ; Size/2 ; Size大小的五次查找。并求取了平均查找时长`average`

* 可以看到，在数据比较大的时候，红黑树和跳表都比AVL树有明显优势。红黑树利用染色来优化旋转，跳表用概率维持平衡，都比AVL单纯的旋转来得更高效。

