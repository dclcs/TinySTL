# TinySTL

## new expression
```c++
Complex* pc = new Complex(1, 2);
```
被编译器转换为

```c++
void *mem = operator new(sizeof(Complex));
pc = static_cast<Complex*>(mem);
pc->Complex::Complex(1, 2); //只有编译器可以直接调用ctor
```
`new` 本质上是调用`malloc`

## delete expression

```c++
delete pc;
```
被编译器转换为
```c++
pc->~Complex(); //可以直接调用析构函数
operator delete(pc)
```


## Allocator

###### ROUNDUP 函数

```c++
static size_t ROUND_UP(size_t bytes){
    return ( ((bytes) + __ALIGN - 1 ) & ~(__ALIGN - 1) );
}
```

- 将bytes对齐至八个字节，其中用到取反和位运算

    - 7 - 反码（0111 - 1000）
    - 13 - 10100 & 1,1000 = 10000
###### 辅助方法

- `uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result)`
    - 将`[first, last)`的数据复制到以`result`为起始点的空间中

- `uninitialized_fill_n(ForwardIterator first,Size n, const T& x)`
    - 从`first`开始填充`n`个值，默认值为`x`

- `uninitialized_fill(ForwardIterator first, ForwardIterator last,const T& x )`
    - 将`[first, last)`填充值为`n`
    
    
## Container

---

[1.  vector](notes/vector.md)